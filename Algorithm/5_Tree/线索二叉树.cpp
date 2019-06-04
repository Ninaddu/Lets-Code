#include <stdio.h>
#include <stdlib.h>

enum { Link, Thread };

typedef char Elemtype;
typedef int Status;

typedef struct TNode {
	Elemtype data;
	struct TNode* lchild;
	struct TNode* rchild;
	Status ltag, rtag;
}TNode, * pNode;

pNode pre = NULL;

static void CreateTree(pNode* T);				//以前序遍历创建一棵线索二叉树
static void InThreading(pNode T);				//辅助函数，用于连接数的节点
static void InOrderThreading(pNode T, pNode* p);			//以中序遍历方式遍历二叉树，修改tag标签，再传入辅助函数连接节点
static void InOrderTraverse(pNode T);			//以中序遍历方式遍历整棵树
static void Destroy(pNode* T);					//销毁

int main()
{
	pNode T = NULL;
	pNode p = NULL;

	printf("输入二叉树节点：\n");
	CreateTree(&T);

	printf("创建了一颗二叉树！\n\n");
	InOrderThreading(T, &p);

	printf("以中序遍历输出：\n");
	InOrderTraverse(p);
	Destroy(&p);
	return 0;
}

static void CreateTree(pNode* T)
{
	char ch;
	ch = getchar();
	if (' ' == ch)
	{
		*T = NULL;
	}
	else
	{
		if (!(*T = (pNode)malloc(sizeof(TNode))))
		{
			exit(0);
		}
		(*T)->data = ch;
		(*T)->ltag = (*T)->rtag = Link;
		CreateTree(&(*T)->lchild);
		CreateTree(&(*T)->rchild);
	}
}

static void InThreading(pNode T)
{
	if (!T)
	{
		return;
	}
	InThreading(T->lchild);
	if (T->lchild == NULL)
	{
		T->ltag = Thread;
		T->lchild = pre;
	}

	if (pre->rchild == NULL)
	{
		pre->rtag = Thread;
		pre->rchild = T;
	}
	pre = T;
	InThreading(T->rchild);
}

static void InOrderThreading(pNode T, pNode* p)
{
	if (!T)
	{
		return;
	}
	if (!((*p) = (pNode)malloc(sizeof(TNode))))				//二叉树头结点用于连接头和尾
	{
		exit(0);
	}
	(*p)->ltag = Link;
	(*p)->rtag = Thread;
	(*p)->lchild = T;
	pre = *p;
	InThreading(T);
	(*p)->rchild = pre;
	pre->rchild = *p;
	printf("Duang！升级为线索二叉树\n\n");
}

static void InOrderTraverse(pNode T)
{
	pNode p;
	if (!T)
	{
		return;
	}
	p = T->lchild;
	while (p != T)
	{
		while (p->ltag == Link)
		{
			p = p->lchild;
		}
		while (p->rtag == Thread && p->rchild != T)
		{
			printf("%c ", p->data);
			p = p->rchild;
		}
		printf("%c ", p->data);
		p = p->rchild;
	}
	printf("\n\n");

	p = T->rchild;
	while (p != T)
	{
		while (p->ltag == Thread && p->lchild != T)
		{
			printf("%c ", p->data);
			p = p->lchild;
		}
		printf("%c ", p->data);
		p = p->lchild;
		while (p->rtag != Thread)
		{
			p = p->rchild;
		}
	}
	printf("\n\n");

}

static void Destroy(pNode* T)
{
	pNode p, q;
	if (!(*T))
	{
		return;
	}
	p = (*T)->lchild;
	while (p->lchild != *T)
	{
		p = p->lchild;
	}
	while (p != (*T))
	{
		q = p->rchild;
		free(p);
		p = q;
	}
	free(p);
	*T = NULL;
	printf("砍了砍了\n\n");
}