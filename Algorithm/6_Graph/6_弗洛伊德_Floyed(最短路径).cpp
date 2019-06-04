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
    std::cout << "����ͼ�ж���ͱ�������";
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


    std::cout << "\n\n���붥�㣺" << "\n\n";
    for( i = 0; i < G->numvex; i++ )
    {
        std::cout << "��" << i+1 << "�����㣺";
        std::cin >> G->vex[i];
        std::cin.ignore();
    }

    int k, w;
    std::cout << "\n\n����ߣ�" << "\n\n";
    for( k = 0; k < G->numedge; k++ )
    {
        std::cout << "��" << k+1 << "���ߺ�Ȩֵ��";
        std::cin >> i >> j >> w;
        --i;
        --j;
        G->edge[i][j] = w;
        G->edge[j][i] = w;
    }
    
    std::cout << "\n\n�ɹ������ڽӾ���(#^.^#)\n\n";
}


/************************************************************************************************
 * ���ܣ�ͨ������lowcost��ά���飬���ϸı�ǰ���������飨prevex�����ҵ����ж����Ӧ�������������������·��
 * �������ڽӾ���ͼ
 * ����ֵ������·�߾����ַ
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
            prevex[i][j] = i;                               //ǰ�������ʼ��Ϊ�����ж�Ӧ�Ļ�ͷ����β
            lowcost[i][j] = G->edge[i][j];                  //���·����ʼ��ΪĿǰ�ڽӾ�����·�����
        }
    }
    
    //O(n^3)
    for( k = 0; k < G->numvex; k++ )     //��ĳ��������Ϊ·����Ȼ����֮�����õ��ö��㵽�������ж�������·��
    {                                    //kѭ��������ÿ�����������������
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