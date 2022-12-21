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

wstring ToStringMonterType(BOX_TYPE type)
{
	switch (type)
	{
	case BOX_TYPE::GFC:
		return  L"MUSHROOM";
	case BOX_TYPE::HOSIC:
		return  L"OCTOPUS";

	case BOX_TYPE::KYOCHON:
		return  L"PENGUIN";

	case BOX_TYPE::PERICANA:
		return  L"PINKBEEN";

	case BOX_TYPE::PURADAC:
		return  L"SSLIME";

	default:
		break;
	}
}

wstring s2ws(const string& s)
{
	int len;
	int slength = static_cast<int>(s.length()) + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];

	::MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	wstring ret(buf);
	delete[] buf;

	return ret;
}

string ws2s(const wstring& ws)
{
	int len;
	int slength = static_cast<int>(ws.length()) + 1;
	len = WideCharToMultiByte(CP_ACP, 0, ws.c_str(), slength, 0, 0, 0, 0);
	string ret(len, '\0');
	WideCharToMultiByte(CP_ACP, 0, ws.c_str(), slength, &ret[0], len, 0, 0);

	return ret;
}