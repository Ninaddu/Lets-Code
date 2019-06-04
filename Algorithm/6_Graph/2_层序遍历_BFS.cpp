#include <iostream>
#include <string.h>
#define MAX         100
#define OK      1
#define ERROR   0

typedef char Elemtype;
typedef int Vexnum;                     //瀛樺偍鐨勬槸椤剁偣鍦ㄦ暟缁勪腑瀵瑰簲鐨勯渶瑕侊紝杈撳叆鏃朵笉鏂逛究锛屽瓨鍌ㄦ柟渚匡紙涓嶇劧姣忔瀛樺偍闇�瑕侀亶鍘嗘暟缁勶級
typedef int Status;

/*链表队列*/
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
        std::cout << "内存空间不足" << "\n";
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
        std::cout << "内存不足" << "\n";
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

//邻接表建立图

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
    std::cout << "输入图中顶点和边的数量：";
    std::cin >> G->numvex >> G->numedge;
    std::cin.ignore();

    G->vexgroup = new Vex[G->numvex];           //鏍规嵁杈撳叆鏁伴噺鍒涘缓椤剁偣鏁扮粍
    std::cout << "\n输入顶点：\n";
    int i;
    for( i = 0; i < G->numvex; i++ )
    {
        std::cout << "第" << i+1 << "个顶点：";
        std::cin >> G->vexgroup[i].data;
        std::cin.ignore(10, '\n');                      //鍚冩帀鍥炶溅鎴栫┖鏍?
        
        G->vexgroup[i].firstedge = NULL;
    }

    std::cout << "\n输入边和权重:\n";
    int j, k, w;
    PEdge p;
    for( k = 0; k < G->numedge; k++ )
    {
        std::cout << "第" << k+1 << "条边：";
        std::cin >> i >> j >> w;
        --i;
        --j;
        try
        {
            p = new GEdge;
        }
        catch(std::bad_alloc)
        {
            std::cout << "内存不足" << '\n';
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
            std::cout << "内存不足" << '\n';
        }
        p->data = j;
        p->weight = w;
        p->next = G->vexgroup[i].firstedge;
        G->vexgroup[i].firstedge = p;
    }
    std::cout << "成功创建邻接表" <<"\n\n";
    return OK;
}

Status BFSTranverse( AdjGraph *G , Queue *q )
{
    int *flag = new int[G->numvex];
    memset(flag, 0, sizeof(int) * G->numvex);

    std::cout << "以层序遍历方式输出图：" << "\n\n";
    if( !(G->vexgroup) )
    {
        return ERROR;
    }

    Vexnum e;
    Insert( q, 0 );
    while( Is_Empty(*q) )                           //闃熷垪涓虹┖鏃惰〃绀烘墍鏈夌殑椤剁偣閮藉凡杈撳嚭
    {
        Delete(q, &e);
        if( flag[e] == 0 )
        {
            std::cout << G->vexgroup[e].data << " -> ";
            flag[e] = 1;                            //杈撳嚭鐨勯《鐐瑰仛鏍囪
            
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