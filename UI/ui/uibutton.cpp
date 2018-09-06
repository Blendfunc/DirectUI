#include "uibutton.h"

//void CDirectUIButton::SetDirectUIButtonHeightWidth(int height, int width)
//{
//	m_Rect.SetWidthHeight(height, width);
//}

CDirectUIButton::CDirectUIButton()
{
	m_callback = 0;
}

CDirectUIButton::~CDirectUIButton()
{
}

IDirectUIButtonUICallBack * CDirectUIButton::GetEventCallBack()
{
	return m_callback;
}

void CDirectUIButton::SetEventCallBack(IDirectUIButtonUICallBack * callback)
{
	m_callback = callback;
}

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

const CDirectUIText * CDirectUIButton::GetDirectUIButtonText()
{
	return &m_Text;
}

void CDirectUIButton::UpdateDirectUIButtonDC()
{
	m_Rect.UpdateDC();
	m_Text.UpdateDC();
	COLORREF cr = m_Text.GetTextDCBKColor();
	CDCControl::colorrgb rgb;
	rgb.b = GetBValue(cr);
	rgb.g = GetGValue(cr);
	rgb.r = GetRValue(cr);

	CDCControl::GetDCControlInstance()->TransparentBitmapCopy(m_Rect.GetDirectUIRectDC(),
		m_Text.GetDirectUITextDC(),
		rgb,
		0,
		0,
		m_Text.GetDirectUITextDCWidth(),
		m_Text.GetDirectUITextDCHeight(),
		0,
		0);




}
