#pragma once

enum {
	GameMode_FIELD,
	GameMode_MENU,
	GameMode_BATTLE,
	GameMode_LOAD,
};
enum {
	MenuType_Talk,
	MenuType_SEARCH,
	MenuType_Item,
	MenuType_DOOR,
	MenuType_STATUS,
	MenuType_MAX,
};

enum {
	Dire_N,
	Dire_E,
	Dire_S,
	Dire_W,
	Dire_MAX,
};

typedef struct {
	int x;
	int y;
	const char* Dire;
}DIRE;

static DIRE dire[] = {
	{510,280,"�k"},
	{550,325,"��"},
	{510,370,"��"},
	{470,325,"��"},
};

typedef struct {
	int x;
	int y;
	const char* name;
}MENU;

static MENU menu[] = {
	{500,30,"�͂Ȃ�"},
	{490,75,"����ׂ�"},
	{500,120,"�ǂ���"},
	{500,165,"�Ƃт�"},
	{500,210,"�悳"},
};
typedef struct {
	const char* Item_name;
}ITEM;


static ITEM item[] = {
	{"�₭����"},
	{"����"},
	{"�ǂ��̂邬"},
	{"����̂�낢"},
	{"����"},
};

class Mode {
public:
	static int GameMode;
	static char keyState[256];
	static char old_E_keyState;
	static char old_RETURN_keyState;
	static char old_ESCAPE_keyState;
	static int Select_Menu_Num;
	static int Select_Dire_Num;
	static int Select_Item;
	static int Selected_Menu;

	static void Initialize();
	static void Field_Mode();
	static void Menu_Mode();
	static void Menu_DireSelect(int Selected_Menu_Num);
	static void Item_Select();
	static void Status_Show();
};