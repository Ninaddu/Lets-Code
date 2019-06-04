#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#define MAX	10
using namespace std;

static void EightQueen( int chess[][MAX], int n );
static int NotDanger( int chess[][MAX], int row, int col );
static void Prnt( int chess[][MAX], int cnt );

int cnt = 0;

int main()
{
	int chess1[MAX][MAX];
	memset(chess1, 0, sizeof(chess1));
	EightQueen(chess1, 0);
	return 0;
}

static void EightQueen( int chess[][MAX], int n )
{	
	if( MAX == n )
	{
		cnt++;
		Prnt(chess, cnt);
		return;
	}
	else
	{
		int chess0[MAX][MAX];
		memset(chess0, 0, sizeof(chess0));
		
		int i, j;
		for( i=0; i < MAX; i++)
		{
			for( j=0; j < MAX; j++ )	
			{
				chess0[i][j] = chess[i][j];
			}
		}
		
		for( i=0; i < MAX; i++ )
		{
			if( NotDanger(chess, n, i) )
			{
				for( j=0; j < MAX; j++ )
				{
					chess0[n][j] = 0;
				}
				chess0[n][i] = 1;
				EightQueen(chess0, n+1);
			}
		}
	}
}

static int NotDanger( int chess[][MAX], int row, int col )
{
	int i;
	for( i=row-1; i >= 0; i-- )
	{
		if( 1 == chess[i][col] )
		{
			return 0;
		}
	}
	int j;
	for( i=row-1, j=col-1; i >= 0 && j >= 0; i--, j--  )
	{
		if( 1 == chess[i][j] )
		{
			return 0;
		}
	}
	for( i=row-1, j=col+1; i >= 0 && j < MAX; i--, j++ )
	{
		if( 1 == chess[i][j] )
		{
			return 0;
		}
	}
	return 1;
}

static void Prnt( int chess[][MAX], int cnt )
{
	ofstream fp("EightQueen.txt", ios::out | ios::app);
	if( !fp.is_open() )
	{
		cout <<"Fail to open file!" << "\n\n";
		exit(0);
	}
	fp << cnt << ":\n\n";
	for( int i=0; i < MAX; i++ )
	{
		for( int j=0; j < MAX; j++ )
		{
			fp << chess[i][j] << " ";
		}
		fp << "\n"; 
	}
	fp << "\n\n";
	fp.close();
}
