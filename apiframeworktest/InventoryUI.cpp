#include "pch.h"
#include "Core.h"
#include "InventoryUI.h"
#include "InventoryBoxUI.h"
#include "KeyMgr.h"
#include "Block.h"
#include "BlockMgr.h"
#include "SoundMgr.h"

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

	if (BlockMgr::GetInst()->GetGameState() != GAME_STATE::GAME)
	{
		return;
	}

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

	for (int i = 0; i < m_uiBoxList.size(); ++i)
	{
		m_uiBoxList[i]->Render(hdc);
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

		InventoryBoxUI* boxUI = new InventoryBoxUI;
		RECT rt = {
			  (int)(pos.x)
			, (int)(pos.y)
			, (int)(pos.x + blockSize.x)
			, (int)(pos.y + blockSize.y) };

		boxUI->SetRect(rt);

		boxUI->SetPos(pos);
		boxUI->SetScale(blockSize);

		m_uiBoxList.push_back(boxUI);
	}
}

void InventoryUI::AddBlock(int idx, Block* block)
{
	Vec2 pos;
	const RECT& rt = m_uiBoxList[idx]->GetRect();

	m_uiBoxList[idx]->SetBlock(block);

	pos.x = rt.left + (rt.right - rt.left) / 2;
	pos.y = rt.top + (rt.bottom - rt.top) / 2;
	m_uiBoxList[idx]->GetBlock()->SetPos(pos);
	m_uiBoxList[idx]->GetBlock()->SetScale(Vec2(1, 1));

	SoundMgr::GetInst()->LoadSound(L"SetBox", true, L"Sound\\SetBox.mp3");
	SoundMgr::GetInst()->Play(L"SetBox");
}

void InventoryUI::PtInBoxUI()
{
	POINT pt;
	GetCursorPos(&m_mousept);
	ScreenToClient(Core::GetInst()->GetWndHandle(), &m_mousept);

	for (int i = 0; i < m_uiBoxList.size(); ++i)
	{
		if (PtInRect(&m_uiBoxList[i]->GetRect(), m_mousept))
		{
			m_selectBoxUI = m_uiBoxList[i];
			BlockMgr::GetInst()->SelectInventoryBoxUI(m_uiBoxList[i]);
		}
		else
		{
			m_uiBoxList[i]->SetIsClick(false);

			if (m_uiBoxList[i]->GetBlock() != nullptr)
			{
				Vec2 pos;
				const RECT& rt = m_uiBoxList[i]->GetRect();
				m_uiBoxList[i]->SetIsClick(false);
				pos.x = rt.left + (rt.right - rt.left) / 2;
				pos.y = rt.top + (rt.bottom - rt.top) / 2;
				m_uiBoxList[i]->GetBlock()->SetPos(pos);
			}
		}
	}

	if (m_selectBoxUI != nullptr && m_selectBoxUI->GetBlock() != nullptr)
	{
		Vec2 pos;
		const RECT& rt = m_selectBoxUI->GetRect();
		m_selectBoxUI->SetIsClick(true);
		pos.x = rt.left + (rt.right - rt.left) / 2;
		pos.y = rt.top + (rt.bottom - rt.top) / 2;
		pos.y -= 16;
		m_selectBoxUI->GetBlock()->SetPos(pos);
	}
}

void InventoryUI::ResetBoxUI()
{
	m_selectBoxUI = nullptr;
	for (int i = 0; i < m_uiBoxList.size(); ++i)
	{
		m_uiBoxList[i]->SetIsClick(false);
	}
}

bool InventoryUI::AllUsedBlock()
{
	for (auto boxUI : m_uiBoxList)
	{
		if (boxUI->GetBlock() != nullptr)
		{
			return false;
		}
	}

	return true;
}


