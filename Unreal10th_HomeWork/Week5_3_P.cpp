#include <iostream>

#include "Week5_3_P.h"

using namespace std;

//void Homework_Run()
//{
//	Ship Ship5("항공모함", 5);
//	Ship Ship4("전함", 4);
//	Ship Ship3("순양함", 3);
//	Ship Ship2("구축함", 2);
//	Map Sea_Map(10, 10);
//	
//	while (1)
//	{
//		printf("배틀쉽");
//		
//	}
//}
//
//void Ship_Installation(Map& UseMap)
//{
//	int line = 0, pass = 1;
//	int x = 0, y = 0;
//	// 배를 순서대로
//	for (int i = 5; i > 1;)
//	{// 배크기
//		pass = 1;
//		GetRandomRange(0, 1);
//			if (GetRandomRange(0, 1))
//			{//세로
//				line = 1;
//			}
//			else
//			{//가로
//				line = 0;
//			}
//
//		if (line)
//		{// 세로면
//			x = GetRandomRange(0, 10);
//			y = GetRandomRange(0, 10 - i);
//			for (int j = 0; j < i; j++)
//			{
//				if (UseMap.UseMap[x + ((y + j) * 10)] > 0)
//				{// 뭐 있으면
//					pass = 0;
//					break;
//				}
//			}
//			if (pass == 1)
//			{// 뭐 없으면
//				for (int k = 0; k < i; k++)
//				{// 크기만큼 설치
//					UseMap.UseMap[x + ((y + k) * 10)] = i;
//				}
//				i--;
//			}
//		}
//
//		else
//		{// 가로면
//			x = GetRandomRange(0, 10 - i);
//			y = GetRandomRange(0, 10);
//			for (int j = 0; j < i; j++)
//			{
//				if (UseMap.UseMap[x + j + (y * 10)] > 0)
//				{// 뭐 있으면
//					pass = 0;
//					break;
//				}
//			}
//			if (pass == 1)
//			{// 뭐 없으면
//				for (int k = 0; k < i; k++)
//				{// 크기만큼 설치
//					UseMap.UseMap[x + k + (y * 10)] = i;
//				}
//				i--;
//			}
//		}
//	}
//}
//
//void Map_Print(Map UseMap)
//{
//	for (int i = 0; i < UseMap.Y; i++)
//	{
//		for (int j = 0; j < UseMap.X; j++)
//		{
//			printf("%d ", UseMap.UseMap[i * UseMap.X + j]);
//		}
//		printf("\n");
//	}
//}
//
//void Map::Cleanup()
//{
//	delete[] UseMap;
//	UseMap = nullptr;
//	delete[] ViewMap;
//	ViewMap = nullptr;
//}
//
//int GetRandomRange(int Min, int Max)
//{
//	return Min + rand() % (Max - Min + 1);  // Min ~ Max(양끝 포함)
//}

void Homework_Run()
{
	srand((unsigned int)time(nullptr));

	Game Game;
	Game.Run();
}

void Game::Init()
{
	PlaceShips();
}

void Game::PlaceShips()
{
	for (int ShipIndex = 0; ShipIndex < 4; ShipIndex++)
	{
		int Size = Ships[ShipIndex].Size;

		while (true)
		{
			bool Vertical = rand() % 2;

			int X;
			int Y;

			if (Vertical)
			{
				X = rand() % 10;
				Y = rand() % (11 - Size);
			}
			else
			{
				X = rand() % (11 - Size);
				Y = rand() % 10;
			}

			bool CanPlace = true;

			for (int i = 0; i < Size; i++)
			{
				int CheckX = Vertical ? X : X + i;
				int CheckY = Vertical ? Y + i : Y;

				if (UseMap[CheckY][CheckX] != 0)
				{
					CanPlace = false;
					break;
				}
			}

			if (!CanPlace)
				continue;

			for (int i = 0; i < Size; i++)
			{
				int PlaceX = Vertical ? X : X + i;
				int PlaceY = Vertical ? Y + i : Y;

				UseMap[PlaceY][PlaceX] = ShipIndex + 1;
			}

			break;
		}
	}
}

void Game::PrintMap()
{
	cout << "\n남은 공격 횟수 : " << AttackCount << "\n\n";

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (ViewMap[y][x] == 0)
				cout << ". ";
			else if (ViewMap[y][x] == -1)
				cout << "O ";
			else
				cout << "X ";
		}
		cout << '\n';
	}
}

void Game::Attack()
{
	int X;
	int Y;

	cout << "X 입력 : ";
	cin >> X;

	cout << "Y 입력 : ";
	cin >> Y;

	if (X < 0 || X > 9 || Y < 0 || Y > 9)
		return;

	if (ViewMap[Y][X] != 0)
	{
		cout << "이미 공격한 위치입니다.\n";
		return;
	}

	AttackCount--;

	if (UseMap[Y][X] == 0)
	{
		cout << "실패!\n";
		ViewMap[Y][X] = -1;
	}
	else
	{
		cout << "명중!\n";

		ViewMap[Y][X] = 1;

		int ShipIndex = UseMap[Y][X] - 1;

		Ships[ShipIndex].HP--;

		CheckSunk(ShipIndex);
	}
}

void Game::CheckSunk(int ShipIndex)
{
	if (Ships[ShipIndex].HP == 0 &&
		Ships[ShipIndex].Sunk == false)
	{
		Ships[ShipIndex].Sunk = true;

		cout << Ships[ShipIndex].Name
			<< " 격침!\n";
	}
}

bool Game::IsWin()
{
	for (int i = 0; i < 4; i++)
	{
		if (!Ships[i].Sunk)
			return false;
	}

	return true;
}

void Game::RevealMap()
{
	cout << "\n===== 정답 =====\n";

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			cout << UseMap[y][x] << ' ';
		}
		cout << '\n';
	}
}

void Game::Run()
{
	Init();

	while (AttackCount > 0)
	{
		PrintMap();

		Attack();

		if (IsWin())
		{
			cout << "\n승리!\n";
			return;
		}
	}

	cout << "\n패배!\n";

	RevealMap();
}