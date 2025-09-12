#pragma once


class Sound{
public:
	static int SHandle;
	static int bgm;
	Sound();
	static void PlayBGMSound(int* Handle);
	static void LoadSound(const char *SoundName,int *map_bgm);
	static void StopSound(int* Handle);
};