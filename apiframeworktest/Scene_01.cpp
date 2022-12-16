#include "pch.h"
#include "Scene_01.h"
#include "KeyMgr.h"
#include "InventoryUI.h"
#include "PyramidUI.h"
Scene_01::Scene_01()
{
}

Scene_01::~Scene_01()
{
}

void Scene_01::Enter()
{
    Object* pObj = new PyramidUI;
    pObj->Init();   
    CreateObject(pObj, GROUP_TYPE::UI);
}

void Scene_01::Exit()
{
}

void Scene_01::Update()
{
	Scene::Update();
}
