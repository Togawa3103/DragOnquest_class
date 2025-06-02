#include"Shop.h"

Shop::Shop() {}
Shop::~Shop() {};
int Shop::shop_npc = -1;
int Shop::shop_select_item = 0;
int Shop::check = 0; 
int Shop::Yes_No = 0;

void Shop::BUY(int npc_num,int item) {
	Player::ItemBox.push_back(item);
	Player::Gold = Player::Gold - shop[npc_num].Item_Price[item];
}