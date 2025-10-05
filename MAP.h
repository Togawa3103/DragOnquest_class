#pragma once
#include <vector>
#include "DxLib.h"

#define MAP_HEIGHT 50
#define MAP_WIDTH 52

#define VIEW_RANGE_WIDHT 12
#define VIEW_RANGE_HEIGHT 10

enum {
	DOOR_0,
	DOOR_MAX,
};

enum {
	MAP_KINGROOM,
	MAP_CASTLE,
	MAP_FIELD,
	MAP_DUNGEON,
	MAP_MAX,
};

typedef struct {
	int toMap_Num;
	int Start_X;
	int Start_Y;
	int toStep_num;
}MAP_INFO;

typedef struct {
	int Door_Num;
	int Door_X;
	int Door_Y;
}DOOR_INFO;

typedef struct {
	const char* Map_Name;
	const char* BGM_Name;
	bool Monster_Appears;
	std::vector<MAP_INFO> map_info;
	std::vector<int > NPC_Num;
	std::vector<DOOR_INFO> Door;
	std::vector<int> Monster_Array;
}MAP_DATA;

static MAP_DATA map_data[] = {
	{"map_test_door.bmp","castle.mp3",FALSE,{{1,6,8,0}},{0,1,3},{{0,5,7}},{}},
	{"map_castle.bmp","castle.mp3",FALSE,{{0,19,17,0},{2,20,35,0}},{},{}},
	{"map_field.bmp","castle.mp3",FALSE,{{1,6,6,1},{3,15,12,0}},{},{},{0,1}},
	{"map_dungeon.bmp","castle.mp3",TRUE,{{2,6,8,1}},{},{}},
};

typedef struct {
	const char* Graph_Name;
	int Graph_Handle;
}GRAPHDESC;

typedef struct {
	unsigned char b, g, r;
}BGR;

typedef struct {
	BGR bgr;
	bool f_canMove;
}CELLDESC;

static CELLDESC cellDescs[] = {
	{0,0,255,FALSE},//CELL_TYPE_WALL
	{0,255,0,TRUE},//CELL_TYPE_FLOOR
	{0,0,0,FALSE},//CELL_TYPE_DOOR
	{232,162,0,TRUE},//CELL_TYPE_STEPS
	{0,255,255,FALSE},//CELL_TYPE_TREASURE
	{128,255,0,TRUE},//CELL_TYPE_GRASS
	{0,128,128,FALSE},//CELL_TYPE_MOUNTAIN
	{128,0,128,TRUE},//CELL_TYPE_CASTLE
	{201,174,255,TRUE},//CELL_TYPE_DUNGEON
	{127,127,127,TRUE},//CELL_TYPE_ROCK
	{195,195,195,FALSE},//CELL_TYPE_WALL_ROCK
	{255,0,0,FALSE},//CELL_TYPE_PLAYER
};


static GRAPHDESC graphDescs[] = {
	{"wall.bmp",},//GRAPH_TYPE_WALL,
	{"floor.bmp",},//GRAPH_TYPE_FLOOR,
	{"door.bmp",},//GRAPH_TYPE_DOOR,
	{"steps.bmp",},//GRAPH_TYPE_STEPS
	{"box.bmp",},//GRAPH_TYPE_TRESURE
	{"grass.bmp",},//GRAPH_TYPE_GRASS,
	{"mountain.bmp",},//GRAPH_TYPE_MOUNTAIN,
	{"castle.bmp",},//GRAPH_TYPE_CASTLE,
	{"dungeon.bmp",},//GRAPH_TYPE_DUNGEON,
	{"rock.bmp",},//GRAPH_TYPE_ROCK,
	{"wall_rock.bmp",},//GRAPH_TYPE_WALL_ROCK,
	{"Player.bmp",},//GRAPH_TYPE_PLAYER,
	{"Player_turn.bmp",},//GRAPH_TYPE_PLAYER2,
};

enum {
	CELL_TYPE_WALL,
	CELL_TYPE_FLOOR,
	CELL_TYPE_DOOR,
	CELL_TYPE_STEPS,
	CELL_TYPE_TREASURE,
	CELL_TYPE_GRASS,
	CELL_TYPE_MOUNTAIN,
	CELL_TYPE_CASTLE,
	CELL_TYPE_DUNGEON,
	CELL_TYPE_ROCK,
	CELL_TYPE_WALL_ROCK,
	CELL_TYPE_PLAYER,
	CELL_TYPE_NPC,
	CELL_TYPE_MAX,
};

enum {
	GRAPH_TYPE_WALL,
	GRAPH_TYPE_FLOOR,
	GRAPH_TYPE_DOOR,
	GRAPH_TYPE_STEPS,
	GRAPH_TYPE_TREASURE,
	GRAPH_TYPE_GRASS,
	GRAPH_TYPE_MOUNTAIN,
	GRAPH_TYPE_CASTLE,
	GRAPH_TYPE_DUNGEON,
	GRAPH_TYPE_ROCK,
	GRAPH_TYPE_WALL_ROCK,
	GRAPH_TYPE_PLAYER,
	GRAPH_TYPE_PLAYER2,
	GRAPH_TYPE_NPC_KING,
	GRAPH_TYPE_MAX,
};


class MAP{
public:
	static int cells[MAP_HEIGHT][MAP_WIDTH];
	static int map[MAP_HEIGHT][MAP_WIDTH];
	static bool canmove[MAP_HEIGHT][MAP_WIDTH];
	static const char* File_Name;
	static int Screen_X;
	static int Screen_Y;
	static int Move_Count_X;
	static int Move_Count_Y;
	static int MAP_Num;
	static int map_bgm[MAP_MAX];
	static std::vector<int> Door_Open;

	MAP();
	~MAP();
	static void Initialize();
	static void Draw_FIELD();
	static void Load_MAP(int MAP_Num);
	static bool ChangeMAP(int Player_x,int Player_y);
};
