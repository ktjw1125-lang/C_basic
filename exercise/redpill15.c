/*
[임베디드 필수 자료구조 (Data Structures)]

▶ Day 15. 원형 버퍼 (Ring Buffer) 구현
*/

// 260822 토

/*
- **Day 15. 원형 버퍼 (Ring Buffer) 구현**
    - **입력:** 데이터 Push/Pop 요청
    - **출력:** 버퍼 상태 (Full/Empty), 꺼낸 데이터
    - **제약조건:** 배열로 구현, Head/Tail 인덱스 관리, 오버플로우 방지 로직.
    - **실행결과:**
    
    ```c
    -- Phase 1: Filling Buffer ---
    Put: 1 (Head: 1, Tail: 0)
    Put: 2 (Head: 2, Tail: 0)
    Put: 3 (Head: 3, Tail: 0)
    Put: 4 (Head: 4, Tail: 0)
    Put: 5 (Head: 5, Tail: 0)
    Put: 6 (Head: 6, Tail: 0)
    Put: 7 (Head: 7, Tail: 0)
    Fail to Put: 8 (Buffer Full!)
    
    --- Phase 2: Reading Buffer ---
    Get: 1 (Head: 7, Tail: 1)
    Get: 2 (Head: 7, Tail: 2)
    Get: 3 (Head: 7, Tail: 3)
    
    --- Phase 3: Writing again (Wrap around) ---
    Put: 99 (Head: 0, Tail: 3)
    
    ```
    
    - 참고
        
        ```c
        // ---- 테스트 코드 ----
        int main() {
            RingBuffer uart_rx_buf;
            uint8_t temp;
        
            rb_init(&uart_rx_buf);
        
            printf("--- Phase 1: Filling Buffer ---\n");
            // 버퍼 사이즈가 8이므로, 한 칸 비우면 최대 7개 저장 가능
            for (int i = 1; i <= 8; i++) {
                if (rb_put(&uart_rx_buf, i)) {
                    printf("Put: %d (Head: %d, Tail: %d)\n", i, uart_rx_buf.head, uart_rx_buf.tail);
                } else {
                    printf("Fail to Put: %d (Buffer Full!)\n", i);
                }
            }
        
            printf("\n--- Phase 2: Reading Buffer ---\n");
            // 3개만 읽어봄
            for (int i = 0; i < 3; i++) {
                if (rb_get(&uart_rx_buf, &temp)) {
                    printf("Get: %d (Head: %d, Tail: %d)\n", temp, uart_rx_buf.head, uart_rx_buf.tail);
                }
            }
        
            printf("\n--- Phase 3: Writing again (Wrap around) ---\n");
            // 읽어서 공간이 생겼으므로 다시 쓰기 가능 (인덱스가 0으로 돌아가는지 확인)
            if (rb_put(&uart_rx_buf, 99)) {
                 printf("Put: 99 (Head: %d, Tail: %d)\n", uart_rx_buf.head, uart_rx_buf.tail);
            }
        
            return 0;
        }
        ```
        
    
    Day15
*/

// 7칸짜리 원형 버퍼(Ring Buffer / Circular Buffer)
// Head → 데이터를 넣는 위치
// Tail → 데이터를 빼는 위치
// 처음에는: Head = 0, Tail = 0
// put하면 데이터를 넣고 head가 다음칸으로 이동
// get하면 데이터를 빼고 tail이 다음칸으로 이동
// 이 버퍼는 FIFO(First In, First Out) 방식이라서 먼저 넣은 데이터부터 먼저 빠져.
// Get()을 하면 넣은 순서대로 나온다

// 그래서 일반 큐처럼 데이터를 앞으로 밀어낼 필요 없이, 
// Head와 Tail만 빙글빙글 돌면서 데이터를 넣고 뺄 수 있다는 게 링버퍼의 핵심

// 8칸짜리 배열에서 1칸을 비워두고 7개만 저장하는 구현
// Ring Buffer가 Full인지 Empty인지 구분하기 위해 일부러 마지막 한 칸을 비워두는 것

#include <stdio.h>
#include <stdint.h>

#define BUFFER_SIZE 8

typedef struct {
    uint8_t buffer[BUFFER_SIZE];
    int head;
    int tail;
} RingBuffer;


// Ring Buffer 초기화
void rb_init(RingBuffer *rb)
{
    rb->head = 0;
    rb->tail = 0;
}


// 데이터 넣기
// 성공: 1
// 실패(버퍼 Full): 0
int rb_put(RingBuffer *rb, uint8_t data)
{
    // 다음 Head 위치 계산
    int next_head = (rb->head + 1) % BUFFER_SIZE;

    // 다음 Head가 Tail과 같다면 버퍼가 가득 찬 상태
    if (next_head == rb->tail) {
        return 0;
    }

    // 현재 Head 위치에 데이터 저장
    rb->buffer[rb->head] = data;

    // Head 이동
    rb->head = next_head;

    return 1;
}


// 데이터 꺼내기
// 성공: 1
// 실패(버퍼 Empty): 0
int rb_get(RingBuffer *rb, uint8_t *data)
{
    // Head와 Tail이 같으면 버퍼가 비어있음
    if (rb->head == rb->tail) {
        return 0;
    }

    // Tail 위치의 데이터 꺼내기
    *data = rb->buffer[rb->tail];

    // Tail 이동
    rb->tail = (rb->tail + 1) % BUFFER_SIZE;

    return 1;
}


// ---- 테스트 코드 ----
int main()
{
    RingBuffer uart_rx_buf;
    uint8_t temp;

    rb_init(&uart_rx_buf);

    printf("--- Phase 1: Filling Buffer ---\n");

    // 버퍼 사이즈가 8이므로
    // 한 칸을 비워두어 최대 7개 저장 가능
    for (int i = 1; i <= 8; i++) {
        if (rb_put(&uart_rx_buf, i)) {
            printf("Put: %d (Head: %d, Tail: %d)\n",
                   i,
                   uart_rx_buf.head,
                   uart_rx_buf.tail);
        } else {
            printf("Fail to Put: %d (Buffer Full!)\n", i);
        }
    }


    printf("\n--- Phase 2: Reading Buffer ---\n");

    // 3개만 읽어봄
    for (int i = 0; i < 3; i++) {
        if (rb_get(&uart_rx_buf, &temp)) {
            printf("Get: %d (Head: %d, Tail: %d)\n",
                   temp,
                   uart_rx_buf.head,
                   uart_rx_buf.tail);
        }
    }


    printf("\n--- Phase 3: Writing again (Wrap around) ---\n");

    // 읽어서 공간이 생겼으므로 다시 쓰기 가능
    // Head가 0으로 돌아가는지 확인
    if (rb_put(&uart_rx_buf, 99)) {
        printf("Put: 99 (Head: %d, Tail: %d)\n",
               uart_rx_buf.head,
               uart_rx_buf.tail);
    }

    return 0;
}