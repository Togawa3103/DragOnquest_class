#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include "DxLib.h"
#include "Game.h"
#include "Player.h"
#include "MAP.h"
#include "Mode.h"
#include "Battle.h"
#include "Sound.h"
#include "NPC.h"


int Game::FPS = 144;
float Game::mFPS = 1000.f / FPS;
int Game::Game_Mode = 0;
clock_t Game::end;
clock_t Game::now;
double Game::looptime;
int Game::comand = -1;
int Game::select_magic=-1;
int Game::select_item = -1;
int old_comand=-1;
bool Game::Talk_now = false;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE); //ウインドウモード(TRUE)・フルスクリーンモード(FALSE)の変更(DXライブラリ)
    SetGraphMode(600, 500, 32); //画面モードの変更(画面の解像度、カラービット数)

    DxLib_Init();   // DXライブラリ初期化処理
    SetDrawScreen(DX_SCREEN_BACK); //描画先グラフィック領域の指定(DX_SCREEN_FRONT:表の画面　DX_SCREEN_BACK:裏の画面)
    
    SetTransColor(182, 185, 184); //グラフィックで透明色にする色をセット

    ClearDrawScreen(); //画面に描画されたものを消去する

    //Game game;
    //game.Game_Start();

    //スタート画面の表示
    /*if (game.Game_Start() == StartMenu_Start) {
        game.Initialize();
    }
    else {
        game.Load_Date();
    }*/
    //スタート画面の表示
    //game.Game_Start();
    Game::Game_Start();
    //ゲームメインループ
    //game.Game_Main(&game.player,&game.mode,&game.map);
    Game::Game_Main();

    WaitKey();      // キー入力待ち
    DxLib_End();    // DXライブラリ終了処理
    return 0;
}

Game::Game() {
    Initialize();
}

Game::~Game() {
}

void Game::Initialize() {
    //game->player = Player(); //gameのPlayerを初期化
    //game->map = MAP(); //gameのMAPを初期化
    //game->mode = Mode(); ////gameのModeを初期化
    end = clock(); //ゲーム開始の時間設定
}

void Game::Game_Start() {
    if (Game::Game_StartDraw() == StartMenu_Start) {
        Game::Start(); //はじめから
    }
    else {
        Game::Load_Date(); //つづきから
    }
}

void Game::Start() {
    //game->map.Initialize(); //マップの初期化
    //game->map.Load_MAP(game->map.MAP_Num); //マップデータの取得
    //game->map.Draw_FIELD(); //マップの表示
    //game->mode.Initialize(); //ゲームの状態を初期化
    MAP::MAP(); //マップの初期化
    MAP::Load_MAP(MAP::MAP_Num); //マップデータの取得
    MAP::Draw_FIELD(); //マップの表示
    Mode::Initialize(); //ゲームの状態を初期化
    end = clock(); //ゲーム開始の時間設定
}

//スタート画面の表示
int Game::Game_StartDraw() {
    unsigned int Comand_Cr1 = GetColor(255, 255, 255);
    unsigned int Comand_Cr2 = GetColor(0, 0, 0);
    int Select_Menu = 0;
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        GetHitKeyStateAll(Mode::keyState); //キーボード入力の取得

        //外枠の表示
        DrawBox(200, 370, 350, 500, Comand_Cr1, TRUE); 
        DrawBox(210, 380, 340, 490, Comand_Cr2, TRUE); 

        //選択肢の表示
        for (int i = 0; i < StartMenu_Max; i++) {
            if (Select_Menu == i) {
                DrawBox(215, 385 + 40 * i, 335, 425+40*i, Comand_Cr1, TRUE);
                DrawFormatString(220, 390+45*i, Comand_Cr2, start[i].startmenu_name);
            }
            else {
                DrawFormatString(220, 390 + 45 * i, Comand_Cr1, start[i].startmenu_name);
            }
        }

        //キー入力によって状態を変える
        if (Player::Player_Time == 0) {
            //Sキーを押した場合
            if (Mode::keyState[KEY_INPUT_S]) { 
                Select_Menu = (Select_Menu + 1) % (StartMenu_Max);
                Player::Player_Time = Player::Player_Time + Game::mFPS;
            }
            //Wキーを押した場合
            if (Mode::keyState[KEY_INPUT_W]) { 
                Select_Menu = (Select_Menu + StartMenu_Max - 1) % (StartMenu_Max);
                Player::Player_Time = Player::Player_Time + Game::mFPS;
            }

            //エンターキーを押した場合
            if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
                Player::Player_Time = Player::Player_Time + Game::mFPS;
                return Select_Menu;
            }

            //エスケープを押した場合
            if (Mode::keyState[KEY_INPUT_ESCAPE] && !Mode::old_ESCAPE_keyState) {

            }
        }

        //キーの入力後1フレームごとにmFPSを加算
        if (Player::Player_Time != 0) {
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        
        //0.3秒ごとに入力可能にする
        if (Player::Player_Time > 300) {
            Player::Player_Time = 0;
        }
        
        //前回のキーの状態を保持
        Mode::old_E_keyState = Mode::keyState[KEY_INPUT_E];
        Mode::old_RETURN_keyState = Mode::keyState[KEY_INPUT_RETURN];
        Mode::old_ESCAPE_keyState = Mode::keyState[KEY_INPUT_RETURN];

        //フレームの待機処理
        now = clock();
        looptime = now - end;
        if (looptime < mFPS) {
            Sleep(mFPS - looptime);
        }
        end = now;
    }
}

