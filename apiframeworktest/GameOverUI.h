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

public:
	void BGRender(HDC hdc) ;
	void TitleRender(HDC hdc) ;
	void BoxCountTextRender(HDC hdc);
	void PlayTimeTextRender(HDC hdc);
	void TitleBtnRender(HDC hdc);

private:
	class Image* m_pBGImage;
	class Image* m_pTitleBtnImage;
	BLENDFUNCTION m_bf;
	RECT m_titleBtnRect;

};

