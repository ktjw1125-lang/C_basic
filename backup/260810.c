#include <stdio.h>
#include <stdlib.h>

void swap(float *x, float *y)
{
    float temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int main(int argc, char const *argv[])
{
    float num[3];
    for (int i = 0; i < 3; i++)
    {
        printf("float(%d) : ", i);
        scanf("%f", &num[i]);
    }

    //  중간값과 최소값, 중간값과 최대값, 최소값과 최대값을 비교해서 swap() 진행
    if (num[0] < num[1])
    {
        swap(&num[0], &num[1]);
    }

    if (num[1] < num[2])
    {
        swap(&num[1], &num[2]);
    }

    if (num[0] < num[1])
    {
        swap(&num[0], &num[1]);
    }

    printf("sorted : ");
    for (int i = 0; i < 3; i++)
    {
        printf("%g ", num[i]);
    }

    return 0;
}
