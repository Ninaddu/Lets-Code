#pragma once
#define OK		1
#define ERROR	0
#define MAXCODE	100
#define LT	0		
#define RT	1	

typedef int Status;
typedef char Elemtype;


//�������ڵ�

typedef struct tNode {
	Elemtype data;
	struct tNode* lchild;
	struct tNode* rchild;
}tNode, *pNode;


//������ڵ�

typedef struct hTree {
	pNode root;
}hTree;


//�����
//data����Ҫ�����ַ�
//code����0101��������

typedef struct hCode {
	Elemtype data;
	char* code;
	struct hCode* next;
}hCode;


//���������

typedef struct HfmCode {
	hCode* codeptr;
}HfmCode;


hTree* HuffmanTree(Elemtype* str);					//����Huffman������
HfmCode* Coding(hTree* t);							//��������
Status Tranverse(HfmCode* c, pNode p, char* code, int n);		//����Ѱ��Ҷ�ӽڵ㣬��������Ԫ��
void Prnt(HfmCode* c);								//��ӡ�����

void Search(HfmCode* c, Elemtype* str);				//������������û���������ķ���Ϊ����
void DeCoding(hTree* t, char* str);					//��������������������ҵ����ĺ����
Status Destroy(hTree** t, HfmCode** c);				//Huffman Tree��Code Table����
Status Tree_Destroy(pNode* p);						//����������������
Status CodeLink_Destroy(HfmCode** c);				//����������������������

