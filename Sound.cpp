#include "DXUT.h"
#include "Sound.h"

Sound::Sound()
{
	soundmanager = new CSoundManager;
	soundmanager->Initialize(DXUTGetHWND(), DSSCL_PRIORITY);
	soundmanager->SetPrimaryBufferFormat(22050, 1, 15);
}

void Sound::soundpreloads()
{
	Sound::GetIns()->preLoad(L"res/Sound/ButtonClick.wav", L"click");
	Sound::GetIns()->preLoad(L"res/Sound/BirdJump.wav", L"jump");
	Sound::GetIns()->preLoad(L"res/Sound/GameSet.wav", L"set");
	Sound::GetIns()->preLoad(L"res/Sound/NewRecord.wav", L"record");
}

void Sound::preLoad(LPWSTR path, wstring name)
{
	CSound* sound;
	auto isFail = soundmanager->Create(&sound, path, DSBCAPS_CTRLVOLUME, GUID_NULL, 15);
	if (FAILED(isFail))
	{
		wcout << "SoundFail!! " << path << endl;
		return;
	}
	wcout << "SoundLoad!! " << path << endl;
	soundlist.emplace(name, sound);
}

void Sound::playSonud(wstring name, bool loop, LONG volume)
{
	auto f = soundlist.find(name);
	if (f == soundlist.end())
	{
		wcout << "SoundPlay Failed " << name << endl;
		return;
	}
	f->second->Play(0, loop, volume);
}

void Sound::stopSound(wstring name)
{
	auto f = soundlist.find(name);
	if (f == soundlist.end()) return;
	f->second->Stop();
}
