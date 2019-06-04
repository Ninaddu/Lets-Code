// 1+2-(4*5/6+(7-8)*3)*9/10-2  ->  1 2 + 4 5 * 6 / 7 8 - 3 * + 9 * 10 / - 2 -
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE		100
#define INITSIZE	20
#define INCREMENT	10

typedef struct Sqstack{
	double *base;
	double *top;
	int size;
}Sqstack;

static void InitStack( Sqstack *s )
{
	if( !(s->base = (double *)malloc(sizeof(double) * INITSIZE)) )
	{
		exit(0);
	}
	s->top = s->base;
	s->size = INITSIZE;
}

static void Push( Sqstack *s, double e )
{
	if( s->top - s->base == s->size)
	{
		s->base = (double *)realloc(s->base, sizeof(double) * (s->size + INCREMENT));
		s->size += INCREMENT;
	}
	*(s->top) = e;
	s->top++;
}

static void Pop( Sqstack *s, double *e )
{
	if( s->top == s->base )
	{
		return;
	}
	*e = *(--s->top);
}

static void Destroy( Sqstack *s )
{
	free(s->base);
	s->base = s->top = NULL;
}

static double NRP( Sqstack *s, char str[] )
{
	double c, d;
	int i, j;
	char str0[INCREMENT];

	i = 0;
	while( str[i] != '\n')
	{	
		if( str[i] >= '0' && str[i] <= '9' )		//执行完if后，往下走的字符只有可能是 运算符 或其 他乱七八糟符号 或者 空格
		{
			j = 0;
			str0[j++] = str[i];
			while( str[++i] != ' ' )
			{
				str0[j++] = str[i];
			}
			c = atof(str0);
			memset(str0, '\0', sizeof(str0));
			Push(s, c);
		}
		
		if( str[i] != ' ' )
		{
			switch (str[i])
			{
				case '+':
					Pop(s, &d);		//后一个
					Pop(s, &c);		//前一个
					c += d;
					Push(s, c);
					break;
				case '-':
					Pop(s, &d);		
					Pop(s, &c);		
					c -= d;
					Push(s, c);
					break;
				case '*':
					Pop(s, &d);		
					Pop(s, &c);		
					c *= d;
					Push(s, c);
					break;
				case '/':
					Pop(s, &d);		
					Pop(s, &c);	
					if( 0 == d )
					{
						printf("ERROR！除数为0\n\n");
						exit(0);
					}
					c /= d;
					Push(s, c);
					break;
				default:
					printf("输入未知字符\n\n");
					exit(0);
					break;
			}
		}
		i++;
	}
	Pop(s, &c);
	return c;
}

int main()
{
	Sqstack s;
	char str[MAXSIZE];
	int i = 0;
	
	InitStack(&s);
	printf("输入后缀表达式（以空格分开，不超过100字符）：");
	while( (str[i++] = getchar()) != '\n' )			//以‘\n’为结束标志
		;
	printf("\n\n后缀表达式值 = %.2lf\n\n", NRP(&s, str));
	Destroy(&s);
	return 0;
}

