#include "pch.h"
#include "BlockMgr.h"
#include"Block.h"
#include "PyramidUI.h"
#include"InventoryUI.h"
#include"InventoryBoxUI.h"
#include"PyramidBoxUI.h"
#include "SoundMgr.h"

BlockMgr::BlockMgr()
{
}

BlockMgr::~BlockMgr()
{
}

void BlockMgr::Init()
{
	//CreateMonsterTypes();
	m_inventoryUI = new InventoryUI;
	m_inventoryUI->Init();

	m_pyramidUI = new PyramidUI;
	m_pyramidUI->Init();

	CreateObject(m_inventoryUI, GROUP_TYPE::DEFAULT);
	CreateObject(m_pyramidUI, GROUP_TYPE::DEFAULT);
	CreateMonsterTypes();
}

void BlockMgr::FinalUpdate()
{
	for (auto& box : m_inventoryUI->GetUIBoxList())
	{
		if (box->GetBlock() == nullptr) continue;

		if (!m_pyramidUI->ExistSelectableBox(box->GetBlockType()))
		{
			int a = 10;
		}
	}
}

void BlockMgr::CreateMonsterTypes()
{
	srand(time(NULL));

	for (int i = 0; i < 12; i++)
	{
		m_monsterTypes[i] = (BOX_TYPE)(rand() % 5);
		CreateMonster(m_monsterTypes[i], i);
	}

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

	ResetBoxUI();

	if (m_inventoryUI->AllUsedBlock())
	{
		CreateMonsterTypes();
		SoundMgr::GetInst()->LoadSound(L"ChageArray", true, L"Sound\\ChageArray.mp3");
		SoundMgr::GetInst()->Play(L"ChageArray");
	}

	// 여기에 게임 오버 조건 만들기
}

void BlockMgr::ResetBoxUI()
{
	m_inventoryUI->ResetBoxUI();
	m_pyramidUI->ResetBoxUI();
}

