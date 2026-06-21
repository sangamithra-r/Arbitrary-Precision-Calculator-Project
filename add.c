#include "apc.h"
/*
*
* Function Name: addition()
* Purpose: Performs addition of two arbitrary precision integers represented using doubly linked lists.
*
* Algorithm:
*   Traverse both operand lists from tail (Least Significant Digit).
*   Add corresponding digits along with carry.
*   Store carry for the next iteration.
*   Insert the result digit at the beginning of the result list.
*   Continue until both operands and carry are exhausted.
*
* Parameters:
*   tail1 : Tail pointer of first operand.
*   tail2 : Tail pointer of second operand.
*   headR : Address of result list head.
*   tailR : Address of result list tail.
*
* Return Value: No return value (void). Result is stored in the result linked list.
*
*
/* Function to perform addition of two APC numbers */
void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    // Stores digits from operand1 and operand2, intermediate sum and result digit and carry
    int digit1, digit2, sum, result_digit;
    int carry = 0;

    // Continue until both operands and carry are exhausted
    while(tail1 || tail2 || carry){
        // Default digit value when operand length differs
        digit1 = 0;
        digit2 = 0;

        // Fetch digit from operand1 and move towards MSD
        if(tail1){
            digit1 = tail1->data;
            tail1 = tail1->prev;
        }

        // Fetch digit from operand2 and move towards MSD
        if(tail2){
            digit2 = tail2->data;
            tail2 = tail2->prev;
        }

        // Add digits along with carry
        sum = digit1 + digit2 + carry;

        // Calculate carry for next iteration
        carry = sum / 10;

        // Extract current result digit
        result_digit = sum % 10;

        // Insert result digit at beginning of result list
        if(insert_first(headR, tailR, result_digit) != SUCCESS){
            fprintf(stderr,"ERROR: Addition operation failed\n");
            return;
        } 
    }
}
