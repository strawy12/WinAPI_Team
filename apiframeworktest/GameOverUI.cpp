#include "pch.h"
#include "GameOverUI.h"
#include "BlockMgr.h"
#include "ResMgr.h"
#include "Image.h"
#include "Core.h"
#include "KeyMgr.h"

GameOverUI::GameOverUI() : Object()
{
	m_pBGImage = ResMgr::GetInst()->ImgLoad(L"UIBackground", L"Image\\UIBackground.bmp");
	m_pTitleBtnImage = ResMgr::GetInst()->ImgLoad(L"TitleBtn", L"Image\\TitleBtn.bmp");

	SetScale(Vec2(1.f, 1.f));
	SetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50));

	m_bf = {};
	m_bf.BlendOp = AC_SRC_OVER;
	m_bf.BlendFlags = 0;
	m_bf.AlphaFormat = 0;
	m_bf.SourceConstantAlpha = 200.f;

	Vec2 pos = GetPos();
	int bgWidth = (int)m_pBGImage->GetWidth();
	int bgHeight = (int)m_pBGImage->GetHeight();
	int btnWidth = (int)m_pTitleBtnImage->GetWidth();
	int btnHeight = (int)m_pTitleBtnImage->GetHeight();

	m_titleBtnRect.left = pos.x - btnWidth / 2;
	m_titleBtnRect.right = m_titleBtnRect.left + btnWidth;
	m_titleBtnRect.top = pos.y + bgHeight / 2 - 50 - btnHeight/ 2;
	m_titleBtnRect.bottom = m_titleBtnRect.top + btnHeight ;
}


GameOverUI::~GameOverUI()
{
}

void GameOverUI::Update()
{
	if (BlockMgr::GetInst()->GameOver() == false) return;

	if (KEY_UP(KEY::LBTN))
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(Core::GetInst()->GetWndHandle(), &pt);

		if (PtInRect(&m_titleBtnRect, pt))
		{
			int a = 0;
			//Title ¾ÀÀ¸·Î
			//ChangeScene(SCENE_TYPE::DEFAULT);
		}
	}
	
}

void GameOverUI::Render(HDC hdc)
{
	if (BlockMgr::GetInst()->GameOver() == false) return;

	BGRender(hdc);
	TitleRender(hdc);
	BoxCountTextRender(hdc);
	PlayTimeTextRender(hdc);
	TitleBtnRender(hdc);

}

void GameOverUI::BGRender(HDC hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = (int)m_pBGImage->GetWidth();
	int Height = (int)m_pBGImage->GetHeight();

	HDC alphaDC = CreateCompatibleDC(hdc);
	HBITMAP alphabit = CreateCompatibleBitmap(hdc,
		Core::GetInst()->GetResolution().x, Core::GetInst()->GetResolution().y);
	SelectObject(alphaDC, alphabit);

	BitBlt(alphaDC
		, 0
		, 0
		, Width, Height
		, hdc
		, (int)(vPos.x) - Width / 2, (int)(vPos.y) - Height / 2
		, SRCCOPY);

	TransparentBlt(alphaDC
		, 0
		, 0
		, Width, Height
		, m_pBGImage->GetDC()
		, 0, 0, Width, Height
		, RGB(255, 0, 255));

	AlphaBlend(hdc
		, (int)(vPos.x) - Width / 2
		, (int)(vPos.y) - Height / 2
		, Width, Height,
		alphaDC,
		0, 0, Width, Height, m_bf);

	DeleteObject(alphabit);
	DeleteDC(alphaDC);
}

void GameOverUI::TitleRender(HDC hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = (int)m_pBGImage->GetWidth();
	int Height = (int)m_pBGImage->GetHeight();

	HFONT titleFont = CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, HANGEUL_CHARSET, 0, 0, 0, 0, L"³ª´®°íµñ");
	HFONT oldFont = (HFONT)SelectObject(hdc, titleFont);

	SetTextColor(hdc, RGB(255, 0, 0));
	SetBkMode(hdc, TRANSPARENT);

	wstring str = TEXT("GAME OVER");

	TextOut(hdc,
		vPos.x - 80,
		vPos.y - (float)(Height * vScale.y / 2.f) + 10,
		str.c_str(), str.length());

	SelectObject(hdc, oldFont);
	DeleteObject(titleFont);
}

void GameOverUI::BoxCountTextRender(HDC hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = (int)m_pBGImage->GetWidth();
	int Height = (int)m_pBGImage->GetHeight();

	HFONT hFont = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, HANGEUL_CHARSET, 0, 0, 0, 0, L"³ª´®°íµñ");
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);

	TCHAR szTemp[256];
	int stackBoxCnt = BlockMgr::GetInst()->GetBoxCount();
	swprintf_s(szTemp, TEXT("½×Àº ¹Ú½º: %d"), stackBoxCnt);

	wstring str = szTemp;

	TextOut(hdc,
		vPos.x - Width / 2 + 20,
		vPos.y - (float)(Height * vScale.y / 2.f) + 70,
		str.c_str(), str.length());

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void GameOverUI::PlayTimeTextRender(HDC hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = (int)m_pBGImage->GetWidth();
	int Height = (int)m_pBGImage->GetHeight();

	HFONT hFont = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, HANGEUL_CHARSET, 0, 0, 0, 0, L"³ª´®°íµñ");
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);

	TCHAR szTemp[256];
	int seceond = (int)BlockMgr::GetInst()->GetPlayTime();
	int minute = 0;

	if (seceond >= 60)
	{
		minute = seceond / 60;
		seceond %= 60;
	}
	swprintf_s(szTemp, TEXT("ÇÃ·¹ÀÌ Å¸ÀÓ: %dºÐ %dÃÊ"), minute, seceond);

	wstring str = szTemp;

	TextOut(hdc,
		vPos.x - Width / 2 + 20,
		vPos.y - (float)(Height * vScale.y / 2.f) + 105,
		str.c_str(), str.length());

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void GameOverUI::TitleBtnRender(HDC hdc)
{
	int Width = (int)m_pTitleBtnImage->GetWidth();
	int Height = (int)m_pTitleBtnImage->GetHeight();
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	TransparentBlt(hdc
		, m_titleBtnRect.left
		, m_titleBtnRect.top
		, Width, Height
		, m_pTitleBtnImage->GetDC()
		, 0, 0, Width, Height
		, RGB(255, 0, 255));
}
