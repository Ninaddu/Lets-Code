#include <stdio.h>
#include <stdlib.h>
#define OK		1
#define ERROR	0


typedef int Status;
typedef struct ListLine {
	int code;
	int num;
	struct ListLine *next;
}Node, *NodeList;

Status InitList( NodeList *L )
{
	*L = (NodeList)malloc(sizeof(Node));
	if( !*L )
	{
		exit(0);
	}
	(*L)->next = NULL;
	return OK;
}

Status CreateList( NodeList *L, int n )
{
	if( !*L )
	{
		return ERROR;
	}
	NodeList p, q;
	for( int i=0; i < n; i++ )
	{
		p = (Node *)malloc(sizeof(Node));
		if( !p )
		{
			exit(0);
		}
		printf("\n输入第%d个人的密码：", i+1);
		scanf("%d", &p->code);
		p->num = i+1;
		if( !(*L)->next )
		{
			(*L)->next = p;
			p->next = p;
		}
		else
		{
			p->next = q->next;
			q->next = p;
		}
		q = p;
	}
	printf("完成单项循环链表的创建！\n");
	return OK;
}

Status PrintList( NodeList *L, int n )
{
	for( int i=0; i < n; i++ )
	{
		*L = (*L)->next;
		printf("\n第%d个人，密码：%d\n", i+1, (*L)->code);		
	}
	printf("\n");
	return OK;
}

Status DeleteList( NodeList *L, int m )
{
	NodeList p, q, temp;
	int cnt;
	if( !*L || !(*L)->next )
	{
		return ERROR;
	}
	p = q = (*L)->next;
	while( q->next != p  )			//让q指针跑到链表表尾，使next指向p（如果M为1，第一个同学就死掉，最后一个同学要接上）
	{
		q = q->next;
	}
	while( p->next != p )			//只剩一个元素时，p->next指向自己
	{
		for( cnt=1; cnt < m; cnt++ )
		{
			q = p;
			p = p->next;
		}
		printf("\n第%d个人出列，密码为%d\n", p->num, p->code);
		m = p->code;
		temp = p;
		p = p->next;
		q->next = p;
		free(temp);	
	}
	free(p);
	return OK;
} 

Status DestroyList( NodeList *L )
{
	free(*L);
	return OK;
}

int main()
{
	NodeList L = NULL;
	int n, m;
	InitList(&L);
	printf("请输入人数n：" );
	scanf("%d", &n);
	printf("和初始密码m：");
	scanf("%d", &m);
	CreateList(&L, n);
	printf("\n-----------循环链表原始打印-----------\n");
	PrintList(&L, n);
	printf("\n-----------删除出队情况打印-----------\n");
	DeleteList(&L, m);
	//DestroyList(&L);
	return 0;
}