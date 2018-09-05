#include "windows.h"
#include <vector>

#ifdef UNICODE  
#ifndef TSTRING  
#define TSTRING std::wstring  
#endif  
#else  
#ifndef TSTRING  
#define TSTRING std::string  
#endif  
#endif 


class CDCControl
{
public:
	enum color_mode
	{
		monochrome = 0,
		color = 1
	};
	enum colors
	{
		undefine = -1,
		red = 0,
		white = 1,
		black = 2,
		blue = 3
	};
	struct colorrgb
	{
		unsigned char r;	
		unsigned char g; 
		unsigned char b;
	};
	static CDCControl* GetDCControlInstance()
	{
		if (*GetStaticDCControl() == 0)
			*GetStaticDCControl() = new CDCControl;
		return *GetStaticDCControl();
	}

	
	BOOL WriteBmp(const TSTRING &strFile, HDC hdc)
	{
		int iWidth = GetDeviceCaps(hdc, HORZRES);
		int iHeight = GetDeviceCaps(hdc, VERTRES);
		RECT rcDC = { 0,0,iWidth,iHeight };

		return WriteBmp(strFile, hdc, rcDC);
	}

	void SwitchDCColorMode(color_mode mode, HDC memoryDC, LPCTSTR colorFileName)
	{
		if (mode == monochrome)
		{
			HDC dc = CreateCompatibleDC(NULL);
			HBITMAP bitmap_monochrome = CreateCompatibleBitmap(dc, 1, 1);//或者通过createbitmap创建单色位图
			HBITMAP old_bitmap = (HBITMAP)SelectObject(memoryDC, bitmap_monochrome);
			DeleteDC(dc);
			DeleteObject(old_bitmap);
		}
		else if (mode == color)
		{
			HDC dc = CreateCompatibleDC(NULL);
			HBITMAP bitmap_color = 0;
			if (colorFileName != 0)
				bitmap_color = (HBITMAP)LoadImage(NULL, colorFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			else
				bitmap_color = (HBITMAP)LoadImage(NULL, L"D:\\1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//bitmap_color = CreateBitmap();
			
			HBITMAP old_bitmap = (HBITMAP)SelectObject(dc, bitmap_color);
			HBITMAP bitmap_color_new = CreateCompatibleBitmap(dc, 1, 1);
			HBITMAP old_bitmap_new = (HBITMAP)SelectObject(memoryDC, bitmap_color_new);
			DeleteDC(dc);
			DeleteObject(bitmap_color);
			DeleteObject(old_bitmap);
			//DeleteObject(bitmap_color_new);
			DeleteObject(old_bitmap_new);
		}
	}

	//创建设备兼容彩色位图，背景色，dc要提前转换为彩色dc
	HBITMAP CreateCompatibleDCColorBitmapWith8Bits(HDC dc, LONG width, LONG height, colors color)
	{
		//SwitchDCColorMode(color_mode::color, dc, 0);
		BITMAPINFO* pinfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * 256));
		/*BITMAPINFO info = *pinfo;*/
		pinfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		pinfo->bmiHeader.biWidth = width;
		pinfo->bmiHeader.biHeight = height;
		pinfo->bmiHeader.biPlanes = 1;
		pinfo->bmiHeader.biBitCount = 8;
		pinfo->bmiHeader.biCompression = BI_RGB;
		pinfo->bmiHeader.biSizeImage = (width * 8 + 31) / 32 * 4 * height;
		pinfo->bmiHeader.biXPelsPerMeter = 0;
		pinfo->bmiHeader.biYPelsPerMeter = 0;
		pinfo->bmiHeader.biClrUsed = 0;
		pinfo->bmiHeader.biClrImportant = 0;
		RGBQUAD rgbq;
		rgbq.rgbBlue = 7; rgbq.rgbGreen = 0; rgbq.rgbRed = 0;
		RGBQUAD rgbq2;
		rgbq2.rgbBlue = 0; rgbq2.rgbGreen = 0; rgbq2.rgbRed = 0;
		pinfo->bmiColors[0] = rgbq;
	//	pinfo->bmiColors[1] = rgbq2;
		char r, g, b;
		switch (color)
		{
		case white:
		{
			r = 0;
			g = 0;
			b = 0;
		}
		break;
		}
		WORD WS = *((WORD*)pinfo->bmiColors);

		void* data = malloc((width * 8 + 31) / 32 * 4 * height);
		int src = (int)data;
		char start = 'r';

		for (int h = 0; h < height; h++)
		{
			for (int i = 0; i < (width * 8 + 31) / 32 * 4; i++)
			{
				char* c1 = (char*)(src + (h * ((width * 8 + 31) / 32 * 4) + i));
				if (i >= width * 3)
				{
					*c1 = 0;
				}
				else
				{
					switch (start)
					{
					case 'r':
					{
						*c1 = r;
						start = 'g';
					}
					break;
					case 'g':
					{
						*c1 = g;
						start = 'b';
					}
					break;
					case 'b':
					{
						*c1 = b;
						start = 'r';
					}
					break;
					}
				}
			}
		}
		HBITMAP bitmap = CreateDIBitmap(dc, &pinfo->bmiHeader, CBM_INIT, data, pinfo, DIB_PAL_COLORS);
	
		

		//SelectObject(dc, bitmap);

		int a = GetDIBits(dc, bitmap, 0, 300, data, pinfo, DIB_PAL_COLORS);
		//WORD wa[256] = { 0 };
		//WORD(*pw)[256];
		//pw = (WORD(*)[256])&(pinfo->bmiColors);L
		//
		////WORD* pwd = *pw;

		////WORD wd = *pwd;
		//WORD wd2 = pw[0][5];

		//int aa[3][4] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
		//int(*p)[4];
		//p = (int(*)[4])aa;
		//p[1][1];

//		RGBQUAD ad = pinfo->bmiColors[252];
		//	CreateBitmapIndirect()
		free(data);
		free(pinfo);
		return bitmap;
	}

