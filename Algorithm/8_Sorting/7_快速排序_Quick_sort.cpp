/**********************************************************************************************
 * �Ĳ��Ż���
 * 1������ȡһ����׼
 * 2���������
 * 3�����׼���Ԫ�ؾ�£
 * 4��β�ݹ�
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
 * ���ܣ�����ȡһѡȡ��׼��Ƚϣ��ȽϹ��������Ԫ�ط����ߣ����Ż�׼������
 * ���������������飻��Ԫ���±ꣻβԪ���±ꣻ��������׼����ͬ��Ԫ��ǰһ��Ԫ���±� ������ַ��
 *       ��������׼����ͬβԪ�غ�һ��Ԫ���±� ������ַ
 * ����ֵ����
 **********************************************************************************************/

void Patition( int *array, int start, int finish, int *pos1, int *pos2 )
{
    //���ס��С�βԪ���д�СΪ��Ԫ����Ϊ��׼��ת����Ԫ��
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

    //��posС���������󣬴����ң����������
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
            array[start++] = array[finish];               //start��ʱ����׼�������±꣬�������׼�㵽finish��
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

    //���½��������Ԫ�����׼���£
    *pos1 = start - 1;                             //��ʹ������pos���ڻ�׼�����ҵ㣬���Ԫ�ؾ�£���ٵ���
    *pos2 = start + 1;  
    for( int i=0; i < min_cnt; ++i )                //��������׼���������������
    {
        Exchange(&array[min+i], &array[*pos1]);
        --(*pos1);
    }
    for( int i=0; i < max_cnt; ++i )                //�ұߣ�ͬ��
    {
        Exchange(&array[max-i], &array[*pos2]);
        ++(*pos2);
    }
}


/**********************************************************************************************
 * ���ܣ���������
 * ���������������飻����Ԫ�ظ���
 * ����ֵ����
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
 * ���ܣ�β�ݹ�ʵ�ֿ���
 * ���������������飻��Ԫ���±ꣻβԪ���±�
 * ����ֵ����
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
            Patition(array, start, finish, &pos1, &pos2);  //pos1��pos2��Ϊһ�ֽ�����ǰ���׼�㣨�ظ����»�׼��ͬ��
                                                           //����Patition������

            int start_next = start;                        //�Ի�׼���Ϊ�����ֵݹ�
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
    for( int i = 0; i < SIZE; i++ )             //�������25������
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