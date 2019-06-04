/****************************************************************************************************
 * 若邻接链表结构为：入度&弧尾 - 计算拓扑路径时用入度为0
 * 若结构为：出度&弧头 - 可以用出度为0，将最出的顶点压栈，求出所有顶点后再出栈（未实现）
 * 
 * void Topological_1( AdjGraph *G );       删边法求一条拓扑路径
 * void Topological_DFS( AdjGraph *G, int *stack, int top );        深搜求所有路径
 * PS：以上两个函数不可以同时测试，因为删边法求路径时已经改变了图中顶点的入度
****************************************************************************************************/
#include <iostream>
#include <string.h>

typedef char Elemtype;
typedef struct edge {
    int val;
    int weight;
    struct edge *next;
}edge;

typedef struct vexes {
    Elemtype vex;
    int in;                     //入度
    edge *firstptr;
}vexes;

typedef struct AdjGraph {
    vexes *vexgroup;
    int numvex, numedge;
}AdjGraph;


void CreateGraph( AdjGraph *G );
void Topological_1( AdjGraph *G );
void Topological_DFS( AdjGraph *G, int *stack, int top );
void Destroy( AdjGraph *G, int **stack );


int main()
{
    AdjGraph g;
    g.vexgroup = NULL;
    CreateGraph(&g);

    Topological_1(&g);

    int *stack_DFS = new int[g.numvex];
    memset(stack_DFS, 0, sizeof(int) * g.numvex);
    Topological_DFS(&g, stack_DFS, 0);

    Destroy(&g, &stack_DFS);
    system("pause");
    return 0;
}


void CreateGraph( AdjGraph *G )
{
    std::cout << "输入图中顶点和弧数量：";
    std::cin >> G->numvex >> G->numedge;
    std::cin.ignore();

    int i;
    try
    {
        G->vexgroup = new vexes[G->numvex];
        for( i = 0; i < G->numvex; i++ )
        {
            G->vexgroup[i].in = 0;
            G->vexgroup[i].firstptr = NULL;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "\n\n输入顶点：\n\n";
    for( i = 0; i < G->numvex; i++ )
    {
        std::cout << "第" << i+1 << "个顶点：";
        std::cin >> G->vexgroup[i].vex;
        std::cin.ignore();
    }

    std::cout << "\n\n输入弧的起点、终点和权值：\n\n";
    int j, k, w;
    for( k = 0; k < G->numedge; k++ )
    {
        std::cout << "第" << k+1 << "条弧：";
        std::cin >> i >> j >> w;
        --i;
        --j;
        edge *p;
        try
        {
            p = new edge;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        p->val = j;
        p->weight = w;
        p->next = G->vexgroup[i].firstptr;
        G->vexgroup[i].firstptr = p;
        ++(G->vexgroup[j].in);
    }
    std::cout << "\n成功创建邻接表图\n\n";
}


void Topological_1( AdjGraph *G )
{
    int cnt = 0;            //用于记录输出个数，若小于所有顶点，表明图中有环
    int *stack;
    int top = 0;
    try
    {
        stack = new int[G->numvex];
        memset(stack, 0, sizeof(int) * G->numvex);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    int i;
    for( i = 0; i < G->numvex; i++ )
    {
        if( NULL == G->vexgroup[i].in )
        {
            stack[top++] = i;
        }
    }
    
    std::cout << "拓扑路径：\n\n";
    while( 0 != top )
    {
        int temp = stack[--top];
        std::cout << G->vexgroup[temp].vex << " -> ";
        ++cnt;
        edge *p = G->vexgroup[temp].firstptr;
        while( p )
        {
            if( --(G->vexgroup[p->val].in) == 0 )
                {
                    stack[top++] = p->val;
                }
            p = p->next;
        }        
    }
    std::cout << "^\n\n";
    
    if( cnt < G->numvex )
    {
        std::cout << "图中存在环，无法找到拓扑路径\n\n";
    }
    delete stack;
}


//通过递归求出所有拓扑路径
void Topological_DFS( AdjGraph *G, int *stack, int top )
{
    if( G->numvex == top )
    {
        static int cnt = 0;
        std::cout << "路径" << ++cnt << ":\n";
        for( int i = 0; i < top; i++ )
        {
            std::cout << G->vexgroup[stack[i]].vex << " -> ";
        }
        std::cout << "^\n\n";
        return;
    }

    for( int i = 0; i < G->numvex; i++ )
    {
        if( 0 == G->vexgroup[i].in )
        {
            stack[top] = i;
            --G->vexgroup[i].in;
            for( edge *p = G->vexgroup[i].firstptr; p; p = p->next )
            {
                --(G->vexgroup[p->val].in);
            }
            Topological_DFS( G, stack, top+1 );

            //递归结束后还原if()前状态
            ++G->vexgroup[i].in;
            for( edge *p0 = G->vexgroup[i].firstptr; p0; p0 = p0->next )
            {
                ++(G->vexgroup[p0->val].in);
            }
        }
    }
}

void Destroy( AdjGraph *G, int **stack )
{
    for( int i = 0; i < G->numvex; i++ )
    {
        edge *p = G->vexgroup[i].firstptr;
        edge *q;
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
    delete *stack;
    *stack = NULL;
}