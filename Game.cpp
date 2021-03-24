#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "DxLib.h"
#include "Game.h"
#include "Player.h"
#include "MAP.h"
#include "Mode.h"

int Game::FPS = 144;
float Game::mFPS = 1000.f / FPS;
int Game::Game_Mode = 0;
clock_t Game::end;
clock_t Game::now;
double Game::looptime;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE);
    SetGraphMode(600, 500, 32);

    DxLib_Init();   // DXライブラリ初期化処理
    SetDrawScreen(DX_SCREEN_BACK);

    SetTransColor(182, 185, 184);
    
    ClearDrawScreen();
    Game game;
    game.Game_Main();
    WaitKey();      // キー入力待ち
    DxLib_End();    // DXライブラリ終了処理
    return 0;
}
Game::Game() {
}
Game::~Game() {
}

void Game::Initialize() {
    
    Game::end = clock();
}

void Game::Game_Main() {
    Player player;
    MAP map;
    Mode mode;
    map.Initialize();
    map.Load_MAP(map.MAP_Num);
    map.Draw_FIELD();
    mode.Initialize();
    map.Initialize();
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        player.Update_Status(player.Player_Lv);
        GetHitKeyStateAll(mode.keyState);
        //ScreenFlip();
        //ClearDrawScreen();
        if (mode.GameMode==GameMode_FIELD) {
            mode.Field_Mode();
        }
        else if (mode.GameMode==GameMode_MENU) {
            map.Draw_FIELD();
            if (mode.Selected_Menu < 0) {
                mode.Menu_Mode();
            }
            else if (mode.Selected_Menu == MenuType_DOOR) {
                mode.Menu_DireSelect(mode.Selected_Menu);
            }
            else if (mode.Selected_Menu==MenuType_SEARCH) {
                mode.Menu_DireSelect(mode.Selected_Menu);
            }
            else if (mode.Selected_Menu==MenuType_Item) {
                mode.Item_Select();
            }
            else if (mode.Selected_Menu==MenuType_STATUS) {
                mode.Status_Show();
            }
        }
        mode.old_E_keyState = mode.keyState[KEY_INPUT_E];
        mode.old_RETURN_keyState = mode.keyState[KEY_INPUT_RETURN];
        mode.old_ESCAPE_keyState = mode.keyState[KEY_INPUT_RETURN];
        
        Game::now = clock();
        Game::looptime = Game::now - Game::end;
        if (Game::looptime<Game::mFPS) {
            Sleep(Game::mFPS-Game::looptime);
        }
    }
}