#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//����ü ����
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
        printf("�޸� �Ҵ� ����\n");
        return;
    }

    printf("�̸� : ");
    fgets(newStudent->name, sizeof(newStudent->name), stdin);
    newStudent->name[strcspn(newStudent->name, "\n")] = '\0';

    printf("�й� : ");
    fgets(newStudent->id, sizeof(newStudent->id),stdin);
    newStudent->id[strcspn(newStudent->id, "\n")] = '\0';

    printf("�а� : ");
    fgets(newStudent->major, sizeof(newStudent->major),stdin);
    newStudent->major[strcspn(newStudent->major, "\n")] = '\0';

    printf("�� ���� ������ �Է��ϼ��� (��/��/��): ");
    fflush(stdout);
    // fflush(stdout);
    
    char temp[100];
    if (fgets(temp, sizeof(temp), stdin) == NULL || sscanf(temp, "%d %d %d",
        &newStudent->scores[0], &newStudent->scores[1], &newStudent->scores[2]) !=3){
            printf("������ �ùٸ��� �Է��ϼ��� (�� : 90 85 78)\n");
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
    printf("�л��� ���������� �߰��Ǿ����ϴ�.\n");
}

void printStudents(Student*  head) {
    if (head == NULL) {
        printf("��ϵ� �л��� �����ϴ�.\n");
        return;
    }

    printf("\n[ ��ü �л� ���\n]");
    printf("----------------------------------------------------------");
    printf("��ȣ | �̸�\t�й�\t\t�а�\t\t���� ���� ���� ��� ����\n");
    printf("----------------------------------------------------------");

    int count = 1;
    printf("\n[ ��ü �л� ��� ]\n");
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
            printf("\n[ �˻� ��� ]\n");
            printf("�̸� : %s\n", head->name);
            printf("�й� : %s\n", head->id);
            printf("�а� : %s\n", head->major);
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
                *head = current->next; // ù ��� ����
            } else {
                prev->next = current->next; // �߰� ���� ����
            }
            free(current);
            printf("'%s' �л� ������ �����߽��ϴ�.\n", name);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("'%s' �л� ������ �����߽��ϴ�.\n", name);
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
        printf("\n[ �л� ���� �ý��� ]\n");
        printf("1. �л� �߰�\n2. ��ü ���\n3. �л��˻�\n4. ����\n5. ����\n���� : ");
        if(scanf_s("%d", &choice) != 1){
            printf("���ڸ� �Է��ϼ���.\n");
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
                print("�˻��� �̸� : ");
                fgets(searchName, sizeof(searchName), stdin);
                searchName[strcspn(searchName, "\n")] = '\0';
                findStudent(head, searchName);
                break;
            case 4:
                char deleteName[50];
                printf("������ �̸� : ");
                fgets(deleteName, sizeof(deleteName), stdin);
                deleteName[strcspn(deleteName, "\n")] = '\0';
                deleteStudent(&head, deleteName);
                break;
            case 5:
                printf("���α׷��� �����մϴ�.\n");
                return 0;    
            default:
                printf("�߸��� �����Դϴ�.\n");
        }
    }
}
