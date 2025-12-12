#include "Battle.h"
#include "Mode.h"
#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#include "MAP.h"
#include "Monster.h"
#include "Enum.h"
#include "Magic.h"
#include "Sound.h"
#include<random>

int Battle::Monster_Num = -1;
int Battle::Monster_graph;
int Battle::Select_Comand;
bool Battle::Battle_Now=false;
bool Battle:: canRun = false;
int Battle::Turn;
bool Battle::effect = false;
unsigned int Comand_Cr1 = GetColor(255, 255, 255);
unsigned int Comand_Cr2 = GetColor(0, 0, 0);

bool debug = false;
Battle::Battle() {}
Battle::~Battle(){};

int damage=0;
int Heal = 0;
int select_magic = 0;
int select_item = 0;
bool canuse = true;
//int bgm;

int Battle::blackout_loop_count=0;
int Battle::brightness=255;

void Battle::Initialize() {
    Battle::Monster_Num= Monster::set_Monster(MAP::MAP_Num);
    Battle::Monster_graph = LoadGraph(Monster::MonsterArray[Battle::Monster_Num].Monster_Graph_Name);
    Monster::now_Monster = Monster::MonsterArray[Battle::Monster_Num].enemy_status;
    Monster::now_Monster.HP = Monster::now_Monster.MAXHP;
    Monster::now_Monster.MP = Monster::now_Monster.MAXMP;
    Select_Comand = 0;
    //Battle_Now = true;
    canRun = false;
    Game::comand = -1;
    Battle::check_speed();
    effect = false;
   
    Sound::bgm = LoadSoundMem("battle.mp3");
    ChangeVolumeSoundMem(80, Sound::bgm);
    PlaySoundMem(Sound::bgm,DX_PLAYTYPE_LOOP);

}
void Battle::Draw_Battle() {
    MAP::Draw_FIELD();
    DrawBox(150, 50, 450, 360, Comand_Cr1, TRUE);
    DrawBox(160, 60, 440, 350, Comand_Cr2, TRUE);
    DrawExtendGraph(225,150,375,300,Battle::Monster_graph,true);
    
    DrawBox(10, 10, 100, 100, Comand_Cr1, TRUE);
    DrawBox(20, 20, 90, 90, Comand_Cr2, TRUE);   
    DrawFormatString(30, 30, Comand_Cr1, "HP:%d", Player::HP);
    DrawFormatString(30, 60, Comand_Cr1, "MP:%d", Player::MP);
    if (debug) {
        DrawBox(0,0,200,200,Comand_Cr1,TRUE);
        DrawFormatString(10,10,Comand_Cr2,"%d", Monster::now_Monster.HP);
        DrawFormatString(10, 50, Comand_Cr2, "%d", Player::HP);
    }
}
int Battle::Start_Battle(int Player_Count) {
	if (Player_Count < 10&& map_data[MAP::MAP_Num].Monster_Appears) {
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
            Player::Player_Time = Player::Player_Time + Game::mFPS;
            return Select_Comand;
        }
        if (Mode::keyState[KEY_INPUT_ESCAPE] && !Mode::old_ESCAPE_keyState) {
            
        }

    }
    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 300) {
        Player::Player_Time = 0;
    }

    return -1;
}

