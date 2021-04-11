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
	{120,390,"‚½‚½‚©‚¤"},
	{120,415,"‚¶‚ã‚à‚ñ"},
	{120,440,"‚Ç‚¤‚®"},
	{120,465,"‚É‚°‚é"},
};


class Battle {
public:
	Battle();
	~Battle();
	static void Initialize();
	static void Draw_Battle(int);
	static int Start_Battle(int Player_Count);
	static int Set_Comand();
	static int Select_Magic();
	static int Select_Item();
	static bool Comand_RunAway();
	static void Update_Battle(int Comand);


	static int Monster_Num;
	static int Monster_graph;
	static int Select_Comand;
	
};