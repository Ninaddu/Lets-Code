#include <iostream>
#include <string.h>
#define INFINITY   65535

typedef char Elemtype;
typedef struct AdjMatrix {
    Elemtype *vex;
    int **edge;
    int numvex, numedge;
}AdjMatrix;


void CreateGraph( AdjMatrix *G );
int **Floyed( AdjMatrix *G );
void Prnt( AdjMatrix *G, int **prevex );
void Destroy( AdjMatrix *G, int **prevex[] );


int main()
{
    AdjMatrix g;
    CreateGraph(&g);
    int **prevex = Floyed(&g);
    Prnt(&g, prevex);
    Destroy(&g, &prevex);
    system("pause");
    return 0;
}


void CreateGraph( AdjMatrix *G )
{
    std::cout << "输入图中顶点和边数量：";
    std::cin >> G->numvex >> G->numedge;
    std::cin.ignore();

    int i;
    try
    {
        G->vex = new Elemtype[G->numvex + 1];
        memset(G->vex, '\0', sizeof(Elemtype) * (G->numvex + 1));
        G->edge = new int*[G->numvex];
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
        std::cout << "第" << k+1 << "条边和权值：";
        std::cin >> i >> j >> w;
        --i;
        --j;
        G->edge[i][j] = w;
        G->edge[j][i] = w;
    }
    
    std::cout << "\n\n成功创建邻接矩阵！(#^.^#)\n\n";
}


/************************************************************************************************
 * 功能：通过更新lowcost二维数组，不断改变前驱顶点数组（prevex），找到所有顶点对应到所有其他顶点的最优路线
 * 参数：邻接矩阵图
 * 返回值：最优路线矩阵地址
*************************************************************************************************/
int **Floyed( AdjMatrix *G )
{
    int i, j, k;
    int **prevex, **lowcost;
    try
    {
        prevex = new int*[G->numvex];
        lowcost = new int*[G->numvex];
        for( i = 0; i < G->numvex; i++ )
        {
            prevex[i] = new int[G->numvex];
            lowcost[i] = new int[G->numvex];
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for( i = 0; i < G->numvex; i++ )
    {
        for( j = 0; j < G->numvex; j++ )
        {
            prevex[i][j] = i;                               //前驱顶点初始化为矩阵中对应的弧头、弧尾
            lowcost[i][j] = G->edge[i][j];                  //最短路径初始化为目前邻接矩阵中路径情况
        }
    }
    
    //O(n^3)
    for( k = 0; k < G->numvex; k++ )     //以某个顶点作为路径必然经过之处，得到该顶点到其他所有顶点最优路径
    {                                    //k循环，遍历每个顶点完成上述操作
        for( i = 0; i < G->numvex; i++ )
        {
            for( j = 0; j < G->numvex; j++ )
            {
                if( lowcost[i][j] > lowcost[i][k] + lowcost[k][j] )
                {
                    lowcost[i][j] = lowcost[i][k] + lowcost[k][j];
                    prevex[i][j] = k;
                }
            }
        }
    }

    for( i = 0; i < G->numvex; i++ )
    {
        delete lowcost[i];
    }
    return prevex;
}

void Prnt( AdjMatrix *G, int **prevex )
{
    for( int i = 0; i < G->numvex; i++ )
    {
        for( int j = 0; j < G->numvex; j++ )
        {
            std::cout.width(3);
            std::cout << std::left << G->vex[prevex[i][j]];
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}


void Destroy( AdjMatrix *G, int **prevex[] )
{
    delete G->vex;
    G->vex = NULL;
    for( int i = 0; i < G->numvex; i++ )
    {
        delete G->edge[i];
        G->edge[i] = NULL;
        delete (*prevex)[i];
        (*prevex)[i] = NULL;
    }
    delete **prevex;
    **prevex = NULL;
}