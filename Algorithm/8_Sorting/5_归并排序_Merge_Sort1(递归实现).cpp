#include <iostream>
#define INFINITY    65535
#define MAX     15
#define SIZE    10


static void Merging( int *array1, int left, int *array2, int right )
{
    int i, j, k;
    int *temp = new int[left+right];
    for( k = 0; k < left+right; k++ )
    {
        temp[k] = INFINITY;
    }
    i = j = k = 0;
    while( i < left && j < right )
    {
        temp[k++] = array1[i] <= array2[j] ? array1[i++] : array2[j++];
    }
    while( i < left )
    {
        temp[k++] = array1[i++];
    }
    for( i = 0; i < k; i++ )
    {
        array1[i] = temp[i]; 
    }
    delete temp;
} 

//递归实现归并，当n<1时return
//分为左右两部分进行递归
void Merge_Sort1( int *array, int n )
{
    if( n > 1 )
    {
        int *array1 = array;
        int length1 = n / 2;
        int *array2 = array1 + length1;
        int length2 = n - length1;

        Merge_Sort1( array1, length1 );
        Merge_Sort1( array2, length2 );

        Merging(array1, length1, array2, length2);
    }
}


int main()
{
    int array[MAX] = {0, 5, 3, 9, 0, 81, -3, 100, 42, 30};
    Merge_Sort1(array, SIZE);
    for( int i = 0; i < SIZE; i++ )
    {
        std::cout << array[i] << " ";
    }
    std::cout << "\n\n";
    system("pause");
    return 0;
}