#include <stdio.h>

void input_nums(int *lotto);
void print_nums(int *lotto);

int main(int argc, char const *argv[])
{
    int lotto_nums[6];
    input_nums(lotto_nums); // lotto_nums는 배열의 첫 주소를 저장하고 있음
    // printf("%d", lotto_nums);
    print_nums(lotto_nums);
    return 0;
}

void input_nums(int *lotto)
{
    int num;
    int a;
    for (int i = 0; i < 6; i++)
    {
        printf("번호 입력[%d] : ", i + 1);
        scanf("%d", &num);
        a = 0;

        for (int j = 0; j < i; j++)
        {
            if (num == lotto[j])
            {
                a = 1;
                break;
            }
        }

        if (!a)
        {
            lotto[i] = num;
        }
        else
        {
            printf("같은 번호가 있습니다.\n");
            i--;
        }
    }
}

void print_nums(int *lotto)
{
    printf("\n로또번호 : ");
    for (int i = 0; i < 6; i++)
    {
        printf(" %d", lotto[i]);
    }
}