	HBITMAP CreateCompatibleDCColorBitmapWith24Bits(HDC dc, LONG width, LONG height, colors color, COLORREF cr = RGB(0, 0, 0))
	{
		//SwitchDCColorMode(color_mode::color, dc, 0);
		BITMAPINFO* pinfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * 0));
		/*BITMAPINFO info = *pinfo;*/
		pinfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		pinfo->bmiHeader.biWidth = width;
		pinfo->bmiHeader.biHeight = height;
		pinfo->bmiHeader.biPlanes = 1;
		pinfo->bmiHeader.biBitCount = 24;
		pinfo->bmiHeader.biCompression = BI_RGB;
		pinfo->bmiHeader.biSizeImage = (width * 24 + 31) / 32 * 4 * height;
		pinfo->bmiHeader.biXPelsPerMeter = 0;
		pinfo->bmiHeader.biYPelsPerMeter = 0;
		pinfo->bmiHeader.biClrUsed = 0;
		pinfo->bmiHeader.biClrImportant = 0;
		/*RGBQUAD rgbq;
		rgbq.rgbBlue = 7; rgbq.rgbGreen = 0; rgbq.rgbRed = 0;
		RGBQUAD rgbq2;
		rgbq2.rgbBlue = 0; rgbq2.rgbGreen = 0; rgbq2.rgbRed = 0;
		pinfo->bmiColors[0] = rgbq;*/
		//	pinfo->bmiColors[1] = rgbq2;
		char r, g, b;
		switch (color)
		{
		case white:
		{
			r = 255;
			g = 255;
			b = 255;
		}
		break;
		case undefine:
		{
			r = GetRValue(cr);
			g = GetGValue(cr);
			b = GetBValue(cr);
		}
		break;
		}

		void* data = malloc((width * 24 + 31) / 32 * 4 * height);
		int src = (int)data;
		char start = 'r';

		for (int h = 0; h < height; h++)
		{
			for (int i = 0; i < (width * 24 + 31) / 32 * 4; i++)
			{
				char* c1 = (char*)(src + (h * ((width * 24 + 31) / 32 * 4) + i));
				if (i >= width * 3)
				{
					*c1 = 0;
				}
				else
				{
					switch (start)
					{
					case 'r':
					{
						*c1 = r;
						start = 'g';
					}
					break;
					case 'g':
					{
						*c1 = g;
						start = 'b';
					}
					break;
					case 'b':
					{
						*c1 = b;
						start = 'r';
					}
					break;
					}
				}
			}
		}
		HBITMAP bitmap = CreateDIBitmap(dc, &pinfo->bmiHeader, CBM_INIT, data, pinfo, DIB_RGB_COLORS);



		//SelectObject(dc, bitmap);

	//	int a = GetDIBits(dc, bitmap, 0, 300, data, pinfo, DIB_PAL_COLORS);
		//WORD wa[256] = { 0 };
		//WORD(*pw)[256];
		//pw = (WORD(*)[256])&(pinfo->bmiColors);L
		//
		////WORD* pwd = *pw;

		////WORD wd = *pwd;
		//WORD wd2 = pw[0][5];

		//int aa[3][4] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
		//int(*p)[4];
		//p = (int(*)[4])aa;
		//p[1][1];

		//		RGBQUAD ad = pinfo->bmiColors[252];
		//	CreateBitmapIndirect()
		free(data);
		free(pinfo);
		return bitmap;


	}

	void TransparentBitmapCopy(HDC dc_des, HDC dc_src, colorrgb transparent_color, int x_des, int y_des, int width, int height, int x_src, int y_src)
	{
		//创建单色图
		HDC dcMemMonochrome = CreateCompatibleDC(0);
		SwitchDCColorMode(color_mode::monochrome, dcMemMonochrome, 0);

		HBITMAP bitmap = CreateCompatibleBitmap(dcMemMonochrome, width, height);

		HBITMAP old_bitmap = (HBITMAP)SelectObject(dcMemMonochrome, bitmap);
		DeleteObject(old_bitmap);

		//将dc_src转换到单色DC上
		COLORREF cr = GetBkColor(dc_src);

		SetBkColor(dc_src, RGB(transparent_color.r, transparent_color.g, transparent_color.b));

		BitBlt(dcMemMonochrome, 0, 0, width, height, dc_src, x_src, y_src, SRCCOPY);
		SetBkColor(dc_src, cr);


		//将单色DC转换到彩色DC上
		HDC dcMemColor = CreateCompatibleDC(0);
		SwitchDCColorMode(color_mode::color, dcMemColor, 0);
		HBITMAP color_bitmap = CreateCompatibleBitmap(dcMemColor, width, height);
		HBITMAP old_color_bitmap = (HBITMAP)SelectObject(dcMemColor, color_bitmap);
		DeleteObject(old_color_bitmap);
		SetBkColor(dcMemColor, RGB(255, 255, 255));
		SetTextColor(dcMemColor, RGB(0, 0, 0));
		BitBlt(dcMemColor, 0, 0, width, height, dcMemMonochrome, 0, 0, SRCCOPY);
		
		//删除单色DC
		DeleteObject(bitmap);
		DeleteObject(dcMemMonochrome);
		//
		BitBlt(dc_des, x_des, y_des, width, height, dc_src, x_src, y_src, SRCINVERT);
		BitBlt(dc_des, x_des, y_des, width, height, dcMemColor, 0, 0, SRCAND);
		BitBlt(dc_des, x_des, y_des, width, height, dc_src, x_src, y_src, SRCINVERT);
		//
		DeleteObject(color_bitmap);
		DeleteObject(dcMemColor);
	}
