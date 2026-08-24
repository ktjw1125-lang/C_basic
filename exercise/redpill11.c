/*

- **Day 11. 함수 포인터 배열을 이용한 계산기**
    - **입력:** 연산자 ID (0:Add, 1:Sub, 2:Mul...), 두 정수
    - **출력:** 연산 결과
    - **제약조건:** `if`나 `switch` 문 사용 금지. enum사용
    - **실행결과:**
    
    ```bash
    === Day 11: Function Pointer Array Calculator ===
    
    Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): 0
    Input two integers: 1 2
    >> Result: 3
    
    Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): 1
    Input two integers: 2 1
    >> Result: 1
    
    Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): 2
    Input two integers: 2 1
    >> Result: 2
    
    Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): 3
    Input two integers: 1 2
    >> Result: 0
    
    Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): 4
    
    ```
    
    Day11

*/


#include <stdio.h>

typedef enum {
    ADD,
    SUB,
    MUL,
    DIV,
    EXIT
} Operator;

// int 2개를 받아서 int를 반환하는 함수의 포인터 타입을 Operation이라는 이름으로 만들겠다
typedef int (*Operation)(int, int);

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int mul(int a, int b)
{
    return a * b;
}

int divi(int a, int b)
{
    return a / b;
}

int main(void)
{
    const Operation operations[] = {
        add,
        sub,
        mul,
        divi
    };

    int choice;
    int a, b;

    printf("=== Day 11: Function Pointer Array Calculator ===\n");

    while (1)
    {
        printf("\nSelect (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): ");
        scanf("%d", &choice);

        if (choice == 4)
            break;

        printf("Input two integers: ");
        scanf("%d %d", &a, &b);

        printf(">> Result: %d\n", operations[choice](a, b));
    }

    return 0;
}