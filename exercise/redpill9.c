/*
- **Day 9. 제네릭 Swap 함수 (void)***
    - **입력:** 두 변수의 주소 `void *a, void *b`, 데이터 크기 `size_t size`
    - **출력:** 두 변수의 값이 교환됨
    - **제약조건:** `malloc` 사용 금지, 바이트 단위 교환 알고리즘 사용.
    - **실행결과:**
    
    ```c
    === Day 9: Generic Swap Implementation ===
    
    [Int] Before: 10, 20
    [Int] After : 20, 10
    
    [Double] Before: 3.14159, 99.99000
    [Double] After : 99.99000, 3.14159
    
    [Struct] Before: Kim(1), Lee(2)
    [Struct] After : Lee(2), Kim(1)
    ```

*/

#include <stdio.h>
#include <stddef.h> // size_t 사용을 위한

void swap(void *a, void *b, size_t size)
// 어떤 타입이 들어올지 알수 없다; 메모리를 바이트 단위로만 처리한 것
// size_t는 주로 배열의 크기, 메모리 크기, 문자열 길이 같은 "크기"를 표현할 때 쓰는 타입
// (unsigned integer type)
{
    unsigned char *pa = (unsigned char *)a; // 바이트 단위로 처리를 위해 char 사용
    unsigned char *pb = (unsigned char *)b;

    for (size_t i = 0; i < size; i++)
    {
        unsigned char temp = pa[i]; // 역참조 값 교환
        pa[i] = pb[i];
        pb[i] = temp;
    }
}

typedef struct
{
    char name[10]; // 고정크기 배열
    int id;
} Person;

int main(void)
{
    printf("=== Day 9: Generic Swap Implementation ===\n\n");

    // Int
    int a = 10;
    int b = 20;

    printf("[Int] Before: %d, %d\n", a, b);

    swap(&a, &b, sizeof(a));

    printf("[Int] After : %d, %d\n\n", a, b);


    // Double
    double x = 3.14159;
    double y = 99.99000;

    printf("[Double] Before: %.5f, %.5f\n", x, y);

    swap(&x, &y, sizeof(x));

    printf("[Double] After : %.5f, %.5f\n\n", x, y);


    // Struct
    Person kim = {"Kim", 1};
    Person lee = {"Lee", 2};

    printf("[Struct] Before: %s(%d), %s(%d)\n",
           kim.name, kim.id, lee.name, lee.id);

    swap(&kim, &lee, sizeof(kim));

    printf("[Struct] After : %s(%d), %s(%d)\n",
           kim.name, kim.id, lee.name, lee.id);

    return 0;
}