#pragma once


class BlockMgr
{
public:
	SINGLE(BlockMgr);

private:
	BlockMgr();
	~BlockMgr();

public:
	void Init();

public:
	void CreateMonsterTypes();
	void CreateMonster(MONSTER_TYPE type, Vec2 pos);

private:
	MONSTER_TYPE m_monsterTypes[12];
};

