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
    if( rightstr >= n )                         //û���ұ߲��֣���߲��������򣬿�ֱ�ӷ���
    {
        return;
    }
    int *temp = new int[2*gap];
    for( int i=0; i < 2*gap; i++ )              //��ʱ����
    {
        temp[i] = INFINITY;
    }
    int i = 0;
    //���ұȽϣ�����С���������ʱ���飬��ת��array
    while( leftstr < leftend && rightstr < rightend )
    {
        if( rightstr == n )
        {
            break;
        }
        temp[i++] = array[leftstr] <= array[rightstr] ? 
                    array[leftstr++] : array[rightstr++];
    }

    while( leftstr < leftend )                  //�ұ���ʣ�಻��Ҫת�ƣ�ֱ�ӽ�temp�����ݸ�����array��ʼ������rightstr�����غ�
        {
            temp[i++] = array[leftstr++];
        }

    for( int j = 0; j < i; j++, start++ )                //����ʱ����������ת��array��
    {
        array[start] = temp[j];
    }
    delete temp;
}


//�ݹ�ʵ�ֹ鲢����n<1ʱreturn
//��Ϊ���������ֽ��еݹ�
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