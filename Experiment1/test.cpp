#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct process_type
{
    int pcbId;  // ���̿��ƿ�ı�ʶ
    int priorityNum;  // ���ȼ����
    int size; // ռ�õĴ�С
    char info[100];   // ���̵���Ϣ
};

struct process_type mainMemory[20];
int number = 0, pcbId_1 = -1;

void create()   // ����һ������
{
    if (number >= 20)
    {
        printf("\n�ڴ����������Ƚ������߻�������");
        return;
    }
    else
    {
        printf("�������½��̵�pcbid:");
        scanf("%d", &mainMemory[number].pcbId);
        printf("�������½��̵����ȼ�:");
        scanf("%d", &mainMemory[number].priorityNum);
        printf("�������½��̵Ĵ�С");
        scanf("%d", &mainMemory[number].size);
        printf("�������½��̵���Ϣ");
        scanf("%s", mainMemory[number].info);
        number++;
        if (number == 1)   // ������һ������
        {
            pcbId_1 = 0;
        }
    }
}

void clrscr()   // ����
{
    system("cls");
}

void run()
{
    if (number == 0)
    {
        printf("��ǰû�н�������\n");
    }
    else
    {
        printf("��ǰ���н��̵����Ϊ:\n");
        printf("\t ���̱�ʶ��:%d\n", mainMemory[pcbId_1].pcbId);
        printf("\t ���ȼ�:%d\n", mainMemory[pcbId_1].priorityNum);
        printf("\t ��С:%d\n", mainMemory[pcbId_1].size);
        printf("\t ��Ϣ:%s\n", mainMemory[pcbId_1].info);
    }
}

void kill()     // ��ֹ����
{
    if (number == 0)
    {
        printf("��ǰû�н�������\n");
    }
    else
    {
        int i;
        for (i = pcbId_1; i < number - 1; i++) // �� pcbId_1 ��ʼ������
        {
            mainMemory[i].pcbId = mainMemory[i + 1].pcbId;
            mainMemory[i].priorityNum = mainMemory[i + 1].priorityNum;
            mainMemory[i].size = mainMemory[i + 1].size;
            strcpy(mainMemory[i].info, mainMemory[i + 1].info);
        }
        number--; // ������һ
        if (number == 0) // ����Ѿ�û�н�����
        {
            pcbId_1 = -1;
        }
    }
}

int seek(int pcbId)
{
    int i;
    for (i = 0; i < number; i++)
    {
        if (mainMemory[i].pcbId == pcbId)
        {
            return i;
        }
    }
    return -1;
}

//ģ�����֮���ͨ��
void comm()
{
    int send, receive;
    int i, j;
    printf("�����뷢����Ϣ�Ľ��̱��:");
    scanf("%d", &send);
    if ((i = seek(send)) == -1)
    {
        printf("�ý��̱�Ų�����\n");
        return;
    }
    printf("�����������Ϣ�Ľ��̱��:");
    scanf("%d", &receive);
    if ((j = seek(receive)) == -1)
    {
        printf("�ý��̱�Ų�����\n");
        return;
    }
    strcpy(mainMemory[j].info, mainMemory[i].info);
}

void query()       // �鿴��ǰ���н�������״̬
{
    int i;
    if (number == 0)
    {
        printf("��ǰû�н�������\n");
    }
    else
    {
        printf("pcbif  ���ȼ�    ��С   ��Ϣ\n");
        for (i = 0; i < number; i++) // ʹ��ѭ������ i
        {
            printf("%-8d", mainMemory[i].pcbId);
            printf("%-10d", mainMemory[i].priorityNum);
            printf("%-9d", mainMemory[i].size);
            printf("%s", mainMemory[i].info);
            printf("\n");
        }
    }
}

void ShowMenu()
{
    printf("\n------------     ������ʾϵͳ     ------------\n");
    printf("\n------  1.�����½���        2.�鿴���н��� ------\n");
    printf("\n------  3.�鿴���н���      4.��ֹ���н��� ------\n");
    printf("\n------  5.����֮��ͨ��      6.�˳�ϵͳ     ------\n");
    printf("��ѡ��(1~6):");
}

int clear_input_buffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* ѭ����ȡ�����ַ���ֱ����ȡ���س������ļ�������Ϊֹ */
    }
    return 0; // ����0��ʾ������뻺�����ɹ�
}
int main()
{
    char c;
    clrscr();   // ����
    do
    {
        ShowMenu();
        //fflush(stdin);
        clear_input_buffer(); // ������뻺����
        c = getchar();
        switch (c)
        {
        case '1':
            create();
            break;
        case '2':
            run();
            break;
        case '3':
            query();
            break;
        case '4':
            kill();
            break;
        case '5':
            comm();
            break;
        case '6':
            exit(0);
            break;
        default:
            printf("û�����ѡ�����������룡");
            break;
        }
    } while (1);
    return 0;
}
