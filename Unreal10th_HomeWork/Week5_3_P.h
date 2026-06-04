#pragma once

// 1. 목표
// - 플레이어는 컴퓨터가 숨겨놓은 적 함선을 찾아 격침시킨다.
// 2. 맵 크기는 10 x 10이다.
// - 각 칸에는 함선 또는 빈 칸이 위치한다.
// 3. 적 함선 종류
// - 총 4척: 크기 5, 4, 3, 2 (항공모함, 전함, 순양함, 구축함 등)
// 4. 함선 배치
// - 함선은 맵에 겹치지 않게 가로 또는 세로로 랜덤 배치된다.
// 5. 플레이어의 목표
// - 제한된 공격 횟수(30회) 내에 모든 적 함선을 명중시켜 격침시키는 것.
// 6. 게임 진행 방식
// - 플레이어는(x, y) 좌표를 입력해 공격한다.
// - 공격 결과(명중 / 실패)는 바로 표시되고, 플레이어의 맵에 기록된다.
// - 이미 공격한 좌표는 다시 공격할 수 없다.
// 7. 함선 격침
// - 한 함선의 모든 칸을 명중시키면 "격침" 메시지가 출력된다.
// 8. 게임 종료 조건
// - 모든 적 함선을 격침시키면 승리.
// - 주어진 횟수 내에 격침하지 못하면 패배하며, 패배 시 적 함선의 실제 위치가 공개된다.
// 9. 추가 정보
// - 남은 공격 횟수와 남은 적 함선 수가 항상 안내된다.
// - 제출 방식
//		- 리포지토리 링크와 플레이 영상 링크 올리기

void Homework_Run(); 

class Ship
{
public:
	std::string Name = "배";
	int Size = 0;
	Ship() = default;
	Ship(const char* InName, int InSize)
		: Name(InName), Size(InSize)
	{ }
	~Ship() = default;
};

class Map
{
public:
	int X = 0;
	int Y = 0;
	int* ViewMap = new int[X * Y];
	int* UseMap = new int[X * Y];

	Map() = default;
	Map(int InX, int InY)
		: X(InX), Y(InY)
	{ 
	}
	~Map() 
	{
	}

	void Cleanup();
};

void Ship_Installation(Map& UseMap);

void Map_Print(Map UseMap);

int GetRandomRange(int Min, int Max);