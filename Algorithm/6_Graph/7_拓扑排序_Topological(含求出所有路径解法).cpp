/****************************************************************************************************
 * ���ڽ�����ṹΪ�����&��β - ��������·��ʱ�����Ϊ0
 * ���ṹΪ������&��ͷ - �����ó���Ϊ0��������Ķ���ѹջ��������ж�����ٳ�ջ��δʵ�֣�
 * 
 * void Topological_1( AdjGraph *G );       ɾ�߷���һ������·��
 * void Topological_DFS( AdjGraph *G, int *stack, int top );        ����������·��
 * PS��������������������ͬʱ���ԣ���Ϊɾ�߷���·��ʱ�Ѿ��ı���ͼ�ж�������
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
    int in;                     //���
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
    std::cout << "����ͼ�ж���ͻ�������";
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

    std::cout << "\n\n���붥�㣺\n\n";
    for( i = 0; i < G->numvex; i++ )
    {
        std::cout << "��" << i+1 << "�����㣺";
        std::cin >> G->vexgroup[i].vex;
        std::cin.ignore();
    }

    std::cout << "\n\n���뻡����㡢�յ��Ȩֵ��\n\n";
    int j, k, w;
    for( k = 0; k < G->numedge; k++ )
    {
        std::cout << "��" << k+1 << "������";
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
    std::cout << "\n�ɹ������ڽӱ�ͼ\n\n";
}


void Topological_1( AdjGraph *G )
{
    int cnt = 0;            //���ڼ�¼�����������С�����ж��㣬����ͼ���л�
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
    
    std::cout << "����·����\n\n";
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
        std::cout << "ͼ�д��ڻ����޷��ҵ�����·��\n\n";
    }
    delete stack;
}


//ͨ���ݹ������������·��
void Topological_DFS( AdjGraph *G, int *stack, int top )
{
    if( G->numvex == top )
    {
        static int cnt = 0;
        std::cout << "·��" << ++cnt << ":\n";
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

            //�ݹ������ԭif()ǰ״̬
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