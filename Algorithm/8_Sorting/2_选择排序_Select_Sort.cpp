#include <iostream>
#define MAX     15
#define SIZE    10


void Select_Sort( int *array, int n )
{
    for( int i=0; i < n-1; i++ )
    {
        int min = i;
        for( int j=i+1; j < n; j++ )
        {
            if( array[min] > array[j] )
            {
                min = j;
            }
        }
        if( min != i )
        {
            int temp = array[min];
            array[min] = array[i];
            array[i] = temp;
        }
    }
}


int main()
{
    int array[MAX] = {0, 5, 3, 9, 0, 81, -3, 100, 42, 30};
    Select_Sort(array, SIZE);
    for( int i = 0; i < SIZE; i++ )
    {
        std::cout << array[i] << " ";
    }
    std::cout << "\n\n";
    system("pause");
    return 0;
}