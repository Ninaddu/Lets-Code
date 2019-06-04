#include <iostream>
#define IMPOSSIBLE  65535
#define KEY    -5

int Sq_Search1( int *array, int n, int key );
int Sq_Search2( int *array, int n, int key );

int main()
{
    int array[10] = {-5, 0, 2, 6, 8, 10, 22, 25, 46, 100};
    int i;
    if( (i = Sq_Search1(array, 10, KEY)) == IMPOSSIBLE )
    {
        std::cout << KEY << "不存在数组中\n\n";
    }
    else
    {
         std::cout << KEY << "位于第" << i+1 << "个数字\n\n";
    }

    if( (i = Sq_Search2(array, 10, KEY)) == IMPOSSIBLE )
    {
        std::cout << KEY << "不存在数组中\n\n";
    }
    else
    {
         std::cout << KEY << "位于第" << i+1 << "个数字\n\n";
    }
    system("pause");
    return 0;
}

//不借助其他变量，空间复杂度0
int Sq_Search1( int *array, int n, int key )
{
    if( array[0] == key ) 
    {
        return 0;
    }
    array[0] = key;

    do
    {
        --n;
    }while( array[n] != key );

    if( 0 == n )
    {
        return IMPOSSIBLE;
    }
    return n;
}

int Sq_Search2( int *array, int n, int key )
{
    for( int i = 0; i < n; i++ )
    {
        if( array[i] == key )
        {
            return i;
        }
    }
    return IMPOSSIBLE;
}