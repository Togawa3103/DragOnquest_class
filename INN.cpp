#include"INN.h"
#include "Player.h"

INN::INN() {};

INN::~INN() {};

void INN::BUY(bool rest) {
	if (rest) {
		Player::HP = player_status[Player::Player_Lv].MAXHP;
		Player::MP = player_status[Player::Player_Lv].MAXMP;
	}
}