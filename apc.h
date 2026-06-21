#ifndef APC_H
#define APC_H

/* Standard Header Files */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Return Status Macros */
#define SUCCESS		1
#define FAILURE		0

/* Comparison Result Macros */
#define SAME		0
#define OPERAND1	1
#define OPERAND2	2

/* Doubly Linked List Node */
typedef struct node
{
    struct node *prev; // Pointer to previous node
    int data; // Stores a single digit
    struct node *next; // Pointer to next node
}node;

/* Arithmetic Operations */
void addition(node *tail1, node *tail2, node **headR, node **tailR);
void subtraction(node *tail1, node *tail2, node **headR, node **tailR);
void multiplication(node *tail1, node *tail2, node **headR, node **tailR);
void division(node *head1, node *head2, node *tail2,node **headQ, node **tailQ,node **headRem, node **tailRem);
void modulus(node *head1, node *head2, node *tail2,node **headR, node **tailR);
void power(node *headBase, node *tailBase,node *headExp, node *tailExp,node **headR, node **tailR);

/* Power Helper Functions */
void decrement(node **head, node **tail);
int is_odd(node *tail);
int copy_list(node *head, node *tail,node **headCopy,node **tailCopy);

/* Validation Functions */
int cla_validation(int argc, char *argv[]);
int is_numeric(char *operand);
int checksign(char *operand);
int is_zero(node *head);

/* List Creation Functions */
void create_list(char *opr, node **head, node **tail);

/* List Manipulation Functions */
int insert_first(node **head, node **tail, int data);
int insert_last(node **head, node **tail, int data);
int delete_list(node **head, node **tail);
void print_list(node *head);

/* Utility Functions */
int compare_list(node *head1, node *head2);
int list_len(node *head);
void remove_pre_zeros(node **head);


#endif
