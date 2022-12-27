#include "pch.h"
#include "StartScene.h"
#include "Image.h"
#include "ResMgr.h"
#include "SoundMgr.h"
#include "BlockMgr.h"
#include "Core.h"
#include "KeyMgr.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

void StartScene::Enter()
{

	m_StartPos = { 230, 500 };
	m_StartRect = {};

	m_ImageBG = ResMgr::GetInst()->ImgLoad(L"TitleBG", L"Image\\TitleBG.bmp");
	m_ImageStart = ResMgr::GetInst()->ImgLoad(L"Start", L"Image\\StartBtn.bmp");

	m_StartRect.left = m_StartPos.x;
	m_StartRect.right = m_StartRect.left + m_ImageStart->GetWidth();
	m_StartRect.top = m_StartPos.y;
	m_StartRect.bottom = m_StartRect.top + m_ImageStart->GetHeight();

	SoundMgr::GetInst()->LoadSound(L"TitleBGM", true, L"Sound\\TitleBGM.mp3");
	SoundMgr::GetInst()->Play(L"TitleBGM");
	SoundMgr::GetInst()->Volume(SOUND_CHANNEL::SC_BGM, 0.3);

	BlockMgr::GetInst()->EnterTitleState();
}

void StartScene::Exit()
{
}

void StartScene::Update()
{
	if (KEY_UP(KEY::LBTN))
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(Core::GetInst()->GetWndHandle(), &pt);

		if (PtInRect(&m_StartRect, pt))
		{
			SoundMgr::GetInst()->LoadSound(L"ClickButton", false, L"Sound\\ClickButton.mp3");
			SoundMgr::GetInst()->Play(L"ClickButton");
			SoundMgr::GetInst()->Stop(SOUND_CHANNEL::SC_BGM);
			ChangeScene(SCENE_TYPE::DEFAULT);
		}
	}
}

void StartScene::Render(HDC hdc)
{
	int Width = (int)m_ImageBG->GetWidth();
	int Height = (int)m_ImageBG->GetHeight();

	int posx = SCREEN_WIDTH / 2;
	int posy = SCREEN_HEIGHT / 2;
	TransparentBlt(hdc,
		posx - Width / 2,
		posy - Height / 2,
		posx + Width / 2,
		posy + Height / 2, m_ImageBG->GetDC(), 0, 0, Width, Height, RGB(255, 0, 255));

	int BtnWidth = (int)m_ImageStart->GetWidth();
	int BtnHeight = (int)m_ImageStart->GetHeight();

	TransparentBlt(hdc
		, m_StartRect.left
		, m_StartRect.top
		, BtnWidth, BtnHeight
		, m_ImageStart->GetDC()
		, 0, 0, BtnWidth, BtnHeight
		, RGB(255, 0, 255));
}
