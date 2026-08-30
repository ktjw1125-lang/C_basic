/*

- **Day 18. 우선순위 큐 (Min Heap) - 태스크 스케줄링용**
    - **입력:** (TaskID, Priority) 쌍 삽입, Pop 요청
    - **출력:** 우선순위가 가장 높은(숫자가 낮은) TaskID 반환
    - **제약조건:** 배열 기반 힙 구현.
    - **실행결과:**
    
    ```c
    === Day 18: Task Scheduler (Min Heap) ===
    
    Tasks pushed: (1, 50), (2, 10), (3, 5), (5, 0), (4, 100)
    Processing Tasks...
    
    >> Executing Task 5 (Priority 0)
    >> Executing Task 3 (Priority 5)
    >> Executing Task 2 (Priority 10)
    >> Executing Task 1 (Priority 50)
    >> Executing Task 4 (Priority 100)
    
    ```
    
    입력 순서와 상관없이, **우선순위 숫자(0 → 5 → 10...)** 순서대로 정확하게 출력
    
    Day18

*/

/*
- **memory heap vs min heap**
    
    **둘은 이름만 같을 뿐 완전히 다른 개념입니다.**
    
    사용자가 작성한 태스크 스케줄링 코드에서 사용된 Min Heap(최소 힙)은 '자료구조'를 뜻하며, 메모리 구조의 Heap(힙 영역)은 '런타임 메모리 관리 구역'을 뜻합니다.
    
    이 차이를 명확히 이해하는 것이 로우 레벨 프로그래밍에서 매우 중요합니다. 
    
    ### 1. 사용자의 코드에서 사용된 Min Heap (자료구조)
    
    구현하신 것은 **데이터를 조직화하는 수학적/논리적 방법**입니다.
    
    - **정의:** 완전 이진트리(Complete Binary Tree)의 일종으로, **부모 노드의 값이 자식 노드의 값보다 항상 작거나 같은** 특징을 가집니다.
    - **목적:** 여러 데이터 중 **최솟값(우선순위가 가장 높은 것)을 빠르게(O(1)) 찾아내고**, 데이터를 삽입/삭제할 때 힙 구조를 유지( $O(\log N)$)하기 위해 사용됩니다.
    - **물리적 구현:** 트리 모양이지만, 실제로는 제약조건처럼 일반적인 '배열'에 데이터를 특정 규칙에 따라 배치하여 구현합니다.
    - **메모리와의 관계:** 이 배열은 스택(Stack) 영역에 있을 수도 있고, 메모리 구조의 힙(Heap) 영역에 있을 수도 있습니다. 핵심은 그 데이터가 배열 내에서 '최소 힙 규칙'에 따라 정렬되어 있다는 점입니다.
    
    ### 2. 메모리 구조의 Heap (런타임 메모리 관리 구역)
    
    이것은 프로그램이 실행될 때 **운영체제(OS)로부터 할당받는 물리적인 RAM 공간의 일부**입니다.
    
    - **정의:** 프로그램이 실행 중에 크기가 결정되는 데이터를 저장하기 위해 사용되는 **동적 메모리 할당 영역**입니다.
    - **목적:** 컴파일 타임에 크기를 알 수 없는 배열, 구조체 등을 **런타임에 `malloc()`, `calloc()` (C언어) 또는 `new` (C++) 함수를 통해 메모리를 할당**받아 저장합니다.
    - **특징:** 사용자가 원할 때 할당받고, 반드시 원할 때 `free()` 또는 `delete`를 통해 메모리를 해제해야 합니다. (하지 않으면 메모리 누수 발생).
    - **구조:** 자료구조 힙처럼 이진트리 형태가 아닙니다. OS가 관리하는 빈 메모리 블록들의 집합에 가깝습니다.
    
    ---
    
    - **느슨한 정렬 (Partial Order):** 이진 탐색 트리(BST)는 왼쪽 노드는 작고 오른쪽 노드는 커야 한다는 엄격한 횡적/종적 정렬 규칙이 있음. 반면 힙은 오직 '부모가 자식보다 우선순위가 높다'는 종적인 규칙만 존재함.
    - **루트(Root) 노드의 특권:** 건초더미에서 가장 눈에 띄는 맨 꼭대기에 가장 큰(또는 가장 작은) 값 하나만 올려두면 됨.
    - **하위 구조의 무작위성:** 형제 노드들 사이에는 대소 관계 규칙이 전혀 없음. 꼭대기를 제외한 밑바닥의 데이터들은 그저 조건만 대충 맞춘 채 흩뿌려져 있는 '더미'와 같기 때문에 Heap이라는 이름이 논리적 구조와 완벽히 부합함.
*/

