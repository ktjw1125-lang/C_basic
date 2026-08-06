#include <stdio.h>

// void swap(int a, int b)
// {
//     int temp = a;
//     a = b;
//     b = temp;
// }

// void swap(int *a, int *b)   // 주소를 받음
// {
//     // int *temp = a;   // 주소를 넘겨줌
//     // unsigned long long s = sizeof(a);   // 주소변수 8바이트
//     // s = sizeof(*a)   // 역참조하여 값은 int이므로 4바이트

//     int temp = *a;   // 역참조 (값 가져오기)
//     *a = *b;
//     *b = temp;
// }

// void swap(void *a, void *b, int data_t)   // void로 가져옴, data_t을 지정할때
void swap(void *a, void *b)   // void로 가져옴, data_t을 지정할때
{
    // unsigned long long s = sizeof(a);
    // unsigned long long s = sizeof(*(char*)a);
    // printf("%c", *(char*)a);
    // char temp = (char*)a;   // 주소의 실제값을 char로 해석하겠다
    int temp = *(int*)a;   // 주소의 실제값을 char로 해석하겠다
    *(int*)a = *(int*)b;
    *(int*)b = temp;
}

int main(int argc, char const *argv[])
{
    int a = 1, b = 2;

    // swap(a, b);
    swap(&a, &b);   // 주소를 가리킴

    printf("a: %d, b: %d", a, b);
    return 0;
}