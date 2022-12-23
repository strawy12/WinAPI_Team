#pragma once
class InventoryUI;
class PyramidUI;
class GameOverUI;

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
	void Render(HDC hdc);
	void Release();

	void TimerRender(HDC hdc);
	void PlayTimeTextRender(HDC hdc);

public:
	void CreateMonsterTypes();
	void CreateMonster(BOX_TYPE type, int idx);
	void SelectInventoryBoxUI(InventoryBoxUI* invenBoxUI);
	void SelectPyramidBoxUI(PyramidBoxUI* pyBoxUI);
	void ResetBoxUI();

	void CheckGameOver();

public:
	void SetMaxTime(float maxTime) { m_maxTime = m_currentTime = maxTime; }
	GAME_STATE GetGameState() { return m_gameState; }
	void SetGameState(GAME_STATE state) { m_gameState = state; }
	int GetBoxCount() { return m_boxCount; }
	float GetPlayTime() { return m_playTime; }

	bool GameOver() { return m_isGameOver; }


private:
	InventoryUI* m_inventoryUI;
	PyramidUI* m_pyramidUI;

	InventoryBoxUI* m_invenBoxUI;
	GameOverUI* m_gameOverUI;


	float m_playTime;
	float m_currentTime;
	float m_maxTime;

	int m_cirCount; // 순환 카운트
	int m_boxCount; // 쌓은 카운트

	bool m_isGameOver = false;

	GAME_STATE m_gameState;
};

