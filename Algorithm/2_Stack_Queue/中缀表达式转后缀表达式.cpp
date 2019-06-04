//中缀转后缀表达式
//1+2-(4*5/6+(7-8)*3)*9/10-2  ->  1 2 + 4 5 * 6 / 7 8 - 3 * + 9 * 10 / - 2 -
//输入包括：数字，小数点，四符号，左右括号，非法字符，回车
//8*(7+8*(8+8)) -> 8 7 8 8 8 + * + *

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define INITSIZE	20
#define INCREMENT	10

typedef char Elemtype;

typedef struct Sqstack {
	Elemtype *base;
	Elemtype *top;
	int size;
}Sqstack;

static void Initstack( Sqstack *s )
{
	if( !(s->base = (Elemtype *)malloc(sizeof(Elemtype) * INITSIZE)) )
	{
		exit(0);
	}
	s->top = s->base;
	s->size = INITSIZE;
}

static void Push( Sqstack *s, Elemtype e )
{
	if( s->top - s->base == s->size )
	{
		if( !(s->base = (Elemtype *)realloc(s->base, sizeof(Elemtype) * (s->size + INCREMENT))) )
		{
			exit(0);
		}
		s->size += INCREMENT;
	}
	*(s->top) = e;
	s->top++;
}

static void Pop( Sqstack *s, Elemtype *e )
{
	if( s->top == s->base )
	{
		return;
	}
	*e = *(--s->top);
}

static int IsEmpty( Sqstack s )			//返回值为0，表示空；否则为非零值
{
	return (s.top - s.base);
}

static void Destroy( Sqstack *s )
{
	free(s->base);
	s->base = s->top = NULL;
}

int main()
{
	Sqstack s;
	Elemtype e;
	char ch;
	
	Initstack(&s);
	printf("输入中缀表达式：");
	scanf("%c", &ch);
	while( ch != '\n' )
	{
		if( (isdigit(ch)) || ch == '.' )
		{
			printf("%c", ch);
			while( (ch = getchar()) == '.' || isdigit(ch) )
			{
				printf("%c", ch);
			}
			if( ch == '\n' )
			{
				printf(" ");
				break;
			}
			printf(" ");
		}
		else 
		{
			if( !IsEmpty(s) )
			{
				Push(&s, ch);
			}
			else
			{
				switch (ch)
				{
					case '+':
					case '-':
						Pop(&s, &e);
						while( e != '(' && IsEmpty(s) )
						{
							printf("%c ", e);
							Pop(&s, &e);
						}
						if( e == '(' )
						{
							Push(&s, e);
						}
						else
						{
							printf("%c ", e);
						}
						Push(&s, ch);
						break;
					case '*':
					case '/':
						Pop(&s, &e);
						if( e == '*' || e == '/')
						{
							printf("%c ", e);
						}
						else 
						{
							Push(&s, e);
						}
						Push(&s, ch);
						break;
					case '(':
						Push(&s, ch);
						break;
					case ')':
						Pop(&s, &e);
						do
						{
							printf("%c ", e);
							Pop(&s, &e);
						}while( e != '(' );
						break;
					default:
						printf("\n输入含非法字符！\n\n");
						break;
				}
			}	
			ch = getchar();
		}
	}
	while( IsEmpty(s) )
	{
		Pop(&s, &e);
		printf("%c ", e);
	}
	printf("\n\n");
	Destroy(&s);
	return 0;
}


