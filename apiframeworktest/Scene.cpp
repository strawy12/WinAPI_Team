#include "pch.h"
#include "Core.h"
#include "Scene.h"
#include "Object.h"

void Scene::Update()
{ 
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); j++)
		{
			if (!m_vecObj[i][j]->IsDead())
				m_vecObj[i][j]->Update();
		}
	}

	if (Core::GetInst()->m_CameraObject.GetIsShaking())
	{
		Core::GetInst()->m_CameraObject.CameraShake();
	}
}

void Scene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); j++)
		{
			m_vecObj[i][j]->FinalUpdate();
		}
	}
}

void Scene::Render(HDC hdc)
{
	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGHT;
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		vector<Object*>::iterator iter = m_vecObj[i].begin();
		for (; iter != m_vecObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->Render(hMemDC);
				iter++;
			}
			else
			{
				iter = m_vecObj[i].erase(iter);
			}
		}
	}

	Camera& cameraObject = Core::GetInst()->m_CameraObject;

	GdiTransparentBlt(hdc, 0 + Core::GetInst()->m_CameraObject.GetShakeNumber(), 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		Core::GetInst()->GetMainDC()
		, Core::GetInst()->m_CameraObject.GetLeft()
		, Core::GetInst()->m_CameraObject.GetTop()
		, Core::GetInst()->m_CameraObject.GetWidth()
		, Core::GetInst()->m_CameraObject.GetHeight()
		, RGB(255, 0, 255));
}

void Scene::DeleteGroup(GROUP_TYPE _eTarget)
{
	//for (size_t i = 0; i < m_vecObj[(UINT)_eTarget].size(); i++)
	//{
	//	delete m_vecObj[(UINT)_eTarget][i];
	//}
	//m_vecObj[(UINT)_eTarget].clear();
//	Safe_Delete_Vec(m_vecObj[(UINT)_eTarget]);
	Safe_Delete_Vec<Object*>(m_vecObj[(UINT)_eTarget]);

}

void Scene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

Scene::Scene()
{
}

Scene::~Scene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); j++)
		{
			delete m_vecObj[i][j];
		}
	}
}
