#include <iostream>
#include <cstring>
#define SUCCESS 1
#define FAIL    0

typedef char Elemtype;
typedef int Status;

typedef struct edge {
    int val;
    int weight;
    struct edge *next;
}edge;

typedef struct vexes {
    Elemtype data;
    int in;
    edge *first;
}vexes;

typedef struct Adjgraph {
    vexes *vexgroup;
    int numvex, numedge;
}Adjgraph;


void CreateGraph( Adjgraph *G );
Status Topological( Adjgraph *G, int *stack1, int *etv);
void CriticalPath( Adjgraph *G, int *stack1, int *etv);
void Destroy( Adjgraph *G, int **stack1, int **etv);


int main()
{
    Adjgraph g;
    g.vexgroup = NULL;
    CreateGraph(&g);
    int *stack1, *etv;
    try
    {
        stack1 = new int[g.numvex];
        memset(stack1, 0, sizeof(int) * g.numvex);
        etv = new int[g.numvex];
        memset(etv, 0, sizeof(int) * g.numvex);        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    if( Topological(&g, stack1, etv) )
    {
        CriticalPath(&g, stack1, etv);
    }
    Destroy(&g, &stack1, &etv);
    system("pause");
    return 0;
}


void CreateGraph( Adjgraph *G )
{
    std::cout << "输入顶点和边数量：";
    std::cin >> G->numvex >> G->numedge;
    std::cin.ignore();

    try
    {
        G->vexgroup = new vexes[G->numvex];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "\n\n输入顶点：" << "\n\n";
    int i;
    for( i = 0; i < G->numvex; i++ )
    {
        std::cout << "第" << i+1 << "个顶点：";
        std::cin >> G->vexgroup[i].data;
        std::cin.ignore();
        G->vexgroup[i].in = 0;
        G->vexgroup[i].first = NULL;
    }

    std::cout << "\n\n输入边和权值：" << "\n\n";
    int j, k;
    for( k = 0; k < G->numedge; k++ )
    {
        edge *p;
        try
        {
            p = new edge;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        std::cout << "第" << k+1 << "条边和权值：";
        std::cin >> i >> j >> p->weight;
        --i;
        --j;
        p->val = j;
        p->next = G->vexgroup[i].first;
        G->vexgroup[i].first = p;
        ++(G->vexgroup[j].in);
    }
    std::cout << "\n\n成功创建邻接表！(＾－＾)V" << "\n\n";
}


/************************************************************************************************
*  功能：求出拓扑路径，将路径入栈；以及路径中每个事件（顶点）的最晚发生时间（权值之和），存放在etv中
*  参数：邻接表图、结果栈指针、etv
*  返回值：执行结果状态
***********************************************************************************************/

Status Topological( Adjgraph *G, int *stack1, int *etv)
{
    int cnt = 0;
    int top0 = 0;
    int *stack0;
    try
    {
        stack0 = new int[G->numvex];
        memset(stack0, 0, sizeof(int) * G->numvex);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    int i;
    for( i = 0; i < G->numvex; i++ )
    {
        if( 0 == G->vexgroup[i].in )
        {
            stack0[top0++] = i;
        }
    }

    int top1 = 0;
    while( 0 != top0 )
    {
        ++cnt; 
        int temp = stack0[--top0];
        stack1[top1++] = temp;
        edge *p = G->vexgroup[temp].first;
        while( p )
        {
            if( 0 == --(G->vexgroup[p->val].in) )
            {
                stack0[top0++] = p->val;
            }
            if( etv[p->val] < etv[temp] + p->weight )           //求出该顶点连接事件的发生事件，更新至最晚
            {
                etv[p->val] = etv[temp] + p->weight; 
            }
            p = p->next;
        }
    }

    delete stack0;
    stack0 = NULL;

    if( cnt < G->numvex )
    {
        std::cout << "\n\n不存在拓扑路径，无法求出关键路径o(╥﹏╥)o" << "\n\n"; 
        return FAIL;
    }
    return SUCCESS;
}


/***********************************************************************************************
 * 功能：根据图中事件入栈的顺序，从后往前求出事件最早发生时间ltv；找到etv和ltv中相同的发生时间即为关键路径
 * 参数：图，拓扑中求得的Stack1和etv
 * 返回值：无
************************************************************************************************/

void CriticalPath( Adjgraph *G, int *stack1, int *etv)
{
    int *ltv;
    int top = G->numvex;
    try
    {
        ltv = new int[G->numvex];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    int i;
    int ltv_max = etv[--top];
    for( i = 0; i < G->numvex; i++ )           //初始化ltv为最后执行事件的发生时间；注意，此时top已经指向栈顶下一个元素
    {
        ltv[i] = ltv_max;
    }

    //根据stack1出栈顺序，从后往前推导工程中各个事件的最早发生时间
    while( 0 != top )
    {
        //通过遍历temp为下标事件所连接的其他事件，求出temp最早时间
        int temp = stack1[--top];                           
        edge *p = G->vexgroup[temp].first;
        while( p )
        {
            if( ltv[temp] > ltv[p->val] - p->weight )
            {
                ltv[temp] = ltv[p->val] - p->weight;
            }
            p = p->next;
        }
    }

    //得到etv和ltv，找到其中发生时间相同事件并输出，即关键路径
    std::cout << "输出关键路径：" << "\n\n";
    for( i = 0; i < G->numvex; i++ )
    {
        if( etv[i] == ltv[i] )
        {
            std::cout << G->vexgroup[i].data << " -> ";
        }
    }
    std::cout << "^\n\n";
    delete ltv;
    ltv = NULL;
}

void Destroy( Adjgraph *G, int **stack1, int **etv)
{
    delete *stack1;
    stack1 = NULL;
    delete *etv;
    *etv = NULL;
    for( int i = 0; i < G->numvex; i++ )
    {
        edge *q, *p = G->vexgroup[i].first;
        while( p )
        {
            q = p->next;
            delete p;
            p = NULL;
            p = q;
        }
    }
    delete G->vexgroup;
    G->vexgroup = NULL;
}