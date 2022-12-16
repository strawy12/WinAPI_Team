#pragma once
#include "Object.h"

class Block;
struct InventoryBoxUI
{
	RECT rt;
	Block* block;
	bool isClick;
};

class InventoryUI : public Object
{
public:
	InventoryUI();
	virtual ~InventoryUI();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override; 
	InventoryUI* Clone() { return new InventoryUI(*this); }

public:
	void CreateBoxUI();
	void AddBlock(int idx, Block* block);
	void PtInBoxUI();

private:
	Vec2 m_BGSize;
	RECT m_padding;
	float m_spalling;

	vector<InventoryBoxUI> m_uiBoxVec;
	POINT m_mousept;
	InventoryBoxUI* m_selectBoxUI;
	// 추후 이미지로 변경할 예정
};


