#include <iostream>
#define MAX     15
#define SIZE    10


void Bubble_Sort( int *array, int n )
{
    int i, j;
    for( int i = 0; i < n-1; i++ )
    {
        int flag = 0;
        for( int j = 1; j < n-i; j++ )
        {
            if( array[j-1] > array[j] )
            {
                int temp = array[j-1];
                array[j-1] = array[j];
                array[j] = temp;
                flag = 1;
            }
        }
        if( flag == 0 )
        {
            break;
        }
    }
}


int main()
{
    int array[MAX] = {0, 5, 3, 9, 0, 81, -3, 100, 42, 30};
    Bubble_Sort(array, SIZE);
    for( int i = 0; i < SIZE; i++ )
    {
        std::cout << array[i] << " ";
    }
    std::cout << "\n\n";
    system("pause");
    return 0;
}