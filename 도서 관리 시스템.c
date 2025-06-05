#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 오래된 코드 경고성 메시지 무시하는 함수
#define _CRT_SECURE_NO_WARNINGS

// 구조체 정의
typedef struct Book {
	char title[100];    // 캐릭터(char) title에 대한 100개의 배열
	char author[50];    // 캐릭터(char) author에 대한 50개의 배열
	int year;			// year 정수형으로 몇 년인지
	struct Book* next;  
}Book;


// 책 추가
void addBook(Book** head, const char* title, const char* author, int year) {
	Book* newBook = (Book*)malloc(sizeof(Book));
	
	// 만약 newBook이 메모리 할당을 받지 못하면, (newBook == NULL)은 만약 값이 없다면.
	// 메모리 할당 실패라고 출력을 해라.
	if (newBook == NULL) {
		printf("메모리 할당 실패\n");
		return;
	}

	/*
	(*포인터).멤버    =  일반적인 구조체 접근 방식   ex) (*newBook).title
	포인터 -> 멤버    =  위의 표현을 간단하게 줄인 것.
	*/
	strcpy_s(newBook->title, sizeof(newBook->title), title);
	strcpy_s(newBook->author, sizeof(newBook->author), author);
	
	// strcpy는 오랜된 함수는 보안상 위험하기 때문에. strcpy_s로 변환
	
	// ex)
	// strcpy(newBook->title, title); --> strcpy_s(newBooki->title, sizeof(newBook->title), title);
	newBook->year = year;
	
	// newBook->year = NULL;

	if (*head == NULL) {   // head는 이중 포인터이다. (Book** head)
		*head = newBook;   // 리스트의 시작 주소를 가리키는 포인터를 함수 인자로 전달받음.
	}					   // *head는 연결 리스트의 시작 노드(Book)를 의미한다.	

	/* 즉, 리스트가 비어있으면(head가 NULL이면), 새로 만든 노드를 첫 노드로 설정하라.*/


	else {
		Book* current = *head;      // Book* current를 head로 초기화 
		while (current->next != NULL) {   // current가 가르키는 노드 next 가 NULL이 아닐때 까지 반복.
			current = current->next;      // 다음 노드로 이동하는 코드
		}								  // 위 두 줄이 지나면 current가 마지막 노드가 됨
		current->next = newBook;		//  마지막 노드의 next에 새로 만든 노드 연결
	}
	/* 이로써 새 노드는 리스트이 맨 끝에 붙는다.*/
}

// 책 목록 출력
void printBooks(Book* head) {     // Book 구조체 포인터한 후 head, 시작 노드를 가르키는 포인터
	printf("\n[ 도서 목록 ]\n");

	if (head == NULL) {
		printf("등록된 도서가 없습니다.\n");
		return;
	}
	while (head != NULL) {  // head가 NULL일 때 까지 while사용.
		printf("제목 : %s | 저자 : %s | 출판년도 : %d\n", head->title, head->author, head->year);
		
		head = head->next;  // 루프마다 head를 다음 노드로 옮김.
							// 연결 리스트 핵심 다음을 따라가면서 순회
	}
}

// 책 삭제 
void deleteBook(Book** head, const char* title) {
	Book* current = *head;
	Book* prev = NULL;

	while (current != NULL) {
		if (strcmp(current->title, title) == 0) {
			if (prev == NULL) {
				*head = current->next;
			}
			else {
				prev->next = current->next;
			}
			free(current);     //current 메모리 해제
			printf("'%s' 도서 삭제 완료.\n", title);
			return;
		}
		prev = current;
		current = current->next;
	}
	printf("'%s' 도서를 찾을 수 없습니다.\n", title);
}

// 메모리 해제
void freeAllBooks(Book** head) {
	Book* current = *head;
	Book* temp;

	while (current != NULL) {
		temp = current;
		current = current->next; // current->next;로 다음으로 넘겨줌.
		free(temp);
	}
	*head = NULL;
}

