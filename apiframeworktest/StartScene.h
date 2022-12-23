#pragma once

#include"Scene.h"

class StartScene : public Scene
{
public:
	StartScene();
	virtual ~StartScene();

public:
	void	Enter() override;
	virtual void Exit() override;
	void	Update() override;
	void	Render(HDC hdc)override;

private:
	class Image* m_ImageBG;
	class Image* m_ImageStart;
	class Image* m_ImageLogo;
	POINT m_StartPos;
	RECT m_StartRect;

};

