#include "apc.h"

/*
*
*
* Function Name: subtraction()
*
* Purpose:Performs subtraction of two arbitrary precision integers represented using doubly linked lists.
*
* Algorithm:
*   Traverse both operands from the least significant digit.
*   Apply any borrow from the previous operation.
*   Compare the current digits.
*   If the minuend digit is smaller, borrow from the next higher digit.
*   Compute the difference.
*   Insert the difference digit at the beginning of the result list.
*   Continue until all digits of the larger operand are processed.
*
*
* Assumption: The function assumes that the first operand is greater than or equal to the second operand in magnitude.
*           operand1 ≥ operand2
* This comparison is performed before calling the function.
*
*
* Parameters:
*   tail1 : Tail pointer of the larger operand.
*   tail2 : Tail pointer of the smaller operand.
*   headR : Address of result head.
*   tailR : Address of result tail.
*
*
* Return Value:No direct return value (void).Result is stored in the result linked list.
*
*
*/

/* Function to perform subtraction of two APC numbers */
void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    // Stores borrow generated during subtraction
    int borrow = 0;

    // Stores operand digits and subtraction result
    int digit1,digit2,diff;

    // Traverse from LSD to MSD
    while(tail1){
        // Default digit value when second operand becomes shorter
        digit2 = 0;
        
        // Fetch current digit from first operand and apply borrow
        digit1 = (tail1->data) - borrow;

        // Move towards MSD
        tail1 = tail1 -> prev;
        
        // Fetch digit from second operand if available
        if(tail2){
            digit2 = tail2->data;
            tail2 = tail2->prev;    
        }

        // Borrow from next higher digit if required
        if(digit1 < digit2){
            digit1 += 10;
            borrow = 1;
        }
        else{
            borrow = 0;
        }

        // Compute difference of current digits
        diff = digit1 - digit2;

        // Store result digit in result list
        if(insert_first(headR, tailR, diff) != SUCCESS){
            fprintf(stderr,"ERROR: Subtraction operation failed\n");
            return;
        } 
    }
}
