#pragma once
#include <windows.h>
#include "uiattribute.h"
#include "uitext.h"
#include <map>


class CDirectUIRect
{
public:
	CDirectUIRect();
	~CDirectUIRect();
public:
	//void SetCompatibleMainDC(HDC dc);
	void SetWidthHeight(int height, int width);
	void SetUIAttributeImg(DirectUIAttribute attribute, LPCTSTR filename);

	int GetWidth() const;
	int GetHeight() const;
public:
	void UpdateDC(DirectUIAttribute attribute);
	void UpdateDC(LPCTSTR bitmap_name);

	HDC GetDirectUIRectDC() const;

	void SetUserData(void* data);
	void* GetUserData();
protected:
	HDC m_DC;
	HBITMAP m_Bitmap;

	std::map<DirectUIAttribute, std::basic_string<TCHAR>> m_AttrMap;
	
	HDC m_MemoryDC;
	HDC m_OwnerDC;

	int m_Height;
	int m_Width;

	void* m_UserData;
};