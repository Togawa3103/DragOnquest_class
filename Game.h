#include <time.h>
#include "DxLib.h"

typedef struct {
	int Player_Lv;
	//PLAYER_STATUS Player_Status;    
	int Player_X;
	int Player_Y;
	int MAP_Num;
	int Screen_X;
	int Screen_Y;
	int Move_Count_X;
	int Move_Count_Y;
	int ItemBox_size;
	//std::vector<int> ItemBox;
}SaveData;

enum {
	StartMenu_Start,
	StartMenu_Continue,
	StartMenu_Max,
};
typedef struct {
	const char* startmenu_name;
}StartMenu;

static StartMenu start[] = {
	{"‚Í‚¶‚ß‚©‚ç"},
	{"‚Â‚Ã‚«‚©‚ç"},
};

class Game {
public:
	Game();
	~Game();
	static void Initialize();
	void Game_Main();
	int Game_Start();
	void Save_Data();
	void Load_Date();
public:
	static int Game_Mode;
	static int FPS;
	static float mFPS;
	static clock_t end;
	static clock_t now;
	static double looptime;
	static int comand;
	static int select_magic;
	static int select_item;
	static bool Talk_now;
	
};