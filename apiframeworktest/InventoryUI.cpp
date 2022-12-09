#include "pch.h"
#include "InventoryUI.h"

InventoryUI::InventoryUI()
	: m_BGSize{}
{
}

InventoryUI::~InventoryUI()
{
}

void InventoryUI::Init()
{
	TCHAR szTemp[256];
	wstring str;
	swprintf_s(szTemp, TEXT("게임속도 FPS: %d, DT: %f"), 1, 1.f);
	
	SetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50));
	m_BGSize = { SCREEN_WIDTH - 50,  50 };
	m_spalling = 10.f;
	m_padding = { 10,5,10,5 };
}

void InventoryUI::Update()
{

}

void InventoryUI::Render(HDC hdc)
{
	Vec2 vPos = GetPos();
	//마젠타 색상 뺄때 transparent: 투명한
	// bmp 

	HBRUSH bgBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, bgBrush);

	Rectangle(hdc
		, (int)(vPos.x - m_BGSize.x / 2.f)
		, (int)(vPos.y - m_BGSize.y / 2.f)
		, (int)(vPos.x + m_BGSize.x / 2.f)
		, (int)(vPos.y + m_BGSize.y / 2.f));

	SelectObject(hdc, oldBrush);

	Vec2 startPos = Vec2(vPos.x - m_BGSize.x / 2.f + m_padding.left, vPos.y - m_BGSize.y / 2.f + m_padding.top);
	Vec2 blockSize = Vec2((m_BGSize.x - (m_padding.left + m_padding.right)) / MAX_BLOCK_COUNT - m_spalling,
							m_BGSize.y - (m_padding.top + m_padding.bottom));

	for(int i = 0; i < MAX_BLOCK_COUNT; ++i)
	{
		Vec2 pos = startPos;
		pos.x += i * (blockSize.x + m_spalling);

		Rectangle(hdc
			, (int)(pos.x)
			, (int)(pos.y)
			, (int)(pos.x + blockSize.x)
			, (int)(pos.y + blockSize.y));
	}

	DeleteObject(bgBrush);
}

