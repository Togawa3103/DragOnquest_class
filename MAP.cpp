#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "MAP.h"
#include "Player.h"
#include "Game.h"
#include "Sound.h"
#include "NPC.h"
#include"Mode.h"

int MAP::MAP_Num = 0;
const char* MAP::File_Name = map_data[MAP_Num].Map_Name;
int MAP::Screen_X;
int MAP::Screen_Y;
int MAP::Move_Count_X;
int MAP::Move_Count_Y;
bool MAP::canmove[MAP_HEIGHT][MAP_WIDTH];
int MAP::map[MAP_HEIGHT][MAP_WIDTH];
int MAP::cells[MAP_HEIGHT][MAP_WIDTH];
int MAP::map_bgm[MAP_MAX];

std::vector<int> MAP::Door_Open(DOOR_MAX, 0);
int MAP::player_moving = 0;
int MAP::scrool_x = 0;
int MAP::scrool_y = 0;
static bool scrool_flag_x = false;
static bool scrool_flag_y = false;
MAP::MAP() {
    for (int i = 0; i < MAP_MAX; i++) {
        MAP::map_bgm[i] = -1;
    }
    MAP::Initialize();
}

MAP::~MAP() {}

void MAP::Initialize() {
    MAP::MAP_Num = 0;
    MAP::Screen_X = 5;
    MAP::Screen_Y = 5;
    MAP::Move_Count_Y = 0;
    MAP::Move_Count_X = 0;

}

