
#include <stdio.h>
#include <stdlib.h>

#include "apc.h"


void insert_last(Node** head, Node** tail, int digit) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->digit = digit;
    newNode->next = NULL;
    newNode->prev = *tail;

    if (*tail) (*tail)->next = newNode;
    else *head = newNode; // first node

    *tail = newNode;
}  


void insert_first(Node **head, Node **tail, int digit) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->digit = digit;
    newNode->prev = NULL;
    newNode->next = *head;

    if (*head)
        (*head)->prev = newNode;
    else
        *tail = newNode; // first node

    *head = newNode;
}  



//functions for division operation
int is_zero(Node *head)
{
    return (head != NULL && head->digit == 0 && head->next == NULL);
}

int compare(Node *h1, Node *h2)
{
    int len1 = 0, len2 = 0;
    Node *p;

    for (p = h1; p; p = p->next) len1++;
    for (p = h2; p; p = p->next) len2++;

    if (len1 > len2) return 1;
    if (len1 < len2) return -1;

    while (h1 && h2)
    {
        if (h1->digit > h2->digit) return 1;
        if (h1->digit < h2->digit) return -1;
        h1 = h1->next;
        h2 = h2->next;
    }
    return 0;
}

void copy_list(Node *src_h, Node **dst_h, Node **dst_t)
{
    while (src_h)
    {
        insert_last(dst_h, dst_t, src_h->digit);
        src_h = src_h->next;
    }
}
void int_to_list(int num, Node **head, Node **tail)
{
    if (num == 0)
    {
        insert_first(head, tail, 0);
        return;
    }

    while (num > 0)
    {
        insert_first(head, tail, num % 10);
        num /= 10;
    }
}

//for printing
void print_result(char sign, Node *head)
{
    if (is_zero(head))
        sign = '+';

    if (sign == '-')
        printf("-");

    print_list(head);
}

char get_sign_and_build(const char *str, Node **head, Node **tail)
{
    int i = 0;
    char sign = '+';

    if (str[0] == '-') {
        sign = '-';
        i = 1;
    }

    for (; str[i] != '\0'; i++) {
        insert_last(head, tail, str[i] - '0');
    }

    return sign;
}

void free_list(Node **head, Node **tail)
{
    Node *temp = *head;
    while (temp)
    {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;
    *tail = NULL;
}

void print_list(Node *head)
{
    if (!head)
    {
        printf("0\n");
        return;
    }

    while (head)
    {
        printf("%d", head->digit);
        head = head->next;
    }
    printf("\n");
}
