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
	{510,280,"ñk"},
	{550,325,"ìå"},
	{510,370,"ìÏ"},
	{470,325,"êº"},
};

typedef struct {
	int x;
	int y;
	const char* name;
}MENU;

static MENU menu[] = {
	{500,30,"ÇÕÇ»Ç∑"},
	{490,75,"ÇµÇÁÇ◊ÇÈ"},
	{500,120,"Ç«Ç§ÇÆ"},
	{500,165,"Ç∆Ç—ÇÁ"},
	{500,210,"Ç¬ÇÊÇ≥"},
};
typedef struct {
	const char* Item_name;
	bool canuse;
	int power;
	bool consumption;
}ITEM;


static ITEM item[] = {
	{"Ç‚Ç≠ÇªÇ§",true,30,true},
	{"Ç©Ç¨",false,-1,false},
	{"Ç«Ç§ÇÃÇ¬ÇÈÇ¨",false,-1,false},
	{"Ç©ÇÌÇÃÇÊÇÎÇ¢",false,-1,false},
	{"Ç§ÇÒÇø",false,-1,false},
	{"ÉIÅ[Éu",false,-1,false}
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
	//static void Walk_Effect(int x, int y);
};