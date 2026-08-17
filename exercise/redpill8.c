/*
- **Day 8. 안전한 Memcpy 구현 (Overlap 처리)**
    - **입력:** 소스 주소, 목적지 주소, 복사할 바이트 수
    - **출력:** 메모리 복사 후 목적지 주소의 데이터 덤프
    - **제약조건:** `memcpy` 대신 `memmove` 동작 구현 (src와 dest 영역이 겹칠 때 데이터 오염 방지).
    - **실행결과:**
s
    ```c

        // 복사: 0~4번지(5개)를 2~6번지로 이동
        // 복사: 2~6번지(5개)를 0~4번지로 이동
    ```

    ```c
    === Day 8: Safe Memcpy (memmove) Implementation ===

    [Initial] **01 02 03 04 05** 06 07 08 09 0A

    Test 1: Overlap (Dest > Src) -> Shift Right 2 bytes
    [Result ] 01 02 **01 02 03 04 05** 08 09 0A
    >> Success!

    [Initial] 01 02 **03 04 05 06 07** 08 09 0A
    Test 2: Overlap (Dest < Src) -> Shift Left 2 bytes
    [Result ] **03 04 05 06 07** 06 07 08 09 0A
    >> Success!
    ```
*/

#include <stdint.h>
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

void print_data(const uint8_t *data, size_t size, int first, int num);

void *my_memmove(void *dest, const void *src, size_t n)
// void *memmove : memmove가 포인터를 반환
// const : "src가 가리키는 데이터를 함수 안에서 수정하지 않겠다"는 뜻
// void * : 어떤 자료형의 주소든 받을 수 있는 포인터
// size_t : 메모리 크기나 배열 크기를 나타낼 때 사용하는 unsigned 정수 타입
{
    unsigned char *d = dest;
    const unsigned char *s = src;
    // unsigned char * : 메모리 주소를 1바이트 단위로 다루기 위해서

    if (d < s) // dest가 src 앞에있으면 앞에서부터 복사
    {
        for (size_t i = 0; i < n; i++)
            d[i] = s[i];
    }
    else if (d > s) // dest가 src보다 뒤에 있다면 뒤에서부터 복사 (오버랩 대응)
    {
        for (size_t i = n; i > 0; i--)
            d[i - 1] = s[i - 1];
    }

    return dest;
}

int main(int argc, char const *argv[])
{
    printf("=== Day 8: Safe Memcpy (memmove) Implementation ===\r\n\n");

    // test 1
    printf("Test 1: Overlap (Dest = 2 > Src = 0) -> Shift Right 2 bytes\r\n");

    uint8_t data[10] = {
        0x01, 0x02, 0x03, 0x04, 0x05,
        0x06, 0x07, 0x08, 0x09, 0x0A};

    printf("[Initial] ");
    print_data(data, ARRAY_SIZE(data), 0, 5);

    my_memmove(&data[2], &data[0], 5);

    printf("[Result] ");
    print_data(data, ARRAY_SIZE(data), 2, 5);
    printf(">> Success!\r\n\n");

    // test 2
    printf("Test 2: Overlap (Dest = 0 < Src = 2) -> Shift Left 2 bytes\r\n");

    uint8_t data2[10] = {
        0x01, 0x02, 0x03, 0x04, 0x05,
        0x06, 0x07, 0x08, 0x09, 0x0A};

    printf("[Initial] ");
    print_data(data2, ARRAY_SIZE(data2), 2, 5);

    my_memmove(&data2[0], &data2[2], 5);

    printf("[Result] ");
    print_data(data2, ARRAY_SIZE(data2), 0, 5);
    printf(">> Success!\r\n\n");

    return 0;
}

void print_data(const uint8_t *data, size_t size, int first, int num)
{
    for (size_t i = 0; i < size; i++)
    {
        if (i == first)
            printf("(");

        printf("%02X", data[i]);

        if (i == first + num - 1)
            printf(")");

        if (i < size - 1)
            printf(" ");
    }

    printf("\r\n");
}