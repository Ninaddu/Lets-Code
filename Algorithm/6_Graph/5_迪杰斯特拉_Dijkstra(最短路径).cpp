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
    std::cout <<"����ͼ�еĶ���ͱ�������";
    std::cin >> G->numvex >> G->numedge;
    std::cin.ignore();


    //����vex��edge����ռ䲢��ʼ��
    int i;
    try
    {
        G->vex = new Elemtype[G->numvex + 1];
        memset(G->vex, '\0', sizeof(Elemtype) * (G->numvex + 1));
        G->edge = new int *[G->numvex];         //ָ������
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
        std::cout << "��" << k+1 << "���ߣ�"; 
        std::cin >> i >> j >> w;
        --i;
        --j;
        G->edge[i][j] = w;
        G->edge[j][i] = w;
    }
    std::cout << "\n\n�ɹ������ڽӾ���" << "\n\n";
}


/*******************************************************************************************
 * ���ܣ�Ѱ�Ҵ�ĳ�����㵽�������ж�������·���������lowcost������
 * �������ڽӾ���
 * ����ֵ�����·��ǰ���ڵ�����ĵ�ַ
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
        lowcost[i] = G->edge[0][i];                         //��ʼ��lowcostΪA��㵽�������ж��㿪ʼ��Ȩֵ
        prevex[i] = 0;                                       //��ʼ��prevexȫ��ΪA(0)
    }

    int cnt;                                                //��������ѭ��G->numvex - 1�ο��ҵ�ʣ�����ж���
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
            int newcost = G->edge[minptr][i] + min;         //����·�ߣ�prevex���ҵ�����һ������+�ҵ����㵽ʣ�ඥ��·��
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
        std::cout << "\n\n������Ҫ���ҵĽ�������";
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

        std::cout << "�Ƿ����²��ң�";
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