#include "pch.h"
#include "BlockMgr.h"
#include"Block.h"

BlockMgr::BlockMgr()
{
}

BlockMgr::~BlockMgr()
{ 
}

void BlockMgr::Init()
{
	CreateMonsterTypes();
}

void BlockMgr::CreateMonsterTypes()
{
	srand(time(NULL));
	int cnt = 100;

	for (int i = 0; i < 12; i++) 
	{
		m_monsterTypes[i] = (MONSTER_TYPE)(rand() % 5);
		CreateMonster(m_monsterTypes[i], Vec2(cnt, 150));
		cnt += 150;
	}

}

void BlockMgr::CreateMonster(MONSTER_TYPE type, Vec2 pos)
{
	Object* pObj = new Block(type);
	pObj->SetPos(pos);

	CreateObject(pObj, GROUP_TYPE::DEFAULT);
}
