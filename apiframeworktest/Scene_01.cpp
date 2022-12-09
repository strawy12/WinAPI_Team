#include "pch.h"
#include "Scene_01.h"
#include "KeyMgr.h"
#include "InventoryUI.h"
Scene_01::Scene_01()
{
}

Scene_01::~Scene_01()
{
}

void Scene_01::Enter()
{
    Object* pObj = new InventoryUI;
    pObj->Init();
    AddObject(pObj, GROUP_TYPE::UI);
}

void Scene_01::Exit()
{
}

void Scene_01::Update()
{
	Scene::Update();
}
