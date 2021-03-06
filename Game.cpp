#define _CRT_SECURE_NO_WARNINGS
#ifdef GLOBAL_VALUE_DEFINE
#define GLOBAL
#else
#define GLOBAL extern
#endif
#include <windows.h>
#include "DxLib.h"
#include "Game.h"
#include "Player.h"
#include "MAP.h"
#include "Mode.h"
#include "Battle.h"

int Game::FPS = 144;
float Game::mFPS = 1000.f / FPS;
int Game::Game_Mode = 0;
clock_t Game::end;
clock_t Game::now;
double Game::looptime;
int Game::comand = -1;
int old_comand=-1;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE);
    SetGraphMode(600, 500, 32);

    DxLib_Init();   // DXライブラリ初期化処理
    SetDrawScreen(DX_SCREEN_BACK);

    SetTransColor(182, 185, 184);
    
    ClearDrawScreen();
    Game game;
    game.Initialize();
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
    Player player;
    MAP map;
    Mode mode;
    map.Initialize();
    map.Load_MAP(map.MAP_Num);
    map.Draw_FIELD();
    mode.Initialize();
    end = clock();
    
}

void Game::Game_Main() {
    Initialize();
    
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        Player::Update_Status(Player::Player_Lv);
        GetHitKeyStateAll(Mode::keyState);
        //ScreenFlip();
        //ClearDrawScreen();
        if (Mode::GameMode==GameMode_FIELD) {
            Mode::Field_Mode();
        }
        else if (Mode::GameMode==GameMode_BATTLE) {
            
            if (Battle::Monster_Num < 0) {
                Battle::Initialize();
            }
            if (Battle::Battle_Now) {
                Battle::Draw_Battle();
                if (comand < 0 && Battle::Turn == 1) {
                    comand = Battle::Set_Comand();
                    if (comand>=0) {
                        Battle::Update_Player(comand);
                    }
                }
                else  if(comand<0&&Battle::Turn==0){
                    comand=Battle::Enemy_AI();
                    
                    Battle::Update_Monster(comand);

                }
                else if (comand>=0) {  
                    //Battle::Update_Battle(comand);
                    Battle::Draw_Message(comand, Battle::Turn);
                    //Battle::Turn_Swap();
                    old_comand = comand;
                }
                if (!Battle::Check_Battle_End()) {
                    Battle::Battle_Now = false;
                }
            }
            else {
                Battle::Finish_Battle(old_comand);
                Battle::Monster_Num = -1;
            }
        }
        else if (Mode::GameMode==GameMode_MENU) {
            MAP::Draw_FIELD();
            if (Mode::Selected_Menu < 0) {
                Mode::Menu_Mode();
            }
            else if (Mode::Selected_Menu == MenuType_DOOR) {
                Mode::Menu_DireSelect(Mode::Selected_Menu);
            }
            else if (Mode::Selected_Menu==MenuType_SEARCH) {
                Mode::Menu_DireSelect(Mode::Selected_Menu);
            }
            else if (Mode::Selected_Menu==MenuType_Item) {
                Mode::Item_Select();
            }
            else if (Mode::Selected_Menu==MenuType_STATUS) {
                Mode::Status_Show();
            }
        }
        Mode::old_E_keyState = Mode::keyState[KEY_INPUT_E];
        Mode::old_RETURN_keyState = Mode::keyState[KEY_INPUT_RETURN];
        Mode::old_ESCAPE_keyState = Mode::keyState[KEY_INPUT_RETURN];
        
        now = clock();
        looptime = now -end;
        if (looptime<mFPS) {
            Sleep(mFPS-looptime);
        }
        end = now;
    }
}