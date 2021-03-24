#pragma once
#include "Player.h"
#include "Enum.h"
int Player::Player_Time = 0;
int Player::MENU_Time = 0;
int Player::PlayerCount = 0;
int Player::Player_X = 4;
int Player::Player_Y = 4;
int Player::old_Player_X = Player_X;
int Player::old_Player_Y = Player_Y;
int Player::HP = 10;
int Player::MP = 5;
int Player::Player_Lv = 1;
int Player::Gold = 0;
int Player::Exp = 0;
std::vector<int> Player::ItemBox = { 0,2,3,4 }; //‚à‚¿‚à‚Ì
PLAYER_STATUS Player::now_player_status = (player_status[Player::Player_Lv - 1]);
int Player::Player_Status[STATUS_MAX];

bool Player::haveKey=false;
bool Player::Lv_Up = false;

Player::Player() {
	Player::Initialize();
}

Player::~Player() {
}

void Player::Initialize() {
	now_player_status = (player_status[Player_Lv - 1]);
	now_player_status.HP = HP;
	now_player_status.MP = MP;
	now_player_status.GOLD = Gold;
	now_player_status.EXP = Exp;
	int* p;
	p = &(now_player_status.MAXHP);
	for (int i = 0; i < STATUS_MAX; i++) {
		Player_Status[i] = *(p + i);
	}
}

void Player::Update_Status(int Player_Lv) {
	if (Exp>=LVUP_EXP[Player_Lv-1]) {
		Player::Player_Lv++;
		Lv_Up = true;
	}
	if (Lv_Up) {
		int now_HP = now_player_status.HP;
		int now_MP = now_player_status.MP;
		int now_GOLD = now_player_status.GOLD;
		int now_EXP = now_player_status.EXP;

	}
	now_player_status = (player_status[Player_Lv - 1]);
	now_player_status.HP = HP;
	now_player_status.MP = MP;
	now_player_status.GOLD = Gold;
	now_player_status.EXP = Exp;
	int* p;
	p = &(now_player_status.MAXHP);
	for (int i = 0; i < STATUS_MAX; i++) {
		Player_Status[i] = *(p + i);
	}
	haveKey = false;
	for (int i = 0; i < ItemBox.size(); i++) {
		if (ItemBox[i] == Item_Key) {
			haveKey = true;
		}
	}
	
}