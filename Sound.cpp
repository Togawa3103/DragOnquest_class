#include "Sound.h"
#include "DxLib.h"
int Sound::SHandle;
Sound::Sound() {

}

void Sound::LoadSound(const char *SoundName) {
	SHandle=LoadSoundMem(SoundName);
	ChangeVolumeSoundMem(100, SHandle);
}

void Sound::PlayBGMSound(int Handle) {
	PlaySoundMem(Handle,DX_PLAYTYPE_LOOP);
}