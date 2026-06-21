#include "apc.h"

/*
*
* Function Name: division()
* Purpose: Performs arbitrary precision integer division using the long division method and repeated subtraction.
*
* Algorithm:
*   Create a temporary dividend using the leading digits of the original dividend.
*   Compare the temporary dividend with the divisor.
*   Repeatedly subtract the divisor while the temporary dividend is greater than or equal to the divisor.
*   Count the number of successful subtractions to obtain a quotient digit.
*   Append the quotient digit to the quotient list.
*   Bring down the next digit from the dividend.
*   Repeat until all digits are processed.
*   Store the final quotient and remainder.
*
* Parameters:
*   head1 : Head of dividend.
*   head2 : Head of divisor.
*   tail2 : Tail of divisor.
*   headQ : Address of quotient head.
*   tailQ : Address of quotient tail.
*   headRem : Address of remainder head.
*   tailRem : Address of remainder tail.
*
* Return Value: No direct return value (void). Quotient is stored in headQ and tailQ. Remainder is stored in headRem and tailRem.
*
*
*/
/* Function to perform division using long division and repeated subtraction */
void division(node *head1, node *head2, node *tail2,node **headQ, node **tailQ,node **headRem, node **tailRem)
{
    // Working dividend used during division
    node *headD = NULL;
    node *tailD = NULL;

    // Pointer to traverse the original dividend
    node *temp = head1;

    // Stores subtraction result
    node *headSR = NULL;
    node *tailSR = NULL;

    // Counts how many times divisor fits into current dividend
    int sub_count = 0;

    // Stores comparison result
    int cmp;

    // Insert first digit of dividend into working dividend
    insert_last(&headD, &tailD, temp->data);

    // If current dividend is smaller than divisor, bring down next digit
    if(compare_list(headD, head2) == OPERAND2){
        temp = temp->next;
        if(temp){
            insert_last(&headD, &tailD, temp->data);
        }
    }

    // Process each digit of the dividend
    while(temp){

        // Reset quotient digit count
        sub_count = 0;

        // Compare working dividend with divisor
        cmp = compare_list(headD, head2);

        // Repeatedly subtract divisor while dividend >= divisor
        while(cmp == OPERAND1 || cmp == SAME){

            // Initialize subtraction result list
            tailSR = NULL;
            headSR = NULL;

            // Perform subtraction
            subtraction(tailD, tail2, &headSR, &tailSR);

            // Delete previous working dividend
            delete_list(&headD, &tailD);

            // Update working dividend with subtraction result
            tailD = tailSR;
            headD = headSR;

            // Remove leading zeros from working dividend
            remove_pre_zeros(&headD);

            // Increment quotient digit
            sub_count++;

            // Compare again after subtraction
            cmp = compare_list(headD, head2);            
        }

        // Store quotient digit
        insert_last(headQ, tailQ, sub_count);

        // Move to next dividend digit
        temp = temp->next;

        // Bring down next digit
        if(temp){
            insert_last(&headD, &tailD, temp->data);

            // Remove leading zeros from working dividend
            remove_pre_zeros(&headD);

        }
    }

    // Remove leading zeros from quotient
    remove_pre_zeros(headQ);

    // Remove leading zeros from remainder
    remove_pre_zeros(&headD);

    // Return remainder list
    *headRem = headD;
    *tailRem = tailD;
}
