#pragma once
#include "HfmTree.h"


//哈夫曼链表
//val：树叶子节点，存储用户输入字符
//frequency：字符出现频率，用于从小到大排列

typedef struct htNode {
	pNode val;
	int frequency;
	struct htNode* next;
}htNode;


//哈夫曼链表索引
//fitptr指向链表表头
//cnt为计数器，记录链表中元素的数量

typedef struct HfmTable {
	htNode* firptr;
	int cnt;
}HfmTable;


Status InitTable(HfmTable** h);		//Huffman Table 索引初始化
Status Insert(HfmTable* h, pNode* e, int freq);		//链表元素插入
htNode* Get(HfmTable* h);			//取出Table中首元素