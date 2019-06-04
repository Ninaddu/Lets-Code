#include <iostream>
#define MAX     15
#define SIZE    10

//通过异或完成值传递
void Exchange( int *x, int *y )
{
    *x = *x ^ *y;
    *y = *y ^ *x;
    *x = *x ^ *y;
}


/*******************************************************************************
 * 功能：构造大顶对
 * 参数：数组，顶点下标，末尾下标
 * 返回值：无
 *******************************************************************************/
//方法一：通过递归构造大顶堆
void Heaping( int *array, int h, int n )
{ 
    int lchild = 2*h+1;
    int rchild = 2*h+2;
    if( lchild <= n )
    {
        if( rchild <= n && array[lchild] < array[rchild] )    //将较大数字放在左节点；若右子树为已排序数字无需比较
        {
            Exchange(&array[lchild], &array[rchild]);
        }
        if( array[h] >= array[lchild] )                 //顶点大于两叶子顶点，不需要交换  
        {
            return;
        }
        else                                    //顶点和较大叶子交换，并调整下面顺序
        {
            Exchange(&array[h], &array[lchild]);
            Heaping(array, lchild, n);
        }
    }
} 


//方法二：迭代构造大顶堆
void Heaping( int *array, int beg, int end )
{ 
    int parent = beg;
    int child = 2*parent + 1;
    for( ; child <= end; )
    {
        if( (child+1 <= end) && array[child] < array[child+1] ) //确保child下标所表示的数在end范围内是较大孩子
        {
            ++child;
        }
        if( array[parent] >= array[child] )
        {
            return;
        }
        else
        {
            Exchange(&array[parent], &array[child]);
            parent = child;
            child = 2*child + 1;
        }      
    }
}


/*******************************************************************************
 * 功能：借助完全二叉树性质完成数组排序
 * 1、节点h的叶子节点分别为2h+1、2h+2
 * 2、若数组中共有n个数据，最后一个有叶子的子节点是n/2-1完成排序
 * 参数：数组，节点数量
 * 返回值：无
 *******************************************************************************/
void Heap_Sort( int *array, int n )
{
    for( int i = n/2-1; i >= 0; i-- )     //构造第一轮大顶堆
    {
        Heaping(array, i, n-1);
    }

    for( int j = n-1; j > 0; j-- )
    {
        Exchange(&array[j], &array[0]);
        Heaping(array, 0, j-1);
    }
}


int main()
{
    int array[MAX] = {0, 5, 3, 9, 0, 81, -3, 100, 42, 30};
    Heap_Sort(array, SIZE);
    for( int i = 0; i < SIZE; i++ )
    {
        std::cout << array[i] << " ";
    }
    std::cout << "\n\n";
    system("pause");
    return 0;
}