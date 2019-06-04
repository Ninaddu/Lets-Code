#include <iostream>
#include <cstring>
#define SUCCESS 1
#define FAIL    0

typedef char Elemtype;
typedef int Status;

typedef struct edge {
    int val;
    int weight;
    struct edge *next;
}edge;

typedef struct vexes {
    Elemtype data;
    int in;
    edge *first;
}vexes;

typedef struct Adjgraph {
    vexes *vexgroup;
    int numvex, numedge;
}Adjgraph;


void CreateGraph( Adjgraph *G );
Status Topological( Adjgraph *G, int *stack1, int *etv);
void CriticalPath( Adjgraph *G, int *stack1, int *etv);
void Destroy( Adjgraph *G, int **stack1, int **etv);


int main()
{
    Adjgraph g;
    g.vexgroup = NULL;
    CreateGraph(&g);
    int *stack1, *etv;
    try
    {
        stack1 = new int[g.numvex];
        memset(stack1, 0, sizeof(int) * g.numvex);
        etv = new int[g.numvex];
        memset(etv, 0, sizeof(int) * g.numvex);        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    if( Topological(&g, stack1, etv) )
    {
        CriticalPath(&g, stack1, etv);
    }
    Destroy(&g, &stack1, &etv);
    system("pause");
    return 0;
}


void CreateGraph( Adjgraph *G )
{
    std::cout << "���붥��ͱ�������";
    std::cin >> G->numvex >> G->numedge;
    std::cin.ignore();

    try
    {
        G->vexgroup = new vexes[G->numvex];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "\n\n���붥�㣺" << "\n\n";
    int i;
    for( i = 0; i < G->numvex; i++ )
    {
        std::cout << "��" << i+1 << "�����㣺";
        std::cin >> G->vexgroup[i].data;
        std::cin.ignore();
        G->vexgroup[i].in = 0;
        G->vexgroup[i].first = NULL;
    }

    std::cout << "\n\n����ߺ�Ȩֵ��" << "\n\n";
    int j, k;
    for( k = 0; k < G->numedge; k++ )
    {
        edge *p;
        try
        {
            p = new edge;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        std::cout << "��" << k+1 << "���ߺ�Ȩֵ��";
        std::cin >> i >> j >> p->weight;
        --i;
        --j;
        p->val = j;
        p->next = G->vexgroup[i].first;
        G->vexgroup[i].first = p;
        ++(G->vexgroup[j].in);
    }
    std::cout << "\n\n�ɹ������ڽӱ�(�ޣ���)V" << "\n\n";
}


/************************************************************************************************
*  ���ܣ��������·������·����ջ���Լ�·����ÿ���¼������㣩��������ʱ�䣨Ȩֵ֮�ͣ��������etv��
*  �������ڽӱ�ͼ�����ջָ�롢etv
*  ����ֵ��ִ�н��״̬
***********************************************************************************************/

Status Topological( Adjgraph *G, int *stack1, int *etv)
{
    int cnt = 0;
    int top0 = 0;
    int *stack0;
    try
    {
        stack0 = new int[G->numvex];
        memset(stack0, 0, sizeof(int) * G->numvex);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    int i;
    for( i = 0; i < G->numvex; i++ )
    {
        if( 0 == G->vexgroup[i].in )
        {
            stack0[top0++] = i;
        }
    }

    int top1 = 0;
    while( 0 != top0 )
    {
        ++cnt; 
        int temp = stack0[--top0];
        stack1[top1++] = temp;
        edge *p = G->vexgroup[temp].first;
        while( p )
        {
            if( 0 == --(G->vexgroup[p->val].in) )
            {
                stack0[top0++] = p->val;
            }
            if( etv[p->val] < etv[temp] + p->weight )           //����ö��������¼��ķ����¼�������������
            {
                etv[p->val] = etv[temp] + p->weight; 
            }
            p = p->next;
        }
    }

    delete stack0;
    stack0 = NULL;

    if( cnt < G->numvex )
    {
        std::cout << "\n\n����������·�����޷�����ؼ�·��o(�i�n�i)o" << "\n\n"; 
        return FAIL;
    }
    return SUCCESS;
}


/***********************************************************************************************
 * ���ܣ�����ͼ���¼���ջ��˳�򣬴Ӻ���ǰ����¼����緢��ʱ��ltv���ҵ�etv��ltv����ͬ�ķ���ʱ�伴Ϊ�ؼ�·��
 * ������ͼ����������õ�Stack1��etv
 * ����ֵ����
************************************************************************************************/

void CriticalPath( Adjgraph *G, int *stack1, int *etv)
{
    int *ltv;
    int top = G->numvex;
    try
    {
        ltv = new int[G->numvex];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    int i;
    int ltv_max = etv[--top];
    for( i = 0; i < G->numvex; i++ )           //��ʼ��ltvΪ���ִ���¼��ķ���ʱ�䣻ע�⣬��ʱtop�Ѿ�ָ��ջ����һ��Ԫ��
    {
        ltv[i] = ltv_max;
    }

    //����stack1��ջ˳�򣬴Ӻ���ǰ�Ƶ������и����¼������緢��ʱ��
    while( 0 != top )
    {
        //ͨ������tempΪ�±��¼������ӵ������¼������temp����ʱ��
        int temp = stack1[--top];                           
        edge *p = G->vexgroup[temp].first;
        while( p )
        {
            if( ltv[temp] > ltv[p->val] - p->weight )
            {
                ltv[temp] = ltv[p->val] - p->weight;
            }
            p = p->next;
        }
    }

    //�õ�etv��ltv���ҵ����з���ʱ����ͬ�¼�����������ؼ�·��
    std::cout << "����ؼ�·����" << "\n\n";
    for( i = 0; i < G->numvex; i++ )
    {
        if( etv[i] == ltv[i] )
        {
            std::cout << G->vexgroup[i].data << " -> ";
        }
    }
    std::cout << "^\n\n";
    delete ltv;
    ltv = NULL;
}

void Destroy( Adjgraph *G, int **stack1, int **etv)
{
    delete *stack1;
    stack1 = NULL;
    delete *etv;
    *etv = NULL;
    for( int i = 0; i < G->numvex; i++ )
    {
        edge *q, *p = G->vexgroup[i].first;
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
}