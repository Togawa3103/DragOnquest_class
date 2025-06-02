#pragma once
#include "enum.h"
#include<vector>
#include<string>
#include"Player.h"

// ショップ構造体
typedef struct{
	int NPC_NUM;
	std::vector<int> Item_List;
	std::vector<int> Item_Price;
}SHOP;

// ショップ一覧
static SHOP shop[] = {
	{2,{Item_Herb,Item_Key},{3,50}}
};
class Shop {
public:
	
	Shop();
	~Shop();
	static int Shop_Type;
	static int shop_npc;
	static int shop_select_item;
	static int check;
	static int Yes_No;
	static void BUY(int npc_num, int item);
};

