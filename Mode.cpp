#include "DxLib.h"
#include "Mode.h"
#include "Game.h"
#include "Player.h"
#include "Sound.h"
#include "MAP.h"
#include "Enum.h"
#include "Battle.h"
#include "NPC.h"
unsigned static int TextBox_Cr1 = GetColor(255, 255, 255);
unsigned static int TextBox_Cr2 = GetColor(0, 0, 0);

int heal;

int Mode::GameMode;
char Mode::keyState[256];
char Mode::old_E_keyState;
char Mode::old_RETURN_keyState;
char Mode::old_ESCAPE_keyState;
int Mode::Select_Menu_Num;
int Mode::Select_Dire_Num;
int Mode::Select_Item;
int Mode::Selected_Menu;
int Mode::selected_NPC;
bool Mode::show_message;

//初期化
void Mode::Initialize() {
    heal = 0;
    Mode::GameMode=0;
    Mode::old_E_keyState=-1;
    Mode::old_RETURN_keyState=-1;
    Mode::old_ESCAPE_keyState=-1;
    Mode::Select_Menu_Num=0;
    Mode::Select_Dire_Num=0;
    Mode::Select_Item=0;
    Mode::Selected_Menu=-1;
    show_message = false;
}

//フィールドモード
void Mode::Field_Mode() {
    Player::PlayerCount = (Player::PlayerCount + 1) % Game::FPS;
    int Next_X = Player::Player_X;
    int Next_Y = Player::Player_Y;
    if (Player::Player_Time == 0) {

        if (keyState[KEY_INPUT_W] && !keyState[KEY_INPUT_S]) {

            if (MAP::canmove[Player::Player_Y - 1][Player::Player_X]) {
                Next_Y = Player::Player_Y - 1;
            }
        }
        if (keyState[KEY_INPUT_S] && !keyState[KEY_INPUT_W]) {
            if (MAP::canmove[Player::Player_Y + 1][Player::Player_X]) {
                Next_Y = Player::Player_Y + 1;
            }
        }
        if (keyState[KEY_INPUT_A] && !keyState[KEY_INPUT_D]) {
            if (MAP::canmove[Player::Player_Y][Player::Player_X - 1]) {
                Next_X = Player::Player_X - 1;
            }
        }
        if (keyState[KEY_INPUT_D] && !keyState[KEY_INPUT_A]) {
            if (MAP::canmove[Player::Player_Y][Player::Player_X + 1]) {
                Next_X = Player::Player_X + 1;
            }
        }

        if (MAP::canmove[Next_Y][Next_X]) {
            Player::old_Player_X = Player::Player_X;
            Player::old_Player_Y = Player::Player_Y;
            Player::Player_X = Next_X;
            Player::Player_Y = Next_Y;
            //Screen_x = Player_X;
            //Screen_y = Player_Y;
        }

        if (keyState[KEY_INPUT_E] && !old_E_keyState) {
            GameMode = GameMode_MENU;
            Player::Player_Time = Player::Player_Time + Game::mFPS;

        }


        if (Player::Player_X != Player::old_Player_X || Player::Player_Y != Player::old_Player_Y) {
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
    }

    MAP::Draw_FIELD();

    
   
    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 300) {
        if (MAP::map[Player::Player_Y][Player::Player_X] == CELL_TYPE_STEPS && (Player::Player_X != Player::old_Player_X || Player::Player_Y != Player::old_Player_Y)) {
            for (int i = 0; i < map_data[MAP::MAP_Num].map_info.size(); i++) {
                if (Player::Player_X == map_data[MAP::MAP_Num].map_info[i].Start_X && Player::Player_Y == map_data[MAP::MAP_Num].map_info[i].Start_Y) {
                    Sound::StopSound(MAP::map_bgm);
                    MAP::MAP_Num = map_data[MAP::MAP_Num].map_info[i].toMap_Num;

                    MAP::File_Name = map_data[MAP::MAP_Num].Map_Name;
                    MAP::Load_MAP(MAP::MAP_Num);



                    Player::Player_X = map_data[MAP::MAP_Num].map_info[i].Start_X;
                    Player::Player_Y = map_data[MAP::MAP_Num].map_info[i].Start_Y;
                    Player::old_Player_X = Player::Player_X;
                    Player::old_Player_Y = Player::Player_Y;
                    if (Player::Player_X > 8) {
                        MAP::Move_Count_X = Player::Player_X - 6;
                    }
                    else {
                        MAP::Move_Count_X = 0;
                    }
                    if (Player::Player_Y > 7) {
                        MAP::Move_Count_Y = Player::Player_Y - 4;
                    }
                    else {
                        MAP::Move_Count_Y = 0;
                    }
                    MAP::Screen_X = 5;
                    MAP::Screen_Y = 5;
                }
            }
        }
        
        if (Player::Player_X != Player::old_Player_X || Player::Player_Y != Player::old_Player_Y) {
            //Player::Exp++;
            Mode::GameMode = Battle::Start_Battle(Player::PlayerCount);
            if (Mode::GameMode == GameMode_BATTLE) {
                Battle::Battle_Now = true;
            }
        }
        Player::old_Player_X = Player::Player_X;
        Player::old_Player_Y = Player::Player_Y;
        Player::Player_Time = 0;
    }
}

