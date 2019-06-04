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


Status Search( pNode T, Elemtype e );               //查找平衡二叉树中是否存在e
void LeftBalance( pNode *T );                       //左平衡
void RightBalance( pNode *T );                      //右平衡
void LeftRotate( pNode *T );                        //左旋
void RightRotate( pNode *T );                       //右旋
Status Insert( pNode *T, int e, int *taller );      //将array中数字插入二叉树
Status Delete( pNode *T, int e, int *taller );      //将array中数字从二叉树删除
void Delete_Node( pNode *T );                       //二叉查找树的节点删除方法
void Show( pNode T );                               //显示树节点
void Destroy( pNode *T );                           //销毁树


int main()
{
    pNode t = NULL;
    while( 1 )
    {
        std::cout << "功能列表：\n1、插入\n2、显示\n3、查找\n4、删除\n5、退出\n\n";
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
                std::cin.ignore(1000, '\n');
                Elemtype insert_data;
                std::cout << "\n输入需要插入的" << cnt1 << "个数字:";
                for( int i = 0; i < cnt1; i++ )
                {
                    Status taller1 = 0;
                    std::cin >> insert_data;
                    Insert(&t, insert_data, &taller1);
                }
                std::cin.ignore(1000, '\n');                        //清空缓冲区中更多的输入 
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
                TRUE == Search(t, s3) ? std::cout << "\n树中存在需要查找的数字\n\n":
                                        std::cout << "\n树中还不存在需要查找的数字\n\n";              
                break;
            }
            case '4':
            {
                int cnt4;
                std::cout << "\n输入删除数字的数量：";
                std::cin >> cnt4;
                std::cin.ignore(1000, '\n');
                Elemtype delete_data;
                std::cout << "\n输入需要删除的" << cnt4 << "个数字:";
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
                std::cout << "\n输入不合法\n\n";
                break;
        }
        std::cout << "\n";
    }
    return 0;  
}



/**********************************************************************************************
 * 功能：查找平衡二叉树中是否存在e
 * 参数：树节点地址；待查找元素
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
 * 功能：平衡节点
 * 参数：失衡的节点地址地址
 * 返回值：无
************************************************************************************************/

void LeftBalance( pNode *T )
{
    pNode L = (*T)->lchild;
    switch( L->bf )
    {
        case LH:                                    //单选情况
            RightRotate(T);
            (*T)->bf = EH;                          //调整改变的节点bf状态
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
 * 功能：旋转节点
 * 参数：需要旋转的节点地址地址
 * 返回值：无
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
 * 功能：将array中数字插入二叉树
 * 参数：树根节点地址的地址；需要插入的数据；插入状态记录
 * 返回值：无
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
        std::cout << "平衡树中已经存在" << e << "，无法重复插入\n\n";
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
                    *taller = FALSE;                        //左平衡后树的高度恢复
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
                    *taller = FALSE;                        //左平衡后树的高度恢复
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
 * 功能：将array中数字从二叉树中删除
 * 参数：树根节点地址的地址；需要删除的数据；删除状态记录
 * 返回值：无
************************************************************************************************/

void Delete_Node( pNode *T )                        //二叉查找树的删除方法
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
        std::cout << "树中不存在" << e << "，无法删除\n\n";
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
 * 功能：显示树节点
 * 参数：树根节点地址
 * 返回值：无
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
 * 功能：销毁树
 * 参数：树根节点地址的地址
 * 返回值：无
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