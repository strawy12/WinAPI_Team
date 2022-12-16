#pragma once
class InventoryUI;
class PyramidUI;
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
	void CreateMonster(MONSTER_TYPE type, int idx);
	void SelectInventoryBoxUI(MONSTER_TYPE type);

private:
	MONSTER_TYPE m_monsterTypes[12];
	InventoryUI* m_inventoryUI; 
	PyramidUI* m_pyramidUI;
};

