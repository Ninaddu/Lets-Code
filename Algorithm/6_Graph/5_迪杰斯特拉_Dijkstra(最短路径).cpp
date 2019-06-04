#include <iostream>
#include <string.h>
#define INFINITY    65535
#define MAX 10


typedef char Elemtype;

typedef struct AdjMaxtrix {
    Elemtype *vex;
    int **edge;
    int numvex, numedge;
}AdjMatrix;

void CreateGraph( AdjMatrix *G );
int *Dijkstra( AdjMatrix *G );
void Search( AdjMatrix *G, int *prevex);
void Destroy( AdjMatrix *G, int **prevex );

int main()
{
    AdjMatrix g;
    g.vex = NULL;
    g.edge = NULL;
    CreateGraph(&g);
    int *prevex = Dijkstra(&g); 
    Search(&g, prevex);
    Destroy(&g, &prevex);
    system("pause");
    return 0;
}


void CreateGraph( AdjMatrix *G )
{
    std::cout <<"输入图中的顶点和边数量：";
    std::cin >> G->numvex >> G->numedge;
    std::cin.ignore();


    //申请vex和edge数组空间并初始化
    int i;
    try
    {
        G->vex = new Elemtype[G->numvex + 1];
        memset(G->vex, '\0', sizeof(Elemtype) * (G->numvex + 1));
        G->edge = new int *[G->numvex];         //指针数组
        for( i = 0; i < G->numvex; i++ )
        {
            G->edge[i] = new int[G->numvex];
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    int j;
    for( i = 0; i < G->numvex; i++ )
    {
        for( j = 0; j < G->numvex; j++ )
        {
              G->edge[i][j] = (i == j)? 0 : INFINITY;         
        }
    }

    std::cout << "\n\n输入顶点：" << "\n\n";
    for( i = 0; i < G->numvex; i++ )
    {
        std::cout << "第" << i+1 << "个顶点：";
        std::cin >> G->vex[i];
        std::cin.ignore();
    }

    int k, w;
    std::cout << "\n\n输入边：" << "\n\n";
    for( k = 0; k < G->numedge; k++ )
    {
        std::cout << "第" << k+1 << "条边："; 
        std::cin >> i >> j >> w;
        --i;
        --j;
        G->edge[i][j] = w;
        G->edge[j][i] = w;
    }
    std::cout << "\n\n成功创建邻接矩阵" << "\n\n";
}


/*******************************************************************************************
 * 功能：寻找从某个顶点到其他所有顶点的最短路径，存放在lowcost数组中
 * 参数：邻接矩阵
 * 返回值：最短路径前驱节点数组的地址
 ********************************************************************************************/
int *Dijkstra( AdjMatrix *G )
{
    int *prevex;
    int *lowcost;
    try
    {
        prevex = new int[G->numvex];
        lowcost = new int[G->numvex];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    int i;
    for( i = 0; i < G->numvex; i++ )                    
    {
        lowcost[i] = G->edge[0][i];                         //初始化lowcost为A起点到其他所有顶点开始的权值
        prevex[i] = 0;                                       //初始化prevex全部为A(0)
    }

    int cnt;                                                //计数器，循环G->numvex - 1次可找到剩下所有顶点
    for( cnt = 0; cnt < G->numvex - 1; cnt++ )
    {
        int min = INFINITY;
        int minptr = 0;
        for( i = 0; i < G->numvex; i++ )
        {
            if( lowcost[i] != 0 && lowcost[i] < min )
            {
                min = lowcost[i];
                minptr = i;
            }
        }
        lowcost[minptr] = 0;

        for( i = 0; i < G->numvex; i++ )
        {
            int newcost = G->edge[minptr][i] + min;         //更新路线，prevex到找到的下一个顶点+找到顶点到剩余顶点路径
            if( lowcost[i] != 0 && lowcost[i] > newcost )
            {
                lowcost[i] = newcost;
                prevex[i] = minptr;
            }
        }
    }
    delete lowcost;
    for(i=0; i < G->numvex ;i++)
    {
        std::cout << prevex[i] << " ";
    }

    return prevex;
}

void Search( AdjMatrix *G, int *prevex)
{
    char contin;
    while(1)
    {
        int finish;
        int start = 0;
        std::cout << "\n\n输入需要查找的结束顶点";
        std::cin >> finish;
        std::cin.ignore();

        int stack[MAX];
        int top = 0;
        memset(stack, 0, sizeof(stack));

        do
        {
            stack[top++] = finish;
            finish = prevex[finish];
        }while( finish != start );
        
        std::cout << G->vex[start] << " -> ";
        while( top != 0 )
        {
            std::cout << G->vex[stack[--top]] << " -> ";
        }
        std::cout << "^\n\n";

        std::cout << "是否重新查找：";
        std::cin >> contin;
        std::cin.ignore();
        if( 'N' == contin || 'n' == contin )
        {
            break;
        }
    }
}

void Destroy( AdjMatrix *G, int **p )
{
    delete G->vex;
    G->vex = NULL;
    for( int i=0; i < G->numvex; i++ )
    {
        delete G->edge[i];
        G->edge[i] = NULL;
    }
    delete G->edge;
    G->edge = NULL;
    delete *p;
    *p = NULL;
}