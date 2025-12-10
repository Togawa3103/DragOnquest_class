#include "EVENT.h"
#include "Sound.h"
std::bitset<4> EVENT::flag;

EVENT::EVENT() {
	flag.reset();
};

int EVENT::IsEvent() {
	if (!flag.test(EVENTS_CLEAR)&&flag.test(EVENTS_BATTLE)) {
		//flag |= (1<< EVENTS_CLEAR); 不要
		return EVENTS_CLEAR;
	}
	else if (!flag.test(EVENTS_BATTLE) && MAP::MAP_Num == events[EVENTS_BATTLE].map_num && (Player::Player_X == events[EVENTS_BATTLE].x && Player::Player_Y == events[EVENTS_BATTLE].y)){
		//flag |= (1 << EVENTS_BATTLE);　不要
		return EVENTS_BATTLE;
	}
	
	return EVENTS_None;
}

int EVENT::SetMonster(int Events_Num) {
	return Monster::MonsterArray[events[Events_Num].monster_num].Monster_Num;
}

void EVENT::SetFlag(int Events_Num) {
	flag.set(Events_Num);
}


void EVENT::BattleInit(int Events_Num) {
	Battle::Monster_graph = LoadGraph(Monster::MonsterArray[events[Events_Num].monster_num].Monster_Graph_Name);
	Monster::now_Monster = Monster::MonsterArray[events[Events_Num].monster_num].enemy_status;
	Monster::now_Monster.HP = Monster::now_Monster.MAXHP;
	Monster::now_Monster.MP = Monster::now_Monster.MAXMP;
	Battle::Select_Comand = 0;
	Battle::Battle_Now = true;
	Battle::canRun = false;
	Game::comand = -1;
	Battle::check_speed();
	Battle::effect = false;

	Sound::bgm = LoadSoundMem("battle.mp3");
	ChangeVolumeSoundMem(80, Sound::bgm);
	PlaySoundMem(Sound::bgm, DX_PLAYTYPE_LOOP);
	Player::old_Player_X = Player::Player_X;
	Player::old_Player_Y = Player::Player_Y;
	Player::Player_Time = 0;
}