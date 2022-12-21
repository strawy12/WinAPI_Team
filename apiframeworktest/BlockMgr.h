#pragma once
class InventoryUI;
class PyramidUI;

class PyramidBoxUI;
class InventoryBoxUI;

class BlockMgr
{
public:
	SINGLE(BlockMgr)

private:
	BlockMgr();
	~BlockMgr();

public:
	void Init();
	void FinalUpdate();

public:
	void CreateMonsterTypes();
	void CreateMonster(BOX_TYPE type, int idx);
	void SelectInventoryBoxUI(InventoryBoxUI* invenBoxUI);
	void SelectPyramidBoxUI(PyramidBoxUI* pyBoxUI);
	void ResetBoxUI();

private:
	BOX_TYPE m_monsterTypes[12];
	InventoryUI* m_inventoryUI; 
	PyramidUI* m_pyramidUI;

	InventoryBoxUI* m_invenBoxUI;
};

