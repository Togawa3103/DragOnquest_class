#pragma once
#include<vector>
enum {
	NPC_1,
	NPC_2,
	NPC_MAX,
};

enum {
	NPC_TYPE_King,
	NPC_TYPE_Solder,
	NPC_Type_2,
};
typedef struct {
	const char* text;
}TEXT;

static TEXT text[] = {
	"おお、ゆうしゃよ",
	"まおうをたおしてくれ！",
	"ありがとう",
	"うんち",
	"しね",
	"うんち",
	"まおうをたおしにいくらしいな！",
	"がんばってくれ！",
	"おうえんしているぞ！",
};

typedef struct {
	int NPC_Type;
	const char* Graph_Name;
	int load_graph;
}NPC_GRAPH;

static NPC_GRAPH npc_graph[] = {
	{NPC_TYPE_King,"king.bmp",-1},
	{NPC_TYPE_Solder,"solder.bmp",-1}
};
typedef struct {
	int NPC_Num;
	int MAP_Num;
	int x;
	int y;
	int NPC_Type;
	std::vector<int> text;
}NPC_DATA;

static NPC_DATA npc[] = {
	{0,0,4,5,NPC_TYPE_King,{0,1,-2,2,3,4,5}},
	{1,0,7,5,NPC_TYPE_Solder,{6,7,8}},
};

class NPC {
public:
	static std::vector<int> npc_num;
	static int Talk_Count;
	static int Yes_No;
	static int finish_text;
	static void Load_NPC(int MAP_Num);
	static void Draw_NPC(std::vector<int> npc_num);
	static void Draw_Talk(int NPC_Num);
	static void Draw_Question(int NPC_Num);
};

