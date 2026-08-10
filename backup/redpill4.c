/*
Day 4. 비트 단위 Reverse (Mirroring)
입력: 8비트 정수 0b11010010
출력: 0b01001011 (비트 순서 반전)
제약조건: Lookup Table(LUT)을 사용하지 않고 O(1) 비트 연산으로 구현.
실행결과:
=== Day 4: Bitwise Reverse (Mirroring) ===

Case 1:
  Input : 0xD2 (1101 0010)
  Output: 0x4B (0100 1011)
  Verify: OK
------------------------
Case 2:
  Input : 0x0F (0000 1111)
  Output: 0xF0 (1111 0000)
  Verify: OK
------------------------
Case 3:
  Input : 0xAA (1010 1010)
  Output: 0x55 (0101 0101)
  Verify: OK
------------------------
Case 4:
  Input : 0x12 (0001 0010)
  Output: 0x48 (0100 1000)
  Verify: OK
------------------------
*/

#include <stdio.h>
#include <stdint.h>

uint8_t reverse_bits(uint8_t x);
void print_result(uint8_t input, uint8_t output);

int main(int argc, char const *argv[])
{
    uint8_t input[] = {0xD2, 0x0F, 0xAA, 0x12};
    uint8_t expected[] = {0x4B, 0xF0, 0x55, 0x48};

    uint8_t output;
    printf("=== Day 4: Bitwise Reverse (Mirroring) ===\r\n\n");
    for (int i = 0; i < 4; i++)
    {
        output = reverse_bits(input[i]);

        printf("Case %d:\r\n", i + 1);
        print_result(input[i], output);

        if (output == expected[i])
            printf("Verify: OK\r\n");
        else
            printf("Verify: FAIL (Expected: 0x%02X)\r\n", expected[i]);

        printf("------------------------\r\n");
    }

    return 0;
}

uint8_t reverse_bits(uint8_t x)
{
    x = ((x & 0xF0) >> 4) | ((x & 0x0F) << 4); // 1111 0000, 0000 1111
    x = ((x & 0xCC) >> 2) | ((x & 0x33) << 2); // 1100 1100, 0011 0011
    x = ((x & 0xAA) >> 1) | ((x & 0x55) << 1); // 1010 1010, 0101 0101

    return x;
}

void print_result(uint8_t input, uint8_t output)
{
    uint8_t values[] = {input, output};
    char *names[] = {"Input", "Output"};

    for (int j = 0; j < 2; j++)
    {
        printf("%s: 0x%02X (", names[j], values[j]);

        for (int i = 7; i >= 0; i--)
        {
            printf("%d", (values[j] >> i) & 1);
            if (i == 4)
                printf(" ");
        }

        printf(")\r\n");
    }
}
