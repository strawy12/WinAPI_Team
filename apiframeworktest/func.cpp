#include "pch.h"
#include "func.h"
#include "EventMgr.h"
void CreateObject(Object* _pObj, GROUP_TYPE _eGroup) // Instantiate
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;
	
	EventMgr::GetInst()->AddEvent(evn);
}

void DeleteObject(Object* _pObj) // Destroy
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	EventMgr::GetInst()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _eNext) 
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext;

	EventMgr::GetInst()->AddEvent(evn);
}

wstring ToStringMonterType(MONSTER_TYPE type)
{
	switch (type)
	{
	case MONSTER_TYPE::MUSHROOM:
		return  L"MUSHROOM";
	case MONSTER_TYPE::OCTOPUS:
		return  L"OCTOPUS";

	case MONSTER_TYPE::PENGUIN:
		return  L"PENGUIN";

	case MONSTER_TYPE::PINKBEEN:
		return  L"PINKBEEN";

	case MONSTER_TYPE::SSLIME:
		return  L"SSLIME";

	default:
		break;
	}
}
