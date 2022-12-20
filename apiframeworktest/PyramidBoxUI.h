#pragma once
#include "BoxUI.h"
class PyramidBoxUI : public BoxUI
{
public:
	PyramidBoxUI(int left, int right);
	virtual ~PyramidBoxUI();

	virtual void Render(HDC hdc) override;

public:
	bool IsSelectable()
	{
		if (m_isSelectable == true && m_block == nullptr)
		{
			return true;
		}
		else return false;
	}

	int GetLeft() { return m_left; }
	int GetRight() { return m_right; }

	void SetLeft(int left) { m_left = left; }
	void SetRight(int right) { m_right = right; }
	void SetIsSelectable(bool isSelectable) { m_isSelectable = isSelectable; }

private:
	bool m_isSelectable;
	int m_left; 
	int m_right;
};

