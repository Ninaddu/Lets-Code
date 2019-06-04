/**********************************************************************************************
 * 四层优化：
 * 1、三点取一做基准
 * 2、插入查找
 * 3、与基准相等元素聚拢
 * 4、尾递归
 **********************************************************************************************/
#include <iostream>
#include <cstdlib>
#include <time.h>
#define MAX     30
#define SIZE    25
#define INSERT_SIZE  7


void Exchange( int *x, int *y )
{
    *x = *x ^ *y;
    *y = *y ^ *x;
    *x = *x ^ *y;
}


/**********************************************************************************************
 * 功能：三点取一选取基准点比较，比较过程中相等元素放两边，最后放基准点两边
 * 参数：待排序数组；首元素下标；尾元素下标；排序后与基准点相同首元素前一个元素下标 变量地址；
 *       排序后与基准点相同尾元素后一个元素下标 变量地址
 * 返回值：无
 **********************************************************************************************/

void Patition( int *array, int start, int finish, int *pos1, int *pos2 )
{
    //将首、中、尾元素中大小为中元素作为基准，转到首元素
    int mid = (start + finish) >> 1;
    if( array[mid] > array[start] )             
    {
        Exchange(&array[mid], &array[start]);
    }
    if( array[mid] > array[finish] )
    {
        Exchange(&array[mid], &array[finish]);
    }
    if( array[finish] < array[start] )
    {
        Exchange(&array[finish], &array[start]);
    }

    int min = start, max = finish;
    int min_cnt = 0, max_cnt = 0;
    int pos = array[start];

    //比pos小的数都置左，大置右，相等置两边
    while( start < finish )
    {
        while( array[finish] >= pos && start < finish )
        {
            if( array[finish] == pos )
            {
                Exchange(&array[finish], &array[max-max_cnt]);
                ++max_cnt;
            }
            --finish;
        }
        if( start < finish )
        {
            array[start++] = array[finish];               //start此时即基准点所在下标，交换后基准点到finish处
        }

        while( array[start] <= pos && start < finish )
        {
            if( array[start] == pos )
            {
                Exchange(&array[start], &array[min+min_cnt]);
                ++min_cnt;
            }
            ++start;
        }
        if( start < finish )
        {
            array[finish--] = array[start];
        }
    }
    array[start] = pos;

    //以下将两边相等元素向基准点聚拢
    *pos1 = start - 1;                             //先使得左右pos等于基准点左右点，相等元素聚拢后再调整
    *pos2 = start + 1;  
    for( int i=0; i < min_cnt; ++i )                //最左边与基准相等数字移至中轴
    {
        Exchange(&array[min+i], &array[*pos1]);
        --(*pos1);
    }
    for( int i=0; i < max_cnt; ++i )                //右边，同上
    {
        Exchange(&array[max-i], &array[*pos2]);
        ++(*pos2);
    }
}


/**********************************************************************************************
 * 功能：插入排序
 * 参数：待排序数组；数组元素个数
 * 返回值：无
 **********************************************************************************************/

void InsertSorting( int *array, int n )
{
    for( int i=1; i < n; i++ )
    {
        if( array[i] < array[i-1] )
        {
            int temp = array[i];
            int j;
            for( j=i-1; j >= 0 && array[j] >temp; j-- )
            {
                array[j+1] = array[j];
            }
            array[j+1] = temp;
        }
    }
}


void InsertSort( int *array, int start, int finish )
{
    InsertSorting( array+start, finish-start+1 );
}


/**********************************************************************************************
 * 功能：尾递归实现快排
 * 参数：待排序数组；首元素下标；尾元素下标
 * 返回值：无
 **********************************************************************************************/

void Quick_Sorting( int *array, int start, int finish )
{
    if( start < finish )
    {
        if( finish - start <= INSERT_SIZE )
        {
            InsertSort(array, start, finish);
        }
        else
        {
            int pos1, pos2;
            Patition(array, start, finish, &pos1, &pos2);  //pos1，pos2作为一轮交换后前后基准点（重复导致基准不同）
                                                           //传入Patition函数，

            int start_next = start;                        //以基准点分为两部分递归
            int finish_next = pos1;
            for( int i=2; i > 0; i-- )                                 
            {
                Quick_Sorting(array, start_next, finish_next);
                start_next = pos2;
                finish_next = finish;
            }
        }       
    }
}


void Quick_Sort( int *array, int n )
{
    Quick_Sorting(array, 0, n-1);
}


int main()
{
    int array[MAX] = {0};
    srand(time(0));
    for( int i = 0; i < SIZE; i++ )             //随机生成25个数字
    {
        array[i] = rand()%100;
    }
    for( int i = 0; i < SIZE; i++ )
    {
        std::cout << array[i] << " ";
    }
    std::cout << "\n\n";

    Quick_Sort(array, SIZE);
    for( int i = 0; i < SIZE; i++ )
    {
        std::cout << array[i] << " ";
    }
    std::cout << "\n\n";
    system("pause");
    return 0;
}