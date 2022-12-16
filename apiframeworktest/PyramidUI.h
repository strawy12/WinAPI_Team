#pragma once
#include"Object.h"

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

private:
	vector<PyramidBoxUI> m_uiBoxList;

};

