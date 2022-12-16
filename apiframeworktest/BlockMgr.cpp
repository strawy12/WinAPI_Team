#include "pch.h"
#include "BlockMgr.h"
#include"Block.h"
#include"InventoryUI.h"

BlockMgr::BlockMgr() 
{
}

BlockMgr::~BlockMgr()
{ 
}

void BlockMgr::Init()
{
	m_inventoryUI = new InventoryUI;
	m_inventoryUI->Init();

	CreateObject(m_inventoryUI, GROUP_TYPE::DEFAULT);
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
