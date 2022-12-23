#include "pch.h"
#include "GameOverUI.h"
#include "ResMgr.h"
#include "Image.h"

GameOverUI::GameOverUI() : Object()
{
	m_pBGImage = ResMgr::GetInst()->ImgLoad(L"UIBackground", L"Image\\UIBackground.bmp");
	SetScale(Vec2(1.f, 1.f));
	SetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50));

	m_bf = {};
	m_bf.BlendOp = AC_SRC_OVER;
	m_bf.BlendFlags = 0;
	m_bf.AlphaFormat = 0;
	m_bf.SourceConstantAlpha = 255.f;
}


GameOverUI::~GameOverUI()
{
}

void GameOverUI::Update()
{
}

void GameOverUI::Render(HDC hdc)
{
	int Width = (int)m_pBGImage->GetWidth();
	int Height = (int)m_pBGImage->GetHeight();

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	BitBlt(m_pBGImage->GetDC()
		, (int)(vPos.x - (float)(Width * vScale.x / 2.f))
		, (int)(vPos.y - (float)(Height * vScale.y / 2.f))
		, (int)(vPos.x  + (float)(Width * vScale.x /2.f)),
		(int)(vPos.y  + (float)(Height * vScale.y/2.f))
		, hdc, Width * vScale.x, Height * vScale.y, SRCCOPY);

	AlphaBlend(hdc
		, (int)(vPos.x - (float)(Width * vScale.x / 2.f))
		, (int)(vPos.y - (float)(Height * vScale.y / 2.f))
		, Width * vScale.x, Height * vScale.y,
		m_pBGImage->GetDC(),
		0, 0, Width, Height, m_bf);


}
