#include <iostream>
using namespace std;
#define Bsize 3
#define Psize 20

//LRU算法
struct pageInfor
{
	int content; //页面号
	int timer;	//被访问标记
};

class PRA
{
public:
	PRA(void);
	int findSpace(void);	//查找是否有空闲内存
	int findExitst(int curpage);	//查找内存是否有该页面
	int findReplace(void);	//查找置换的页面
	void display(void);	//显示
	void LRU(void);	//LRU算法
	void BlockClear();	//BLOCK恢复
	pageInfor* block;	//物理块
	pageInfor* page;	//页面号串
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
			return i;	//找到空闲内存，返回BLOCK中位置
		return -1;
	}
}

int PRA::findExitst(int curpage)
{
	for(int i=0; i<Bsize; i++)
		if (block[i].content == page[curpage].content)
			return i;	//找到内存中有该页面，返回BLOCK中位置
	return -1;
} 

int PRA::findReplace(void)
{
	int pos = 0;
	for (int i = 0; i < Bsize; i++)
	{
		if (block[i].timer >= block[pos].timer)
			pos = i;	//找到应予置换页面，返回BLOCK中位置
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
			cout << "不缺页" << endl;
			block[exist].timer = -1;	//恢复存在的并刚访问过的BLOCK中页面，令其timer为-1
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
	cout << "----------------页面置换算法----------------" << endl;
	cout << "页面号引用串：4, 0, 3, 2, 1, 5, 8, 4, 2, 3, 0, 3, 2, 1, 6, 8, 9, 7, 0, 1" << endl;
	int select;
	PRA test;
	cout << "LRU算法结果如下: " << endl;
	test.LRU();
	test.BlockClear();
	cout << "--------------------------------" << endl;
}