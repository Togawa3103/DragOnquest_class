#include "Battle.h"
#include "Mode.h"
#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#include "MAP.h"
#include "Monster.h"
#include "Enum.h"
#include<random>

int Battle::Monster_Num = -1;
int Battle::Monster_graph;
int Battle::Select_Comand;
bool Battle::Battle_Now=false;
bool Battle:: canRun = false;
int Battle::Turn;
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
    
    DrawBox(10, 10, 100, 100, Comand_Cr1, TRUE);
    DrawBox(20, 20, 90, 90, Comand_Cr2, TRUE);   
    DrawFormatString(30, 30, Comand_Cr1, "HP:%d", Player::HP);
    DrawFormatString(30, 60, Comand_Cr1, "MP:%d", Player::MP);
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
            Player::Player_Time = Player::Player_Time + Game::mFPS;
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

//���@�̑I��
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
    if (Player::Player_Time > 200) {
        Player::Player_Time = 0;
    }
    
    return -1;
}

//�o�g�����̃A�C�e���I��
int Battle::Select_Item() {
    DrawBox(100, 370, 210, 500, Comand_Cr1, TRUE);
    DrawBox(110, 380, 200, 490, Comand_Cr2, TRUE);
    //int max_item_top = Player::ItemBox.size()-(2-Player::ItemBox.size() % 4/2) + 4 * (Player::ItemBox.size() / 4);
    int max_item_top = Player::ItemBox.size()-(Player::ItemBox.size()%4-Player::ItemBox.size() % 4/2) ;
    int max_item_bottom = Player::ItemBox.size()-1;
    //�R�}���h���j���[�̕\��
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
    //�A�C�e���ꗗ�̕\��
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
    if (Player::Player_Time > 200) {
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


//������
void Battle::Draw_Message(int Comand, int turn,bool canrun) {
    
  
        if (Player::Player_Time == 0) {
            if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
                Game::comand = -1;
                Turn = 1 - Turn;
                Player::Player_Time = Player::Player_Time + Game::mFPS;
            }

        }
        if (canRun) {
            Draw_Battle();
            DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
            DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
            DrawFormatString(115, 385, Comand_Cr1, "�䂤����͓����o����");
        }
        else {
            Draw_Battle();
            DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
            DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
            DrawFormatString(115, 385, Comand_Cr1, "�䂤����͂܂�肱�܂ꂽ");
        }

        if (Player::Player_Time != 0) {
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (Player::Player_Time > 200) {
            Player::Player_Time = 0;
        }
       
}

//�U��
void Battle::Draw_Message(int Comand,int turn) {
        if (Player::Player_Time == 0) {
            if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
                 Game::comand = -1;
                 Turn = 1 - Turn;
                 Player::Player_Time = Player::Player_Time + Game::mFPS;
            }

        }

        DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
        DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
        if (turn ==1) {          
            DrawFormatString(115, 385, Comand_Cr1, "%s��%d�̃_���[�W�I", slime.Monster_Name, damage);
        }
        else {
            
            DrawFormatString(115, 385, Comand_Cr1, "�䂤�����%d�̃_���[�W�I",   damage );
        }
        if(Player::Player_Time != 0) {
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (Player::Player_Time > 200) {
            Player::Player_Time = 0;
        }
        

}

//���@
void Battle::Draw_Message(int Comand, int turn, int magic_num) {
        if (Player::Player_Time == 0) {
            if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
                Game::comand = -1;
                Game::select_magic = -1;
                select_magic = 0;
                Turn = 1 - Turn;
                Player::Player_Time = Player::Player_Time + Game::mFPS;
            }

        }


        DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
        DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
        switch (magic_num) {
        case magic_1:
            if (turn == 1) {
                if (!canuse) {
                    DrawFormatString(115, 385, Comand_Cr1, "MP������Ȃ��I");
                }
                else {
                    DrawFormatString(115, 385, Comand_Cr1, "�䂤�����%d�����ӂ������I", Heal);
                }
            }
            else {
                DrawFormatString(115, 385, Comand_Cr1, "%s��%d�����ӂ������I", slime.Monster_Name, Heal);
            }
            break;
        case magic_2:
            if (turn == 1) {
                if (!canuse) {
                    DrawFormatString(115, 385, Comand_Cr1, "MP������Ȃ��I");
                }
                else {
                    DrawFormatString(115, 385, Comand_Cr1, "%s��%d�̃_���[�W�I", slime.Monster_Name, damage);
                }
            }
            else {

                DrawFormatString(115, 385, Comand_Cr1, "�䂤�����%d�̃_���[�W�I", damage);
            }
            break;
        }
        if (Player::Player_Time != 0) {
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }
        if (Player::Player_Time > 200) {
            Player::Player_Time = 0;
        }
        

}

//����
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
                
            Player::Player_Time = Player::Player_Time + Game::mFPS;
        }

    }


    DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
    DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
    switch (item_num) {
    case Item_Herb:
        if (turn == 1) {
            DrawFormatString(115, 385, Comand_Cr1, "�䂤�����%d�����ӂ������I", Heal);
        }
        else {
            DrawFormatString(115, 385, Comand_Cr1, "%s��%d�����ӂ������I", slime.Monster_Name, Heal);
        }
        break;
    default:
        if (turn==1) {
            DrawFormatString(115, 385, Comand_Cr1, "����͎g���Ȃ��I");
        }
        break;
    }
    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 200) {
        Player::Player_Time = 0;
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
    //int comand = 0;
    int attack=slime.Attack[0];

    return attack;
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
        break;
    case Comand_Magic:
        if (Player::MP - magic[Game::select_magic].magic_mp < 0) {
            canuse = false;
        }
        else {
            Cal_Damage(Turn, Comand, Game::select_magic);
        }
        break;
    
    case Comand_Item:
        Cal_Damage(Turn, Comand, Player::ItemBox[Game::select_item], item[Game::select_item].canuse);
        break;
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
            Heal = 25 + (rand() % slime.enemy_status.WISE);
            if (Monster::now_HP + Heal > slime.enemy_status.MAXHP) {
                Monster::now_HP = slime.enemy_status.MAXHP;
                Heal = slime.enemy_status.MAXHP - Monster::now_HP;
            }
            else {
                Monster::now_HP = Monster::now_HP + Heal;
            }
        }
        break;
    case magic_Type_2:
        if (turn == 1) {
            Player::MP -= magic[Magic_Num].magic_mp;
            damage = magic[Magic_Num].magic_power+(rand()%Player::now_player_status.WISE)-slime.enemy_status.MAGICDEF;
            if (damage <= 0) {
                damage = 1;
            }
            Monster::now_HP = Monster::now_HP - damage;
        }
        else {
            damage = 5+(rand()%slime.enemy_status.WISE - Player::now_player_status.MAGICDEF);
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
            if (Monster::now_HP + Heal > slime.enemy_status.MAXHP) {
                Monster::now_HP = slime.enemy_status.MAXHP;
                Heal = slime.enemy_status.MAXHP - Monster::now_HP;
            }
            else {
                Monster::now_HP = Monster::now_HP + Heal;
            }
        }
        break;
    default:
        break;
    }
}

