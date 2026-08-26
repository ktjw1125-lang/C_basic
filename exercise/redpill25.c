/*
260826 수

- **Day 25. 이동 평균 필터 (Moving Average)**
    - **입력:** 센서 노이즈 데이터 스트림
    - **출력:** 필터링된 값
    - **제약조건:** 최근 N개의 데이터를 저장하는 윈도우 버퍼 사용, 매번 합계 다시 계산하지 말고 최적화(Sliding Window).
    - **실행결과:**
    
    ```bash
    === Day 25: Moving Average Filter (Sliding Window) ===
    Window Size: 5
    
    Step | Raw Input | Filtered Output
    -----+-----------+----------------
       1 |    20.0   |       20.0  (1개 평균)
       2 |    22.0   |       21.0  (2개 평균)
       3 |    18.0   |       20.0  (3개 평균: 20+22+18 / 3)
       4 |    25.0   |       21.2
       5 |    15.0   |       20.0  (5개 꽉 참)
       6 |    20.0   |       20.0  (20.0이 들어오고, 맨 처음 20.0이 빠짐)
       7 |    21.0   |       19.8  (21.0이 들어오고, 22.0이 빠짐 -> 평균 하락)
       8 |    19.0   |       20.0
       9 |    20.5   |       19.1
      10 |    20.0   |       20.1
    ```
    
    Day25

*/

/*

기존:
[20][22][18][25][15]
 ↑
head

새로운 20 들어옴
 ↓

sum -= 20
sum += 20

[20][22][18][25][20]
 ↑
head 다음 위치로 이동

*/



#include <stdio.h>

#define WINDOW_SIZE 5

typedef struct {
    float buffer[WINDOW_SIZE];
    int head;
    int count;
    float sum;
} SlidingWindow;

float data[] = {
    20.0f, 22.0f, 18.0f, 25.0f, 15.0f,
    20.0f, 21.0f, 19.0f, 20.5f, 20.0f
};

float sliding_mean(SlidingWindow *window, float new_value)
{
    if (window->count < WINDOW_SIZE)
    {
        window->buffer[window->head] = new_value;
        window->sum += new_value;
        window->count++;
    }
    else
    {
        window->sum -= window->buffer[window->head];

        window->buffer[window->head] = new_value;
        window->sum += new_value;
    }

    window->head = (window->head + 1) % WINDOW_SIZE;
    // % WINDOW_SIZE가 링버퍼를 한 바퀴 돌게 해주는 거고
    // 처음 5개는 계속 데이터가 쌓이고 → 5개가 차면 → 가장 오래된 값을 빼면서 새 값을 넣는다.

    return window->sum / window->count;
}

int main(void)
{
    SlidingWindow window = {0};

    int data_count = sizeof(data) / sizeof(data[0]);

    printf("=== Day 25: Moving Average Filter (Sliding Window) ===\n");
    printf("Window Size: %d\n\n", WINDOW_SIZE);

    printf("Step | Raw Input | Filtered Output\n");
    printf("-----+-----------+----------------\n");

    for (int i = 0; i < data_count; i++)
    {
        float filtered = sliding_mean(&window, data[i]);

        printf("%4d | %9.1f | %15.1f\n",
               i + 1,
               data[i],
               filtered);
    }

    return 0;
}
