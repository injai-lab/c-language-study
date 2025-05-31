#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 3

// ����ü ����
typedef struct {
	char name[50];
	int scores[3]; // ����, ����, ����
	float average; // �Ǽ������� ���� �� ��հ�
	char grade;   // ���
}Student;

// �Լ� ����
void inputStudent(Student* s);
float calculateAverage(int scores[], int count);
char assignGrade(float avg);
void printStudent(Student s);


// �л� ���� �Է� �Լ�
void inputStudent(Student* s) {
	printf("�̸�: ");
	scanf_s("%s", s->name, (unsigned)_countof(s->name));

	printf("���� ����: ");
	if (scanf_s("%d", &s->scores[0]) != 1) {
		printf("�Է� ���� : ���� ���� \n");
		s->scores[0] = 0;
	}

	printf("���� ����: ");
	if (scanf_s("%d", &s->scores[1]) != 1) {
		printf("�Է� ���� : ���� ����\n");
		s->scores[1] = 0;
	}

	printf("���� ����: ");
	if (scanf_s("%d", &s->scores[2]) != 1) {
		printf("�Է� ���� : ���� ����\n");
		s->scores[2] = 0;
	}	
}

// ��� ��� �Լ�
float calculateAverage(int scores[], int count) {
	int sum = 0;
	for (int i = 0; i < count; i++) {
		sum += scores[i];
	}
	return (float)sum / count;
}

// ���� ��� �Լ�
char assignGrade(float avg) {
	if (avg >= 90) {
		return 'A';
	}
	else if (avg >= 80) {
		return 'B';
	}
	else if (avg >= 70) {
		return 'C';
	}
	else if (avg >= 60) {
		return 'D';
	}
	else {
		return 'F';
	}
}

void printStudent(Student s) {
	printf("\n�̸� : %s\n", s.name);
	printf("��� : %.2f\n", s.average);
	printf("���� : %c\n", s.grade);
}


int main() {
	Student students[MAX_STUDENTS];

	printf("=== �л� ���� �Է� ===\n");
	for (int i = 0; i < MAX_STUDENTS; i++) {
		printf("\n[%d��° �л�]\n", i + 1);
		inputStudent(&students[i]);
	}

	printf("\n=== ���� ��� ===\n");
	for (int i = 0; i < MAX_STUDENTS; i++) {
		students[i].average = calculateAverage(students[i].scores, 3);
		students[i].grade = assignGrade(students[i].average);
		printStudent(students[i]);
	}
	return 0;
}

