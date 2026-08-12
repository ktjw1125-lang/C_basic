/*

260806 Thu
Day1 특정 비트 제어 매크로 구현

입력 : 32비트 정수 0x12345678, 조작할 비트 위치(3), 동작(set/clear/toggle)
출력 : 조작된 16진수 값
제약조건 : <stdint.h> 사용할것, 함수가 아닌 매크로로 구현할것
실행결과 : set 3rd bit of 0x... -> 0x...

=== Day 1: Bitwise Macro Test ===
[Init]   Hex: 0x12345678 | Bin: 0001 0010 0011 0100 0101 0110 0111 1000

[SET]    Target: Bit 0
Result   Hex: 0x12345679 | Bin: 0001 0010 0011 0100 0101 0110 0111 1001

[CLEAR]  Target: Bit 4
Result   Hex: 0x12345669 | Bin: 0001 0010 0011 0100 0101 0110 0110 1001

[TOGGLE] Target: Bit 3
Result   Hex: 0x12345661 | Bin: 0001 0010 0011 0100 0101 0110 0110 0001

[CHECK]  Bit 3 is currently: 0

*/

#include <stdint.h>
#include <stdio.h>

#define BIT_SET(var, pos) ((var) |= (1UL << (pos)))
#define BIT_CLEAR(var, pos) ((var) &= ~(1UL << (pos)))
#define BIT_TOGGLE(var, pos) ((var) ^= (1UL << (pos)))
#define BIT_CHECK(var, pos) (!!((var) & (1UL << (pos))))

char *print_bin(uint32_t num) // 이 함수는 char * 타입을 반환한다 // 16진수(hex) -> 2진수(str)
{
    static char result[40]; // 함수가 끝나도 메모리에 남아있습니다. // 40 = 32비트 + 빈칸7 + \n
    int pos = 0;

    for (int i = 31; i >= 0; i--)
    {
        result[pos++] = ((num >> i) & 1) + '0'; // 0의 아스키코드 48에 1을 더함 -> 문자 1이 됨

        if (i % 4 == 0 && i != 0)
        {
            result[pos++] = ' ';
        }
    }

    result[pos] = '\0';

    return result;
}

int main(int argc, char const *argv[])
{
    char input[11];
    input[0] = '0';
    input[1] = 'x';
    int32_t num = 0; // 0x12345678;

    printf("\n=== Day 1: Bitwise Macro Test ===\n\n");

    int input_done = 0;
    while (!input_done)
    {
        int len_error = 0;

        printf("16진수 8자리(32비트) 입력해주세요 : 0x");
        scanf("%s", &input[2]);

        if (strlen(input) != 10)
        {
            printf("\nerror : 8자리 입력해주세요\n\n");
            continue;
        }
        for (int i = 2; i < 10; i++)
        {
            if (!((input[i] >= '0' && input[i] <= '9') ||
                  (input[i] >= 'a' && input[i] <= 'f') ||
                  (input[i] >= 'A' && input[i] <= 'F')))
            {
                printf("\nerror : 0-9, a-f, A-F만으로 입력해주세요\n\n");
                len_error = 1;
                break;
            }
        }
        if (len_error == 1)
            continue;

        input_done = 1;
    }

    num = (int32_t)strtol(input, NULL, 0);
    printf("\n----------------------------------------\n");
    printf("\n[Init]   Hex: 0x%X | Bin: %s\n", num, print_bin(num));
    printf("\n----------------------------------------\n\n");

    while (1)
    {
        int bit = 0;
        printf("조작할 비트 위치(종료: -1) : ");
        scanf("%d", &bit);

        if (bit == -1)
            break;

        input_done = 0;
        char task[7];

        while (!input_done)
        {
            printf("동작(set/clear/toggle/check) : ");
            scanf("%6s", task);

            if (strcmp(task, "set") != 0 &&
                strcmp(task, "clear") != 0 &&
                strcmp(task, "toggle") != 0 &&
                strcmp(task, "check") != 0)
            {
                printf("\nerror : set/clear/toggle/check 중에서 입력해주세요\n\n");
                continue;
            }
            input_done = 1;
        }

        printf("\n");

        if (strcmp(task, "set") == 0)
        {
            num = BIT_SET(num, bit);
            printf("[SET]     Target: Bit %d\n", bit);
            printf("Result   Hex: 0x%X | Bin: %s\n", num, print_bin(num));
        }
        else if (strcmp(task, "clear") == 0)
        {
            num = BIT_CLEAR(num, bit);
            printf("[CLEAR]   Target: Bit %d\n", bit);
            printf("Result   Hex: 0x%X | Bin: %s\n", num, print_bin(num));
        }
        else if (strcmp(task, "toggle") == 0)
        {
            num = BIT_TOGGLE(num, bit);
            printf("[TOGGLE]  Target: Bit %d\n", bit);
            printf("Result   Hex: 0x%X | Bin: %s\n", num, print_bin(num));
        }
        else if (strcmp(task, "check") == 0)
        {
            printf("[CHECK]   Bit %d is currently: %d\n",
                   bit, BIT_CHECK(num, bit));
        }

        printf("\n----------------------------------------\n\n");
    }

    // num = BIT_SET(num, 0);
    // printf("[SET]    Target: Bit 0\n");
    // printf("Result   Hex: 0x%X | Bin: %s\n\n", num, print_bin(num));

    // num = BIT_CLEAR(num, 4);
    // printf("[CLEAR]    Target: Bit 4\n");
    // printf("Result   Hex: 0x%X | Bin: %s\n\n", num, print_bin(num));

    // num = BIT_TOGGLE(num, 3);
    // printf("[TOGGLE]    Target: Bit 3\n");
    // printf("Result   Hex: 0x%X | Bin: %s\n\n", num, print_bin(num));

    // printf("[CHECK]  Bit 3 is currently: %d\n\n", BIT_CHECK(num, 3));

    return 0;
}
