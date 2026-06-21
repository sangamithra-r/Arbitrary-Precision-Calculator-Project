#include "apc.h"

// Function definitions

// Validate command line arguments and operator
int cla_validation(int argc, char *argv[]){

    // Check argument count
    if(argc != 4){
        fprintf(stderr,"ERROR: Invalid Arguments Count\n");
        fprintf(stderr,"USAGE: ./a.out operand1 operator operand2\n");
        return FAILURE;
    }

    // Store operands and operator
    char *opr1 = argv[1];
    char *opr2 = argv[3];
    char *oper = argv[2];

    // Validate operands
    if(is_numeric(opr1) == FAILURE || is_numeric(opr2) == FAILURE){
        fprintf(stderr,"ERROR: operand1 : %s operand2 : %s\nInvalid operand\n",opr1,opr2);
        fprintf(stderr,"USAGE: Enter only numeric value\n");
        return FAILURE;
    }

    // Validate operator
    if(strcmp(oper,"+") != 0 && strcmp(oper,"-") != 0 && strcmp(oper,"x") != 0 && strcmp(oper,"/") != 0 && strcmp(oper,"X") != 0 && strcmp(oper,"%") != 0 && strcmp(oper,"^") != 0){
        fprintf(stderr,"ERROR: %s : Invalid operator\n",oper);
        fprintf(stderr,"USAGE: Use only operators +,-,x,/ \n");
        return FAILURE;
    }
    return SUCCESS;
}

// Check whether operand contains only numeric characters
int is_numeric(char *operand){
    int i = 0;
    // Skip sign character
    if(operand[0] == '-' || operand[0] == '+'){
        i++;
    }

    // Reject empty operand
    if(operand[i] == '\0')
    {
        return FAILURE;
    }

    // Validate each character
    while(operand[i] != '\0'){
        if(!(isdigit(operand[i]))){
            return FAILURE;
        }
        i++;
    }
    return SUCCESS;
}

// Insert node at beginning of list
int insert_first(node **head, node **tail, int data){
    // Allocate memory for new node
    node *new = malloc(sizeof(node));
    if(new == NULL){
        fprintf(stderr,"Memory Allocation failed\n");
        return FAILURE;
    }
    new->data = data;
    new->prev = NULL;

    // First node insertion
    if(*head == NULL){
        new->next = NULL;
        *head = new;
        *tail = new;
        return SUCCESS;
    }

    // Insert before current head
    (*head)->prev = new;
    new->next = (*head);
    *head = new;

    return SUCCESS;
}

// Insert node at end of list
int insert_last(node **head, node **tail, int data){
    // Allocate memory for new node
    node *new = malloc(sizeof(node));
    if(new == NULL){
        fprintf(stderr,"ERROR: Memory Allocation failed\n");
        return FAILURE;
    }
    new->data = data;
    new->next = NULL;

    // First node insertion
    if(*head == NULL){
        new->prev = NULL;
        *head = new;
        *tail = new;
        return SUCCESS;
    }

    // Insert after current tail
    new->prev = (*tail);
    (*tail)->next = new;
    *tail = new;
    return SUCCESS;
}

// Delete entire list and free memory
int delete_list(node **head, node **tail){
    if(*head == NULL){
        fprintf(stderr,"ERROR: List empty\n");
        return FAILURE;
    }
    node *temp;
    while(*head != NULL){
        temp = *head;
        *head = temp->next;
        free(temp);
    }
    *tail = NULL;
    return SUCCESS;
}

// Display list contents
void print_list(node *head){
    if(head == NULL){
        fprintf(stderr,"List is empty\n");
    }
    else{
        while(head){
            printf("%d",head->data);
            head = head->next;
        }
    }
}

// Convert operand string into doubly linked list
void create_list(char *opr, node **head, node **tail){
    int i = 0;

    // Skip sign character
    if(opr[0] == '-' || opr[0] == '+'){
        i++;
    }

    // Insert each digit into list
    while(opr[i]){
        if(insert_last(head,tail,opr[i]-'0') != SUCCESS){
            fprintf(stderr,"ERROR: List not created\nOperation failed\n");
            return;
        }
        i++;
    }
}

// Determine sign of operand
int checksign(char *operand){
    if(operand[0] == '-'){
        return -1;
    }
    return 1;
}

// Compare two APC numbers
int compare_list(node *head1, node *head2){
    int len1 = list_len(head1);
    int len2 = list_len(head2);

    // Compare lengths
    if(len1 > len2){
        return OPERAND1;
    }
    else if(len1 < len2){
        return OPERAND2;
    }
    // Compare digit by digit
    while(head1 && head2){
        if(head1->data > head2->data){
            return OPERAND1;
        }
        else if(head1->data < head2->data){
            return OPERAND2;
        }
        head1 = head1->next;
        head2 = head2->next;
    }
    return SAME;
}

// Find length of linked list
int list_len(node *head){
    int len = 0;
    while(head != NULL){
        len++;
        head = (head)->next;
    }
    return len;
}

// Remove leading zeros from list
void remove_pre_zeros(node **head){
    if(*head == NULL){
        return;
    }
    node *temp = *head;
    while(temp != NULL && temp->next != NULL){
        if(temp->data != 0){
            break;
        }
        node *del = temp;
        temp = temp->next;
        temp->prev = NULL;
        free(del);
    }
    *head = temp;
}

// Check whether number is zero
int is_zero(node *head){
    if(head && head->data == 0 && head->next == NULL){
        return SUCCESS;
    }
    return FAILURE;
}

// Decrement APC number by one
void decrement(node **head, node **tail)
{
    node *temp = *tail;

    while(temp)
    {
        // Borrow not required
        if(temp->data > 0)
        {
            temp->data--;
            break;
        }

        // Borrow from previous digit
        temp->data = 9;
        temp = temp->prev;
    }
    // Remove leading zeros after decrement
    remove_pre_zeros(head);
}

// Check whether APC number is odd
int is_odd(node *tail)
{
    return (tail->data % 2);
}

// Create a duplicate copy of a list
int copy_list(node *head, node *tail,node **headCopy,node **tailCopy)
{
    while(head)
    {
        if(insert_last(headCopy,tailCopy,head->data) != SUCCESS)
        {
            return FAILURE;
        }
        head = head->next;
    }

    return SUCCESS;
}