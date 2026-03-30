
#include <stdio.h>
#include <stdlib.h>


//list creation
typedef struct Node {
    int digit;
    struct Node* prev;
    struct Node* next;
} Node; 

//for insert functions
void insert_last(Node **head, Node **tail, int digit);
void insert_first(Node **head, Node **tail, int digit);

//sign handling
char get_sign_and_build(const char *str, Node **head, Node **tail);

//print
void print_list(Node *head);
void print_result(char sign, Node *head);

//compare and copy functions
int is_zero(Node *head);
int compare(Node *h1, Node *h2);
void copy_list(Node *src_h, Node **dst_h, Node **dst_t);
void int_to_list(int num, Node **head, Node **tail);

//arithmetic operations
void addition(
    Node *head1, Node *tail1,
    Node *head2, Node *tail2,
    Node **res_h, Node **res_t
);

void subtraction(
    Node *head1, Node *tail1,
    Node *head2, Node *tail2,
    Node **res_h, Node **res_t
);


void multiply(
    Node *head1, Node *tail1,
    Node *head2, Node *tail2,
    Node **res_h, Node **res_t
);

int division(
    Node *head1, Node *tail1,
    Node *head2, Node *tail2,
    Node **res_h, Node **res_t
);

void calculate_with_sign(
    char sign1, Node *h1, Node *t1,
    char sign2, Node *h2, Node *t2,
    char op,
    Node **res_h, Node **res_t,
    char *res_sign
);


void free_list(Node **head, Node **tail);
