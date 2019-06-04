#include <iostream>
#include <string.h>
#define INFINITY    -1

typedef char Elemtype;
typedef struct Edge {
    int start;
    int end;
    int weight;
}Edge;

typedef struct Adjgraph {
    Edge *edge;                                 //边数组
    Elemtype *vex;                              //顶点数组     
    int numvex, numedge;
}Adjgraph;


void CreateGraph( Adjgraph *G );
void Sort( Adjgraph *G );
void Kruskal( Adjgraph *G );
int Parent( int *first, int vex );
void Delete( Adjgraph *G );


int main()
{
    Adjgraph g;
    g.edge = NULL;
    g.vex = NULL;

    CreateGraph(&g);
    Sort(&g);
    Kruskal(&g);
    Delete(&g);
    system("pause");
    return 0;
}


void CreateGraph( Adjgraph *G )
{
    std::cout << "输入图中顶点和边的数量：";
    std::cin >> G->numvex >> G->numedge;
    std::cin.ignore();

    std::cout << "\n\n输入顶点：" <<"\n";
    try
    {
        G->vex = new Elemtype[G->numvex];
        memset(G->vex, NULL, sizeof(Elemtype) * G->numvex);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }  
    int i;
    for( i = 0; i < G->numvex; i++ )
    {
        std::cout << "第" << i+1 << "个顶点：";
        std::cin >> G->vex[i];
        std::cin.ignore();  
    }

    std::cout << "\n\n输入边：" <<"\n";
    try
    {
        G->edge = new Edge[G->numedge];
        memset(G->edge, NULL, sizeof(Edge) * G->numedge);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }  
    int j, k;
    for( i = 0; i < G->numedge; i++ )
    {
        std::cout << "第" << i+1 << "条边和边上权重：";
        std::cin >> j;
        G->edge[i].start = --j;
        std::cin >> k;
        G->edge[i].end = --k;
        std::cin >> G->edge[i].weight; 
    }
    std::cout << "\n\n成功创建边集数组！(#^.^#)" <<"\n\n";
}


//根据G->edge[i].weight大小对edge[i]排序，选择法

void Sort( Adjgraph *G )
{
    int i, j;
    for( i = 0; i < G->numedge-1; i++ )
    {
        int min = i;
        for( j = i+1; j < G->numedge; j++ )
        {
            if( G->edge[j].weight < G->edge[min].weight )
            {
                min = j;
            }
        }
        if( i != min )
        {
            Edge temp = G->edge[min];
            G->edge[min] = G->edge[i];
            G->edge[i] = temp;
        }
    }
}

//从权值最小边出发，在firvex数组中查找边起点和终点是否有指向的顶点，顶点是否相同；若相同表示路线已行程环形，换下一条边进行比较
void Kruskal( Adjgraph *G )
{
    int *firvex;
    try
    {
        firvex = new int[G->numvex];
        memset(firvex, INFINITY, sizeof(int) * G->numvex);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    int i, m, n;
    for( i = 0; i < G->numedge; i++ )
    {
        m = Parent(firvex, G->edge[i].start);
        n = Parent(firvex, G->edge[i].end);

        if( m != n )
        {
            std::cout << G->vex[G->edge[i].start] << " -> " << G->vex[G->edge[i].end] 
            << "  " << G->edge[i].weight << "\n";
            firvex[n] = m;
        }
    }
    std::cout << "\n\n";
    delete firvex;
}

//功能：寻找&存储最开始的前驱顶点
//参数：前驱顶点数组；寻找的顶点
//返回值：前驱顶点
int Parent( int *firvex, int v )
{
    while( firvex[v] != INFINITY )
    {
        v = firvex[v];
    }
    return v;
}

void Delete( Adjgraph *G )
{
    delete G->edge;
    delete G->vex;
    G->edge = NULL;
    G->vex = NULL;
}