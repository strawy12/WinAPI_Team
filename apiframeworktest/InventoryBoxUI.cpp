#include "pch.h"
#include "InventoryBoxUI.h"
#include "Block.h"

InventoryBoxUI::InventoryBoxUI()
	: BoxUI(), m_isClick(false)
{
}

InventoryBoxUI::~InventoryBoxUI()
{
}

void InventoryBoxUI::Render(HDC hdc)
{
	HBRUSH selectablePenBrush = CreateSolidBrush(RGB(255, 222, 121));
	HPEN selectablePen = CreatePen(PS_DASHDOT, 1, RGB(255, 160, 0));
	HPEN oldPen = nullptr;
	HBRUSH oldBrush = nullptr;

	BoxUI::Render(hdc);

	if (m_isClick)
	{
		oldPen = (HPEN)SelectObject(hdc, selectablePen);
		SelectObject(hdc, selectablePenBrush);
		Rectangle(hdc
			, m_rt.left + 3
			, m_rt.top + 3
			, m_rt.right - 3
			, m_rt.bottom - 3);

		SelectObject(hdc, oldPen);
		SelectObject(hdc, oldBrush);
	}


	if (m_block)
	{
		m_block->Render(hdc);
	}

	DeleteObject(selectablePenBrush);
	DeleteObject(selectablePen);
}
