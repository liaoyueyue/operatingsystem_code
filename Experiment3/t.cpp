#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node
{
    char name[10];  //���̱�ʶ��
    int round;  //����ÿ����ת��ʱ��Ƭ
    int cputime;    //����ռ��CUP��ʱ��
    int needtime;   //���̵���ɻ���Ҫ��ʱ��
    char state; //���̵�״̬
    struct node* next;  //��ָ��
}PCB;

PCB* finish, * ready, * run;    //����
int N, t;   //��������ʱ��Ƭ�Ĵ�С

void firstin()   //�������еĵ�һ������Ͷ������
{
    run = ready;    //�������еĵ�һ������Ͷ������
    run->state = 'R';   //����ת̨��Ϊ����̬
    ready = ready->next;    //��������ͷָ����Ƶ���һ����
}

void prt1(char a)    //������⺯��
{
    if (toupper(a) == 'P')
    {
        printf("������ ռ��CPUʱ�� ����ɻ���Ҫ��ʱ�� ��תʱ��Ƭ ״̬\n");
    }
}

void prt2(char a, PCB* q)   //����к���
{
    if (toupper(a) == 'P')
    {
        printf("%4s %8d %12d %14d %8c\n", q->name, q->cputime, q->needtime, q->round, q->state);
    }
}

void prt(char algo) //�������
{
    PCB* p;
    prt1(algo); //�������
    if (run != NULL)    //�������ָ�벻��
    {
        prt2(algo, run);    //�����ǰ��������PCB
    }
    p = ready;
    while (p != NULL)
    {
        prt2(algo, p);
        p = p->next;
    }
    p = finish; //�����ɶ��е�PCB
    while (p != NULL)
    {
        prt2(algo, p);
        p = p->next;
    }
    getchar();//�����������
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
    printf("���������������Ҫ���е�ʱ�䣨�м��Կո��������\n");
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
    printf("**************ʱ��Ƭ��ת���̵��ȹ���**************\n");
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
    printf("������̵ĸ�����");
    scanf("%d", &N);
    printf("����ʱ��Ƭ��С��");
    scanf("%d", &t);
    create(algo);
    timeslicecycle(algo);
    free(run);
    free(ready);
    free(finish);
    return 0;
}
