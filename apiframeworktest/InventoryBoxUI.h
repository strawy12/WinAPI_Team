#pragma once
#include "BoxUI.h"
class InventoryBoxUI : public BoxUI
{
public:
	InventoryBoxUI();
	virtual ~InventoryBoxUI();

	virtual void Render(HDC hdc) override;
	
	void SetIsClick(bool isClick) { m_isClick = isClick; }
	bool GetIsClick() { return m_isClick; }

private:
	bool m_isClick;
};

