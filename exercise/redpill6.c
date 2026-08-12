/*
- **Day 6. 원형 비트 시프트 (Circular Shift/Rotate)**
    - **입력:** 32비트 정수, 이동할 비트 수 `n`, 방향(Left/Right)
    - **출력:** 회전된 결과값
    - **제약조건:** 버려지는 비트가 반대편으로 채워져야 함.
    - **실행결과:**

=== Day 6: Circular Shift (Rotate) ===

[Init]   Hex: 0xF0000000
         Bin: 1111 0000 0000 0000 0000 0000 0000 0000

[ROL 4]  Hex: 0x0000000F
         Bin: 0000 0000 0000 0000 0000 0000 0000 1111
         (MSB bits moved to LSB)

[ROR 4]  Hex: 0xF0000000
         Bin: 1111 0000 0000 0000 0000 0000 0000 0000
         (Restored to original)

[Test 2] Data: 0x12345678 -> ROR 8 -> 0x78123456
*/
#include <stdio.h>
#include <stdint.h>

char *get_input(void);
uint32_t rotate_bits(int, char, uint32_t);
char *print_binary(uint32_t);
void print_result(int, char, uint32_t);

int main(int argc, char const *argv[])
{
    printf("=== Day 6: Circular Shift (Rotate) ===\r\n\n");

    uint32_t x = (int32_t)strtoul(get_input(), NULL, 0);

    printf("\n[Init]   Hex: 0x%08X\r\n", x);
    printf("         Bin: %s \r\n\n", print_binary(x));

    int pos = 0;
    char direc = '\0';
    while (1)
    {
        printf("how many bits to rotate? (-1 to quit) : ");
        scanf("%d", &pos);

        if (pos == -1)
            break;

        printf("left or right direction? (L/R) : ");
        scanf(" %c", &direc); // 공백 중요; 입력 버퍼에 남아있는 \n, 스페이스 같은 공백 문자들을 건너뜀

        x = rotate_bits(pos, direc, x);
        print_result(pos, direc, x);
    }

    return 0;
}

char *get_input(void)
{
    static char input[2 + 8 + 1];
    input[0] = '0';
    input[1] = 'x';

    int input_done = 0;
    while (!input_done)
    {
        int len_error = 0;

        printf("Enter an 8-digit hex value (32-bit): 0x");
        scanf("%s", &input[2]);

        if (strlen(input) != 10)
        {
            printf("\nerror : Enter 8 digits.\n\n");
            continue;
        }
        for (int i = 2; i < 10; i++)
        {
            if (!((input[i] >= '0' && input[i] <= '9') ||
                  (input[i] >= 'a' && input[i] <= 'f') ||
                  (input[i] >= 'A' && input[i] <= 'F')))
            {
                printf("\nerror : Use only 0-9, a-f, A-F.\n\n");
                len_error = 1;
                break;
            }
        }
        if (len_error == 1)
            continue;

        input_done = 1;
    }

    return input;
}

uint32_t rotate_bits(int pos, char direc, uint32_t x)
{
    if (direc == 'L')

        // ROL (Rotate Leftward)
        x = (x << pos) | (x >> (32 - pos));

    else
        // ROR (Rotate Rightward)
        x = (x >> pos) | (x << (32 - pos));

    return x;
}

char *print_binary(uint32_t x)
{
    static char bin[32 + 7 + 1];
    int n = 0; // 이진수를 왼쪽부터 하나씩 얻어내 문자열로 쌓는다.
    for (int i = 31; i >= 0; i--)
    {
        bin[n++] = ((x >> i) & 1) + '0'; // 0 아스키 값에 1인경우 1 더해줌, 0인경우 '0' 전달

        if (i % 4 == 0 && i != 0)
            bin[n++] = ' ';
    }

    bin[n] = '\0';

    return bin;
}

void print_result(int pos, char direc, uint32_t x)
{
    if (direc == 'L')
    {
        printf("\n[ROL %d]  Hex: 0x%08X\r\n", pos, x);
        printf("         Bin: %s \r\n", print_binary(x));
        printf("         (MSB bits moved to LSB)\r\n\n");
        // MSB = Most Significant Bit
        // LSB = Least Significant Bit
        // 큰 자리값(MSB 쪽 비트)을 작은 자리값(LSB 쪽)으로 이동시킨다
    }
    else
    {
        printf("\n[ROR %d]  Hex: 0x%08X\r\n", pos, x);
        printf("         Bin: %s \r\n", print_binary(x));
        printf("         (LSB bits moved to MSB)\r\n\n");
    }
}