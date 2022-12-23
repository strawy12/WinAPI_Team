#include "pch.h"
#include "PyramidBoxUI.h"
#include "Block.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "Image.h"
#include "BlockMgr.h"


PyramidBoxUI::PyramidBoxUI(int left, int right)
	: BoxUI(), m_left(left), m_right(right), m_isSelectable(false)
{
}

PyramidBoxUI::~PyramidBoxUI()
{
}



void PyramidBoxUI::Update()
{
	if (m_isSpawn)
	{
		Vec2 pos = m_block->GetPos();
		pos.y += TimeMgr::GetInst()->GetfDT() * m_acceleration;
		m_acceleration += 200.f;
		if (pos.y >= m_originPos.y)
		{
			pos.y = m_originPos.y;
			m_isSpawn = false;
			
			BlockMgr::GetInst()->SetGameState(GAME_STATE::GAME);
		}
		m_block->SetPos(pos);
	}

}

void PyramidBoxUI::Render(HDC hdc)
{
	HBRUSH selectablePenBrush = CreateSolidBrush(RGB(255, 222, 121));
	HPEN selectablePen = CreatePen(PS_DASHDOT, 1, RGB(255, 160, 0));
	HPEN oldPen = nullptr;
	HBRUSH oldBrush = nullptr;

	BoxUI::Render(hdc);

	if (IsSelectable())
	{
		oldPen = (HPEN)SelectObject(hdc, selectablePen);
		oldBrush = (HBRUSH)SelectObject(hdc, selectablePenBrush);
		Rectangle(hdc
			, m_rt.left + 3
			, m_rt.top + 3
			, m_rt.right - 3
			, m_rt.bottom - 3);

		SelectObject(hdc, oldPen);
		SelectObject(hdc, oldBrush);
	}

	DeleteObject(selectablePenBrush);
	DeleteObject(selectablePen);
}

void PyramidBoxUI::SpawnEffect()
{
	if (m_block == nullptr) return;

	m_isSpawn = true;
	m_originPos = m_block->GetPos();
	m_block->SetPos(Vec2(m_originPos.x, m_originPos.y - 70));
	m_acceleration = 300.f;
}