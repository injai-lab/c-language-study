#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ������ �ڵ� ��� �޽��� �����ϴ� �Լ�
#define _CRT_SECURE_NO_WARNINGS

// ����ü ����
typedef struct Book {
	char title[100];    // ĳ����(char) title�� ���� 100���� �迭
	char author[50];    // ĳ����(char) author�� ���� 50���� �迭
	int year;			// year ���������� �� ������
	struct Book* next;  
}Book;


// å �߰�
void addBook(Book** head, const char* title, const char* author, int year) {
	Book* newBook = (Book*)malloc(sizeof(Book));
	
	// ���� newBook�� �޸� �Ҵ��� ���� ���ϸ�, (newBook == NULL)�� ���� ���� ���ٸ�.
	// �޸� �Ҵ� ���ж�� ����� �ض�.
	if (newBook == NULL) {
		printf("�޸� �Ҵ� ����\n");
		return;
	}

	/*
	(*������).���    =  �Ϲ����� ����ü ���� ���   ex) (*newBook).title
	������ -> ���    =  ���� ǥ���� �����ϰ� ���� ��.
	*/
	strcpy_s(newBook->title, sizeof(newBook->title), title);
	strcpy_s(newBook->author, sizeof(newBook->author), author);
	
	// strcpy�� ������ �Լ��� ���Ȼ� �����ϱ� ������. strcpy_s�� ��ȯ
	
	// ex)
	// strcpy(newBook->title, title); --> strcpy_s(newBooki->title, sizeof(newBook->title), title);
	newBook->year = year;
	
	// newBook->year = NULL;

	if (*head == NULL) {   // head�� ���� �������̴�. (Book** head)
		*head = newBook;   // ����Ʈ�� ���� �ּҸ� ����Ű�� �����͸� �Լ� ���ڷ� ���޹���.
	}					   // *head�� ���� ����Ʈ�� ���� ���(Book)�� �ǹ��Ѵ�.	

	/* ��, ����Ʈ�� ���������(head�� NULL�̸�), ���� ���� ��带 ù ���� �����϶�.*/


	else {
		Book* current = *head;      // Book* current�� head�� �ʱ�ȭ 
		while (current->next != NULL) {   // current�� ����Ű�� ��� next �� NULL�� �ƴҶ� ���� �ݺ�.
			current = current->next;      // ���� ���� �̵��ϴ� �ڵ�
		}								  // �� �� ���� ������ current�� ������ ��尡 ��
		current->next = newBook;		//  ������ ����� next�� ���� ���� ��� ����
	}
	/* �̷ν� �� ���� ����Ʈ�� �� ���� �ٴ´�.*/
}

// å ��� ���
void printBooks(Book* head) {     // Book ����ü �������� �� head, ���� ��带 ����Ű�� ������
	printf("\n[ ���� ��� ]\n");

	if (head == NULL) {
		printf("��ϵ� ������ �����ϴ�.\n");
		return;
	}
	while (head != NULL) {  // head�� NULL�� �� ���� while���.
		printf("���� : %s | ���� : %s | ���ǳ⵵ : %d\n", head->title, head->author, head->year);
		
		head = head->next;  // �������� head�� ���� ���� �ű�.
							// ���� ����Ʈ �ٽ� ������ ���󰡸鼭 ��ȸ
	}
}

// å ���� 
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
			free(current);
			printf("'%s' ���� ���� �Ϸ�.\n", title);
			return;
		}
		prev = current;
		current = current->next;
	}
	printf("'%s' ������ ã�� �� �����ϴ�.\n", title);
}

// �޸� ����
void freeAllBooks(Book** head) {
	Book* current = *head;
	Book* temp;

	while (current != NULL) {
		temp = current;
		current = current->next;
		free(temp);
	}
	*head = NULL;
}

