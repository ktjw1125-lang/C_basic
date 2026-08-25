/*

260825 화

Day 24. 디바운싱 (Debouncing) 알고리즘
입력: 노이즈가 섞인 0/1 입력 배열 (버튼 신호 모사)
출력: 안정화된 출력 값
제약조건: 연속된 N번의 샘플링이 동일할 때만 상태 변경.
실행결과: 
=== Day 24: Button Debouncing Logic ===
Condition: 3 consecutive samples required.

Step | Raw Input | Counter | Output (Stable)
-----+-----------+---------+----------------
   1 |     0     |    0    |       0
   2 |     0     |    0    |       0
   3 |     1     |    1    |       0  <-- 노이즈 발생 (카운트 시작)
   4 |     0     |    0    |       0  <-- 다시 0 복귀 (카운트 리셋!)
   5 |     1     |    1    |       0  <-- 진신호 시작
   6 |     1     |    2    |       0
  >> [State Changed] to 1
   7 |     1     |    0    |       1  <-- 3회 연속 성공으로 상태 변경
   8 |     1     |    0    |       1
   9 |     1     |    0    |       1
  10 |     0     |    1    |       1  <-- 노이즈 무시

*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main(void)
{
    uint8_t sampling_interval = 10; // 샘플간 ms 시간간격
    uint8_t required_count = 3; // 몇개나 일정한지 볼지

    uint16_t raw_input = 0b0010111110; // 데이터
    bool sig = false; // 현재 상태

    int count = 0;

    printf("\n=== Day 24: Button Debouncing Logic ===\n");
    printf("Condition: %d consecutive samples required.\n\n",
           required_count);

    printf("Step | Raw Input | Counter | Output (Stable)\n");
    printf("-----+-----------+---------+----------------\n");

    for (int i = 0; i < 10; i++)
    {
        // 왼쪽(MSB)부터 1비트씩 추출
        int raw = (raw_input >> (9 - i)) & 1;

        if (raw == sig) // 변화가 없을 경우
        {
            count = 0;
        }
        else // 다른 값이 들어온 경우
        {
            count++; // 카운트 시작

            if (count == required_count) // n개까지 일정할 경우
            {
                sig = raw;
                count = 0;

                printf(">> [State Changed] to %d\n", sig);
            }
        }

        printf("%4d | %9d | %7d | %15d\n",
               i + 1,
               raw,
               count,
               sig);
    }

    return 0;
}
