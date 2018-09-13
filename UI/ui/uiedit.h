#pragma once
#include "uitype.h"
#include "uitext.h"

class CDirectUIEdit;

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

	virtual void SetClassNameType(DIRECTUITYPE type);

	virtual DIRECTUITYPE GetClassNameType();


	void Add(wchar_t wchar);

	void Delete();

	void SetEditHeight(int height);

	int GetEditHeight();

	int GetEditWidth();

	void SetEditWidth(int width);

	void SetEditBKColor(COLORREF cr);

	void SetEditTextColor(COLORREF cr);

	void SetEditFont(int i);

	void SetEditFontHeight(int height);

	void SetEditFontWidth(int width);

	void UpdateEditDC();

	void SetXPosition(int x);

	int GetXPosition();

	void SetYPosition(int y);

	int GetYPosition();


	HDC GetDirectUIEditDC();

private:
	std::wstring m_edit_wstring;
	int m_x;
	int m_y;

};
