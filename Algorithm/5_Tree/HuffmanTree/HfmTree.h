#pragma once
#define OK		1
#define ERROR	0
#define MAXCODE	100
#define LT	0		
#define RT	1	

typedef int Status;
typedef char Elemtype;


//定义树节点

typedef struct tNode {
	Elemtype data;
	struct tNode* lchild;
	struct tNode* rchild;
}tNode, *pNode;


//定义根节点

typedef struct hTree {
	pNode root;
}hTree;


//密码表
//data：需要加密字符
//code：以0101加密密码

typedef struct hCode {
	Elemtype data;
	char* code;
	struct hCode* next;
}hCode;


//密码表索引

typedef struct HfmCode {
	hCode* codeptr;
}HfmCode;


hTree* HuffmanTree(Elemtype* str);					//创建Huffman密码树
HfmCode* Coding(hTree* t);							//密码链表
Status Tranverse(HfmCode* c, pNode p, char* code, int n);		//遍历寻找叶子节点，创建链表元素
void Prnt(HfmCode* c);								//打印密码表

void Search(HfmCode* c, Elemtype* str);				//根据密码表，将用户输入的明文翻译为密码
void DeCoding(hTree* t, char* str);					//根据输入密码遍历树，找到明文后输出
Status Destroy(hTree** t, HfmCode** c);				//Huffman Tree和Code Table销毁
Status Tree_Destroy(pNode* p);						//辅助函数，销毁树
Status CodeLink_Destroy(HfmCode** c);				//辅助函数，销毁密码链表

