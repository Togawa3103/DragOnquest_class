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
int Player::HP = 20;
int Player::MP = 5;
int Player::Player_Lv = 1;
int Player::Gold = 0;
int Player::Exp = 0;
std::vector<int> Player::ItemBox = { 0,1,2,3,4,5,4 }; //‚à‚¿‚à‚Ì
std::vector<int> Player::MagicBox = {magic_1,magic_2};
int Player::EquipField[Equip_MAX] = {-1,-1,-1,-1};
PLAYER_STATUS Player::now_player_status = (player_status[Player::Player_Lv - 1]);


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
	
}

void Player::Update_Status(int Player_lv) {
	if (Exp>=LVUP_EXP[Player_lv-1]) {
		Player_Lv++;
		Lv_Up = true;
	}
	if (Lv_Up) {
		now_player_status.MAXHP = now_player_status.MAXHP + player_status[Player::Player_Lv - 1].MAXHP;
		now_player_status.MAXMP = now_player_status.MAXMP + player_status[Player::Player_Lv - 1].MAXMP;
		now_player_status.ATTACK = now_player_status.ATTACK + player_status[Player::Player_Lv - 1].ATTACK;
		now_player_status.DEFENSE = now_player_status.DEFENSE + player_status[Player::Player_Lv - 1].DEFENSE;
		now_player_status.SPEED = now_player_status.SPEED + player_status[Player::Player_Lv - 1].SPEED;
		now_player_status.WISE = now_player_status.WISE + player_status[Player::Player_Lv - 1].WISE;
		now_player_status.MAGICDEF = now_player_status.MAGICDEF + player_status[Player::Player_Lv - 1].MAGICDEF;
		Lv_Up = false;
		for (int i = 0; i < player_status[Player::Player_Lv - 1].Learn_Magic.size();i++) {
			MagicBox.push_back(player_status[Player::Player_Lv - 1].Learn_Magic[i]);
		}
	}
	//now_player_status = (player_status[Player_Lv - 1]);
	now_player_status.HP = HP;
	now_player_status.MP = MP;
	now_player_status.GOLD = Gold;
	now_player_status.EXP = Exp;
	int* p;
	p = &(now_player_status.MAXHP);
	
	haveKey = false;
	for (int i = 0; i < ItemBox.size(); i++) {
		if (ItemBox[i] == Item_Key) {
			haveKey = true;
		}
	}
	
}