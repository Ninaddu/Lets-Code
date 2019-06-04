#include <iostream>
#define MAX     15
#define SIZE    10


//increment = increment/3 + 1
void Shell_Sort( int *array, int n )
{
    for( int ht=n; ht > 1; )
    {
        ht = ht/3 + 1;                      //??
        for( int i=ht; i < n; i++ )
        {
            if( array[i] < array[i-ht] )
            {
                int temp = array[i];
                int j;
                for( j = i-ht; j >= 0 && array[j] > temp; j -= ht )
                {
                    array[j+ht] = array[j];
                }
                array[j+ht] = temp;
            }
        }
    }
}


int main()
{
    int array[MAX] = {0, 5, 3, 9, 0, 81, -3, 100, 42, 30};
    Shell_Sort(array, SIZE);
    for( int i = 0; i < SIZE; i++ )
    {
        std::cout << array[i] << " ";
    }
    std::cout << "\n\n";
    system("pause");
    return 0;
}