#pragma once
#include "windows.h"
#include <string>
#include <vector>
#include "dc_control.hpp"

struct directuifont
{
	LOGFONTA lfa;
	TEXTMETRICA tma;
	DWORD dw_font_type;
};



class CDirectUIText
{
public:
	CDirectUIText();
	~CDirectUIText();
	static void GetFonts();
	static std::vector<directuifont> vt_font;

	//void SetTextColor();

	void SetText(LPCSTR text);

	void SetDCHeight(int height);

	void SetDCWidth(int width);

	void SetDCBKColor(COLORREF cr);

	void SetDirectUITextColor(COLORREF cr);

	void SetFontName(LPCSTR font);


	COLORREF GetTextDCBKColor();

	void UpdateDC();

	HDC GetDirectUITextDC();

protected:
	HDC m_dc;
	int m_height;
	int m_width;
	std::string m_string;
	std::string m_font_name;
	COLORREF m_cr_bk;
	COLORREF m_cr_text;




};
