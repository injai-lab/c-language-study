#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 구조체 정의
typedef struct Node {
	char name[50]; // 이름 저장 문자열 
	int score;     // 점수
	struct Node* next; // 다음 노드의 주소를 가리키는 포인터 "연결 리스트의 핵심"
}Node; 

/* 왜 struct Node* next; 처럼 자기 자신을 참조하는가.
연결 리스트는 여러 개의 노드가 연결되어 있는 자료구조.
그래서 한 노드가 다음 노드를 가르키기 위해 struct Node* next를 포함시킨다.
*/

// 노드 추가(리스트 끝에)

// 연결 리스트의 끝에 새 노드를 추가하는 함수
void append(Node** head, const char* name, int score) { // const(상수) char* name
	
	// 새 노드를 위한 메모리 공간을 동적으로 할당
	Node* newNode = (Node*)malloc(sizeof(Node));

	// 메모리 할당 실패 시 처리
	if (newNode == NULL) {
		printf("메모리 할당 실패\n");
		return;
	}

	// 입력된 이름을 새 노드의 name 필드에 복사
	strcpy_s(newNode->name, sizeof(newNode->name), name);

	// 입력된 점수를 새 노드의 score 필드에 저장
	newNode->score = score;

	// 새 노드는 마지막 노드이므로 다음 노드는 NULL로 설정
	newNode->next = NULL;

	// 만약 리스트가 비어 있다면 (즉, 헤드가 NULL로 설정)
	if (*head == NULL) {
		// 헤드가 새 노드를 가리키도록 설정 -> 새 노드가 첫 번째 노드가 됨.
		*head = newNode;
	}
	else {
		// 리스트에 이미 노드가 있으면, 현재 노드를 헤드부터 시작
		Node* current = *head;

		// 마지막 노드까지 이동 (next가 NULL일 때까지 반복)
		while (current->next != NULL) {
			current = current->next;
		}

		// 마지막 노드의 next가 새 노드를 가리키도록 설정 -> 연결 완료
		current->next = newNode;
	}
}

// 연결 리스트의 모든 노드를 출력하는 함수
void printList(Node* head) {

	// 제목 출력
	printf("\n[학생 목록]\n");

	// 리스트가 끝날 때까지(head가 NULL이 올 때까지) 반복
	while (head != NULL) {

		// 현재 노드의 이름과 점수 출력 
		printf("이름 : %s, 점수 : %d\n", head->name, head->score);

		// 다음 노드로 이동
		head = head->next;
	}
}

// 연결 리스트에서 특정 이름을 가진 노드를 찾아 삭제하는 함수
void deleteNode(Node** head, const char* name) {

	// 현재 노드를 가리킬 포인터와, 이전 노드를 가리킬 포인터 선언
	Node* current = *head;     // 현재 위치
	Node* prev = NULL;		   // 이전 노드 (처음엔 없음)

	// 리스트를 순회하면서 이름을 비교
	while (current != NULL) {

		// 현재 노드의 이름과 삭제할 이름이 같은지 확인
		if (strcmp(current->name, name) == 0) {
			if (prev == NULL) {

				//삭제할 노드가 첫 번재 노드 일 경우 -> head를 다음 노드로 옮김
				*head = current->next; // 첫 번째 노드
			}
			else {

				// 중간이나 마지막 노드일 경우 -> 이전 노드의 next를 건너뛰게 함
				prev->next = current->next;
			}

			// 현재 노드를 메모리 해제
			free(current);

			// 삭제 완료 메시지 출력
			printf("'%s' 학생 삭제 완료.\n", name);
			return;
		}
		// 다음 노드로 이동하기 전에 이전 노드를 현재로 저장.
		prev = current;
		current = current->next;
	}
	// 끝까지 찾았지만 일치하는 이름이 없을 경우
	printf("'%s' 학생을 찾을 수 없습니다.\n", name);
}

// 전체 리스트 해제

// 연결 리스트에 동적으로 생성된 모든 노드를 메모리에서 해제하는 함수
void freeAll(Node* head) {

	// 임시 포인터로 현재 노드를 저장할 변수
	Node* temp;

	// 리스트가 끝날 때 까지 반복
	while (head != NULL) {
		temp = head;            // 현재 노드를 temp에 저장
		head = head->next;		// head를 다음 노드로 이동
		free(temp);				// temp에 저장한 현재 노드를 메모리에서 해제
	}
}

int main() {
	Node* head = NULL;     // 연결 리스트의 시작 포인터(처음엔 비어있음)
	int choice;			   // 메뉴 선택용 변수
	char name[50];		   // 학생 이름 입력 받는 배열
	int score;			   // 학생 점수 입력용 변수


	// 무한 반복 -> 종료 선택 시 return으로 빠져나감
	while (1) {

		// 메뉴 출력 및 선택 입력
		printf("\n[메뉴] 1.추가 2.출력 3.삭제 4.종료\n선택 : ");
		scanf_s("%d", &choice);

		switch (choice) {

		// 학생 추가
		case 1:
			printf("이름 입력 : ");
			scanf_s("%s", name, (unsigned)_countof(name));          // 이름 입력
			printf("점수 입력 : ");
			scanf_s("%d", &score);        // 점수 입력
			append(&head, name, score);   // 리스트에 추가
			break;
		
		// 리스트 출력
		case 2:
			printList(head);
			break;

		// 학생 삭제
		case 3:
			printf("삭제할 학생 이름 : ");
			scanf_s("%s", name, (unsigned)_countof(name));
			deleteNode(&head, name);    // 해당 이름 가진 노드 삭제
			break;

		// 종료
		case 4:
			freeAll(head);    // 동적 메모리 해제
			return 0;		  // 프로그램 종료

		// 잘못된 입력 처리
		default :
			printf("잘못된 선택입니다. \n");
		}
	}
}