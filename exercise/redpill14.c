// 260821 금

/*
- **Day 14. 헥사 덤프 (Hexdump)**
    
    ```c
    // 테스트 1: 단순 문자열
        char my_text[] = "Hello Embedded World! This is Hexdump.";
        hexdump("String Dump", my_text, sizeof(my_text));
      
        // 테스트 2: 구조체 (엔디안 확인 가능)
        SensorData sensor = { 0x12345678, "Sensor A", 3.14f };
        hexdump("Struct Dump", &sensor, sizeof(sensor)); 
    ```
    
    - **출력:** 주소 오프셋 | 16진수 데이터 16개 | ASCII 표현
    - **제약조건:** 출력 불가능 문자는 `.`으로 표시.
    - **실행결과:**
    
    ```c
    String Dump:
      0000  48 65 6c 6c 6f 20 45 6d 62 65 64 64 65 64 20 57  Hello Embedded W
      0010  6f 72 6c 64 21 20 54 68 69 73 20 69 73 20 48 65  orld! This is He
      0020  78 64 75 6d 70 2e 00                             xdump..
    
    Struct Dump:
      0000  78 56 34 12 53 65 6e 73 6f 72 20 41 00 00 00 00  xV4.Sensor A....
      0010  c3 f5 48 40                                      ..H@
    
    ```
    
    Day14
*/

#include <stdio.h>
#include <stdint.h>
#include <ctype.h> // isprint 쓰기위해
#include <stddef.h> // size_t 쓰기위해

typedef struct {
    uint32_t id;
    char name[12];
    float value;
} SensorData;

void hexdump(const char *title, const void *data, size_t size)
{
    // data가 가리키는 주소를 bytes도 가리키게 하고, 그 메모리를 unsigned char 단위로 읽는 것
    const unsigned char *bytes = (const unsigned char *)data;

    printf("%s:\n", title);

    for (size_t offset = 0; offset < size; offset += 16) {

        // 주소 오프셋
        printf("  %04zx  ", offset);

        // 16진수 출력
        for (size_t i = 0; i < 16; i++) {
            if (offset + i < size)
                printf("%02x ", bytes[offset + i]);
            else
                printf("   ");
        }

        // ASCII 구분
        printf(" ");

        // ASCII 출력
        for (size_t i = 0; i < 16; i++) {
            if (offset + i < size) {
                unsigned char c = bytes[offset + i];

                if (isprint(c)) // 인쇄 가능한 문자인지 확인
                    putchar(c); // 문자1개 출력
                else
                    putchar('.');
            }
        }

        putchar('\n');
    }

    putchar('\n');
}

int main(void)
{
    // 테스트 1: 단순 문자열
    char my_text[] = "Hello Embedded World! This is Hexdump.";
    hexdump("String Dump", my_text, sizeof(my_text));

    // 테스트 2: 구조체 (엔디안 확인 가능)
    SensorData sensor = { 0x12345678, "Sensor A", 3.14f };
    hexdump("Struct Dump", &sensor, sizeof(sensor));

    return 0;
}
