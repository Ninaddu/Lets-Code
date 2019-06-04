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


Status Search( pNode T, pNode *p, Elemtype e );               //查找二叉树中是否存在e
void Insert( pNode *T, int *array, int n );                 //将array中数字插入二叉树
void Delete( pNode *T, int *array, int n );                 //将array中数字从二叉树删除
void Show( pNode T );                                       //显示树节点
void Destroy( pNode *T );                                   //销毁树


int main()
{
    pNode t = NULL;
    char next;
    while( 1 )
    {
        std::cout << "功能列表：\n\n1、插入\n\n2、显示\n\n3、查找\n\n4、删除\n\n5、退出\n\n";
        std::cout << "选择功能：";
        char choice;
        std::cin >> choice;
        std::cin.ignore(1000, '\n');
        switch (choice)
        {
            case '1':
            {
                int cnt1;
                std::cout << "\n输入插入数字的数量：";
                std::cin >> cnt1;
                Elemtype *array1 = new Elemtype[cnt1];
                std::cout << "\n输入需要插入的数字:";
                for( int i = 0; i < cnt1; i++ )
                {
                    std::cin >> array1[i];
                }
                std::cin.ignore(1000, '\n');                        //清空缓冲区中更多的输入  
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
                std::cout << "\n输入需要查找的数：";
                std::cin >> s3;
                std::cin.ignore(1000, '\n');
                pNode p = NULL;
                if( Search(t, &p, s3) )
                {
                    std::cout << "\n树种存在需要查找的数字\n\n";
                }
                else
                {
                    std::cout << "\n树种还不存在需要查找的数字\n\n";
                }              
                break;
            }
            case '4':
            {
                int cnt4;
                std::cout << "\n输入删除数字的数量：";
                std::cin >> cnt4;
                Elemtype *array4 = new Elemtype[cnt4];
                std::cout << "\n输入需要删除的数字:";
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
                std::cout << "\n输入不合法\n\n";
                break;
        }
        std::cout << "\n是否重新输入（输入N/n表示退出）：";
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
 * 功能：查找二叉树中是否存在e
 * 参数：树根节点；根节点前一个节点（传入为NULL，在函数中赋值并递归）；查找元素
 * 返回值：无
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
 * 功能：将array中数字插入二叉树
 * 参数：树节点地址的地址；需要插入的元素数组；元素数量
 * 返回值：无
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
            
            if( NULL == p )                 //没有进行第一轮递归，表示树根为空，直接在树根插入
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
            std::cout << "\n" << array[i] << "已经存在于树中，无法重复插入\n\n";
        }
    }
}  


/****************************************************************************************************
 * 功能：将array中数字从二叉树删除
 * 参数：树节点地址的地址；需要删除的元素数组；元素数量
 * 返回值：无
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
    else if( (*p)->lchild != NULL && (*p)->rchild != NULL )       //寻找左边最大子节点，填充当前位置；也可以寻找右边最小子节点
    {
        pNode q = *p;
        pNode temp = (*p)->lchild;                     //temp为删除节点左边最大节点，q为其前驱
        while( temp->rchild )
        {
            q = temp;
            temp = temp->rchild;
        }
        if( *p != q )                                //若p->lchild没有右子树，p->lchild就是最大子节点
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
            std::cout << "树中不存在" << array[i] << "\n\n";
        }
    }
}


/****************************************************************************************************
 * 功能：显示树节点
 * 参数：树节点地址
 * 返回值：无
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
 * 功能：销毁树
 * 参数：树节点地址的地址
 * 返回值：无
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