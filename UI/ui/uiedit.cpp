#include "uiedit.h"
//static CDirectUIEdit* edit_copy = new CDirectUIEdit;

CDirectUIEdit::CDirectUIEdit()
{
	m_edit_copy = 0;
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

COLORREF CDirectUIEdit::GetEditBKColor()
{
	return m_cr_bk;
}

void CDirectUIEdit::SetEditTextColor(COLORREF cr)
{
	SetDirectUITextColor(cr);
}

COLORREF CDirectUIEdit::GetEditTextColor()
{
	return m_cr_text;
}

void CDirectUIEdit::SetEditFont(const LOGFONTW* font)
{
	SetDirectUITextFont(font);
}

const LOGFONTW * CDirectUIEdit::GetEditFont()
{
	return m_font;
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
	//这里加一个判断 防止用相同的参数多次绘制
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

	//DrawTextW(m_dc, m_string.data(), -1, &rc, DT_LEFT| DT_EDITCONTROL| DT_CALCRECT);//这行注释掉以后 下面的DrawTextW实际显示会不现实最后一行 只有把DT_EDITCONTROL去掉后才会正常显示

	std::wstring ws = L"123";
	GetLine(m_dc, ws, 50);

	DrawTextW(m_dc, m_string.data(), -1, &rc, DT_LEFT);

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

void CDirectUIEdit::SetScrollable()
{
	if (!m_edit_copy)
	{
		m_edit_copy = new CDirectUIEdit;
	}
}

void CDirectUIEdit::Scrollable(float height_top)
{
	if (m_edit_copy)
	{
		
		static SIZE str_size = { 0 };
		static RECT rc;
		static int max_copy_edit_dc_n;
		if (str_size.cx == 0 && str_size.cy == 0)
		{
			HFONT font = 0;
			font = CreateFontIndirectW(GetEditFont());
			HFONT old_font = (HFONT)SelectObject(m_edit_copy->GetDirectUIEditDC(), font);
			DeleteObject(old_font);

			GetTextExtentExPoint(m_dc, L"0", 1, 0, 0, 0, &str_size);
			
			


			
			//
			max_copy_edit_dc_n = ((int)(m_height / str_size.cy)*str_size.cy) + str_size.cy + str_size.cy;
			SetRect(&rc, 0, 0, m_width, max_copy_edit_dc_n);

			
			SetBkColor(m_edit_copy->GetDirectUIEditDC(), GetEditBKColor());
			SetTextColor(m_edit_copy->GetDirectUIEditDC(), GetEditTextColor());
			SetBkMode(m_edit_copy->GetDirectUIEditDC(), TRANSPARENT);
		}

		HBITMAP bitmap = CDCControl::GetDCControlInstance()->CreateCompatibleDCColorBitmapWith24Bits(m_edit_copy->GetDirectUIEditDC(), m_width, max_copy_edit_dc_n, CDCControl::colors::undefine, GetEditBKColor());
		HBITMAP old_bitmap = (HBITMAP)SelectObject(m_edit_copy->GetDirectUIEditDC(), bitmap);
		DeleteObject(old_bitmap);
		//
		int upper_pos = GetUpper(str_size.cy, height_top);
		int lower_pos = GetLower(str_size.cy, height_top + m_height);
		int line_start = upper_pos / str_size.cy;
		int line_end = (lower_pos / str_size.cy) - 1;
		int char_start = 0;
		int char_end = 0;

		int i = 0;
		std::unordered_map<int, int> umap;
		umap = GetLine(m_dc, m_string, m_width);
		while (i != line_start)
		{
			char_start = char_start + umap[i];
			i++;
		}
		char_end = char_start;
		while (i != line_end)
		{
			char_end = char_end + umap.at(i);
			i++;
		}
		char_end  = char_end + umap[i] - 1;
		std::wstring sub_wstr = m_string.substr(char_start, char_end - char_start + 1);

		DrawTextW(m_edit_copy->GetDirectUIEditDC(), sub_wstr.data(), -1, &rc, DT_LEFT);


		//截取
		if (upper_pos < 0)
		{
			upper_pos = 0;
		}
		int y1 = height_top - upper_pos;
		//int height = m_height;
		BitBlt(m_dc, 0, 0, m_width, m_height, m_edit_copy->GetDirectUIEditDC(), 0, y1, SRCCOPY);
		//CDCControl::GetDCControlInstance()->WriteBmp(L"D:\\copydc.bmp", m_edit_copy->GetDirectUIEditDC());

	}
}
std::unordered_map<int, int> GetLine(HDC dc, const std::wstring & str, int line_width)
{
	std::unordered_map<int, int> map;
	
	SIZE str_size = { 0 };
	/*wstr.at(0)*/
	int n_line = 0;
	int start = 0;
	//while()
	

	/*int dis_num = -1;
	while (dis_num != 0)
	{
		GetTextExtentExPoint(dc, str.data()+ start, lstrlen(str.data()+start), line_width, &dis_num, 0, &str_size);
		if (dis_num)
		{
			map.insert(std::make_pair<int,int>(n_line, dis_num));
		}
		start += dis_num;
		n_line++;
	}*/
	int dis_num = 1;
	while (str[start] != L'\0')
	{
		if (str[start] == L'\r' || str[start] == L'\n')
		{
			map.insert(std::make_pair<int, int>(n_line, dis_num));
			dis_num = 0;
			n_line++;
		}		
		dis_num++;
		start++;
	}
	return map;
}

int GetUpper(int height, float current_upper_pos)
{
	int upper = 0;
	while (upper < current_upper_pos)
	{
		upper += height;
	}
	upper -= height;
	return upper;
}

int GetLower(int height, float current_lower_pos)
{
	int upper = 0;
	while (upper < current_lower_pos)
	{
		upper += height;
	}
	return upper;
}
