#include <iostream>
#define IMPOSSIBLE  65535
#define KEY    -5

int Binary_Search( int *array, int n, int key );

int main()
{
    int array[10] = {-5, 0, 2, 6, 8, 10, 22, 25, 46, 100};
    int i;
    if( (i = Binary_Search(array, 10, KEY)) == IMPOSSIBLE )
    {
        std::cout << KEY << "������������\n\n";
    }
    else
    {
         std::cout << KEY << "λ�ڵ�" << i+1 << "������\n\n";
    }
    system("pause");
    return 0;
}


int Binary_Search( int *array, int n, int key )
{
    int low = 0, high = n-1;
    while( low <= high )
    {
        int mid = (low + high) / 2;
        if( array[mid] == key )
        {
            return mid;
        }
        if( array[mid] > key )
        {
            high = mid - 1;
        }
        if( array[mid] < key )
        {
            low = mid + 1;
        }
    }
    return IMPOSSIBLE;
}