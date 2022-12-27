 #include "pch.h"
#include "Scene_01.h"
#include "KeyMgr.h"
#include "InventoryUI.h"
#include "PyramidUI.h"
#include "ResMgr.h"
#include "Image.h"
#include "Object.h"
#include "BlockMgr.h"
#include "TimeMgr.h"
#include "SoundMgr.h"

Scene_01::Scene_01()
{
	m_pBGImage = ResMgr::GetInst()->ImgLoad(L"PyramidBG", L"Image\\Background.bmp");
}

Scene_01::~Scene_01()
{
}

void Scene_01::Enter()
{
	BlockMgr::GetInst()->Init();
	BlockMgr::GetInst()->SetGameState(GAME_STATE::GAME);
	SoundMgr::GetInst()->LoadSound(L"GameBGM", true, L"Sound\\GameBGM.mp3");
	SoundMgr::GetInst()->Play(L"GameBGM");
	SoundMgr::GetInst()->Volume(SOUND_CHANNEL::SC_BGM, 0.3);
}

void Scene_01::Exit()
{
}

void Scene_01::Render(HDC hdc)
{
	int Width = (int)m_pBGImage->GetWidth();
	int Height = (int)m_pBGImage->GetHeight();

	int posx = SCREEN_WIDTH / 2;
	int posy = SCREEN_HEIGHT / 2;
	GdiTransparentBlt(hdc,
		posx - Width / 2,
		posy - Height / 2,
		posx + Width / 2,
		posy + Height / 2, m_pBGImage->GetDC(), 0, 0, Width, Height, RGB(255, 0, 255));

	Scene::Render(hdc);

	
}
