#include <iostream>
#include <time.h>

#include "Week5_2_P2.h"

using namespace std;

void Homework02_Run()
{
	srand(time(0));
	printf("2. 블랙잭 만들기\n\n");
	int Ch_num = 0;
	while (1)
	{
		TrumpCard Card;
		Table Player;
		Table Dealer;
		Dealer.Dealer = true;
		GetCard(Card, Dealer);
		GetCard(Card, Player);
		GetCard(Card, Dealer);
		GetCard(Card, Player);
		PrintTable(Player, Dealer);
		if (Player.BlackJack || Dealer.BlackJack)
		{
			BlackJack(Player, Dealer);
			printf("게임을 다시 하시겠습니까?\n1. 다시한다. 2. 종료한다.\n");
			cin >> Ch_num;
			if (Ch_num == 1) { continue; }
			else { break; }
		}
		SumScore(Player);
		SumScore(Dealer);
		PlayerTurn(Card, Player, Dealer);
		if (Player.Bust)
		{
			printf("버스트 되어 패배 하였습니다.\n\n");
			printf("게임을 다시 하시겠습니까?\n1. 다시한다. 2. 종료한다.\n");
			cin >> Ch_num;
			if (Ch_num == 1) { continue; }
			else { break; }
		}
		DealerTurn(Card, Player, Dealer);
		if (Dealer.Bust)
		{
			printf("딜러가 버스트 되어 승리 하였습니다.\n\n");
			printf("게임을 다시 하시겠습니까?\n1. 다시한다. 2. 종료한다.\n");
			cin >> Ch_num;
			if (Ch_num == 1) { continue; }
			else { break; }
		}
		Result(Player, Dealer);
		printf("게임을 다시 하시겠습니까?\n1. 다시한다. 2. 종료한다.\n");
		cin >> Ch_num;
		if (Ch_num == 1) { continue; }
		else { break; }
	}
}

void GetCard(TrumpCard& card, Table& ind)
{
	int Shape = 0;
	int Number = 0;
	int i = 0;
	while (1)
	{
		if (ind.Card_Number[i] != 0)
		{
			i++;
			continue;
		}
		Shape = rand() % 4;
		Number = rand() % 13;
		switch(Shape)
		{
		case Spade:
			if (card.Spade[Number] == 0) { continue; }
			ind.Card_Shape[i] = Shape;
			ind.Card_Number[i] = card.Spade[Number];
			card.Spade[Number] = 0;
			break;
		case Diamond:
			if (card.Diamond[Number] == 0) { continue; }
			ind.Card_Shape[i] = Shape;
			ind.Card_Number[i] = card.Diamond[Number];
			card.Diamond[Number] = 0;
			break;
		case Heart:
			if (card.Heart[Number] == 0) { continue; }
			ind.Card_Shape[i] = Shape;
			ind.Card_Number[i] = card.Heart[Number];
			card.Heart[Number] = 0;
			break;
		case Club:
			if (card.Club[Number] == 0) { continue; }
			ind.Card_Shape[i] = Shape;
			ind.Card_Number[i] = card.Club[Number];
			card.Club[Number] = 0;
			break;
		}
		break;
	}
	if ((ind.Card_Number[0] == 1 && ind.Card_Number[1] > 9) || (ind.Card_Number[1] == 1 && ind.Card_Number[0] > 9))
	{
		ind.BlackJack = true;
	}
}

void PrintTable(Table player, Table dealer)
{
	printf("----------------------------------------\n");
	printf("    딜러 카드	:	");
	PrintCard(dealer);
	printf("플레이어 카드	:	");
	PrintCard(player);
	printf("----------------------------------------\n\n");
}

void PrintCard(Table ind)
{
	int i = 0;
	while (i < 11 && ind.Card_Number[i] != 0)
	{
		if (ind.Dealer == 1 && i > 0) 
		{
			printf("??");
			i++;
			continue;
		}
		switch (ind.Card_Shape[i])
		{
		case Spade:
			printf("♠");
			break;
		case Diamond:
			printf("◆");
			break;
		case Heart:
			printf("♥");
			break;
		case Club:
			printf("♣");
			break;
		}
		switch (ind.Card_Number[i]) 
		{
		case 1:
			printf("A");
			break;
		case 11:
			printf("J");
			break;
		case 12:
			printf("Q");
			break;
		case 13:
			printf("K");
			break;
		default:
			printf("%d", ind.Card_Number[i]);
			break;
		}
		printf("  ");
		i++;
	}
	printf("\n");
}

void BlackJack(Table& player, Table& dealer)
{
	if (player.BlackJack && dealer.BlackJack)
	{
		printf("둘다 블랙잭이므로 무승부 입니다.\n\n");
	}
	else if (player.BlackJack)
	{
		printf("플레이어가 블랙잭이므로 승리 입니다.\n\n");
	}
	else
	{
		printf("딜러가 블랙잭이므로 패배 입니다.\n\n");
	}
}

void SumScore(Table& ind)
{
	int i = 0;
	int C_A = 0;
	ind.Score = 0;
	ind.Max_Score = 0;
	while (ind.Card_Number[i] != 0)
	{
		if (ind.Card_Number[i] == 1) { C_A++; }
		switch (ind.Card_Number[i])
		{
		case 11:
			ind.Score += 10;
			break;
		case 12:
			ind.Score += 10;
			break;
		case 13:
			ind.Score += 10;
			break;
		default:
			ind.Score += ind.Card_Number[i];
			break;
		}
		i++;
		if (C_A > 0) { ind.Max_Score = ind.Score + 10; }
	}
}

void PlayerTurn(TrumpCard& card, Table& player, Table& dealer)
{
	int Ch_num = 0;
	while (1)
	{
		if (player.Score > 21) 
		{ 
			player.Bust = true;
			break;
		}
		printf("어떤것을 하시겠습니까?\n 1. Hit(카드추가)  2. Stand(멈춤)\n");
		cin >> Ch_num;
		if (Ch_num == 1) 
		{ 
			GetCard(card, player);
			SumScore(player);
			PrintTable(player, dealer);
			continue; 
		}
		else { break; }
	}
}

void DealerTurn(TrumpCard& card, Table& player, Table& dealer)
{
	int Score = 0;
	while (1)
	{
		if (dealer.Score > 21)
		{
			dealer.Bust = true;
			break;
		}
		if (dealer.Max_Score > 0 && dealer.Max_Score <= 21)
		{
			Score = dealer.Max_Score;
		}
		else
		{
			Score = dealer.Score;
		}
		if (Score < 17)
		{
			GetCard(card, dealer);
			SumScore(dealer);
			continue;
		}
		else { break; }
	}
}

void Result(Table& player, Table& dealer)
{
	int p = 0, d = 0;
	if (player.Max_Score > 0 && player.Max_Score <= 21) { p = player.Max_Score; }
	else { p = player.Score; }
	if (dealer.Max_Score > 0 && dealer.Max_Score <= 21) { d = dealer.Max_Score; }
	else { d = dealer.Score; }
	printf("-------------- 결과 --------------\n");
	printf("플레이어 점수: %d  딜러 점수: %d\n\n", p, d);
	if (p == d)
	{
		printf("점수가 동일하여 무승부입니다.\n\n");
	}
	else if (p > d)
	{
		printf("축하합니다! 승리 하셨습니다.\n\n");
	}
	else
	{
		printf("패배 하셨습니다.\n\n");
	}
}