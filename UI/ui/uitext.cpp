#include "uitext.h"
#include <fstream>
#include <string>

std::string GetCharSet(BYTE b);

std::vector<directuifont> CDirectUIText::vt_font;

int CALLBACK EnumFontFamExProc(const LOGFONTA* lpelfe, const TEXTMETRICA* lpntme, DWORD FontType, LPARAM lParam)
{


	/*::MessageBox(0, L"", L"", 0);*/
	//OutputDebugStringA(lpelfe->lfFaceName);
	//OutputDebugStringA(L"\n");

	std::ofstream ofile;
	ofile.open("c:\\font.txt", std::ios::app | std::ios::out);
	
	char chl[33];

	ofile << "字体名称：" << lpelfe->lfFaceName << "  ";//<< "\n" << std::flush;//std::endl

	ofile << "字符高度：" << ltoa(lpelfe->lfHeight, chl, 10) << "  ";
	
	ofile << "字体中字符的平均宽度：" << ltoa(lpelfe->lfWidth, chl, 10) << "  ";
	
	ofile << "角度：" << ltoa(lpelfe->lfEscapement, chl, 10) << "  ";

	ofile << "角度：" << ltoa(lpelfe->lfOrientation, chl, 10) << "  ";

	ofile << "权重：" << ltoa(lpelfe->lfWeight, chl, 10) << "  ";

	const char* ch = lpelfe->lfItalic == 0 ? "否  " : "是  ";

	ofile << "是否斜体：" << ch;

	ch = lpelfe->lfUnderline == 0 ? "否  " : "是  ";

	ofile << "是否带下划线：" << ch;

	ch = lpelfe->lfStrikeOut == 0 ? "否  " : "是  ";

	ofile << "是否带删除线：" << ch;

	ofile << "字符集：" << GetCharSet(lpelfe->lfCharSet) << "  ";
///
	ofile << "字符高度：" << ltoa(lpntme->tmHeight, chl, 10) << "  ";

	ofile << "字符的上升：" << ltoa(lpntme->tmAscent, chl, 10) << "  ";

	ofile << "字符的下降：" << ltoa(lpntme->tmDescent, chl, 10) << "  ";

	ofile << "tmHeight成员设置的边界内的前导（空格）量：" << ltoa(lpntme->tmInternalLeading, chl, 10) << "  ";

	ofile << "应用程序在行之间添加的额外前导（空格）量：" << ltoa(lpntme->tmExternalLeading, chl, 10) << "  ";

	ofile << "字体中字符的平均宽度：" << ltoa(lpntme->tmAveCharWidth, chl, 10) << "  ";

	ofile << "字体中最宽字符的宽度：" << ltoa(lpntme->tmMaxCharWidth, chl, 10) << "  ";

	ofile << "字体的重量：" << ltoa(lpntme->tmWeight, chl, 10) << "  ";



	ofile << "\n" << std::flush;

	ofile.close();
	
	directuifont df;
	CDirectUIText::vt_font.push_back(df);
	memcpy(&CDirectUIText::vt_font.back().lfa, lpelfe, sizeof(LOGFONTA));
	memcpy(&CDirectUIText::vt_font.back().tma, lpntme, sizeof(TEXTMETRICA));
	CDirectUIText::vt_font.back().dw_font_type = FontType;
	return 1;
}

