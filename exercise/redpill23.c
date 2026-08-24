// 260823 일 (추가문제)

/*
- **Day 23. 문자열 토크나이저 (strtok 재구현)**
    - **입력:** "GPS,37.5,127.0", 구분자 ','
    - **출력:** 순차적으로 파싱된 문자열
    - **제약조건:** 내부 정적 변수(`static`)를 사용하여 상태 저장, 원본 문자열 수정 없이 구현해볼 것(선택).
    - **실행결과:**
        
        ```c
        === Day 23: Safe String Tokenizer (static) ===
        
        Input Data: "GPS,37.5665,126.9780,20260213"
        Delimiter : ','
        
        Token 1: GPS
        Token 2: 37.5665
        Token 3: 126.9780
        Token 4: 20260213
        
        >> Original string check: "GPS,37.5665,126.9780,20260213"
        >> (Original string remains unmodified)
        ```
        
    
    Day23
*/

/*
문자열 토크나이저 (strtok) : 문자열을 특정 구분자(delimiter)를 기준으로 잘라서 토큰(token) 단위로 가져오는 함수
char str[] = "hello,world,c";
, 기준으로 나누면:
"hello" → "world" → "c"
이렇게 하나씩 꺼낼 수 있어

#include <stdio.h>
#include <string.h>

int main()
{
    char str[] = "hello,world,c";
    // strtok()은 원본 문자열을 변경해. 그래서 수정 가능한 배열을 사용하는 게 좋아.
    // char *str = "hello,world"; 좋지않음

    char *token = strtok(str, ",");
    // strtok에게 str 문자열을 처음부터 , 기준으로 자를꺼라고 알려줌
    // strtok(str, ",")가 실행되면 첫 번째 ,를 \0으로 바꿔버려.
    // *token은 첫글자를 가리킴

    while (token != NULL) {
        printf("%s\n", token);
        // token 위치부터 \0까지 프린트

        token = strtok(NULL, ",");
        // strtok()이 내부적으로 다음에 어디서부터 찾을지를 기억하고 있어.
        // 처음부터 다시 찾는 게 아니라, 이전에 기억해둔 위치에서 계속 탐색해
        // world 뒤의 ,를 찾아서 또 \0으로 바꾸고 다음 토큰의 시작 주소를 반환
    }

    return 0;
}
*/


#include <stdio.h>

char *my_strtok(const char *str, char delimiter)
{
    // 이전에 어디까지 읽었는지 기억
    static const char *current = NULL;

    // 새로운 문자열이 들어온 경우
    if (str != NULL) {
        current = str;
    }

    // 더 이상 읽을 문자열이 없음
    if (current == NULL || *current == '\0') {
        return NULL;
    }

    // 현재 토큰의 시작 위치
    const char *start = current;

    // delimiter 또는 문자열 끝까지 이동
    while (*current != '\0' && *current != delimiter) {
        current++;
    }

    // delimiter를 만났다면
    if (*current == delimiter) {
        // 다음 호출에서는 delimiter 다음부터 시작
        current++;
    }

    // 원본 문자열을 수정하지 않기 때문에
    // 현재 위치를 그대로 반환할 수 없음
    // → 임시 버퍼에 토큰을 복사
    static char token[128];

    int i = 0;

    while (start < current) {
        // delimiter를 만났다면 제외
        if (*start == delimiter) {
            break;
        }

        token[i++] = *start;
        start++;
    }

    token[i] = '\0';

    return token;
}


int main()
{
    const char data[] = "GPS,37.5665,126.9780,20260213";

    printf("=== Day 23: Safe String Tokenizer (static) ===\n\n");

    printf("Input Data: \"%s\"\n", data);
    printf("Delimiter : ','\n\n");


    char *token;
    int count = 1;

    token = my_strtok(data, ',');

    while (token != NULL) {

        printf("Token %d: %s\n", count, token);

        count++;

        token = my_strtok(NULL, ',');
    }


    printf("\n>> Original string check: \"%s\"\n", data);
    printf(">> (Original string remains unmodified)\n");

    return 0;
}