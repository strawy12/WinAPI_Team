#include "pch.h"
#include "BlockMgr.h"
#include"Block.h"
#include "PyramidUI.h"
#include"InventoryUI.h"
#include"InventoryBoxUI.h"
#include"PyramidBoxUI.h"
#include"GameOverUI.h"
#include"TimeMgr.h"
#include"ResMgr.h"
#include"Image.h"
 
BlockMgr::BlockMgr()
{
} 

BlockMgr::~BlockMgr()
{
	Release();
}

void BlockMgr::Init()
{
	Release();

	m_inventoryUI = new InventoryUI;
	m_inventoryUI->Init();

	m_pyramidUI = new PyramidUI;
	m_pyramidUI->Init();

	m_gameOverUI = new GameOverUI;

	CreateObject(m_inventoryUI, GROUP_TYPE::DEFAULT);
	CreateObject(m_pyramidUI, GROUP_TYPE::DEFAULT);
	CreateObject(m_gameOverUI, GROUP_TYPE::DEFAULT);
	CreateMonsterTypes();

}

void BlockMgr::Update()
{
	if (GameOver())
		return;

	m_playTime += TimeMgr::GetInst()->GetfDT();
	m_currentTime -= TimeMgr::GetInst()->GetfDT();

	if (m_currentTime <= 0.f)
	{
		m_gameState = GAME_STATE::GAMEOVER;
	}
}

void BlockMgr::Render(HDC hdc)
{
	TimerRender(hdc);
	PlayTimeTextRender(hdc);
}

void BlockMgr::Release()
{
	if (m_gameOverUI)
		delete m_gameOverUI;

	if (m_invenBoxUI)
		delete m_invenBoxUI;

	if (m_inventoryUI)
	{
		DeleteObject(m_inventoryUI);
	}

	if (m_pyramidUI)
	{
		DeleteObject(m_pyramidUI);
	}

	m_cirCount = 0;
	m_boxCount = 0;
	m_currentTime = (0.f);
	m_maxTime = (0.f);

}

void BlockMgr::TimerRender(HDC hdc)
{
	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hNullBrush);

	Rectangle(hdc,
		10, 40, 210, 70);

	SelectObject(hdc, hOldBrush);

	int size = (int)((m_currentTime / m_maxTime) * 200.f);

	Rectangle(hdc,
		10, 40, 10 + size, 70);

	HFONT hFont = CreateFont(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, HANGEUL_CHARSET, 0, 0, 0, 0, L"³ª´®°íµñ");
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkMode(hdc, TRANSPARENT);

	TCHAR szTemp[256];
	swprintf_s(szTemp, TEXT("%d / %d"), (int)round(m_currentTime), (int)m_maxTime);
	wstring str = szTemp;

	TextOut(hdc, 80, 45, str.c_str(), str.length());

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void BlockMgr::PlayTimeTextRender(HDC hdc)
{
	HFONT hFont = CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, HANGEUL_CHARSET, 0, 0, 0, 0, L"±Ã¼­");
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);

	TCHAR szTemp[256];

	swprintf_s(szTemp, TEXT("Time: %d"), (int)round(m_playTime));
	wstring str = szTemp;

	TextOut(hdc, 10, 10, str.c_str(), str.length());

	SelectObject(hdc, oldFont);
	::DeleteObject(oldFont);
}

void BlockMgr::CreateMonsterTypes()
{
	srand(time(NULL));

	for (int i = 0; i < 12; i++)
	{
		CreateMonster((BOX_TYPE)(rand() % 5), i);
	}

	SetMaxTime(DEFAULT_MAX_TIME - (m_cirCount++ * 12));

}

void BlockMgr::CreateMonster(BOX_TYPE type, int idx)
{
	Object* pObj = new Block(type);
	//CreateObject(pObj, GROUP_TYPE::DEFAULT);
	m_inventoryUI->AddBlock(idx, dynamic_cast<Block*>(pObj));
}

void BlockMgr::SelectInventoryBoxUI(InventoryBoxUI* invenBoxUI)
{
	if (invenBoxUI->GetBlock() == nullptr)
	{
		m_invenBoxUI = nullptr;
		ResetBoxUI();
		return;
	}

	m_invenBoxUI = invenBoxUI;
	m_pyramidUI->JudgeBoxUI(m_invenBoxUI->GetBlockType());
}

void BlockMgr::SelectPyramidBoxUI(PyramidBoxUI* pyBoxUI)
{
	if (m_invenBoxUI == nullptr)
		return;

	m_pyramidUI->AddBlock(pyBoxUI, m_invenBoxUI->GetBlock());
	m_invenBoxUI->SetBlock(nullptr);
	m_boxCount++;

	ResetBoxUI();

	if (m_inventoryUI->AllUsedBlock())
	{
		CreateMonsterTypes();
	}

	CheckGameOver();
}

void BlockMgr::ResetBoxUI()
{
	m_inventoryUI->ResetBoxUI();
	m_pyramidUI->ResetBoxUI();
}

void BlockMgr::CheckGameOver()
{
	if (m_boxCount >= 36)
	{
		m_gameState = GAME_STATE::GAMECLEAR;
		return;
	}

	bool isExistSelectableBox = false;
	for (auto& box : m_inventoryUI->GetUIBoxList())
	{
		if (box->GetBlock() == nullptr) continue;


		if (isExistSelectableBox == false && m_pyramidUI->ExistSelectableBox(box->GetBlockType()))
		{
			isExistSelectableBox = true;
		}
	}

	if (!isExistSelectableBox)
	{
		m_gameState = GAME_STATE::GAMEOVER;
	}

}

bool BlockMgr::GameOver()
{
	return m_gameState == GAME_STATE::GAMEOVER; 
}

