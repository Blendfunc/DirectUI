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

void CDirectUIEdit::SetEditFont(const LOGFONTW* font)
{
	SetDirectUITextFont(font);
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
	/*UpdateDC();*/
	HBITMAP bitmap = CDCControl::GetDCControlInstance()->CreateCompatibleDCColorBitmapWith24Bits(m_dc, m_width, m_height, CDCControl::colors::undefine, m_cr_bk);
	HBITMAP old_bitmap = (HBITMAP)SelectObject(m_dc, bitmap);
	DeleteObject(old_bitmap);
	SetBkColor(m_dc, m_cr_bk);
	SetTextColor(m_dc, m_cr_text);
	SetBkMode(m_dc, TRANSPARENT);
	HFONT font = 0;

	//int i = 0;
	//for (auto iter = CDirectUIText::vt_font.begin(); iter != CDirectUIText::vt_font.end(); iter++)
	//{
	//	if (m_font_name == iter->lfa.lfFaceName)
	//	{
	//		iter->lfa.lfQuality = ANTIALIASED_QUALITY;
	//		//iter->lfa.lfWeight = FW_BLACK;
	//		//iter->lfa.lfWidth = m_font_width;
	//		//iter->lfa.lfHeight = m_font_height;
	//		font = CreateFontIndirectA(&iter->lfa);			
	//		break;
	//	}
	//	i++;
	//}
	//PROOF_QUALITY
	//vt_font.at(m_i_font).lfa.lfQuality = NONANTIALIASED_QUALITY;
	font = CreateFontIndirectW(m_font);
	//static int lfheight = 20;
	//vt_font.at(300).lfa.lfWidth = 0;
	//vt_font.at(300).lfa.lfHeight = lfheight;
	//vt_font.at(300).lfa.lfHeight = lfheight;





	HFONT old_font = (HFONT)SelectObject(m_dc, font);
	DeleteObject(old_font);
	RECT rc;
	SetRect(&rc, 0, 0, m_width, m_height);

	DrawTextW(m_dc, m_string.data(), -1, &rc, DT_LEFT| DT_EDITCONTROL| DT_CALCRECT);
	
	
	DrawTextW(m_dc, m_string.data(), -1, &rc, DT_LEFT | DT_EDITCONTROL);

	//CDCControl::GetDCControlInstance()->WriteBmp(L"E:\\m_dc.bmp", m_dc);
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
