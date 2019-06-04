//��Сд��ĸ�ֱ����������м��ܣ������ַ�ԭ�����
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

typedef struct ABCList {			//��ĸ˫��ѭ������
	char letter;
	struct ABCList *prior;
	struct ABCList *next;
}ABCList, *PABC;

typedef struct ListLine {			//Vigenere���������洢�� �����ַ��������������
	char val;
	int code;
	struct ListLine *next;
}ListLine, *PList;

static void Create_A( PABC *A )		//��д��ĸ
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
			cur->next->prior = cur;			//��Ԫ�ص�ǰָ��ָ��βԪ��
		}
		pre->next = cur;
		cur->prior = pre;
		pre = cur;	
	}
	cout << "\n������д��������ɹ�!\n" << endl;
}
static void Create_a( PABC *A )		//Сд��ĸ
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
			cur->next->prior = cur;			//��Ԫ�ص�ǰָ��ָ��βԪ��
		}
		pre->next = cur;
		cur->prior = pre;
		pre = cur;	
	}
	cout << "����Сд��������ɹ�!\n" << endl;
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
		char temp = str[i];					//�洢������ַ�
		
		if( NULL == (*L)->next )			//���¼����ַ���������,����ж�val��codeֵ
		{
			(*L)->next = pre = cur;
		}
		else
		{
			cur->next = NULL;
		}
		pre->next = cur;
		pre = cur;
		
		if( temp >= 'A' && temp <= 'Z')		//�������ַ��Ǵ�д��ĸ�����Լ���
		{		
			cur->code = rand() % 20;		//�����������
			PABC p = (*A)->next;
			while( p->letter != temp )		//���������ҵ�����ĸ
			{
				p = p->next;
			}
			for( int cnt = cur->code; cnt > 0; cnt-- )	//�ҵ���ĸ�����λ��code���ҵ�������
			{
				p = p->next;
			}
			
			cur->val = p->letter;			//���ҵ��ļ�����������������
		}
		
		else if( temp >= 'a' && temp <= 'z')		//�������ַ���Сд��ĸ�����Լ���
		{
			cur->code = rand() % 20;		//�����������
			PABC p = (*a)->next;
			while( p->letter != temp )		//���������ҵ�����ĸ
			{
				p = p->next;
			}
			for( int cnt = cur->code; cnt > 0; cnt-- )	//�ҵ���ĸ�����λ��code���ҵ�������
			{
				p = p->next;
			}
			
			cur->val = p->letter;			//���ҵ��ļ�����������������
		}
		
		else								//����ҵ����������ַ�����ֱ�Ӵ��룬��codeΪ0
		{
			cur->val = temp;
			cur->code = 0;
		}
	}
	cout << "����Vigenere����ɹ�!\n" << endl;
}

static void PrntList( PList *L )
{
	PList p = (*L)->next;
	if( !p )	return;
	
	cout << "�����Կ";
	while( p )
	{
		cout.width(4);
		cout << p->code;
		p = p->next;
	}
	
	cout << "\n\n����    ";
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
	
	cout << "\n\n����    ";

	while( p )
	{
		char temp = p->val;
		if( temp >= 'A' && temp <= 'Z')			//��д��ĸ
		{
			PABC q = (*A)->next;
			while( q->letter != temp )			//����ĸ�����ҵ�����
			{
				q = q->next;
			}
			for( int i=p->code; i>0; i-- )		//����
			{
				q = q->prior;
			}
			cout.width(4);
			cout << q->letter;
		}
		else if( temp >= 'a' && temp <= 'z')	//Сд��ĸ
		{
			PABC q = (*a)->next;
			while( q->letter != temp )			//����ĸ�����ҵ�����
			{
				q = q->next;
			}
			for( int i=p->code; i>0; i-- )		//����
			{
				q = q->prior;
			}
			cout.width(4);
			cout << q->letter;
		}
		else									//�����ַ�ֱ�����
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
	PABC A = NULL;					//��д��ĸ
	PABC a = NULL;					//Сд��ĸ
	PList L = NULL;
	const int MAX = 100;
	char input[MAX] = {'\0'};
	char c;
	int i = 0;
	
	//printf("�������ģ�������100���ַ�����");
	//gets (input);

	cout << "�������ģ�������100���ַ�����";				
	while( (c = cin.get()) != '\n' )						//����������ַ��洢��input�����У����س�ֹͣ����
	{
		input[i++] = c;
	}
	
	Create_A (&A);					//������������
	Create_a (&a);	
	Vigenere (&L, &A, &a, input);
	PrntList (&L);
	Crack (&L, &A, &a);
	Destroy_V(&L);
	Destroy_L(&A);
	Destroy_L(&a);
	return 0;
}