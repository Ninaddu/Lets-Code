#include <iostream>
#include <new>
#include "HfmTable.h"
#include "HfmTree.h"


/************************************************************************
*功能：销毁Huffman树
*参数：树根节点
*返回值：返回状态 -OK  -ERROR
*************************************************************************/

Status Tree_Destroy(pNode *p)
{
	if (*p)				//叶子节点delete后返回
	{
		Tree_Destroy(&(*p)->lchild);
		Tree_Destroy(&(*p)->rchild);
		delete *p;
		return OK;
	}
}



/************************************************************************
*功能：销毁Huffman密码链表
*参数：链表索引指针
*返回值：返回状态 -OK  -ERROR
*************************************************************************/

Status CodeLink_Destroy(HfmCode** c)
{
	hCode* p, *q;
	p = (*c)->codeptr;
	while (NULL != p)
	{
		q = p->next;
		delete(p->code);
		delete p;
		p = q;
	}
	delete* c;
	*c = NULL;
	return OK;
}