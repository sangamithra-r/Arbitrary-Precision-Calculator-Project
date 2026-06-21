/*
* ===========================================================================================================================
* Author : Sangamithra R
* 
* ===========================================================================================================================
*	
* DESCRIPTION:
* The Arbitrary Precision Calculator (APC) is a command-line application developed in C to perform arithmetic operations 
* on integers of arbitrary length. Standard data types such as int, long, and long long have limited storage capacity and 
* cannot represent extremely large numbers accurately. To overcome this limitation, the APC stores each digit of a number 
* in a doubly linked list, enabling calculations on numbers of virtually unlimited size.
*
* The calculator supports Addition, Subtraction, Multiplication, Division, Modulus, and Power operations. Each operand is 
* represented as a doubly linked list where every node stores a single digit. Arithmetic operations are performed digit by
* digit, similar to manual calculations, ensuring accurate results even for very large numbers.
*
* OBJECTIVE: 
* The objective of this project is to design and implement an Arbitrary Precision Calculator capable of performing arithmetic
* operations on very large integers that exceed the storage capacity of standard C data types. The project utilizes doubly 
* linked lists and dynamic memory allocation to achieve arbitrary precision arithmetic.
*
* PROBLEM STATEMENT:
* Built-in data types in C have fixed memory sizes and therefore impose limitations on the range of values that can be stored.
* When calculations involve very large numbers, overflow occurs and incorrect results are produced. The APC addresses this 
* problem by representing numbers as linked lists and performing arithmetic operations manually at the digit level.
*
* =============================================================================================================================
* Data Structure : Doubly Linked List (Big Integer)
* =============================================================================================================================
*
* Example :
* Number : 1 2 3 4 5
* NULL <-- [1] <--> [2] <--> [3] <--> [4] <--> [5] --> NULL
*          ^                                    ^
*          head                                tail
*
* head points to the Most Significant Digit.
* tail points to the Least Significant Digit.
* Arithmetic operations begin from the tail.
*
* Command : ./a.out <operand1> <operator> <operand2>
*
* Supported Operators : Addition(+) ,Subtraction(-) ,Multiplication(x)(X) ,Division(/) , Modulus(%), Power(^)   
*
* ===========================================================================================================================
* Compilation
* ===========================================================================================================================
* Using Makefile : make
* Manual Compilation : gcc *.c -o a.out
*
*
*
*
*/


#include "apc.h"

