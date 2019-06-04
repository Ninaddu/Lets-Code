//大小写字母分别两个链表中加密，其他字符原样输出
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

typedef struct ABCList {			//字母双向循环链表
	char letter;
	struct ABCList *prior;
	struct ABCList *next;
}ABCList, *PABC;

typedef struct ListLine {			//Vigenere加密链表，存储了 输入字符、随机加密密码
	char val;
	int code;
	struct ListLine *next;
}ListLine, *PList;

static void Create_A( PABC *A )		//大写字母
{
	PABC cur, pre;
	if( !(*A = (PABC)malloc(sizeof(ABCList))))
	{
		exit(0);
	}
	(*A)->prior = NULL;
	(*A)->next = NULL;

	for( int i=0; i < 26; i++ )
	{
		if( !(cur = (PABC)malloc(sizeof(ABCList))) )
		{
			exit(0);
		}
		cur->letter = 'A' + i;
		if( NULL == (*A)->next )
		{
			(*A)->next = pre = cur;
		}
		else
		{
			cur->next = pre->next;
			cur->next->prior = cur;			//首元素的前指针指向尾元素
		}
		pre->next = cur;
		cur->prior = pre;
		pre = cur;	
	}
	cout << "\n创建大写单词链表成功!\n" << endl;
}
static void Create_a( PABC *A )		//小写字母
{
	PABC cur, pre;
	if( !(*A = (PABC)malloc(sizeof(ABCList))))
	{
		exit(0);
	}
	(*A)->next = NULL;

	for( int i=0; i < 26; i++ )
	{
		if( !(cur = (PABC)malloc(sizeof(ABCList))) )
		{
			exit(0);
		}
		cur->letter = 'a' + i;
		if( NULL == (*A)->next )
		{
			(*A)->next = pre = cur;
		}
		else
		{
			cur->next = pre->next;
			cur->next->prior = cur;			//首元素的前指针指向尾元素
		}
		pre->next = cur;
		cur->prior = pre;
		pre = cur;	
	}
	cout << "创建小写单词链表成功!\n" << endl;
}

static void Vigenere( PList *L, PABC *A, PABC *a, char str[] )
{
	PList cur, pre;
		
	if( !(*L = (PList)malloc(sizeof(ListLine))) )
	{
		exit(0);
	}
	(*L)->next = NULL;

	if( !str[0] )	return;

	srand(time(0));
	for( int i=0; str[i]; i++ )
	{
		if( !(cur = (PList)malloc(sizeof(ListLine))) )
		{
			exit(0);
		}
		char temp = str[i];					//存储输入的字符
		
		if( NULL == (*L)->next )			//将新加入字符插入链表,随后判断val和code值
		{
			(*L)->next = pre = cur;
		}
		else
		{
			cur->next = NULL;
		}
		pre->next = cur;
		pre = cur;
		
		if( temp >= 'A' && temp <= 'Z')		//若输入字符是大写字母，可以加密
		{		
			cur->code = rand() % 20;		//生成随机密码
			PABC p = (*A)->next;
			while( p->letter != temp )		//在链表中找到该字母
			{
				p = p->next;
			}
			for( int cnt = cur->code; cnt > 0; cnt-- )	//找到字母后，向后位移code，找到加密码
			{
				p = p->next;
			}
			
			cur->val = p->letter;			//将找到的加密码存入加密链表中
		}
		
		else if( temp >= 'a' && temp <= 'z')		//若输入字符是小写字母，可以加密
		{
			cur->code = rand() % 20;		//生成随机密码
			PABC p = (*a)->next;
			while( p->letter != temp )		//在链表中找到该字母
			{
				p = p->next;
			}
			for( int cnt = cur->code; cnt > 0; cnt-- )	//找到字母后，向后位移code，找到加密码
			{
				p = p->next;
			}
			
			cur->val = p->letter;			//将找到的加密码存入加密链表中
		}
		
		else								//如果找到的是其他字符，则直接存入，且code为0
		{
			cur->val = temp;
			cur->code = 0;
		}
	}
	cout << "创建Vigenere链表成功!\n" << endl;
}

static void PrntList( PList *L )
{
	PList p = (*L)->next;
	if( !p )	return;
	
	cout << "随机密钥";
	while( p )
	{
		cout.width(4);
		cout << p->code;
		p = p->next;
	}
	
	cout << "\n\n密文    ";
	p = (*L)->next;
	while( p )
	{
		cout.width(4);
		cout << p->val;
		p = p->next;
	}
}

static void Crack( PList *L, PABC *A, PABC *a )
{
	PList p = (*L)->next;
	if( !p )	return;
	
	cout << "\n\n明文    ";

	while( p )
	{
		char temp = p->val;
		if( temp >= 'A' && temp <= 'Z')			//大写字母
		{
			PABC q = (*A)->next;
			while( q->letter != temp )			//从字母表中找到密文
			{
				q = q->next;
			}
			for( int i=p->code; i>0; i-- )		//解码
			{
				q = q->prior;
			}
			cout.width(4);
			cout << q->letter;
		}
		else if( temp >= 'a' && temp <= 'z')	//小写字母
		{
			PABC q = (*a)->next;
			while( q->letter != temp )			//从字母表中找到密文
			{
				q = q->next;
			}
			for( int i=p->code; i>0; i-- )		//解码
			{
				q = q->prior;
			}
			cout.width(4);
			cout << q->letter;
		}
		else									//其他字符直接输出
		{
			cout.width(4);
			cout << temp;
		}
		
		p = p->next;
	}
	cout <<"\n" << endl;
}

static void Destroy_V( PList *L )
{
	PList p = *L;
	while( p )
	{
		*L = p->next;
		free(p);
		p = *L;
	}
}

static void Destroy_L( PABC *A )
{
	PABC p = (*A)->next, q = p->next;
	if( !p )	return;
	if( p == q )
	{
		free(p);
	}
	else
	{
		while( q != (*A)->next )
		{
			q = p->next;
			free(p);
			p = q;
		}
	}
	free(*A);
}

int main()
{
	PABC A = NULL;					//大写字母
	PABC a = NULL;					//小写字母
	PList L = NULL;
	const int MAX = 100;
	char input[MAX] = {'\0'};
	char c;
	int i = 0;
	
	//printf("输入明文（不超过100个字符）：");
	//gets (input);

	cout << "输入明文（不超过100个字符）：";				
	while( (c = cin.get()) != '\n' )						//所有输入的字符存储在input数组中，遇回车停止输入
	{
		input[i++] = c;
	}
	
	Create_A (&A);					//创建单词链表
	Create_a (&a);	
	Vigenere (&L, &A, &a, input);
	PrntList (&L);
	Crack (&L, &A, &a);
	Destroy_V(&L);
	Destroy_L(&A);
	Destroy_L(&a);
	return 0;
}