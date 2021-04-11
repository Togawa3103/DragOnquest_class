#pragma once
#include "Player.h"
enum {
	Monster_Slime,
	Monster_MAX,
};

typedef struct {
	int Monster_Num;
	PLAYER_STATUS enemy_status;
	const char* Monster_Name;
}Monster_Status;

static Monster_Status slime = {
	Monster_Slime,
	{5,	-1,	0,	-1,	3,	3,	3,	0,	0,	2,	2},
	"slime.bmp",
};
class Monster {
public:
	static int set_Monster(int MAP_Num);
};