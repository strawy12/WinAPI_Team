#include "pch.h"
#include "Core.h"
#include "InventoryUI.h"
#include "KeyMgr.h"
#include "Block.h"
#include "BlockMgr.h"

InventoryUI::InventoryUI()
	: Object()
{
}

InventoryUI::~InventoryUI()
{
}

void InventoryUI::Init()
{
	SetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50));
	SetScale({ SCREEN_WIDTH - 50, 50 });

	m_waitBoxScale = GetScale();
	m_waitBoxScale.x += 50;
	m_waitBoxScale.y += 50;

	m_spalling = 10.f;
	m_padding = { 10,5,10,5 };

	CreateBoxUI();
}

void InventoryUI::Update()
{
	if (KEY_UP(KEY::LBTN))
	{
		PtInBoxUI();
	}
}

void InventoryUI::Render(HDC hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	HBRUSH bgBrush = CreateSolidBrush(RGB(98, 53, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, bgBrush);

	// Background

	Rectangle(hdc
		, (int)(vPos.x - vScale.x / 2.f)
		, (int)(vPos.y - vScale.y / 2.f)
		, (int)(vPos.x + vScale.x / 2.f)
		, (int)(vPos.y + vScale.y / 2.f));

	SelectObject(hdc, oldBrush);

	HBRUSH blockBrush = CreateSolidBrush(RGB(255, 222, 121));


	// BoxUI
	for (int i = 0; i < m_uiBoxList.size(); ++i)
	{
		if (m_uiBoxList[i].isClick)
		{
			oldBrush = (HBRUSH)SelectObject(hdc, blockBrush);
		}

		Rectangle(hdc
			, m_uiBoxList[i].rt.left
			, m_uiBoxList[i].rt.top
			, m_uiBoxList[i].rt.right
			, m_uiBoxList[i].rt.bottom);

		if (m_uiBoxList[i].isClick)
		{
			SelectObject(hdc, oldBrush);
		}
	}

	/*HBRUSH waitBoxBrush = CreateSolidBrush(RGB(0, 0, 0));
	SetBkMode(hdc, TRANSPARENT);
	oldBrush = (HBRUSH)SelectObject(hdc, waitBoxBrush);

	Rectangle(hdc
		, (int)(vPos.x - vScale.x / 2.f)
		, (int)(vPos.y - vScale.y / 2.f)
		, (int)(vPos.x + vScale.x / 2.f)
		, (int)(vPos.y + vScale.y / 2.f));

	SelectObject(hdc, oldBrush);

	DeleteObject(waitBoxBrush);*/
	DeleteObject(bgBrush);
	DeleteObject(blockBrush);
}

void InventoryUI::CreateBoxUI()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Vec2 startPos = Vec2(vPos.x - vScale.x / 2.f + m_padding.left, vPos.y - vScale.y / 2.f + m_padding.top);

	Vec2 blockSize = Vec2(((vScale.x - (m_padding.left + m_padding.right) - (m_spalling * (MAX_BLOCK_COUNT - 1))) / MAX_BLOCK_COUNT),
		vScale.y - (m_padding.top + m_padding.bottom));

	for (int i = 0; i < MAX_BLOCK_COUNT; ++i)
	{
		Vec2 pos = startPos;
		pos.x += i * (int)(blockSize.x + m_spalling);

		m_uiBoxList.push_back({
		RECT{
	  (int)(pos.x)
	, (int)(pos.y)
	, (int)(pos.x + blockSize.x)
	, (int)(pos.y + blockSize.y) }, nullptr,false });
	}
}

void InventoryUI::AddBlock(int idx, Block* block)
{
	m_uiBoxList[idx].block = block;
	Vec2 pos;
	pos.x = m_uiBoxList[idx].rt.left + (m_uiBoxList[idx].rt.right - m_uiBoxList[idx].rt.left) / 2;
	pos.y = m_uiBoxList[idx].rt.top + (m_uiBoxList[idx].rt.bottom - m_uiBoxList[idx].rt.top) / 2;
	m_uiBoxList[idx].block->SetPos(pos);
	m_uiBoxList[idx].block->SetScale(Vec2(1, 1));
}

void InventoryUI::PtInBoxUI()
{
	POINT pt;
	GetCursorPos(&m_mousept);
	ScreenToClient(Core::GetInst()->GetWndHandle(), &m_mousept);

	for (int i = 0; i < m_uiBoxList.size(); ++i)
	{
		if (PtInRect(&m_uiBoxList[i].rt, m_mousept))
		{
			m_selectBoxUI = &m_uiBoxList[i];
			BlockMgr::GetInst()->SelectInventoryBoxUI(&m_uiBoxList[i]);
		}
		else
		{
			m_uiBoxList[i].isClick = false;

			if (m_uiBoxList[i].block != nullptr)
			{
				Vec2 pos;
				pos.x = m_uiBoxList[i].rt.left + (m_uiBoxList[i].rt.right - m_uiBoxList[i].rt.left) / 2;
				pos.y = m_uiBoxList[i].rt.top + (m_uiBoxList[i].rt.bottom - m_uiBoxList[i].rt.top) / 2;
				m_uiBoxList[i].block->SetPos(pos);
			}
		}
	}

	if (m_selectBoxUI != nullptr && m_selectBoxUI->block != nullptr)
	{
		m_selectBoxUI->isClick = true;
		Vec2 pos;
		pos.x = m_selectBoxUI->rt.left + (m_selectBoxUI->rt.right - m_selectBoxUI->rt.left) / 2;
		pos.y = m_selectBoxUI->rt.top + (m_selectBoxUI->rt.bottom - m_selectBoxUI->rt.top) / 2;
		pos.y -= 16;
		m_selectBoxUI->block->SetPos(pos);
	}
}

void InventoryUI::ResetBoxUI()
{
	for (int i = 0; i < m_uiBoxList.size(); ++i)
	{
		m_uiBoxList[i].isClick = false;
	}
}


