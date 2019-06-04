#include<stdio.h>
#define MAX	50

typedef char Elemtype;
int next[MAX] = { 0 };

static void KMP(Elemtype strl[], Elemtype strs[]);

static void Next(Elemtype strs[]);

int main()
{
	Elemtype long_str[MAX];
	Elemtype short_str[MAX];
	int i;
	printf("Input the long array:");
	i = 0;
	while ((long_str[i++] = getchar()) != '\n')
		;
	printf("Input the short array:");
	i = 0;
	while ((short_str[i++] = getchar()) != '\n')
		;
	KMP(short_str, long_str);
	return 0;
}


static void KMP(Elemtype strs[], Elemtype strl[])
{
	int i = 0, j = 0;
	int cnt = 0;
	if (strl[0] == '\n' || strs[0] == '\n')
	{
		printf("Input Error!\n\n");
		return;
	}

	Next(strs);
	while (strs[i] != '\n' && strl[j] != '\n')
	{
		if (strs[i] == strl[j] && strs[i + 1] == '\n')
		{
			cnt++;
			printf("Find %d short array in long array: from %d to %d\n\n", cnt, j - i + 1, j + 1);
			j = j - i + 1 ;			//从long_str和short_str比较完全匹配后，long_str从匹配首字符的后一个字符开始重新和short_str[0]比较
			i = 0;
		}
		else if (strs[i] == strl[j])
		{
			i++;
			j++;
		}
		else
		{
			if (-1 == (i = next[i]))
			{
				i = 0;
				j++;
			}
		}
	}
	if (cnt)
	{
		printf("Find %d short array int long array\n\n", cnt);
	}
	else
	{
		printf("Fail to find short array int long array\n\n");
	}
}

static void Next(Elemtype strs[])
{
	int i, j;
	next[0] = -1;
	i = 0;
	j = -1;
	while (strs[i] != '\n')
	{
		if (-1 == j || strs[i] == strs[j])
		{
			if (j > 0 && strs[j] == strs[next[j]])
			{
				j = next[j];
			}
			else
			{
				next[++i] = ++j;
			}
		}
		else
		{
			j = next[j];
		}
	}
}