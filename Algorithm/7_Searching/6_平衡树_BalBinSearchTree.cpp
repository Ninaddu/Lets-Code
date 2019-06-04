#include <iostream>
#include <cstring>
#define TRUE    1
#define FALSE   0
#define EH      0
#define LH      1
#define RH      -1


typedef int Elemtype;
typedef int Status;

typedef struct Node {
    Elemtype data;
    struct Node *lchild, *rchild;
    Status bf;
}Node, *pNode;


Status Search( pNode T, Elemtype e );               //����ƽ����������Ƿ����e
void LeftBalance( pNode *T );                       //��ƽ��
void RightBalance( pNode *T );                      //��ƽ��
void LeftRotate( pNode *T );                        //����
void RightRotate( pNode *T );                       //����
Status Insert( pNode *T, int e, int *taller );      //��array�����ֲ��������
Status Delete( pNode *T, int e, int *taller );      //��array�����ִӶ�����ɾ��
void Delete_Node( pNode *T );                       //����������Ľڵ�ɾ������
void Show( pNode T );                               //��ʾ���ڵ�
void Destroy( pNode *T );                           //������


int main()
{
    pNode t = NULL;
    while( 1 )
    {
        std::cout << "�����б�\n1������\n2����ʾ\n3������\n4��ɾ��\n5���˳�\n\n";
        std::cout << "ѡ���ܣ�";
        char choice;
        std::cin >> choice;
        std::cin.ignore(1000, '\n');
        switch (choice)
        {
            case '1':
            {
                int cnt1;
                std::cout << "\n����������ֵ�������";
                std::cin >> cnt1;
                std::cin.ignore(1000, '\n');
                Elemtype insert_data;
                std::cout << "\n������Ҫ�����" << cnt1 << "������:";
                for( int i = 0; i < cnt1; i++ )
                {
                    Status taller1 = 0;
                    std::cin >> insert_data;
                    Insert(&t, insert_data, &taller1);
                }
                std::cin.ignore(1000, '\n');                        //��ջ������и�������� 
                break;
            }
            case '2':
                Show(t); 
                std::cout << "\n";
                break;
            case '3':
            {
                Elemtype s3;
                std::cout << "\n������Ҫ���ҵ�����";
                std::cin >> s3;
                std::cin.ignore(1000, '\n');
                pNode p = NULL;
                TRUE == Search(t, s3) ? std::cout << "\n���д�����Ҫ���ҵ�����\n\n":
                                        std::cout << "\n���л���������Ҫ���ҵ�����\n\n";              
                break;
            }
            case '4':
            {
                int cnt4;
                std::cout << "\n����ɾ�����ֵ�������";
                std::cin >> cnt4;
                std::cin.ignore(1000, '\n');
                Elemtype delete_data;
                std::cout << "\n������Ҫɾ����" << cnt4 << "������:";
                for( int i = 0; i < cnt4; i++ )
                {
                    Status taller4;
                    std::cin >> delete_data;
                    Delete(&t, delete_data, &taller4);
                }
                std::cin.ignore(1000, '\n'); 
                break;
            }
            case '5':
                Destroy(&t);
                exit(0);
                break;
            default:
                std::cout << "\n���벻�Ϸ�\n\n";
                break;
        }
        std::cout << "\n";
    }
    return 0;  
}



/**********************************************************************************************
 * ���ܣ�����ƽ����������Ƿ����e
 * ���������ڵ��ַ��������Ԫ��
***********************************************************************************************/

Status Search( pNode T, Elemtype e )
{
    if( !T )
    {
        return FALSE;
    }
    if( e == T->data )
    {
        return TRUE;
    }
    else if( e < T->data )
    {
        Search(T->lchild, e);
    }
    else if( e > T->data )
    {
        Search(T->rchild, e);
    }
} 


/***********************************************************************************************
 * ���ܣ�ƽ��ڵ�
 * ������ʧ��Ľڵ��ַ��ַ
 * ����ֵ����
************************************************************************************************/

void LeftBalance( pNode *T )
{
    pNode L = (*T)->lchild;
    switch( L->bf )
    {
        case LH:                                    //��ѡ���
            RightRotate(T);
            (*T)->bf = EH;                          //�����ı�Ľڵ�bf״̬
            L->bf = EH;
            break;
        case RH:
        {
            pNode Lr = L->rchild;
            switch( Lr->bf )
            {
                case LH:
                    (*T)->bf = RH;
                    L->bf = EH;
                    break;
                case EH:
                    (*T)->bf = EH;
                    L->bf = EH;
                    break;
                case RH:
                    (*T)->bf = EH;
                    L->bf = LH;
                    break;
            }
            Lr->bf = EH;
            LeftRotate(&(*T)->lchild);
            RightRotate(T);
            break;
        }
    }
}


void RightBalance( pNode *T )
{
    pNode R = (*T)->rchild;
    switch( R->bf )
    {
        case RH:
            LeftRotate(T);
            (*T)->bf = EH;
            R->bf = EH;
            break;
        case LH:
        {
            pNode Rl = R->lchild;
            switch( Rl->bf )
            {
                case RH:
                    (*T)->bf = LH;
                    R->bf = EH;
                    break;
                case EH:
                    (*T)->bf = EH;
                    R->bf = EH;
                    break;
                case LH:
                    (*T)->bf = EH;
                    R->bf = RH;
                    break;
            }
            Rl->bf = EH;
            RightRotate(&(*T)->rchild);
            LeftRotate(T);
            break;
        }
    }
}


