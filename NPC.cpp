#include "DxLib.h"
#include "MAP.h"
#include "NPC.h"
#include "Mode.h"
#include "Player.h"
#include "Enum.h"
#include "Game.h"
#include "Battle.h"
#include "INN.h"
#include "SHOP.h"
#include <string>
#include <vector>

std::string replaceOtherStr(char* price, const char* text);
int CounstText(std::string text);

unsigned static int TextBox_Cr1 = GetColor(255, 255, 255);
unsigned static int TextBox_Cr2 = GetColor(0, 0, 0);
std::vector<int> NPC::npc_num;
int NPC::Talk_Count;

int NPC::Yes_No=0;
int NPC::finish_text = 0;
void NPC::Load_NPC(int MAP_Num) {
	npc_num.clear();
	for (int i = 0; i < NPC_MAX; i++) {
		if (npc[i].MAP_Num == MAP_Num) {
			if (npc_graph[npc[i].NPC_Type].load_graph==-1) {
				npc_graph[npc[i].NPC_Type].load_graph = LoadGraph(npc_graph[npc[i].NPC_Type].Graph_Name);
			}
			MAP::canmove[npc[i].y][npc[i].x] = false;
			npc_num.push_back(npc[i].NPC_Num);
		}
		/*if (MAP_Num<npc[i].MAP_Num) {
			break;
		}*/
	}
}

void NPC::Draw_NPC(std::vector<int> npc_num) {
	for (int i = 0; i < npc_num.size();i++) {
		int getNpc = 0;
		for (int j = 0; j < NPC_MAX;j++) {
			if (npc_num[i]==npc[j].NPC_Num) {
				getNpc = j;
				break;
			}
		}
		DrawExtendGraph((npc[getNpc].x - MAP::Move_Count_X) * 50, (npc[getNpc].y - MAP::Move_Count_Y) * 50, (npc[getNpc].x - MAP::Move_Count_X) * 50 + 50, (npc[getNpc].y - MAP::Move_Count_Y) * 50 + 50, npc_graph[npc[getNpc].NPC_Type].load_graph, TRUE);

		//DrawExtendGraph((npc[npc_num[i]].x-MAP::Move_Count_X) * 50, (npc[npc_num[i]].y -MAP::Move_Count_Y)*50,( npc[npc_num[i]].x - MAP::Move_Count_X) * 50 + 50, (npc[npc_num[i]].y - MAP::Move_Count_Y) * 50 + 50, npc_graph[npc[npc_num[i]].NPC_Type].load_graph,TRUE);
		
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
	char* gold = NULL;

	if (Player::Player_Time == 0) {
		for (int i = 0; i < INN_MAX; i++) {
			if (inn_list[i].NPC_Num == NPC_Num) {
				gold = (char*)inn_list[i].price;
			}
		}
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
				
				finish_text = (-1) * npc[NPC_Num].text[Talk_Count];
				Talk_Count++;

			}
			else {

				Talk_Count = Talk_Count + (npc[NPC_Num].text.size()-Talk_Count- (-1) * npc[NPC_Num].text[Talk_Count]);
			}
		}
	}
	if (npc[Mode::selected_NPC].text.size() > Talk_Count) {
		DrawBox(100, 370, 500, 500, TextBox_Cr1, TRUE);
		DrawBox(110, 380, 490, 490, TextBox_Cr2, TRUE);
		DrawFormatString(120, 385, TextBox_Cr1, "%s", text[npc[Mode::selected_NPC].text[Talk_Count - 1]]);
		
	}
	DrawBox(430, 250, 520, 340, TextBox_Cr1, TRUE);
	DrawBox(440, 260, 510, 330, TextBox_Cr2, TRUE);
	if (Yes_No==0) {
		DrawBox(444,260,480,290,TextBox_Cr1,TRUE);
		DrawFormatString(445, 265, TextBox_Cr2, "はい");
		DrawFormatString(445, 295, TextBox_Cr1, "いいえ");
	
	}
	else {
		DrawBox(444, 290, 500, 325, TextBox_Cr1, TRUE);
		DrawFormatString(445, 265, TextBox_Cr1, "はい");
		DrawFormatString(445, 295, TextBox_Cr2, "いいえ");
	}
	if (Player::Player_Time != 0) {
		Player::Player_Time = Player::Player_Time + Game::mFPS;
	}
	if (Player::Player_Time > 200) {
		Player::Player_Time = 0;
	}

}

