# c-language-study

이 저장소는 C 언어의 기초부터 자료구조, 알고리즘까지 폭넓게 공부하고 정리하기 위해 만들어졌습니다. 학습한 내용을 실습 예제와 함께 기록하여, 반복 학습 및 참고용으로 사용됩니다.

---
visual studio code에서 하는법

1. mingw 다운로드..
![image](https://github.com/user-attachments/assets/03e431b7-aa3e-4711-b675-1bf696a2085d)
이렇게 우클릭을 눌러서 3개를 체크.

3. installation에서
   apply 클릭.
   ![image](https://github.com/user-attachments/assets/cd2e2c09-7ec2-4ec5-9f2d-41a2149e4a0a)
다 되면 close.
  
4. 환경변수 설정.
window 검색창에 변수 작성.
![image](https://github.com/user-attachments/assets/9ebfd32b-782f-4f03-bcdc-b884f8081823)

![image](https://github.com/user-attachments/assets/4f165c9d-5512-460d-a8cf-6f28a63a77a8)
아래에 있는 path클릭 및 편집 클릭

새로만들기 클릭 -> minGw폴더 경로  bin폴더.
![image](https://github.com/user-attachments/assets/0641bb05-0fe7-4f8a-abcd-3f87260a358c)

bin 폴더까지.
F:\minGw\bin 내 pc 경로.

환경변수 추가.

5. cmd 실행
   gcc -v
   ![image](https://github.com/user-attachments/assets/71375028-130b-417c-ba23-b6e36eaedd5a)
   마지막 줄 gcc version 6.3.0이 뜨면 잘 된거다.

6. visual studio code 확장자 설치.
   visual studio code 실행
   ![image](https://github.com/user-attachments/assets/9937e424-62a1-43a7-85b3-354093b1a792)
   설치

   



## 📁 저장소 구성

| 파일명 | 설명 |
|--------|------|
| `C언어 XOR 공부` | XOR 연산에 대한 개념 및 C 코드 실습 예제 |
| `README.md` | 저장소 소개 및 학습 계획 문서 |
| `singly_Linked.c` | 단일 연결 리스트(Singly Linked List)의 구조체 정의 및 기본 연산 구현 |
| `성적 처리.cpp` | 학생의 성적 입력, 평균 계산, 등급 부여 등 관련 기능 구현 (C++ 기반 코드) |

---

## 🛠 학습 목표

- C언어의 기초 문법 정복 (자료형, 조건문, 반복문 등)
- 구조체, 포인터, 동적 할당 등의 고급 문법 이해
- 연결 리스트, 스택, 큐 등 자료구조 직접 구현
- 간단한 알고리즘 문제 해결 능력 향상

---

## ✍️ 향후 추가 예정 내용

- 이중 연결 리스트 (Doubly Linked List)
- 스택과 큐 구현
- 파일 입출력 실습
- 프로젝트 기반 C언어 실습 (ex. 간단한 ATM 시스템)

---

## 📌 참고사항

- 모든 예제는 Visual Studio 또는 GCC 환경에서 테스트됨
- 실습 환경: Windows 10, VS Code, GCC 컴파일러
- 일부 파일은 `.cpp` 확장자를 사용하였으나, C 문법 기반으로 작성됨

---

함께 공부하거나 피드백을 주고 싶으신 분은 언제든지 Pull Request 또는 Issue를 남겨주세요. 😊
