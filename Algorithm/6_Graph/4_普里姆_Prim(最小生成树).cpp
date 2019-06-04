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

//�ڽӾ�����ͼ�ṹ
void CreateGraph( AdjMatrix *G )
{
    std::cout << "����ͼ�ж���ͱߵ�������";
    std::cin >> G->numvex >> G->numedge;
    std::cin.ignore();
    std::cout << "\n\n";

    std::cout << "���붥�㣺" << "\n\n";
    int i;
    for( i = 0; i < G->numvex; i++ )
    {
        std::cout << "��" << i+1 << "�����㣺";
        std::cin >> G->vex[i];
        std::cin.ignore();
    }

    int j;
    for( i = 0; i < G->numvex; i++ )                        //�߾����ʼ��
    {
        for( j = 0; j < G->numvex; j++ )
        {
            G->edge[i][j] = (i==j)? 0 : INFINITY; 
        }
    }

    std::cout << "\n\n����ߣ�" << "\n\n";
    int k, w;
    j = 0;
    for( i = 0; i < G->numedge; i++ )
    {
        std::cout << "��" << i+1 << "���ߺͱ��ϵ�Ȩֵ��";
        std::cin >> k >> j >> w;
        --k;
        --j;
        G->edge[k][j] = w;
        G->edge[j][k] = w;
    }
    std::cout << "\n�ɹ������ڽӾ���ͼ��(#^.^#)" << "\n\n";
}

/***********************************************************************************
 * ���ƣ���³ķ�㷨
 * ���ܣ���ĳ��������������������ͼȨֵ֮����̵�·��
 * �������ڽӾ���ͼ
 * ����ֵ����
 * ���̣������ؼ����飬lowcost[]��¼�ӵ�ǰ�����Խ��ʣ������δ������������·�ߣ�
 *      һ������ĳ�����㣬lowcost��Ϊ0��
 *      prevex[]�����һ�������ǰ�����㣬ÿ�����¸���lowcostʱ��prevexҲ�û�Ϊ���������·�ߵ�ǰ��
 ***********************************************************************************/
void Prim( AdjMatrix *G )
{
    int *prevex = new int[G->numvex];
    int *lowcost = new int[G->numvex];

    int i;
    for( i = 0; i < G->numvex; i++ )                    //��ʼ���������飬��vex[0]Ϊ���
    {
        prevex[i] = 0;
        lowcost[i] = G->edge[0][i];
    }

    int min, minptr;
    for( int cnt = 0; cnt < G->numvex - 1; cnt++ )          //��������ѭ��G->numvex - 1�Σ�����vex[0]��ʼ���������ж���
    {
        min = INFINITY;
        minptr = 1;
        for( i = 0; i < G->numvex; i++ )                //�ҵ���һ�����㣬���ת��·�ߺͶ�ӦȨֵ��xx->xx  xx��
        {
            if( lowcost[i] != 0 && lowcost[i] < min )
            {
                minptr = i;
                min = lowcost[i];
            }
        }
        //        һ�¸�Ȩֵ��С�����ǰ������           ��һ��Ȩֵ��С����                ��СȨֵ
        std::cout << G->vex[prevex[minptr]] << " -> " << G->vex[minptr] << "  " << lowcost[minptr] << "\n";
        lowcost[minptr] = 0;

        //�ҵ�����һ���㣬����Ŀǰ�ҵ����ж��㵽ʣ�����ж����lowcost����
        for( i = 0; i < G->numvex; i++ )
        {
            if( G->edge[minptr][i] != 0 && G->edge[minptr][i] < lowcost[i] )
            {
                lowcost[i] = G->edge[minptr][i];
                prevex[i] = minptr;                     //����ǰ������
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
 
