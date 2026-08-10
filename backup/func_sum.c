#include <stdio.h>
#include <time.h>

extern int input; // 다른파일에서 보이게 됨, 주소는 모름, 링크시 결정

// int sum(int n)
// {
//     if (n == 0)
//         return 0; // 재귀함수 마지막은 0만 return, 더이상 재귀없음
//     return n + sum(n - 1);
// }

// long long sum(int n)
// {
//     long long result = 0;
//     for (size_t i = 1; i <= n; i++)
//     {
//         result += i;
//     }

//     return result;
// }

// long long sum(long long num)
// {

//     return (long long)((num) * (num - 1)) / 2;
// }

long long sum(int n)
{
    long long result = 0;

    int i = 0;

    // while (i <= n)
    // {
    //     result = result + i;
    //     i++; // while문에 꼭 필요
    // }

    while (1)
    {
        result = result + i;
        i++;
        if (i <= n)
            break;
    }

    return result;
}

int main(int argc, char const *argv[])
{
    clock_t start, end;
    start = clock();

    static int input; // static 쓰면 stack에 쌓이는게 아니라 전역변수처럼 영구저장됨, 하지만 다른데서 쓸순없음, 함수 다시들어오면 다시쓸수있음
    // printf("정수를 입력하시오 : ");
    // scanf("%d", &input);
    input = 1000000000000;

    long long result = sum(input);
    // printf("%d", result);
    printf("%I64d\n", result);

    end = clock();
    double taken_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time taken : %.20f", taken_time);

    return 0;
}
