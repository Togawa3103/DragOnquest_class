#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "DxLib.h"
#include "Game.h"
#include "Player.h"
#include "MAP.h"
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
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

        //ScreenFlip();
        //ClearDrawScreen();
        Game::now = clock();
        Game::looptime = Game::now - Game::end;
        MAP::Initialize();
        MAP::Load_MAP();
        MAP::Draw_FIELD();
        if (Game::looptime<Game::mFPS) {
            Sleep(Game::mFPS-Game::looptime);
        }
    }
}