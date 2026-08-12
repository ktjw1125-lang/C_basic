// // 함수 포인터
// #define _CRT_SECURE_NO_WARNINGS
// #include <stdio.h>

// void func(int (*fp)(int, int));      // 함수 포인터를 매개변수로 갖는 함수
// int sum(int a, int b);               // 두 정수를 더하는 함수
// int mul(int a, int b);               // 두 정수를 곱하는 함수
// int max(int a, int b);               // 두 정수 중에 큰 값을 구하는 함수

// int main(void)
// {
// 	int sel;                         // 선택된 메뉴 번호를 저장할 변수

// 	printf("01 두 정수의 합\n");     // 메뉴 출력
// 	printf("02 두 정수의 곱\n");
// 	printf("03 두 정수 중에서 큰 값 계산\n");
// 	printf("원하는 연산을 선택하세요 : ");
// 	scanf("%d", &sel);               // 메뉴 번호 입력

// 	switch (sel)
// 	{
// 		case 1: func(sum); break;        // 1이면 func에 덧셈 기능 추가
// 		case 2: func(mul); break;        // 2이면 func에 곱셈 기능 추가
// 		case 3: func(max); break;        // 3이면 func에 큰 값 구하는 기능 추가
// 	}

// 	return 0;
// }

// void func(int (*fp)(int, int))
// {
// 	int a, b;                        // 두 정수를 저장할 변수
// 	int res;                         // 함수의 반환값을 저장할 변수

// 	printf("두 정수의 값을 입력하세요 : ");
// 	scanf("%d%d", &a, &b);           // 두 정수 입력
// 	res = fp(a, b);                  // 함수 포인터로 가리키는 함수를 호출
// 	printf("결과값은 : %d\n", res);  // 반환값 출력
// }

// int sum(int a, int b)        // 덧셈 함수
// {
// 	return (a + b);
// }

// int mul(int a, int b)        // 곱셈 함수
// {
// 	return (a * b);
// }

// int max(int a, int b)        // 큰 값을 구하는 함수
// {
// 	if (a > b) return a;
// 	else return b;
// 	}

// // void포인터
// #include <stdio.h>

// int main(void)
// {
//     int a = 10;                           // int형 변수
//     double b = 3.5;                       // double형 변수
//     void* vp;                             // void 포인터

//     vp = &a;                              // int형 변수의 주소 저장
//     printf("a : %d\n", *(int*)vp);

//     vp = &b;                              // double형 변수의 주소 저장
//     printf("b : %.1lf\n", *(double*)vp);
// //printf("b : %.1lf\n", *vp);           // 잘못된 표현(data type을 변경해야 한다!)
//     return 0;
// }





// 구조체
// #include <stdio.h>

// #pragma pack(1) // 컴파일러가 cpu에 따른 패딩 못하게함

// typedef struct _student // 구조체 선언
// {
//     char name[10]; // 3바이트 패딩 들어감
//     int num;       // int형 멤버
//     double grade;  // double형 멤버
// } student;         // 세미콜론 사용

// // struct student           // 구조체 선언
// // {
// // 	char name[10];
// // 	int num;             // int형 멤버
// // 	double grade;        // double형 멤버
// // };

// int main(void)
// {
//     // struct student s1;   // struct student형의 변수 선언
//     student s1;

//     int s = sizeof(s1);

//     s1.name[0] = 'a';
//     s1.name[1] = 'n';
//     s1.num = 2;     // s1의 num 멤버에 2 저장
//     s1.grade = 3.7; // s1의 grade 멤버에 2.7 저장
//     printf("이름 : %s\n", s1.name);
//     printf("학번 : %d\n", s1.num);      // num 멤버 출력
//     printf("학점 : %.1lf\n", s1.grade); // grade 멤버 출력

//     return 0;
// }


// // 함수로 구조체 넘겨주기
// struct vision       // 로봇의 시력을 저장할 구조체
// {
// 	double left;    // 왼쪽 눈
// 	double right;   // 오른쪽 눈
// };

