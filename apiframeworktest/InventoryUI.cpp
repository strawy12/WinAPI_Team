#include "pch.h"
#include "Core.h"
#include "InventoryUI.h"
#include "KeyMgr.h"

InventoryUI::InventoryUI()
	: m_BGSize{}
{
}

InventoryUI::~InventoryUI()
{
}

void InventoryUI::Init()
{
	SetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50));
	m_BGSize = { SCREEN_WIDTH - 50,  50 };
	m_spalling = 10.f;
	m_padding = { 10,5,10,5 };

	CreateBoxUI();
}

void InventoryUI::Update()
{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(Core::GetInst()->GetWndHandle(), &pt);
		int a;
		for (int i = 0; i < MAX_BLOCK_COUNT; ++i)
		{
			if (PtInRect(&m_uiBoxVec[i].rt, pt))
			{
				m_uiBoxVec[i].isClick = true;
			}
			else
			{
				m_uiBoxVec[i].isClick = false;
			}
		}

}

void InventoryUI::Render(HDC hdc)
{
	Vec2 vPos = GetPos();
	//¸¶Á¨Å¸ »ö»ó »¬¶§ transparent: Åõ¸íÇÑ
	// bmp 

	HBRUSH bgBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, bgBrush);

	Rectangle(hdc
		, (int)(vPos.x - m_BGSize.x / 2.f)
		, (int)(vPos.y - m_BGSize.y / 2.f)
		, (int)(vPos.x + m_BGSize.x / 2.f)
		, (int)(vPos.y + m_BGSize.y / 2.f));

	SelectObject(hdc, oldBrush);

	HBRUSH blockBrush = CreateSolidBrush(RGB(0, 0, 0));
	for (int i = 0; i < MAX_BLOCK_COUNT; ++i)
	{
		if (m_uiBoxVec[i].isClick)
		{
			oldBrush = (HBRUSH)SelectObject(hdc, blockBrush);
		}

		Rectangle(hdc
			, m_uiBoxVec[i].rt.left
			, m_uiBoxVec[i].rt.top
			, m_uiBoxVec[i].rt.right
			, m_uiBoxVec[i].rt.bottom);

		if (m_uiBoxVec[i].isClick)
		{
			SelectObject(hdc, oldBrush);
		}
	}

	DeleteObject(bgBrush);
}

void InventoryUI::CreateBoxUI()
{
	Vec2 vPos = GetPos();

	Vec2 startPos = Vec2(vPos.x - m_BGSize.x / 2.f + m_padding.left, vPos.y - m_BGSize.y / 2.f + m_padding.top);
	Vec2 blockSize = Vec2((m_BGSize.x - (m_padding.left + m_padding.right)) / MAX_BLOCK_COUNT - m_spalling,
		m_BGSize.y - (m_padding.top + m_padding.bottom));

	for (int i = 0; i < MAX_BLOCK_COUNT; ++i)
	{
		Vec2 pos = startPos;
		pos.x += i * (blockSize.x + m_spalling);

		m_uiBoxVec.push_back({
	  (int)(pos.x)
	, (int)(pos.y)
	, (int)(pos.x + blockSize.x)
	, (int)(pos.y + blockSize.y) });
	}
}


