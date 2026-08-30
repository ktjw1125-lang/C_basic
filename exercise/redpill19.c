/*

- **Day 19. 스택 오버플로우 감지 (Canary)**
    - **입력:** 재귀 함수 깊게 호출
    - **출력:** 스택 한계 도달 시 경고 메시지
    - **제약조건:** 스택 영역 끝에 특정 패턴(Canary)을 심고 주기적으로 검사.
    - **실행결과:**
    
    ```c
    === Day 19: Stack Overflow Detection (Canary Simulation) ===
    Stack Base Address: 0x7ffc06e480d4
    Soft Limit: 4096 bytes
    
    Current Stack Usage: 33 bytes
    Current Stack Usage: 1041 bytes
    Current Stack Usage: 2049 bytes
    Current Stack Usage: 2097 bytes
    Current Stack Usage: 3105 bytes
    Current Stack Usage: 4113 bytes
    
    [!!! WARNING !!!] Stack Overflow Detected!
    Limit: 4096, Used: 4113
    
    >> System survived. Returned safely to main.
    ```
    
    Day19

*/

#include <stdio.h>
#include <stdint.h>

#define STACK_LIMIT 4096
#define CANARY_VALUE 0xDEADBEEF

typedef struct
{
    uint32_t canary;
} StackGuard;


/*
 * 재귀 깊이를 나타내기 위한 구조체
 *
 * 실제 스택을 일부 사용하는 것처럼
 * 큰 배열을 지역 변수로 만들어 줌
 */
void recursive_function(int depth, StackGuard *guard)
{
    char stack_buffer[1000];

    /* 컴파일러가 stack_buffer를 없애지 못하도록 사용 */
    stack_buffer[0] = (char)depth;

    /*
     * 대략적인 스택 사용량 계산
     *
     * 여기서는 실제 OS 스택 사용량을 측정하는 것이 아니라
     * depth를 기준으로 시뮬레이션
     */
    int stack_usage = 33 + depth * 1008;

    printf("Current Stack Usage: %d bytes\n", stack_usage);

    /*
     * Canary 검사
     */
    if (guard->canary != CANARY_VALUE)
    {
        printf("\n[!!! WARNING !!!] Stack Overflow Detected!\n");
        printf("Canary Corrupted!\n");
        return;
    }

    /*
     * Soft Limit 초과 검사
     */
    if (stack_usage > STACK_LIMIT)
    {
        printf("\n[!!! WARNING !!!] Stack Overflow Detected!\n");
        printf("Limit: %d, Used: %d\n",
               STACK_LIMIT,
               stack_usage);
        return;
    }

    /*
     * 재귀 호출
     */
    recursive_function(depth + 1, guard);

    /*
     * 복귀하면서 Canary 다시 검사
     */
    if (guard->canary != CANARY_VALUE)
    {
        printf("\n[!!! WARNING !!!] Stack Overflow Detected!\n");
        printf("Canary Corrupted!\n");
    }
}


int main(void)
{
    /*
     * Canary를 스택 영역 끝에 둔다고 가정
     */
    StackGuard guard;

    guard.canary = CANARY_VALUE;

    printf("=== Day 19: Stack Overflow Detection (Canary Simulation) ===\n");

    printf("Stack Base Address: %p\n",
           (void *)&guard);

    printf("Soft Limit: %d bytes\n\n",
           STACK_LIMIT);

    recursive_function(0, &guard);

    printf("\n>> System survived. Returned safely to main.\n");

    return 0;
}
