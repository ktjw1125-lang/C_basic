#include <stdio.h>
// 4칙연산, scanf

int main(void)
{
    int a, b;
    char op;
    printf("calc : ");
    scanf("%d %c %d", &a, &op, &b);

    // if (op == '*')
    //     printf("%d %c %d = %d", a, op, b, a * b);
    // else if (op == '+')
    //     printf("%d %c %d = %d", a, op, b, a + b);
    // else if (op == '-')
    //     printf("%d %c %d = %d", a, op, b, a - b);
    // else if (op == '/')
    //     if (b == 0)
    //         printf("can't divided by zero");
    //     else
    //         printf("%d %c %d = %d", a, op, b, a / b);

    switch(op){   // integer, char 만 된다
        case '+':
            printf("%d %c %d = %d", a, op, b, a + b);
            break;
        case '-':
            printf("%d %c %d = %d", a, op, b, a - b);
            break;
        case '*':
            printf("%d %c %d = %d", a, op, b, a * b);
            break;
        case '/':
            if (b == 0)
                printf("can't divided by zero");
            else
                printf("%d %c %d = %.3f\r\n", a, op, b, (float)a / (float)b);
            break;
    }

    return 0;
}