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
	SoundMgr::GetInst()->LoadSound(L"TitleBGM", true, L"Sound\\TitleBGM.mp3");
	SoundMgr::GetInst()->Play(L"TitleBGM");
	BlockMgr::GetInst()->SetGameState(GAME_STATE::GAME);
}

void Scene_01::Exit()
{
}

void Scene_01::Update()
{
	Scene::Update();
	m_playTime += TimeMgr::GetInst()->GetfDT();
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

	HFONT hFont = CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, HANGEUL_CHARSET, 0, 0, 0, 0, L"±Ã¼­");
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);

	TCHAR szTemp[256];
	
	swprintf_s(szTemp, TEXT("Time: %d"), (int)m_playTime);
	wstring str = szTemp;

	TextOut(hdc, 10, 10, str.c_str(), str.length());

	SelectObject(hdc, oldFont);
	DeleteObject(oldFont);
}
