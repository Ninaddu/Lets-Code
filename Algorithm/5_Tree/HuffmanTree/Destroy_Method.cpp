#include <iostream>
#include <new>
#include "HfmTable.h"
#include "HfmTree.h"


/************************************************************************
*���ܣ�����Huffman��
*�����������ڵ�
*����ֵ������״̬ -OK  -ERROR
*************************************************************************/

Status Tree_Destroy(pNode *p)
{
	if (*p)				//Ҷ�ӽڵ�delete�󷵻�
	{
		Tree_Destroy(&(*p)->lchild);
		Tree_Destroy(&(*p)->rchild);
		delete *p;
		return OK;
	}
}



/************************************************************************
*���ܣ�����Huffman��������
*��������������ָ��
*����ֵ������״̬ -OK  -ERROR
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