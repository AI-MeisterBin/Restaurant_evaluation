
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define MAX_NAME    20 //�ִ� �̸� ����
#define MAX_MENU 5 //���� ��
typedef struct {//�޴� ����ü ����
    char name[MAX_NAME + 1];//�޴� �̸�
    int num; //��ȣ
    int scores[MAX_MENU];//�޴� ����
}Restaurant_Menu;

const char* judge[MAX_MENU] = { "��","��","������","�ʱ�","������" };


Restaurant_Menu* R_menu;
int max_Restaurant_Menu;

void reset();//�Ĵ� & �޴� ������ �ʱ�ȭ
void start();//�޴� �� ���α׷� ����
int main(void)
{
    reset();//�޴� ������ �ʱ�ȭ
    start();//�޴� �� ���α׷� ����
    free(R_menu);//�޸� ��ȯ
    return 0;
}

/*void save_file() {
    Restaurant_Menu* f_menu = 0;
    int num = 0;
    char name[10];
    f_menu = R_menu + (num - 1);
    f_menu->num = num;
    FILE* fr;
    fr = fopen("Restaurant_evaluation.txt", "a");            //txt ���Ͽ� �������� ���� ���� �ذ� �Ұ� - ����
    //fputs(R_name, fr);                                     //����ü�� �Ű����� ���� �����ϴ� �Ϳ� ������ �ذ����� ����
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
    printf("�Ĵ� �̸��� �Է��ϼ��� : "); //�Ĵ� �̸� �ޱ�
    scanf_s("%s", R_name, sizeof(R_name));
    printf("%s", R_name);
    printf("�� �� �޴� ��: ");
    scanf_s("%d", &max_Restaurant_Menu);//�� �޴� �� �ޱ�

    R_menu = (Restaurant_Menu*)malloc(sizeof(Restaurant_Menu) * max_Restaurant_Menu);//���� �迭 �޸� �Ҵ�
    memset(R_menu, 0, sizeof(Restaurant_Menu) * max_Restaurant_Menu);//�޸� �ʱ�ȭ


    for (i = 0; i < max_Restaurant_Menu; i++)
    {
        for (s = 0; s < MAX_MENU; s++)
        {
            R_menu[i].scores[s] = -1; //������ -1�� ����
        }
    }
}


int SelectMenu();//�޴� ��� �� ����
void AddRestaurant_Menu();//�޴� ������ �Է�
void RemoveRestaurant_Menu();//�޴� ������ ����
void FindRestaurant_Menu();//�޴� �˻�
void ListRestaurant_Menu();//��� ����
void start()
{
    int key = 0;
    while ((key = SelectMenu()) != 0)//������ �޴��� 0�� �ƴϸ� �ݺ�
    {
        printf("\n");
        switch (key)//������ Ű�� ���� ��� ����
        {
        case 1: AddRestaurant_Menu(); break;
        case 2: RemoveRestaurant_Menu(); break;
        case 3: FindRestaurant_Menu(); break;
        case 4: ListRestaurant_Menu(); break;
        default: printf("�߸� �����Ͽ����ϴ�.\n"); break;
        }
        printf("\n");
    }
    //save_file(); //���Ͽ� ����
    printf("���α׷� ����\n");
}

int SelectMenu()//�޴� ��� �� ����
{
    int key = 0;
    printf("�Ĵ� �޴� �� ���α׷�\n");
    printf("1: �޴� ������ �Է� 2: �޴� ������ ���� 3: �޴� �˻� 4: ��� ���� 0: ����\n���� : ");
    scanf_s("%d", &key);
    return key;
}

int TrueNum(int num);//��ȿ�� ��ȣ���� �Ǻ�
int TrueScore(int score);//��ȿ�� �������� �Ǻ�
void AddRestaurant_Menu()//�޴� ������ �Է�
{
    int num = 0;
    Restaurant_Menu* f_menu = 0;
    int s = 0;

    printf("�߰��� �޴� ��ȣ(1~%d): ", max_Restaurant_Menu);
    scanf_s("%d", &num);

    if (TrueNum(num) == 0)//��ȿ�� ��ȣ�� �ƴ� ��
    {
        printf("������ ��� �޴� ��ȣ�Դϴ�.\n");
        return;
    }

    if (R_menu[num - 1].num)//�̹� ��ȣ�� ������ ������ ��
    {
        printf("�̹� �߰��Ͽ����ϴ�\n");
        return;
    }

    //R_menu�� 1�� �޴� �����͸� �����ϴ� �޸� �ּ�
    //���� R_menu+(num-1)�� num�� �޴� �����͸� �����ϴ� �޸� �ּ�
    f_menu = R_menu + (num - 1);
    f_menu->num = num; f_menu->name;
    printf("�޴� �̸�: ");
    scanf_s("%s", f_menu->name, sizeof(f_menu->name));

    for (s = 0; s < MAX_MENU; s++)
    {
        printf("%s ����:", judge[s]);
        scanf_s("%d", f_menu->scores + s); //�����ͷ� ���� ����

        if (TrueScore(f_menu->scores[s]) == 0)//��ȿ�� ������ �ƴ� ��
        {
            f_menu->scores[s] = -1;
            printf("�Է��� ������ ��ȿ���� �ʾƼ� %s ������ �Է� ó������ �ʾҽ��ϴ�.\n", judge[s]);
        }
    }
}
int TrueNum(int num)//��ȿ�� ��ȣ���� �Ǻ�
{
    return (num >= 1) && (num <= max_Restaurant_Menu);
}
int TrueScore(int score)//��ȿ�� �������� �Ǻ�
{
    return (score >= 0) && (score <= 100);
}
void RemoveRestaurant_Menu()//�޴� ������ ����
{
    int num = 0;
    Restaurant_Menu* f_menu = 0;
    int s = 0;

    printf("������ �޴� ��ȣ(1~%d): ", max_Restaurant_Menu);
    scanf_s("%d", &num);

    if (TrueNum(num) == 0)//��ȿ�� ��ȣ�� �ƴ� ��
    {
        printf("������ ��� �޴� ��ȣ�Դϴ�.\n");
        return;
    }

    if (R_menu[num - 1].num == 0)//��ȣ�� ������ ���°� �ƴ� ��
    {
        printf("�����Ͱ� �����ϴ�.\n");
        return;
    }

    f_menu = R_menu + (num - 1);
    strcpy_s(f_menu->name, sizeof(f_menu->name), "");// �̸� ����
    f_menu->num = 0; // ��ȣ ����
    for (s = 0; s < MAX_MENU; s++)
    {
        f_menu->scores[s] = -1; // ���� ����
    }

    printf("�����Ͽ����ϴ�.\n");
}
void Viewf_menuData(Restaurant_Menu* f_menu);//�޴� �����͸� ������
void FindRestaurant_Menu()
{
    int num = 0;
    Restaurant_Menu* f_menu = 0;
    int s = 0;

    printf("�˻��� �޴� ��ȣ(1~%d): ", max_Restaurant_Menu);
    scanf_s("%d", &num);

    if (TrueNum(num) == 0)//��ȿ�� ��ȣ�� �ƴ� ��
    {
        printf("������ ��� �޴� ��ȣ�Դϴ�.\n");
        return;
    }

    if (R_menu[num - 1].num == 0)//��ȣ�� ������ ���°� �ƴ� ��
    {
        printf("�����Ͱ� �����ϴ�.\n");
        return;
    }

    f_menu = R_menu + (num - 1);
    Viewf_menuData(f_menu);
}
void Viewf_menuData(Restaurant_Menu* f_menu)//�޴� �����͸� ������
{
    int i = 0;
    int s = 0;

    printf("%4d %10s ", f_menu->num, f_menu->name);//��ȣ�� �̸� ���
    for (s = 0; s < MAX_MENU; s++)
    {
        printf("%4d ", f_menu->scores[s]);//���� ���
    }
    printf("\n");
}
void ListRestaurant_Menu()
{
    int i = 0;
    int s = 0;

    printf("%4s %10s ", "��ȣ", "�̸�");
    for (s = 0; s < MAX_MENU; s++)
    {
        printf("%4s ", judge[s]);//�� �׸� ���
    }
    printf("������ -1�� ���� ���Է�\n");

    for (i = 0; i < max_Restaurant_Menu; i++)
    {
        if (R_menu[i].num)
        {
            Viewf_menuData(R_menu + i);// �޴� ������ ���
        }
    }
}
