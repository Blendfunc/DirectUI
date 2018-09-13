#include "uiedit.h"

CDirectUIEdit::CDirectUIEdit()
{
}

CDirectUIEdit::~CDirectUIEdit()
{
}

void CDirectUIEdit::SetClassNameType(DIRECTUITYPE type)
{
}

DIRECTUITYPE CDirectUIEdit::GetClassNameType()
{
	return DIRECTUI_EDIT;
}

void CDirectUIEdit::Add(wchar_t wchar)
{
	m_edit_wstring += wchar;

	m_string = m_edit_wstring;

}

void CDirectUIEdit::Delete()
{
}

void CDirectUIEdit::SetEditHeight(int height)
{
	SetDCHeight(height);
}

int CDirectUIEdit::GetEditHeight()
{
	return GetDirectUITextDCHeight();
}

int CDirectUIEdit::GetEditWidth()
{
	return GetDirectUITextDCWidth();
}

void CDirectUIEdit::SetEditWidth(int width)
{
	SetDCWidth(width);
}

void CDirectUIEdit::SetEditBKColor(COLORREF cr)
{
	SetDCBKColor(cr);
}

void CDirectUIEdit::SetEditTextColor(COLORREF cr)
{
	SetDirectUITextColor(cr);
}

void CDirectUIEdit::SetEditFont(int i)
{
	SetDirectUITextFont(i);
}

void CDirectUIEdit::SetEditFontHeight(int height)
{
	SetFontHeight(height);
}

void CDirectUIEdit::SetEditFontWidth(int width)
{
	SetFontWidth(width);
}

void CDirectUIEdit::UpdateEditDC()
{
	UpdateDC();
}

void CDirectUIEdit::SetXPosition(int x)
{
	m_x = x;
}

int CDirectUIEdit::GetXPosition()
{
	return m_x;
}

void CDirectUIEdit::SetYPosition(int y)
{
	m_y = y;
}

int CDirectUIEdit::GetYPosition()
{
	return m_y;
}

HDC CDirectUIEdit::GetDirectUIEditDC()
{
	return GetDirectUITextDC();
}