private:
	BOOL WriteBmp(const TSTRING &strFile, HDC hdc, const RECT &rcDC)
	{
		BOOL bRes = FALSE;
		BITMAPINFO bmpInfo = { 0 };
		BYTE *pData = NULL;
		SIZE sizeImg = { 0 };
		HBITMAP hBmp = NULL;
		std::vector<BYTE> vtData;
		HGDIOBJ hOldObj = NULL;
		HDC hdcMem = NULL;

		//Initilaize the bitmap information   
		bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmpInfo.bmiHeader.biWidth = rcDC.right - rcDC.left;
		bmpInfo.bmiHeader.biHeight = rcDC.bottom - rcDC.top;
		bmpInfo.bmiHeader.biPlanes = 1;
		bmpInfo.bmiHeader.biBitCount = 24;

		//Create the compatible DC to get the data  
		hdcMem = CreateCompatibleDC(hdc);
		if (hdcMem == NULL)
		{
			goto EXIT;
		}

		//Get the data from the memory DC     
		hBmp = CreateDIBSection(/*hdcMem*/0, &bmpInfo, DIB_RGB_COLORS, reinterpret_cast<VOID **>(&pData), NULL, 0);
		if (hBmp == NULL)
		{
			goto EXIT;
		}
		hOldObj = SelectObject(hdcMem, hBmp);

		//Draw to the memory DC  
		sizeImg.cx = bmpInfo.bmiHeader.biWidth;
		sizeImg.cy = bmpInfo.bmiHeader.biHeight;
		StretchBlt(hdcMem,
			0,
			0,
			sizeImg.cx,
			sizeImg.cy,
			hdc,
			rcDC.left,
			rcDC.top,
			rcDC.right - rcDC.left + 1,
			rcDC.bottom - rcDC.top + 1,
			SRCCOPY);


		vtData.resize(sizeImg.cx * sizeImg.cy * 3);
		memcpy(&vtData[0], pData, vtData.size());
		bRes = WriteBmp(strFile, vtData, sizeImg);

		SelectObject(hdcMem, hOldObj);


	EXIT:
		if (hBmp != NULL)
		{
			DeleteObject(hBmp);
		}

		if (hdcMem != NULL)
		{
			DeleteDC(hdcMem);
		}

		return bRes;
	}

	BOOL WriteBmp(const TSTRING &strFile, const std::vector<BYTE> &vtData, const SIZE &sizeImg)
	{
		BITMAPINFOHEADER bmInfoHeader = { 0 };
		bmInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmInfoHeader.biWidth = sizeImg.cx;
		bmInfoHeader.biHeight = sizeImg.cy;
		bmInfoHeader.biPlanes = 1;
		bmInfoHeader.biBitCount = 24;

		//Bimap file header in order to write bmp file  
		BITMAPFILEHEADER bmFileHeader = { 0 };
		bmFileHeader.bfType = 0x4d42;  //bmp    
		bmFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		bmFileHeader.bfSize = bmFileHeader.bfOffBits + ((bmInfoHeader.biWidth * bmInfoHeader.biHeight) * 3); ///3=(24 / 8)  

		HANDLE hFile = CreateFile(strFile.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return FALSE;
		}

		DWORD dwWrite = 0;
		WriteFile(hFile, &bmFileHeader, sizeof(BITMAPFILEHEADER), &dwWrite, NULL);
		WriteFile(hFile, &bmInfoHeader, sizeof(BITMAPINFOHEADER), &dwWrite, NULL);
		WriteFile(hFile, &vtData[0], vtData.size(), &dwWrite, NULL);


		CloseHandle(hFile);

		return TRUE;
	}

	static CDCControl** GetStaticDCControl()
	{
		static CDCControl* control = 0;
		return &control;
	}
};

