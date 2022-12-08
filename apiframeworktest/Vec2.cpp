#include "pch.h"
#include "Vec2.h"

Vec2::Vec2()
	: x(0.f)
	, y(0.f)
{
}

Vec2::~Vec2()
{
}

Vec2::Vec2(float _x, float _y)
	: x(_x)
	, y(_y)
{
}
Vec2::Vec2(int _x, int _y)
	: x((float)_x)
	, y((float)_y)
{
}

Vec2::Vec2(long _x, long _y)
	: x(_x)
	, y(_y)
{
}

Vec2::Vec2(const POINT _pt)
	: x((float)_pt.x)
	, y((float)_pt.y)
{
}

float Vec2::Length()
{
	return sqrt(x * x + y * y);
}

Vec2& Vec2::Normalize()
{
	float fLen = Length();
	assert(fLen != 0.f);
	x /= fLen;
	y /= fLen;
	return *this;
}


