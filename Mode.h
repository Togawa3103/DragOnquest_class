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
	{510,280,"北"},
	{550,325,"東"},
	{510,370,"南"},
	{470,325,"西"},
};

typedef struct {
	int x;
	int y;
	const char* name;
}MENU;

static MENU menu[] = {
	{500,30,"はなす"},
	{490,75,"しらべる"},
	{500,120,"どうぐ"},
	{500,165,"とびら"},
	{500,210,"つよさ"},
};
typedef struct {
	const char* Item_name;
	bool canuse;
	int power;
	bool consumption;
}ITEM;


static ITEM item[] = {
	{"やくそう",true,30,true},
	{"かぎ",false,-1,false},
	{"どうのつるぎ",false,-1,false},
	{"かわのよろい",false,-1,false},
	{"うんち",false,-1,false},
	{"オーブ",false,-1,false}
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
	static int selected_NPC;
	static bool show_message;

	static void Initialize();
	static void Field_Mode();
	static void Menu_Mode();
	static void Menu_DireSelect(int Selected_Menu_Num);
	static void Item_Select();
	static void Use_Item(int item_num);
	static void Draw_Message(int item_num);
	static void Status_Show();
};