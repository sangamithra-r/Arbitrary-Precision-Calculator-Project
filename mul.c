#include "apc.h"

/*
*
*
* Function Name: multiplication()
*
* Purpose: Performs multiplication of two arbitrary precision integers using the long multiplication technique.
*
*
* Algorithm:
*    Traverse the second operand from the least significant digit.
*    Multiply the current digit with every digit of the first operand.
*    Generate a partial product.
*    Add positional zeros based on the digit position.
*    Store the first partial product as the initial result.
*    Add subsequent partial products to the accumulated result.
*    Continue until all digits of the multiplier are processed.
*    Store the final product in the result list.
*
* Parameters:
*    tail1 : Tail pointer of first operand.
*    tail2 : Tail pointer of second operand.
*    headR : Address of result head.
*    tailR : Address of result tail.
*
* Return Value: No direct return value (void).Final product is stored in the result list.
*
*/

/* Function to perform multiplication using long multiplication method */
void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    // Stores partial product of current multiplication step
    node *headR2 = NULL, *tailR2 = NULL;

    // Stores result after adding partial products
    node *headAR = NULL, *tailAR = NULL;
    
    // Tracks number of trailing zeros required
    int count = 0;

    // Variables used during multiplication
    int carry = 0, result = 0, mul = 0,num;

    // Traverses first operand
    node *temp1 = NULL;

    // Process each digit of second operand from LSD to MSD
    while(tail2){

        // Current multiplier digit
        num = tail2->data;

        // Start multiplication from LSD of operand1
        temp1 = tail1;

        // Reset carry for every partial product
        carry = 0;

        // Add positional zeros to partial product
        for(int i = 0;i<count;i++){
            insert_last(&headR2, &tailR2, 0);
        }
        
        // Multiply current digit with all digits of operand1
        while(temp1){

            // Calculate product including carry
            mul = num * (temp1->data) + carry;

            // Extract current result digit
            result = mul % 10;

            // Calculate carry for next multiplication
            carry = mul / 10;

            // First partial product directly becomes result
            if(count == 0){
                insert_first(headR, tailR, result);
            }
            else{
                insert_first(&headR2, &tailR2, result);
            }

            // Move towards MSD of operand1
            temp1 = temp1->prev;
        }

        // Insert remaining carry digits
        while(carry){
            result = carry % 10;
            carry = carry / 10;
            if(count == 0){
                insert_first(headR, tailR, result);
            }
            else{
                insert_first(&headR2, &tailR2, result);
            }
        }

        // Add newly generated partial product with accumulated result
        if(count != 0){
            addition(*tailR, tailR2, &headAR, &tailAR);

            // Free old result list
            delete_list(headR, tailR);

            // Free temporary partial product list
            delete_list(&headR2, &tailR2);
    
            // Update result list
            *headR = headAR;
            *tailR = tailAR;

            // Reset temporary pointers
            headAR = NULL;
            tailAR = NULL;
        }

        // Increase positional shift count
        count++;

        // Move to next digit of operand2
        tail2 = tail2->prev;
    }

}