/***********************************************************************************************
 * ���ܣ���ת�ڵ�
 * ��������Ҫ��ת�Ľڵ��ַ��ַ
 * ����ֵ����
************************************************************************************************/

void LeftRotate( pNode *T )
{
    pNode L = (*T)->rchild;
    (*T)->rchild = L->lchild;
    L->lchild = *T;
    *T = L;
}


void RightRotate( pNode *T )
{
    pNode L = (*T)->lchild;
    (*T)->lchild = L->rchild;
    L->rchild = *T;
    *T = L;
}


/***********************************************************************************************
 * ���ܣ���array�����ֲ��������
 * �����������ڵ��ַ�ĵ�ַ����Ҫ��������ݣ�����״̬��¼
 * ����ֵ����
************************************************************************************************/

Status Insert( pNode *T, int e, int *taller )
{
    if( !(*T) )
    {
        *T = new Node;
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->bf = EH;
        *taller = TRUE;
        return TRUE;
    }
    if( e == (*T)->data )
    {
        std::cout << "ƽ�������Ѿ�����" << e << "���޷��ظ�����\n\n";
        return FALSE;
    }
    else if( e < (*T)->data )
    {
        if( FALSE == Insert(&(*T)->lchild, e, taller) )
        {
            return FALSE;
        }

        if( TRUE == *taller )
        {
            switch( (*T)->bf )
            {
                case LH:
                    LeftBalance(T);
                    *taller = FALSE;                        //��ƽ������ĸ߶Ȼָ�
                    break;
                case EH:
                    (*T)->bf = LH;
                    *taller = TRUE;
                    break;
                case RH:
                    (*T)->bf = EH;
                    *taller = FALSE;
                    break;
            }
        }
    }
    else if( e > (*T)->data )
    {
        if( FALSE == Insert(&(*T)->rchild, e, taller) )
        {
            return FALSE;
        }

        if( TRUE == *taller )
        {
            switch( (*T)->bf )
            {
                case RH:
                    RightBalance(T);
                    *taller = FALSE;                        //��ƽ������ĸ߶Ȼָ�
                    break;
                case EH:
                    (*T)->bf = RH;
                    *taller = TRUE;
                    break;
                case LH:
                    (*T)->bf = EH;
                    *taller = FALSE;
                    break;
            }
        }
    }
}


/***********************************************************************************************
 * ���ܣ���array�����ִӶ�������ɾ��
 * �����������ڵ��ַ�ĵ�ַ����Ҫɾ�������ݣ�ɾ��״̬��¼
 * ����ֵ����
************************************************************************************************/

void Delete_Node( pNode *T )                        //�����������ɾ������
{
    if( NULL == (*T)->lchild )
    {
        pNode p = *T;
        *T = (*T)->rchild;
        delete p;
    }
    else if( NULL == (*T)->rchild )
    {
        pNode p = *T;
        *T = (*T)->lchild;
        delete p;
    }
    else if( (*T)->rchild && (*T)->lchild )
    {
        pNode p = *T;
        pNode q = p->rchild;
        while( q->lchild )
        {
            p = q;
            q = q->lchild;
        }
        if( p != *T )
        {
            p->lchild = q->rchild;
            q->rchild = (*T)->rchild;
        }    
        q->lchild = (*T)->lchild;
        *T = q;
    }
}

Status Delete( pNode *T, int e, int *taller )
{
    if( !(*T) )
    {
        std::cout << "���в�����" << e << "���޷�ɾ��\n\n";
        return FALSE;
    }

    if( e == (*T)->data )
    {
        Delete_Node(T);
        *taller = TRUE;                
        return TRUE;
    }
    else if( e < (*T)->data )
    {
        if( FALSE == Delete(&(*T)->lchild, e, taller) )
        {
            return FALSE;
        }

        if( TRUE == *taller )
        {
            switch( (*T)->bf )
            {
                case LH:
                    (*T)->bf = EH;
                    *taller = TRUE;
                    break;
                case EH:
                    (*T)->bf = RH;
                    *taller = FALSE;
                    break;
                case RH:
                    RightBalance(T);
                    *taller = TRUE;
                    break;
            }
        }
    }
    else if( e > (*T)->data )
    {
        if( FALSE == Delete(&(*T)->rchild, e, taller) )
        {
            return FALSE;
        }

        if( TRUE == *taller )
        {
            switch( (*T)->bf )
            {
                case RH:
                    (*T)->bf = EH;
                    *taller = TRUE;
                    break;
                case EH:
                    (*T)->bf = LH;
                    *taller = FALSE;
                    break;
                case LH:
                    LeftBalance(T);
                    *taller = TRUE;
                    break;
            }
        }
    }
}


/***********************************************************************************************
 * ���ܣ���ʾ���ڵ�
 * �����������ڵ��ַ
 * ����ֵ����
************************************************************************************************/

void Show( pNode T )
{
    if( T )
    {
        Show( T->lchild );
        std::cout << T->data << " ";
        Show( T->rchild );
    }
}


/***********************************************************************************************
 * ���ܣ�������
 * �����������ڵ��ַ�ĵ�ַ
 * ����ֵ����
************************************************************************************************/

void Destroy( pNode *T )
{
    if( *T )
    {
        Destroy( &(*T)->lchild );
        Destroy( &(*T)->rchild );
        delete *T;
        *T = NULL;
    }
}