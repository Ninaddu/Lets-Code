#include <iostream>
#include <stdlib.h>
#define MAXSIZE     20
#define INFINITY    65535

typedef char Elemtype;

typedef struct AdjMatrix {
    Elemtype vex[MAXSIZE];
    int edge[MAXSIZE][MAXSIZE];
    int numvex, numedge;
}AdjMatrix;

//邻接矩阵建立图结构
void CreateGraph( AdjMatrix *G )
{
    std::cout << "输入图中顶点和边的数量：";
    std::cin >> G->numvex >> G->numedge;
    std::cin.ignore();
    std::cout << "\n\n";

    std::cout << "输入顶点：" << "\n\n";
    int i;
    for( i = 0; i < G->numvex; i++ )
    {
        std::cout << "第" << i+1 << "个顶点：";
        std::cin >> G->vex[i];
        std::cin.ignore();
    }

    int j;
    for( i = 0; i < G->numvex; i++ )                        //边矩阵初始化
    {
        for( j = 0; j < G->numvex; j++ )
        {
            G->edge[i][j] = (i==j)? 0 : INFINITY; 
        }
    }

    std::cout << "\n\n输入边：" << "\n\n";
    int k, w;
    j = 0;
    for( i = 0; i < G->numedge; i++ )
    {
        std::cout << "第" << i+1 << "条边和边上的权值：";
        std::cin >> k >> j >> w;
        --k;
        --j;
        G->edge[k][j] = w;
        G->edge[j][k] = w;
    }
    std::cout << "\n成功生成邻接矩阵图！(#^.^#)" << "\n\n";
}

/***********************************************************************************
 * 名称：普鲁姆算法
 * 功能：从某个顶点出发，求遍历整个图权值之和最短的路线
 * 参数：邻接矩阵图
 * 返回值：无
 * 过程：两个关键数组，lowcost[]记录从当前顶点跨越到剩下所有未遍历顶点的最短路线；
 *      一旦遍历某个顶点，lowcost即为0；
 *      prevex[]存放下一个顶点的前驱顶点，每次重新更新lowcost时，prevex也置换为可能是最短路线的前驱
 ***********************************************************************************/
void Prim( AdjMatrix *G )
{
    int *prevex = new int[G->numvex];
    int *lowcost = new int[G->numvex];

    int i;
    for( i = 0; i < G->numvex; i++ )                    //初始化两个数组，以vex[0]为起点
    {
        prevex[i] = 0;
        lowcost[i] = G->edge[0][i];
    }

    int min, minptr;
    for( int cnt = 0; cnt < G->numvex - 1; cnt++ )          //计数器，循环G->numvex - 1次，即从vex[0]开始遍历完所有顶点
    {
        min = INFINITY;
        minptr = 1;
        for( i = 0; i < G->numvex; i++ )                //找到下一个顶点，输出转移路线和对应权值“xx->xx  xx”
        {
            if( lowcost[i] != 0 && lowcost[i] < min )
            {
                minptr = i;
                min = lowcost[i];
            }
        }
        //        一下个权值最小顶点的前驱顶点           下一个权值最小顶点                最小权值
        std::cout << G->vex[prevex[minptr]] << " -> " << G->vex[minptr] << "  " << lowcost[minptr] << "\n";
        lowcost[minptr] = 0;

        //找到了下一个点，更新目前找到所有顶点到剩下所有顶点的lowcost函数
        for( i = 0; i < G->numvex; i++ )
        {
            if( G->edge[minptr][i] != 0 && G->edge[minptr][i] < lowcost[i] )
            {
                lowcost[i] = G->edge[minptr][i];
                prevex[i] = minptr;                     //更新前驱顶点
            }
        }
    }
    std::cout << "\n\n";
    delete prevex;
    delete lowcost;
}

int main()
{
    AdjMatrix g;
    CreateGraph(&g);
    Prim(&g);
    system("pause");
    return 0;
}
 
