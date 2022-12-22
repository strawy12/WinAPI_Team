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
	//int width = SCREEN_WIDTH;
	//int height = SCREEN_HEIGHT;
	//HDC hMemDC = CreateCompatibleDC(hdc);
	//HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height);
	//HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		vector<Object*>::iterator iter = m_vecObj[i].begin();
		for (; iter != m_vecObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->Render(hdc);
				iter++;
			}
			else
			{
				iter = m_vecObj[i].erase(iter);
			}
		}
	}


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
			if (m_vecObj[i][j])
			{
				//delete m_vecObj[i][j];
			}
		}
	}
}