void NPC::Draw_INNTalk(int NPC_Num) {
	char* gold = NULL;
	for (int i = 0; i < INN_MAX; i++) {
		if (inn_list[i].NPC_Num == NPC_Num) {
			gold = (char*)inn_list[i].price;
		}
	}
	if (Player::Player_Time == 0) {
		if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
			if (npc[Mode::selected_NPC].text.size() - finish_text > Talk_Count) {
				Talk_Count++;
			}
			if (npc[Mode::selected_NPC].text.size() - finish_text <= Talk_Count) {
				Mode::GameMode = GameMode_FIELD;
				Mode::Selected_Menu = -1;
				Game::Talk_now = false;
				Mode::Select_Menu_Num = 0;
			}
		}
	}
	if (npc[Mode::selected_NPC].text.size() - finish_text > Talk_Count) {
		DrawBox(100, 370, 500, 500, TextBox_Cr1, TRUE);
		DrawBox(110, 380, 490, 490, TextBox_Cr2, TRUE);
		if (Talk_Count<2) {
			DrawFormatString(120, 385, TextBox_Cr1, "%s", replaceOtherStr(gold, text[npc[Mode::selected_NPC].text[Talk_Count]].text).c_str());
			//INN::BUY(TRUE);
		}
		else {
			if (Yes_No == 0) {
				if (Player::Gold > std::stoi(gold)) {
					DrawFormatString(120, 385, TextBox_Cr1, "%s", text[npc[Mode::selected_NPC].text[Talk_Count]]); 
					INN::BUY(TRUE);
				}
				else {
					DrawFormatString(120, 385, TextBox_Cr1, "お金が足りません。");
				}
			}
			else {
				DrawFormatString(120, 385, TextBox_Cr1, "%s", text[npc[Mode::selected_NPC].text[Talk_Count]]);
			}
		}
	}
	if (Player::Player_Time != 0) {
		Player::Player_Time = Player::Player_Time + Game::mFPS;
	}
	if (Player::Player_Time > 200) {
		Player::Player_Time = 0;
	}
}

void NPC::Draw_INN(int NPC_Num) {
	//TO_DO 値段を動的に挿入
	char* gold=NULL;
	for (int i = 0; i < INN_MAX; i++) {
		if (inn_list[i].NPC_Num == NPC_Num) {
			gold = (char *)inn_list[i].price;
		}
	}
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
				
				finish_text = (-1) * npc[NPC_Num].text[Talk_Count];
				Talk_Count++;

			}
			else {

				Talk_Count = Talk_Count + (npc[NPC_Num].text.size() - Talk_Count - (-1) * npc[NPC_Num].text[Talk_Count]);
			}
		}
	}
	if (npc[Mode::selected_NPC].text.size() > Talk_Count) {
		DrawBox(100, 370, 500, 500, TextBox_Cr1, TRUE);
		DrawBox(110, 380, 490, 490, TextBox_Cr2, TRUE);

		DrawFormatString(120, 385, TextBox_Cr1, "%s", replaceOtherStr(gold,text[npc[Mode::selected_NPC].text[Talk_Count - 1]].text).c_str());
	}
	DrawBox(430, 250, 520, 340, TextBox_Cr1, TRUE);
	DrawBox(440, 260, 510, 330, TextBox_Cr2, TRUE);
	if (Yes_No == 0) {
		DrawBox(444, 260, 480, 290, TextBox_Cr1, TRUE);
		DrawFormatString(445, 265, TextBox_Cr2, "はい");
		DrawFormatString(445, 295, TextBox_Cr1, "いいえ");

	}
	else {
		DrawBox(444, 290, 500, 325, TextBox_Cr1, TRUE);
		DrawFormatString(445, 265, TextBox_Cr1, "はい");
		DrawFormatString(445, 295, TextBox_Cr2, "いいえ");
	}
	if (Player::Player_Time != 0) {
		Player::Player_Time = Player::Player_Time + Game::mFPS;
	}
	if (Player::Player_Time > 200) {
		Player::Player_Time = 0;
	}

}