// struct vision exchange(struct vision robot);   // 두 시력을 바꾸는 함수

// int main(void)
// {
// 	struct vision robot;                       // 구조체 변수 선언

// 	printf("시력 입력 : ");
// 	scanf("%lf%lf", &(robot.left), &(robot.right));  // 시력 입력
// 	robot = exchange(robot);                   // 교환 함수 호출
// 	printf("바뀐 시력 : %.1lf %.1lf\n", robot.left, robot.right);

// 	return 0;
// }

// struct vision exchange(struct vision robot)    // 구조체를 반환하는 함수
// {
// 	double temp;                   // 교환을 위한 임시 변수

// 	temp = robot.left;             // 좌우 시력 교환
// 	robot.left = robot.right;
// 	robot.right = temp;

// 	return robot;                  // 구조체 변수 반환
// }

// // 주로 포인터로 struct를 넘긴다.. 크니까




// //  구조체 내부의 구조체
// #include <stdio.h>

// struct profile            // 신상명세 구조체 선언
// {
// 	int age;              // 나이
// 	double height;        // 키
// };

// struct student
// {
// 	struct profile pf;    // profile 구조체를 멤버로 사용
// 	int id;               // 학번을 저장할 멤버
// 	double grade;         // 학점을 저장할 멤버
// };

// int main(void)
// {
// 	struct student yuni;      // student 구조체 변수 선언

// 	yuni.pf.age = 17;         // pf 멤버의 age 멤버에 나이 저장
// 	yuni.pf.height = 164.5;   // pf 멤버의 height 멤버에 키 저장
// 	yuni.id = 315;
// 	yuni.grade = 4.3;

// 	printf("나이 : %d\n", yuni.pf.age);       // pf 멤버의 age 멤버 출력
// 	printf("키 : %.1lf\n", yuni.pf.height);   // pf 멤버의 height 멤버 출력
// 	printf("학번 : %d\n", yuni.id);           // id 멤버 출력
// 	printf("학점 : %.1lf\n", yuni.grade);     // grade 멤버 출력

// 	return 0;
// }



// // 포인터구조체 -> 연산자
// // 구조체 자체      → .
// // 구조체를 가리킴  → ->
// #include <stdio.h>

// struct score		// 구조체 선언
// {
// 	int kor;		// 국어 점수를 저장할 멤버
// 	int eng;		// 영어 점수
// 	int math;		// 수학 점수
// };

// int main(void)
// {
// 	struct score yuni = { 90, 80, 70 };   // 구조체 변수 선언과 초기화
// 	struct score* ps = &yuni;             // 구조체 포인터에 주소 저장

// 	printf("국어 : %d\n", (*ps).kor);     // 구조체 포인터로 멤버 접근
// 	printf("영어 : %d\n", ps->eng);       // -> 연산자 사용 (*ps) 쓰기 싫어서
// 	printf("수학 : %d\n", ps->math);

// 	return 0;
// }



// // 구조체 배열을 처리하는 함수
// #include <stdio.h>

// struct address        // 주소록을 만들 구조체 선언
// {
// 	char name[20];    // 이름을 저장할 멤버
// 	int age;          // 나이를 저장할 멤버
// 	char tel[20];     // 전화번호를 저장할 멤버
// 	char addr[80];    // 주소를 저장할 멤버
// };

// void print_list(struct address* lp);

// int main(void)
// {
// 	struct address list[5] = {        // 요소가 5개인 구조체 배열 선언
// 		{"홍길동", 23, "111 - 1111", "울릉도 독도"},
// 		{"이순신", 35, "222 - 2222", "서울 건천동"},
// 		{"장보고", 19, "333 - 3333", "완도 청해진"},
// 		{"유관순", 15, "444 - 4444", "충남 천안"},
// 		{"안중근", 45, "555 - 5555", "황해도 해주"}
// 	};

// 	print_list(list, 5);

// 	return 0;
// }

// void print_list(struct address* lp, int size)   // 매개변수는 구조체 포인터
// {
// 	int i;                            // 반복 제어 변수

