#pragma once
#include "Scene.h"
class Image;

class Scene_01 :
    public Scene
{
private:
    Image* m_pBGImage;

public:
    Scene_01();
    virtual ~Scene_01();
public:
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Render(HDC hdc) override;
};

