#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct process_type
{
    int pcbid;  //���̿��ƿ�ı�ʶ
    int priorityNum;  //���ȼ����
    int daxiao; //ռ�õĴ�С
    char xiaoxi[100];   //���̵���Ϣ
};

struct process_type zhucun[20];
int shumu = 0, pcbid_1 = -1;

void create()   //����һ������
{
    if (shumu >= 20)
    {
        printf("\n�ڴ����������Ƚ������߻�������");
    }
    else
    {
        printf("�������½��̵�pcbid:");
        scanf("%d", &zhucun[shumu].pcbid);
        printf("�������½��̵����ȼ�:");
        scanf("%d", &zhucun[shumu].priorityNum);
        printf("�������½��̵Ĵ�С");
        scanf("%d", &zhucun[shumu].daxiao);
        printf("�������½��̵���Ϣ");
        scanf("%s", &zhucun[shumu].xiaoxi);
        shumu++;
        if (shumu==1)   //������һ������
        {
            pcbid_1 = 0;
        }
    }
}

void clrscr()   //����
{
    system("cls");
}

void run()
{
    if (shumu == 0)
    {
        printf("��ǰû�н�������\n");
    }
    else
    {
        printf("��ǰ���н��̵����Ϊ\n:");
        printf("\t ���̱�ʶ��:%d\n", zhucun[pcbid_1].pcbid);
        printf("\t ���ȼ�:%d\n", zhucun[pcbid_1].priorityNum);
        printf("\t ��С:%d\n", zhucun[pcbid_1].daxiao);
        printf("\t ��Ϣ:%d\n", zhucun[pcbid_1].xiaoxi);
    }
}

void kill()     //��ֹ����
{
    if (shumu==0)
    {
        printf("��ǰû�н�������\n");
    }
    else
    {
        int i;
        for ( i = shumu-1; i > pcbid_1; i--)
        {
            zhucun[i - 1].pcbid = zhucun[i].pcbid;
            zhucun[i - 1].priorityNum = zhucun[i].priorityNum;
            zhucun[i - 1].daxiao = zhucun[i].daxiao;
            strcpy(zhucun[i - 1].xiaoxi, zhucun[i].xiaoxi);
            shumu--;
        }
    }
}

int xunzhao(int pcbid)
{
    int i;
    for (i = 0; i < shumu; i++)
    {
        if (zhucun[i].pcbid == pcbid)
        {
            return i;
        }
    }
    return -1;
}

void tongxun()
{
    int fasong, jieshou;
    int i, j;
    printf("�����뷢����Ϣ�Ľ��̱��");
    scanf("%d", &fasong);
    if ((i = xunzhao(fasong))==-1)
    {
        printf("�ý��̱�Ų�����\n");
        return;
    }
    printf("�����������Ϣ�Ľ��̱��:");
    scanf("%d", &jieshou);
    if ((j=xunzhao(jieshou))==-1)
    {
        printf("�ý��̱�Ų�����\n");
        return;
    }
    strcpy(zhucun[j].xiaoxi, zhucun[i].xiaoxi);
}

void chakan()       //�鿴��ǰ���н�������״̬
{
    int i;
    if (shumu==0)
    {
        printf("��ǰû�н�������\n");
    }
    else
    {
        printf("pcbif  ���ȼ�  ��С  ��Ϣ\n");
    }
    for ( i = 0; i < shumu; i++)
    {
        printf("%-8d", zhucun[pcbid_1].pcbid);
        printf("%-10d", zhucun[pcbid_1].priorityNum);
        printf("%-9d", zhucun[pcbid_1].daxiao);
        printf("%s", zhucun[pcbid_1].xiaoxi);
        printf("\n");
    }
}

void ShowMenu() {
        printf("\n------------     ������ʾϵͳ     ------------\n");
        printf("\n------  1.�����½���        2.�鿴���н��� ------\n");
        printf("\n------  3.�鿴���н���      4.��ֹ���н��� ------\n");
        printf("\n------  5.����֮��ͨ��      6.�˳�ϵͳ     ------\n");
        printf("��ѡ��(1~6):");
}


int main()
{
    char c;
    while (1)
    {
        ShowMenu();
        fflush(stdin);
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
            chakan();
            break;
        case '4':
            kill();
            break;
        case '5':
            tongxun();
            break;
        case '6':
            exit(0);
            break;
        default :
            printf("û�����ѡ�����������룡");
            break;
        }
        Sleep(2000);
        clrscr();   //����
    }
    return 0;
}
