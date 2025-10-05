#pragma once
#include "Player.h"
#include "Battle.h"
#include <vector>
enum {
	Monster_Slime,
	Monster_Bat,
	Monster_Ghost,
	Monster_KingSlime,
	Monster_MAX,
};

enum {
	Attack_1,//Attack
	Attack_2,//Magic
	Attack_3,//Item
	Attack_4,//Run
	Attack_MAX,
};

typedef struct {
	int Monster_Num;
	PLAYER_STATUS enemy_status;
	const char* Monster_Graph_Name;
	const char* Monster_Name;
	std::vector<int> Attack;
	std::vector<float> Attack_Rate;
	std::vector<int> Magic;
}Monster_Status;

static Monster_Status slime = {
	Monster_Slime,
	{5,	-1,	0,	-1,	3,	3,	3,	0,	0,	2,	2},
	"slime.bmp",
	"スライム",
	{Comand_Fight},
	{1.0},
	{}
};

static Monster_Status bat = {
	Monster_Slime,
	{8,	-1,	0,	-1,	4,	3,	5,	0,	0,	4,	3},
	"bat.bmp",
	"バット",
	{Comand_Fight},
	{1.0},
	{}
};

static Monster_Status ghost = {
	Monster_Ghost,
	{8,	-1,	0,	-1,	4,	3,	5,	8,	2,	4,	3},
	"ghost.bmp",
	"ゴースト",
	{Comand_Fight,Comand_Magic},
	{0.3,0.7},
	{magic_2}
};

static Monster_Status king_slime = {
	Monster_KingSlime,
	{15,	-1,	0,	-1,	1,	1,	1,	1,	1,	1,	1},
	"kingslime.bmp",
	"キングスライム",
	{Comand_Fight},
	{1},
	{}
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