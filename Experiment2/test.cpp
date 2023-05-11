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
	float turnaroundTime;//��תʱ��
	float weightedTurnaroundTime;//��Ȩ��תʱ��
	struct  PCB* next;
}pcb;

float time;//��ʱ��
int n;//���̸���
pcb* head = NULL, * p, * q;//��������ָ��

void run_fcfs(pcb* p1)//����δ��ɵĽ���
{
	time = p1->arriveTime > time ? p1->arriveTime : time;
	p1->startTime = time;
	printf("\n����ʱ����%5.1f,��ʼ������ҵ%s\n", time, p1->name);
	time += p1->serviceTime;
	p1->state = 'T';
	p1->finishTime = time;
	p1->turnaroundTime = p1->finishTime - p1->arriveTime;
	p1->weightedTurnaroundTime = p1->turnaroundTime / p1->serviceTime;
	printf("ID      ����ʱ��  ��ʼʱ�� ����ʱ�� ���ʱ�� ��תʱ��  ��Ȩ��תʱ��\n");
	printf("%s%10.1f%10.1f%10.1f%10.1f%10.1f%10.2f\n", p1->id, p1->arriveTime, p1->startTime, p1->serviceTime, p1->finishTime, p1->turnaroundTime, p1->weightedTurnaroundTime);
}

void fcfs()//�ҵ���ǰδ��ɵĽ���
{
	int i;
	p = head;
	for (i = 0; i < n; i++)
	{
		if (p->state == 'F')
		{
			q = p;//��ǵ�ǰδ��ɵĽ���
			run_fcfs(p);
		}
		p = p->next;
	}

}

void getInfo()//��ȡ������Ϣ����������
{
	int num;
	printf("\n ��ҵ����:");
	scanf("%d", &n);

	for (num = 0; num < n; num++)
	{
		p = (pcb*)malloc(sizeof(pcb));//�����½��
		printf("��������:\nID ������ ����ʱ�� ����ʱ��\n");
		scanf("%s\t%s\t%f\t%f", &p->id, &p->name, &p->arriveTime, &p->serviceTime);
		if (head == NULL)
		{
			head = p;
			q = p;
			time = p->arriveTime;
		}
		p->next = NULL;//�½����β���������
		p->startTime = 0;//δ�½���еĳ�Ա��ֵ
		p->finishTime = 0;
		p->turnaroundTime = 0;
		p->weightedTurnaroundTime = 0;
		p->state = 'F';
		q->next = p;//β���ָ���½��
		q = p;//qָ���µ�β���
	}
}


void main()
{
	printf("�����㷨ģ��");
	getInfo();
	p = head;
	fcfs();
}