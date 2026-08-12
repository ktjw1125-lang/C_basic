#include <stdio.h>  // <>는 시스템폴더에서 찾음

#include "include/hello.h"
// header : declaration
// int y(int x);   // 자리만 만들어놓음

int x = 0;   // global variable

int main(int a, int b){
    int c=100;
    char d='a';
    char e[]="abcde";   // 문자열 배열로 넣어야됨, \0 넣어야 글자끝 알려줌(메모리)
    float f = 1.0;   // float 16비트~
    double g = 1.0;   // double : float의 두배 비트 

    printf("\nHello World\n\n");

    printf("result : %d\n\n", y(2));

    return 0;
}

int y(int x){
    return x*2;
}