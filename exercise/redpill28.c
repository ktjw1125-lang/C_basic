/*

- **Day 28. 가변 인자 함수 구현 (my_printf)**
    - **입력:** 포맷 스트링 `"%d %s"`, 가변 인자
    - **출력:** 포맷팅된 문자열 출력
    - **제약조건:** `<stdarg.h>` 사용, `%d`, `%x`, `%s`만 지원.
    
    ```c
    int main() {
        printf("=== Day 28: Custom printf Implementation ===\n\n");
    
        // Test 1: 정수와 문자열
        my_printf("MyPrint: %d %s\n", 10, "test");
    
        // Test 2: 16진수와 음수
        my_printf("Hex: 0x%x, Negative: %d\n", 255, -12345);
    
        // Test 3: 여러 인자 혼합
        my_printf("Result: %d + %d = %d\n", 10, 20, 30);
    
        return 0;
    }
    ```
    
    - **실행결과:**
    
    ```bash
    === Day 28: Custom printf Implementation ===
    
    MyPrint: 10 test
    Hex: 0xFF, Negative: -12345
    Result: 10 + 20 = 30
    ```
    
    Day28

*/

/*

printf(format, ???)
              ↑
        몇 개가 올지 모름

이런 함수를 **가변 인자 함수(variadic function)**라고 합니다.

... 가변 인자 문법
<stdarg.h>
va_list
→ 가변 인자를 읽기 위한 변수

va_start
→ 읽기 시작할 준비

va_arg
→ 다음 인자 하나 꺼내기

va_end
→ 다 읽었으니 종료

포맷 문자열 파싱
자료형에 따라 가변 인자를 다르게 가져오는 방법
특히 va_arg(ap, int)와 va_arg(ap, char *)가 왜 필요한지 이해

*/

#include <stdio.h>
#include <stdarg.h>

void my_printf(const char *fmt, ...)
{
    va_list ap; // 가변 인자를 읽기 위한 변수 준비

    va_start(ap, fmt); // ap가 첫 번째 가변 인자를 읽을 수 있도록 준비

    while (*fmt) // fmt가 가리키는 문자가 '\0'이 아닐 동안 반복
    {
        if (*fmt != '%') // 현재 문자가 %가 아닌 경우
        {
            putchar(*fmt);
            fmt++;
            continue;
        }

        fmt++;

        // 현재 문자가 %인 경우
        if (*fmt == 'd')
        {
            int n = va_arg(ap, int); // ap가 가리키는 다음 가변 인자를 int라고 생각하고 가져오기
            printf("%d", n);
        }
        else if (*fmt == 'x')
        {
            unsigned int n = va_arg(ap, unsigned int);
            printf("%x", n);
        }
        else if (*fmt == 's')
        {
            char *s = va_arg(ap, char *);
            printf("%s", s);
        }

        fmt++;
    }

    va_end(ap);
}


int main(void)
{
    my_printf("=== Day 28: Custom printf Implementation ===\r\n\n");
    my_printf("hello\n");
    my_printf("MyPrint: %d %s\n", 10, "test");
    my_printf("Hex: 0x%x, Negative: %d\n", 255, -12345);
    my_printf("Result: %d + %d = %d\n", 10, 20, 10+20);

    return 0;
}