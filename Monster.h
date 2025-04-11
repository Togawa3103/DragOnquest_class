#pragma once
#include "Player.h"
#include "Magic.h"
#include <vector>
enum {
	Monster_Slime,
	Monster_Bat,
	Monster_MAX,
};

enum {
	Attack_1,//Attack
	Attack_MAX,
};

typedef struct {
	int Monster_Num;
	PLAYER_STATUS enemy_status;
	const char* Monster_Graph_Name;
	const char* Monster_Name;
	std::vector<int> Attack;
}Monster_Status;

static Monster_Status slime = {
	Monster_Slime,
	{5,	-1,	0,	-1,	3,	3,	3,	0,	0,	2,	2},
	"slime.bmp",
	"スライム",
	{0},
};

static Monster_Status bat = {
	Monster_Slime,
	{8,	-1,	0,	-1,	4,	3,	5,	0,	0,	4,	3},
	"bat.bmp",
	"バット",
	{0},
};


class Monster {
public:
	static std::vector<Monster_Status> MonsterArray;
	static int set_Monster(int MAP_Num);
	//static void Cal_Damage(int Comand);
	static int now_HP;
	static int now_MP;
	static int now_Attack;
	static PLAYER_STATUS now_Monster;
};