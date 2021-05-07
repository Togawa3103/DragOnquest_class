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
bool Battle::Battle_Now=false;
bool Battle:: canRun = false;
int Battle::Turn;
unsigned int Comand_Cr1 = GetColor(255, 255, 255);
unsigned int Comand_Cr2 = GetColor(0, 0, 0);

bool debug = true;
Battle::Battle() {}
Battle::~Battle(){};

int damage=0;

void Battle::Initialize() {
    Battle::Monster_Num= Monster::set_Monster(MAP::MAP_Num);
    Battle::Monster_graph = LoadGraph(slime.Monster_Graph_Name);
    Monster::now_HP = slime.enemy_status.MAXHP;
    Monster::now_MP = slime.enemy_status.MAXMP;
    Select_Comand = 0;
    //Battle_Now = true;
    canRun = false;
    Game::comand = -1;
    Battle::check_speed();
}
void Battle::Draw_Battle() {
    MAP::Draw_FIELD();
    DrawBox(150, 50, 450, 360, Comand_Cr1, TRUE);
    DrawBox(160, 60, 440, 350, Comand_Cr2, TRUE);
    DrawExtendGraph(225,150,375,300,Battle::Monster_graph,true);
    if (debug) {
        DrawBox(0,0,200,200,Comand_Cr1,TRUE);
        DrawFormatString(10,10,Comand_Cr2,"%d",Monster::now_HP);
        DrawFormatString(10, 50, Comand_Cr2, "%d", Player::HP);
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
    
    DrawBox(100, 370, 210, 500, Comand_Cr1, TRUE);
    DrawBox(110, 380, 200, 490, Comand_Cr2, TRUE);

    for (int i = 0; i < Comand_Max; i++) {
        if (Select_Comand == i) {
            DrawBox(comand[i].x - 5, comand[i].y - 5, 195, comand[i].y + 18, Comand_Cr1, TRUE);
            DrawFormatString(comand[i].x, comand[i].y, Comand_Cr2, comand[i].string);
        }
        else {
            DrawFormatString(comand[i].x, comand[i].y, Comand_Cr1, comand[i].string);
        }
    }

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

            Mode::old_RETURN_keyState = Mode::keyState[KEY_INPUT_RETURN];
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

/*void Battle::Update_Battle(int Comand) {
    switch (Comand) {
    case Comand_Run:
        if (Battle::Comand_RunAway() && !canRun) {
            canRun = true;
        }
        if (canRun) {
            Battle::Battle_Now = false;
        }
        Draw_Message(Comand,Turn);
        if (Player::Player_Time == 0) {
            if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
                Turn = 1 - Turn;
            }
        }
        if (Player::Player_Time != 0) {
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (Player::Player_Time > 200) {
            Player::Player_Time = 0;
        }
     
    case Comand_Fight:
        
        
        if (slime.enemy_status.HP<0) {
            Battle::Battle_Now = false;
        }
    }
}
*/
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

void Battle::Finish_Battle(int Comand) {
   /* switch (Comand) {
    case Comand_Run:
        Draw_Message(Comand,Turn);
        if (Player::Player_Time == 0) {
            if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
                Mode::GameMode = GameMode_FIELD;
                
                break;
            }
        }
        if (Player::Player_Time != 0) {
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (Player::Player_Time > 200) {
            Player::Player_Time = 0;
        }
    case Comand_Fight:
        //Draw_Message(Comand, Turn);
        if (Player::Player_Time == 0) {
            if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
                Mode::GameMode = GameMode_FIELD;

                break;
            }
        }
        if (Player::Player_Time != 0) {
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (Player::Player_Time > 200) {
            Player::Player_Time = 0;
        }
    }
    */
    if (Player::Player_Time == 0) {
        if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
            Mode::GameMode = GameMode_FIELD;
        }
    }
    
    Draw_Battle();
    DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
    DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
    DrawFormatString(115, 385, Comand_Cr1, "せんとうしゅうりょう");
    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 200) {
        Player::Player_Time = 0;
    }
        
}

void Battle::Draw_Message(int Comand,int turn) {
    switch (Comand) {
    case Comand_Run:
        if (Player::Player_Time == 0) {
            if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
                Game::comand = -1;
                Turn = 1 - Turn;

            }
        }
        if (canRun) {
            Draw_Battle();
            DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
            DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
            DrawFormatString(115, 385, Comand_Cr1, "ゆうしゃは逃げ出した");
        }
        else {
            Draw_Battle();
            DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
            DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
            DrawFormatString(115, 385, Comand_Cr1, "ゆうしゃはまわりこまれた");
        }

        if (Player::Player_Time != 0) {
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (Player::Player_Time > 200) {
            Player::Player_Time = 0;
        }

        break;
    case Comand_Fight:
        if (Player::Player_Time == 0) {
            if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
                 Game::comand = -1;
                 Turn = 1 - Turn;
                 
            }
        }
        
        
        DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
        DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
        if (turn ==1) {          
            DrawFormatString(115, 385, Comand_Cr1, "%sに%dのダメージ！", slime.Monster_Name, damage);
        }
        else {
            
            DrawFormatString(115, 385, Comand_Cr1, "ゆうしゃに%dのダメージ！",   damage );
        }
        if(Player::Player_Time != 0) {
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (Player::Player_Time > 200) {
            Player::Player_Time = 0;
        }
        break;
    }

}

void Battle::check_speed() {
    if (Player::now_player_status.SPEED>slime.enemy_status.SPEED) {
        Turn = 1;
    }
    else {
        Turn = 0;
    }
}

/*void Battle::Player_Turn(int Comand) {
    switch (Comand) {
    case Comand_Fight:
       
        slime.enemy_status.HP = Player::now_player_status.ATTACK - slime.enemy_status.DEFENSE;
        Draw_Message(Comand,Turn);
        
        
    }
}*/

/*void Battle::Turn_Swap() {
    if (Player::Player_Time == 0) {
        if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
            Turn = 1 - Turn;
            if (Turn==0) {
                    
                Game::comand = -1;
            }
     //   }
    //}
    /*if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 200) {
        Player::Player_Time = 0;
    }
    
}*/

int Battle::Enemy_AI() {
    std::random_device rand;
    int comand = 0;
    int attack=slime.Attack[0];

    return attack;
}

void Battle::Update_Player(int Comand) {
    switch (Comand) {
    case Comand_Run:
        if (Battle::Comand_RunAway() && !canRun) {
            canRun = true;
        }
        
    case Comand_Fight:
        Cal_Damage(Turn,Comand);
    }
}
void Battle::Update_Monster(int Comand) {
    switch (Comand) {
    case Comand_Fight:
        Cal_Damage(Turn,Comand);
    }
}
void Battle::Cal_Damage(int turn,int Comand) {
    switch (Comand) {
    case Comand_Fight:
        if (turn == 1) {
            damage = (Player::now_player_status.ATTACK - slime.enemy_status.DEFENSE);
            if (damage <= 0) {
                damage = 1;
            }
            Monster::now_HP = Monster::now_HP - damage;
        }
        else {         
            damage =  (slime.enemy_status.ATTACK - Player::now_player_status.DEFENSE);
            if (damage<=0) {
                damage = 1;
            }
            Player::HP = Player::HP - damage;
        }
    }
}

bool Battle::Check_Battle_End() {
    if (Monster::now_HP<=0||Player::HP<=0) {
        return false;
    }
    if (canRun) {
        return false;
    }
    return true;
}