#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//구조체 정의
typedef struct Student{
    char name[50];
    char id[20];
    char major[50];
    int scores[3];
    float average;
    char grade;
    struct Student* next;
}Student;

void addStudent(Student** head) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if(newStudent == NULL){
        printf("메모리 할당 실패\n");
        return;
    }

    printf("이름 : ");
    fgets(newStudent->name, sizeof(newStudent->name), stdin);
    newStudent->name[strcspn(newStudent->name, "\n")] = '\0';

    printf("학번 : ");
    fgets(newStudent->id, sizeof(newStudent->id),stdin);
    newStudent->id[strcspn(newStudent->id, "\n")] = '\0';

    printf("학과 : ");
    fgets(newStudent->major, sizeof(newStudent->major),stdin);
    newStudent->major[strcspn(newStudent->major, "\n")] = '\0';

    printf("세 과목 점수를 입력하세요 (국/수/영): ");
    fflush(stdout);
    // fflush(stdout);
    
    char temp[100];
    if (fgets(temp, sizeof(temp), stdin) == NULL || sscanf(temp, "%d %d %d",
        &newStudent->scores[0], &newStudent->scores[1], &newStudent->scores[2]) !=3){
            printf("점수를 올바르게 입력하세요 (예 : 90 85 78)\n");
            free(newStudent);
            return;
        }

    newStudent->average = calculateAverage(newStudent->scores, 3);
    newStudent->grade = assignGrade(newStudent->average);
    
            
    newStudent->next = NULL;

    if (*head == NULL) {
        *head = newStudent;
    }else {
        Student* current = *head;
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = newStudent;
    }
    printf("학생이 성공적으로 추가되었습니다.\n");
}

void printStudents(Student*  head) {
    if (head == NULL) {
        printf("등록된 학생이 없습니다.\n");
        return;
    }

    printf("\n[ 전체 학생 목록\n]");
    printf("----------------------------------------------------------");
    printf("번호 | 이름\t학번\t\t학과\t\t국어 수학 영어 평균 학점\n");
    printf("----------------------------------------------------------");

    int count = 1;
    printf("\n[ 전체 학생 목록 ]\n");
    while(head!=NULL){
        printf("%-4d | %-6s\t%-10s\t%-10s\t%3d %3d %3d %5.2f %c\n",
            count++,
            head->name,
            head->id,
            head->major,
            head->scores[0],
            head->scores[1],
            head->scores[2],
            head->average,
            head->grade
        );
        head = head->next;
    }
    printf("----------------------------------------------------------");
} 

void findStudent(Student* head, const char* name) {
    int found = 0;
    while(head != NULL){
        if(strcmp(head->name, name) == 0){
            printf("\n[ 검색 결과 ]\n");
            printf("이름 : %s\n", head->name);
            printf("학번 : %s\n", head->id);
            printf("학과 : %s\n", head->major);
            found = 1;
            break;
        }
    }
}

void deleteStudent(Student** head, const char* name) {
    Student* current = *head;
    Student* prev = NULL;

    while(current != NULL) {
        if(strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                *head = current->next; // 첫 노드 삭제
            } else {
                prev->next = current->next; // 중간 이후 삭제
            }
            free(current);
            printf("'%s' 학생 정보를 삭제했습니다.\n", name);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("'%s' 학생 정보를 삭제했습니다.\n", name);
}

float calculateAverage(int scores[], int count) {
    int sum = 0;
    for(int i = 0; i < count; i++){
        sum += scores[i];
    }
    return (float)sum / count;
}

char assignGrade(float avg) {
    if(avg >= 90){
        return 'A';
    }else if (avg >= 80){
        return 'B';
    }else if (avg >= 70) {
        return 'C';
    }else if (avg >= 60) {
        return 'D';
    }else{
        return 'F';
    }
}



int main(int argc, char const *argv[])
{
    Student* head = NULL;
    int choice;

    while (1) {
        printf("\n[ 학생 정보 시스템 ]\n");
        printf("1. 학생 추가\n2. 전체 출력\n3. 학생검색\n4. 삭제\n5. 종료\n선택 : ");
        if(scanf_s("%d", &choice) != 1){
            printf("숫자를 입력하세요.\n");
            while(getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch(choice) {
            case 1:
                addStudent(&head);
                break;
            case 2:
                printStudents(head);
                break;
            case 3:
                char searchName[50];
                print("검색할 이름 : ");
                fgets(searchName, sizeof(searchName), stdin);
                searchName[strcspn(searchName, "\n")] = '\0';
                findStudent(head, searchName);
                break;
            case 4:
                char deleteName[50];
                printf("삭제할 이름 : ");
                fgets(deleteName, sizeof(deleteName), stdin);
                deleteName[strcspn(deleteName, "\n")] = '\0';
                deleteStudent(&head, deleteName);
                break;
            case 5:
                printf("프로그램을 종료합니다.\n");
                return 0;    
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
}
