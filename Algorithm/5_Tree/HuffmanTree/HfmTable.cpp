#include <iostream>
#include <new>
#include "HfmTable.h"
#include "HfmTree.h"


/***************************************************************************
*���ܣ���ʼ��Huffman Table����
*������������ָ���ָ��
*����ֵ�����״̬-OK -ERROR
****************************************************************************/

Status InitTable(HfmTable** h)
{
	try 
	{
		*h = new HfmTable;
	}
	catch (std::bad_alloc)
	{
		std::cout << "\n����ʧ��...\nԭ���ڴ�漱��������������ϼ����������洢����" << "\n\n";
		exit(0);
	}

	(*h)->firptr = NULL;
	(*h)->cnt = 0;
	std::cout << "Huffman Table ���������ɹ���" << "\n\n";
	return OK;
}



/***************************************************************************
*���ܣ�����frequency��Ԫ�ز���Huffman Table
*������������ָ�룬Ԫ����val��ַ(���ڵ�)���ַ�frequency
*����ֵ�����״̬-OK -ERROR
****************************************************************************/

Status Insert(HfmTable* h, pNode *e, int freq)
{
	htNode* p;							//���岢����һ����Ԫ��
	try 
	{
		p = new htNode;
	}
	catch (std::bad_alloc)
	{
		std::cout << "\n����ʧ��...\nԭ���ڴ�漱��������������ϼ����������洢����" << "\n\n";
		exit(0);
	}
	p->val = *e;
	p->frequency = freq;
	p->next = NULL;

	if (NULL == h->firptr)				//������ָ��ָ��գ���ʾ�������κ�Ԫ�أ�ֱ�Ӳ���
	{
		h->firptr = p;
		++(h->cnt);
		return OK;
	}

	/*�������Ѿ���Ԫ�أ����Ϊ���������
	�ٲ����ַ���frequency <= ��Сfrequency�������������Ԫ�أ��ı�frequencyָ��
	�ڲ����ַ�freq�������У�ֱ�Ӳ��뼴��
	�۲����ַ�freq������Ԫ�ض�����ĩβ���벢ʹnextָ��NULL*/

	htNode* first = h->firptr;			//��ʱָ��h->firptr����ߴ���ɶ���
	if (freq <= first->frequency)
	{
		p->next = first;				//��p�滻firstָ��ĵ�һ��Ԫ��
		h->firptr = p;
	}
	else
	{
		htNode* iterator = first->next;	//�Ե�����Ѱ�ұ�p->freq�����frequency
		htNode* temp = first;			//��ʱָ�룬�����ڲ���ʱ��������
		while (iterator)				//��Table����Ԫ����Ѱ��frequency >= p->freq��λ�ò�����
		{
			if (p->frequency <= iterator->frequency)	
			{
				temp->next = p;
				p->next = iterator;
				break;
			}
			temp = iterator;
			iterator = iterator->next;
		}
		if (NULL == iterator)			//�������Ѿ�����β����û���ҵ���p->freq���frequency������������
		{
			temp->next = p;
			p->next = iterator;
		}
	}
	++(h->cnt);
	return OK;
}



/***************************************************************************
*���ܣ���������ȡ�����е�һ��Ԫ��
*������������ָ��
*����ֵ��Huffman Table��Ԫ�ص�ַ
****************************************************************************/

htNode* Get(HfmTable* h)
{
	if (0 == h->cnt)					//Table�ѿգ��򷵻ؿ�
	{
		return NULL;
	}
	htNode* p = h->firptr;			
	h->firptr = p->next;
	--(h->cnt);
	return p;
}

