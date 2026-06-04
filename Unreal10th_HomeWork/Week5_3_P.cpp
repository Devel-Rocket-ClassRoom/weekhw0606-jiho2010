#include <iostream>

#include "Week5_3_P.h"

using namespace std;

void Homework_Run()
{
	Ship Ship5("항공모함", 5);
	Ship Ship4("전함", 4);
	Ship Ship3("순양함", 3);
	Ship Ship2("구축함", 2);
	Map Sea_Map(10, 10);
	
	while (1)
	{
		printf("배틀쉽");
		
	}
}

void Ship_Installation(Map& UseMap)
{
	int line = 0, pass = 1;
	int x = 0, y = 0;
	// 배를 순서대로
	for (int j = 5; j > 1;)
	{// 배크기
		GetRandomRange(0, 1);
			if (GetRandomRange(0, 1))
			{//세로
				line = 1;
			}
			else
			{//가로
				line = 0;
			}

		if (line)
		{// 세로면
			x = GetRandomRange(0, 10);
			y = GetRandomRange(0, j - 10);
			for (int k = 0; k < j; k++)
			{
				if (UseMap + (x+ ((y + k)*10)) > 0)
				{// 뭐 있으면
					pass = 0;
					break;
				}
			}
			if (pass == 1)
			{// 뭐 없으면
				for (int k = 0; k < j; j++)
				{// 크기만큼 설치
					map[x][y + k] = j
				}
				j--;
			}
		}

		else
		{// 가로면
			x = GetRandomRange(0, j - 10);
			y = GetRandomRange(0, 10);
			for (int k = 0; k < j; j++)
			{
				if (map[x + k][y] > 0)
				{// 뭐 있으면
					pass = 0;
					break;
				}
			}
			if (pass == 1)
			{// 뭐 없으면
				for (int k = 0; k < j; j++)
				{// 크기만큼 설치
					map[x + k][y] = j
				}
				j--;
			}
		}
	}
}

void Map_Print(Map UseMap)
{
	for (int i = 0; i < y크기; i++)
	{
		for (int j = 0; j < x크기; j++)
		{
			printf("%d", UseMap[(i * 10) + j]);
		}
	}
}

void Map::Cleanup()
{
	delete[] UseMap;
	UseMap = nullptr;
	delete[] ViewMap;
	ViewMap = nullptr;
}

int GetRandomRange(int Min, int Max)
{
	return Min + rand() % (Max - Min + 1);  // Min ~ Max(양끝 포함)
}

