#include "pch.h"
#include "BlockMgr.h"
#include"Block.h"
#include "PyramidUI.h"
#include"InventoryUI.h"
#include"PyramidBoxUI.h"

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
		if (box.block == nullptr) continue;

		if (!m_pyramidUI->ExistSelectableBox(box.block->GetBlockType()))
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
		m_monsterTypes[i] = (MONSTER_TYPE)(rand() % 5);
		CreateMonster(m_monsterTypes[i], i);
	}

}

void BlockMgr::CreateMonster(MONSTER_TYPE type, int idx)
{
	Object* pObj = new Block(type);
	CreateObject(pObj, GROUP_TYPE::DEFAULT);
	m_inventoryUI->AddBlock(idx, dynamic_cast<Block*>(pObj));
}

void BlockMgr::SelectInventoryBoxUI(InventoryBoxUI* invenBoxUI)
{
	if (invenBoxUI->block == nullptr)
	{
		m_invenBoxUI = nullptr;
		ResetBoxUI();
		return;
	}

	m_invenBoxUI = invenBoxUI;
	m_pyramidUI->JudgeBoxUI(m_invenBoxUI->block->GetBlockType());
}

void BlockMgr::SelectPyramidBoxUI(PyramidBoxUI* pyBoxUI)
{
	if (m_invenBoxUI == nullptr)
		return;

	m_pyramidUI->AddBlock(pyBoxUI, m_invenBoxUI->block);
	m_invenBoxUI->block = nullptr;

	ResetBoxUI();

	if (m_inventoryUI->AllUsedBlock())
	{
		CreateMonsterTypes();
	}

	// 여기에 게임 오버 조건 만들기
}

void BlockMgr::ResetBoxUI()
{
	m_inventoryUI->ResetBoxUI();
	m_pyramidUI->ResetBoxUI();
}

