#include "pch.h"
#include "PyramidUI.h"
#include "Core.h"
#include "KeyMgr.h"

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

	HBRUSH blockBrush = CreateSolidBrush(RGB(0, 0, 0));

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

	DeleteObject(bgBrush);
	DeleteObject(blockBrush);
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
            Vec2 pos = startPos;
            pos.x += i * boxScale.x;

            m_uiBoxList.push_back({
                    RECT{
                  (int)(pos.x)
                , (int)(pos.y)
                , (int)(pos.x + boxScale.x)
                , (int)(pos.y + boxScale.y) }, false, false, nullptr });
        }
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
			// 되냐 유무
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
