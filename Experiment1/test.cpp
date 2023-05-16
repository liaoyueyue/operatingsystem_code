#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct process_type
{
    int pcbId;  // 进程控制块的标识
    int priorityNum;  // 优先级编号
    int size; // 占用的大小
    char info[100];   // 进程的信息
};

struct process_type mainMemory[20];
int number = 0, pcbId_1 = -1;

void create()   // 创建一个进程
{
    if (number >= 20)
    {
        printf("\n内存已满，请先结束或者换出进程");
        return;
    }
    else
    {
        printf("请输入新进程的pcbid:");
        scanf("%d", &mainMemory[number].pcbId);
        printf("请输入新进程的优先级:");
        scanf("%d", &mainMemory[number].priorityNum);
        printf("请输入新进程的大小");
        scanf("%d", &mainMemory[number].size);
        printf("请输入新进程的消息");
        scanf("%s", mainMemory[number].info);
        number++;
        if (number == 1)   // 产生第一个进程
        {
            pcbId_1 = 0;
        }
    }
}

void clrscr()   // 清屏
{
    system("cls");
}

void run()
{
    if (number == 0)
    {
        printf("当前没有进程运行\n");
    }
    else
    {
        printf("当前运行进程的情况为:\n");
        printf("\t 进程标识符:%d\n", mainMemory[pcbId_1].pcbId);
        printf("\t 优先级:%d\n", mainMemory[pcbId_1].priorityNum);
        printf("\t 大小:%d\n", mainMemory[pcbId_1].size);
        printf("\t 消息:%s\n", mainMemory[pcbId_1].info);
    }
}

void kill()     // 终止进程
{
    if (number == 0)
    {
        printf("当前没有进程运行\n");
    }
    else
    {
        int i;
        for (i = pcbId_1; i < number - 1; i++) // 从 pcbId_1 开始向后遍历
        {
            mainMemory[i].pcbId = mainMemory[i + 1].pcbId;
            mainMemory[i].priorityNum = mainMemory[i + 1].priorityNum;
            mainMemory[i].size = mainMemory[i + 1].size;
            strcpy(mainMemory[i].info, mainMemory[i + 1].info);
        }
        number--; // 数量减一
        if (number == 0) // 如果已经没有进程了
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

//模拟进程之间的通信
void comm()
{
    int send, receive;
    int i, j;
    printf("请输入发送信息的进程编号:");
    scanf("%d", &send);
    if ((i = seek(send)) == -1)
    {
        printf("该进程编号不存在\n");
        return;
    }
    printf("请输入接收信息的进程编号:");
    scanf("%d", &receive);
    if ((j = seek(receive)) == -1)
    {
        printf("该进程编号不存在\n");
        return;
    }
    strcpy(mainMemory[j].info, mainMemory[i].info);
}

void query()       // 查看当前所有进程运行状态
{
    int i;
    if (number == 0)
    {
        printf("当前没有进程运行\n");
    }
    else
    {
        printf("pcbif  优先级    大小   消息\n");
        for (i = 0; i < number; i++) // 使用循环变量 i
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
    printf("\n------------     进程演示系统     ------------\n");
    printf("\n------  1.创建新进程        2.查看运行进程 ------\n");
    printf("\n------  3.查看所有进程      4.终止运行进程 ------\n");
    printf("\n------  5.进程之间通信      6.退出系统     ------\n");
    printf("请选择(1~6):");
}

int clear_input_buffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* 循环读取输入字符，直到读取到回车符或文件结束符为止 */
    }
    return 0; // 返回0表示清空输入缓冲区成功
}
int main()
{
    char c;
    clrscr();   // 清屏
    do
    {
        ShowMenu();
        //fflush(stdin);
        clear_input_buffer(); // 清空输入缓冲区
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
            printf("没有这个选项请重新输入！");
            break;
        }
    } while (1);
    return 0;
}
