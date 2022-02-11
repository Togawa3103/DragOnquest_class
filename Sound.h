#pragma once


class Sound{
public:
	static int SHandle;

	Sound();
	static void PlayBGMSound(int Handle);
	static void LoadSound(const char *SoundName);
};