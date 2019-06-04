#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define OK		1
#define ERROR	0

typedef int Status;
typedef int Elemtype;

typedef struct List {
	Elemtype data;
	struct List *next;
}ListLine, *pList;

//初始化链表
Status InitList(pList *L)
{
	*L = (pList)malloc(sizeof(ListLine));
	if( !*L )
	{
		exit(0);
	}
	(*L)->next = NULL;
	return OK;
}

Status Create(pList *L, int size)
{
	pList p, q;
	int i;
	if( 0 == size )
	{
			printf("输入元素数量不能为0！");
			return ERROR;
	}
	srand(time(0));
	q = *L;
	for( i=0; i < size; i++ )
	{
		p = (pList)malloc(sizeof(ListLine));
		if(!p)
		{
			exit(0);
		}
		p->data = rand()%100;
		q->next = p;
		q = p;
	}
	p->next = NULL;
	return OK;
}

//计算链表长度
int ListLength(pList *L)
{
	pList p = (*L)->next;
	int len = 0;
	while( p )
	{
		len++;
		p = p->next;
	}
	return len;
}

Status Show(pList *L)
{
	pList p = (*L)->next;
	while( p )
	{
		printf("%d -> ", p->data);
		p = p->next;
	}
	printf("^\n\n");
	return OK;
}

int MidSearch(pList *L)
{
	if(!(*L) || !((*L)->next))	return ERROR;
	pList q, s;				//快慢指针
	q = s = *L;
	while( q && q->next )
	{
		q = q->next->next;
		s = s->next;
	}
	return (s->data);
}


int main()
{
	pList L;
	int opp, size;
	int count, mid;
	InitList(&L);
	count = ListLength(&L);
	printf("初始化L后，LishLength(0) = %d\n\n", count);
	printf("1.查看链表\n2.创建链表（尾插法）\n3.链表长度\n4.中间结点值\n0.退出\n请选择你的操作\n\n");
	scanf("%d", &opp);
	while(opp != 0)
	{
		switch(opp)
		{
			case 1:
				Show(&L);
				break;
			case 2:
				printf("输入创建链表的长度");
				scanf("%d", &size);
				Create(&L, size);
				Show(&L);
				break;
			case 3:
				count = ListLength(&L);
				printf("ListLength(L) = %d\n", count);
				break;
			case 4:
				mid = MidSearch(&L);
				printf("链表中间结点的值为：%d\n", mid);
				break;
			case 0:
				exit(0);
		}
		printf("\n");
		scanf("%d", &opp);
	}
	return 0;
}