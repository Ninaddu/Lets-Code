#include <iostream>
#include <windows.h>
#include "HfmTable.h"
#include "HfmTree.h"

int main()
{
	std::cout << "已进入Huffman加密程序，请在三秒后悄咪咪输入加密电报\n\n注意左顾右盼，确保周围环境的安全！";
	Sleep(3000);
	system("cls");
	int i = 0;
	for (i = 3; i > 0; i--)
	{
		std::cout << "\n\n——————————————————— " << i << " ———————————————————";
		Sleep(1000);
		system("cls");
	}
	system("cls");

	Elemtype str[MAXCODE];
	memset(str, NULL, sizeof(str));
	while (1)
	{
		std::cout << "输入加密电报：";
		for (i = 0; (str[i] = std::cin.get()) != '\n'; i++)
			;

		if (i < 3)
		{
			std::cout << "长度未通过检测，请重新确认加密电报！" << "\n\n";
		}
		else
		{
			break;
		}
	}

	std::cout << "\n\n已成功保存，开始启动加密程序，请稍作等待...";
	Sleep(3000);
	system("cls");

	hTree *t;
	t = HuffmanTree(str);

	HfmCode *c;
	c = Coding(t);

	Sleep(3000);

	//这里可以switch不同功能，输入1，查看某个字符密码，2、输入密码后解码，3、敌军攻入大营，销毁加密表
	char contn;
	while (1)
	{
		system("cls");
		std::cout << "功能列表：\n\n1-查看所有明文和对应密码\n\n2-查寻指定字符的编译密码\n\n3-输入需要解码的字符\n\n4-敌军攻入大本营，迅速销毁密码表！！！\n\n\n";
		char fun;
		std::cout << "选择功能：";
		std::cin >> fun;
		std::cin.ignore();										//清除缓冲区中的回车字符
		std::cout << "\n\n";
		switch (fun)
		{
		case '1':
			Prnt(c);
			break;
		case '2':
			Elemtype ch1[MAXCODE];
			memset(ch1, NULL, sizeof(ch1));
			std::cout << "输入需要查询的明文（请勿不出现重复字符）：";
			for (i = 0; (ch1[i] = std::cin.get()) != '\n'; i++)
				;
			std::cout << "\n\n";
			Search(c, ch1);
			break;
		case '3':
			Elemtype ch2[MAXCODE];
			memset(ch2, NULL, sizeof(ch2));
			std::cout << "输入需要编译的密码（0或1）：";
			for (i = 0; (ch2[i] = std::cin.get()) != '\n'; i++)
			{
				if (ch2[i] != '0' && ch2[i] != '1')
				{
					std::cout << "\n\n检测到非法字符！根据提示进行操作,可进入此功能" << "\n\n";
					i = 0;
					break;
				}
			}
			if (i)													//如果输入非法密码字符，则i=0，不进入解码
			{
				DeCoding(t, ch2);
			}
			break;
		case '4':
			if (Destroy(&t, &c))
			{
				std::cout << "密码表成功销毁，快逃命吧！！！！！！！！！！！" << "\n\n";
			}
			else
			{
				std::cout << "销毁失败" << "\n\n";
			}
			exit(0);
			break;
		default:
			std::cout << "\n\n非法字符！根据提示进行操作可重新选择功能" << "\n\n";
			break;
		}

		while (1)
		{
			std::cout << "是否需要重新查看密码，输入Y/N：";
			std::cin >> contn;
			std::cin.ignore();
			
			if( contn == 'Y' || contn == 'y' || contn == 'N' || contn == 'n' )
			{
				break;
			}
			else
			{
				std::cout << "\n\n非法输入！请重新选择";
			}
		}
		if (contn == 'N' || contn == 'n')
		{
			break;
		}
	}
	return 0;
}