/*

- **Day 12. 구조체 멤버 오프셋 매크로 (offsetof 구현)**
    - **입력:** 구조체 타입명, 멤버 변수명
    - **출력:** 구조체 시작 주소로부터 해당 멤버까지의 바이트 거리
    - **제약조건:** `<stddef.h>` 표준 offsetof 사용 (비교용)  ⇒ 사용 금지. 0번지 주소 캐스팅 기법 활용.
    - **실행결과:**
    
    ```bash
    === Day 12: offsetof Implementation ===
    
    Struct Size: 16 bytes
    
    [Standard] Offset of a: 0
    [Standard] Offset of b: 4
    [Standard] Offset of c: 8
    
    -----------------------------
    
    [My Macro] Offset of a: 0
    [My Macro] Offset of b: 4
    [My Macro] Offset of c: 8
    
    >> Success! Implementation is correct.
    ```
    
    참고
    
    ```bash
    
     * [핵심 매크로] my_offsetof
     * type: 구조체 타입 이름 (예: struct Data)
     * member: 멤버 변수 이름 (예: b)
     
    #define my_offsetof(type, member)  ((size_t)&(((type *)0)->member))
    
    // 테스트를 위한 구조체 (패딩이 발생하는 구조)
    typedef struct {
        char a;      // 1 byte
        // (padding 3 bytes) - 4바이트 정렬을 위해 컴파일러가 넣음
        int b;       // 4 bytes
        double c;    // 8 bytes
    } Sample;
    ```
    
    Day12
    
*/



/*  스터디

offsetof는 
구조체(struct) 안에서 특정 멤버가 구조체 시작 주소로부터 
몇 바이트 떨어져 있는지(offset)를 구하는 기능



struct Person {
    char name[20];
    int age;
    double height;
};

offsetof(struct Person, age)

struct Person *p;

(char *)p + offsetof(struct Person, age)
// 구조체 시작점 + age까지의 거리를 간 주소값이 출력
// char *가 붙는 이유는 주소를 바이트 단위로 계산하려고

size_t a1 = offsetof(Data, a); 이렇게 쓰면 크기로 구해짐

// offset 아닌 실제주소 얻을때
&p->age


// 직접 구현시
#define offsetof(type, member) ((size_t)& ( ( (type *)0 )->member) )
// 구조체 첫 주소를 0으로 가정했을때, member의 주소

// type : 구조체의 자료형 이름
// type 자리에 struct Person이 들어감

// (type *)0 : 0번지 주소를 type 포인터로 바꾼 것 
// "주소가 0인 곳에 struct Person이 있다고 가정하자"라는 의미
// 주소값 0을 직접 지정하고, 그 주소를 type* 포인터라고 해석하겠다

// ((type *)0)->member : 그 구조체의 member 위치를 가리키는 것
// "주소 0에 있는 struct Person의 age 멤버"

// & : 그 멤버의 주소값 = 구조체 시작점으로부터의 offset을 얻는다


*/

#include <stdio.h>
#include <stddef.h>

#define myoffsetof(type, member) ((size_t)&(((type *)0)->member))

typedef struct {
    char a;
    int b;
    double c;
} Data;

int main(void)
{
    printf("=== Day 12: offsetof Implementation ===\n\n");

    Data d;

    printf("Struct Size: %zu bytes\n\n", sizeof(d));

    size_t a1 = offsetof(Data, a);
    size_t b1 = offsetof(Data, b);
    size_t c1 = offsetof(Data, c);
    
    size_t a2 = myoffsetof(Data, a);
    size_t b2 = myoffsetof(Data, b);
    size_t c2 = myoffsetof(Data, c);

    printf("[Standard] Offset of a: %zu\n", a1);
    printf("[Standard] Offset of b: %zu\n", b1);
    printf("[Standard] Offset of c: %zu\n", c1);

    printf("\n-----------------------------\n\n");

    printf("[My Macro] Offset of a: %zu\n", a2);
    printf("[My Macro] Offset of b: %zu\n", b2);
    printf("[My Macro] Offset of c: %zu\n", c2);

    printf("\n");

    if ((a1 == a2) && (b1 == b2) && (c1 == c2))
        printf(">> Success! Implementation is correct.\n");
    else
        printf(">> Fail\n");

    return 0;
}