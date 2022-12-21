#include "pch.h"
#include "PyramidBoxUI.h"
#include "Block.h"


PyramidBoxUI::PyramidBoxUI(int left, int right)
	: BoxUI(), m_left(left), m_right(right), m_isSelectable(false)
{
}

PyramidBoxUI::~PyramidBoxUI()
{
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
