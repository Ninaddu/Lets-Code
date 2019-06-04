#include <iostream>
#include <stdlib.h>
#include <math.h>
#define INITSIZE	20
#define SIZEINCREMENT	10
using namespace std;

typedef char Elemtype;

typedef struct stack {
	int *base;
	int *top;
	int size;
}Sqstack;

static void InitStack( Sqstack *S )
{
	if( !(S->base = (int *)malloc(sizeof(int) * INITSIZE)) )
	{
		exit(0);
	}
	S->top = S->base;
	S->size = INITSIZE;
}

static void Push( Sqstack *S, int e )
{
	if( S->top - S->base == S->size )
	{
		S->base = (int *)realloc(S->base, sizeof(int) * (S->size + SIZEINCREMENT));
		S->size += SIZEINCREMENT;
	}
	*(S->top) = e;
	S->top++;
}

static void Pop( Sqstack *S, int *e )
{
	if( S->top == S->base )
	{
		return;
	}
	*e = *(--S->top);
}

static int Length( Sqstack S )
{
	return (S.top - S.base);
}

static void Destroy( Sqstack *S )
{
	free(S->base);
}

static void Tranverse( int str[], int cnt )
{
	Sqstack S1, S2;
	InitStack(&S1);
	InitStack(&S2);
	
	for( int i=0; i < cnt; i++ )			//���������ȫ��ѹջ
	{
		Push(&S1, str[i]);
	}
	
	int j = 0, sum = 0;
	int e;
	for( i=0; i < cnt; i++, j++ )	//4λ��S1��ջ�������Ӧ16����������ջS2
	{
		Pop(&S1, &e);
		sum += (e * (int)pow(2.0, j));
		if( 3 == j )
		{
			Push(&S2, sum);
			j = -1;
			sum = 0;
		}
	}	
	if( 0 != cnt%4 )						//���µ�Ҳ��ջ�����cnt������4���������Ѿ�ȫ����ջ������push
	{
		Push(&S2, sum);
	}
	
	cout << "\nת��ʮ�����ƣ�";
	for( int len = Length(S2); len > 0; len-- )
	{
		Pop(&S2, &e);
		cout << hex << e;
	}
	cout << endl;
	
	Destroy(&S1);
	Destroy(&S2);
}

int main()
{
	cout << "����������������֣�";
	int str[INITSIZE] = {'\0'};
	Elemtype ch;
	int cnt = 0;
	while( (ch = cin.get()) != '\n' )
	{
		str[cnt++] = ch - '0';
	}
	Tranverse(str, cnt);
	return 0;
}

