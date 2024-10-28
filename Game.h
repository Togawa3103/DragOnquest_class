#include <time.h>
#include "DxLib.h"
#include "Player.h"
#include "MAP.h"
#include "Mode.h"

//セーブデータのデータ構造
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

//スタート画面の選択肢
enum {
	StartMenu_Start,
	StartMenu_Continue,
	StartMenu_Max,
};

//スタート画面の選択肢の文字列
typedef struct {
	const char* startmenu_name;
}StartMenu;

//スタート画面の選択肢の文字列
static StartMenu start[] = {
	{"はじめから"},
	{"つづきから"},
};

class Game {
public:
	Game(); //コンストラクタ
	~Game(); //デストラクト
	static void Initialize(); //初期化
	static void Game_Start(); //スタート画面
	static void Game_Main(); //メインループ
	static int Game_StartDraw(); //スタート画面の表示
	static void Save_Data(); //セーブ
	static void Load_Date(); //ロード
	static void Start(); //初めから開始
public:
	static int Game_Mode; //ゲームの状態
	static int FPS; //FPS
	static float mFPS; //1フレームの時間
	static clock_t end; //前フレームの終了時間
	static clock_t now; //現在の時間
	static double looptime; //1フレームにかかった時間
	static int comand; //戦闘時のコマンド
	static int select_magic; //戦闘時選択している魔法
	static int select_item; //戦闘時選択しているアイテム
	static bool Talk_now; //会話しているか
	
};