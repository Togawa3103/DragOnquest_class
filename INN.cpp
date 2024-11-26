#include"INN.h"
#include "Player.h"

INN::INN() {};

INN::~INN() {};

void INN::BUY(bool rest) {
	if (rest) {
		Player::HP = Player::now_player_status.MAXHP;
		Player::MP = Player::now_player_status.MAXMP;
	}
}