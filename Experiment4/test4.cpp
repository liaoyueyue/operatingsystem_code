#include <iostream>
using namespace std;
#define Bsize 3
#define Psize 20

//LRU�㷨
struct pageInfor
{
	int content; //ҳ���
	int timer;	//�����ʱ��
};

class PRA
{
public:
	PRA(void);
	int findSpace(void);	//�����Ƿ��п����ڴ�
	int findExitst(int curpage);	//�����ڴ��Ƿ��и�ҳ��
	int findReplace(void);	//�����û���ҳ��
	void display(void);	//��ʾ
	void LRU(void);	//LRU�㷨
	void BlockClear();	//BLOCK�ָ�
	pageInfor* block;	//�����
	pageInfor* page;	//ҳ��Ŵ�
};

PRA::PRA(void)
{
	int QString[20] = { 4, 0, 3, 2, 1, 5, 8, 4, 2, 3, 0, 3, 2, 1, 6, 8, 9, 7, 0, 1 };
	block = new pageInfor[Bsize];
	for (int i = 0; i < Bsize; i++)
	{
		block[i].content = -1;
		block[i].timer = 0;
	}
	page = new pageInfor[Psize];

	for (int j = 0; j < Psize; j++)
	{
		page[j].content = QString[j];
		page[j].timer = 0;
	}
}

int PRA::findSpace(void)
{
	for (int i = 0; i < Bsize; i++)
	{
		if (block[i].content == -1)
			return i;	//�ҵ������ڴ棬����BLOCK��λ��
		return -1;
	}
}

int PRA::findExitst(int curpage)
{
	for(int i=0; i<Bsize; i++)
		if (block[i].content == page[curpage].content)
			return i;	//�ҵ��ڴ����и�ҳ�棬����BLOCK��λ��
	return -1;
} 

int PRA::findReplace(void)
{
	int pos = 0;
	for (int i = 0; i < Bsize; i++)
	{
		if (block[i].timer >= block[pos].timer)
			pos = i;	//�ҵ�Ӧ���û�ҳ�棬����BLOCK��λ��
		return pos;
	}
}

void PRA::display(void)
{
	for (int i = 0; i < Bsize; i++)
	{
		if (block[i].content != -1)
		cout << block[i].content << " ";
		cout<<endl;
	}
}

void PRA::LRU(void)
{
	int exist, space, position;
	for (int i = 0; i < Psize; i++)
	{
		exist = findExitst(i);
		if (exist != -1)
		{
			cout << "��ȱҳ" << endl;
			block[exist].timer = -1;	//�ָ����ڵĲ��շ��ʹ���BLOCK��ҳ�棬����timerΪ-1
		}
		else
		{
			space = findSpace();
			if (space != -1)
			{
				block[space].content = page[i].content;
				block[space].timer = page[i].timer;
				display();
			}
			else
			{
				position = findReplace();
				block[space].content = page[i].content;
				block[space].timer = page[i].timer;
				display();
			}
		}
		for (int j = 0; j < Bsize; j++)
		{
			block[j].timer++;
		}
	}
}

void PRA::BlockClear()
{
	for (int i = 0; i < Bsize; i++)
	{
		block->content = -1;
		block->timer = 0;
	}
}

int main(void)
{
	cout << "----------------ҳ���û��㷨----------------" << endl;
	cout << "ҳ������ô���4, 0, 3, 2, 1, 5, 8, 4, 2, 3, 0, 3, 2, 1, 6, 8, 9, 7, 0, 1" << endl;
	int select;
	PRA test;
	cout << "LRU�㷨�������: " << endl;
	test.LRU();
	test.BlockClear();
	cout << "--------------------------------" << endl;
}