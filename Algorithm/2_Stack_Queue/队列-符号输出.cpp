#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE	20

typedef char Elemtype;

typedef struct qNode {
	Elemtype val;
	struct qNode *next;
}qNode;

typedef struct Queue {
	qNode *front;
	qNode *rear;
}Queue;

static void InitQueue( Queue *q )
{
	if( !(q->rear = q->front = (qNode *)malloc(sizeof(qNode))) )
	{
		exit(0);
	}
	q->front->next = NULL;
}

static void Insert( Queue *q, Elemtype e )
{
	qNode *p;
	if( !(p = (qNode *)malloc(sizeof(qNode))) )
	{
		exit(0);
	}
	p->val = e;
	p->next = NULL;
	q->rear->next = p;
	q->rear = p;

}

static void Delete( Queue *q, Elemtype *e )
{
	qNode *p;
	if( q->rear == q->front )
	{
		return;
	}
	p = q->front->next;
	*e = p->val;
	q->front->next = p->next;
	free(p);
	if( p == q->rear )					//没有元素啦
	{
		q->rear = q->front;
	}
}

static void Destroy( Queue *q )
{
	qNode *p;
	while( p = q->front )
	{
		q->front = p->next;
		free(p);
	}
	q->front = q->rear = NULL;
}

int main()
{
	Queue q;
	char c, d;
	int cnt = 0, i, j;
	InitQueue(&q);
	
	printf("输入若干‘+’或‘-’：\n\n");
	while( (c = getchar()) != '\n' )
	{
		Insert(&q, c);
		cnt++;
	}
	
	printf("\n\n");
	for( i=cnt; i > 0; i-- )
	{
		for( j=cnt-i; j > 0; j-- )
		{
			printf(" ");
		}
		Delete(&q, &c);
		printf("%c ", c);
		for( j=i-1; j > 0; j-- )
		{
			Delete(&q, &d);
			printf("%c ", d);
			c == d ? Insert(&q, '+'):Insert(&q, '-');
			c = d;
		}
		printf("\n");
	}
	Destroy(&q);
	return 0;
}