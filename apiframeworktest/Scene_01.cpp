#include "pch.h"
#include "Scene_01.h"
#include "KeyMgr.h"
#include "Block.h"
Scene_01::Scene_01()
{
}

Scene_01::~Scene_01()
{
}

void Scene_01::Enter()
{
    Object* pObj = new Block;
    AddObject(pObj, GROUP_TYPE::DEFAULT);
}

void Scene_01::Exit()
{
}

void Scene_01::Update()
{
	Scene::Update();
}
