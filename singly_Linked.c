#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ����ü ����
typedef struct Node {
	char name[50]; // �̸� ���� ���ڿ� 
	int score;     // ����
	struct Node* next; // ���� ����� �ּҸ� ����Ű�� ������ "���� ����Ʈ�� �ٽ�"
}Node; 

/* �� struct Node* next; ó�� �ڱ� �ڽ��� �����ϴ°�.
���� ����Ʈ�� ���� ���� ��尡 ����Ǿ� �ִ� �ڷᱸ��.
�׷��� �� ��尡 ���� ��带 ����Ű�� ���� struct Node* next�� ���Խ�Ų��.
*/

// ��� �߰�(����Ʈ ����)

// ���� ����Ʈ�� ���� �� ��带 �߰��ϴ� �Լ�
void append(Node** head, const char* name, int score) { // const(���) char* name
	
	// �� ��带 ���� �޸� ������ �������� �Ҵ�
	Node* newNode = (Node*)malloc(sizeof(Node));

	// �޸� �Ҵ� ���� �� ó��
	if (newNode == NULL) {
		printf("�޸� �Ҵ� ����\n");
		return;
	}

	// �Էµ� �̸��� �� ����� name �ʵ忡 ����
	strcpy_s(newNode->name, sizeof(newNode->name), name);

	// �Էµ� ������ �� ����� score �ʵ忡 ����
	newNode->score = score;

	// �� ���� ������ ����̹Ƿ� ���� ���� NULL�� ����
	newNode->next = NULL;

	// ���� ����Ʈ�� ��� �ִٸ� (��, ��尡 NULL�� ����)
	if (*head == NULL) {
		// ��尡 �� ��带 ����Ű���� ���� -> �� ��尡 ù ��° ��尡 ��.
		*head = newNode;
	}
	else {
		// ����Ʈ�� �̹� ��尡 ������, ���� ��带 ������ ����
		Node* current = *head;

		// ������ ������ �̵� (next�� NULL�� ������ �ݺ�)
		while (current->next != NULL) {
			current = current->next;
		}

		// ������ ����� next�� �� ��带 ����Ű���� ���� -> ���� �Ϸ�
		current->next = newNode;
	}
}

// ���� ����Ʈ�� ��� ��带 ����ϴ� �Լ�
void printList(Node* head) {

	// ���� ���
	printf("\n[�л� ���]\n");

	// ����Ʈ�� ���� ������(head�� NULL�� �� ������) �ݺ�
	while (head != NULL) {

		// ���� ����� �̸��� ���� ��� 
		printf("�̸� : %s, ���� : %d\n", head->name, head->score);

		// ���� ���� �̵�
		head = head->next;
	}
}

// ���� ����Ʈ���� Ư�� �̸��� ���� ��带 ã�� �����ϴ� �Լ�
void deleteNode(Node** head, const char* name) {

	// ���� ��带 ����ų �����Ϳ�, ���� ��带 ����ų ������ ����
	Node* current = *head;     // ���� ��ġ
	Node* prev = NULL;		   // ���� ��� (ó���� ����)

	// ����Ʈ�� ��ȸ�ϸ鼭 �̸��� ��
	while (current != NULL) {

		// ���� ����� �̸��� ������ �̸��� ������ Ȯ��
		if (strcmp(current->name, name) == 0) {
			if (prev == NULL) {

				//������ ��尡 ù ���� ��� �� ��� -> head�� ���� ���� �ű�
				*head = current->next; // ù ��° ���
			}
			else {

				// �߰��̳� ������ ����� ��� -> ���� ����� next�� �ǳʶٰ� ��
				prev->next = current->next;
			}

			// ���� ��带 �޸� ����
			free(current);

			// ���� �Ϸ� �޽��� ���
			printf("'%s' �л� ���� �Ϸ�.\n", name);
			return;
		}
		// ���� ���� �̵��ϱ� ���� ���� ��带 ����� ����.
		prev = current;
		current = current->next;
	}
	// ������ ã������ ��ġ�ϴ� �̸��� ���� ���
	printf("'%s' �л��� ã�� �� �����ϴ�.\n", name);
}

// ��ü ����Ʈ ����

// ���� ����Ʈ�� �������� ������ ��� ��带 �޸𸮿��� �����ϴ� �Լ�
void freeAll(Node* head) {

	// �ӽ� �����ͷ� ���� ��带 ������ ����
	Node* temp;

	// ����Ʈ�� ���� �� ���� �ݺ�
	while (head != NULL) {
		temp = head;            // ���� ��带 temp�� ����
		head = head->next;		// head�� ���� ���� �̵�
		free(temp);				// temp�� ������ ���� ��带 �޸𸮿��� ����
	}
}

int main() {
	Node* head = NULL;     // ���� ����Ʈ�� ���� ������(ó���� �������)
	int choice;			   // �޴� ���ÿ� ����
	char name[50];		   // �л� �̸� �Է� �޴� �迭
	int score;			   // �л� ���� �Է¿� ����


	// ���� �ݺ� -> ���� ���� �� return���� ��������
	while (1) {

		// �޴� ��� �� ���� �Է�
		printf("\n[�޴�] 1.�߰� 2.��� 3.���� 4.����\n���� : ");
		scanf_s("%d", &choice);

		switch (choice) {

		// �л� �߰�
		case 1:
			printf("�̸� �Է� : ");
			scanf_s("%s", name, (unsigned)_countof(name));          // �̸� �Է�
			printf("���� �Է� : ");
			scanf_s("%d", &score);        // ���� �Է�
			append(&head, name, score);   // ����Ʈ�� �߰�
			break;
		
		// ����Ʈ ���
		case 2:
			printList(head);
			break;

		// �л� ����
		case 3:
			printf("������ �л� �̸� : ");
			scanf_s("%s", name, (unsigned)_countof(name));
			deleteNode(&head, name);    // �ش� �̸� ���� ��� ����
			break;

		// ����
		case 4:
			freeAll(head);    // ���� �޸� ����
			return 0;		  // ���α׷� ����

		// �߸��� �Է� ó��
		default :
			printf("�߸��� �����Դϴ�. \n");
		}
	}
}