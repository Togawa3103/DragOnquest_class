#include <time.h>
#include "DxLib.h"

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