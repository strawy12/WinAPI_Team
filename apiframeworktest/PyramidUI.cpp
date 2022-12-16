#include "pch.h"
#include "PyramidUI.h"

PyramidUI::PyramidUI()
	: m_uiBoxVec{}
{
}

PyramidUI::~PyramidUI()
{
}

void PyramidUI::Init()
{
	SetPos(Vec2((SCREEN_WIDTH / 2), ((SCREEN_HEIGHT / 2 - 30))));
	SetScale(Vec2((SCREEN_WIDTH / 2 - 50), (SCREEN_HEIGHT / 2 - 60)));
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

	for (int i = 0; i < m_uiBoxVec.size(); ++i)
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

void PyramidUI::CreateBoxUI()
{
    Vec2 vPos = GetPos();
    Vec2 vScale = GetScale();

    vPos.x -= vScale.x / 2.f;
    vPos.y += vScale.y / 2.f + 40;

    Vec2 boxSize = Vec2(40, 40);
    int n = 8;

    for (int m = 0; m < n; m++)
    {
        Vec2 startPos = vPos;
        startPos.x += (m * 0.5f) * boxSize.x;
        startPos.y -= boxSize.y * m;

        for (int i = 0; i < n - m; i++)
        {
            Vec2 pos = startPos;
            pos.x += i * boxSize.x;

            m_uiBoxVec.push_back({
                    RECT{
                  (int)(pos.x)
                , (int)(pos.y)
                , (int)(pos.x + boxSize.x)
                , (int)(pos.y + boxSize.y) }, false });
        }
    }
}

void PyramidUI::Update()
{
}
