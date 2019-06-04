#include <iostream>
#define INFINITY    65535
#define MAX     15
#define SIZE    10



static void Merging( int *array, int start, int gap, int n)
{
    int leftstr = start;
    int leftend = start + gap;
    int rightstr = leftend;
    int rightend = rightstr + gap;
    if( rightstr >= n )                         //没有右边部分，左边部分已有序，可直接返回
    {
        return;
    }
    int *temp = new int[2*gap];
    for( int i=0; i < 2*gap; i++ )              //临时数组
    {
        temp[i] = INFINITY;
    }
    int i = 0;
    //左右比较，按从小到大存入临时数组，再转入array
    while( leftstr < leftend && rightstr < rightend )
    {
        if( rightstr == n )
        {
            break;
        }
        temp[i++] = array[leftstr] <= array[rightstr] ? 
                    array[leftstr++] : array[rightstr++];
    }

    while( leftstr < leftend )                  //右边有剩余不需要转移，直接将temp中数据复制入array开始处，与rightstr正好重合
        {
            temp[i++] = array[leftstr++];
        }

    for( int j = 0; j < i; j++, start++ )                //将临时数组中数组转入array中
    {
        array[start] = temp[j];
    }
    delete temp;
}


//递归实现归并，当n<1时return
//分为左右两部分进行递归
void Merge_Sort2( int *array, int n )
{
    for( int length = 1; length < n; length *= 2 )
    {
        for( int i = 0; i < n; i += 2*length )
        {
            Merging(array, i, length, n);
        }
    }
}


int main()
{
    int array[MAX] = {100, -99, 20, 2, 0, 100, 100, 5, -66, 3};
    Merge_Sort2(array, SIZE);
    for( int i = 0; i < SIZE; i++ )
    {
        std::cout << array[i] << " ";
    }
    std::cout << "\n\n";
    system("pause");
    return 0;
}