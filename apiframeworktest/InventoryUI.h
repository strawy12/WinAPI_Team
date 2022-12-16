#pragma once
#include "Object.h"

class InventoryUI : public Object
{
public:
	InventoryUI();
	virtual ~InventoryUI();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	CLONE(InventoryUI)

public:
	void CreateBoxUI();
	void AddBlock(int idx, Block* block);
	void PtInBoxUI();

private:
	Vec2 vScale;
	RECT m_padding;
	float m_spalling;

	vector<InventoryBoxUI> m_uiBoxVec;
	POINT m_mousept;
	InventoryBoxUI* m_selectBoxUI;
	// ���� �̹����� ������ ����
};


