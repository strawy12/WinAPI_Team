#include "pch.h"
#include "SoundMgr.h"
#include "PathMgr.h"
SoundMgr::SoundMgr()
	:m_pSystem(nullptr)
{}
SoundMgr::~SoundMgr()
{
	Safe_Delete_Map(m_mapSod);
	// 다 쓰고 난 후에는 반드시 close, release해야함.
	m_pSystem->close();
	m_pSystem->release();
}
void SoundMgr::Init()
{
	FMOD::System_Create(&m_pSystem);
	if (m_pSystem != nullptr)
		m_pSystem->init(10, FMOD_INIT_NORMAL, NULL);
}
void SoundMgr::LoadSound(const wstring& _strKey, bool _bLoop, const wstring& _strRelativePath)
{
	// 찾으면 생성 x
	if (FindSound(_strKey))
		return;
	wstring strFilePath = PathMgr::GetInst()->GetRsrcPath();
	strFilePath += _strRelativePath;

	// wstring to string
	string str;
	size_t size;
	str.resize(strFilePath.length());
	wcstombs_s(&size, &str[0], str.size() + 1, strFilePath.c_str(), strFilePath.size());

	// 루프 할지 말지 결정
	FMOD_MODE eMode = FMOD_LOOP_NORMAL; // 반복 출력
	if (!_bLoop)
		eMode = FMOD_DEFAULT; // 사운드 1번만 출력

	PSOUNDINFO ptSound = new SOUNDINFO;
	ptSound->bLoop = _bLoop;
	m_pSystem->createSound(str.c_str(), eMode, NULL, &ptSound->pSound);
	m_mapSod.insert({ _strKey,ptSound });
}

void SoundMgr::Play(const wstring& _strKey)
{
	PSOUNDINFO ptSound = FindSound(_strKey);
	if (!ptSound)
		return;

	m_pSystem->update();
	SOUND_CHANNEL eChannel = SOUND_CHANNEL::SC_BGM;
	if (!ptSound->bLoop)
		eChannel = SOUND_CHANNEL::SC_EFFECT;
	m_pSystem->playSound(ptSound->pSound, NULL, false, &m_pChannel[(UINT)eChannel]);
}

void SoundMgr::Pause(SOUND_CHANNEL _eChannel, bool _p)
{
	m_pChannel[(UINT)_eChannel]->setPaused(_p);
}
void SoundMgr::Stop(SOUND_CHANNEL _eChannel)
{
	m_pChannel[(UINT)_eChannel]->stop();
}

void SoundMgr::Volume(SOUND_CHANNEL _eChannel, float _fVol)
{
	m_pChannel[(UINT)_eChannel]->setVolume(_fVol);
}

PSOUNDINFO SoundMgr::FindSound(const wstring& _strKey)
{
	map<wstring, PSOUNDINFO>::iterator iter = m_mapSod.find(_strKey);

	if (iter == m_mapSod.end())
		return nullptr;
	return iter->second;
}
