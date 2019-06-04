#include <iostream>
#include <string.h>
#define TRUE    1
#define FALSE   0


typedef int Elemtype;
typedef int Status;

typedef struct Node {
    Elemtype data;
    struct Node *lchild, *rchild;
}Node, *pNode;


Status Search( pNode T, pNode *p, Elemtype e );               //���Ҷ��������Ƿ����e
void Insert( pNode *T, int *array, int n );                 //��array�����ֲ��������
void Delete( pNode *T, int *array, int n );                 //��array�����ִӶ�����ɾ��
void Show( pNode T );                                       //��ʾ���ڵ�
void Destroy( pNode *T );                                   //������


int main()
{
    pNode t = NULL;
    char next;
    while( 1 )
    {
        std::cout << "�����б�\n\n1������\n\n2����ʾ\n\n3������\n\n4��ɾ��\n\n5���˳�\n\n";
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
                Elemtype *array1 = new Elemtype[cnt1];
                std::cout << "\n������Ҫ���������:";
                for( int i = 0; i < cnt1; i++ )
                {
                    std::cin >> array1[i];
                }
                std::cin.ignore(1000, '\n');                        //��ջ������и��������  
                Insert(&t, array1, cnt1);
                delete array1;
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
                if( Search(t, &p, s3) )
                {
                    std::cout << "\n���ִ�����Ҫ���ҵ�����\n\n";
                }
                else
                {
                    std::cout << "\n���ֻ���������Ҫ���ҵ�����\n\n";
                }              
                break;
            }
            case '4':
            {
                int cnt4;
                std::cout << "\n����ɾ�����ֵ�������";
                std::cin >> cnt4;
                Elemtype *array4 = new Elemtype[cnt4];
                std::cout << "\n������Ҫɾ��������:";
                for( int i = 0; i < cnt4; i++ )
                {
                    std::cin >> array4[i];
                }
                std::cin.ignore(1000, '\n');
                Delete(&t, array4, cnt4);
                delete array4; 
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
        std::cout << "\n�Ƿ��������루����N/n��ʾ�˳�����";
        std::cin >> next;
        std::cin.ignore(1000, '\n');
        if( next == 'N' || next == 'n' )
        {
            break;
        }
        std::cout << "\n\n";
    }
    Destroy(&t);
    return 0;  
}



/****************************************************************************************************
 * ���ܣ����Ҷ��������Ƿ����e
 * �����������ڵ㣻���ڵ�ǰһ���ڵ㣨����ΪNULL���ں����и�ֵ���ݹ飩������Ԫ��
 * ����ֵ����
 ****************************************************************************************************/

Status Search( pNode T, pNode *p, Elemtype e )
{
    if( !T )
    {
        return FALSE;
    }
    if( e == T->data )
    {
        *p = T;
        return TRUE;
    }
    else if( e < T->data )
    {
        *p = T;
        Search( T->lchild, p, e ); 
    }
    else if( e > T->data )
    {
        *p = T;
        Search( T->rchild, p, e ); 
    }
}


/****************************************************************************************************
 * ���ܣ���array�����ֲ��������
 * ���������ڵ��ַ�ĵ�ַ����Ҫ�����Ԫ�����飻Ԫ������
 * ����ֵ����
 ****************************************************************************************************/

void Insert( pNode *T, int *array, int n )
{
    for(int i = 0; i < n; i++ )
    {
        pNode p = NULL;
        if( FALSE == Search(*T, &p, array[i]) )
        {
            pNode q = new Node;
            q->data = array[i];
            q->lchild = NULL;
            q->rchild = NULL;
            
            if( NULL == p )                 //û�н��е�һ�ֵݹ飬��ʾ����Ϊ�գ�ֱ������������
            {
                *T = q;
            }
            else if( array[i] < p->data )
            {
                p->lchild = q;
            }
            else if( array[i] > p->data )
            {
                p->rchild = q;
            }
        }
        else
        {
            std::cout << "\n" << array[i] << "�Ѿ����������У��޷��ظ�����\n\n";
        }
    }
}  


/****************************************************************************************************
 * ���ܣ���array�����ִӶ�����ɾ��
 * ���������ڵ��ַ�ĵ�ַ����Ҫɾ����Ԫ�����飻Ԫ������
 * ����ֵ����
 ****************************************************************************************************/

void Delete_Node( pNode *p )
{
    if( (*p)->lchild == NULL )
    {
        pNode q = *p;
        *p = (*p)->rchild;
        delete q;
    }
    else if( (*p)->rchild == NULL )
    {
        pNode q = *p;
        *p = (*p)->lchild;
        delete q;
    }
    else if( (*p)->lchild != NULL && (*p)->rchild != NULL )       //Ѱ���������ӽڵ㣬��䵱ǰλ�ã�Ҳ����Ѱ���ұ���С�ӽڵ�
    {
        pNode q = *p;
        pNode temp = (*p)->lchild;                     //tempΪɾ���ڵ�������ڵ㣬qΪ��ǰ��
        while( temp->rchild )
        {
            q = temp;
            temp = temp->rchild;
        }
        if( *p != q )                                //��p->lchildû����������p->lchild��������ӽڵ�
        {
            q->rchild = temp->lchild;   
            temp->lchild = (*p)->lchild;
        }
        temp->rchild = (*p)->rchild;
        delete p;
        *p = temp;                            
    }
}

Status Delete_Search( pNode *T, int n )
{
    if( !(*T) )
    {
        return FALSE;
    }
    if( n == (*T)->data )
    {
        Delete_Node(T);
        return TRUE;
    }
    else if( n < (*T)->data )
    {
        Delete_Search(&(*T)->lchild, n);
    }
    else if( n > (*T)->data )
    {
        Delete_Search(&(*T)->rchild, n);
    }
}

void Delete( pNode *T, int *array, int n )
{
    for( int i = 0; i < n; i++  )
    {
        if( FALSE == Delete_Search(T, array[i]) )
        {
            std::cout << "���в�����" << array[i] << "\n\n";
        }
    }
}


/****************************************************************************************************
 * ���ܣ���ʾ���ڵ�
 * ���������ڵ��ַ
 * ����ֵ����
 ****************************************************************************************************/

void Show( pNode T )
{
    if( !T )
    {
        return;
    }
    Show( T->lchild );
    std::cout << T->data << " ";
    Show( T->rchild );
}


/****************************************************************************************************
 * ���ܣ�������
 * ���������ڵ��ַ�ĵ�ַ
 * ����ֵ����
 ****************************************************************************************************/
void Destroy( pNode *T )
{
    if( !(*T) )
    {
        return;
    }
    Destroy( &(*T)->lchild );
    Destroy( &(*T)->rchild );
    delete *T;
}