#pragma once
#include "HfmTree.h"


//����������
//val����Ҷ�ӽڵ㣬�洢�û������ַ�
//frequency���ַ�����Ƶ�ʣ����ڴ�С��������

typedef struct htNode {
	pNode val;
	int frequency;
	struct htNode* next;
}htNode;


//��������������
//fitptrָ�������ͷ
//cntΪ����������¼������Ԫ�ص�����

typedef struct HfmTable {
	htNode* firptr;
	int cnt;
}HfmTable;


Status InitTable(HfmTable** h);		//Huffman Table ������ʼ��
Status Insert(HfmTable* h, pNode* e, int freq);		//����Ԫ�ز���
htNode* Get(HfmTable* h);			//ȡ��Table����Ԫ��