int main() {
	Book* head = NULL; // ���� ����Ʈ�� ���� ��带 ����Ű�� ������ 
	// (�ƹ� ��尡 ������ NULL)
	
	/* ����� �Է��� ���� ������*/
	int choice;
	char title[100], author[50];
	int year;    

	// while 1�� TRUE�� ���� ���� ������ ���� ��.
	while (1) {
		printf("\n[�޴�] 1. ���� �߰� 2.��� ��� 3.���� 4.����\n ���� : "); // �������ִ� �����.
		if (scanf_s("%d", &choice) != 1) {
			printf("���ڸ� �Է��ϼ���.\n");
			while (getchar() != '\n');  // �߸��� �Է� ���� ����
			continue;  // continue�� �ٽ� ��ȯ.
		}
		while (getchar() != '\n'); // ���� ���� ����
		/* scanf_s()�� ���� �ƴ� �� �Է��ϸ� ���� ���� ������ ������ �����ϴ� ��.*/
		/* getchar()�� ���ۿ� ���� \n �����ϴ� ��*/

		// scanf("%d", &choice);
		// getchar();

		switch (choice) {   //choice ����ڰ� ��ư�� ����� �� ��� 1, 2, 3, 4���߿� ������ ���� �����.

		// 1�� ���� �߰�
		case 1:
			printf("���� �Է� : ");
			fgets(title, sizeof(title), stdin);   // fgets�� ���� �Է�

			title[strcspn(title, "\n")] = '\0'; // strcspn(..., "\n")���� ���ڿ� ���� �ٴ� \n����
			// fegts�� �ڵ����� \n�� �ֱ�  ������

			printf("���� �Է� : ");
			fgets(author, sizeof(author), stdin); //fgets�� ���� �Է�

			author[strcspn(author, "\n")] = '\0'; // strcspn(..., "\n")���� ���ڿ� ���� �ٴ� \n ����

			printf("���ǳ⵵ �Է� : ");
			if (scanf_s("%d", &year) != 1) {     // ���ǳ⵵�� ���ڰ� �ƴ� �ٸ� ���� ������  �ʰ� ����� ��.
				printf("���ǳ⵵�� �����Դϴ�. \n"); // scanf�� ���� �������� ����. scanf("%d"�� ,year���� ������ �������� �����ϴ� ��.
				while (getchar() != '\n');    // while getchar() ! = \n
				break;
			}
//			scanf("%d", &year);
//			getchar();

			addBook(&head, title, author, year); //Book**�� head�� ���� -> ����Ʈ�� ������ ��� �߰� ���.
			break;

		case 2:
			printBooks(head);   // 1������ ���� �Է��ߴ� �͵��� ������
			break;
			/* ���� ����Ʈ ��ȸ�ϸ� ��� å ���.*/

		case 3:
			printf("������ å ���� : ");  // ���� ��� ��.
			fgets(title, sizeof(title), stdin); // scanf("%s", title�� ����, ���� �ִ� ���ڸ� ��� ��������.
												// �׸��Ͽ�, fgets�� ���� ���� ���ڿ��� �����ϰ� ���� �� ����.
												// sizefof(title)�� ���� ũ�� (100), stdin�� ǥ���Է���ġ(Ű���� �ǹ�)
			/* Ű����� �Է� �޴� title ���� ũ��� title(100)�ڸ��� �ο� ����.*/
			title[strcspn(title, "\n")] = '\0'; // fgets()�� ���ڿ� ���� ���� ����(\n)�� �ڵ����� ����. �̸� ����
												// strcspn(title, "\n")�� title ���ڿ����� \n�� ó�� ��Ÿ���� ��ġ�� �˷���.
												// �ش� ��ġ�� '\0'�� ������, ���ڿ� ���ᰡ �Ǹ鼭 \n�� ���ŵ˴ϴ�.
			/*
			�Է� �� : "C Programming\n"
			�Է� �� : "C Programming"
			*/
			deleteBook(&head, title); // ���� ����Ʈ���� title�� ���� ������ ���� ��带 �����ϴ� �Լ�,
									 // &head�� �ѱ�� ������ ���� ����� ù ��° ����̸� �ȵǱ� ����
									//ù ��° ��带 ������Ű�� head��ü�� �ٲ�� �ϹǷ� ���� �����͸� 
									// �ѱ��. ���������δ� strcmp(current->title, title)�� ���ؼ� ��ġ�ϸ�
									// �����Ѵ�.
			break;

		case 4:
			freeAllBooks(&head); // �����Ҵ��̵� ��� �޸𸮸� ���� �� ���� ������.
			head = NULL; 
			return 0;

		default :
			printf("�߸��� �����Դϴ�.\n");
		}
	}
}