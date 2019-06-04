#include <iostream>
#include <windows.h>
#include "HfmTable.h"
#include "HfmTree.h"

int main()
{
	std::cout << "�ѽ���Huffman���ܳ������������������������ܵ籨\n\nע��������Σ�ȷ����Χ�����İ�ȫ��";
	Sleep(3000);
	system("cls");
	int i = 0;
	for (i = 3; i > 0; i--)
	{
		std::cout << "\n\n�������������������������������������� " << i << " ��������������������������������������";
		Sleep(1000);
		system("cls");
	}
	system("cls");

	Elemtype str[MAXCODE];
	memset(str, NULL, sizeof(str));
	while (1)
	{
		std::cout << "������ܵ籨��";
		for (i = 0; (str[i] = std::cin.get()) != '\n'; i++)
			;

		if (i < 3)
		{
			std::cout << "����δͨ����⣬������ȷ�ϼ��ܵ籨��" << "\n\n";
		}
		else
		{
			break;
		}
	}

	std::cout << "\n\n�ѳɹ����棬��ʼ�������ܳ����������ȴ�...";
	Sleep(3000);
	system("cls");

	hTree *t;
	t = HuffmanTree(str);

	HfmCode *c;
	c = Coding(t);

	Sleep(3000);

	//�������switch��ͬ���ܣ�����1���鿴ĳ���ַ����룬2�������������룬3���о������Ӫ�����ټ��ܱ�
	char contn;
	while (1)
	{
		system("cls");
		std::cout << "�����б�\n\n1-�鿴�������ĺͶ�Ӧ����\n\n2-��Ѱָ���ַ��ı�������\n\n3-������Ҫ������ַ�\n\n4-�о������Ӫ��Ѹ���������������\n\n\n";
		char fun;
		std::cout << "ѡ���ܣ�";
		std::cin >> fun;
		std::cin.ignore();										//����������еĻس��ַ�
		std::cout << "\n\n";
		switch (fun)
		{
		case '1':
			Prnt(c);
			break;
		case '2':
			Elemtype ch1[MAXCODE];
			memset(ch1, NULL, sizeof(ch1));
			std::cout << "������Ҫ��ѯ�����ģ����𲻳����ظ��ַ�����";
			for (i = 0; (ch1[i] = std::cin.get()) != '\n'; i++)
				;
			std::cout << "\n\n";
			Search(c, ch1);
			break;
		case '3':
			Elemtype ch2[MAXCODE];
			memset(ch2, NULL, sizeof(ch2));
			std::cout << "������Ҫ��������루0��1����";
			for (i = 0; (ch2[i] = std::cin.get()) != '\n'; i++)
			{
				if (ch2[i] != '0' && ch2[i] != '1')
				{
					std::cout << "\n\n��⵽�Ƿ��ַ���������ʾ���в���,�ɽ���˹���" << "\n\n";
					i = 0;
					break;
				}
			}
			if (i)													//�������Ƿ������ַ�����i=0�����������
			{
				DeCoding(t, ch2);
			}
			break;
		case '4':
			if (Destroy(&t, &c))
			{
				std::cout << "�����ɹ����٣��������ɣ���������������������" << "\n\n";
			}
			else
			{
				std::cout << "����ʧ��" << "\n\n";
			}
			exit(0);
			break;
		default:
			std::cout << "\n\n�Ƿ��ַ���������ʾ���в���������ѡ����" << "\n\n";
			break;
		}

		while (1)
		{
			std::cout << "�Ƿ���Ҫ���²鿴���룬����Y/N��";
			std::cin >> contn;
			std::cin.ignore();
			
			if( contn == 'Y' || contn == 'y' || contn == 'N' || contn == 'n' )
			{
				break;
			}
			else
			{
				std::cout << "\n\n�Ƿ����룡������ѡ��";
			}
		}
		if (contn == 'N' || contn == 'n')
		{
			break;
		}
	}
	return 0;
}