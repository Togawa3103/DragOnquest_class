#pragma once
#include <vector>
#include "Magic.h"
typedef struct {
	int MAXHP;
	int HP;
	int MAXMP;
	int MP;
	int ATTACK;
	int DEFENSE;
	int SPEED;
	int WISE;
	int MAGICDEF;
	int GOLD;
	int EXP;
	std::vector<int> Learn_Magic;
}PLAYER_STATUS;

typedef struct {
	const char* status_name;
}STATUS;

static PLAYER_STATUS player_status[] = {
	{20,-1,3,-1,5,5,5,5,5,-1,-1,{}},//Lv1
	{5,-1,5,-1,3,3,3,3,3,-1,-1,{magic_2,magic_1}},//Lv2
	{5,-1,5,-1,11,15,5,5,3,-1,-1,{magic_3} },//Lv3
	{5,-1,5,-1,14,13,13,13,5,-1,-1,{magic_4}},//Lv4
};

static STATUS status[] = {
	{"‚³‚¢‚¾‚¢HP"},
	{"HP"},
	{"‚³‚¢‚¾‚¢MP"},
	{"MP"},
	{"‚±‚¤‚°‚«"},
	{"‚Ú‚¤‚¬‚å"},
	{"‚Í‚â‚³"},
	{"‚©‚µ‚±‚³"},
	{"‚Ü‚Ù‚¤‚Ú"},
	{"‚¨‚©‚Ë"},
	{"‚¯‚¢‚¯‚ñ‚¿"},
};

enum {
	STATUS_MAXHP,
	STATUS_HP,
	STATUS_MAXMP,
	STATUS_MP,
	STATUS_ATTACK,
	STATUS_DEFENSE,
	STATUS_SPEED,
	STATUS_WISE,
	STATUS_MAGICDEF,
	STATUS_GOLD,
	STATUS_EXP,
	STATUS_MAX,
};

enum {
	Equip_Head,
	Equip_Meal,
	Equip_Weapon,
	Equip_Sheild,
	Equip_MAX,
};

static int LVUP_EXP[] = {10,30,50,70};

class Player {
public:
	static int Player_Time;
	static int MENU_Time;
	static int PlayerCount;
	static int Player_X;
	static int Player_Y;
	static int old_Player_X;
	static int old_Player_Y;
	
	static int HP;
	static int MP;
	static int Player_Lv;
	static int Gold;
	static int Exp;
	static std::vector<int> ItemBox; //‚à‚¿‚à‚Ì
	static std::vector<int> MagicBox;
	static int EquipField[Equip_MAX];
	static bool Lv_Up;
	static bool haveKey;
	
	static PLAYER_STATUS now_player_status;
	

public:
	Player();
	~Player();
	void Initialize();
	static void Update_Status(int Player_lv);
};