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
    Edge *edge;                                 //������
    Elemtype *vex;                              //��������     
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
    std::cout << "����ͼ�ж���ͱߵ�������";
    std::cin >> G->numvex >> G->numedge;
    std::cin.ignore();

    std::cout << "\n\n���붥�㣺" <<"\n";
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
        std::cout << "��" << i+1 << "�����㣺";
        std::cin >> G->vex[i];
        std::cin.ignore();  
    }

    std::cout << "\n\n����ߣ�" <<"\n";
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
        std::cout << "��" << i+1 << "���ߺͱ���Ȩ�أ�";
        std::cin >> j;
        G->edge[i].start = --j;
        std::cin >> k;
        G->edge[i].end = --k;
        std::cin >> G->edge[i].weight; 
    }
    std::cout << "\n\n�ɹ������߼����飡(#^.^#)" <<"\n\n";
}


//����G->edge[i].weight��С��edge[i]����ѡ��

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

//��Ȩֵ��С�߳�������firvex�����в��ұ������յ��Ƿ���ָ��Ķ��㣬�����Ƿ���ͬ������ͬ��ʾ·�����г̻��Σ�����һ���߽��бȽ�
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

//���ܣ�Ѱ��&�洢�ʼ��ǰ������
//������ǰ���������飻Ѱ�ҵĶ���
//����ֵ��ǰ������
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