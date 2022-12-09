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
	CLONE(InventoryUI);

private:
	Vec2 m_BGSize;
	RECT m_padding;
	float m_spalling;
	// 추후 이미지로 변경할 예정
};


