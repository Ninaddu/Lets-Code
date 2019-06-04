#include <iostream>
#include <stdlib.h>
#include <new>
#include "HfmTable.h"
#include "HfmTree.h"


/***************************************************************************
*���ܣ��ݹ��ҵ�����Ҷ�ӣ����������Ԫ�ش���Ҷ��data��·��
*���������ڵ㣬·�ߣ�Ŀǰ��¼��·�߱������
*����ֵ��-OK  -ERROR
*���̣�ͨ���ݹ��ҵ�Ҷ�ӣ�����¼��ÿ��Ҷ�ӵ�·�ߣ�1-��2-��
****************************************************************************/

Status Tranverse(HfmCode* c, pNode p, char* code, int n)
{
	if (NULL == p->lchild && NULL == p->rchild)				//�ҵ���Ҷ�ӽڵ�
	{
		hCode* cnode;
		try
		{
			cnode = new hCode;
		}
		catch (std::bad_alloc)
		{
			std::cout << "\n����ʧ��...\nԭ���ڴ�漱��������������ϼ����������洢����" << "\n\n";
			exit(0);
		}

		cnode->data = p->data;								//�����Ԫ����data������ڵ�Ԫ�أ�code�洢·��
		try
		{
			cnode->code = new char[n + 1];
		}
		catch (std::bad_alloc)
		{
			std::cout << "\n����ʧ��...\nԭ���ڴ�漱��������������ϼ����������洢����" << "\n\n";
			exit(0);
		}
		for (int i = 0; i < n; i++)
		{
			cnode->code[i] = code[i];
		}
		cnode->code[n] = '\0';

		/*�������Ԫ�ز��������У���������ָ���һ��Ԫ��*/
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

	/*�������Ҷ�ӽڵ㣬�ͼ������µݹ飬����·�߼�¼��0�����Ҽ�1*/
	char code0[MAXCODE];
	for (int j = 0; j < MAXCODE; j++)							//����ǰ���·��
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
*���ܣ���ӡHfmCode
*������HfmCode����
*����ֵ����
****************************************************************************/

void Prnt(HfmCode* c)
{
	hCode* p = c->codeptr;
	std::cout << "���� -> ����" << "\n";
	while (p)
	{
		std::cout << p->data << " -> ";
		std::cout << p->code << "\n";
		p = p->next;
	}
	std::cout << "\n\n";
}