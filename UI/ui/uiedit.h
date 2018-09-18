#pragma once
#include "uitype.h"
#include "uitext.h"
#include <unordered_map>

extern std::unordered_map<int, int> GetLine(HDC dc, const std::wstring& str, int line_widthx);

extern int GetUpper(int height, float current_upper_pos);

extern int GetLower(int height, float current_lower_pos);

extern class CDirectUIEdit;

class IDirectUIEditCallBack
{
public:
	enum result
	{
		DONOTHING = 0 ,
		CONTINUE = 1,
		DONOTPAINT = 2
	};
	virtual result OnGetUnicodeChar(CDirectUIEdit* edit, wchar_t(*chars)[2]) = 0;




};


class CDirectUIEdit : public CDirectUIBase , protected CDirectUIText
{
public:
	CDirectUIEdit();
	~CDirectUIEdit();

	wchar_t edit_char[2];

	virtual void SetClassNameType(DIRECTUITYPE type) override;

	virtual DIRECTUITYPE GetClassNameType() override;


	void Add(wchar_t wchar);

	void Delete();

	void SetEditHeight(int height);

	int GetEditHeight();

	int GetEditWidth();

	void SetEditWidth(int width);

	void SetEditBKColor(COLORREF cr);

	COLORREF GetEditBKColor();

	void SetEditTextColor(COLORREF cr);

	COLORREF GetEditTextColor();

	void SetEditFont(const LOGFONTW* font);

	const LOGFONTW* GetEditFont();


	void SetEditFontHeight(int height);

	void SetEditFontWidth(int width);

	void UpdateEditDC();

	void SetXPosition(int x);

	int GetXPosition();

	void SetYPosition(int y);

	int GetYPosition();


	HDC GetDirectUIEditDC();

	void SetScrollable();

	void Scrollable(float height_top);

	//void 
private:
	std::wstring m_edit_wstring;
	int m_x;
	int m_y;
	CDirectUIEdit* m_edit_copy;
};
