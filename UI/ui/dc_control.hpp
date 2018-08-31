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
		red = 0,
		white = 1,
		black = 2,
		blue = 3
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
			HBITMAP bitmap_monochrome = CreateCompatibleBitmap(dc, 1, 1);
			HBITMAP old_bitmap = (HBITMAP)SelectObject(memoryDC, bitmap_monochrome);
			DeleteDC(dc);
			DeleteObject(old_bitmap);
		}
		else if (mode == color)
		{
			HDC dc = CreateCompatibleDC(NULL);
			HBITMAP bitmap_color = (HBITMAP)LoadImage(NULL, colorFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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

	HBITMAP CreateCompatibleDCColorBitmapWith24Bits(HDC dc, LONG width, LONG height, colors color)
	{
		BITMAPINFO info;
		info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		info.bmiHeader.biWidth = width;
		info.bmiHeader.biHeight = height;
		info.bmiHeader.biPlanes = 1;
		info.bmiHeader.biBitCount = 24;
		info.bmiHeader.biCompression = BI_RGB;
		info.bmiHeader.biSizeImage = (width * 24 + 31) / 32 * 4 * height;
		info.bmiHeader.biXPelsPerMeter = 0;
		info.bmiHeader.biYPelsPerMeter = 0;
		info.bmiHeader.biClrUsed = 0;
		info.bmiHeader.biClrImportant = 0;
		char r, g, b;
		switch (color)
		{
		case white:
		{
			r = 180;
			g = 180;
			b = 180;
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
		HBITMAP bitmap = CreateDIBitmap(dc, &info.bmiHeader, CBM_INIT, data, &info, DIB_RGB_COLORS);
		free(data);
		return bitmap;
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