//メニューモード
void Mode::Menu_Mode() {
    //int Player_Time = Player::Player_Time;
    
    
    unsigned int Menu_Cr1 = GetColor(255, 255, 255);
    unsigned int Menu_Cr2 = GetColor(0, 0, 0);
    DrawBox(450, 10, 590, 200, Menu_Cr1, TRUE);
    DrawBox(460, 20, 580, 190, Menu_Cr2, TRUE);
    if (Player::Player_Time == 0) {
        if (keyState[KEY_INPUT_S]) {
            Select_Menu_Num = (Select_Menu_Num + 1) % (MenuType_MAX);
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (keyState[KEY_INPUT_W]) {
            Select_Menu_Num = (Select_Menu_Num + MenuType_MAX - 1) % (MenuType_MAX);
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (keyState[KEY_INPUT_E] && !old_E_keyState) {
            GameMode = GameMode_FIELD;
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }


        if (keyState[KEY_INPUT_RETURN] && !old_RETURN_keyState) {
            Selected_Menu = Select_Menu_Num;
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (keyState[KEY_INPUT_ESCAPE] && !old_ESCAPE_keyState) {
            Selected_Menu = -1;
            Select_Menu_Num = 0;
            GameMode = GameMode_FIELD;
        }

    }
    DrawBox(450, 10, 590, 250, Menu_Cr1, TRUE);
    DrawBox(460, 20, 580, 240, Menu_Cr2, TRUE);
    for (int i = 0; i < MenuType_MAX; i++) {
        if (Select_Menu_Num == i) {
            if (i == MenuType_SEARCH) {
                DrawBox(menu[i].x - 10, menu[i].y - 10, menu[i].x + 80, menu[i].y + 20, Menu_Cr1, TRUE);
                DrawFormatString(menu[i].x, menu[i].y, Menu_Cr2, menu[i].name);
            }
            else {
                DrawBox(menu[i].x - 10, menu[i].y - 10, menu[i].x + 60, menu[i].y + 20, Menu_Cr1, TRUE);
                DrawFormatString(menu[i].x, menu[i].y, Menu_Cr2, menu[i].name);
            }

        }
        else {
            DrawFormatString(menu[i].x, menu[i].y, Menu_Cr1, menu[i].name);
        }
    }

    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 200) {
        Player::Player_Time = 0;
    }
    
}

//「とびら」、「しらべる」、「はなす」コマンドの方向選択
void Mode::Menu_DireSelect(int Selected_Menu_Num) {
    bool haveKey = Player::haveKey;
    int Player_Time = Player::Player_Time;
    unsigned int Menu_Cr1 = GetColor(255, 255, 255);
    unsigned int Menu_Cr2 = GetColor(0, 0, 0);
    int Select_Menu = Selected_Menu_Num;


    switch (Select_Menu)
    {
    case MenuType_DOOR:
        if (Player_Time == 0) {

            if (keyState[KEY_INPUT_W]) {
                Select_Dire_Num = Dire_N;
            }
            if (keyState[KEY_INPUT_D]) {
                Select_Dire_Num = Dire_E;
            }
            if (keyState[KEY_INPUT_S]) {
                Select_Dire_Num = Dire_S;
            }
            if (keyState[KEY_INPUT_A]) {
                Select_Dire_Num = Dire_W;
            }
            if (keyState[KEY_INPUT_ESCAPE] && !old_ESCAPE_keyState) {
                Selected_Menu = -1;
                Select_Dire_Num = 0;

            }


            if (keyState[KEY_INPUT_RETURN] && !old_RETURN_keyState) {
                Selected_Menu = FALSE;
                Select_Menu_Num = 0;
                Selected_Menu = -1;
                if (haveKey) {
                    switch (Select_Dire_Num)
                    {
                    case Dire_N:
                        if (MAP::map[Player::Player_Y - 1][Player::Player_X] == CELL_TYPE_DOOR) {
                            for (int i = 0; i < Player::ItemBox.size(); i++) {
                                if (Player::ItemBox[i] == Item_Key) {
                                    Player::ItemBox.erase(Player::ItemBox.begin() + i);
                                    break;
                                }
                            }
                            MAP::canmove[Player::Player_Y - 1][Player::Player_X] = TRUE;
                            MAP::map[Player::Player_Y - 1][Player::Player_X] = MAP::map[Player::Player_Y][Player::Player_X];
                            for (int j = 0; j < map_data[MAP::MAP_Num].Door.size(); j++) {
                                if (map_data[MAP::MAP_Num].Door[j].Door_X ==Player::Player_X&& map_data[MAP::MAP_Num].Door[j].Door_Y==Player::Player_Y-1) {
                                    MAP::Door_Open[map_data[MAP::MAP_Num].Door[j].Door_Num] = 1;
                                }
                            }
                            GameMode = GameMode_FIELD;

                        }
                        else {
                            GameMode = GameMode_FIELD;
                            break;
                        }

                    case Dire_E:
                        if (MAP::map[Player::Player_Y][Player::Player_X + 1] == CELL_TYPE_DOOR) {
                            for (int i = 0; i < Player::ItemBox.size(); i++) {
                                if (Player::ItemBox[i] == Item_Key) {
                                    Player::ItemBox.erase(Player::ItemBox.begin() + i);
                                    break;
                                }
                            }
                            MAP::canmove[Player::Player_Y][Player::Player_X + 1] = TRUE;
                            MAP::map[Player::Player_Y][Player::Player_X + 1] = MAP::map[Player::Player_Y][Player::Player_X];
                            for (int j = 0; j < map_data[MAP::MAP_Num].Door.size(); j++) {
                                if (map_data[MAP::MAP_Num].Door[j].Door_X == Player::Player_X +1
                                    && map_data[MAP::MAP_Num].Door[j].Door_Y == Player::Player_Y) {
                                    MAP::Door_Open[map_data[MAP::MAP_Num].Door[j].Door_Num] = 1;
                                }
                            }
                            GameMode = GameMode_FIELD;
                        }
                        else {
                            GameMode = GameMode_FIELD;
                            break;
                        }

                    case Dire_S:
                        if (MAP::map[Player::Player_Y + 1][Player::Player_X] == CELL_TYPE_DOOR) {
                            for (int i = 0; i < Player::ItemBox.size(); i++) {
                                if (Player::ItemBox[i] == Item_Key) {
                                    Player::ItemBox.erase(Player::ItemBox.begin() + i);
                                    break;
                                }
                            }
                            MAP::canmove[Player::Player_Y + 1][Player::Player_X] = TRUE;
                            MAP::map[Player::Player_Y + 1][Player::Player_X] = MAP::map[Player::Player_Y][Player::Player_X];
                            for (int j = 0; j < map_data[MAP::MAP_Num].Door.size(); j++) {
                                if (map_data[MAP::MAP_Num].Door[j].Door_X == Player::Player_X 
                                    && map_data[MAP::MAP_Num].Door[j].Door_Y == Player::Player_Y+1) {
                                    MAP::Door_Open[map_data[MAP::MAP_Num].Door[j].Door_Num] =1;
                                }
                            }
                            GameMode = GameMode_FIELD;
                        }
                        else {
                            GameMode = GameMode_FIELD;
                            break;
                        }

                    case Dire_W:
                        if (MAP::map[Player::Player_Y][Player::Player_X - 1] == CELL_TYPE_DOOR) {
                            for (int i = 0; i < Player::ItemBox.size(); i++) {
                                if (Player::ItemBox[i] == Item_Key) {
                                    Player::ItemBox.erase(Player::ItemBox.begin() + i);
                                    break;
                                }
                            }
                            MAP::canmove[Player::Player_Y][Player::Player_X - 1] = TRUE;
                            MAP::map[Player::Player_Y][Player::Player_X - 1] = MAP::map[Player::Player_Y][Player::Player_X];
                            for (int j = 0; j < map_data[MAP::MAP_Num].Door.size(); j++) {
                                if (map_data[MAP::MAP_Num].Door[j].Door_X == Player::Player_X-1
                                    && map_data[MAP::MAP_Num].Door[j].Door_Y == Player::Player_Y) {
                                    MAP::Door_Open[map_data[MAP::MAP_Num].Door[j].Door_Num] = 1;
                                }
                            }
                            GameMode = GameMode_FIELD;
                        }
                        else {
                            GameMode = GameMode_FIELD;
                            break;
                        }

                    }
                    Select_Dire_Num = 0;
                }
                else {
                    Select_Dire_Num = 0;
                    GameMode = GameMode_FIELD;
                }
            }
        }



        break;

    case MenuType_SEARCH:
        if (Player_Time == 0) {

            if (keyState[KEY_INPUT_W]) {
                Select_Dire_Num = Dire_N;
            }
            if (keyState[KEY_INPUT_D]) {
                Select_Dire_Num = Dire_E;
            }
            if (keyState[KEY_INPUT_S]) {
                Select_Dire_Num = Dire_S;
            }
            if (keyState[KEY_INPUT_A]) {
                Select_Dire_Num = Dire_W;
            }
            if (keyState[KEY_INPUT_ESCAPE] && !old_ESCAPE_keyState) {
                Selected_Menu = -1;
                Select_Dire_Num = 0;

            }


            if (keyState[KEY_INPUT_RETURN] && !old_RETURN_keyState) {
                Selected_Menu = FALSE;
                Select_Menu_Num = 0;
                Selected_Menu = -1;

                switch (Select_Dire_Num)
                {
                case Dire_N:
                    if (MAP::map[Player::Player_Y - 1][Player::Player_X] == CELL_TYPE_TREASURE) {
                        for (int i = 0; i < TRESURE_MAX; i++) {
                            if (MAP::File_Name == tresure[i].map_name && Player::Player_X == tresure[i].x && Player::Player_Y - 1 == tresure[i].y) {
                                Player::ItemBox.push_back(tresure[i].ItemNum);
                                GameMode = GameMode_FIELD;
                            }
                        }

                    }
                    else {
                        GameMode = GameMode_FIELD;
                        break;
                    }

                case Dire_E:
                    if (MAP::map[Player::Player_Y][Player::Player_X + 1] == CELL_TYPE_TREASURE) {
                        for (int i = 0; i < TRESURE_MAX; i++) {
                            if (MAP::File_Name == tresure[i].map_name && Player::Player_X + 1 == tresure[i].x && Player::Player_Y == tresure[i].y) {
                                Player::ItemBox.push_back(tresure[i].ItemNum);
                                GameMode = GameMode_FIELD;
                            }
                        }
                    }
                    else {
                        GameMode = GameMode_FIELD;
                        break;
                    }

                case Dire_S:
                    if (MAP::map[Player::Player_Y + 1][Player::Player_X] == CELL_TYPE_TREASURE) {
                        for (int i = 0; i < TRESURE_MAX; i++) {
                            if (MAP::File_Name == tresure[i].map_name && Player::Player_X == tresure[i].x && Player::Player_Y + 1 == tresure[i].y) {
                                Player::ItemBox.push_back(tresure[i].ItemNum);
                                GameMode = GameMode_FIELD;
                            }
                        }
                    }
                    else {
                        GameMode = GameMode_FIELD;
                        break;
                    }

                case Dire_W:
                    if (MAP::map[Player::Player_Y][Player::Player_X - 1] == CELL_TYPE_TREASURE) {
                        for (int i = 0; i < TRESURE_MAX; i++) {
                            if (MAP::File_Name == tresure[i].map_name && Player::Player_X - 1 == tresure[i].x && Player::Player_Y == tresure[i].y) {
                                Player::ItemBox.push_back(tresure[i].ItemNum);
                                GameMode = GameMode_FIELD;
                            }
                        }
                    }
                    else {
                        GameMode = GameMode_FIELD;
                        break;
                    }

                }
                Select_Dire_Num = 0;
            }
        }
        break;
    case MenuType_Talk:
        if (Player_Time == 0) {

            if (keyState[KEY_INPUT_W]) {
                Select_Dire_Num = Dire_N;
            }
            if (keyState[KEY_INPUT_D]) {
                Select_Dire_Num = Dire_E;
            }
            if (keyState[KEY_INPUT_S]) {
                Select_Dire_Num = Dire_S;
            }
            if (keyState[KEY_INPUT_A]) {
                Select_Dire_Num = Dire_W;
            }
            if (keyState[KEY_INPUT_ESCAPE] && !old_ESCAPE_keyState) {
                Selected_Menu = -1;
                Select_Dire_Num = 0;

            }


            if (keyState[KEY_INPUT_RETURN] && !old_RETURN_keyState) {
                Selected_Menu = FALSE;
                Select_Menu_Num = 0;
                

                switch (Select_Dire_Num)
                {
                case Dire_N:
                    if (!MAP::canmove[Player::Player_Y - 1][Player::Player_X]) {
                        for (int i = 0; i < NPC::npc_num.size();i++) {
                            if (Player::Player_Y - 1 == npc[NPC::npc_num[i]].y && Player::Player_X == npc[NPC::npc_num[i]].x) {
                                Game::Talk_now = true;
                                selected_NPC = NPC::npc_num[i];
                                NPC::Talk_Count = 0;
                            }
                        }

                    }
                    else {
                        GameMode = GameMode_FIELD;
                        Selected_Menu = -1;
                        break;
                    }
                    break;
                case Dire_E:
                    if (!MAP::canmove[Player::Player_Y][Player::Player_X+1]) {
                        for (int i = 0; i < NPC::npc_num.size(); i++) {
                            if (Player::Player_Y== npc[NPC::npc_num[i]].y && Player::Player_X+1 == npc[NPC::npc_num[i]].x) {
                                Game::Talk_now = true;
                                selected_NPC = NPC::npc_num[i];
                                NPC::Talk_Count = 0;
                            }
                        }

                    }
                    else {
                        Selected_Menu = -1;
                        GameMode = GameMode_FIELD;
                        break;
                    }
                    break;
                case Dire_S:
                    if (!MAP::canmove[Player::Player_Y + 1][Player::Player_X]) {
                        for (int i = 0; i < NPC::npc_num.size(); i++) {
                            if (Player::Player_Y + 1 == npc[NPC::npc_num[i]].y && Player::Player_X == npc[NPC::npc_num[i]].x) {
                                Game::Talk_now = true;
                                selected_NPC = NPC::npc_num[i];
                                NPC::Talk_Count = 0;
                            }
                        }

                    }
                    else {
                        GameMode = GameMode_FIELD;
                        Selected_Menu = -1;
                        break;
                    }
                    break;

                case Dire_W:
                    if (!MAP::canmove[Player::Player_Y ][Player::Player_X-1]) {
                        for (int i = 0; i < NPC::npc_num.size(); i++) {
                            if (Player::Player_Y  == npc[NPC::npc_num[i]].y && Player::Player_X-1 == npc[NPC::npc_num[i]].x) {
                                Game::Talk_now = true;
                                selected_NPC = NPC::npc_num[i];
                                NPC::Talk_Count = 0;
                            }
                        }

                    }
                    else {
                        GameMode = GameMode_FIELD;
                        Selected_Menu = -1;
                        break;
                    }

                }
                Select_Dire_Num = 0;
            }
        }
        break;

    }


    DrawBox(450, 260, 590, 410, Menu_Cr1, TRUE);
    DrawBox(460, 270, 580, 400, Menu_Cr2, TRUE);
    for (int i = 0; i < Dire_MAX; i++) {
        if (i == Select_Dire_Num) {
            DrawBox(dire[i].x - 10, dire[i].y - 10, dire[i].x + 30, dire[i].y + 20, Menu_Cr1, TRUE);
            DrawFormatString(dire[i].x, dire[i].y, Menu_Cr2, dire[i].Dire);
        }
        else {
            DrawFormatString(dire[i].x, dire[i].y, Menu_Cr1, dire[i].Dire);
        }
    }
    DrawBox(450, 10, 590, 250, Menu_Cr1, TRUE);
    DrawBox(460, 20, 580, 240, Menu_Cr2, TRUE);
    for (int i = 0; i < MenuType_MAX; i++) {
        if (Select_Menu_Num == i) {
            DrawBox(menu[i].x - 10, menu[i].y - 10, menu[i].x + 80, menu[i].y + 20, Menu_Cr1, TRUE);
            DrawFormatString(menu[i].x, menu[i].y, Menu_Cr2, menu[i].name);
        }
        else {
            DrawFormatString(menu[i].x, menu[i].y, Menu_Cr1, menu[i].name);
        }
    }
    if (Player_Time != 0) {
        Player_Time = Player_Time + Game::mFPS;
    }
    if (Player_Time > 200) {
        Player_Time = 0;
    }
    Player::Player_Time = Player_Time;



}

//アイテムの選択
void Mode::Item_Select() {
    unsigned int Menu_Cr1 = GetColor(255, 255, 255);
    unsigned int Menu_Cr2 = GetColor(0, 0, 0);
    
    if (Player::Player_Time == 0) {

        if (keyState[KEY_INPUT_S]) {
            Select_Item = (Select_Item + 1) % (Player::ItemBox.size());
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }

        if (keyState[KEY_INPUT_W]) {
            Select_Item = (Select_Item + Player::ItemBox.size() - 1) % (Player::ItemBox.size());
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (keyState[KEY_INPUT_RETURN] && !old_RETURN_keyState) {
            if (Player::ItemBox.size()>0) {
                if (item[Player::ItemBox[Select_Item]].canuse) {
                    Use_Item(Player::ItemBox[Select_Item]);
                    show_message = true;
                }
                else if (item[Player::ItemBox[Select_Item]].canEquip) {
                    Use_Item(Player::ItemBox[Select_Item]);
                    show_message = true;
                }
                else {
                    show_message = true;
                }
            }
            else {
                Selected_Menu = -1;
                Select_Menu_Num = 0;
                GameMode = GameMode_FIELD;
            }
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (keyState[KEY_INPUT_ESCAPE]) {
            Selected_Menu = -1;
            Select_Menu_Num = 0;
            GameMode = GameMode_FIELD;
        }
        old_RETURN_keyState = keyState[KEY_INPUT_RETURN];

    }
    DrawBox(200, 50, 400, 450, Menu_Cr1, TRUE);
    DrawBox(210, 60, 390, 440, Menu_Cr2, TRUE);
    for (int i = 0; i < Player::ItemBox.size(); i++) {
        if (Select_Item == i) {
            DrawBox(215, 65 + i * 30 - 5, 385, 65 + i * 30 + 25, Menu_Cr1, TRUE);
            DrawFormatString(220, 65 + i * 30, Menu_Cr2, item[Player::ItemBox[i]].Item_name);
        }
        else {
            DrawFormatString(220, 65 + i * 30, Menu_Cr1, item[Player::ItemBox[i]].Item_name);
        }
    }
    DrawBox(450, 10, 590, 250, Menu_Cr1, TRUE);
    DrawBox(460, 20, 580, 240, Menu_Cr2, TRUE);
    for (int i = 0; i < MenuType_MAX; i++) {
        if (Select_Menu_Num == i) {
            DrawBox(menu[i].x - 10, menu[i].y - 10, menu[i].x + 60, menu[i].y + 20, Menu_Cr1, TRUE);
            DrawFormatString(menu[i].x, menu[i].y, Menu_Cr2, menu[i].name);
        }
        else {
            DrawFormatString(menu[i].x, menu[i].y, Menu_Cr1, menu[i].name);
        }
    }
    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 200) {
        Player::Player_Time = 0;
    }

}

//「つよさ」コマンド
void Mode::Status_Show() {

    unsigned int Menu_Cr1 = GetColor(255, 255, 255);
    unsigned int Menu_Cr2 = GetColor(0, 0, 0);
    old_RETURN_keyState = keyState[KEY_INPUT_RETURN];

    if (Player::Player_Time == 0) {

        if (keyState[KEY_INPUT_RETURN] && !old_RETURN_keyState) {
            Selected_Menu = -1;
            Select_Menu_Num = 0;
            GameMode = GameMode_FIELD;
        }
        if (keyState[KEY_INPUT_ESCAPE]) {
            Selected_Menu = -1;
            Select_Menu_Num = 0;
            GameMode = GameMode_FIELD;
        }
        old_RETURN_keyState = keyState[KEY_INPUT_RETURN];

    }
    DrawBox(200, 50, 400, 400, Menu_Cr1, TRUE);
    DrawBox(210, 60, 390, 390, Menu_Cr2, TRUE);
    DrawBox(50, 50, 150, 300, Menu_Cr1, TRUE);
    DrawBox(60, 60, 140, 290, Menu_Cr2, TRUE);
    int* p;
    p = &(Player::now_player_status.MAXHP);
    for (int i = 0; i < STATUS_MAX; i++) {
        DrawFormatString(220, 65 + i * 30, Menu_Cr1, status[i].status_name);
        DrawFormatString(350, 65 + i * 30, Menu_Cr1, "%d", *(p + i));
    }
    for (int i = 0; i < Player::MagicBox.size();i++) {
        DrawFormatString(70,65+i*30,Menu_Cr1,magic[Player::MagicBox[i]].magic_name);
    }

    /*
    DrawFormatString(350, 65 + 0 * 30, Menu_Cr1, "%d", player_status[Player_Lv - 1].MAXHP);
    DrawFormatString(350, 65 + 1 * 30, Menu_Cr1, "%d", player_status[Player_Lv-1].HP);
    DrawFormatString(350, 65 + 2 * 30, Menu_Cr1, "%d", player_status[Player_Lv - 1].MAXMP);
    DrawFormatString(350, 65 + 3 * 30, Menu_Cr1, "%d", player_status[Player_Lv-1].MP);
    DrawFormatString(350, 65 + 4 * 30, Menu_Cr1, "%d", player_status[Player_Lv - 1].ATTACK);
    DrawFormatString(350, 65 + 5 * 30, Menu_Cr1, "%d", player_status[Player_Lv - 1].DEFENSE);
    DrawFormatString(350, 65 + 6 * 30, Menu_Cr1, "%d", player_status[Player_Lv - 1].SPEED);
    DrawFormatString(350, 65 + 7 * 30, Menu_Cr1, "%d", player_status[Player_Lv - 1].WISE);
    DrawFormatString(350, 65 + 8 * 30, Menu_Cr1, "%d", player_status[Player_Lv - 1].MAGICDEF);
    DrawFormatString(350, 65 + 9 * 30, Menu_Cr1, "%d", player_status[Player_Lv-1].GOLD);
    DrawFormatString(350, 65 + 10 * 30, Menu_Cr1, "%d", player_status[Player_Lv-1].EXP);
    */
    DrawBox(450, 10, 590, 250, Menu_Cr1, TRUE);
    DrawBox(460, 20, 580, 240, Menu_Cr2, TRUE);
    for (int i = 0; i < MenuType_MAX; i++) {
        if (Select_Menu_Num == i) {
            DrawBox(menu[i].x - 10, menu[i].y - 10, menu[i].x + 60, menu[i].y + 20, Menu_Cr1, TRUE);
            DrawFormatString(menu[i].x, menu[i].y, Menu_Cr2, menu[i].name);
        }
        else {
            DrawFormatString(menu[i].x, menu[i].y, Menu_Cr1, menu[i].name);
        }
    }
    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 200) {
        Player::Player_Time = 0;
    }
}

//「どうぐ」コマンドで使うを選択した場合
void Mode::Use_Item(int item_num) {
    switch (item_num) {
    case Item_Herb:
        if (Player::now_player_status.MAXHP>=Player::HP + 30) {
            Player::HP = Player::HP + 30;
            heal = 30;
        }
        else {
            heal = Player::now_player_status.MAXHP - Player::HP;
            Player::HP = Player::now_player_status.MAXHP;
        }
        break;
    case Item_CupperSword:
        Equip(Item_CupperSword);
        break;
    }
}

//「どうぐ」コマンドで装備できるものを選択した場合の装備処理
void Mode::Equip(int item_num) {
    if (Player::EquipField[item[item_num].place]==-1) {
        Player::EquipField[item[item_num].place] = item_num;
        int* p=&Player::now_player_status.HP;
        *(p + item[item_num].status) += item[item_num].power;
    }
}

//アイテム使用時のメッセージ表示
void Mode::Draw_Message(int item_num) {
    if (Player::Player_Time == 0) {
        if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
            heal = 0;
            Player::ItemBox.erase(Player::ItemBox.begin() + Select_Item);
            Mode::GameMode = GameMode_FIELD;
            Mode::Selected_Menu = -1;
            Mode::Select_Menu_Num = 0;
            Mode::Select_Item = 0;
            Mode::show_message = false;
        }
    }
    if (item[item_num].canuse) {
        DrawBox(100, 370, 500, 500, TextBox_Cr1, TRUE);
        DrawBox(110, 380, 490, 490, TextBox_Cr2, TRUE);
        DrawFormatString(120, 385, TextBox_Cr1, "ゆうしゃは%dかいふくした",heal);
    }
    else {
        DrawBox(100, 370, 500, 500, TextBox_Cr1, TRUE);
        DrawBox(110, 380, 490, 490, TextBox_Cr2, TRUE);
        DrawFormatString(120, 385, TextBox_Cr1, "このアイテムはつかえない");
    }
    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 200) {
        Player::Player_Time = 0;
    }
}

