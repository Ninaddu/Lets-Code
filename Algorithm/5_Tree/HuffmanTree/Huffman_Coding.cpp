#include <iostream>
#include <stdlib.h>
#include <new>
#include <windows.h>
#include "HfmTable.h"
#include "HfmTree.h"


/***************************************************************************
*���ܣ�����Huffman��
*������������ַ���
*����ֵ��Huffman����ָ��
*���̣�1�����㴫���ַ�����ÿ���ַ��ĳ���Ƶ�ʣ��Դ�С�����˳�����Huffman����
*	  2����������ָ����Ԫ�أ�Insert�����������ַ�Ԫ�أ��������Ĵ���
*	  3���������ڵ㣬��������Get����Ԫ�طֱ�Ϊ���Һ��ӣ��ڵ�Ƶ����������Ƶ��֮�ͣ�����Ƶ�ʴ�СInsert������
*	  4����������������������������ָ��
****************************************************************************/

hTree* HuffmanTree(Elemtype* str)
{
	int* frequency = new int[256];
	memset(frequency, 0, sizeof(int) * 256);

	int i = 0;
	for (i = 0; str[i] != '\n'; i++)			//���ַ�ASCIIΪС�꣬����ÿ���ַ����ִ���
	{
		++frequency[str[i]];
	}	

	HfmTable* h;								//���岢��ʼ��fhmtable����
	InitTable(&h);	
	Sleep(1000);

	i = 0;
	for (i = 0; i < 256; i++)					//�����ֹ����ַ���frequency>0������HfmTable
	{
		if (frequency[i])
		{
			pNode p;							//���������ַ���Ҷ�ӽڵ�
			try
			{
				p = new tNode;
			}
			catch (std::bad_alloc)
			{
				std::cout << "\n����ʧ��...\nԭ���ڴ�漱��������������ϼ����������洢����" << "\n\n";
				exit(0);
			}
			p->data = (Elemtype)i;
			p->lchild = NULL;
			p->rchild = NULL;
			Insert(h, &p, frequency[i]);		//��Ҷ�ӽڵ����Table��
		}
	}
	std::cout << "����Huffman Table�ɹ���Ŀǰ������������Ϊ30%" << "\n\n";
	Sleep(1000);
	delete(frequency);							//�ַ�Ƶ����Ϣ�Ѽ�¼��Table�У�������

	
	/*��������ʼ������*/
	while( h->cnt > 1)
	{
		pNode p;
		try
		{
			p = new tNode;				//�������ڵ�
		}
		catch (std::bad_alloc)
		{
			std::cout << "\n����ʧ��...\nԭ���ڴ�漱��������������ϼ����������洢����" << "\n\n";
			exit(0);
		}
		htNode* q1 = Get(h);
		htNode* q2 = Get(h);
		p->data = q1->frequency + q2->frequency;		//�µ����ڵ���data�������frequency֮�ͣ����ݴ˲���table
		p->lchild = q1->val;
		p->rchild = q2->val;
		Insert(h, &p, p->data);
		delete(q1);
		delete(q2);
	}

	hTree* t;
	try
	{
		t = new hTree;						//���������ڵ�
	}
	catch (std::bad_alloc)
	{
		std::cout << "\n����ʧ��...\nԭ���ڴ�漱��������������ϼ����������洢����" << "\n\n";
		exit(0);
	}
	htNode* p = Get(h);						//���һ��TableԪ�ص������������ڵ㣬��������
	t->root = p->val;
	delete(p);
	delete(h);								//Table����Ҳ�ͷ�

	std::cout << "�ѳɹ�������Huffman Tree��Ŀǰ����Ϊ70%����ϲ�ɺؿɿڿ��֣�" << "\n\n";
	Sleep(1000);
	return t;
}



/***************************************************************************
*���ܣ��������ܱ�
*������Huffman����ָ�룬�ַ�����
*����ֵ�����������ָ��
*���̣�����Tranverse����Ҷ�ӣ�����Prnt��ӡ�����
****************************************************************************/

HfmCode* Coding( hTree *t )
{
	pNode p = t->root;
	HfmCode* c;									//���������
	try
	{
		c = new HfmCode;
		c->codeptr = NULL;
	}
	catch (std::bad_alloc)
	{
		std::cout << "\n����ʧ��...\nԭ���ڴ�漱��������������ϼ����������洢����" << "\n\n";
		exit(0);
	}
	char code[MAXCODE];
	memset(code, NULL, sizeof(code));
	Tranverse(c, p, code, 0);

	std::cout << "����Huffman�����ɹ����������100%" << "\n\n";
	Sleep(1000);
	return c;
}



/************************************************************************
*���ܣ�����������ҵ����Ķ�Ӧ�����벢���
*���������������ָ�룬��Ҫ��ѯ������
*����ֵ����
*************************************************************************/

void Search(HfmCode* c, Elemtype* str)
{
	hCode* p;
	for (int i = 0; str[i] != '\n'; i++)				//������������Ԫ�ؿ�ʼ����������ҵ������
	{
		p = c->codeptr;	
		while (p && (p->data != str[i]))				//ѭ��ֱ�� pΪNULL �� �ҵ�����
		{
			p = p->next;
		}

		if (p)											//p��ΪNULL�����ʱp->dataΪ���ģ����
		{
			static int flag = 0;
			if (!flag)
			{
				std::cout << "\n\n���ĺ�������ս�����£�\n\n���� -> ����\n" << "\n";
				flag++;
			}
			std::cout << p->data << " -> " << p->code << "\n";
		}
		else
		{
			std::cout << "����������" << "�� " << i+1 << " ���ַ� " << str[i] << " Ϊ�Ƿ��ַ���" << "\n";
		}
	}
	std::cout << "\n\n";
}



/************************************************************************
*���ܣ��������������
*������Huffman��������Ҫ���������
*����ֵ����
*************************************************************************/

void DeCoding(hTree* t, char* str)
{
	std::cout << "\n\n���������£�\n���� -> ����\n" << "\n";
	pNode p = t->root;
	char code[MAXCODE];								//��¼ĳ�����ĵ�����
	memset(code, '\0', sizeof(code));
	int j = 0;
	for (int i = 0; str[i] != '\n'; i++)		  //�Բ�ѯ����Ϊ·�ߣ��ҵ�Ҷ�ӽڵ㲢������ģ�Ȼ��Ӹ���ʼѰ����һ��
	{
		code[j++] = str[i];
		('0' == str[i]) ? p = p->lchild : p = p->rchild;
		if (NULL == p->lchild && NULL == p->rchild)
		{
			std::cout << code << " -> " << p->data << "\n";
			p = t->root;							//���´�������ʼ���룬�����¼������գ����¼�¼
			memset(code, '\0', sizeof(code));			
			j = 0;
		}
	}
	std::cout << "\n\n";
}



/************************************************************************
*���ܣ�����Huffman���������
*������Huffman����ָ���ָ�룬���������ָ���ָ��
*����ֵ����
*************************************************************************/

Status Destroy(hTree** t, HfmCode** c)
{
	pNode p = (*t)->root;
	if (Tree_Destroy(&p))
	{
		delete* t;
		std::cout << "Huffman Tree�ѳɹ����٣�" << "\n\n";
	}
	Sleep(1000);

	if (CodeLink_Destroy(c))
	{
		std::cout << "Huffman CodeList�ѳɹ����٣�" << "\n\n";
	}
	Sleep(1000);
	return OK;
}
