#pragma once

enum {
	Comand_Fight,
	Comand_Magic,
	Comand_Item,
	Comand_Run,
	Comand_Max,
};

typedef struct {
	int x;
	int y;
	const char* string;
}Comand;

static Comand comand[] = {
	{120,390,"たたかう"},
	{120,415,"じゅもん"},
	{120,440,"どうぐ"},
	{120,465,"にげる"},
};


class Battle {
public:
	Battle();
	~Battle();
	static void Initialize();
	static void Draw_Battle();
	static int Start_Battle(int Player_Count);
	static int Set_Comand();
	static int Select_Magic();
	static int Select_Item();
	static bool Comand_RunAway();
	//static void Update_Battle(int Comand);
	static void Finish_Battle(int Comand);
	static void Dead();
	static void Draw_Message(int Comand, int turn,bool canrun);//逃げる
	static void Draw_Message(int Comand, int turn);//攻撃
	static void Draw_Message(int Comand,int turn,int magic_num);//魔法
	static void Draw_Message(int Comand,int turn, int item_Num, bool canuse);//道具
	static void check_speed();
	//static void Player_Turn(int Comand);
	static int Enemy_AI(int Monster_Num);
	//static void Turn_Swap();

	static void Update_Player(int Comand);
	static void Update_Monster(int Comand);
	static void Cal_Damage(int turn,int Comand);
	static void Cal_Damage(int turn, int Comand, int Magic_Num);
	static void Cal_Damage(int turn, int Comand, int item_Num,bool canuse);
	static void Check_Battle_End();

	static void Effect(int turn,int Comand,int sub_Num);
	
	static void NoMagic();
	static void NoItem();

	static int Turn;//0:Enemy 1:Player
	static bool Battle_Now;
	static bool canRun;
	static int Monster_Num;
	static int Monster_graph;
	static int Select_Comand;
	static int blackout_loop_count;
	static int brightness;
	static bool effect;
};