#include "apc.h"

/*
*
* Function Name: power()
* 
* Purpose: Computes the exponentiation of an arbitrary precision integer using repeated multiplication.
*
* Algorithm:
*   Create a copy of the exponent to avoid modifying the original operand.
*   Initialize the result as 1.
*   Repeatedly multiply the current result with the base.
*   Decrement the exponent after each multiplication.
*   Continue until the exponent becomes zero.
*   Store the final result in the result list.
*   Free the copied exponent list.
*
*
* Parameters:
*   headBase : Head pointer of base operand.
*   tailBase : Tail pointer of base operand.
*   headExp : Head pointer of exponent operand.
*   tailExp : Tail pointer of exponent operand.
*   headR : Address of result head.
*   tailR : Address of result tail.
*
* Return Value: No direct return value (void).Result is stored in the result linked list.
*
*
*/

/* Function to perform exponentiation using repeated multiplication */
void power(node *headBase, node *tailBase,node *headExp, node *tailExp,node **headR, node **tailR)
{
    // Copy of exponent used for repeated decrement
    node *headExpCopy = NULL;
    node *tailExpCopy = NULL;

    // Temporary result generated after each multiplication
    node *headTemp = NULL;
    node *tailTemp = NULL;

    // Create a copy of exponent to preserve original operand
    copy_list(headExp, tailExp,&headExpCopy,&tailExpCopy);

    // Initialize result as 1
    insert_first(headR, tailR, 1);

    // Repeat multiplication until exponent becomes zero
    while(is_zero(headExpCopy) == FAILURE)
    {
        // Multiply current result with base
        multiplication(*tailR,tailBase,&headTemp,&tailTemp);

        // Delete previous result
        delete_list(headR, tailR);

        // Update result with newly generated product
        *headR = headTemp;
        *tailR = tailTemp;

        // Reset temporary pointers
        headTemp = NULL;
        tailTemp = NULL;

        // Decrement exponent by one
        decrement(&headExpCopy,&tailExpCopy);
    }

    // Free exponent copy
    delete_list(&headExpCopy,&tailExpCopy);
}