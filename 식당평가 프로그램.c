
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define MAX_NAME    20 //최대 이름 길이
#define MAX_MENU 5 //과목 수
typedef struct {//메뉴 구조체 정의
    char name[MAX_NAME + 1];//메뉴 이름
    int num; //번호
    int scores[MAX_MENU];//메뉴 점수
}Restaurant_Menu;

const char* judge[MAX_MENU] = { "맛","양","가성비","맵기","느끼함" };


Restaurant_Menu* R_menu;
int max_Restaurant_Menu;

void reset();//식당 & 메뉴 데이터 초기화
void start();//메뉴 평가 프로그램 시작
int main(void)
{
    reset();//메뉴 데이터 초기화
    start();//메뉴 평가 프로그램 시작
    free(R_menu);//메모리 반환
    return 0;
}

/*void save_file() {
    Restaurant_Menu* f_menu = 0;
    int num = 0;
    char name[10];
    f_menu = R_menu + (num - 1);
    f_menu->num = num;
    FILE* fr;
    fr = fopen("Restaurant_evaluation.txt", "a");            //txt 파일에 평가정보를 저장 오류 해결 불가 - 실패
    //fputs(R_name, fr);                                     //구조체의 매개변수 값을 저장하는 것에 오류를 해결하지 못함
    for (int i = 0; i < 5; ++i)
    {       
        f_menu->name[i] = name;
        fputs(judge[i], fr);
        fprintf(fr, "pointer addr : %s ", name);
        fputs("\n", fr);
    }
    fclose(fr);
}*/

void reset()
{
    int i = 0;
    int s = 0;
    char R_name[100];
    printf("식당 이름을 입력하세요 : "); //식당 이름 받기
    scanf_s("%s", R_name, sizeof(R_name));
    printf("%s", R_name);
    printf("의 평가 메뉴 수: ");
    scanf_s("%d", &max_Restaurant_Menu);//평가 메뉴 수 받기

    R_menu = (Restaurant_Menu*)malloc(sizeof(Restaurant_Menu) * max_Restaurant_Menu);//동적 배열 메모리 할당
    memset(R_menu, 0, sizeof(Restaurant_Menu) * max_Restaurant_Menu);//메모리 초기화


    for (i = 0; i < max_Restaurant_Menu; i++)
    {
        for (s = 0; s < MAX_MENU; s++)
        {
            R_menu[i].scores[s] = -1; //점수을 -1로 설정
        }
    }
}


int SelectMenu();//메뉴 출력 및 선택
void AddRestaurant_Menu();//메뉴 데이터 입력
void RemoveRestaurant_Menu();//메뉴 데이터 삭제
void FindRestaurant_Menu();//메뉴 검색
void ListRestaurant_Menu();//목록 보기
void start()
{
    int key = 0;
    while ((key = SelectMenu()) != 0)//선택한 메뉴가 0이 아니면 반복
    {
        printf("\n");
        switch (key)//선택한 키에 따라 기능 수행
        {
        case 1: AddRestaurant_Menu(); break;
        case 2: RemoveRestaurant_Menu(); break;
        case 3: FindRestaurant_Menu(); break;
        case 4: ListRestaurant_Menu(); break;
        default: printf("잘못 선택하였습니다.\n"); break;
        }
        printf("\n");
    }
    //save_file(); //파일에 저장
    printf("프로그램 종료\n");
}

int SelectMenu()//메뉴 출력 및 선택
{
    int key = 0;
    printf("식당 메뉴 평가 프로그램\n");
    printf("1: 메뉴 데이터 입력 2: 메뉴 데이터 삭제 3: 메뉴 검색 4: 목록 보기 0: 종료\n선택 : ");
    scanf_s("%d", &key);
    return key;
}

