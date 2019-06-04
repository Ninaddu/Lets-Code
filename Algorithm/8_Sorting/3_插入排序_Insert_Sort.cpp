#include <iostream>
#define MAX     15
#define SIZE    10


void Insert_Sort( int *array, int n )
{
    for( int i=1; i < n; i++ )
    {
        if( array[i] < array[i-1] )
        {
            int temp = array[i];
            int j;
            for( j=i-1; j >= 0 && temp < array[j]; j-- )
            { 
                array[j+1] = array[j];              
            }
            array[j+1] = temp;
        }
    }
}


int main()
{
    int array[MAX] = {0, 5, 3, 9, 0, 81, -3, 100, 42, 30};
    Insert_Sort(array, SIZE);
    for( int i = 0; i < SIZE; i++ )
    {
        std::cout << array[i] << " ";
    }
    std::cout << "\n\n";
    system("pause");
    return 0;
}