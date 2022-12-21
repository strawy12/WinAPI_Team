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
	void Update();
	void FinalUpdate();
	void Render(HDC hdc);

public:
	void CreateMonsterTypes();
	void CreateMonster(BOX_TYPE type, int idx);
	void SelectInventoryBoxUI(InventoryBoxUI* invenBoxUI);
	void SelectPyramidBoxUI(PyramidBoxUI* pyBoxUI);
	void ResetBoxUI();

public:
	void SetMaxTime(float maxTime) { m_maxTime = m_currentTime = maxTime; }
	GAME_STATE GetGameState() { return m_gameState; }
	void SetGameState(GAME_STATE state) { m_gameState = state; }

private:
	BOX_TYPE m_monsterTypes[12];
	InventoryUI* m_inventoryUI; 
	PyramidUI* m_pyramidUI;

	InventoryBoxUI* m_invenBoxUI;

	float m_currentTime;
	float m_maxTime;

	int m_cirCount; // 순환 카운트

	GAME_STATE m_gameState;
};

