#include "pch.h"
#include "PyramidUI.h"
#include "Core.h"
#include "KeyMgr.h"
#include "Block.h"

PyramidUI::PyramidUI()
	: m_uiBoxList{}
{
}

PyramidUI::~PyramidUI()
{
}

void PyramidUI::Init()
{
	SetPos(Vec2((SCREEN_WIDTH / 2), ((SCREEN_HEIGHT / 2 - 30))));
	SetScale(Vec2((SCREEN_WIDTH - 100), (SCREEN_HEIGHT - 120)));
	CreateBoxUI();
}

void PyramidUI::Render(HDC hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	HBRUSH bgBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, bgBrush);

	Rectangle(hdc
		, (int)(vPos.x - vScale.x / 2.f)
		, (int)(vPos.y - vScale.y / 2.f)
		, (int)(vPos.x + vScale.x / 2.f)
		, (int)(vPos.y + vScale.y / 2.f));

	SelectObject(hdc, oldBrush);

	HBRUSH clickBrush = CreateSolidBrush(RGB(0, 0, 0));
	HPEN selectablePen = CreatePen(PS_DASH, 1, RGB(1, 1, 0));
	HPEN oldPen = nullptr;

	for (int i = 0; i < m_uiBoxList.size(); ++i)
	{
		if (m_uiBoxList[i].isClick)
		{
			oldBrush = (HBRUSH)SelectObject(hdc, clickBrush);
		}
		if (m_uiBoxList[i].IsSelectable()) 
		{
			oldPen = (HPEN)SelectObject(hdc, selectablePen);
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
		if (m_uiBoxList[i].IsSelectable())
		{
			SelectObject(hdc, oldPen);
		}

	}

	DeleteObject(bgBrush);
	DeleteObject(clickBrush);
	DeleteObject(selectablePen);
}

void PyramidUI::CreateBoxUI()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	float boxSize = 69.f;

	vPos.x -= vScale.x / 2.f;
	vPos.y += vScale.y / 2.f - boxSize;

	Vec2 boxScale = Vec2(boxSize, boxSize);
	int n = 8;

	for (int m = 0; m < n; m++)
	{
		Vec2 startPos = vPos;
		startPos.x += (m * 0.5f) * boxScale.x;
		startPos.y -= boxScale.y * m;

		for (int i = 0; i < n - m; i++)
		{
			int left;
			int right;
			Vec2 pos = startPos;
			pos.x += i * boxScale.x;
			if (m == 0)
				left = right = -1;
			else
			{
				left = m_uiBoxList.size() - (n - m) - 1;
				right = m_uiBoxList.size() - (n - m);
			}

			m_uiBoxList.push_back({
					RECT{
				  (int)(pos.x)
				, (int)(pos.y)
				, (int)(pos.x + boxScale.x)
				, (int)(pos.y + boxScale.y) }, false, false, nullptr, left, right });
		}
	}
}

void PyramidUI::JudgeBoxUI(MONSTER_TYPE type)
{
	int left;
	int	right;

	for (int i = 0; i < 8; i++)
	{
		m_uiBoxList[i].isSelectable = true;
	}
	for (int i = 8; i < 36; i++)
	{
		left = m_uiBoxList[i].left;
		right = m_uiBoxList[i].right;

		if (m_uiBoxList[left].block == nullptr || m_uiBoxList[right].block == nullptr)
			continue;

		if (m_uiBoxList[left].block->GetBlockType() == type || m_uiBoxList[right].block->GetBlockType() == type)
			m_uiBoxList[i].isSelectable = true;
	}
}

void PyramidUI::Update()
{
	if (KEY_UP(KEY::LBTN))
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(Core::GetInst()->GetWndHandle(), &pt);

		for (int i = 0; i < m_uiBoxList.size(); ++i)
		{
			if (m_uiBoxList[i].IsSelectable() == false)
				continue;

			if (PtInRect(&m_uiBoxList[i].rt, pt))
			{
				m_uiBoxList[i].isClick = true;
			}
			else
			{
				m_uiBoxList[i].isClick = false;
			}
		}
	}
}
