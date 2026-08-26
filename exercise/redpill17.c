/*
260826 수

- **Day 17. 비트맵 (Bitmap) 관리자**
    - **입력:** 관리할 리소스 개수(예: 100개), 할당/해제 요청
    - **출력:** 할당된 인덱스 번호
    - **제약조건:** `uint8_t` 배열을 비트 단위로 쪼개서 사용 여부 마킹 (1bit = 1resource).
    - **실행결과:**
    
    ```c
    === Day 17: Bitmap Manager ===
    
    >> Index 0 allocated. (Byte 0, Bit 0 set)
    >> Index 1 allocated. (Byte 0, Bit 1 set)
    >> Index 2 allocated. (Byte 0, Bit 2 set)
    >> Index 3 allocated. (Byte 0, Bit 3 set)
    >> Index 4 allocated. (Byte 0, Bit 4 set)
    >> Index 5 allocated. (Byte 0, Bit 5 set)
    >> Index 6 allocated. (Byte 0, Bit 6 set)
    >> Index 7 allocated. (Byte 0, Bit 7 set)
    [Bitmap Visual] 11111111 | 00000000 | 0000
    
    Freeing index 2...
    >> Index 2 freed. (Byte 0, Bit 2 cleared)
    [Bitmap Visual] 11011111 | 00000000 | 0000
    
    Allocating again (expecting index 2)...
    >> Index 2 allocated. (Byte 0, Bit 2 set)
    [Bitmap Visual] 11111111 | 00000000 | 0000
    ```
    
    !image.png
    
    Day17

*/

/*
Bitmap Manager는 리소스 자체를 관리하는 게 아니라, "사용 가능한 번호표(index)를 관리"하는 겁니다
*/

#include <stdint.h>
#include <stdio.h>

#define RESOURCE_COUNT 100
#define BITMAP_SIZE ((RESOURCE_COUNT + 7) / 8)
#define VISUAL_WIDTH 20

uint8_t bitmap[BITMAP_SIZE] = {0};


// 특정 index가 사용 중인지 확인
int is_allocated(int index)
{
    int byte = index / 8;
    int bit  = index % 8;

    return (bitmap[byte] & (1 << bit)) != 0;
}


// Bitmap의 특정 범위만 출력
void Bitmap_Visual(int start, int count)
{
    int end = start + count;

    // 범위를 0 ~ RESOURCE_COUNT 안으로 제한
    if (start < 0)
        start = 0;

    if (end > RESOURCE_COUNT)
        end = RESOURCE_COUNT;

    printf("[Bitmap Visual] Index %d~%d : ",
           start, end - 1);

    for (int i = start; i < end; i++)
    {
        int bit = (bitmap[i / 8] >> (i % 8)) & 1;

        printf("%d", bit);

        // 8비트마다 구분
        if ((i - start + 1) % 8 == 0 &&
            i != end - 1)
        {
            printf(" | ");
        }
    }

    printf("\n");
}


// index 할당
void allocate(int index)
{
    int byte = index / 8;
    int bit  = index % 8;

    if (is_allocated(index))
    {
        printf(">> Index %d is already occupied.\n", index);
        return;
    }

    bitmap[byte] |= (1 << bit);

    printf(">> Index %d allocated. (Byte %d, Bit %d set)\n",
           index, byte, bit);
}


// index 해제
void deallocate(int index)
{
    int byte = index / 8;
    int bit  = index % 8;

    bitmap[byte] &= ~(1 << bit);

    printf(">> Index %d freed. (Byte %d, Bit %d cleared)\n",
           index, byte, bit);
}


int main(void)
{
    printf("=== Day 17: Bitmap Manager ===\n\n");


    // 0 ~ 7 할당
    for (int i = 0; i < 8; i++)
    {
        allocate(i);
    }

    Bitmap_Visual(0, VISUAL_WIDTH);

    printf("\n");


    // index 2 해제
    printf("Freeing index 2...\n");
    deallocate(2);

    Bitmap_Visual(0, VISUAL_WIDTH);

    printf("\n");


    // index 2 다시 할당
    printf("Allocating again (expecting index 2)...\n");
    allocate(2);

    Bitmap_Visual(0, VISUAL_WIDTH);


    return 0;
}