// Entry point: parses arguments, builds operand lists, and calls the correct operation
int main(int argc, char *argv[])
{

	// Declare head and tail pointers for both operands and the result list
    node *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL, *headR = NULL, *tailR = NULL;

    // Validation
	// Exit early if arguments are invalid
	if((cla_validation(argc,argv)) != SUCCESS){
		return FAILURE;
	}

	// Get the sign of both operands (+1 for positive, -1 for negative)
	int sign1 = checksign(argv[1]);
	int sign2 = checksign(argv[3]);

    // Create 2 lists of operands	
	create_list(argv[1],&head1,&tail1);
	create_list(argv[3],&head2,&tail2);

    // Remove pre zeros
	remove_pre_zeros(&head1);
	remove_pre_zeros(&head2);

	int result_sign, cmp; // Variable to store the result sign and compare_list function result
    char oper = argv[2][0]; // Extract the operator character from argv[2]

	// Switch function to get the correct arithmetic function based on the operator
    switch(oper)
    {

	// Perform addition operation
	case '+':
	{
		// Same sign: add magnitudes and apply the common sign
	    if(sign1 == sign2){
			addition(tail1,tail2, &headR, &tailR);
			result_sign = sign1;
		}
		else{
			// Different signs: subtract smaller magnitude from larger
			cmp = compare_list(head1,head2);

			if(cmp == SAME){
				insert_first(&headR, &tailR, 0);
				result_sign = 1;
			}
			else if(cmp == OPERAND1){
				// |operand1| > |operand2|: result takes sign of operand1
				subtraction(tail1,tail2, &headR, &tailR);
				result_sign = sign1;
			}
			else{
				// |operand2| > |operand1|: result takes sign of operand2
				subtraction(tail2,tail1, &headR, &tailR);
				result_sign = sign2;
			}
		}
	}
	break;

	// Perform Subtraction operation
	case '-':
	{	
	    // If operands have different signs, perform addition of magnitudes	
		if(sign1 != sign2){
			addition(tail1,tail2, &headR, &tailR);
			result_sign = sign1;
		}
		else{
			cmp = compare_list(head1,head2);
        	// Compare magnitudes of both operands
			// If both operands are equal, result is zero
			if(cmp == SAME){
				insert_first(&headR, &tailR, 0);
				result_sign = 1;
			}
			// If operand1 magnitude is larger, perform operand1 - operand2
			else if(cmp == OPERAND1){
				subtraction(tail1,tail2, &headR, &tailR);
				result_sign = sign1;				
			}
			// If operand2 magnitude is larger, perform operand2 - operand1
			else{
				subtraction(tail2,tail1, &headR, &tailR);
				// Result sign becomes opposite of operand1 sign
				result_sign = -sign1;
			}
		}
	}
	break;

	case 'x':
	case 'X':

		// If any operand is zero, product is zero
		if(is_zero(head1) ==  SUCCESS || is_zero(head2) == SUCCESS){
			insert_first(&headR, &tailR, 0);
			result_sign = 1;
			break;
		}

		// Determine sign of multiplication result
		if(sign1 != sign2){
			result_sign = -1;
		}
		else{
			result_sign = 1;
		}

		// Perform multiplication
		multiplication(tail1,tail2, &headR, &tailR);

	    break;

	case '/':
	{
		// Division by zero is not allowed
		if(is_zero(head2) == SUCCESS){
			fprintf(stderr,"Error: Division by zero\n");
			return FAILURE;
		}

		// Zero divided by any number is zero
		if(is_zero(head1) == SUCCESS){
			insert_first(&headR, &tailR, 0);
			result_sign = 1;
			break;
		}

		// If dividend is smaller than divisor, quotient is zero
		if(compare_list(head1,head2) == OPERAND2){
			insert_first(&headR, &tailR, 0);
			result_sign = 1;
			break;
		}

		// If both operands are equal, quotient is one
		if(compare_list(head1,head2) == SAME){
			insert_first(&headR, &tailR, 1);
			if(sign1 != sign2){
				result_sign = -1;
			}
			else{
				result_sign = 1;
			}
			break;
		}
		
		// Division by one returns the dividend itself
		if(head2 && head2->data == 1 && head2->next == NULL){
			headR = head1;
			tailR = tail1;

			if(sign1 != sign2){
				result_sign = -1;
			}
			else{
				result_sign = 1;
			}

			break;
		}

		// Stores remainder returned by division function
		node *headRem = NULL;
		node *tailRem = NULL;

		// Determine quotient sign
		if(sign1 != sign2){
			result_sign = -1;
		}
		else{
			result_sign = 1;
		}

		// Perform division
		division(head1, head2, tail2,&headR, &tailR,&headRem, &tailRem);
		// Free remainder list as quotient alone is required
		delete_list(&headRem, &tailRem);

	}
	break;

	case '%':
	{
		// Modulus by zero is not allowed
		if(is_zero(head2) == SUCCESS){
			fprintf(stderr,"Error: Modulus by zero\n");
			return FAILURE;
		}

		// Zero modulus any number is zero
		if(is_zero(head1) == SUCCESS){
			insert_first(&headR, &tailR, 0);
			result_sign = 1;
			break;
		}

		// If dividend is smaller than divisor, remainder is dividend
		if(compare_list(head1,head2) == OPERAND2){
			headR = head1;
			tailR = tail1;
			result_sign = sign1;
			break;
		}

		// Equal operands give remainder zero
		if(compare_list(head1,head2) == SAME){
			insert_first(&headR, &tailR, 0);
			result_sign = 1;
			break;
		}

		// Any number modulus one is zero
		if(head2 && head2->data == 1 && head2->next == NULL){
			insert_first(&headR, &tailR, 0);
			result_sign = 1;
			break;
		}

		// Perform modulus operation
		modulus(head1, head2, tail2, &headR, &tailR);
		// Remainder takes dividend sign
    	result_sign = sign1;

	}
	break;

	case '^':
		// 0^0 is mathematically undefined
    	if(is_zero(head1) == SUCCESS && is_zero(head2) == SUCCESS)
    	{
        	fprintf(stderr, "ERROR: 0^0 is undefined\n");
        	return FAILURE;
    	}

		// 0^n = 0
    	if(is_zero(head1) == SUCCESS)
    	{
        	insert_first(&headR, &tailR, 0);
        	result_sign = 1;
        	break;
    	}

		// n^0 = 1
    	if(is_zero(head2) == SUCCESS)
    	{
        	insert_first(&headR, &tailR, 1);
        	result_sign = 1;
        	break;
    	}

		// n^1 = n
    	if(head2->data == 1 && head2->next == NULL)
    	{
        	copy_list(head1, tail1,&headR, &tailR);
        	result_sign = sign1;
        	break;
    	}

		// 1^n = 1
    	if(head1->data == 1 && head1->next == NULL)
    	{
        	insert_first(&headR, &tailR, 1);
        	result_sign = 1;
        	break;
    	}

		// Determine sign for power operation
    	if(sign1 == 1)
    	{
        	result_sign = 1;
    	}
    	else
    	{
			// Negative base with odd exponent gives negative result
        	if(is_odd(tail2))
        	{
            	result_sign = -1;
        	}
			// Negative base with even exponent gives positive result
        	else
        	{
            	result_sign = 1;
        	}
    	}
		// Perform exponentiation
    	power(head1, tail1,head2, tail2,&headR, &tailR);

    	break;

	default:
		// Invalid operator entered
	    printf("Invalid operator\n");
    }

	// Remove leading zeros from final result
	remove_pre_zeros(&headR);
	
	// Print negative sign if result is negative
	if(result_sign == -1){
		printf("-");
	}
	// Display final result
	print_list(headR);
	printf("\n");

	// Indicate successful execution
	return SUCCESS;
	
}