int TrueNum(int num);//유효한 번호인지 판별
int TrueScore(int score);//유효한 점수인지 판별
void AddRestaurant_Menu()//메뉴 데이터 입력
{
    int num = 0;
    Restaurant_Menu* f_menu = 0;
    int s = 0;

    printf("추가할 메뉴 번호(1~%d): ", max_Restaurant_Menu);
    scanf_s("%d", &num);

    if (TrueNum(num) == 0)//유효한 번호가 아닐 때
    {
        printf("범위를 벗어난 메뉴 번호입니다.\n");
        return;
    }

    if (R_menu[num - 1].num)//이미 번호를 설정한 상태일 때
    {
        printf("이미 추가하였습니다\n");
        return;
    }

    //R_menu는 1번 메뉴 데이터를 관리하는 메모리 주소
    //따라서 R_menu+(num-1)는 num번 메뉴 데이터를 관리하는 메모리 주소
    f_menu = R_menu + (num - 1);
    f_menu->num = num; f_menu->name;
    printf("메뉴 이름: ");
    scanf_s("%s", f_menu->name, sizeof(f_menu->name));

    for (s = 0; s < MAX_MENU; s++)
    {
        printf("%s 점수:", judge[s]);
        scanf_s("%d", f_menu->scores + s); //포인터로 점수 저장

        if (TrueScore(f_menu->scores[s]) == 0)//유효한 성적이 아닐 때
        {
            f_menu->scores[s] = -1;
            printf("입력한 성적이 유효하지 않아서 %s 성적은 입력 처리하지 않았습니다.\n", judge[s]);
        }
    }
}
int TrueNum(int num)//유효한 번호인지 판별
{
    return (num >= 1) && (num <= max_Restaurant_Menu);
}
int TrueScore(int score)//유효한 점수인지 판별
{
    return (score >= 0) && (score <= 100);
}
void RemoveRestaurant_Menu()//메뉴 데이터 삭제
{
    int num = 0;
    Restaurant_Menu* f_menu = 0;
    int s = 0;

    printf("삭제할 메뉴 번호(1~%d): ", max_Restaurant_Menu);
    scanf_s("%d", &num);

    if (TrueNum(num) == 0)//유효한 번호가 아닐 때
    {
        printf("범위를 벗어난 메뉴 번호입니다.\n");
        return;
    }

    if (R_menu[num - 1].num == 0)//번호를 설정한 상태가 아닐 때
    {
        printf("데이터가 없습니다.\n");
        return;
    }

    f_menu = R_menu + (num - 1);
    strcpy_s(f_menu->name, sizeof(f_menu->name), "");// 이름 제거
    f_menu->num = 0; // 번호 제거
    for (s = 0; s < MAX_MENU; s++)
    {
        f_menu->scores[s] = -1; // 점수 제거
    }

    printf("삭제하였습니다.\n");
}
void Viewf_menuData(Restaurant_Menu* f_menu);//메뉴 데이터를 보여줌
void FindRestaurant_Menu()
{
    int num = 0;
    Restaurant_Menu* f_menu = 0;
    int s = 0;

    printf("검색할 메뉴 번호(1~%d): ", max_Restaurant_Menu);
    scanf_s("%d", &num);

    if (TrueNum(num) == 0)//유효한 번호가 아닐 때
    {
        printf("범위를 벗어난 메뉴 번호입니다.\n");
        return;
    }

    if (R_menu[num - 1].num == 0)//번호를 설정한 상태가 아닐 때
    {
        printf("데이터가 없습니다.\n");
        return;
    }

    f_menu = R_menu + (num - 1);
    Viewf_menuData(f_menu);
}
void Viewf_menuData(Restaurant_Menu* f_menu)//메뉴 데이터를 보여줌
{
    int i = 0;
    int s = 0;

    printf("%4d %10s ", f_menu->num, f_menu->name);//번호와 이름 출력
    for (s = 0; s < MAX_MENU; s++)
    {
        printf("%4d ", f_menu->scores[s]);//점수 출력
    }
    printf("\n");
}
void ListRestaurant_Menu()
{
    int i = 0;
    int s = 0;

    printf("%4s %10s ", "번호", "이름");
    for (s = 0; s < MAX_MENU; s++)
    {
        printf("%4s ", judge[s]);//평가 항목 출력
    }
    printf("점수가 -1인 곳은 미입력\n");

    for (i = 0; i < max_Restaurant_Menu; i++)
    {
        if (R_menu[i].num)
        {
            Viewf_menuData(R_menu + i);// 메뉴 데이터 출력
        }
    }
}
