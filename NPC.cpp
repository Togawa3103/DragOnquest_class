#include "DxLib.h"
#include "MAP.h"
#include "NPC.h"
#include "Mode.h"
#include "Player.h"
#include "Enum.h"
#include "Game.h"
#include "Battle.h"
#include <vector>

unsigned static int TextBox_Cr1 = GetColor(255, 255, 255);
unsigned static int TextBox_Cr2 = GetColor(0, 0, 0);
std::vector<int> NPC::npc_num;
int NPC::Talk_Count;

int NPC::Yes_No=0;
int NPC::finish_text = 0;
void NPC::Load_NPC(int MAP_Num) {
	for (int i = 0; i < NPC_MAX; i++) {
		if (npc[i].MAP_Num == MAP_Num) {
			if (npc_graph[npc[i].NPC_Type].load_graph==-1) {
				npc_graph[npc[i].NPC_Type].load_graph = LoadGraph(npc_graph[npc[i].NPC_Type].Graph_Name);
			}
			MAP::canmove[npc[i].y][npc[i].x] = false;
			npc_num.push_back(npc[i].NPC_Num);
		}
		if (MAP_Num<npc[i].MAP_Num) {
			break;
		}
	}
}

void NPC::Draw_NPC(std::vector<int> npc_num) {
	for (int i = 0; i < npc_num.size();i++) {
		DrawExtendGraph((npc[npc_num[i]].x-MAP::Move_Count_X) * 50, (npc[npc_num[i]].y -MAP::Move_Count_Y)*50,( npc[npc_num[i]].x - MAP::Move_Count_X) * 50 + 50, (npc[npc_num[i]].y - MAP::Move_Count_Y) * 50 + 50, npc_graph[npc[npc_num[i]].NPC_Type].load_graph,TRUE);
		
	}
}

void NPC::Draw_Talk(int NPC_Num) {
	if (Player::Player_Time==0) {
		if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
			if (npc[Mode::selected_NPC].text.size()-finish_text>Talk_Count) {
				Talk_Count++;
			}
			if(npc[Mode::selected_NPC].text.size()-finish_text <= Talk_Count){
				Mode::GameMode = GameMode_FIELD;
				Mode::Selected_Menu = -1;
				Game::Talk_now = false;
				Mode::Select_Menu_Num = 0;
			}
		}
	}
	if (npc[Mode::selected_NPC].text.size()-finish_text > Talk_Count) {
		DrawBox(100, 370, 500, 500, TextBox_Cr1, TRUE);
		DrawBox(110, 380, 490, 490, TextBox_Cr2, TRUE);
		DrawFormatString(120, 385, TextBox_Cr1, "%s", text[npc[Mode::selected_NPC].text[Talk_Count]]);
	}
	if (Player::Player_Time != 0) {
		Player::Player_Time = Player::Player_Time + Game::mFPS;
	}
	if (Player::Player_Time > 200) {
		Player::Player_Time = 0;
	}
}

void NPC::Draw_Question(int NPC_Num) {
	if (Player::Player_Time == 0) {
		if (Mode::keyState[KEY_INPUT_W]) {
			Yes_No = 1 - Yes_No;
			Player::Player_Time = Player::Player_Time + Game::mFPS;
		}
		if (Mode::keyState[KEY_INPUT_S]) {
			Yes_No = 1 - Yes_No;
			Player::Player_Time = Player::Player_Time + Game::mFPS;
		}
		if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
			Player::Player_Time = Player::Player_Time + Game::mFPS;
			if (Yes_No == 0) {
				
				finish_text = (-1) * npc[Mode::selected_NPC].text[Talk_Count];
				Talk_Count++;
			}
			else {

				Talk_Count = Talk_Count + (npc[Mode::selected_NPC].text.size()-Talk_Count- (-1) * npc[Mode::selected_NPC].text[Talk_Count]);
			}
		}
	}
	if (npc[Mode::selected_NPC].text.size()> Talk_Count) {
		DrawBox(100, 370, 500, 500, TextBox_Cr1, TRUE);
		DrawBox(110, 380, 490, 490, TextBox_Cr2, TRUE);
		DrawFormatString(120, 385, TextBox_Cr1, "%s", text[npc[Mode::selected_NPC].text[Talk_Count-1]]);
	}
	DrawBox(430, 250, 520, 340, TextBox_Cr1, TRUE);
	DrawBox(440, 260, 510, 330, TextBox_Cr2, TRUE);
	if (Yes_No==0) {
		DrawBox(444,260,480,290,TextBox_Cr1,TRUE);
		DrawFormatString(445, 265, TextBox_Cr2, "‚Í‚¢");
		DrawFormatString(445, 295, TextBox_Cr1, "‚¢‚¢‚¦");
	
	}
	else {
		DrawBox(444, 290, 500, 325, TextBox_Cr1, TRUE);
		DrawFormatString(445, 265, TextBox_Cr1, "‚Í‚¢");
		DrawFormatString(445, 295, TextBox_Cr2, "‚¢‚¢‚¦");
	}
	if (Player::Player_Time != 0) {
		Player::Player_Time = Player::Player_Time + Game::mFPS;
	}
	if (Player::Player_Time > 200) {
		Player::Player_Time = 0;
	}

}