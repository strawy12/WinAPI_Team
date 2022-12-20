#pragma once
#include"Object.h"

class PyramidBoxUI;
class Block;

class PyramidUI : public Object
{
public:
	PyramidUI();
	virtual ~PyramidUI();
	
	virtual void Init();
	virtual void Render(HDC hdc);
	virtual void Update() override;
	CLONE(PyramidUI)

	void CreateBoxUI();
	void JudgeBoxUI(MONSTER_TYPE type);
	void ResetBoxUI();
	void AddBlock(int idx, Block* block);
	void AddBlock(PyramidBoxUI* boxUI, Block* block);

	bool ExistSelectableBox(MONSTER_TYPE type);


private:
	vector<PyramidBoxUI*> m_uiBoxList;


};

