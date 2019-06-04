#include <iostream>
#include <stdlib.h>
#include <new>
#include "HfmTable.h"
#include "HfmTree.h"


/***************************************************************************
*功能：递归找到所有叶子，创建密码表元素储存叶子data和路线
*参数：树节点，路线，目前记录的路线标记数量
*返回值：-OK  -ERROR
*过程：通过递归找到叶子，并记录下每个叶子的路线，1-左，2-右
****************************************************************************/

Status Tranverse(HfmCode* c, pNode p, char* code, int n)
{
	if (NULL == p->lchild && NULL == p->rchild)				//找到了叶子节点
	{
		hCode* cnode;
		try
		{
			cnode = new hCode;
		}
		catch (std::bad_alloc)
		{
			std::cout << "\n编译失败...\n原因：内存告急。解决方案：向上级申请升级存储器！" << "\n\n";
			exit(0);
		}

		cnode->data = p->data;								//密码表元素中data存放树节点元素，code存储路线
		try
		{
			cnode->code = new char[n + 1];
		}
		catch (std::bad_alloc)
		{
			std::cout << "\n编译失败...\n原因：内存告急。解决方案：向上级申请升级存储器！" << "\n\n";
			exit(0);
		}
		for (int i = 0; i < n; i++)
		{
			cnode->code[i] = code[i];
		}
		cnode->code[n] = '\0';

		/*将密码表元素插入链表中，索引总是指向第一个元素*/
		if (NULL == c->codeptr)
		{
			c->codeptr = cnode;
			cnode->next = NULL;
		}
		else
		{
			cnode->next = c->codeptr;
			c->codeptr = cnode;
		}
		return OK;
	}

	/*如果不是叶子节点，就继续向下递归，向左路线记录加0，向右加1*/
	char code0[MAXCODE];
	for (int j = 0; j < MAXCODE; j++)							//复制前面的路线
	{
		code0[j] = code[j];
	}

	if (p->lchild)
	{
		code0[n] = '0';
		Tranverse(c, p->lchild, code0, n + 1);
	}

	if (p->rchild)
	{
		code0[n] = '1';
		Tranverse(c, p->rchild, code0, n + 1);
	}
}



/***************************************************************************
*功能：打印HfmCode
*参数：HfmCode索引
*返回值：无
****************************************************************************/

void Prnt(HfmCode* c)
{
	hCode* p = c->codeptr;
	std::cout << "明文 -> 密码" << "\n";
	while (p)
	{
		std::cout << p->data << " -> ";
		std::cout << p->code << "\n";
		p = p->next;
	}
	std::cout << "\n\n";
}