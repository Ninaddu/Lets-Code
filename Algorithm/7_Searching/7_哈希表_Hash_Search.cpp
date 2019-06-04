#include <iostream>
#include <cstring>
#define MAXSIZE 20
#define INFINITY    65535

typedef int Elemtype;
typedef int Address[MAXSIZE];


int Position( Elemtype d );
void Insert( Elemtype *hashmap, Elemtype d );
int Search( Elemtype *hashmap, Elemtype d );
void Delete( Elemtype *hashmap, Elemtype d );
void Prnt( Elemtype *hashmap );


int main()
{
    Address hashmap;
    for( int i = 0; i < MAXSIZE; i++ )
    {
        hashmap[i] = INFINITY;
    }
    while( 1 )
    {
        std::cout << "功能列表：\n\n1、插入\n2、查找\n3、删除\n4、退出\n\n选择功能：";
        char option;
        std::cin >> option;
        std::cin.ignore(1000, '\n');
        std::cout << "\n";
        switch( option )
        {
            case '1':
            {
                Elemtype d;
                char c;
                std::cout << "输入需要插入的数字：";
                do
                {
                    std::cin >> d;
                    Insert(hashmap, d);
                } while ((c = std::cin.get()) != '\n' );
                std::cout << "\n插入成功\n\n"; 
                Prnt(hashmap);
                break;
            }
            case '2':
            {
                Elemtype d;
                char c;
                std::cout << "输入需要查找的数字：";
                do
                {
                    std::cin >> d;
                    int pos = Search(hashmap, d);
                    pos == -1 ? std::cout << "\n未查找到" << d << "\n":
                                std::cout << "\n" << d << "位于hashmap中第" 
                                << pos+1 << "位\n";
                } while ((c = std::cin.get()) != '\n' );
                std::cout << "\n\n"; 
                break;
            }
            case '3':
            {
                Elemtype d;
                char c;
                std::cout << "输入需要删除的数字：";
                do
                {
                    std::cin >> d;
                    Delete(hashmap, d);
                } while ((c = std::cin.get()) != '\n' );
                std::cout << "\n删除成功\n\n"; 
                Prnt(hashmap);
                break;
            }
            case '4':
                exit(0);
            default:
                std::cout << "非法输入！\n\n";
                break;
        }
    }
    return 0;
}


/****************************************************************************
 * 功能：定位
 * 参数：待插入数据
 * 返回值：无
*****************************************************************************/
int Position( Elemtype d )
{
    int pos = d % (MAXSIZE-1);
    if( pos >= 0 )
        return pos;
    else
        return 0;
}


/****************************************************************************
 * 功能：找到合适位置并插入hashmap
 * 参数：hashmap；待插入数据
 * 返回值：无
*****************************************************************************/
void Insert( Elemtype *hashmap, Elemtype d )
{
    int pos = Position(d);
    int flag = pos;
    while( hashmap[pos] != INFINITY )
    {
        ++pos;
        pos = Position(pos);
        if( pos == flag )
        {
            std::cout << "hashmap已经储存满，请扩容！\n\n";
            return;
        }
    }
    hashmap[pos] = d;
}


/****************************************************************************
 * 功能：hashmap中查找数据
 * 参数：hashmap；待查找数据
 * 返回值：d在hashmap中位置，若未查找成功则返回-1
*****************************************************************************/
int Search( Elemtype *hashmap, Elemtype d )
{
    int pos = Position(d);
    int flag = pos;
    while( hashmap[pos] != d )
    {
        ++pos;
        pos = Position(pos);
        if( flag == pos || hashmap[pos] == INFINITY )           //1、找了一圈回到原点依然没找到；2、所在之处为初始化数
        {
            return -1;
        }
    }
    return pos;
}


/****************************************************************************
 * 功能：从hashmap中删除数据
 * 参数：hashmap；待删除数据
 * 返回值：无
*****************************************************************************/
void Delete( Elemtype *hashmap, Elemtype d )
{
    int pos = Search(hashmap, d);
    if( pos == -1 )
    {
        std::cout << d << "不存在于hashmap中，无法删除\n\n";
        return;
    }
    hashmap[pos] = INFINITY;
}


void Prnt( Elemtype *hashmap )
{
    int flag = 0;
    for( int i=0; i<MAXSIZE; i++ )
    {
        if( hashmap[i] != INFINITY )
        {
            std::cout << hashmap[i] << " ";
            flag = 1;
        }
    }
    flag == 0 ? std::cout << "hashmap为空\n\n" : std::cout << "\n\n";
}