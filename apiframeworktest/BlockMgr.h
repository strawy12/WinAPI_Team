#pragma once
class InventoryUI;
class PyramidUI;

struct PyramidBoxUI;
struct InventoryBoxUI;

class BlockMgr
{
public:
	SINGLE(BlockMgr)

private:
	BlockMgr();
	~BlockMgr();

public:
	void Init();

public:
	void CreateMonsterTypes();
	void CreateMonster(MONSTER_TYPE type, int idx);
	void SelectInventoryBoxUI(InventoryBoxUI* invenBoxUI);
	void SelectPyramidBoxUI(PyramidBoxUI* pyBoxUI);
	void ResetBoxUI();

private:
	MONSTER_TYPE m_monsterTypes[12];
	InventoryUI* m_inventoryUI; 
	PyramidUI* m_pyramidUI;

	InventoryBoxUI* m_invenBoxUI;
};

