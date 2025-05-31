#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 3

// 구조체 정의
typedef struct {
	char name[50];
	int scores[3]; // 국어, 수학, 영어
	float average; // 실수형으로 선언 해 평균값
	char grade;   // 등급
}Student;

// 함수 선언
void inputStudent(Student* s);
float calculateAverage(int scores[], int count);
char assignGrade(float avg);
void printStudent(Student s);


// 학생 정보 입력 함수
void inputStudent(Student* s) {
	printf("이름: ");
	scanf_s("%s", s->name, (unsigned)_countof(s->name));

	printf("국어 점수: ");
	if (scanf_s("%d", &s->scores[0]) != 1) {
		printf("입력 오류 : 국어 점수 \n");
		s->scores[0] = 0;
	}

	printf("수학 점수: ");
	if (scanf_s("%d", &s->scores[1]) != 1) {
		printf("입력 오류 : 수학 점수\n");
		s->scores[1] = 0;
	}

	printf("영어 점수: ");
	if (scanf_s("%d", &s->scores[2]) != 1) {
		printf("입력 오류 : 영어 점수\n");
		s->scores[2] = 0;
	}	
}

// 평균 계산 함수
float calculateAverage(int scores[], int count) {
	int sum = 0;
	for (int i = 0; i < count; i++) {
		sum += scores[i];
	}
	return (float)sum / count;
}

// 학점 계산 함수
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
	printf("\n이름 : %s\n", s.name);
	printf("평균 : %.2f\n", s.average);
	printf("학점 : %c\n", s.grade);
}


int main() {
	Student students[MAX_STUDENTS];

	printf("=== 학생 정보 입력 ===\n");
	for (int i = 0; i < MAX_STUDENTS; i++) {
		printf("\n[%d번째 학생]\n", i + 1);
		inputStudent(&students[i]);
	}

	printf("\n=== 성적 결과 ===\n");
	for (int i = 0; i < MAX_STUDENTS; i++) {
		students[i].average = calculateAverage(students[i].scores, 3);
		students[i].grade = assignGrade(students[i].average);
		printStudent(students[i]);
	}
	return 0;
}

