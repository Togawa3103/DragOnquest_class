#pragma once
#include <vector>
#define MAP_HEIGHT 50
#define MAP_WIDTH 52

#define VIEW_RANGE_WIDHT 12
#define VIEW_RANGE_HEIGHT 10

enum {
	MAP_KINGROOM,
	MAP_CASTLE,
};
typedef struct {
	int toMap_Num;
	int Start_X;
	int Start_Y;
}MAP_INFO;

typedef struct {
	const char* Map_Name;
	std::vector<MAP_INFO> map_info;
}MAP_DATA;

static MAP_DATA map_data[] = {
	{"map_test_door.bmp",{{1,6,8}}},
	{"map_test_next.bmp",{{0,22,21}}},
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
	{0,255,255,FALSE},
	{255,0,0,FALSE}//CELL_TYPE_PLAYER
};


static GRAPHDESC graphDescs[] = {
	{"wall.bmp",},//GRAPH_TYPE_WALL,
	{"floor.bmp",},//GRAPH_TYPE_FLOOR,
	{"door.bmp",},//GRAPH_TYPE_DOOR,
	{"steps.bmp"},//GRAPH_TYPE_STEPS
	{"box.bmp"},//GRAPH_TYPE_TRESURE
	{"Player.bmp",},//GRAPH_TYPE_PLAYER,
	{"Player_turn.bmp"},//GRAPH_TYPE_PLAYER2,
};

enum {
	CELL_TYPE_WALL,
	CELL_TYPE_FLOOR,
	CELL_TYPE_DOOR,
	CELL_TYPE_STEPS,
	CELL_TYPE_TRESURE,
	CELL_TYPE_PLAYER,
	CELL_TYPE_MAX,
};

enum {
	GRAPH_TYPE_WALL,
	GRAPH_TYPE_FLOOR,
	GRAPH_TYPE_DOOR,
	GRAPH_TYPE_STEPS,
	GRAPH_TYPE_TRESURE,
	GRAPH_TYPE_PLAYER,
	GRAPH_TYPE_PLAYER2,
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

	MAP();
	~MAP();
	static void Initialize();
	static void Draw_FIELD();
	static void Load_MAP(int MAP_Num);
};