//魔法の選択
int Battle::Select_Magic() {
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
    DrawBox(220, 370, 500, 500, Comand_Cr1, TRUE);
    DrawBox(230, 380, 490, 490, Comand_Cr2, TRUE);
    for (int i = 0; i < Player:: MagicBox.size(); i++) {
        if (select_magic == i) {
            DrawBox(240 + (i % 2) * 60-5, 390 + (i / 2) * 30-5, 240 + (i % 2) * 60+55, 390 + (i / 2) * 30+30, Comand_Cr1, TRUE);
            DrawFormatString(240 + (i % 2) * 60, 390 + (i / 2) * 30, Comand_Cr2, "%s", magic[Player::MagicBox[i]].magic_name);
        }
        else {
            DrawFormatString(240 + (i % 2) * 60, 390 + (i / 2) * 30, Comand_Cr1, "%s", magic[Player::MagicBox[i]].magic_name);
        }
        
    }
    if (Player::Player_Time == 0) {
        if (Mode::keyState[KEY_INPUT_S]) {
            if ((select_magic - (select_magic % 2 * 2) + 2) % magic_MAX <Player::MagicBox.size()) {
                select_magic = (select_magic + 2) % magic_MAX;
                Player::Player_Time = Player::Player_Time + Game::mFPS;
            }
        }
        if (Mode::keyState[KEY_INPUT_W]) {
            if ((select_magic - (select_magic % 2 * 2) + 2) % magic_MAX <Player::MagicBox.size()) {
                select_magic = (select_magic +  2) % magic_MAX;
                Player::Player_Time = Player::Player_Time + Game::mFPS;
            }
        }
        if (Mode::keyState[KEY_INPUT_D]) {
            if ((select_magic - (select_magic % 2 * 2) + 1) % magic_MAX < Player::MagicBox.size()) {
                select_magic = (select_magic + 5 + (select_magic % 2 * 2)) % magic_MAX;
                Player::Player_Time = Player::Player_Time + Game::mFPS;
            }
        }
        if (Mode::keyState[KEY_INPUT_A]) {
            if ((select_magic - (select_magic % 2 * 2) + 1) % magic_MAX < Player::MagicBox.size()) {
                select_magic = (select_magic - (select_magic % 2 * 2) + 1) % magic_MAX;

                Player::Player_Time = Player::Player_Time + Game::mFPS;
            }
        }
        if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
            Player::Player_Time = Player::Player_Time + Game::mFPS;
            if (Player::now_player_status.MP > magic[Player::MagicBox[select_magic]].magic_mp) {
                canuse = true;
            }
            else {
                canuse = false;
            }
            return select_magic;
        }
        if (Mode::keyState[KEY_INPUT_ESCAPE] && !Mode::old_ESCAPE_keyState) {
            Game::comand = -1;
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }

    }
    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 300) {
        Player::Player_Time = 0;
    }
    
    return -1;
}

