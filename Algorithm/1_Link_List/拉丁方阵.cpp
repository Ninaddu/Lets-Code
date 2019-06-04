#include <stdio.h>
#include <stdlib.h>

typedef struct ListLine{
	int val;
	struct ListLine *next;
}ListNode, *PNodeList;

void CreateList( PNodeList *L, int n )
{
	PNodeList p, q;
	*L = (PNodeList)malloc(sizeof(ListNode));			//ͷָ��
	(*L)->next = NULL;
	for( int i=1; i <= n; i++ )
	{
		p = (PNodeList)malloc(sizeof(ListNode));
		p->val = i;
		if( (*L)->next == NULL )
		{
			(*L)->next = q = p;
		}
		else
		{
			p->next = q->next;
		}
		q->next = p;
		q = p;
	}
}

void Latin( PNodeList *L, int *latin, int n )
{
	PNodeList p = (*L)->next;
	for( int i=0; i < n; i++ )				//ѭ��n�Σ���n��
	{
		for( int j=0; j < n; j++ )
		{
			*(latin+n*i+j) = p->val;
			p = p->next;
		}
		p = p->next;
	}
}

void PrntLatin( int *latin, int n )
{
	printf("\n�����������\n\n");
	for( int i=0; i < n; i++ )
	{
		for( int j=0; j < n; j++ )
		{
			printf("%d ", *(latin+n*i+j));
		}
		printf("\n");
	}
}

int main()
{
	const int MAXIMUM = 1000;
	PNodeList L;
	int latin[MAXIMUM] ;			//��Ϊ������Ҫ���룬���ڴ�����ά���������ɿռ��˷ѣ���һά���ּ�¼��ά����
	int n;
	printf("�����������������n�����Ϊ100����");
	scanf("%d", &n);
	while(1)
	{
		if(n <= 100 && n > 0)	
		{	
			break;
		}
		else if(n <= 0)
		{
			printf("����n���Ϲ棬���������룺");
		}
		else
		{
			printf("����n�������������룺");
		}
		scanf("%d", &n);
	}
	CreateList (&L, n);
	Latin (&L, latin, n);
	PrntLatin (latin, n);
	return 0;
}