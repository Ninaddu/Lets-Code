#include <iostream>
#include <stdlib.h>
#include <new>
#include <windows.h>
#include "HfmTable.h"
#include "HfmTree.h"


/***************************************************************************
*功能：创建Huffman树
*参数：输入的字符串
*返回值：Huffman数根指针
*过程：1、计算传入字符串中每个字符的出现频率，以从小到大的顺序插入Huffman链表
*	  2、链表索引指向首元素，Insert函数插入行字符元素，完成链表的创建
*	  3、创建树节点，从链表中Get两个元素分别为左右孩子，节点频率是两孩子频率之和，根据频率大小Insert链表中
*	  4、用树根索引整棵树，返回树根指针
****************************************************************************/

hTree* HuffmanTree(Elemtype* str)
{
	int* frequency = new int[256];
	memset(frequency, 0, sizeof(int) * 256);

	int i = 0;
	for (i = 0; str[i] != '\n'; i++)			//以字符ASCII为小标，计算每个字符出现次数
	{
		++frequency[str[i]];
	}	

	HfmTable* h;								//定义并初始化fhmtable索引
	InitTable(&h);	
	Sleep(1000);

	i = 0;
	for (i = 0; i < 256; i++)					//将出现过的字符（frequency>0）插入HfmTable
	{
		if (frequency[i])
		{
			pNode p;							//创建包涵字符的叶子节点
			try
			{
				p = new tNode;
			}
			catch (std::bad_alloc)
			{
				std::cout << "\n编译失败...\n原因：内存告急。解决方案：向上级申请升级存储器！" << "\n\n";
				exit(0);
			}
			p->data = (Elemtype)i;
			p->lchild = NULL;
			p->rchild = NULL;
			Insert(h, &p, frequency[i]);		//将叶子节点插入Table中
		}
	}
	std::cout << "创建Huffman Table成功！目前的密码编译进度为30%" << "\n\n";
	Sleep(1000);
	delete(frequency);							//字符频率信息已记录在Table中，可销毁

	
	/*接下来开始种树啦*/
	while( h->cnt > 1)
	{
		pNode p;
		try
		{
			p = new tNode;				//创建树节点
		}
		catch (std::bad_alloc)
		{
			std::cout << "\n编译失败...\n原因：内存告急。解决方案：向上级申请升级存储器！" << "\n\n";
			exit(0);
		}
		htNode* q1 = Get(h);
		htNode* q2 = Get(h);
		p->data = q1->frequency + q2->frequency;		//新的树节点中data存放子树frequency之和，根据此插入table
		p->lchild = q1->val;
		p->rchild = q2->val;
		Insert(h, &p, p->data);
		delete(q1);
		delete(q2);
	}

	hTree* t;
	try
	{
		t = new hTree;						//创建树根节点
	}
	catch (std::bad_alloc)
	{
		std::cout << "\n编译失败...\n原因：内存告急。解决方案：向上级申请升级存储器！" << "\n\n";
		exit(0);
	}
	htNode* p = Get(h);						//最后一个Table元素弹出，即树根节点，用树连接
	t->root = p->val;
	delete(p);
	delete(h);								//Table索引也释放

	std::cout << "已成功创建了Huffman Tree，目前进度为70%，可喜可贺可口可乐！" << "\n\n";
	Sleep(1000);
	return t;
}



/***************************************************************************
*功能：创建加密表
*参数：Huffman树根指针，字符个数
*返回值：密码表索引指针
*过程：传入Tranverse查找叶子，传入Prnt打印密码表
****************************************************************************/

HfmCode* Coding( hTree *t )
{
	pNode p = t->root;
	HfmCode* c;									//密码表索引
	try
	{
		c = new HfmCode;
		c->codeptr = NULL;
	}
	catch (std::bad_alloc)
	{
		std::cout << "\n编译失败...\n原因：内存告急。解决方案：向上级申请升级存储器！" << "\n\n";
		exit(0);
	}
	char code[MAXCODE];
	memset(code, NULL, sizeof(code));
	Tranverse(c, p, code, 0);

	std::cout << "创建Huffman密码表成功！编译完成100%" << "\n\n";
	Sleep(1000);
	return c;
}



/************************************************************************
*功能：根据密码表，找到明文对应的密码并输出
*参数：密码表索引指针，需要查询的明文
*返回值：无
*************************************************************************/

void Search(HfmCode* c, Elemtype* str)
{
	hCode* p;
	for (int i = 0; str[i] != '\n'; i++)				//从密码链表首元素开始逐个遍历，找到就输出
	{
		p = c->codeptr;	
		while (p && (p->data != str[i]))				//循环直到 p为NULL 或 找到明文
		{
			p = p->next;
		}

		if (p)											//p不为NULL，则此时p->data为明文，输出
		{
			static int flag = 0;
			if (!flag)
			{
				std::cout << "\n\n明文和密码对照结果如下：\n\n明文 -> 密码\n" << "\n";
				flag++;
			}
			std::cout << p->data << " -> " << p->code << "\n";
		}
		else
		{
			std::cout << "输入明文中" << "第 " << i+1 << " 个字符 " << str[i] << " 为非法字符！" << "\n";
		}
	}
	std::cout << "\n\n";
}



/************************************************************************
*功能：编译输入的密码
*参数：Huffman树根，需要编译的密码
*返回值：无
*************************************************************************/

void DeCoding(hTree* t, char* str)
{
	std::cout << "\n\n编译结果如下：\n密码 -> 明文\n" << "\n";
	pNode p = t->root;
	char code[MAXCODE];								//记录某个明文的密码
	memset(code, '\0', sizeof(code));
	int j = 0;
	for (int i = 0; str[i] != '\n'; i++)		  //以查询密码为路线，找到叶子节点并输出明文，然后从根开始寻找下一个
	{
		code[j++] = str[i];
		('0' == str[i]) ? p = p->lchild : p = p->rchild;
		if (NULL == p->lchild && NULL == p->rchild)
		{
			std::cout << code << " -> " << p->data << "\n";
			p = t->root;							//重新从树根开始编译，密码记录数组清空，重新记录
			memset(code, '\0', sizeof(code));			
			j = 0;
		}
	}
	std::cout << "\n\n";
}



/************************************************************************
*功能：销毁Huffman树和密码表
*参数：Huffman树根指针的指针，密码表索引指针的指针
*返回值：无
*************************************************************************/

Status Destroy(hTree** t, HfmCode** c)
{
	pNode p = (*t)->root;
	if (Tree_Destroy(&p))
	{
		delete* t;
		std::cout << "Huffman Tree已成功销毁！" << "\n\n";
	}
	Sleep(1000);

	if (CodeLink_Destroy(c))
	{
		std::cout << "Huffman CodeList已成功销毁！" << "\n\n";
	}
	Sleep(1000);
	return OK;
}
