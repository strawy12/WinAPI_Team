#pragma once
#include "Object.h"

class Image;
class Block;

class BoxUI : public Object
{
public:
	BoxUI();
	virtual ~BoxUI();

public:
	virtual void Update() override;
	CLONE(BoxUI)
	virtual void Render(HDC hdc) override;

public:
	void OutlineRender(HDC hdc);
	void BackgroundRender(HDC hdc);

	const RECT& GetRect() { return m_rt; }
	Block* GetBlock() { return m_block; }
	MONSTER_TYPE GetBlockType();

	void SetBlock(Block* block) { m_block = block; }
	void SetRect(RECT& rt) { m_rt = rt; }

protected:
	Image* m_pBGImage;
	Image* m_pOutLineImage;

	RECT m_rt;
	class Block* m_block;

	BLENDFUNCTION m_bf;
};