void MAP::Draw_FIELD() {
    if (!CheckSoundMem(MAP::map_bgm[MAP::MAP_Num]) && Mode::GameMode == GameMode_FIELD) {
        Sound::PlayBGMSound(MAP::map_bgm);
    }
    else if (CheckSoundMem(MAP::map_bgm[MAP::MAP_Num]) && Mode::GameMode == GameMode_BATTLE) {
        Sound::StopSound(MAP::map_bgm);
    }

    //スクロール制御
    if ((Player::Player_X != Player::old_Player_X || Player::Player_Y != Player::old_Player_Y)
        && !(scrool_flag_x || scrool_flag_y)
        && Player::Player_Time < Game::mFPS+1) {
        if (Player::Player_X > Player::old_Player_X) {
            MAP::Screen_X++;
        }
        if (Player::Player_X < Player::old_Player_X) {
            MAP::Screen_X--;
        }
        if (MAP::Screen_X > 8 && Player::Player_X > Player::old_Player_X) {
            scrool_flag_x = true;
            MAP::Screen_X = 8;
        }
        else if (MAP::Screen_X < 3 && Player::Player_X < Player::old_Player_X) {
            scrool_flag_x = true;
            MAP::Screen_X = 3;
        }

        if (Player::Player_Y > Player::old_Player_Y) {
            MAP::Screen_Y++;
        }
        if (Player::Player_Y < Player::old_Player_Y) {
            MAP::Screen_Y--;
        }
        if (MAP::Screen_Y > 7 && Player::Player_Y > Player::old_Player_Y) {
            scrool_flag_y = true;
            MAP::Screen_Y = 7;
        }
        else if (MAP::Screen_Y < 4 && Player::Player_Y < Player::old_Player_Y) {
            scrool_flag_y = true;
            MAP::Screen_Y = 4;

        }
    }

    
    for (int i = -1; i < VIEW_RANGE_HEIGHT + 1; i++) {
        for (int j = -1; j < VIEW_RANGE_WIDHT + 1; j++) {
            DrawExtendGraph(j * 50 - scrool_x, i * 50 - scrool_y, j * 50 + 50 - scrool_x, i * 50 + 50 - scrool_y,
                graphDescs[MAP::map[i + MAP::Move_Count_Y][j + MAP::Move_Count_X]].Graph_Handle, TRUE);
        }
    }
    /*
    if (Player::PlayerCount / (Game::FPS / 2) > 0 && Player::Player_Time == 0) {
        DrawExtendGraph((Player::Player_X - MAP::Move_Count_X) * 50, (Player::Player_Y - MAP::Move_Count_Y) * 50, (Player::Player_X - MAP::Move_Count_X) * 50 + 50, (Player::Player_Y - MAP::Move_Count_Y) * 50 + 50, graphDescs[GRAPH_TYPE_PLAYER].Graph_Handle, TRUE);
    }
    else if(!(Player::PlayerCount / (Game::FPS / 2) > 0) && Player::Player_Time == 0) {
        DrawExtendGraph((Player::Player_X - MAP::Move_Count_X) * 50, (Player::Player_Y - MAP::Move_Count_Y) * 50, (Player::Player_X - MAP::Move_Count_X) * 50 + 50, (Player::Player_Y - MAP::Move_Count_Y) * 50 + 50, graphDescs[GRAPH_TYPE_PLAYER2].Graph_Handle, TRUE);
    }*/

    if (Player::PlayerCount / (Game::FPS / 2) > 0) {
        DrawExtendGraph((Player::old_Player_X - MAP::Move_Count_X) * 50 + (MAP::player_moving) * (Player::Player_X - Player::old_Player_X),
            (Player::old_Player_Y - MAP::Move_Count_Y) * 50 + (MAP::player_moving) * (Player::Player_Y - Player::old_Player_Y),
            (Player::old_Player_X - MAP::Move_Count_X) * 50 + 50 + (MAP::player_moving) * (Player::Player_X - Player::old_Player_X),
            (Player::old_Player_Y - MAP::Move_Count_Y) * 50 + 50 + (MAP::player_moving) * (Player::Player_Y - Player::old_Player_Y),
            graphDescs[GRAPH_TYPE_PLAYER].Graph_Handle, TRUE);
    }
    else {
        DrawExtendGraph((Player::old_Player_X - MAP::Move_Count_X) * 50 + (MAP::player_moving) * (Player::Player_X - Player::old_Player_X),
            (Player::old_Player_Y - MAP::Move_Count_Y) * 50 + (MAP::player_moving) * (Player::Player_Y - Player::old_Player_Y),
            (Player::old_Player_X - MAP::Move_Count_X) * 50 + 50 + (MAP::player_moving) * (Player::Player_X - Player::old_Player_X),
            (Player::old_Player_Y - MAP::Move_Count_Y) * 50 + 50 + (MAP::player_moving) * (Player::Player_Y - Player::old_Player_Y),
            graphDescs[GRAPH_TYPE_PLAYER2].Graph_Handle, TRUE);
    }

    //描画後プレイヤーのスクロール更新
    if ((Player::Player_X != Player::old_Player_X || Player::Player_Y != Player::old_Player_Y)
        && Player::Player_Time <= 300
        && (MAP::player_moving < 50)) {
        if(!scrool_flag_x){
            MAP::player_moving = MAP::player_moving + (Player::Player_X - Player::old_Player_X)* (Player::Player_X - Player::old_Player_X);
        }
        if (!scrool_flag_y) {
            MAP::player_moving = MAP::player_moving + (Player::Player_Y - Player::old_Player_Y)* (Player::Player_Y - Player::old_Player_Y);
        }       
    }
    else {
        MAP::player_moving = 0;
    }

    //描画後マップのスクロール更新
    if (scrool_flag_x) {
        if (scrool_x * scrool_x <= 2500) {
            if (MAP::Screen_X == 8) {
                scrool_x = scrool_x + 1;
            }
            else if (MAP::Screen_X == 3) {
                scrool_x = scrool_x - 1;
            }
        }
        if (scrool_x * scrool_x > 2500) {
            scrool_flag_x = false;
            scrool_x = 0;
            scrool_y = 0;
            if (MAP::Screen_X == 8) {
                Move_Count_X++;
            }
            else if (MAP::Screen_X == 3) {
                Move_Count_X--;
            }
        }
    }
    if (scrool_flag_y) {
        if (scrool_y * scrool_y <= 2500) {

            if (MAP::Screen_Y == 7) {
                scrool_y = scrool_y + 1;
            }
            else if (MAP::Screen_Y == 4) {
                scrool_y = scrool_y - 1;
            }
        }
        if (scrool_y * scrool_y > 2500) {
            scrool_flag_y = false;
            scrool_x = 0;
            scrool_y = 0;
            if (MAP::Screen_Y == 7) {
                Move_Count_Y++;
            }
            else if (MAP::Screen_Y == 4) {
                Move_Count_Y--;
            }
        }
    }


    //Mode::Walk_Effect(Player::Player_X, Player::Player_Y);
    NPC::Draw_NPC(NPC::npc_num,scrool_x,scrool_y);
    
    if (false) {//デバッグ用座標表示
        unsigned int Comand_Cr1 = GetColor(255, 255, 255);
        unsigned int Comand_Cr2 = GetColor(0, 0, 0);

        DrawBox(200, 370, 350, 500, Comand_Cr1, TRUE);
        DrawBox(210, 380, 340, 490, Comand_Cr2, TRUE);
        DrawFormatString(220, 390, Comand_Cr1, "%d", Player::Player_X);
        DrawFormatString(220, 390 +20, Comand_Cr1, "%d", Player::Player_Y); 
        DrawFormatString(220, 390+ 40, Comand_Cr1, "%d", MAP::MAP_Num);
        DrawFormatString(220, 390 + 60, Comand_Cr1, "%d", MAP::Screen_X);
        DrawFormatString(220, 390 + 80, Comand_Cr1, "%d", MAP::Screen_Y);
    }
}

