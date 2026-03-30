
#include <stdio.h>
#include <stdlib.h>

#include "apc.h"


void calculate_with_sign(
        char sign1, Node *h1, Node *t1,
        char sign2, Node *h2, Node *t2,
        char op,
        Node **res_h, Node **res_t,
        char *res_sign)
{
    *res_h = NULL;
    *res_t = NULL;
    *res_sign = '+';

    // Multiplication
    if (op == '*')
    {
        *res_sign = (sign1 == sign2) ? '+' : '-';
        multiply(h1, t1, h2, t2, res_h, res_t);
        return;
    }

    //Division
    if (op == '/')
    {
        *res_sign = (sign1 == sign2) ? '+' : '-';
        if (division(h1, t1, h2, t2, res_h, res_t) < 0)
        {
            *res_h = NULL;
            *res_t = NULL;
            *res_sign = '+';
            return;
        }
        return;
        
    }

    // Addition
    if (op == '+')
    {
        if (sign1 == sign2)
        {
            // +A + +B  or  -A + -B
            addition(h1, t1, h2, t2, res_h, res_t);
            *res_sign = sign1;
        }
        else
        {
            // +A + -B  or  -A + +B
            if (compare(h1, h2) >= 0)
            {
                subtraction(h1, t1, h2, t2, res_h, res_t);
                *res_sign = sign1;
            }
            else
            {
                subtraction(h2, t2, h1, t1, res_h, res_t);
                *res_sign = sign2;
            }
        }
        return;
    }

    //Subtraction
    if (op == '-')
    {
        // A - B = A + (-B)
        sign2 = (sign2 == '+') ? '-' : '+';

        if (sign1 == sign2)
        {
            addition(h1, t1, h2, t2, res_h, res_t);
            *res_sign = sign1;
        }
        else
        {
            if (compare(h1, h2) >= 0)
            {
                subtraction(h1, t1, h2, t2, res_h, res_t);
                *res_sign = sign1;
            }
            else
            {
                subtraction(h2, t2, h1, t1, res_h, res_t);
                *res_sign = sign2;
            }
        }
    }
}

int main(int argc, char* argv[]) 
{

    if (argc != 4) {
        printf("Usage: %s <num1> <operator> <num2>\n", argv[0]);
        return 1;
    }

    Node *head1 = NULL, *tail1 = NULL;
    Node *head2 = NULL, *tail2 = NULL;
    Node *res_h = NULL, *res_t = NULL;



    char sign1, sign2, res_sign;
    char op = argv[2][0];

    //get sign
    sign1 = get_sign_and_build(argv[1], &head1, &tail1);
    sign2 = get_sign_and_build(argv[3], &head2, &tail2);

    //handles signs and operations
    calculate_with_sign(
        sign1, head1, tail1,
        sign2, head2, tail2,
        op,
        &res_h, &res_t,
        &res_sign
    );

    if (res_h == NULL)
    {
    // Do not print result, error already printed for division by zero
        return 1;
    }

    // Print result
    printf("Result = ");
    print_result(res_sign, res_h);

    return 0;
}

 
