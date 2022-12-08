#pragma once
#include "define.h"
#include <map>
struct tKeyInfo
{
//	KEY			eKey;  인덱스가 곧 키 값임.
	KEY_STATE	eState; // 키의 상태값
	bool		bPrevCheck; // 이전 프레임에서 눌렸는지 여부
};
class KeyMgr
{
public:
	SINGLE(KeyMgr);
private:
	KeyMgr();
	~KeyMgr();
private:
	vector<tKeyInfo> m_vecKey;
	map<int, bool> m_mapKey;
public:
	void Init();
	void Update();
	KEY_STATE	GetKey(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }
};

