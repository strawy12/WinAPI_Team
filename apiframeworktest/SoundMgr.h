#pragma once
#include "fmod.hpp"
#pragma comment(lib, "fmod_vc")
enum class SOUND_CHANNEL
{
	SC_BGM, SC_EFFECT, SC_END
};
typedef struct tSoundInfo
{
	FMOD::Sound* pSound;
	bool bLoop;
}SOUNDINFO, * PSOUNDINFO;

class SoundMgr
{
public:
	SINGLE(SoundMgr);
private:
	SoundMgr();
	~SoundMgr();
private:
	FMOD::System* m_pSystem;
	map<wstring, PSOUNDINFO> m_mapSod;
	FMOD::Channel* m_pChannel[(UINT)SOUND_CHANNEL::SC_END];

public:
	void Init();
	void LoadSound(const wstring& _strKey, bool _bLoop, const wstring& _strRelativePath);
	void Play(const wstring& _strKey);
	void Stop(SOUND_CHANNEL _eChannel);
	void Volume(SOUND_CHANNEL _eChannel, float _fVol);
	void Pause(SOUND_CHANNEL _eChannel, bool _p);
private:
	PSOUNDINFO FindSound(const wstring& _strKey);
};