/*
Day 3. 팩맨 (Packed Data) 파싱
입력: 16비트 정수 (RGB565 포맷: Red 5bit, Green 6bit, Blue 5bit)
출력: R, G, B 각각의 8비트 확장 값 (0~255)
제약조건: 비트 마스킹과 쉬프트 연산 사용.
실행결과:
=== Day 3: Packed Data Parsing (RGB565) ===

Input: 0xFFFF
  [Raw Value] R: 31 (0x1F), G: 63 (0x3F), B: 31 (0x1F)
  [8-bit Ext] R: 248,      G: 252,      B: 248
--------------------------------------------------
Input: 0xF800
  [Raw Value] R: 31 (0x1F), G:  0 (0x00), B:  0 (0x00)
  [8-bit Ext] R: 248,      G:   0,      B:   0
--------------------------------------------------
Input: 0x07E0
  [Raw Value] R:  0 (0x00), G: 63 (0x3F), B:  0 (0x00)
  [8-bit Ext] R:   0,      G: 252,      B:   0
--------------------------------------------------
Input: 0x1234
  [Raw Value] R:  2 (0x02), G: 17 (0x11), B: 20 (0x14)
  [8-bit Ext] R:  16,      G:  68,      B: 160
--------------------------------------------------
*/

#include <stdio.h>
#include <stdint.h>

// rgb565 - 5 6 5 16bit
#define MASK_RED 0xF800   // 1111 1000 0000 0000
#define MASK_GREEN 0x07E0 // 0000 0111 1110 0000
#define MASK_BLUE 0x001F  // 0000 0000 0001 1111

void parse_rgb565(uint16_t pixel)
{
    // 16비트를 5,6,5비트로 쪼갬
    uint8_t r_raw = (pixel & MASK_RED) >> 11; // 1111 1000 0000 0000 -> 0001 1111
    uint8_t g_raw = (pixel & MASK_GREEN) >> 5;
    uint8_t b_raw = (pixel & MASK_BLUE);

    // 8비트로 만듬
    uint8_t r8 = (r_raw << 3); // 0001 1111 -> 1111 1000
    uint8_t g8 = (g_raw << 2); // 0011 1111 -> 1111 1100
    uint8_t b8 = (b_raw << 3); // 0001 1111 -> 1111 1000

    printf("Input: 0x%04X\r\n", pixel);
    printf("[Raw Value] R: %2d (0x%02X), G: %2d (0x%02X), B: %2d (0x%02X)\r\n",
           r_raw, r_raw, g_raw, g_raw, b_raw, b_raw);
    printf("[8-bit Ext] R: %3d,      G: %3d,      B: %3d\r\n", r8, g8, b8);
    printf("--------------------------------------------------");
}

int main(int argc, char const *argv[])
{
    printf("=== Day 3: Packed Data Parsing (RGB565) ===");
    parse_rgb565(0xFFFF);
    parse_rgb565(0xF800);
    parse_rgb565(0x07E0);
    parse_rgb565(0x1234);

    return 0;
}
