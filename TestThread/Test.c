#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct process_type
{
    int pcbid;  //进程控制块的标识
    int priorityNum;  //优先级编号
    int daxiao; //占用的大小
    char xiaoxi[100];   //进程的信息
};

struct process_type zhucun[20];
int shumu = 0, pcbid_1 = -1;

void create()   //创建一个进程
{
    if (shumu >= 20)
    {
        printf("\n内存已满，请先结束或者换出进程");
    }
    else
    {
        printf("请输入新进程的pcbid:");
        scanf("%d", &zhucun[shumu].pcbid);
        printf("请输入新进程的优先级:");
        scanf("%d", &zhucun[shumu].priorityNum);
        printf("请输入新进程的大小");
        scanf("%d", &zhucun[shumu].daxiao);
        printf("请输入新进程的消息");
        scanf("%s", &zhucun[shumu].xiaoxi);
        shumu++;
        if (shumu==1)   //产生第一个进程
        {
            pcbid_1 = 0;
        }
    }
}

void clrscr()   //清屏
{
    system("cls");
}

void run()
{
    if (shumu == 0)
    {
        printf("当前没有进程运行\n");
    }
    else
    {
        printf("当前运行进程的情况为\n:");
        printf("\t 进程标识符:%d\n", zhucun[pcbid_1].pcbid);
        printf("\t 优先级:%d\n", zhucun[pcbid_1].priorityNum);
        printf("\t 大小:%d\n", zhucun[pcbid_1].daxiao);
        printf("\t 消息:%d\n", zhucun[pcbid_1].xiaoxi);
    }
}

void kill()     //终止进程
{
    if (shumu==0)
    {
        printf("当前没有进程运行\n");
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
    printf("请输入发送信息的进程编号");
    scanf("%d", &fasong);
    if ((i = xunzhao(fasong))==-1)
    {
        printf("该进程编号不存在\n");
        return;
    }
    printf("请输入接收信息的进程编号:");
    scanf("%d", &jieshou);
    if ((j=xunzhao(jieshou))==-1)
    {
        printf("该进程编号不存在\n");
        return;
    }
    strcpy(zhucun[j].xiaoxi, zhucun[i].xiaoxi);
}

void chakan()       //查看当前所有进程运行状态
{
    int i;
    if (shumu==0)
    {
        printf("当前没有进程运行\n");
    }
    else
    {
        printf("pcbif  优先级  大小  消息\n");
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
        printf("\n------------     进程演示系统     ------------\n");
        printf("\n------  1.创建新进程        2.查看运行进程 ------\n");
        printf("\n------  3.查看所有进程      4.终止运行进程 ------\n");
        printf("\n------  5.进程之间通信      6.退出系统     ------\n");
        printf("请选择(1~6):");
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
            printf("没有这个选项请重新输入！");
            break;
        }
        Sleep(2000);
        clrscr();   //清屏
    }
    return 0;
}