void NPC::Draw_SHOP(int NPC_Num) {
	if (Player::Player_Time == 0) {
		if (Mode::keyState[KEY_INPUT_W]) {
			if (!Shop::check) {
				Shop::shop_select_item = (Shop::shop_select_item - 1) % (shop[Shop::shop_npc].Item_List.size());
			}
			else {
				Shop::Yes_No = 1- Shop::Yes_No;
			}
			Player::Player_Time = Player::Player_Time + Game::mFPS;
		}
		if (Mode::keyState[KEY_INPUT_S]) {
			if (!Shop::check) {
				Shop::shop_select_item = (Shop::shop_select_item + 1) % (shop[Shop::shop_npc].Item_List.size());
			}
			else {
				Shop::Yes_No = 1 - Shop::Yes_No;

			}
			Player::Player_Time = Player::Player_Time + Game::mFPS;
		}
		if (Mode::keyState[KEY_INPUT_RETURN] && !Mode::old_RETURN_keyState) {
			if (!Shop::check) {
				Shop::check = true;
			}
			else {
				if (Shop::Yes_No == 0 &&(Player::now_player_status.GOLD>= shop[Shop::shop_npc].Item_Price[Shop::shop_select_item])&&(Player::ItemBox.size()< ItemBox_Max)) {
					Shop::BUY(Shop::shop_npc,shop[Shop::shop_npc].Item_List[Shop::shop_select_item]);
				}
				Shop::check = false;
			}
			Player::Player_Time = Player::Player_Time + Game::mFPS;
		}
		if (Mode::keyState[KEY_INPUT_ESCAPE] && !Mode::old_ESCAPE_keyState) {
			if (!Shop::check) {
				Mode::Selected_Menu = -1;
				Mode::Select_Menu_Num = 0;
				Mode::GameMode = GameMode_FIELD;
				Shop::shop_npc == -1;
				Game::Talk_now = false;
			}
			else {
				Shop::check = false;
			}
			Player::Player_Time = Player::Player_Time + Game::mFPS;
		}
	}

	// NPC_Numから商人を設定
	if (Shop::shop_npc==-1) {
		while (true) {
			if (shop[Shop::shop_npc].NPC_NUM == NPC_Num) {
				break;
			}
			Shop::shop_npc++;
		}
	}

	// 商品リストの枠を表示
	DrawBox(80, 40, 300, 260, TextBox_Cr1, TRUE);
	DrawBox(90, 50, 290, 250, TextBox_Cr2, TRUE);
	DrawBox(100, 370, 500, 500, TextBox_Cr1, TRUE);
	DrawBox(110, 380, 490, 490, TextBox_Cr2, TRUE);

	//メッセージ表示
	if (!Shop::check) {
		DrawFormatString(120, 385, TextBox_Cr1, "%s", "よろずやです");
	}
	else {
		if(Player::now_player_status.GOLD < shop[Shop::shop_npc].Item_Price[Shop::shop_select_item]) {
			DrawFormatString(120, 385, TextBox_Cr1, "%s", "おかねがたりません");
		}
		else if (Player::ItemBox.size() >= ItemBox_Max) {
			DrawFormatString(120, 385, TextBox_Cr1, "%s", "荷物がいっぱいです");
		}else {
			DrawFormatString(120, 385, TextBox_Cr1, "%s", "かいますか？");
		}
	}
	// 商品を表示
	for (int i = 0; i < shop[Shop::shop_npc].Item_List.size() ; i++) {
		
		if (Shop::shop_select_item == i) {
				DrawBox(95, 55 + (i) * 30, 285, 85 + (i) * 30, TextBox_Cr1, TRUE);
				DrawFormatString(100, 60 + (i) * 30, TextBox_Cr2, "%s %d", item[shop[Shop::shop_npc].Item_List[i]].Item_name, shop[Shop::shop_npc].Item_Price[i]);
		}
		else {
			DrawFormatString(100, 60 + (i) * 30, TextBox_Cr1, "%s %d", item[shop[Shop::shop_npc].Item_List[i]].Item_name, shop[Shop::shop_npc].Item_Price[i]);
		}
			
	}
	if (Shop::check&& (Player::now_player_status.GOLD >= shop[Shop::shop_npc].Item_Price[Shop::shop_select_item]) && (Player::ItemBox.size() < ItemBox_Max)) {
		DrawBox(430, 250, 520, 340, TextBox_Cr1, TRUE);
		DrawBox(440, 260, 510, 330, TextBox_Cr2, TRUE);
		if (Shop::Yes_No == 0) {
			DrawBox(444, 260, 480, 290, TextBox_Cr1, TRUE);
			DrawFormatString(445, 265, TextBox_Cr2, "はい");
			DrawFormatString(445, 295, TextBox_Cr1, "いいえ");

		}
		else {
			DrawBox(444, 290, 500, 325, TextBox_Cr1, TRUE);
			DrawFormatString(445, 265, TextBox_Cr1, "はい");
			DrawFormatString(445, 295, TextBox_Cr2, "いいえ");
		}
	}
	
	if (Player::Player_Time != 0) {
		Player::Player_Time = Player::Player_Time + Game::mFPS;
	}
	if (Player::Player_Time > 200) {
		Player::Player_Time = 0;
	}

}

std::string replaceOtherStr(char* price, const char* text) {
	
	std::string tmp = std::string("X");
	std::string tmp2 = std::string(price);
	//std::string tmp3 = std::string(const_cast<char*> (text)); 
	//std::string tmp3 = std::string("泊まりますか？\n一泊XGです。");
	std::string retext = "泊まりますか？\n一泊" + tmp2 + "Gです。";
	std::string tmp3 = retext;
	return tmp3;
	const unsigned int pos = tmp3.find(tmp);
	const int len = CounstText(tmp3);

	
	return tmp3.replace(pos, len, tmp2);
}

int CounstText(std::string text) {
	int     i1;
	int count = 0;

	for (i1 = 0;;) {
		if (text[i1] == '\0')
			break;
		if (_ismbblead(text[i1])) {
			if (text[i1 + 1] == '\0') {
				count++;
				break;
			}
			count++;
			i1 += 2;
			continue;
		}
		count++;
		i1++;
	}
	return count;
}