#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node
{
    char name[10];  //进程标识符
    int round;  //经常每次轮转的时间片
    int cputime;    //进程占用CUP的时间
    int needtime;   //进程到完成还需要的时间
    char state; //进程的状态
    struct node* next;  //链指针
}PCB;

PCB* finish, * ready, * run;    //队列
int N, t;   //进程数和时间片的大小

void firstin()   //就绪队列的第一个进程投入运行
{
    run = ready;    //就绪队列的第一个进程投入运行
    run->state = 'R';   //就绪转台变为运行态
    ready = ready->next;    //就绪队列头指针后移到下一进程
}

void prt1(char a)    //输出标题函数
{
    if (toupper(a) == 'P')
    {
        printf("进程名 占用CPU时间 到完成还需要的时间 轮转时间片 状态\n");
    }
}

void prt2(char a, PCB* q)   //输出行函数
{
    if (toupper(a) == 'P')
    {
        printf("%4s %8d %12d %14d %8c\n", q->name, q->cputime, q->needtime, q->round, q->state);
    }
}

void prt(char algo) //输出函数
{
    PCB* p;
    prt1(algo); //输出标题
    if (run != NULL)    //如果运行指针不空
    {
        prt2(algo, run);    //输出当前正在运行PCB
    }
    p = ready;
    while (p != NULL)
    {
        prt2(algo, p);
        p = p->next;
    }
    p = finish; //输出完成队列的PCB
    while (p != NULL)
    {
        prt2(algo, p);
        p = p->next;
    }
    getchar();//按任意键继续
}

void insert(PCB* q)
{
    PCB* p1, * s, * r;
    s = q;
    p1 = ready;
    r = NULL;
    while (p1 != NULL && p1->round <= s->round)
    {
        r = p1;
        p1 = p1->next;
    }
    if (r != NULL)
    {
        r->next = s;
    }
    else
    {
        ready = s;
    }
    s->next = p1;
}

void create(char alg)
{
    PCB* p;
    int i, time;
    char na[10];
    ready = NULL;
    finish = NULL;
    run = NULL;
    printf("输入进程名及其需要运行的时间（中间以空格隔开）：\n");
    for (i = 1; i <= N; i++)
    {
        p = (PCB*)malloc(sizeof(PCB));
        scanf("%s %d", &na, &time);
        strcpy(p->name, na);
        p->cputime = 0;
        p->needtime = time;
        p->state = 'W';
        p->round = 0;
        if (ready != NULL)
        {
            insert(p);
        }
        else
        {
            p->next = ready;
            ready = p;
        }
    }
    printf("**************时间片轮转进程调度过程**************\n");
    prt(alg);
    run = ready;
    ready = ready->next;
    run->state = 'R';
}


void timeslicecycle(char alg)
{
    while (run != NULL)
    {
        run->cputime = run->cputime + t;
        run->needtime = run->needtime - t;
        run->round = run->round + t;
        if (run->needtime <= 0)
        {
            run->next = finish;
            finish = run;
            run->state = 'F';
            run = NULL;
            if (ready != NULL)
            {
                firstin();
            }
        }
        else
        {
            run->state = 'W';
            insert(run);
            firstin();
        }
        prt(alg);
    }
}

int main()
{
    char algo = 'P';
    printf("输入进程的个数：");
    scanf("%d", &N);
    printf("定义时间片大小：");
    scanf("%d", &t);
    create(algo);
    timeslicecycle(algo);
    free(run);
    free(ready);
    free(finish);
    return 0;
}
