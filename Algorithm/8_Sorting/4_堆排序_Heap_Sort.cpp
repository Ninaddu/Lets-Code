#include <iostream>
#define MAX     15
#define SIZE    10

//ͨ��������ֵ����
void Exchange( int *x, int *y )
{
    *x = *x ^ *y;
    *y = *y ^ *x;
    *x = *x ^ *y;
}


/*******************************************************************************
 * ���ܣ�����󶥶�
 * ���������飬�����±꣬ĩβ�±�
 * ����ֵ����
 *******************************************************************************/
//����һ��ͨ���ݹ鹹��󶥶�
void Heaping( int *array, int h, int n )
{ 
    int lchild = 2*h+1;
    int rchild = 2*h+2;
    if( lchild <= n )
    {
        if( rchild <= n && array[lchild] < array[rchild] )    //���ϴ����ַ�����ڵ㣻��������Ϊ��������������Ƚ�
        {
            Exchange(&array[lchild], &array[rchild]);
        }
        if( array[h] >= array[lchild] )                 //���������Ҷ�Ӷ��㣬����Ҫ����  
        {
            return;
        }
        else                                    //����ͽϴ�Ҷ�ӽ���������������˳��
        {
            Exchange(&array[h], &array[lchild]);
            Heaping(array, lchild, n);
        }
    }
} 


//����������������󶥶�
void Heaping( int *array, int beg, int end )
{ 
    int parent = beg;
    int child = 2*parent + 1;
    for( ; child <= end; )
    {
        if( (child+1 <= end) && array[child] < array[child+1] ) //ȷ��child�±�����ʾ������end��Χ���ǽϴ���
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
 * ���ܣ�������ȫ���������������������
 * 1���ڵ�h��Ҷ�ӽڵ�ֱ�Ϊ2h+1��2h+2
 * 2���������й���n�����ݣ����һ����Ҷ�ӵ��ӽڵ���n/2-1�������
 * ���������飬�ڵ�����
 * ����ֵ����
 *******************************************************************************/
void Heap_Sort( int *array, int n )
{
    for( int i = n/2-1; i >= 0; i-- )     //�����һ�ִ󶥶�
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