#include <iostream>
#include <time.h>

#include "Week5_3_P.h"

using namespace std;

void Homework_Run()
{
	srand((unsigned int)time(nullptr));

	Game BattleShip;
	BattleShip.Run();
}

void Game::PlaceShips()
{
	int Size = 0, X = 0, Y = 0;
	int CheckX = 0, CheckY = 0, PlaceX = 0, PlaceY = 0;
	bool CanPlace = false, Vertical = false;

	for (int ShipIndex = 0; ShipIndex < 4; ShipIndex++)
	{
		Size = Ships[ShipIndex].Size;

		while (1)
		{
			Vertical = rand() % 2;

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

			CanPlace = true;

			for (int i = 0; i < Size; i++)
			{
				if (Vertical)
				{
					CheckX = X;
					CheckY = Y + i;
				}
				else
				{
					CheckX = X + i;
					CheckY = Y;
				}

				if (UseMap[CheckY][CheckX] != 0)
				{
					CanPlace = false;
					break;
				}
			}

			if (!CanPlace)
			{
				continue;
			}

			for (int i = 0; i < Size; i++)
			{
				if (Vertical)
				{
					PlaceX = X;
					PlaceY = Y + i;
				}
				else
				{
					PlaceX = X + i;
					PlaceY = Y;
				}

				if (PlaceX >= 0 && PlaceX < 10 && PlaceY >= 0 && PlaceY < 10)
				{
					UseMap[PlaceY][PlaceX] = ShipIndex + 1;
				}
			}

			break;
		}
	}
}

void Game::PrintMap()
{
	printf("\n남은 공격 횟수 : %d\n", AttackCount);
	printf("남은 함선 수 : %d\n\n", RemainShip);

	printf("   1 2 3 4 5 6 7 8 9 10\n");
	for (int y = 0; y < 10; y++)
	{
		if (y == 9) { printf("%d ", y + 1); }
		else { printf("%d  ", y + 1); }
		
		for (int x = 0; x < 10; x++)
		{
			if (ViewMap[y][x] == 0)
				printf(". ");
			else if (ViewMap[y][x] == -1)
				printf("O ");
			else
				printf("X ");
		}
		printf("\n");
	}
	printf("\n");
}

void Game::Attack()
{
	int X = 0, Y = 0;

	while (1)
	{
		printf("X Y 입력 (ex 0 0): ");
		cin >> X >> Y;
		X--;
		Y--;

		if (X < 0 || X > 9 || Y < 0 || Y > 9)
		{
			printf("범위밖의 위치입니다.\n");
			continue;
		}
		else if (ViewMap[Y][X] != 0)
		{
			printf("이미 공격한 위치입니다.\n");
			continue;
		}
		else
		{
			break;
		}
	}

	AttackCount--;

	if (UseMap[Y][X] == 0)
	{
		printf("실패!\n");
		ViewMap[Y][X] = -1;
	}
	else
	{
		printf("명중!\n");

		ViewMap[Y][X] = 1;

		int ShipIndex = UseMap[Y][X] - 1;

		Ships[ShipIndex].HP--;

		CheckSunk(ShipIndex);
	}
	
}

void Game::CheckSunk(int ShipIndex)
{
	if (Ships[ShipIndex].HP == 0 && Ships[ShipIndex].Sunk == false)
	{
		Ships[ShipIndex].Sunk = true;
		RemainShip--;
		printf("%s 격침!\n", Ships[ShipIndex].Name.c_str());
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
	printf("===== 정답 =====\n");

	printf("   1 2 3 4 5 6 7 8 9 10\n");
	for (int y = 0; y < 10; y++)
	{
		if (y == 9) { printf("%d ", y + 1); }
		else { printf("%d  ", y + 1); }
		for (int x = 0; x < 10; x++)
		{
			if (UseMap[y][x] == 0){ printf(". "); }
			else { printf("%d ", UseMap[y][x]); }
		}
		printf("\n");
	}
}

void Game::Run()
{
	PlaceShips();

	while (AttackCount > 0)
	{
		PrintMap();

		Attack();

		if (IsWin())
		{
			printf("\n승리!\n");
			return;
		}
	}
	printf("\n패배!\n");
	PrintMap();
	RevealMap();
}