// HW 0-2.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int main()
{
	char choice;
	int num, n[100], time = 0, success = 0;
	while (1)
	{
		success = 0;
		printf("Input or Delete?");
		cin >> choice;
		printf("Input an integer?");
		cin >> num;
		if (choice == 'I')
		{
			if (time == 0)
			{
				n[0] = num;
			}

			else
			{
				for (int i = 0;i < time;i++)
				{
					if (n[i] > num)
					{
						success = 1;
						for (int k = time - 1;k >= i;k--)
						{
							n[k + 1] = n[k];
						}
						n[i] = num;
						break;
					}
				}
			}
			if (success == 0)
			{
				n[time] = num;
			}
			time++;
		}
		else if (choice == 'D')
		{
			while (1)
			{
				int q = 1;
				for (int i = 0;i <= time;i++)
				{

					if (n[i] == num)
					{
						for (int k = i;k < time;k++)
						{
							n[k] = n[k + 1];
						}
						q = 0;
						time--;
						break;
					}
				}
				if (q == 1)
				{
					printf("沒這個數字\n");
					break;
				}
				else
				{
					int count = 0;
					for (int i = 0;i <= time;i++)
					{
						if (n[i] == num)
						{
							count++;
						}
					}
					if (count == 0)
					{
						break;
					}
				}
			}
		}
		
		if (time == 0)
		{
			printf("no integer\n");
		}
		else
		{
			for (int i = 0;i < time;i++)
			{
				printf("%d ", n[i]);
			}
			printf("\n");
		}
	}
	system("pause");
	return 0;
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