// 	for (i = 0; i < size; i++)           // 배열 요소의 개수 만큼 반복
// 	{
// 		printf("%10s%5d%15s%20s\n",   // 각 배열 요소의 멤버 출력
// 			(lp + i)->name, (lp + i)->age, (lp + i)->tel, (lp + i)->addr);
// 		//lp[i]->name,
// 	}
// }




// // 자기참조 구조체 (linked list)
// // 개별적으로 할당된 구조체 변수들을 포인터로 연결하면 관련된 데이터를 하나로 묶어 관리
// // 리눅스에서 자주 씀
// #include <stdio.h>

// struct list              // 자기 참조 구조체
// {
// 	int num;             // 데이터를 저장하는 멤버
// 	struct list* next;   // 구조체 자신을 가리키는 포인터 멤버
// };

// int main(void)
// {
// 	struct list a = { 10, 0 }, b = { 20, 0 }, c = { 30, 0 };  // 구조체 변수 초기화
// 	struct list* head = &a, * current;                        // 헤드 포인터 초기화

// 	a.next = &b;                        // a의 포인터 멤버가 b를 가리킴
// 	b.next = &c;                        // b의 포인터 멤버가 c를 가리킴

// 	printf("head->num : %d\n", head->num);        // head가 가리키는 a의 num 멤버 사용
// 	printf("head->next->num : %d\n", head->next->num);    // head로 b의 num 멤버 사용

// 	printf("list all : ");
// 	current = head;                     // 최초 current 포인터가 a를 가리킴
// 	while (current != NULL)             // 마지막 구조체 변수까지 출력하면 반복 종료
// 	{
// 		printf("%d  ", current->num);   // current가 가리키는 구조체 변수의 num 출력
// 		current = current->next;        // current가 다음 구조체 변수를 가리키도록 함
// 	}
// 	printf("\n");

// 	return 0;
// }







// 공용체 union
// 네트워크에서 많이씀
// union은 "여러 타입 중 하나를 저장하기 위한 하나의 메모리 공간"





// ### 열거형(enum)
// 번호를 사람이 알아듣기 편하게 이름붙인거

// - 구조체와 비슷하게 선언하나, 열거형은 변수에 저장할 수 있는 정수 값을 기호로 정의하여 나열한다.
// - 17-11.c : 열거형을 사용한 프로그램
    
//     ```c
//     #include <stdio.h>
    
//     enum season { SPRING=10, SUMMER, FALL=20, WINTER };  // 열거형 선언
    
//     int main(void)
//     {
//     	enum season ss;              // 열거형 변수 선언
//     	char* pc = NULL;             // 문자열을 저장할 포인터
    
//     	ss = SPRING;                 // 열거 멤버의 값 대입
//     	switch (ss)                  // 열거 멤버 판단
//     	{
//     		case SPRING:                 // 봄이면
//     			pc = "inline"; break;    // 인라인 문자열 선택
//     		case SUMMER:                 // 여름이면
//     			pc = "swimming"; break;  // 수영 문자열 선택
//     		case FALL:                   // 가을이면
//     			pc = "trip"; break;      // 여행 문자열 선택
//     		case WINTER:                 // 겨울이면
//     		pc = "skiing"; break;    // 스키 문자열 선택
//     	}
//     	printf("나의 레저 활동 = > %s\n", pc);     // 선택된 문자열 출력
    
//     	return 0;
//     }
//     ```
    
// - 열거형 선언 : 예약어 enum과 열거형 이름을 짓고 괄호 안에 멤버를 콤마로 나열
    
//     ```c
//     enum season {SPRING, SUMMER, FALL, WINTER};
//     ```
    
// - 컴파일러는 멤버를 0부터 차례로 하나 씩 큰 정수로 바꾼다.
// - 초기값을 원하는 값으로 다시 설정할 수 있다. 
// - 새로 설정된 멤버 이후의 큰정수로 바뀝니다.
    
//     ```c
//     enum season {SPRING=5, SUMMER, FALL=10, WINTER};
//     ```








// typedef를 사용한 형 재정의