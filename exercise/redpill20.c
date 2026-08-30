/*

- **Day 20. 희소 행렬(Sparse Matrix) 압축**
    - **입력:** 0이 대부분인 2차원 배열
    - **출력:** (Row, Col, Value) 구조체 배열로 변환된 데이터
    - **제약조건:** 메모리 사용량 비교 출력.
    - **실행결과:**
    
    ```c
    === Day 20: Sparse Matrix Compression ===
    
    --- Compressed Data (Row, Col, Val) ---
    Index 0: (0, 1, 5)
    Index 1: (2, 3, 8)
    Index 2: (4, 0, 2)
    Index 3: (4, 3, 9)
    
    [Memory Usage Analysis]
    Original Matrix Size : 400 bytes (100 x 4 ints)
    Compressed Data Size : 48 bytes (4 elements x3 x 4 bytes)
    >> Compression Ratio : 12.0% of original size
    ```
    
    !image.png
    
    Day20

*/

/*

대부분의 값이 0인 행렬을 **희소 행렬(Sparse Matrix)**이라고 해.
반대로 값이 대부분 채워져 있으면 밀집 행렬(Dense Matrix)이라고 해.

"압축"은 0은 굳이 저장하지 말고, 값이 존재하는 위치만 저장하자는 거야.
즉, "2차원 배열에서 0이 아닌 값만 (행, 열, 값)으로 기록한다.

*/


#include <stdio.h>

#define ROWS 100
#define COLS 4
#define NON_ZERO_COUNT 4

typedef struct _MatrixElement
{
    int Row;
    int Col;
    int Value;
} MatrixElement;

int main(void)
{
    int matrix[ROWS][COLS] = {0};

    matrix[0][1] = 5;
    matrix[2][3] = 8;
    matrix[4][0] = 2;
    matrix[4][3] = 9;

    MatrixElement compressed[NON_ZERO_COUNT];

    int count = 0;

    /* 0이 아닌 값만 압축 배열에 저장 */
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (matrix[row][col] != 0)
            {
                compressed[count].Row = row;
                compressed[count].Col = col;
                compressed[count].Value = matrix[row][col];

                count++;
            }
        }
    }

    printf("=== Day 20: Sparse Matrix Compression ===\n\n");

    printf("--- Compressed Data (Row, Col, Val) ---\n");

    for (int i = 0; i < count; i++)
    {
        printf("Index %d: (%d, %d, %d)\n",
               i,
               compressed[i].Row,
               compressed[i].Col,
               compressed[i].Value);
    }

    /* 메모리 크기 */
    size_t original_size = sizeof(matrix);
    size_t compressed_size = count * sizeof(MatrixElement);

    /* 압축률 */
    double ratio =
        (double)compressed_size / original_size * 100.0;

    printf("\n[Memory Usage Analysis]\n");

    printf("Original Matrix Size : %zu bytes (%d x %d ints)\n",
           original_size, ROWS, COLS);

    printf("Compressed Data Size : %zu bytes (%d elements x3 x %zu bytes)\n",
           compressed_size, count, sizeof(int));

    printf(">> Compression Ratio : %.1f%% of original size\n",
           ratio);

    return 0;
}
