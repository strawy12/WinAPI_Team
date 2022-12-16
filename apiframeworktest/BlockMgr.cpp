#include "pch.h"
#include "BlockMgr.h"
#include"Block.h"
#include"InventoryUI.h"
#include "PyramidUI.h"

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

void BlockMgr::SelectInventoryBoxUI(MONSTER_TYPE type)
{
	m_pyramidUI->JudgeBoxUI(type);
}
