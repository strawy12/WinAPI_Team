#pragma once
#include"Object.h"

struct PyramidBoxUI
{
	RECT rt;
	bool isSelectable;
	class Block* block;
	int left;
	int right;

	bool IsSelectable()
	{
		if (isSelectable == true && block == nullptr)
		{
			return true;
		}
		else return false;
	}
};

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



private:
	vector<PyramidBoxUI> m_uiBoxList;

};

