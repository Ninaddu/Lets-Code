/***************************************************************************************
 * 1、chess[8][8]，1-64填充完成后Prnt输出
 * 2、Next_Postion()函数8个方位分别寻找
 * 3、DFS()传入棋盘&行&列&第几步，调用Next_Postion找到下一个则return OK，否则return ERROR
 **************************************************************************************/
#include <iostream>
#include <fstream>
#include <time.h>
#include <string.h>
#define SIZE    5
#define OK      1
#define END     0
#define ERROR   0

typedef int Status;

Status DFS( int chess[][SIZE], int row, int col, int n );           
Status Next_Postion( int chess[][SIZE], int *row, int *col, int *cnt );
void Prnt( int chess[][SIZE], int cnt );

int cnt = 0;

int main()
{
    int chess[SIZE][SIZE];
    memset(chess, 0, sizeof(chess));
    clock_t start, finish;
    start = clock();
    DFS(chess, 0, 0, 1);
    finish = clock();
    double time = (double)((finish-start)/CLOCKS_PER_SEC);
    if( cnt == 0 )
    {
        std::cout << "Sorry, fail to find way to cover the whole chess." << "\n\n"; 
    }
    else
    {
        std::cout << "Successfully find " << cnt << " ways in " << time << " seconds!!(#^.^#)" << "\n\n";
    }
    system("pause");
    return 0;
}

Status DFS( int chess[][SIZE], int row, int col, int n )
{
    chess[row][col] = n;
    if( SIZE*SIZE == n )
    {
        cnt++;
        Prnt(chess, cnt);
        chess[row][col] = 0;
        return END;
    }

    int cnt_pos = 0;
    int row0 = row, col0 = col;
    for( cnt_pos = 1; cnt_pos <= SIZE; )
    {
        //能否寻找到下一个pos，则将row、col传入DFS搜索下一个pos
        if( Next_Postion(chess, &row0, &col0, &cnt_pos) )   
        {
            //下一个位置寻找失败，需要退回并寻找这一步的NEXTPOS
            while( 0 == DFS( chess, row0, col0, n+1 ) )     
            {
                row0 = row;
                col0 = col;
                /*Next_Pos返回0表示8个位置均寻找完毕，需跳出循环，跳出循环后若cnt还未到8，
                则继续查找下面的位置是否可能有其他路径*/
                if( 0 == Next_Postion(chess, &row0, &col0, &cnt_pos) )      
                {                                                           
                    break;
                }
            }
        }
    }

    //循环结束表示找不到下一个路径，则撤回传入位置的赋值，向上返回ERROE
    chess[row][col] = 0;
    return ERROR;
}

Status Next_Postion( int chess[][SIZE], int *row, int *col, int *cnt )
{
    switch(*cnt)
    {
    case 1:
        (*cnt)++;
        if( (*row)-1 >= 0 && (*col)+2 < SIZE && chess[(*row)-1][(*col)+2] == 0 )
        {
            (*row) -= 1;
            *col += 2;
            return OK;
        }
    case 2:
        (*cnt)++;
        if( (*row)-2 >= 0 && (*col)+1 < SIZE && chess[(*row)-2][(*col)+1] == 0 )
        {
            (*row) -= 2;
            (*col) += 1;
            return OK;
        }
    case 3:
        (*cnt)++;
        if( (*row)-2 >= 0 && (*col)-1 >= 0 && chess[(*row)-2][(*col)-1] == 0 )
        {
            (*row) -= 2;
            (*col) -= 1;
            return OK;
        }
    case 4:
        (*cnt) ++;
        if( (*row)-1 >= 0 && (*col)-2 >= 0 && chess[(*row)-1][(*col)-2] == 0 )
        {
            (*row) -= 1;
            (*col) -= 2;
            return OK;
        }
    case 5:
        (*cnt) ++;
        if( (*row)+1 < SIZE && (*col)-2 >= 0 && chess[(*row)+1][(*col)-2] == 0 )
        {
            (*row) += 1;
            (*col) -= 2;
            return OK;
        }
    case 6:
        (*cnt)++;
        if( (*row)+2 < SIZE && (*col)-1 >= 0 && chess[(*row)+2][(*col)-1] == 0 )
        {
            (*row) += 2;
            (*col) -= 1;
            return OK;
        }
    case 7:
        (*cnt)++;
        if( (*row)+2 < SIZE && (*col)+1 < SIZE && chess[(*row)+2][(*col)+1] == 0 )
        {
            (*row) += 2;
            (*col) += 1;
            return OK;
        }
     case 8:
        (*cnt) ++;
        if( (*row)+1 < SIZE && (*col)+2 < SIZE && chess[(*row)+1][(*col)+2] == 0 )
        {
            (*row) += 1;
            (*col) += 2;
            return OK;
        }
    default:
        return ERROR;
    }
}

void Prnt( int chess[][SIZE], int cnt )
{
    std::ofstream out("Eight chess.txt", std::ios::app | std::ios::out);        //末尾追加 + 写入
    if( ! out.is_open() )
    {
        std::cout << "Fail to open Eight chess.txt" << "\n\n";
        exit(-1);
    }
    out << "第" << cnt << "种走法：" << "\n\n";
    int i, j;
    for( i = 0; i < SIZE; i++ )
    {
        for( j = 0; j < SIZE; j++ ) 
        {
            out << chess[i][j] << " ";
        }
        out << "\n";
    }
    out << "\n\n";
    out.close();
}