//バトル中のアイテム選択
int Battle::Select_Item() {
    DrawBox(100, 370, 210, 500, Comand_Cr1, TRUE);
    DrawBox(110, 380, 200, 490, Comand_Cr2, TRUE);
    //int max_item_top = Player::ItemBox.size()-(2-Player::ItemBox.size() % 4/2) + 4 * (Player::ItemBox.size() / 4);
    int max_item_top = Player::ItemBox.size()-(Player::ItemBox.size()%4-Player::ItemBox.size() % 4/2) ;
    int max_item_bottom = Player::ItemBox.size()-1;
    //コマンドメニューの表示
    for (int i = 0; i < Comand_Max; i++) {
        if (Select_Comand == i) {
            DrawBox(comand[i].x - 5, comand[i].y - 5, 195, comand[i].y + 18, Comand_Cr1, TRUE);
            DrawFormatString(comand[i].x, comand[i].y, Comand_Cr2, comand[i].string);
        }
        else {
            DrawFormatString(comand[i].x, comand[i].y, Comand_Cr1, comand[i].string);
        }
    }
    DrawBox(220, 370, 500, 500, Comand_Cr1, TRUE);
    DrawBox(230, 380, 490, 490, Comand_Cr2, TRUE);
    //アイテム一覧の表示
    for (int i = 0; i < 4; i++) {
        if (Player::ItemBox.size()>(select_item/4)*4+i) {
            if (select_item == i + ((select_item / 4) * 4)) {
                DrawBox(240 + (i % 2) * 120 - 5, 390 + (i / 2) * 30 - 5, 240 + (i % 2) * 120 + 120, 390 + (i / 2) * 30 + 30, Comand_Cr1, TRUE);
                DrawFormatString(240 + (i % 2) * 120, 390 + (i / 2) * 30, Comand_Cr2, "%s", item[Player::ItemBox[i + ((select_item / 4) * 4)]].Item_name);
            }
            else {
                DrawFormatString(240 + (i % 2) * 120, 390 + (i / 2) * 30, Comand_Cr1, "%s", item[Player::ItemBox[i + ((select_item / 4) * 4)]].Item_name);
            }
        }
    }
    if (Player::Player_Time == 0) {
        if (Mode::keyState[KEY_INPUT_S]) {
            if ((select_item%3==1||select_item%3==0)&&select_item+2<Player::ItemBox.size()) {
                select_item=select_item + 2;
                
            }
            else {
                select_item = select_item - 2;
            }
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (Mode::keyState[KEY_INPUT_W]) {
            if ((select_item % 3 == 1 || select_item % 3 == 0) && select_item + 2 < Player::ItemBox.size()) {
                select_item = select_item + 2;

            }
            else {
                select_item = select_item - 2;
            }
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (Mode::keyState[KEY_INPUT_D]) {
            
            if (select_item%2==0) {
                if (select_item + 1 < Player::ItemBox.size()) {
                    select_item = select_item + 1;
                }
                else {
                    if (select_item % 4 > 1) {
                        select_item = 2;
                    }
                    else {
                        select_item = 0;
                    }
                }
            }
            else {
                if (select_item+3<Player::ItemBox.size()) {
                    select_item = select_item + 3;
                }
                else {
                    if (select_item + 1 < Player::ItemBox.size() - (1-select_item%4/2)) {
                        select_item = select_item +1;
                    }
                    else {
                        if (select_item%4>1) {
                            select_item = 2;
                        }
                        else {
                            select_item = 0;
                        }
                       
                    }
                }
            }
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (Mode::keyState[KEY_INPUT_A]) {
            
            if (select_item%2!=0) {
                select_item = select_item - 1;
            }
            else if(select_item%2==0){
                if (!(select_item-3<0)) {
                    select_item = select_item - 3;
                }
                else {
                    if (select_item%4 / 2 == 0) {
                        select_item = max_item_top;
                    }
                    else if(select_item%4/2!=0){
                        select_item = max_item_bottom;
                    }
                }
            }
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {

            Player::Player_Time = Player::Player_Time + Game::mFPS;
            return select_item;
        }
        if (Mode::keyState[KEY_INPUT_ESCAPE] && !Mode::old_ESCAPE_keyState) {
            Game::comand = -1;
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }

    }
    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 300) {
        Player::Player_Time = 0;
    }
    return -1;
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


//逃げる
void Battle::Draw_Message(int Comand, int turn,bool canrun) {
    
  
        if (Player::Player_Time == 0) {
            if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
                Game::comand = -1;
                Turn = 1 - Turn;
                Battle::Check_Battle_End();
                Player::Player_Time = Player::Player_Time + Game::mFPS;
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
        if (Player::Player_Time > 300) {
            Player::Player_Time = 0;
            effect = false;
        }
       
}

//攻撃
void Battle::Draw_Message(int Comand,int turn) {
        if (Player::Player_Time == 0) {
            if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
                 Game::comand = -1;
                 Turn = 1 - Turn;
                 Battle::Check_Battle_End();
                 Player::Player_Time = Player::Player_Time + Game::mFPS;
            }

        }

        DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
        DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
        if (turn ==1) {          
            DrawFormatString(115, 385, Comand_Cr1, "%sに%dのダメージ！", Monster::MonsterArray[Battle::Monster_Num].Monster_Name, damage);
        }
        else {
            
            DrawFormatString(115, 385, Comand_Cr1, "ゆうしゃに%dのダメージ！",   damage );
        }
        if(Player::Player_Time != 0) {
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (Player::Player_Time > 300) {
            Player::Player_Time = 0;
            effect = false;
        }
        

}

//魔法
void Battle::Draw_Message(int Comand, int turn, int magic_num) {
        if (Player::Player_Time == 0) {
            if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
                Game::comand = -1;
                Game::select_magic = -1;
                select_magic = 0;
                Turn = 1 - Turn;
                Battle::Check_Battle_End();
                Player::Player_Time = Player::Player_Time + Game::mFPS;
            }

        }


        DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
        DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
        switch (magic_num) {
        case magic_1:
            if (turn == 1) {
                if (!canuse) {
                    DrawFormatString(115, 385, Comand_Cr1, "MPが足りない！");
                }
                else {
                    DrawFormatString(115, 385, Comand_Cr1, "ゆうしゃは%dかいふくした！", Heal);
                }
            }
            else {
                DrawFormatString(115, 385, Comand_Cr1, "%sは%dかいふくした！", Monster::MonsterArray[Battle::Monster_Num].Monster_Name, Heal);
            }
            break;
        case magic_2:
            if (turn == 1) {
                if (!canuse) {
                    DrawFormatString(115, 385, Comand_Cr1, "MPが足りない！");
                }
                else {
                    DrawFormatString(115, 385, Comand_Cr1, "%sに%dのダメージ！", Monster::MonsterArray[Battle::Monster_Num].Monster_Name, damage);
                }
            }
            else {

                DrawFormatString(115, 385, Comand_Cr1, "%sをとなえた。ゆうしゃに%dのダメージ！", magic[magic_2].magic_name, damage);
            }
            break;
        }
        if (Player::Player_Time != 0) {
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (Player::Player_Time > 300) {
            Player::Player_Time = 0;
            effect = false;
        }
        

}

//道具
void Battle::Draw_Message(int Comand, int turn,int item_num,bool canuse) {
    if (Player::Player_Time == 0) {
        if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
            if (item_num >= 0) {
                if (item[item_num].consumption) {
                    Player::ItemBox.erase(Player::ItemBox.begin() + Game::select_item);
                }
            }
            Game::comand = -1;
            Game::select_item = -1;
            select_item = 0;
            Turn = 1 - Turn;
            Battle::Check_Battle_End();
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }

    }


    DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
    DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
    switch (item_num) {
    case Item_Herb:
        if (turn == 1) {
            DrawFormatString(115, 385, Comand_Cr1, "ゆうしゃは%dかいふくした！", Heal);
        }
        else {
            DrawFormatString(115, 385, Comand_Cr1, "%sは%dかいふくした！", Monster::MonsterArray[Battle::Monster_Num].Monster_Name, Heal);
        }
        break;
    default:
        if (turn==1) {
            DrawFormatString(115, 385, Comand_Cr1, "これは使えない！");
        }
        break;
    }
    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 300) {
        Player::Player_Time = 0;
        effect = false;
    }
}
void Battle::check_speed() {
    if (Player::now_player_status.SPEED> Monster::MonsterArray[Battle::Monster_Num].enemy_status.SPEED) {
        Turn = 1;
    }
    else {
        Turn = 0;
    }
}

/*void Battle::Player_Turn(int Comand) {
    switch (Comand) {
    case Comand_Fight:
       
        Monster::MonsterArray[Battle::Monster_Num].enemy_status.HP = Player::now_player_status.ATTACK - Monster::MonsterArray[Battle::Monster_Num].enemy_status.DEFENSE;
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

int Battle::Enemy_AI(int Monster_Num) {
    std::random_device rand;
    //int comand = 0;
    //int attack= Monster::MonsterArray[Monster_Num].Attack[0];
    //return attack;
    float rate = (rand() % 100) /100.0;
    float count = 0;
    for (int i = 0; i < Monster::MonsterArray[Monster_Num].Attack.size();i++) {
        count = count + Monster::MonsterArray[Monster_Num].Attack_Rate[i];
        if (count>rate) {
            return Monster::MonsterArray[Monster_Num].Attack[i];
        }
    }
}

void Battle::Update_Player(int Comand) {
    switch (Comand) {
    case Comand_Run:
        if (Battle::Comand_RunAway() && !canRun) {
            canRun = true;
        }
        break;
    case Comand_Fight:
        Cal_Damage(Turn, Comand);
        effect = true;
        break;
    case Comand_Magic:
        if (Player::MP - magic[Game::select_magic].magic_mp < 0) {
            canuse = false;
        }
        else {
            Cal_Damage(Turn, Comand, Game::select_magic);
            if(magic[Game::select_magic].magic_type==magic_Type_2)effect = true;
        }
        break;
    
    case Comand_Item:
        Cal_Damage(Turn, Comand, Player::ItemBox[Game::select_item], item[Game::select_item].canuse);
        //effect = true;
        break;
    }
    
   
}

void Battle::Update_Monster(int Comand) {
    switch (Comand) {
    case Comand_Fight:
        Cal_Damage(Turn,Comand);
        break;
    case Comand_Magic:
        Cal_Damage(Turn, Comand, magic_2);
    }
}

void Battle::Cal_Damage(int turn,int Comand) {
    switch (Comand) {
    case Comand_Fight:
        if (turn == 1) {
            damage = (Player::now_player_status.ATTACK - Monster::MonsterArray[Battle::Monster_Num].enemy_status.DEFENSE);
            if (damage <= 0) {
                damage = 1;
            }
            Monster::now_Monster.HP = Monster::now_Monster.HP - damage;

        }
        else {         
            damage =  (Monster::MonsterArray[Battle::Monster_Num].enemy_status.ATTACK - Player::now_player_status.DEFENSE);
            if (damage<=0) {
                damage = 1;
            }
            Player::HP = Player::HP - damage;
        }
    }
}



void Battle::Cal_Damage(int turn, int Comand, int Magic_Num) {
    std::random_device rand;
    switch(magic[Magic_Num].magic_type) {
    case magic_Type_1:
        if (turn == 1) {
            Player::MP -= magic[Magic_Num].magic_mp;
            if (Player::HP==Player::now_player_status.MAXHP) {
                Heal = 0;
            }
            else {
                Heal = magic[Magic_Num].magic_power + (rand() % Player::now_player_status.WISE);

                if (Player::HP + Heal >= Player::now_player_status.MAXHP) {
                    Heal = Player::now_player_status.MAXHP - Player::HP;
                    Player::HP = Player::now_player_status.MAXHP;
                    
                }
                else {
                    Player::HP = Player::HP + Heal;
                }
            }
        }
        else {
            Heal = 25 + (rand() % Monster::MonsterArray[Battle::Monster_Num].enemy_status.WISE);
            if (Monster::now_Monster.HP + Heal > Monster::MonsterArray[Battle::Monster_Num].enemy_status.MAXHP) {
                Monster::now_Monster.HP = Monster::MonsterArray[Battle::Monster_Num].enemy_status.MAXHP;
                Heal = Monster::MonsterArray[Battle::Monster_Num].enemy_status.MAXHP - Monster::now_Monster.HP;
            }
            else {
                Monster::now_Monster.HP = Monster::now_Monster.HP + Heal;
            }
        }
        break;
    case magic_Type_2:
        if (turn == 1) {
            Player::MP -= magic[Magic_Num].magic_mp;
            damage = magic[Magic_Num].magic_power+(rand()%Player::now_player_status.WISE)- Monster::MonsterArray[Battle::Monster_Num].enemy_status.MAGICDEF;
            if (damage <= 0) {
                damage = 1;
            }
            Monster::now_Monster.HP = Monster::now_Monster.HP - damage;
        }
        else {
            damage = magic[Magic_Num].magic_power +(rand()% Monster::MonsterArray[Battle::Monster_Num].enemy_status.WISE - Player::now_player_status.MAGICDEF);
            if (damage <= 0) {
                damage = 1;
            }
            Player::HP = Player::HP - damage;
        }
        break;
    }
}

void Battle::Cal_Damage(int turn, int Comand, int item_Num,bool canuse) {
    std::random_device rand;
    switch (item_Num) {
    case Item_Herb:
        if (turn == 1) {
            if (Player::HP == Player::now_player_status.MAXHP) {
                Heal = 0;
            }
            else {
                Heal = item[Item_Herb].power;

                if (Player::HP + Heal >= Player::now_player_status.MAXHP) {
                    Heal = Player::now_player_status.MAXHP - Player::HP;
                    Player::HP = Player::now_player_status.MAXHP;

                }
                else {
                    Player::HP = Player::HP + Heal;
                }
            }
        }
        else {
            Heal = 30;
            if (Monster::now_Monster.HP + Heal > Monster::MonsterArray[Battle::Monster_Num].enemy_status.MAXHP) {
                Monster::now_Monster.HP = Monster::MonsterArray[Battle::Monster_Num].enemy_status.MAXHP;
                Heal = Monster::MonsterArray[Battle::Monster_Num].enemy_status.MAXHP - Monster::now_Monster.HP;
            }
            else {
                Monster::now_Monster.HP = Monster::now_Monster.HP + Heal;
            }
        }
        break;
    default:
        break;
    }
}

void Battle::Check_Battle_End() {
    if (Monster::now_Monster.HP <= 0 || Player::HP <= 0) {
        Battle_Now = false;
    }
    if (canRun) {
        Battle_Now = false;
    }
    
}
void Battle::Finish_Battle(int Comand) {
    if (Player::Player_Time == 0) {
        if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
            Mode::GameMode = GameMode_FIELD;
            if(!canRun)Player::Exp = Player::Exp + Monster::MonsterArray[Battle::Monster_Num].enemy_status.EXP;
            if(!canRun)Player::Gold = Player::Gold + Monster::MonsterArray[Battle::Monster_Num].enemy_status.GOLD;
            //Player::Player_Time = Player::Player_Time + Game::mFPS;
            Player::Player_Time = 0;
            Game::select_item = -1;
            Game::select_magic = -1;
            
            StopSoundMem(Sound::bgm);
        }

    }

    Draw_Battle();
    DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
    DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
    DrawFormatString(115, 385, Comand_Cr1, "せんとうしゅうりょう");
    if(!canRun)DrawFormatString(115, 415, Comand_Cr1, "経験値:%d お金:%d", Monster::MonsterArray[Battle::Monster_Num].enemy_status.EXP, Monster::MonsterArray[Battle::Monster_Num].enemy_status.GOLD);
    if (Mode::GameMode == GameMode_FIELD) Battle::Monster_Num = -1;
    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 300) {
        Player::Player_Time = 0;
    }

}

void Battle::Dead() {
    if (Player::Player_Time == 0 && !Player::dead) {
        if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
            //Mode::GameMode = GameMode_FIELD;
            //Player::Player_Time = Player::Player_Time + Game::mFPS;
            Player::Player_Time = 0;

            Game::select_item = -1;
            Game::select_magic = -1;
            //Player::Initialize();
            //MAP::Initialize();
            StopSoundMem(Sound::bgm);
            Player::dead = true;
            blackout_loop_count = 0;
            brightness = 255;
        }
    }
    if (Player::dead) {
        blackout_loop_count++;
        SetDrawBright(brightness, brightness, brightness);
        brightness--;
        if (brightness == 0) {
            SetDrawBright(255, 255, 255);
            Player::dead = false;
            Mode::GameMode = GameMode_FIELD;
            Player::Initialize();
            MAP::Initialize();
            MAP::Load_MAP(MAP::MAP_Num);
        }
    }

    Draw_Battle();
    DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
    DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
    DrawFormatString(115, 385, Comand_Cr1, "やられてしまった");
    if (Mode::GameMode == GameMode_FIELD) Battle::Monster_Num = -1;

    

    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 300) {
        Player::Player_Time = 0;
    }

}

void Battle::Effect(int turn, int Comand, int sub_Num) {
    
    switch (Comand) {
    case Comand_Run:
        break;
    
    default:
        if (effect&&turn ==1&&(Player::Player_Time/100)%2==0) {
            MAP::Draw_FIELD();
            DrawBox(150, 50, 450, 360, Comand_Cr1, TRUE);
            DrawBox(160, 60, 440, 350, Comand_Cr2, TRUE);
            //DrawExtendGraph(225, 150, 375, 300, Battle::Monster_graph, true);

            DrawBox(10, 10, 100, 100, Comand_Cr1, TRUE);
            DrawBox(20, 20, 90, 90, Comand_Cr2, TRUE);
            DrawFormatString(30, 30, Comand_Cr1, "HP:%d", Player::HP);
            DrawFormatString(30, 60, Comand_Cr1, "MP:%d", Player::MP);
        }
        break;
    }
}

void Battle::NoMagic() {
    if (Player::Player_Time == 0) {
        if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
            Game::comand = -1;
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }

    }

    DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
    DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
    DrawFormatString(115, 385, Comand_Cr1, "使える魔法がない！");
    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 300) {
        Player::Player_Time = 0;
        effect = false;
    }


}
void Battle::NoItem() {
    if (Player::Player_Time == 0) {
        if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
            Game::comand = -1;
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }

    }

    DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
    DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
    DrawFormatString(115, 385, Comand_Cr1, "使える道具がない！");
    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 300) {
        Player::Player_Time = 0;
        effect = false;
    }


}