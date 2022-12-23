#include "pch.h"
#include "Block.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Image.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "BlockMgr.h"

Block::Block(BOX_TYPE type) : Object()
{
	wstring imagePath[(UINT)BOX_TYPE::END] = { L"Image\\GFC.bmp", L"Image\\Hosic.bmp", L"Image\\kyochon.bmp", L"Image\\Pericana.bmp", L"Image\\Puradac.bmp" }; // 이미지 업로드
	m_pImage = ResMgr::GetInst()->ImgLoad(ToStringBoxType(type), imagePath[(int)type]); // 블록을 랜덤으로 출력

	m_blockType = type;
}
Block::~Block()
{

}

void Block::Update() {}

void Block::Render(HDC _dc)
{
	int Width = (int)m_pImage->GetWidth();
	int Height = (int)m_pImage->GetHeight();
	//SetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	TransparentBlt(_dc
		, (int)(vPos.x - (float)(Width * vScale.x / 2))
		, (int)(vPos.y - (float)(Height * vScale.y / 2))
		, Width * vScale.x, Height * vScale.y
		, m_pImage->GetDC()
		, 0, 0, Width, Height
		, RGB(255, 0, 255));

}