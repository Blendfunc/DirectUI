#include "uibutton.h"

//void CDirectUIButton::SetDirectUIButtonHeightWidth(int height, int width)
//{
//	m_Rect.SetWidthHeight(height, width);
//}

void CDirectUIButton::SetClassNameType(DIRECTUITYPE type)
{
}

DIRECTUITYPE CDirectUIButton::GetClassNameType()
{
	return  DIRECTUI_BUTTON;
}

void CDirectUIButton::SetXPosition(int x)
{
	m_x = x;
}

int CDirectUIButton::GetXPosition()
{
	return m_x;
}

void CDirectUIButton::SetYPosition(int y)
{
	m_y = y;
}

int CDirectUIButton::GetYPosition()
{
	return m_y;
}

const CDirectUIRect * CDirectUIButton::GetDirectUIButtonRect()
{
	return &m_Rect;
}
