/*
- **Day 7. Checksum 계산 (XOR 방식)**
    - **입력:** 바이트 배열 `[0x01, 0x02, 0x03, 0x04]`, 길이
    - **출력:** XOR 누적 체크섬 값
    - **제약조건:** 포인터 연산 사용.
    - **실행결과:**

    ```c
    === Day 7: XOR Checksum Calculation ===

    [TX] Sending Packet...
         Data: 0x01 0x04 0x10 0x20 0x30 0x40
         Calculated Checksum: 0x04

    [RX] Receiving Normal Packet...
         >> Verification SUCCESS (Result: 0x00)

    [RX] Receiving Corrupted Packet (Noise injected)...
         Corrupted Data: 0x01 0x04 0xEF 0x20 0x30 0x40 0x04
         >> Verification FAIL (Result: 0xFF)
         >> Error detected! Discarding packet.
    ```

    01 ^ 02 ^ 03 ^ 04 = checksum
    XOR는 데이터의 "변경 여부를 빠르고 간단하게 감지하기 위한 체크섬을 만들기 좋아서" 사용하는 거야.

    다만 중요한 점은 XOR 체크섬이 모든 오류를 잡아내는 건 아니야.
    여러 바이트가 특정 방식으로 동시에 바뀌면 같은 체크섬이 나올 수도 있어.
    그래서 실제 통신에서는 더 강력한 CRC 같은 것도 많이 사용해.

    마지막에 체크섬 추가하여 전송
    받은 데이터 + 받은 체크섬까지 전부 XOR = 0x00
*/

#include <stdint.h>

uint8_t xor_sum(uint8_t *data, int len);
void print_result(uint8_t *data, int len, uint8_t verifying);

int main(int argc, char const *argv[])
{
    // Data prep
    uint8_t data[6 + 1] = {0x01, 0x04, 0x10, 0x20, 0x30, 0x40, 0x00}; // 6 data + 1 checksum
    int len = sizeof(data) / sizeof(data[0]);

    // check_sum 값 구하기
    uint8_t check_sum = xor_sum(data, len - 1);
    data[len - 1] = check_sum; // checksum 값을 data 끝에 추가

    printf("=== Day 7: XOR Checksum Calculation ===\r\n\n");

    // Tx
    printf("[TX] Sending Packet...\r\n");
    printf("     Data: ");
    for (int i = 0; i < len; i++)
        printf("0x%02X ", data[i]);
    printf("\n");
    printf("     Calculated Checksum: 0x%02X\r\n\n", check_sum);

    // Rx
    uint8_t verifying = xor_sum(data, len);
    print_result(data, len, verifying);

    data[3] = 0xFF; // corrupting data ...

    // Rx2
    verifying = xor_sum(data, len);
    print_result(data, len, verifying);

    return 0;
}

uint8_t xor_sum(uint8_t *data, int len)
{
    // 데이터 포인터로 받아서, 개수만큼 차례대로 XOR 함
    uint8_t check_sum = 0x0;

    for (int i = 0; i < len; i++)
    {
        check_sum ^= *(data + i); // data[i] 와 같음
    }

    return check_sum;
}

void print_result(uint8_t *data, int len, uint8_t verifying)
{
    if (verifying == 0x00)
    {
        printf("[RX] Receiving Normal Packet...\r\n");
        printf("     >> Verification SUCCESS (Result: 0x%02X)\r\n\n", verifying);
    }
    else
    {
        printf("[RX] Receiving Corrupted Packet (Noise injected)...\r\n");
        printf("     Corrupted Data: ");

        for (int i = 0; i < len; i++)
        {
            printf("0x%02X ", data[i]);
        }

        printf("\r\n");
        printf("     >> Verification FAIL (Result: 0x%02X)\r\n", verifying);
        printf("     >> Error detected! Discarding packet.\r\n");
    }
}