#pragma once
#include <windows.h>
#include "uiattribute.h"

#include <map>

class CDirectUIRect
{
public:
	CDirectUIRect();
	~CDirectUIRect();
public:
	void SetOwnerDC(HDC dc);
	void SetWidthHeight(int height, int width);
	void SetUIAttributeImg(DirectUIAttribute attribute, LPCTSTR filename);

	void UpdateDC(DirectUIAttribute attribute);

	HDC GetDirectUIRectDC();
private:
	HDC m_DC;
	HBITMAP m_Bitmap;

	std::map<DirectUIAttribute, std::basic_string<TCHAR>> m_AttrMap;
	
	HDC m_MemoryDC;
	HDC m_OwnerDC;

	int m_Height;
	int m_Width;
};