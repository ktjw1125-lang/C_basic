#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    int count;
    printf("정수 입력해주세요 : ");
    scanf("%d", &count);
    printf("prime number : ");
    printf("2 ");

    clock_t s,e;
    // time_t s,e;

    // time(&s);
    s = clock();
    // 소수 구하기 (prime number)
    for (int i = 3; i < count+1; i += 2)   // 3부터시작, 짝수 건너뜀.. 짝수들은 이미 소수가 아님
    {
        int pn = 1; // for문에서만 사용되는 지역변수
        for (int j = 3; j * j < i; j += 2)   // 마찬가지
        {
            if (i % j == 0)
            {
                pn = 0;
                break;
            }
        }

        if (pn)
            printf(" %d ", i);
            pn = 1;
        
    }
    // time(&e);
    e = clock();
    // double elapsed = (double)(e - s) / CLOCKS_PER_SEC;

    printf("\r\ncount : %d", count);
    // printf("\ntime : %d", e-s);    
    printf("\ntime : %f초", (double)(e - s) / CLOCKS_PER_SEC);    
    
    return 0;
}