//メインループ
void Game::Game_Main() {
    //Initialize();
    Player::Player_Time = 0;
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
                if (CheckSoundMem(MAP::map_bgm[MAP::MAP_Num])) {
                    // StopSoundFile();
                    Sound::StopSound(MAP::map_bgm);
                }
                Battle::Initialize();
            }
            if (Battle::Battle_Now) {
                
                Battle::Draw_Battle();
                if (comand < 0 && Battle::Turn == 1) {
                    comand = Battle::Set_Comand();
                    if (comand == Comand_Run||comand==Comand_Fight) {
                        
                        Battle::Update_Player(comand);
                    }

                }
                else if (select_magic < 0 && comand == Comand_Magic && Battle::Turn == 1) {
                    select_magic = Battle::Select_Magic();
                    if (select_magic >= 0) {
                        
                        Battle::Update_Player(comand);
                    }
                }
                else if (select_item < 0&&comand==Comand_Item&&Battle::Turn==1) {
                    select_item = Battle::Select_Item();
                    if (select_item >= 0) {
                       
                       Battle::Update_Player(comand);
                    }
                }
                else  if(comand<0&&Battle::Turn==0){
                    comand=Battle::Enemy_AI();
                    
                    Battle::Update_Monster(comand);

                }
                else if (comand>=0) {
                    switch (comand) {
                    case Comand_Run:
                        Battle::Draw_Message(comand, Battle::Turn,Battle::canRun);
                        break;
                    case Comand_Fight:
                        //Battle::Update_Battle(comand);
                        Battle::Effect(Battle::Turn, comand, -1);
                        Battle::Draw_Message(comand, Battle::Turn);
                        //Battle::Turn_Swap();
                        break;
                    case Comand_Magic:
                        Battle::Effect(Battle::Turn, comand, select_magic);
                        Battle::Draw_Message(comand, Battle::Turn,select_magic);
                        break;
                    case Comand_Item:
                        
                        Battle::Effect(Battle::Turn, comand, Player::ItemBox[select_item]);
                        
                        Battle::Draw_Message(comand, Battle::Turn, Player::ItemBox[select_item], item[Player::ItemBox[select_item]].canuse);
                        break;
                    }
                    old_comand = comand;
                }
                
            }
            else {
                Battle::Finish_Battle(old_comand);
                
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
            }else if(Mode::Selected_Menu==MenuType_Talk) {
                if (!Talk_now) {
                    Mode::Menu_DireSelect(Mode::Selected_Menu);
                    NPC::Yes_No = 0;
                    NPC::finish_text = 0;
                }
                else if (Talk_now) {
                    switch (Mode::selected_NPC) {
                    case NPC_TYPE_INN:
                        if (npc[Mode::selected_NPC].text[NPC::Talk_Count] >= 0) {
                            NPC::Draw_INNTalk(Mode::selected_NPC);
                        }
                        else {
                            NPC::Draw_INN(Mode::selected_NPC);
                        }
                        break;
                    default:
                        if (npc[Mode::selected_NPC].text[NPC::Talk_Count] >= 0) {
                            NPC::Draw_Talk(Mode::selected_NPC);
                        }
                        else {
                            NPC::Draw_Question(Mode::selected_NPC);
                        }
                        break;
                    }
                }
            }
            else if (Mode::Selected_Menu == MenuType_Item) {
                if (!Mode::show_message) {
                    Mode::Item_Select();
                }
                else if(Mode::show_message){
                    Mode::Draw_Message(Player::ItemBox[Mode::Select_Item]);
                }
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
        Save_Data();
    }
}



