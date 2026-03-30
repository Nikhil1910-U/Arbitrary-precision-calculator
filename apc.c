#include <stdio.h>
#include <stdlib.h>

#include "apc.h"


  //for addition
void addition(Node* head1, Node* tail1, Node* head2, Node* tail2, Node **res_h, Node **res_t) {
    Node *t1 = tail1;
    Node *t2 = tail2;
    int carry = 0;

    while (t1 != NULL || t2 != NULL) {
        int d1 = (t1 != NULL) ? t1->digit : 0;
        int d2 = (t2 != NULL) ? t2->digit : 0;

        int sum = d1 + d2 + carry;
        carry = sum / 10;
        int digit = sum % 10;

        insert_first(res_h, res_t, digit);

        if (t1) t1 = t1->prev;
        if (t2) t2 = t2->prev;
    }

    // If carry remains after finishing all digits
    if (carry > 0) {
        insert_first(res_h, res_t, carry);
    }
}


//for subtraction
void subtraction(Node* head1, Node* tail1, Node* head2, Node* tail2, Node **res_h, Node **res_t) {
    //determine which number is bigger
    int len1 = 0, len2 = 0;
    Node* temp;

    for (temp = head1; temp != NULL; temp = temp->next) len1++;
    for (temp = head2; temp != NULL; temp = temp->next) len2++;

    int negative = 0; // flag if result is negative

    Node *num1_h = head1, *num1_t = tail1;
    Node *num2_h = head2, *num2_t = tail2;

    if (len1 < len2) {  // num2 > num1
        negative = 1;
        num1_h = head2; num1_t = tail2;
        num2_h = head1; num2_t = tail1;
    } else if (len1 == len2) {          // same length, compare digits
        Node *t1 = head1, *t2 = head2;
        while (t1 != NULL) {
            if (t1->digit < t2->digit) {
                negative = 1;
                num1_h = head2; num1_t = tail2;
                num2_h = head1; num2_t = tail1;
                break;
            } else if (t1->digit > t2->digit) {
                break;           // num1 bigger, keep as is
            }
            t1 = t1->next;
            t2 = t2->next;
        }
    }

    //subtract digits from tail
    Node* t1 = num1_t;
    Node* t2 = num2_t;
    int borrow = 0;

    while (t1 != NULL || t2 != NULL) {
        int d1 = (t1 != NULL) ? t1->digit : 0;
        int d2 = (t2 != NULL) ? t2->digit : 0;

        if (borrow) {
            d1 -= 1;
            borrow = 0;
        }

        if (d1 < d2) {
            d1 += 10;
            borrow = 1;
        }

        int diff = d1 - d2;
        insert_first(res_h, res_t, diff);

        if (t1) t1 = t1->prev;
        if (t2) t2 = t2->prev;
    }

    //Remove leading zeros
    while (*res_h != NULL && (*res_h)->digit == 0 && *res_h != *res_t) {
        Node* temp = *res_h;
        *res_h = (*res_h)->next;
        if (*res_h) (*res_h)->prev = NULL;
        free(temp);
    }

    // Print negative sign if needed
    if (negative) 
        printf("-");
}


//for multiplication  
void multiply(Node *head1, Node *tail1, Node *head2, Node *tail2, Node **res_h, Node **res_t)
{
    *res_h = NULL;
    *res_t = NULL;

    int zeros = 0;  

    // loop through num2 from least significant digit
    for (Node *p2 = tail2; p2 != NULL; p2 = p2->prev)
    {
        Node *partial_h = NULL, *partial_t = NULL;
        int carry = 0;

        // Multiply num1 with ONE digit of num2
        for (Node *p1 = tail1; p1 != NULL; p1 = p1->prev)
        {
            int mul = (p1->digit * p2->digit) + carry;

            int digit = mul % 10;
            carry = mul / 10;

            insert_first(&partial_h, &partial_t, digit);
        }

        // leftover carry
        if (carry)
            insert_first(&partial_h, &partial_t, carry);

        // Add zeros for place value 
        for (int i = 0; i < zeros; i++)
            insert_last(&partial_h, &partial_t, 0);

        zeros++;  // Next partial gets one more zero

        // First partial result, assign it to final result
        if (*res_h == NULL)
        {
            *res_h = partial_h;
            *res_t = partial_t;
        }
        else
        {
            // We already have a result, add this partial to result

            Node *temp_h = NULL, *temp_t = NULL;

            addition(*res_h, *res_t, partial_h, partial_t, &temp_h, &temp_t);

            // free old result
            free_list(res_h, res_t);

            // free partial
            free_list(&partial_h, &partial_t);

            // new result
            *res_h = temp_h;
            *res_t = temp_t;
        }
    }
}

//for division
int division(Node *head1, Node *tail1,
              Node *head2, Node *tail2,
              Node **res_h, Node **res_t)
{
    *res_h = NULL;
    *res_t = NULL;

    // divide by zero
    if (is_zero(head2))
    {
        printf("Error: Division by zero\n");
        return -1;
    }

    // 0 / anything = 0
    if (is_zero(head1))
    {
        insert_first(res_h, res_t, 0);
        return 0;
    }

    Node *temp_h = NULL, *temp_t = NULL;
    copy_list(head1, &temp_h, &temp_t);

    int count = 0;

    // Repeated subtraction
    while (compare(temp_h, head2) >= 0)
    {
        Node *new_h = NULL, *new_t = NULL;

        subtraction(temp_h, temp_t, head2, tail2, &new_h, &new_t);

        free_list(&temp_h, &temp_t);

        temp_h = new_h;
        temp_t = new_t;

        count++;
    }

    // Convert count to linked list
    int_to_list(count, res_h, res_t);

    free_list(&temp_h, &temp_t);
    return 0;
}



