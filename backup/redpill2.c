/*
260807 Fri
Day 2. Endianness 변환 함수 (Network to Host) (Byte Order)
입력: 32비트 정수 0x12345678 (Big Endian 가정 데이터)
출력: 실행 시스템의 Endian에 맞춰 변환된 값
제약조건: 시스템의 Endian을 런타임에 판별하여 동작할 것. 비트 연산만 사용.

실행결과: 
=== Day 2: Endianness Conversion ===
Received Data (Hex): 0x12345678

[System Check] This system is Little Endian.
 -> Need to swap bytes to match Host Order.

Original (Network): 0x12345678
Converted (Host)  : 0x78563412
Memory Dump: [12] [34] [56] [78] (Low Addr -> High Addr)

big endian : 그대로 저장, 전송시, FS 저장시, 몇몇 옛날컴들
little endian : 거꾸로 저장(작은것부터) x86, arm
*/