#include "uirect.h"
#include <vector>

CDirectUIRect::CDirectUIRect()
{
	m_DC = CreateCompatibleDC(NULL);
	m_MemoryDC = CreateCompatibleDC(NULL);
	CDCControl::GetDCControlInstance()->SwitchDCColorMode(CDCControl::color, m_DC, L"D:\\1.bmp");
	CDCControl::GetDCControlInstance()->SwitchDCColorMode(CDCControl::color, m_MemoryDC, L"D:\\1.bmp");
	SetStretchBltMode(m_DC, HALFTONE);
	m_Height = 0;
	m_Width = 0;
	m_UserData = 0;
}

CDirectUIRect::~CDirectUIRect()
{
	HBITMAP bitmap = (HBITMAP)GetCurrentObject(m_MemoryDC, OBJ_BITMAP);
	DeleteObject(m_Bitmap);
	DeleteObject(bitmap);
	DeleteDC(m_DC);
}

//void CDirectUIRect::SetCompatibleMainDC(HDC dc)
//{
//	m_OwnerDC = dc;
//}

void CDirectUIRect::SetWidthHeight(int height, int width)
{
	m_Bitmap = CreateCompatibleBitmap(m_DC, width, height);
	HBITMAP old_bitmap = (HBITMAP)SelectObject(m_DC, m_Bitmap);
	m_Height = height;
	m_Width = width;
	DeleteObject(old_bitmap);
}

void CDirectUIRect::SetUIAttributeImg(DirectUIAttribute attribute, LPCTSTR filename)
{
	std::basic_string<TCHAR> str = filename;
	m_AttrMap[attribute] = str;

}

int CDirectUIRect::GetWidth() const
{
	return m_Width;
}

int CDirectUIRect::GetHeight() const
{
	return m_Height;
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
	

	CDirectUIText text;
	text.SetDCBKColor(RGB(255, 255, 255));
	text.SetDirectUITextColor(RGB(255, 0, 0));
	text.SetDCHeight(50);
	text.SetDCWidth(200);
	text.SetText("ÄãºÃ");
	text.SetFontName("Î¢ÈíÑÅºÚ");
	text.UpdateDC();
	HDC dc2 = text.GetDirectUITextDC();

	/*bitmap = (HBITMAP)LoadImage(NULL, L"D:\\haha.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HDC dc = CreateCompatibleDC(0);

	SelectObject(dc, bitmap);*/

	CDCControl::colorrgb rgb;
	/*rgb.r = 164; rgb.g = 51; rgb.b = 39;
	CDCControl::GetDCControlInstance()->TransparentBitmapCopy(m_DC, dc, rgb, 0, 0, 100, 100, 0, 0);*/

	rgb.r = 255; rgb.g = 255; rgb.b = 255;
	CDCControl::GetDCControlInstance()->TransparentBitmapCopy(m_DC, dc2, rgb, 100, 100, 200, 50, 0, 0);


	//CDCControl::GetDCControlInstance()->WriteBmp(L"D:\\DCSavePart.bmp", dc);
	
	//CDCControl::GetDCControlInstance()->WriteBmp(L"D:\\DCSavePart.bmp", m_DC);
}

void CDirectUIRect::UpdateDC(LPCTSTR bitmap_name)
{
	HBITMAP bitmap = (HBITMAP)LoadImage(NULL, bitmap_name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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

HDC CDirectUIRect::GetDirectUIRectDC() const
{
	return m_DC;
}
