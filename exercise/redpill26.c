/*

- **Day 26. 생산자-소비자 (Producer-Consumer) 시뮬레이션**
    - **입력:** 랜덤한 생산 및 소비 속도
    - **출력:** 버퍼 상태 및 데이터 처리 로그
    - **제약조건:** 뮤텍스/세마포어 개념을 `volatile` 플래그로 단순화하여 모사.
    - **실행결과:**
    
    ```bash
    === Day 26: Producer-Consumer Simulation ===
    Buffer Size: 5
    
    [PROD] Produced Item 1 (Head: 1, Count: 1)
    [PROD] Produced Item 2 (Head: 2, Count: 2)
    [CONS] Consumed Item 1 (Tail: 1, Count: 1)
    [PROD] Produced Item 3 (Head: 3, Count: 2)
    [PROD] Produced Item 4 (Head: 4, Count: 3)
    [PROD] Produced Item 5 (Head: 0, Count: 4)
    [PROD] Produced Item 6 (Head: 1, Count: 5)
      >> [Buffer Full!] Producer waits... (Count: 5)  <-- 꽉 참!
      >> [Buffer Full!] Producer waits... (Count: 5)
    [CONS] Consumed Item 2 (Tail: 2, Count: 4)        <-- 소비자가 공간 확보
    [PROD] Produced Item 7 (Head: 2, Count: 5)        <-- 다시 생산 가능
    [CONS] Consumed Item 3 (Tail: 3, Count: 4)
    ...
    ```
    
    Day26

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 5

typedef struct
{
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;

    volatile int lock;
} item;

void lock(item *buf)
{
    while (buf->lock)
    {
        /* 기다림 */
    }

    buf->lock = 1;
}

void unlock(item *buf)
{
    buf->lock = 0;
}

void prod(item *buf, int data)
{
    lock(buf);

    if (buf->count == BUFFER_SIZE)
    {
        printf("  >> [Buffer Full!] Producer waits... (Count: %d)\n",
               buf->count);

        unlock(buf);
        return;
    }

    buf->buffer[buf->head] = data;

    buf->head = (buf->head + 1) % BUFFER_SIZE;
    buf->count++;

    printf("[PROD] Produced Item %d (Head: %d, Count: %d)\n",
           data, buf->head, buf->count);

    unlock(buf);
}

void cons(item *buf)
{
    lock(buf);

    if (buf->count == 0)
    {
        printf("  >> [Buffer Empty!] Consumer waits... (Count: %d)\n",
               buf->count);

        unlock(buf);
        return;
    }

    int data = buf->buffer[buf->tail];

    buf->tail = (buf->tail + 1) % BUFFER_SIZE;
    buf->count--;

    printf("[CONS] Consumed Item %d (Tail: %d, Count: %d)\n",
           data, buf->tail, buf->count);

    unlock(buf);
}

int main(void)
{
    item buf = {0};

    printf("=== Day 26: Producer-Consumer Simulation ===\n");
    printf("Buffer Size: %d\n\n", BUFFER_SIZE);

    prod(&buf, 1);
    prod(&buf, 2);

    cons(&buf);

    prod(&buf, 3);
    prod(&buf, 4);
    prod(&buf, 5);
    prod(&buf, 6);

    /* 버퍼가 가득 참 */
    prod(&buf, 7);

    /* 소비자가 공간 확보 */
    cons(&buf);

    /* 다시 생산 가능 */
    prod(&buf, 7);

    cons(&buf);
    cons(&buf);

    return 0;
}