bool Battle::Check_Battle_End() {
    if (Monster::now_HP <= 0 || Player::HP <= 0) {
        return true;
    }
    if (canRun) {
        return true;
    }
    return false;
}
void Battle::Finish_Battle(int Comand) {
    if (Player::Player_Time == 0) {
        if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
            Mode::GameMode = GameMode_FIELD;
            Player::Exp = Player::Exp + slime.enemy_status.EXP;
            Player::Gold = Player::Gold + slime.enemy_status.GOLD;
            Player::Player_Time = Player::Player_Time + Game::mFPS;
            Game::select_item = -1;
            Game::select_magic = -1;
        }

    }

    Draw_Battle();
    DrawBox(100, 370, 500, 500, Comand_Cr1, TRUE);
    DrawBox(110, 380, 490, 490, Comand_Cr2, TRUE);
    DrawFormatString(115, 385, Comand_Cr1, "����Ƃ����イ��傤");
    DrawFormatString(115, 415, Comand_Cr1, "�o���l:%d ����:%d", slime.enemy_status.EXP, slime.enemy_status.GOLD);
    if (Player::Player_Time != 0) {
        Player::Player_Time = Player::Player_Time + Game::mFPS;
    }
    if (Player::Player_Time > 200) {
        Player::Player_Time = 0;
    }

}