#include "Battle.h"
#include "Mode.h"
#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#include "MAP.h"
#include "Monster.h"

#include<random>

int Battle::Monster_Num = -1;
int Battle::Monster_graph;
int Battle::Select_Comand;

Battle::Battle() {}
Battle::~Battle(){};
void Battle::Initialize() {
    Battle::Monster_Num= Monster::set_Monster(MAP::MAP_Num);
    Battle::Monster_graph = LoadGraph(slime.Monster_Name);
    Select_Comand = 0;
}
void Battle::Draw_Battle(int Comand) {
    MAP::Draw_FIELD();
    unsigned int Comand_Cr1 = GetColor(255, 255, 255);
    unsigned int Comand_Cr2 = GetColor(0, 0, 0);
    DrawBox(150, 50, 450, 360, Comand_Cr1, TRUE);
    DrawBox(160, 60, 440, 350, Comand_Cr2, TRUE);
    DrawExtendGraph(225,150,375,300,Battle::Monster_graph,true);
    
    DrawBox(100, 370, 210, 500, Comand_Cr1, TRUE);
    DrawBox(110, 380, 200, 490, Comand_Cr2, TRUE);
    
    for (int i = 0; i < Comand_Max; i++) {
        if (Select_Comand == i) {
            DrawBox(comand[i].x-5,comand[i].y-5,195,comand[i].y+18,Comand_Cr1,TRUE);
            DrawFormatString(comand[i].x, comand[i].y, Comand_Cr2, comand[i].string);
        }else{
            DrawFormatString(comand[i].x, comand[i].y, Comand_Cr1, comand[i].string);
        }
    }
}
int Battle::Start_Battle(int Player_Count) {
	if (Player_Count < 10) {
		return GameMode_BATTLE;
	}
	else {
		return GameMode_FIELD;
	}
}

int Battle::Set_Comand() {
    if (Player::Player_Time == 0) {
        if (Mode::keyState[KEY_INPUT_S]) {
            Select_Comand = (Select_Comand + 1) % (Comand_Max);
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (Mode::keyState[KEY_INPUT_W]) {
            Select_Comand= (Select_Comand + Comand_Max - 1) % (Comand_Max);
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }

        if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
            return Select_Comand;
        }
        if (Mode::keyState[KEY_INPUT_ESCAPE] && !Mode::old_ESCAPE_keyState) {
            
        }

    }
    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 200) {
        Player::Player_Time = 0;
    }
    return -1;
}

void Battle::Update_Battle(int Comand) {
    if (Comand == Comand_Run) {
        if (Battle::Comand_RunAway()) {
            Mode::GameMode = GameMode_FIELD;
        }
    }
}

int Battle::Select_Magic() {
    return 0;
}
int Battle::Select_Item() {
    return 0;
}
bool Battle::Comand_RunAway() {
    std::random_device rand;
    if (rand() % 2==0) {
        return true;
    }
    else {
        return false;
    }
}