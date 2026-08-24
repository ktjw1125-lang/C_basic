// 260820 목 - 어려움..

/*

- **Day 13. 고정 크기 메모리 풀 (Memory Pool) 할당기**
    - **입력:** 할당 요청
    - **출력:** 할당된 메모리 블록 주소 (실패 시 NULL)
    - **제약조건:** 런타임에 `malloc` 사용 금지. 미리 잡아둔 큰 배열 안에서 청크를 쪼개 줄 것.
    - **실행결과:**
    
    ```c
    [Init] Memory Pool Initialized (10 blocks of 32 bytes)
    Allocated: 0x5a6dbc0c9040, 0x5a6dbc0c9060, 0x5a6dbc0c9080
    Used Blocks: 3
    Freeing 0x5a6dbc0c9060...
    Re-allocated: 0x5a6dbc0c9060 (Should be same as old p2)
    
    ```
    
    ```c
    // 설정: 블록 크기와 개수
    #define BLOCK_SIZE  32
    #define POOL_SIZE   10
    
    // 메모리 블록 구조체 (Free List 관리를 위한 연결 리스트 노드)
    // 할당되지 않았을 때는 다음 빈 블록을 가리키는 포인터로 사용됨
    typedef struct Block {
        struct Block* next;
    } Block;
    
    // 메모리 풀 컨텍스트
    typedef struct {
        // 실제 메모리 공간 (바이트 배열)
        // 정렬(Alignment)을 위해 uint64_t나 align 속성을 사용할 수 있음
        uint8_t memory_area[POOL_SIZE * BLOCK_SIZE]; 
        
        // 현재 사용 가능한 첫 번째 블록을 가리키는 포인터
        Block* free_list;
        
        // 디버깅용: 현재 사용 중인 블록 수
        int used_count;
    } MemoryPool;
    
    // 1. 초기화: 모든 메모리를 쪼개서 연결 리스트로 연결
    void pool_init(MemoryPool* pool) {}
    
    // 2. 할당: Free List의 헤드(Head)를 떼어줌 (Pop)
    void* pool_alloc(MemoryPool* pool) {}
    
    // 3. 해제: 반환된 블록을 Free List의 헤드에 다시 붙임 (Push)
    void pool_free(MemoryPool* pool, void* ptr) {}
    
    // 테스트 코드
    int main() {
        pool_init(&my_pool);
    
        // 3개 할당
        void* p1 = pool_alloc(&my_pool);
        void* p2 = pool_alloc(&my_pool);
        void* p3 = pool_alloc(&my_pool);
    
        printf("Allocated: %p, %p, %p\n", p1, p2, p3);
        printf("Used Blocks: %d\n", my_pool.used_count);
    
        // 1개 해제 (p2)
        printf("Freeing %p...\n", p2);
        pool_free(&my_pool, p2); // 이제 p2가 free_list의 head가 됨
        
        // 다시 1개 할당 (p2와 같은 주소가 나와야 함 - LIFO 특성)
        void* p4 = pool_alloc(&my_pool);
        printf("Re-allocated: %p (Should be same as old p2)\n", p4);
    
        return 0;
    }
    ```
    
    Day13

*/

/*

// 스터디

`malloc()` 대신 미리 확보해 둔 메모리 창고에서 일정한 크기의 조각을 꺼내주는 프로그램을 만들어라”**는 뜻이야.

void *p = malloc(64);
이렇게 OS/런타임에서 메모리를 받아오지만, 이 과제에서는 금지.

대신:

void *p = pool + 0 * BLOCK_SIZE;

처럼 `pool` 안에서 직접 잘라서 줘.

**사용 가능한 블록을 찾아서 주소를 반환한다**

예를 들어 현재 상태가

```
블록 0: 사용 중
블록 1: 빈칸  ← 이걸 반환
블록 2: 사용 중
블록 3: 빈칸
```

이라면

```
pool + 1 * BLOCK_SIZE
```

의 주소를 반환하는 거야.

그리고 나중에 `free()`에 해당하는 **pool_free()**를 만들어서 다시 빈칸으로 표시해주면 됨.

*/

#include <stdio.h>
#include <stdint.h>

// 설정: 블록 크기와 개수
#define BLOCK_SIZE  32
#define POOL_SIZE   10

// 메모리 블록 구조체 (Free List 관리를 위한 연결 리스트 노드)
// 할당되지 않았을 때는 다음 빈 블록을 가리키는 포인터로 사용됨
typedef struct Block {
    struct Block* next;
} Block;

// 메모리 풀 컨텍스트
typedef struct {
    // 실제 메모리 공간 (바이트 배열)
    // 정렬(Alignment)을 위해 uint64_t나 align 속성을 사용할 수 있음
    uint8_t memory_area[POOL_SIZE * BLOCK_SIZE];
    
    // 현재 사용 가능한 첫 번째 블록을 가리키는 포인터
    Block* free_list;
    
    // 디버깅용: 현재 사용 중인 블록 수
    int used_count;
} MemoryPool;


// 1. 초기화: 모든 메모리를 쪼개서 연결 리스트로 연결
void pool_init(MemoryPool* pool) {
    pool->free_list = NULL;
    pool->used_count = 0;

    for (int i = 0; i < POOL_SIZE; i++) {
        Block* block = (Block*)&pool->memory_area[i * BLOCK_SIZE];

        block->next = pool->free_list;
        pool->free_list = block;
    }

    printf("[Init] Memory Pool Initialized (%d blocks of %d bytes)\n",
           POOL_SIZE, BLOCK_SIZE);
}


// 2. 할당: Free List의 헤드(Head)를 떼어줌 (Pop)
void* pool_alloc(MemoryPool* pool) {

    // 빈 블록이 없으면 NULL
    if (pool->free_list == NULL) {
        return NULL;
    }

    // 현재 free_list의 첫 번째 블록을 가져옴
    Block* block = pool->free_list;

    // free_list를 다음 빈 블록으로 이동
    pool->free_list = block->next;

    // 사용 중인 블록 수 증가
    pool->used_count++;

    // Block 주소를 사용자에게 반환
    return (void*)block;
}


// 3. 해제: 반환된 블록을 Free List의 헤드에 다시 붙임 (Push)
void pool_free(MemoryPool* pool, void* ptr) {

    // NULL이면 아무것도 안 함
    if (ptr == NULL) {
        return;
    }

    // 반환된 메모리를 Block으로 취급
    Block* block = (Block*)ptr;

    // 현재 free_list 앞에 붙임
    block->next = pool->free_list;
    pool->free_list = block;

    // 사용 중인 블록 수 감소
    pool->used_count--;
}


// 테스트 코드
int main() {

    MemoryPool my_pool;

    pool_init(&my_pool);

    // 3개 할당
    void* p1 = pool_alloc(&my_pool);
    void* p2 = pool_alloc(&my_pool);
    void* p3 = pool_alloc(&my_pool);

    printf("Allocated: %p, %p, %p\n", p1, p2, p3);
    printf("Used Blocks: %d\n", my_pool.used_count);

    // 1개 해제 (p2)
    printf("Freeing %p...\n", p2);
    pool_free(&my_pool, p2);

    // 다시 1개 할당 (p2와 같은 주소가 나와야 함 - LIFO 특성)
    void* p4 = pool_alloc(&my_pool);

    printf("Re-allocated: %p (Should be same as old p2)\n", p4);

    return 0;
}