//歩くエフェクト
static int k = 0;
void Mode::Walk_Effect(int x, int y) {
 //   if (Player::Player_X != Player::old_Player_X|| Player::old_Player_Y != Player::old_Player_Y) {
        
        for (int i = 0; i < VIEW_RANGE_HEIGHT; i++) {
            for (int j = 0; j < VIEW_RANGE_WIDHT; j++) {
                DrawExtendGraph(j * 50, i * 50, j * 50 + 50, i * 50 + 50, 
                    graphDescs[MAP::map[i + MAP::Move_Count_Y][j + MAP::Move_Count_X]].Graph_Handle, TRUE);
            }
        }

       /* if (Player::PlayerCount % 2 == 0 && Player::Player_Time != 0) {
            DrawExtendGraph((Player::old_Player_X - MAP::Move_Count_X) * 50 + (k) * (Player::Player_X - Player::old_Player_X),
                (Player::old_Player_Y - MAP::Move_Count_Y) * 50 + (k) * (Player::Player_Y - Player::old_Player_Y),
                (Player::old_Player_X - MAP::Move_Count_X) * 50 + 50 + (k) * (Player::Player_X - Player::old_Player_X),
                (Player::old_Player_Y - MAP::Move_Count_Y) * 50 + 50 + (k) * (Player::Player_Y - Player::old_Player_Y),
                graphDescs[GRAPH_TYPE_PLAYER].Graph_Handle, TRUE);
        }
        else if (Player::PlayerCount % 2 == 1 && Player::Player_Time != 0) {
            DrawExtendGraph((Player::old_Player_X - MAP::Move_Count_X) * 50 + (k) * (Player::Player_X - Player::old_Player_X),
                (Player::old_Player_Y - MAP::Move_Count_Y) * 50 + (k) * (Player::old_Player_Y - Player::old_Player_Y),
                (Player::old_Player_X - MAP::Move_Count_X) * 50 + 50 + (k) * (Player::Player_X - Player::old_Player_X),
                (Player::old_Player_Y - MAP::Move_Count_Y) * 50 + 50 + (k) * (Player::Player_Y - Player::old_Player_Y),
                graphDescs[GRAPH_TYPE_PLAYER2].Graph_Handle, TRUE);
        }
        if (Player::PlayerCount / (Game::FPS / 2) > 0 && Player::Player_Time == 0) {
            DrawExtendGraph((Player::Player_X - MAP::Move_Count_X) * 50, (Player::Player_Y - MAP::Move_Count_Y) * 50, (Player::Player_X - MAP::Move_Count_X) * 50 + 50, (Player::Player_Y - MAP::Move_Count_Y) * 50 + 50, graphDescs[GRAPH_TYPE_PLAYER].Graph_Handle, TRUE);
        }
        else if (!(Player::PlayerCount / (Game::FPS / 2) > 0) && Player::Player_Time == 0) {
            DrawExtendGraph((Player::Player_X - MAP::Move_Count_X) * 50, (Player::Player_Y - MAP::Move_Count_Y) * 50, (Player::Player_X - MAP::Move_Count_X) * 50 + 50, (Player::Player_Y - MAP::Move_Count_Y) * 50 + 50, graphDescs[GRAPH_TYPE_PLAYER2].Graph_Handle, TRUE);
        }*/
        if (Player::PlayerCount / (Game::FPS / 2) > 0) {
            DrawExtendGraph((Player::old_Player_X - MAP::Move_Count_X) * 50 + (k) * (Player::Player_X - Player::old_Player_X),
                (Player::old_Player_Y - MAP::Move_Count_Y) * 50 + (k) * (Player::Player_Y - Player::old_Player_Y),
                (Player::old_Player_X - MAP::Move_Count_X) * 50 + 50 + (k) * (Player::Player_X - Player::old_Player_X),
                (Player::old_Player_Y - MAP::Move_Count_Y) * 50 + 50 + (k) * (Player::Player_Y - Player::old_Player_Y),
                graphDescs[GRAPH_TYPE_PLAYER].Graph_Handle, TRUE);
        }
        else {
            DrawExtendGraph((Player::old_Player_X - MAP::Move_Count_X) * 50 + (k) * (Player::Player_X - Player::old_Player_X),
                (Player::old_Player_Y - MAP::Move_Count_Y) * 50 + (k) * (Player::Player_Y - Player::old_Player_Y),
                (Player::old_Player_X - MAP::Move_Count_X) * 50 + 50 + (k) * (Player::Player_X - Player::old_Player_X),
                (Player::old_Player_Y - MAP::Move_Count_Y) * 50 + 50 + (k) * (Player::Player_Y - Player::old_Player_Y),
                graphDescs[GRAPH_TYPE_PLAYER2].Graph_Handle, TRUE);
        }
        if (Player::Player_X != Player::old_Player_X || Player::Player_Y != Player::old_Player_Y) {
            k = k + 1;
            if (k == 50) {
                k = 0;
            }
        }
 //   }

}