void MAP::Load_MAP(int MAP_Num) {

    MAP::MAP_Num = MAP_Num;
    MAP::File_Name = map_data[MAP_Num].Map_Name;
    if (MAP::map_bgm[MAP::MAP_Num] == -1) {
        Sound::LoadSound(map_data[MAP::MAP_Num].BGM_Name, MAP::map_bgm);
    }
    FILE* pFile = fopen(MAP::File_Name, "rb");
    if (pFile == NULL) {
        DxLib_End();
    }

    BITMAPFILEHEADER bmfh;
    fread(&bmfh, sizeof BITMAPFILEHEADER, 1, pFile);
    BITMAPINFOHEADER bmih;
    fread(&bmih, sizeof BITMAPINFOHEADER, 1, pFile);


    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {

            BGR bgr;
            fread(&bgr, sizeof BGR, 1, pFile);
            int cellType = -1;
            ClearDrawScreen();
            for (int i = 0; i < CELL_TYPE_MAX; i++) {
                if ((bgr.b == cellDescs[i].bgr.b) && (bgr.g == cellDescs[i].bgr.g) && (bgr.r == cellDescs[i].bgr.r)) {
                    unsigned int Cr = GetColor(255, 255, 255);
                    DrawFormatString(50, 50, Cr, "%d %d", y, x);
                    DrawFormatString(100, 50, Cr, "%d %d %d", bgr.b, bgr.g, bgr.r);
                    //WaitKey();
                    cellType = i;
                    break;
                }
            }
            if (cellType == -1) {
                unsigned int Cr = GetColor(255, 255, 255);
                DrawFormatString(50, 50, Cr, "%d %d", y, x);
                DrawFormatString(100, 50, Cr, "%d %d %d", bgr.b, bgr.g, bgr.r);
                ScreenFlip();
                WaitKey();
                DxLib_End();
            }
            MAP::map[MAP_HEIGHT - 1 - y][x] = cellType;
            MAP::cells[MAP_HEIGHT - 1 - y][x] = cellType;
            MAP::canmove[MAP_HEIGHT - 1 - y][x] = cellDescs[cellType].f_canMove;
        }
    }
    for (int i = 0; i < map_data[MAP_Num].Door.size(); i++) {
        if (Door_Open[map_data[MAP_Num].Door[i].Door_Num] == 1) {
            MAP::canmove[map_data[MAP_Num].Door[i].Door_Y][map_data[MAP_Num].Door[i].Door_X] = TRUE;
            MAP::map[map_data[MAP_Num].Door[i].Door_Y][map_data[MAP_Num].Door[i].Door_X] = CELL_TYPE_FLOOR;
        }
    }
    for (int i = 0; i < GRAPH_TYPE_MAX; i++) {
        graphDescs[i].Graph_Handle = LoadGraph(graphDescs[i].Graph_Name);
    }
    NPC::Load_NPC(MAP::MAP_Num);
    //PlaySoundMem(MAP::map_bgm[MAP_Num], DX_PLAYTYPE_LOOP);
   // Sound::PlayBGMSound(map_bgm);
}

bool MAP::ChangeMAP(int Player_x, int Player_y) {
    return (MAP::map[Player::Player_Y][Player::Player_X] == CELL_TYPE_STEPS 
        || MAP::map[Player::Player_Y][Player::Player_X] == CELL_TYPE_CASTLE 
        || MAP::map[Player::Player_Y][Player::Player_X] == CELL_TYPE_DUNGEON);
}