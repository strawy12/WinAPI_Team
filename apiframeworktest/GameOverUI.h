#pragma once
#include "Object.h"

class GameOverUI : public Object
{
public:
	GameOverUI();
	virtual ~GameOverUI();
	// Object��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	CLONE(GameOverUI)

private:
	class Image* m_pBGImage;
	BLENDFUNCTION m_bf;

};

