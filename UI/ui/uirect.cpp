#include "uirect.h"

CDirectUIRect::CDirectUIRect()
{
	m_DC = CreateCompatibleDC(NULL);
	m_MemoryDC = CreateCompatibleDC(NULL);
	m_Height = 0;
	m_Width = 0;
}

CDirectUIRect::~CDirectUIRect()
{
	HBITMAP bitmap = (HBITMAP)GetCurrentObject(m_MemoryDC, OBJ_BITMAP);
	DeleteObject(m_Bitmap);
	DeleteObject(bitmap);
	DeleteDC(m_DC);
}

void CDirectUIRect::SetOwnerDC(HDC dc)
{
	m_OwnerDC = dc;
}

void CDirectUIRect::SetWidthHeight(int height, int width)
{
	m_Bitmap = CreateCompatibleBitmap(m_OwnerDC, width, height);
	SelectObject(m_DC, m_Bitmap);
	m_Height = height;
	m_Width = width;
}

void CDirectUIRect::SetUIAttributeImg(DirectUIAttribute attribute, LPCTSTR filename)
{
	std::basic_string<TCHAR> str = filename;
	m_AttrMap[attribute] = str;

}

void CDirectUIRect::UpdateDC(DirectUIAttribute attribute)
{
	
	//HBITMAP bitmap = LoadBitmap(NULL, m_AttrMap.at(attribute).c_str());
	HBITMAP bitmap = (HBITMAP)LoadImage(NULL, m_AttrMap.at(attribute).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(m_MemoryDC, bitmap);
	BITMAP bitmapInfo;
	memset(&bitmapInfo, 0, sizeof(BITMAP));
	int result = GetObject(bitmap, sizeof(BITMAP), &bitmapInfo);
	if (result == 0)
	{
		MessageBox(0, L"", L"", 0);
	}
	DeleteObject(oldBitmap);
	StretchBlt(m_DC, 0, 0, m_Width, m_Height, m_MemoryDC, 0, 0, bitmapInfo.bmWidth, bitmapInfo.bmHeight, SRCCOPY);
	
}

HDC CDirectUIRect::GetDirectUIRectDC()
{
	return m_DC;
}