/*
핵심은 배열로 Min Heap을 만들고, push()와 pop()을 구현하는 것

        (5, 0)
       /      \
   (3, 5)    (2, 10)
   /   \
(1,50) (4,100)


Min Heap의 핵심은 사실 세 개
//  부모 
// parent = (index - 1) / 2;

//  왼쪽 자식 
// left = index * 2 + 1;

//  오른쪽 자식 
// right = index * 2 + 2;

push
→ 맨 뒤에 넣음
→ 부모보다 작으면 위로 올림

pop
→ heap[0] 꺼냄
→ 마지막 원소를 0번으로 이동
→ 자식 중 작은 놈과 바꾸면서 아래로 내림

*/

#include <stdio.h>

// Task 하나
#define MAX_SIZE 100

typedef struct
{
    int task_id;
    int priority;
} Task;


// Heap 배열
typedef struct
{
    Task heap[MAX_SIZE];
    int size;
} MinHeap;

/* 두 Task 교환 */
void swap(Task *a, Task *b)
{
    Task temp = *a;
    *a = *b;
    *b = temp;
}

// Push - 새로운 Task를 배열의 맨 뒤에 넣고, 부모와 비교하면서 위로 올리면 된다.
void push(MinHeap *h, int task_id, int priority)
{
    if (h->size >= MAX_SIZE)
    {
        printf("Heap is full!\n");
        return;
    }

    /* 맨 뒤에 삽입 */
    int index = h->size;

    h->heap[index].task_id = task_id;
    h->heap[index].priority = priority;

    h->size++;

    /* 부모와 비교하면서 위로 이동 */
    while (index > 0)
    {
        int parent = (index - 1) / 2;

        if (h->heap[parent].priority <= h->heap[index].priority)
            break;

        swap(&h->heap[parent], &h->heap[index]);

        index = parent;
    }
}

// Pop - Pop은 항상 heap[0]을 꺼낸다.
Task pop(MinHeap *h)
{
    Task result = h->heap[0];

    /* 마지막 원소를 루트로 이동 */
    h->size--;
    h->heap[0] = h->heap[h->size];

    /* 아래로 내려가면서 정렬 */
    int index = 0;

    while (1)
    {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int smallest = index;

        /* 왼쪽 자식 */
        if (left < h->size &&
            h->heap[left].priority < h->heap[smallest].priority)
        {
            smallest = left;
        }

        /* 오른쪽 자식 */
        if (right < h->size &&
            h->heap[right].priority < h->heap[smallest].priority)
        {
            smallest = right;
        }

        /* 현재가 가장 작으면 종료 */
        if (smallest == index)
            break;

        swap(&h->heap[index], &h->heap[smallest]);

        index = smallest;
    }

    return result;
}

int main(void)
{
    MinHeap h;

    h.size = 0;

    printf("=== Day 18: Task Scheduler (Min Heap) ===\n\n");

    /* Task 삽입 */
    push(&h, 1, 50);
    push(&h, 2, 10);
    push(&h, 3, 5);
    push(&h, 5, 0);
    push(&h, 4, 100);

    printf("Tasks pushed: ");
    printf("(1, 50), ");
    printf("(2, 10), ");
    printf("(3, 5), ");
    printf("(5, 0), ");
    printf("(4, 100)\n");

    printf("Processing Tasks...\n\n");

    /* 하나씩 꺼내서 실행 */
    while (h.size > 0)
    {
        Task task = pop(&h);

        printf(">> Executing Task %d (Priority %d)\n",
               task.task_id,
               task.priority);
    }

    return 0;
}