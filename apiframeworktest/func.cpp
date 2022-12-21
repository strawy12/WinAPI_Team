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

wstring ToStringBoxType(BOX_TYPE type)
{
	switch (type)
	{
	case BOX_TYPE::HOSIC:
		return  L"HOSIC";
	case BOX_TYPE::KYOCHON:
		return  L"KYOCHON";

	case BOX_TYPE::PERICANA:
		return  L"PERICANA";

	case BOX_TYPE::PURADAC:
		return  L"PURADAC";

	case BOX_TYPE::GFC:
		return  L"GFC";

	default:
		break;
	}
}
