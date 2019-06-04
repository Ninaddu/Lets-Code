#include <iostream>
#include <new>
#include "HfmTable.h"
#include "HfmTree.h"


/***************************************************************************
*功能：初始化Huffman Table索引
*参数：表索引指针的指针
*返回值：完成状态-OK -ERROR
****************************************************************************/

Status InitTable(HfmTable** h)
{
	try 
	{
		*h = new HfmTable;
	}
	catch (std::bad_alloc)
	{
		std::cout << "\n编译失败...\n原因：内存告急。解决方案：向上级申请升级存储器！" << "\n\n";
		exit(0);
	}

	(*h)->firptr = NULL;
	(*h)->cnt = 0;
	std::cout << "Huffman Table 索引创建成功！" << "\n\n";
	return OK;
}



/***************************************************************************
*功能：按照frequency将元素插入Huffman Table
*参数：表索引指针，元素中val地址(树节点)，字符frequency
*返回值：完成状态-OK -ERROR
****************************************************************************/

Status Insert(HfmTable* h, pNode *e, int freq)
{
	htNode* p;							//定义并创建一个表元素
	try 
	{
		p = new htNode;
	}
	catch (std::bad_alloc)
	{
		std::cout << "\n编译失败...\n原因：内存告急。解决方案：向上级申请升级存储器！" << "\n\n";
		exit(0);
	}
	p->val = *e;
	p->frequency = freq;
	p->next = NULL;

	if (NULL == h->firptr)				//若索引指针指向空，表示表内无任何元素，直接插入
	{
		h->firptr = p;
		++(h->cnt);
		return OK;
	}

	/*若表中已经有元素，则分为三种情况：
	①插入字符的frequency <= 最小frequency，则加入链表首元素，改变frequency指向
	②插入字符freq在链表中，直接插入即可
	③插入字符freq比所有元素都大，在末尾插入并使next指向NULL*/

	htNode* first = h->firptr;			//临时指代h->firptr，提高代码可读性
	if (freq <= first->frequency)
	{
		p->next = first;				//用p替换first指向的第一个元素
		h->firptr = p;
	}
	else
	{
		htNode* iterator = first->next;	//以迭代器寻找比p->freq更大的frequency
		htNode* temp = first;			//临时指针，用于在插入时连接链表
		while (iterator)				//在Table已有元素中寻找frequency >= p->freq的位置并插入
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
		if (NULL == iterator)			//迭代器已经到表尾，并没有找到比p->freq大的frequency，需在最后插入
		{
			temp->next = p;
			p->next = iterator;
		}
	}
	++(h->cnt);
	return OK;
}



/***************************************************************************
*功能：根据索引取出表中第一个元素
*参数：表索引指针
*返回值：Huffman Table首元素地址
****************************************************************************/

htNode* Get(HfmTable* h)
{
	if (0 == h->cnt)					//Table已空，则返回空
	{
		return NULL;
	}
	htNode* p = h->firptr;			
	h->firptr = p->next;
	--(h->cnt);
	return p;
}

