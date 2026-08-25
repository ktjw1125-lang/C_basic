/*

260825 화

Day 16. 단일 연결 리스트 역순 정렬
입력: 1 -> 2 -> 3 -> NULL
출력: 3 -> 2 -> 1 -> NULL
제약조건: 메모리 재할당 없이 포인터 방향만 조작하여 구현.
실행결과: List Reversed.

*/

// #include <stdio.h>
// #include <stdint.h>

// typedef struct _node {
//     uint8_t value;
//     struct _node* next;
// } node;

// int main(void)
// {
//     node n1 = {1, NULL};
//     node n2 = {2, NULL};
//     node n3 = {3, NULL};

//     // 1 -> 2 -> 3
//     n1.next = &n2;
//     n2.next = &n3;

//     node* head = &n1;

//     printf("input: ");
//     printf("%d -> %d -> %d -> NULL\n",
//         head->value,
//         head->next->value,
//         head->next->next->value);

//     // Reverse
//     n3.next = &n2;
//     n2.next = &n1;
//     n1.next = NULL;

//     head = &n3;

//     printf("output: ");
//     printf("%d -> %d -> %d -> NULL\n",
//            head->value,
//            head->next->value,
//            head->next->next->value);

//     printf("List Reversed\n");

//     return 0;
// }



#include <stdio.h>
#include <stdint.h>

typedef struct _node {
    uint8_t value;
    struct _node* next;
} node;

int main(void)
{
    node n1 = {1, NULL};
    node n2 = {2, NULL};
    node n3 = {3, NULL};

    n1.next = &n2;
    n2.next = &n3;

    node* head = &n1;

    printf("input: ");
    printf("%d -> %d -> %d -> NULL\n",
        head->value,
        head->next->value,
        head->next->next->value);

    // Reverse
    node* prev = NULL;
    node* current = head;
    node* next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev;

    printf("output: ");
    printf("%d -> %d -> %d -> NULL\n",
           head->value,
           head->next->value,
           head->next->next->value);

    printf("List Reversed.\n");

    return 0;
}
