#include "pch.h"
#include "PyramidUI.h"
#include "Core.h"
#include "KeyMgr.h"
#include "Block.h"
#include "BlockMgr.h"
#include "PyramidBoxUI.h"

PyramidUI::PyramidUI()
	: m_uiBoxList{}
{
}

PyramidUI::~PyramidUI()
{
	for (auto boxUI : m_uiBoxList)
	{
		delete boxUI;
	}

	m_uiBoxList.clear();
}

void PyramidUI::Init()
{
	SetPos(Vec2((SCREEN_WIDTH / 2), ((SCREEN_HEIGHT / 2 - 30))));
	SetScale(Vec2((SCREEN_WIDTH - 105), (SCREEN_HEIGHT - 120)));
	CreateBoxUI();
}

void PyramidUI::Render(HDC hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	for (int i = 0; i < m_uiBoxList.size(); ++i)
	{
		m_uiBoxList[i]->Render(hdc);
	}

	for (int i = 0; i < m_uiBoxList.size(); ++i)
	{
		if(m_uiBoxList[i]->GetBlock())
			m_uiBoxList[i]->GetBlock()->Render(hdc);
	}
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

			PyramidBoxUI* boxUI = new PyramidBoxUI(left, right);
			RECT rt = {
				  (int)(pos.x)
				, (int)(pos.y)
				, (int)(pos.x + boxScale.x)
				, (int)(pos.y + boxScale.y) };

			boxUI->SetRect(rt);

			boxUI->SetPos(pos);
			boxUI->SetScale(boxScale);

			m_uiBoxList.push_back(boxUI);
		}
	}
}

void PyramidUI::JudgeBoxUI(BOX_TYPE type)
{
	ResetBoxUI();

	int left;
	int	right;

	for (int i = 0; i < 8; i++)
	{
		m_uiBoxList[i]->SetIsSelectable(true);
	}
	for (int i = 8; i < 36; i++)
	{
		left = m_uiBoxList[i]->GetLeft();
		right = m_uiBoxList[i]->GetRight();

		if (m_uiBoxList[left]->GetBlock() == nullptr || m_uiBoxList[right]->GetBlock() == nullptr)
			continue;

		if (m_uiBoxList[left]->GetBlockType() == type || m_uiBoxList[right]->GetBlockType() == type)
			m_uiBoxList[i]->SetIsSelectable(true);
	}
}

void PyramidUI::ResetBoxUI()
{
	for (int i = 0; i < m_uiBoxList.size(); i++)
	{
		m_uiBoxList[i]->SetIsSelectable(false);
	}
}

void PyramidUI::Update()
{
	for (auto box : m_uiBoxList)
	{
		box->Update();
	}

	if (BlockMgr::GetInst()->GetGameState() != GAME_STATE::GAME)
	{
		return;
	}

	if (KEY_UP(KEY::LBTN))
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(Core::GetInst()->GetWndHandle(), &pt);

		for (int i = 0; i < m_uiBoxList.size(); ++i)
		{
			if (m_uiBoxList[i]->IsSelectable() == false)
				continue;

			if (PtInRect(&m_uiBoxList[i]->GetRect(), pt))
			{
				BlockMgr::GetInst()->SelectPyramidBoxUI(m_uiBoxList[i]);
				break;
			}
		}
	}

}

void PyramidUI::AddBlock(int idx, Block* block)
{
	AddBlock(m_uiBoxList[idx], block);
}

void PyramidUI::AddBlock(PyramidBoxUI* boxUI, Block* block)
{
	Vec2 pos;
	const RECT& rt = boxUI->GetRect();
	boxUI->SetBlock(block);

	BlockMgr::GetInst()->SetGameState(GAME_STATE::SPAWNBLOCK);
	// 생성 이펙트 넣어보자!

	pos.x = rt.left + (rt.right - rt.left) / 2;
	pos.y = rt.top + (rt.bottom - rt.top) / 2;
	boxUI->GetBlock()->SetPos(pos);
	boxUI->GetBlock()->SetScale(Vec2(2, 2));
	boxUI->SpawnEffect();
}

bool PyramidUI::ExistSelectableBox(BOX_TYPE type)
{
	int left;
	int	right;

	for (int i = 0; i < 8; i++)
	{
		if (m_uiBoxList[i]->GetBlock() == nullptr)
		{
			return true;
		}
	}
	for (int i = 8; i < 36; i++)
	{
		left =  m_uiBoxList[i]->GetLeft();
		right = m_uiBoxList[i]->GetRight();

		if (m_uiBoxList[left]->GetBlock() == nullptr || m_uiBoxList[right]->GetBlock() == nullptr)
			continue;

		if (m_uiBoxList[left]->GetBlockType() == type || m_uiBoxList[right]->GetBlockType() == type)
		{
			if (m_uiBoxList[i]->GetBlock() == nullptr)
			{
				return true;
			}
		}
	}

	return false;
}
