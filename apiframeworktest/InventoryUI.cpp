#include "pch.h"
#include "Core.h"
#include "InventoryUI.h"
#include "KeyMgr.h"

InventoryUI::InventoryUI()
	: vScale{}
{
}

InventoryUI::~InventoryUI()
{
}

void InventoryUI::Init()
{
	SetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50));
	vScale = { SCREEN_WIDTH - 50,  50 };
	m_spalling = 10.f;
	m_padding = { 10,5,10,5 };

	CreateBoxUI();
}

void InventoryUI::Update()
{
		POINT pt;
		GetCursorPos(&m_mousept);
		ScreenToClient(Core::GetInst()->GetWndHandle(), &m_mousept);
		int a;
		for (int i = 0; i < MAX_BLOCK_COUNT; ++i)
		{
			if (PtInRect(&m_uiBoxVec[i].rt, m_mousept))
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
	/*TCHAR szTemp[256];
	wstring str;
	LONG x = m_mousept.x;
	LONG y = m_mousept.y;
	swprintf_s(szTemp, TEXT("mouse pos: %ld %ld"), x, y);
	OutputDebugString(szTemp);*/
	Vec2 vPos = GetPos();
	//¸¶Á¨Å¸ »ö»ó »¬¶§ transparent: Åõ¸íÇÑ
	// bmp 

	HBRUSH bgBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, bgBrush);

	Rectangle(hdc
		, (int)(vPos.x - vScale.x / 2.f)
		, (int)(vPos.y - vScale.y / 2.f)
		, (int)(vPos.x + vScale.x / 2.f)
		, (int)(vPos.y + vScale.y / 2.f));

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
	DeleteObject(blockBrush);
}

void InventoryUI::CreateBoxUI()
{
	Vec2 vPos = GetPos();

	Vec2 startPos = Vec2(vPos.x - vScale.x / 2.f + m_padding.left, vPos.y - vScale.y / 2.f + m_padding.top);

	Vec2 blockSize = Vec2(((vScale.x - (m_padding.left + m_padding.right) - (m_spalling * (MAX_BLOCK_COUNT -1))) / MAX_BLOCK_COUNT),
		vScale.y - (m_padding.top + m_padding.bottom));

	for (int i = 0; i < MAX_BLOCK_COUNT; ++i)
	{
		Vec2 pos = startPos;
		pos.x += i * (int)(blockSize.x+ m_spalling);

		m_uiBoxVec.push_back({ 
		RECT{
	  (int)(pos.x)
	, (int)(pos.y)
	, (int)(pos.x + blockSize.x)
	, (int)(pos.y + blockSize.y) }, false});
	}
}