void Game::Save_Data() {
    FILE* fp = fopen("savedata.dat","wb");
    //SaveData savedata = { Player::Player_Lv ,Player::now_player_status ,Player::Player_X ,Player::Player_Y ,MAP::MAP_Num ,MAP::Screen_X ,MAP::Screen_Y ,MAP::Move_Count_X ,MAP::Move_Count_Y,Player::ItemBox.size(),Player::ItemBox };
    SaveData savedata = { Player::Player_Lv ,Player::Player_X ,Player::Player_Y ,MAP::MAP_Num ,MAP::Screen_X ,MAP::Screen_Y ,MAP::Move_Count_X ,MAP::Move_Count_Y,Player::ItemBox.size()};
    /*fwrite(&(Player::Player_Lv), sizeof(int), 1, fp);
    fwrite(&(Player::now_player_status), sizeof(PLAYER_STATUS), 1,fp);
    fwrite(&Player::Player_X, sizeof(int), 1, fp);
    fwrite(&Player::Player_Y, sizeof(int), 1, fp);
    fwrite(&MAP::MAP_Num, sizeof(int), 1, fp);
    fwrite(&MAP::Screen_X, sizeof(int), 1, fp);
    fwrite(&MAP::Screen_Y, sizeof(int), 1, fp);
    fwrite(&MAP::Move_Count_X, sizeof(int), 1, fp);
    fwrite(&MAP::Move_Count_Y, sizeof(int), 1, fp);
    */
    fwrite(&savedata,sizeof(savedata),1,fp);
    fwrite(&Player::now_player_status, sizeof(int)*STATUS_MAX, 1, fp);
    fwrite(&Player::MagicBox[0], sizeof(Player::MagicBox[0]) * Player::MagicBox.size(), 1, fp);
    fwrite(&Player::ItemBox[0], sizeof(Player::ItemBox[0]) * Player::ItemBox.size(), 1, fp);
    fwrite(&MAP::Door_Open[0], sizeof(MAP::Door_Open[0]) * MAP::Door_Open.size(), 1, fp);
    fclose(fp);
}

void Game::Load_Date() {
    FILE* fp = fopen("savedata.dat", "rb");
    SaveData savedata;
    //savedata.ItemBox.reserve(10);
    Player player;
    MAP map;
    Mode mode;
    
    fread(&savedata,sizeof(savedata),1,fp);
    fread(&Player::now_player_status, sizeof(int) * STATUS_MAX, 1, fp);
    fread(&Player::MagicBox[0], sizeof(Player::MagicBox[0]) * Player::MagicBox.size(), 1, fp);
    Player::HP = Player::now_player_status.HP;
    Player::MP = Player::now_player_status.MP;
    fread(&Player::ItemBox[0], sizeof(&Player::ItemBox[0]) * Player::ItemBox.size(), 1, fp);
    fread(&MAP::Door_Open[0], sizeof(MAP::Door_Open[0]) * MAP::Door_Open.size(), 1, fp);
    fclose(fp);

    map.Initialize();
    mode.Initialize();
 
    Player::Player_Lv = savedata.Player_Lv;
   // Player::now_player_status = savedata.Player_Status;
    //Player::ItemBox = savedata.ItemBox;
    Player::Player_X = savedata.Player_X;
    Player::Player_Y = savedata.Player_Y;
    map.MAP_Num = savedata.MAP_Num;
    map.Screen_X = savedata.Screen_X;
    map.Screen_Y = savedata.Screen_Y;
    map.Move_Count_X = savedata.Move_Count_X;
    map.Move_Count_Y = savedata.Move_Count_Y;
    Player::ItemBox.resize(savedata.ItemBox_size);
    //Player::ItemBox = savedata.ItemBox;
    map.Load_MAP(map.MAP_Num);
    map.Draw_FIELD();

    end = clock();
}