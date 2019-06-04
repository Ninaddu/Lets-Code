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
        std::cout << "�����б�\n\n1������\n2������\n3��ɾ��\n4���˳�\n\nѡ���ܣ�";
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
                std::cout << "������Ҫ��������֣�";
                do
                {
                    std::cin >> d;
                    Insert(hashmap, d);
                } while ((c = std::cin.get()) != '\n' );
                std::cout << "\n����ɹ�\n\n"; 
                Prnt(hashmap);
                break;
            }
            case '2':
            {
                Elemtype d;
                char c;
                std::cout << "������Ҫ���ҵ����֣�";
                do
                {
                    std::cin >> d;
                    int pos = Search(hashmap, d);
                    pos == -1 ? std::cout << "\nδ���ҵ�" << d << "\n":
                                std::cout << "\n" << d << "λ��hashmap�е�" 
                                << pos+1 << "λ\n";
                } while ((c = std::cin.get()) != '\n' );
                std::cout << "\n\n"; 
                break;
            }
            case '3':
            {
                Elemtype d;
                char c;
                std::cout << "������Ҫɾ�������֣�";
                do
                {
                    std::cin >> d;
                    Delete(hashmap, d);
                } while ((c = std::cin.get()) != '\n' );
                std::cout << "\nɾ���ɹ�\n\n"; 
                Prnt(hashmap);
                break;
            }
            case '4':
                exit(0);
            default:
                std::cout << "�Ƿ����룡\n\n";
                break;
        }
    }
    return 0;
}


/****************************************************************************
 * ���ܣ���λ
 * ����������������
 * ����ֵ����
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
 * ���ܣ��ҵ�����λ�ò�����hashmap
 * ������hashmap������������
 * ����ֵ����
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
            std::cout << "hashmap�Ѿ��������������ݣ�\n\n";
            return;
        }
    }
    hashmap[pos] = d;
}


/****************************************************************************
 * ���ܣ�hashmap�в�������
 * ������hashmap������������
 * ����ֵ��d��hashmap��λ�ã���δ���ҳɹ��򷵻�-1
*****************************************************************************/
int Search( Elemtype *hashmap, Elemtype d )
{
    int pos = Position(d);
    int flag = pos;
    while( hashmap[pos] != d )
    {
        ++pos;
        pos = Position(pos);
        if( flag == pos || hashmap[pos] == INFINITY )           //1������һȦ�ص�ԭ����Ȼû�ҵ���2������֮��Ϊ��ʼ����
        {
            return -1;
        }
    }
    return pos;
}


/****************************************************************************
 * ���ܣ���hashmap��ɾ������
 * ������hashmap����ɾ������
 * ����ֵ����
*****************************************************************************/
void Delete( Elemtype *hashmap, Elemtype d )
{
    int pos = Search(hashmap, d);
    if( pos == -1 )
    {
        std::cout << d << "��������hashmap�У��޷�ɾ��\n\n";
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
    flag == 0 ? std::cout << "hashmapΪ��\n\n" : std::cout << "\n\n";
}