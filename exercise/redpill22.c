/*
[알고리즘 및 시스템 모사 (Algorithms & System)]

▶ Day 22. 소프트웨어 타이머 (Linked List 기반)
▶ Day 23. 문자열 토크나이저 (strtok 재구현)
*/

// 260823 일

/*
- **Day 22. 소프트웨어 타이머 (Linked List 기반)**
    - **입력:** `SetTimer(ID, ms)`, `Tick()` 주기적 호출
    - **출력:** 시간 만료 시 콜백 함수 실행
    - **제약조건:** 단일 연결 리스트로 남은 시간 순으로 정렬하여 관리(Delta Time 방식).
    - 참고1
        
        **"수많은 타이머를 어떻게 효율적으로 관리할 것인가?"**에 대한 임베디드 시스템의 표준 해법입니다.
        모든 타이머의 남은 시간을 매번 깎는 방식(O(N))은 타이머가 많아지면 시스템을 느리게 합니다.
        대신 **Delta Time(상대 시간)** 방식을 사용하면, 
        타이머 틱(Tick)마다 **맨 앞의 노드 하나만 깎으면(O(1))** 되므로 성능이 획기적으로 개선됩니다.
        
        ---
        
        ### 1. 핵심 원리: Delta Time (상대 시간)
        
        타이머를 **"만료될 절대 시간"**이 아니라, **"앞의 타이머가 터지고 나서 기다려야 할 시간"**으로 저장합니다.
        
        - **요청:** A(10ms), B(15ms), C(15ms)
        - **저장(Linked List):** `Head -> [A: 10] -> [B: 5] -> [C: 0] -> NULL`
            - A는 10초 뒤 만료.
            - B는 A가 만료된 후 5초 뒤(총 15초) 만료.
            - C는 B가 만료된 후 0초 뒤(즉시, 총 15초) 만료.
    - 참고2
        
        1. 초기 상태 (Initial State)
        
        Head -> id: T1 (dt = 10ms) -> id: T2 (dt = 5ms) -> id: T3 (dt = 15ms) -> NULL
        
        2. 시간 경과 후 상태 (After 5ms)
        
        Head -> id: T1 (dt = 5ms) -> id: T2 (dt = 5ms) -> id: T3 (dt = 15ms) -> NULL
        
        3. 타이머 만료 및 제거 (Timer Expiration and Removal)
        
        Head -> id: T2 (dt = 5ms) -> id: T3 (dt = 15ms) -> NULL
        
    - **실행결과:**
        
        ```c
        === Day 22: Software Timer (Delta List) ===
        
        Timer 1 set (10 ms) [Inserted at HEAD]
        [Timer List] (ID:1, dt:10, total:10) -> NULL
        Timer 2 set (5 ms) [Inserted at HEAD]
        [Timer List] (ID:2, dt:5, total:5) -> (ID:1, dt:5, total:10) -> NULL
        Timer 3 set (15 ms) [Inserted in List]
        [Timer List] (ID:2, dt:5, total:5) -> (ID:1, dt:5, total:10) -> (ID:3, dt:5, total:15) -> NULL
        
        >> Start Ticking...
        Tick 1: Rem Head dt: 4
        ... (생략) ...
        Tick 4: Rem Head dt: 1
        Tick 5: >> [Event] Timer 2 expired! Action executed.
        Rem Head dt: 5
        Tick 6: Rem Head dt: 4
        ... (생략) ...
        Tick 9: Rem Head dt: 1
        Tick 10: >> [Event] Timer 1 expired! Action executed.
        Rem Head dt: 5
        Tick 11: Rem Head dt: 4
        ... (생략) ...
        Tick 14: Rem Head dt: 1
        Tick 15: >> [Event] Timer 3 expired! Action executed.
        All timers cleared.
        ```
        
    
    Day22
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct TimerNode {
    int id;
    int dt;             // 앞 타이머와의 상대 시간
    int total;          // 디버깅용: 원래 설정한 시간
    struct TimerNode *next;
} TimerNode;

typedef struct {
    TimerNode *head;
} TimerManager;


// 타이머 초기화
void Timer_Init(TimerManager *tm)
{
    tm->head = NULL;
}


// 리스트 출력
void Timer_Print(TimerManager *tm)
{
    TimerNode *cur = tm->head;

    printf("[Timer List] ");

    while (cur != NULL) {
        printf("(ID:%d, dt:%d, total:%d)",
               cur->id,
               cur->dt,
               cur->total);

        if (cur->next != NULL)
            printf(" -> ");

        cur = cur->next;
    }

    printf(" -> NULL\n");
}


// 타이머 등록
void SetTimer(TimerManager *tm, int id, int ms)
{
    TimerNode *new_node =
        (TimerNode *)malloc(sizeof(TimerNode));

    new_node->id = id;
    new_node->total = ms;
    new_node->dt = ms;
    new_node->next = NULL;


    // 1. 리스트가 비어있는 경우
    if (tm->head == NULL) {
        tm->head = new_node;

        printf("Timer %d set (%d ms) [Inserted at HEAD]\n",
               id, ms);

        Timer_Print(tm);
        return;
    }


    // 2. HEAD보다 먼저 실행되는 경우
    if (ms < tm->head->dt) {

        new_node->dt = ms;

        tm->head->dt -= ms;

        new_node->next = tm->head;
        tm->head = new_node;

        printf("Timer %d set (%d ms) [Inserted at HEAD]\n",
               id, ms);

        Timer_Print(tm);
        return;
    }


    // 3. 중간 또는 마지막에 삽입
    TimerNode *cur = tm->head;
    int remaining = ms;

    while (cur != NULL) {

        if (remaining <= cur->dt) {
            break;
        }

        remaining -= cur->dt;
        cur = cur->next;
    }


    // cur이 NULL이면 마지막에 삽입
    if (cur == NULL) {

        TimerNode *last = tm->head;

        while (last->next != NULL) {
            last = last->next;
        }

        new_node->dt = remaining;
        last->next = new_node;

    }
    else {
        // cur 앞에 삽입
        new_node->dt = remaining;

        // cur의 Delta 조정
        cur->dt -= remaining;

        // 이전 노드 찾기
        TimerNode *prev = tm->head;

        while (prev->next != cur) {
            prev = prev->next;
        }

        new_node->next = cur;
        prev->next = new_node;
    }


    printf("Timer %d set (%d ms) [Inserted in List]\n",
           id, ms);

    Timer_Print(tm);
}


// 1ms 경과
void Tick(TimerManager *tm)
{
    // 타이머가 하나도 없음
    if (tm->head == NULL)
        return;

    // HEAD의 남은 시간 감소
    tm->head->dt--;

    // 만료된 타이머 처리
    while (tm->head != NULL &&
           tm->head->dt <= 0) {

        TimerNode *expired = tm->head;

        printf(">> [Event] Timer %d expired! Action executed.\n",
               expired->id);

        tm->head = expired->next;

        free(expired);
    }

    // 현재 HEAD 상태 출력
    if (tm->head != NULL) {
        printf("Rem Head dt: %d\n",
               tm->head->dt);
    }
}


// 모든 타이머 제거
void Timer_Clear(TimerManager *tm)
{
    TimerNode *cur = tm->head;

    while (cur != NULL) {
        TimerNode *next = cur->next;
        free(cur);
        cur = next;
    }

    tm->head = NULL;
}


// 테스트
int main()
{
    TimerManager tm;

    Timer_Init(&tm);

    printf("=== Day 22: Software Timer (Delta List) ===\n\n");


    // Timer 1: 10ms
    SetTimer(&tm, 1, 10);


    // Timer 2: 5ms
    SetTimer(&tm, 2, 5);


    // Timer 3: 15ms
    SetTimer(&tm, 3, 15);


    printf("\n>> Start Ticking...\n");

    for (int tick = 1; tick <= 15; tick++) {

        printf("Tick %d: ", tick);

        Tick(&tm);
    }


    Timer_Clear(&tm);

    printf("All timers cleared.\n");

    return 0;
}