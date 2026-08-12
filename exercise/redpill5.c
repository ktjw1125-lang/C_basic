/*
Day 5. 1의 개수 세기 (Population Count)
입력: 32비트 정수
출력: 켜져 있는 비트(1)의 개수
제약조건: 루프(for/while) 없이 비트 연산만으로 구현 (Brian Kernighan 알고리즘 등 활용).
실행결과:
=== Day 5: Population Count (Counting Set Bits) ===

Case 1: Input 0x00000000
  [Naive]     : 0
  [Kernighan] : 0 (Recommended Logic)
  [SWAR]      : 0 (Strict Loop-free)
  [Built-in]  : 0
------------------------------
Case 2: Input 0x00000007
  [Naive]     : 3
  [Kernighan] : 3 (Recommended Logic)
  [SWAR]      : 3 (Strict Loop-free)
  [Built-in]  : 3
------------------------------
Case 3: Input 0x12345678
  [Naive]     : 13
  [Kernighan] : 13 (Recommended Logic)
  [SWAR]      : 13 (Strict Loop-free)
  [Built-in]  : 13
------------------------------
Case 4: Input 0xFFFFFFFF
  [Naive]     : 32
  [Kernighan] : 32 (Recommended Logic)
  [SWAR]      : 32 (Strict Loop-free)
  [Built-in]  : 32
------------------------------

0000 0007 = 0000 0000 0000 0000 / 0000 0000 0000 0111 = 3개
1234 5678 = 0001 0010 0011 0100 / 0101 0110 0111 1000 = 13개
FFFF FFFF = 1111 1111 1111 1111 / 1111 1111 1111 1111 = 32개
*/

#include <stdio.h>
#include <stdint.h>
#include <intrin.h>

int naive_count(uint32_t);
int kernighan_count(uint32_t);
int swar_count(uint32_t);
int built_in_count(uint32_t);

void print_result(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

int main(int argc, char const *argv[])
{
    uint32_t input[4] = {0x00000000, 0x00000007, 0x12345678, 0xFFFFFFFF};
    uint32_t r1, r2, r3, r4;

    printf("=== Day 5: Population Count (Counting Set Bits) ===\r\n\n");

    for (int i = 0; i < 4; i++)
    {
        r1 = naive_count(input[i]);
        r2 = kernighan_count(input[i]);
        r3 = swar_count(input[i]);
        r4 = built_in_count(input[i]);
        print_result(i, input[i], r1, r2, r3, r4);
    }

    return 0;
}

int naive_count(uint32_t x)
{
    // 모든 비트를 검사
    int count = 0;
    for (int i = 0; i < 32; i++)
        if (x & (1U << i))
            count++;

    return count;
}

int kernighan_count(uint32_t x)
{
    // 1 인 비트 하나를 지울 때마다 카운트
    int count = 0;
    while (x)
    {
        x &= (x - 1);
        count++;

        // x - 1을 할 때 가장 오른쪽 1이 0으로 바뀌고, 그 오른쪽에 있던 0들은 전부 1로 바뀐다.
        // 10110100
        // -      1
        // --------
        // 10110011

        // AND 하면 결국 가장 오른쪽 1 하나만 제거된다.
        //     10110100
        // AND 10110011
        // ------------
        //     10110000

        // 10110100  → 10110000   count = 1
        // 10110000  → 10100000   count = 2
        // 10100000  → 10000000   count = 3
        // 10000000  → 00000000   count = 4
        // x가 0이되면 끝난다.
    }
    // 반복문때문에 Kernighan = 1이 적을 때 유리

    return count;
}

int swar_count(uint32_t x)
{
    // SWAR(SIMD Within A Register), SIMD(Single Instruction, Multiple Data)
    // 비트들을 여러 그룹으로 나눠서 병렬적으로 합산하는 방식

    // 1단계: 2비트씩 그룹지어 1 개수 합산
    x = x - ((x >> 1) & 0x55555555); // 5 = 0101
    // 11(3)-1=2, 10(2)-1=1, 01(1)-0=1 하여 오른쪽 비트로 합산 후,
    // 0101 마스킹하여 합산 개수만 가져옴

    // 2단계: 4비트씩 그룹지어 1 개수 합산
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333); // 3 = 0011
    // 0X0Y ->  000Y + 000X = 000 X+Y (위에서 합산된 X,Y를 같은 자리로 모아 합산)

    // 3단계: 8비트씩 그룹지어 1 개수 합산
    x = (x + (x >> 4)) & 0x0F0F0F0F; // F = 1111
    // 000X 000Y : 000 X+Y (위에서 합산된 X,Y를 같은자리로 모아 합산)

    // 마지막 단계: 8비트(1바이트)의 값들을 합산
    return x % 255; // 255 = 0xFF, 2^8 = 256
    // ( a * 256^3 + b * 256^2 + c * 256^1 + d * 256^0 + e ) % 255 = a+b+c+d+e
    // 왜냐하면, 256^n % 255 = 1
    // 왜냐하면, (256 × 256) mod 255
    // = ((256 mod 255) × (256 mod 255)) mod 255
    // = (1 × 1) mod 255 = 1 

    // 반복문이 없어 1이 몇 개든 거의 일정한 연산량
}

int built_in_count(uint32_t x)
{
    // CPU/컴파일러가 제공하는 내장 함수를 사용
    int count = __popcnt(x); // MSVC 계열

    return count;
}

void print_result(int i, uint32_t x, uint32_t r1, uint32_t r2, uint32_t r3, uint32_t r4)
{
    printf("Case %d: Input 0x%08X\r\n", i+1, x);
    printf("  [Naive]     : %d\r\n", r1);
    printf("  [Kernighan] : %d (Recommended Logic)\r\n", r2);
    printf("  [SWAR]      : %d (Strict Loop-free)\r\n", r3);
    printf("  [Built-in]  : %d\r\n", r4);
    printf("------------------------------\r\n");
}