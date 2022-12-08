#pragma once
#include "framework.h"
#include "define.h"
#include "BWindow.h"
class Core
	: public BWindow
{
public:
//	SINGLE(Core);
public:
	static Core* GetInst()
	{
		static Core core;
		return &core;
	}
private:
	Core();
	~Core();
private:
	POINT						m_ptResolution; // 메인 윈도우 해상도
	HDC							m_hDC;   // 메인 윈도우에 Draw할 DC
	HBITMAP						m_hBit;	 //사본용 비트맵
	HDC							m_memDC; // 사본용 DC

	// 자주 사용하는 GDI(Graphic Device Interface) Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

public:
	const HWND& GetWndHandle() { return m_hWnd; }
	const POINT& GetResolution() { return m_ptResolution; }
	const HDC& GetMainDC() { return m_hDC; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Progress();
private:
	void Update();
	void Render();
	void CreateBrushPen();
};

