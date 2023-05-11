#define _CRT_SECURE_NO_WARNINGS 1

#include "stdio.h"
#include "stdlib.h"

typedef struct PCB
{
	char id[3];
	char name[10];
	char state;
	float arriveTime;
	float startTime;
	float finishTime;
	float serviceTime;
	float turnaroundTime;//周转时间
	float weightedTurnaroundTime;//带权周转时间
	struct  PCB* next;
}pcb;

float time;//计时器
int n;//进程个数
pcb* head = NULL, * p, * q;//进程链表指针

void run_fcfs(pcb* p1)//运行未完成的进程
{
	time = p1->arriveTime > time ? p1->arriveTime : time;
	p1->startTime = time;
	printf("\n现在时间是%5.1f,开始运行作业%s\n", time, p1->name);
	time += p1->serviceTime;
	p1->state = 'T';
	p1->finishTime = time;
	p1->turnaroundTime = p1->finishTime - p1->arriveTime;
	p1->weightedTurnaroundTime = p1->turnaroundTime / p1->serviceTime;
	printf("ID      到达时间  开始时间 服务时间 完成时间 周转时间  带权周转时间\n");
	printf("%s%10.1f%10.1f%10.1f%10.1f%10.1f%10.2f\n", p1->id, p1->arriveTime, p1->startTime, p1->serviceTime, p1->finishTime, p1->turnaroundTime, p1->weightedTurnaroundTime);
}

void fcfs()//找到当前未完成的进程
{
	int i;
	p = head;
	for (i = 0; i < n; i++)
	{
		if (p->state == 'F')
		{
			q = p;//标记当前未完成的进程
			run_fcfs(p);
		}
		p = p->next;
	}

}

void getInfo()//获取进程信息并创建进程
{
	int num;
	printf("\n 作业个数:");
	scanf("%d", &n);

	for (num = 0; num < n; num++)
	{
		p = (pcb*)malloc(sizeof(pcb));//开辟新结点
		printf("依次输入:\nID 进程名 到达时间 服务时间\n");
		scanf("%s\t%s\t%f\t%f", &p->id, &p->name, &p->arriveTime, &p->serviceTime);
		if (head == NULL)
		{
			head = p;
			q = p;
			time = p->arriveTime;
		}
		p->next = NULL;//新结点与尾结点相连接
		p->startTime = 0;//未新结点中的成员赋值
		p->finishTime = 0;
		p->turnaroundTime = 0;
		p->weightedTurnaroundTime = 0;
		p->state = 'F';
		q->next = p;//尾结点指向新结点
		q = p;//q指向新的尾结点
	}
}


void main()
{
	printf("服务算法模拟");
	getInfo();
	p = head;
	fcfs();
}