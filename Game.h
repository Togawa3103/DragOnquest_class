#include <time.h>


class Game {
public:
	Game();
	~Game();
	static void Initialize();
	void Game_Main();
public:
	static int Game_Mode;
	static int FPS;
	static float mFPS;
	static clock_t end;
	static clock_t now;
	static double looptime;
	static int comand;
	
};