std::string GetCharSet(BYTE b)
{
	std::string r;
	switch (b)
	{
	case ANSI_CHARSET :
	{
		r = "ANSI_CHARSET";
	}
	break;
	case BALTIC_CHARSET:
	{
		r = "BALTIC_CHARSET";
	}
	break;
	case CHINESEBIG5_CHARSET:
	{
		r = "CHINESEBIG5_CHARSET";
	}
	break;
	case DEFAULT_CHARSET:
	{
		r = "DEFAULT_CHARSET";
	}
	break;
	case EASTEUROPE_CHARSET:
	{
		r = "EASTEUROPE_CHARSET";
	}
	break;
	case GB2312_CHARSET:
	{
		r = "GB2312_CHARSET";
	}
	break;
	case GREEK_CHARSET:
	{
		r = "GREEK_CHARSET";
	}
	break;
	case HANGUL_CHARSET:
	{
		r = "HANGUL_CHARSET";
	}
	break;
	case MAC_CHARSET:
	{
		r = "MAC_CHARSET";
	}
	break;
	case OEM_CHARSET:
	{
		r = "OEM_CHARSET";
	}
	break;
	case RUSSIAN_CHARSET:
	{
		r = "RUSSIAN_CHARSET";
	}
	break;
	case SHIFTJIS_CHARSET:
	{
		r = "SHIFTJIS_CHARSET";
	}
	break;
	case SYMBOL_CHARSET:
	{
		r = "SYMBOL_CHARSET";
	}
	break;
	case TURKISH_CHARSET:
	{
		r = "TURKISH_CHARSET";
	}
	break;
	case VIETNAMESE_CHARSET:
	{
		r = "VIETNAMESE_CHARSET";
	}
	break;
	}
	return r;
}





CDirectUIText::CDirectUIText()
{
	m_dc = CreateCompatibleDC(NULL);
	CDCControl::GetDCControlInstance()->SwitchDCColorMode(CDCControl::color, m_dc, 0);
	m_height = 1;
	m_width = 1;
	m_cr_bk = RGB(255, 255, 255);
	m_cr_text = RGB(0, 0, 0);


}

CDirectUIText::~CDirectUIText()
{

	HBITMAP bitmap = (HBITMAP)GetCurrentObject(m_dc, OBJ_BITMAP);
	DeleteObject(bitmap);
	HFONT font = (HFONT)GetCurrentObject(m_dc, OBJ_FONT);
	DeleteObject(font);
	DeleteDC(m_dc);

}

void CDirectUIText::GetFonts()
{
	LOGFONTA lf;
	//memset(&lf, 0, sizeof(LOGFONT));
	lf.lfCharSet = DEFAULT_CHARSET;
	//lstrcpyW(lf.lfFaceName, L'\0');

	lf.lfFaceName[0] = '\0';

	lf.lfPitchAndFamily = 0;
	
	HWND hw = 0;
	HDC hdc = GetDC(hw);

	int i = EnumFontFamiliesExA(hdc, &lf, EnumFontFamExProc, 0, 0);

	ReleaseDC(hw, hdc);
	//int j = EnumFontFamiliesEx(hdc, &lf, EnumFontFamExProc, 0, 0);


}

void CDirectUIText::SetText(LPCSTR text)
{
	m_string = text;
}

void CDirectUIText::SetDCHeight(int height)
{
	m_height = height;
}

void CDirectUIText::SetDCWidth(int width)
{
	m_width = width;
}

void CDirectUIText::SetDCBKColor(COLORREF cr)
{
	m_cr_bk = cr;
}

void CDirectUIText::SetDirectUITextColor(COLORREF cr)
{
	m_cr_text = cr;
}

void CDirectUIText::SetFontName(LPCSTR font)
{
	m_font_name = font;
}

void CDirectUIText::UpdateDC()
{
	HBITMAP bitmap = CDCControl::GetDCControlInstance()->CreateCompatibleDCColorBitmapWith24Bits(m_dc, m_width, m_height, CDCControl::colors::undefine, m_cr_bk);
	HBITMAP old_bitmap = (HBITMAP)SelectObject(m_dc, bitmap);
	DeleteObject(old_bitmap);
	SetBkColor(m_dc, m_cr_bk);
	SetTextColor(m_dc, m_cr_text);
	HFONT font = 0;


	for (auto iter = CDirectUIText::vt_font.begin(); iter != CDirectUIText::vt_font.end(); iter++)
	{
		if (m_font_name == iter->lfa.lfFaceName)
		{
			font = CreateFontIndirectA(&iter->lfa);
			break;
		}
	}

	HFONT old_font = (HFONT)SelectObject(m_dc, font);
	DeleteObject(old_font);
	RECT rc;
	SetRect(&rc, 0, 0, m_width, m_height);
	DrawTextA(m_dc, m_string.data(), -1, &rc, DT_LEFT);

}

HDC CDirectUIText::GetDirectUITextDC()
{
	return m_dc;
}
