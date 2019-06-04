#include <stdio.h>
#include <stdlib.h>

typedef struct ListLine{
	int val;
	struct ListLine *next;
}ListNode, *PNodeList;

void CreateList( PNodeList *L, int n )
{
	PNodeList p, q;
	*L = (PNodeList)malloc(sizeof(ListNode));			//头指针
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
	for( int i=0; i < n; i++ )				//循环n次，有n行
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
	printf("\n输出拉丁方正\n\n");
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
	int latin[MAXIMUM] ;			//因为长度需要输入，现在创建二维数组可能造成空间浪费，用一维数字记录二维即可
	int n;
	printf("请输入拉丁方阵阶数n（最大为100）：");
	scanf("%d", &n);
	while(1)
	{
		if(n <= 100 && n > 0)	
		{	
			break;
		}
		else if(n <= 0)
		{
			printf("输入n不合规，请重新输入：");
		}
		else
		{
			printf("输入n过大，请重新输入：");
		}
		scanf("%d", &n);
	}
	CreateList (&L, n);
	Latin (&L, latin, n);
	PrntLatin (latin, n);
	return 0;
}