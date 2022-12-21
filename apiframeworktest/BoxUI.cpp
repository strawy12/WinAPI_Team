#include "pch.h"
#include "Block.h"
#include "BoxUI.h"
#include "ResMgr.h"
#include "Image.h"

BoxUI::BoxUI()
	: m_rt{}
	, m_block(nullptr)
{
	m_pOutLineImage = ResMgr::GetInst()->ImgLoad(L"BoxUI_Outline", L"Image\\BoxOutLine.bmp");
	m_pBGImage = ResMgr::GetInst()->ImgLoad(L"Box_Background", L"Image\\BoxBackground.bmp");

	m_bf = {};
	m_bf.BlendOp = AC_SRC_OVER;
	m_bf.BlendFlags = 0;
	m_bf.AlphaFormat = 0;
	m_bf.SourceConstantAlpha = 100.f;
}

BoxUI::~BoxUI()
{
}

void BoxUI::Update()
{
}

void BoxUI::Render(HDC hdc)
{
	BackgroundRender(hdc);
	OutlineRender(hdc);

}

MONSTER_TYPE BoxUI::GetBlockType()
{
	if (m_block == nullptr)
	{
		return MONSTER_TYPE::NONE;
	}

	return m_block->GetBlockType();
}

void BoxUI::OutlineRender(HDC hdc)
{
	int Width = (int)m_pOutLineImage->GetWidth();
	int Height = (int)m_pOutLineImage->GetHeight();
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	TransparentBlt(hdc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, vScale.x, vScale.y
		, m_pOutLineImage->GetDC()
		, 0, 0, Width, Height
		, RGB(255, 0, 255));
}

void BoxUI::BackgroundRender(HDC hdc)
{
	int Width = (int)m_pBGImage->GetWidth();
	int Height = (int)m_pBGImage->GetHeight();

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	HDC alphaDC = CreateCompatibleDC(hdc);

	BitBlt(alphaDC
		, (int)(vPos.x)
		, (int)(vPos.y)
		, vScale.x, vScale.y,
		hdc,
		Width, Height, SRCCOPY);

	TransparentBlt(alphaDC
		, (int)(vPos.x)
		, (int)(vPos.y)
		, vScale.x, vScale.y
		, m_pOutLineImage->GetDC()
		, 0, 0, Width, Height
		, RGB(255, 0, 255));

	AlphaBlend(hdc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, vScale.x, vScale.y,
		alphaDC,
		0, 0, Width, Height, m_bf);

	



	DeleteDC(alphaDC);
}

