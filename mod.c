#include "apc.h"

/*
*
*
* Function Name: modulus()
* Purpose:Computes the remainder obtained after dividing one arbitrary precision integer by another.
*
* Algorithm:
*    Call the division function.
*    Obtain both quotient and remainder from division.
*    Ignore the quotient.
*    Return the remainder as the final result.
*    Free the memory allocated for the quotient list.
*
* Parameters:
*    head1 : Head of dividend.
*    head2 : Head of divisor.
*    tail2 : Tail of divisor.
*    headR : Address of remainder head.
*    tailR : Address of remainder tail.
*
* Return Value: No direct return value (void).Remainder is stored in headR and tailR.
*
*
*/

/* Function to perform modulus operation */
void modulus(node *head1, node *head2, node *tail2,node **headR, node **tailR)
{
    // Stores quotient generated during division
    node *headQ = NULL;
    node *tailQ = NULL;

    // Perform division and obtain remainder
    division(head1, head2, tail2,&headQ, &tailQ,headR, tailR);

    // Quotient is not required for modulus operation
    delete_list(&headQ, &tailQ);
}