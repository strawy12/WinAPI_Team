#pragma once
#include "Object.h"

struct InventoryBoxUI
{
	RECT rt;
	class Block* block;
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
	CLONE(InventoryUI)

public:
	void CreateBoxUI();
	void AddBlock(int idx, Block* block);
	void PtInBoxUI();
	void ResetBoxUI();

	bool AllUsedBlock()
	{
		for (auto boxUI : m_uiBoxList)
		{
			if (boxUI.block != nullptr)
			{
				return false;
			}
		}

		return true;
	}

private:
	Vec2 m_waitBoxScale;

	RECT m_padding;
	float m_spalling;

	vector<InventoryBoxUI> m_uiBoxList;
	POINT m_mousept;
	InventoryBoxUI* m_selectBoxUI;
	// 추후 이미지로 변경할 예정
};


