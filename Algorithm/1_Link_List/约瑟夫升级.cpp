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
		printf("\n�����%d���˵����룺", i+1);
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
	printf("��ɵ���ѭ������Ĵ�����\n");
	return OK;
}

Status PrintList( NodeList *L, int n )
{
	for( int i=0; i < n; i++ )
	{
		*L = (*L)->next;
		printf("\n��%d���ˣ����룺%d\n", i+1, (*L)->code);		
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
	while( q->next != p  )			//��qָ���ܵ������β��ʹnextָ��p�����MΪ1����һ��ͬѧ�����������һ��ͬѧҪ���ϣ�
	{
		q = q->next;
	}
	while( p->next != p )			//ֻʣһ��Ԫ��ʱ��p->nextָ���Լ�
	{
		for( cnt=1; cnt < m; cnt++ )
		{
			q = p;
			p = p->next;
		}
		printf("\n��%d���˳��У�����Ϊ%d\n", p->num, p->code);
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
	printf("����������n��" );
	scanf("%d", &n);
	printf("�ͳ�ʼ����m��");
	scanf("%d", &m);
	CreateList(&L, n);
	printf("\n-----------ѭ������ԭʼ��ӡ-----------\n");
	PrintList(&L, n);
	printf("\n-----------ɾ�����������ӡ-----------\n");
	DeleteList(&L, m);
	//DestroyList(&L);
	return 0;
}