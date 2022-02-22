#include "Sound.h"
#include "DxLib.h"
#include "MAP.h"
int Sound::SHandle;
Sound::Sound() {

}

void Sound::LoadSound(const char *SoundName,int* map_bgm) {
	map_bgm[MAP::MAP_Num]=LoadSoundMem(SoundName);
	ChangeVolumeSoundMem(100, map_bgm[MAP::MAP_Num]);
}

void Sound::PlayBGMSound(int* Handle) {
	PlaySoundMem(Handle[MAP::MAP_Num],DX_PLAYTYPE_LOOP);
}

void Sound::StopSound(int* Handle) {
	StopSoundMem(Handle[MAP::MAP_Num]);
}