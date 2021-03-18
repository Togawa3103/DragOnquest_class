#include "DxLib.h"
#include "Game.h"
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    
    FILE* pFile = fopen(File_Name, "rb");
    if (pFile == NULL) {
        DxLib_End();
    }
    Game game;
    game.Initialize();
    game.Game_Main();
    
    
    WaitKey();      // キー入力待ち
    DxLib_End();    // DXライブラリ終了処理
    return 0;
}

Game::Game() {
    
}

Game::Initialize() {
    ChangeWindowMode(TRUE);
    SetGraphMode(600, 500, 32);

    DxLib_Init();   // DXライブラリ初期化処理
    SetDrawScreen(DX_SCREEN_BACK);

    SetTransColor(182, 185, 184);
    Game_Mode = 0;
    FPS = 144;
    mFPS = 1000.f / FPS;
    ClearDrawScreen();
}

Game::Game_Main() {
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

        end = clock();
    }
}