////由文件创建一幅设备相关的位图
//HBITMAP LoadBitmapEx(LPCTSTR lpszFile)
//{
//	if (lpszFile == NULL) return NULL;
//
//
//	HBITMAP hBitmap;
//	HANDLE hf;
//	BITMAPFILEHEADER* pbmfh;
//	DWORD dwBytesRead, dwFileSize, dwFileSizeHigh;
//	BOOL bSuccess;
//	// 打开一个bmp文件
//	hf = CreateFile(lpszFile, GENERIC_READ, FILE_SHARE_READ,
//		NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
//	if (hf == INVALID_HANDLE_VALUE)
//	{
//		//TRACE("Open file filed with error %d ", GetLastError());
//		return NULL;
//	}
//	// 得到这个文件大小
//	dwFileSize = GetFileSize(hf, &dwFileSizeHigh);
//	if (dwFileSizeHigh)
//	{
//		CloseHandle(hf);
//		return NULL;
//	}
//	// 分配内存,大小为该文件的大小
//	pbmfh = (BITMAPFILEHEADER*)malloc(dwFileSize);
//	if (!pbmfh)
//	{
//		CloseHandle(hf);
//		return NULL;
//	}
//	// 读取数据
//	bSuccess = ReadFile(hf, pbmfh, dwFileSize, &dwBytesRead, NULL);
//	CloseHandle(hf);
//	// 效验文件大小和文件格式
//	if (!bSuccess || dwFileSize != dwBytesRead || pbmfh->bfType != 0x4D42 || pbmfh->bfSize != dwFileSize)
//	{
//		free((void*)pbmfh);
//		return NULL;
//	}
//	// 进行DIB转换
//	hBitmap = CreateDIBitmap(GetWindowDC(NULL),
//		(BITMAPINFOHEADER*)(pbmfh + 1),
//		CBM_INIT,
//		(BYTE*)pbmfh + pbmfh->bfOffBits,
//		(BITMAPINFO*)(pbmfh + 1),
//		DIB_RGB_COLORS);
//	free((void*)pbmfh);
//
//
//
//	//bfOffBits bfOffBits 从文件头开始到颜色数据的偏移量  54+sizeof(RGBQUAD)*256
//
//	//54   int size = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);  size = 54
//	return hBitmap;
//}
