#pragma once

#include "Singleton.h"

class Sound : public Singleton<Sound>
{
public:
	Sound();
	~Sound(){};

	CSoundManager* soundmanager;
	map<wstring, CSound*> soundlist;

	void soundpreloads();

	void preLoad(LPWSTR path, wstring name);
	void playSonud(wstring name, bool loop = false, LONG volume = 0);
	void stopSound(wstring name);
};