int main() {
	Book* head = NULL; // 도서 리스트의 시작 노드를 가리키는 포인터 
	// (아무 노드가 없으면 NULL)
	
	/* 사용자 입력을 받을 변수들*/
	int choice;
	char title[100], author[50];
	int year;    

	// while 1은 TRUE를 말함 무한 루프를 도는 것.
	while (1) {
		printf("\n[메뉴] 1. 도서 추가 2.목록 출력 3.삭제 4.종료\n 선택 : "); // 설명해주는 문장들.
		if (scanf_s("%d", &choice) != 1) {
			printf("숫자를 입력하세요.\n");
			while (getchar() != '\n');  // 잘못된 입력 버퍼 비우기
			continue;  // continue로 다시 반환.
		}
		while (getchar() != '\n'); // 개행 문자 제거
		/* scanf_s()로 숫자 아닌 걸 입력하면 무한 루프 빠지는 문제를 예방하는 것.*/
		/* getchar()로 버퍼에 남은 \n 제거하는 것*/

		// scanf("%d", &choice);
		// getchar();

		switch (choice) {   //choice 사용자가 버튼을 골랐을 때 어떻게 1, 2, 3, 4번중에 선택을 때의 문장들.

		// 1번 도서 추가
		case 1:
			printf("제목 입력 : ");
			fgets(title, sizeof(title), stdin);   // fgets로 제목 입력

			title[strcspn(title, "\n")] = '\0'; // strcspn(..., "\n")으로 문자열 끝에 붙는 \n제거
			// fegts는 자동으로 \n을 넣기  때문에

			printf("저자 입력 : ");
			fgets(author, sizeof(author), stdin); //fgets로 저자 입력

			author[strcspn(author, "\n")] = '\0'; // strcspn(..., "\n")으로 문자열 끝에 붙는 \n 제거

			printf("출판년도 입력 : ");
			if (scanf_s("%d", &year) != 1) {     // 출판년도를 숫자가 아닌 다른 수가 들어오지  않게 만드는 것.
				printf("출판년도는 숫자입니다. \n"); // scanf를 통해 숫자인지 구별. scanf("%d"를 ,year값을 가져와 숫자인지 구별하는 것.
				while (getchar() != '\n');    // while getchar() ! = \n
				break;
			}
//			scanf("%d", &year);
//			getchar();

			addBook(&head, title, author, year); //Book**로 head를 전달 -> 리스트에 실제로 노드 추가 기능.
			break;

		case 2:
			printBooks(head);   // 1번에서 도서 입력했던 것들을 보여줌
			break;
			/* 연결 리스트 순회하며 모든 책 출력.*/

		case 3:
			printf("삭제할 책 제목 : ");  // 문장 출력 문.
			fgets(title, sizeof(title), stdin); // scanf("%s", title을 쓰면, 공백 있는 문자를 얻기 쉽지않음.
												// 그리하여, fgets는 공백 포함 문자열을 안전하게 받을 수 있음.
												// sizefof(title)은 버퍼 크기 (100), stdin은 표준입력장치(키보드 의미)
			/* 키보드로 입력 받는 title 제목 크기는 title(100)자리는 부여 받음.*/
			title[strcspn(title, "\n")] = '\0'; // fgets()는 문자열 끝에 개행 문자(\n)를 자동으로 포함. 이를 제거
												// strcspn(title, "\n")은 title 문자열에서 \n이 처음 나타나는 위치를 알려줌.
												// 해당 위치에 '\0'을 넣으면, 문자열 종료가 되면서 \n이 제거됩니다.
			/*
			입력 전 : "C Programming\n"
			입력 후 : "C Programming"
			*/
			deleteBook(&head, title); // 연결 리스트에서 title과 같은 제목을 가진 노드를 삭제하는 함수,
									 // &head를 넘기는 이유는 삭제 대상이 첫 번째 노드이면 안되기 때문
									//첫 번째 노드를 삭제시키면 head자체를 바꿔야 하므로 이중 포인터를 
									// 넘긴다. 내부적으로는 strcmp(current->title, title)로 비교해서 일치하면
									// 삭제한다.
			break;

		case 4:
			freeAllBooks(&head); // 동적할당이된 모든 메모리를 해제 후 정상 종료함.
			head = NULL; 
			return 0;

		default :
			printf("잘못된 선택입니다.\n");
		}
	}
}
