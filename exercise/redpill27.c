/*

- **Day 27. CRC-32 구현**
    - **입력:** 바이트 배열
    - **출력:** 32비트 CRC 체크섬
    - **제약조건:** 비트 단위 계산 방식 구현 후, 테이블 기반 방식으로 최적화 비교.
    - **실행결과:**
    
    ```bash
    === Day 27: CRC-32 Implementation ===
    Input Data: "123456789"
    
    [Bit-wise] CRC: 0xCBF43926
    [Table-based] CRC: 0xCBF43926
    
    >> Verification Success! (Matches Standard)
    ```
    
    Day27
    
*/

/*

CRC(Cyclic Redundancy Check)
데이터를 어떤 다항식으로 나눴을 때 나머지를 checksum으로 붙이고, 받는 쪽에서 다시 나눠서 나머지가 0인지 확인하는 방식
CRC가 일반적인 checksum보다 비트 오류 패턴을 검출하는 데 더 강력한 경우가 많습니다.

CRC에서는 **Generator(생성 다항식)**를 하나 정합니다.
예를 들어:
1101을 사용한다고 해봅시다.
이걸 다항식으로 표현하면:
x³ + x² + 1 입니다.

데이터가 1011001이라고 해봅시다.
Generator의 길이가 4이므로 CRC는 3비트가 필요합니다.

1101은 4비트이고, 이에 대응하는 다항식의 최고 차수는 3입니다.
1101
 ↓
x³ + x² + 1
그래서 CRC의 최대 크기는 3비트가 됩니다.
따라서 데이터 뒤에 CRC자리로 0을 3개 붙입니다.
CRC = 1011001000

그 후 1101xxx만큼 0패딩해서 xor을 하고 앞에 0을 버리면서 xor을 반복해서 3자리 CRC가 나온다.

실제 CRC-32에서는 32비트 CRC가 나오도록 차수가 32인 Polynomial을 사용합니다.

*/


#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define CRC32_POLYNOMIAL 0xEDB88320

/*
 * ============================================================
 * 1. Bit-wise CRC-32
 * ============================================================
 */
uint32_t crc32_bitwise(const uint8_t *data, size_t length)
{
    uint32_t crc = 0xFFFFFFFF;

    for (size_t i = 0; i < length; i++)
    {
        crc ^= data[i];

        for (int bit = 0; bit < 8; bit++)
        {
            if (crc & 1)
                crc = (crc >> 1) ^ CRC32_POLYNOMIAL;
            else
                crc >>= 1;
        }
    }

    return crc ^ 0xFFFFFFFF;
}


/*
 * ============================================================
 * 2. Table-based CRC-32
 * ============================================================
 */
uint32_t crc_table[256];

/*
 * CRC 테이블 생성
 */
void crc32_init_table(void)
{
    for (int i = 0; i < 256; i++)
    {
        uint32_t crc = i;

        for (int bit = 0; bit < 8; bit++)
        {
            if (crc & 1)
                crc = (crc >> 1) ^ CRC32_POLYNOMIAL;
            else
                crc >>= 1;
        }

        crc_table[i] = crc;
    }
}


/*
 * 테이블을 이용한 CRC-32 계산
 */
uint32_t crc32_table_based(const uint8_t *data, size_t length)
{
    uint32_t crc = 0xFFFFFFFF;

    for (size_t i = 0; i < length; i++)
    {
        uint8_t index = (uint8_t)(crc ^ data[i]);

        crc = (crc >> 8) ^ crc_table[index];
    }

    return crc ^ 0xFFFFFFFF;
}


/*
 * ============================================================
 * Main
 * ============================================================
 */
int main(void)
{
    const char *input = "123456789";

    printf("=== Day 27: CRC-32 Implementation ===\n");
    printf("Input Data: \"%s\"\n\n", input);

    /*
     * Bit-wise 방식
     */
    uint32_t crc_bitwise =
        crc32_bitwise((const uint8_t *)input, strlen(input));

    /*
     * Table 생성
     */
    crc32_init_table();

    /*
     * Table-based 방식
     */
    uint32_t crc_table_result =
        crc32_table_based((const uint8_t *)input, strlen(input));

    printf("[Bit-wise] CRC: 0x%08X\n", crc_bitwise);
    printf("[Table-based] CRC: 0x%08X\n\n", crc_table_result);

    /*
     * 결과 비교
     */
    if (crc_bitwise == crc_table_result &&
        crc_bitwise == 0xCBF43926)
    {
        printf(">> Verification Success! (Matches Standard)\n");
    }
    else
    {
        printf(">> Verification Failed!\n");
    }

    return 0;
}
