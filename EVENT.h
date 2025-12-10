#pragma once
#include <bitset>
#include "MAP.h"
#include "Monster.h"
#include "Game.h"

enum {
	EVENTS_None,
	EVENTS_CLEAR,
	EVENTS_BATTLE,
	EVENTS_BOSS,
	EVENTS_MAX
};

enum {
	EVENTNUM_0,
	EVENTNUM_1,
	EVENTNUM_2,
	EVENTNUM_MAX
};

typedef struct {
	int map_num;
	int x;
	int y;
	int item_num;
	int monster_num;
}EVENT_DATA;

static EVENT_DATA events[] = {
	{0,0,0,0,-1},
	{MAP_KINGROOM,5,5,0,-1},
	{MAP_DUNGEON,6,3,0, Monster_KingSlime},
};

class EVENT {
public:
	EVENT(); //コンストラクタ
	//~EVENT(); //デストラクト

	static int IsEvent();
	static int SetMonster(int Events_Num);
	static void BattleInit(int Events_Num);
	static void SetFlag(int Events_Num);
public:
	static std::bitset<4> flag;
};