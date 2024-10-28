#pragma once
#include"Shop.h"

enum {
	INN_1,
	INN_MAX,
};

typedef struct {
	int NPC_Num;
	const char* price;
}INN_PRICE_LIST;

static INN_PRICE_LIST inn_list[] = {
	{2,"5" },
};

class INN :public Shop {
public:
	INN();
	~INN();
	static void BUY(bool rest);
	int Price=0;
};