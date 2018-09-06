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
	m_Bitmap = 0;
	m_current_attribute = DirectUIAttribute::DUI_MOUSE_REMAINON;
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

void CDirectUIRect::SetWidth(int width)
{
//	m_Bitmap = CreateCompatibleBitmap(m_DC, width, height);
//	HBITMAP old_bitmap = (HBITMAP)SelectObject(m_DC, m_Bitmap);
//	m_Height = height;
	m_Width = width;
//	DeleteObject(old_bitmap);
}

void CDirectUIRect::SetHeight(int height)
{
	m_Height = height;
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

void CDirectUIRect::UpdateDC()
{
	m_Bitmap = CreateCompatibleBitmap(m_DC, m_Width, m_Height);
	HBITMAP old_bitmap = (HBITMAP)SelectObject(m_DC, m_Bitmap);
	DeleteObject(old_bitmap);
	//HBITMAP bitmap = LoadBitmap(NULL, m_AttrMap.at(attribute).c_str());
	HBITMAP bitmap = (HBITMAP)LoadImage(NULL, m_AttrMap.at(m_current_attribute).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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
	
	
	//»æÖÆÎÄ×Ö

	/*CDirectUIText text;
	text.SetDCBKColor(RGB(0, 0, 0));
	text.SetDirectUITextColor(RGB(255, 0, 0));
	text.SetDCHeight(50);
	text.SetDCWidth(200);
	text.SetText("ÄãºÃ123456789");
	text.SetFontName("Ó×Ô²");
	text.UpdateDC();
	HDC dc2 = text.GetDirectUITextDC();*/



	//HFONT font = 0;
	//SetBkMode(m_DC, TRANSPARENT);
	//SetTextColor(m_DC, RGB(255, 0, 0));
	//for (auto iter = CDirectUIText::vt_font.begin(); iter != CDirectUIText::vt_font.end(); iter++)
	//{
	//	//strcmp(iter->lfa.lfFaceName, "Ó×Ô²") == 0
	//	if (strcmp(iter->lfa.lfFaceName, "Ó×Ô²") == 0)
	//	{
	//		iter->lfa.lfQuality = ANTIALIASED_QUALITY;
	//		iter->lfa.lfWeight = FW_BLACK;
	//		iter->lfa.lfHeight = 20;
	//		iter->lfa.lfWidth = 5;
	//		font = CreateFontIndirectA(&iter->lfa);
	//		break;
	//	}
	//}
	//SelectObject(m_DC, font);
	//RECT rc;
	//SetRect(&rc, 0, 0, 300, 150);
	//DrawTextA(m_DC, "ÄãºÃ123456789", -1, &rc, DT_LEFT);



	/*bitmap = (HBITMAP)LoadImage(NULL, L"D:\\haha.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HDC dc = CreateCompatibleDC(0);

	SelectObject(dc, bitmap);*/

	/*CDCControl::colorrgb rgb;*/
	/*rgb.r = 164; rgb.g = 51; rgb.b = 39;
	CDCControl::GetDCControlInstance()->TransparentBitmapCopy(m_DC, dc, rgb, 0, 0, 100, 100, 0, 0);*/

	/*rgb.r = 0; rgb.g = 0; rgb.b = 0;
	CDCControl::GetDCControlInstance()->TransparentBitmapCopy(m_DC, dc2, rgb, 0, 0, 200, 50, 0, 0);*/


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

void CDirectUIRect::SetCurrentAttribute(DirectUIAttribute attribute)
{
	m_current_attribute = attribute;
}
