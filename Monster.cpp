#include "Monster.h"
#include "Battle.h"
#include "MAP.h"
#include <random>

int Monster::now_HP;
int Monster::now_MP;
PLAYER_STATUS Monster::now_Monster;
std::vector<Monster_Status> Monster::MonsterArray = { slime,bat,ghost,king_slime};
int Monster::set_Monster(int Map_Num) {
	int count_MonsterNum = map_data[Map_Num].Monster_Array.size();
	std::random_device rand;
	int monster_Num = rand() % count_MonsterNum;
	int Monster_Num = map_data[Map_Num].Monster_Array[monster_Num];
	return Monster_Num;
}

