#include <iostream>
#include <string.h>
#define MAX         100
#define OK      1
#define ERROR   0

typedef char Elemtype;
typedef int Vexnum;                     //存储的是顶点在数组中对应的需要，输入时不方便，存储方便（不然每次存储需要遍历数组）
typedef int Status;

/*�������*/
typedef struct QNode {
    Vexnum data;
    struct QNode *next;
}QNode, *PNode;

typedef struct Queue {
    PNode front;
    PNode rear;
}Queue;

Status InitQueue( Queue *q )
{
    try
    {
        q->front = q->rear = new QNode;
    }
    catch(std::bad_alloc)
    {
        std::cout << "�ڴ�ռ䲻��" << "\n";
    }
    q->front->next = NULL;
    return OK;
}

Status Insert( Queue *q, Vexnum e )
{
    PNode p;
    try
    {
        p = new QNode;
    }
    catch(std::bad_alloc)
    {
        std::cout << "�ڴ治��" << "\n";
    }   
    p->data = e;
    p->next = NULL;
    q->rear->next = p;
    q->rear = p;
    return OK;
}

Status Delete( Queue *q, Vexnum *e )
{
    if( q->front == q->rear )
    {
        return ERROR;
    }
    PNode p = q->front->next;
    q->front->next = p->next;
    *e = p->data;
    delete p;
    if( p == q->rear )
    {
        q->rear = q->front;
    }
    return OK;
}

int Is_Empty( Queue q )
{
    if( q.front == q.rear )
    {
        return 0;
    }
    return 1;
}

//�ڽӱ���ͼ

typedef struct GEdge {
    Vexnum data;
    int weight;
    struct GEdge *next;
}GEdge, *PEdge;

typedef struct Vex {
    Elemtype data;
    PEdge firstedge;
}Vex;

typedef struct AdjGraph {
    Vex *vexgroup;
    int numvex, numedge;
}AdjGraph;

Status CreateGraph( AdjGraph *G )
{
    std::cout << "����ͼ�ж���ͱߵ�������";
    std::cin >> G->numvex >> G->numedge;
    std::cin.ignore();

    G->vexgroup = new Vex[G->numvex];           //根据输入数量创建顶点数组
    std::cout << "\n���붥�㣺\n";
    int i;
    for( i = 0; i < G->numvex; i++ )
    {
        std::cout << "��" << i+1 << "�����㣺";
        std::cin >> G->vexgroup[i].data;
        std::cin.ignore(10, '\n');                      //吃掉回车或空�?
        
        G->vexgroup[i].firstedge = NULL;
    }

    std::cout << "\n����ߺ�Ȩ��:\n";
    int j, k, w;
    PEdge p;
    for( k = 0; k < G->numedge; k++ )
    {
        std::cout << "��" << k+1 << "���ߣ�";
        std::cin >> i >> j >> w;
        --i;
        --j;
        try
        {
            p = new GEdge;
        }
        catch(std::bad_alloc)
        {
            std::cout << "�ڴ治��" << '\n';
        }
        p->data = i;
        p->weight = w;
        p->next = G->vexgroup[j].firstedge;
        G->vexgroup[j].firstedge = p;

        try
        {
            p = new GEdge;
        }
        catch(std::bad_alloc)
        {
            std::cout << "�ڴ治��" << '\n';
        }
        p->data = j;
        p->weight = w;
        p->next = G->vexgroup[i].firstedge;
        G->vexgroup[i].firstedge = p;
    }
    std::cout << "�ɹ������ڽӱ�" <<"\n\n";
    return OK;
}

Status BFSTranverse( AdjGraph *G , Queue *q )
{
    int *flag = new int[G->numvex];
    memset(flag, 0, sizeof(int) * G->numvex);

    std::cout << "�Բ��������ʽ���ͼ��" << "\n\n";
    if( !(G->vexgroup) )
    {
        return ERROR;
    }

    Vexnum e;
    Insert( q, 0 );
    while( Is_Empty(*q) )                           //队列为空时表示所有的顶点都已输出
    {
        Delete(q, &e);
        if( flag[e] == 0 )
        {
            std::cout << G->vexgroup[e].data << " -> ";
            flag[e] = 1;                            //输出的顶点做标记
            
            PEdge p = G->vexgroup[e].firstedge;
            while( p )
            {
                Insert( q, p->data );
                p = p->next;
            }
        }
    }
    delete flag;
    std::cout << "^" << "\n\n";
    return OK;
}

Status DestroyGraph( AdjGraph *G )
{
    PEdge p, q;
    int i;
    for( i = 0; i < G->numvex; i++ )
    {      
        p = G->vexgroup[i].firstedge->next;
        while( p )
        {
            q = p->next;
            delete p;
            p = q;
        }
    }
    delete G->vexgroup;
    G->vexgroup = NULL;
    return OK;
}

int main()
{
    Queue q;
    InitQueue(&q);

    AdjGraph g;
    g.vexgroup = NULL;
    CreateGraph(&g);

    BFSTranverse(&g, &q);
    DestroyGraph(&g);
    delete q.front;
    delete q.rear;
    system("pause");
    return 0;
}