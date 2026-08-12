#include <stdio.h>
#include <stdint.h>

// 매크로 (컴파일 전 쓰인곳 가서 싹 치환함) (함수와 다르게 오버헤드없음) (에러잡기힘듬)
#define BIT_SET(var, pos) ((var) |= (1UL << (pos))) // 람다식같은거; var = var | 1ul
// 1UL = 0000 0001 (unsigned long) (long은 8바이트)
// var | 1UL 는 결국 마지막 비트 켜란 뜻 (마스킹이라고 함)
// 비트의 원하는 위치를 1로 켤때

#define BIT_CLEAR(var, pos) ((var) &= ~(1UL << (pos)))
// pos 위치를 0으로 끌때
// 둘다 1이어야하는데 강제로 0이니까 and하면 무조건 0

#define BIT_TOGGLE(var, pos) ((var) ^= (1UL << (pos)))
// 비트반전
// exclusive or

#define BIT_CHECK(var, pos) (!!((var) & (1UL << (pos))))
// 비트확인
// !! : 0이 아니면 1로 비트화

int main(int argc, char const *argv[])
{
    uint32_t data = 0x12345678; // 32비트이므로 8바이트짜리 (16진수 8자리)
    // BIT_SET(data, 0);
    BIT_TOGGLE(data, 0);
    BIT_TOGGLE(data, 3);
    int bit_status = BIT_CHECK(data,3);

    return 0;
}
