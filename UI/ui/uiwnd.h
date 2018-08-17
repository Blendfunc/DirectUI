#pragma once
#include <windows.h>
#include <vector>
#include "uirect.h"

class CDirectUIWndClass
{
public:
	static CDirectUIWndClass* GetCDirectUIWndClassInstance();
public:
	void SetDirectUIWndAttribute(LPCWSTR lpszClassName = L"DirectUIWnd", HINSTANCE hinstance = 0, UINT style = CS_HREDRAW | CS_VREDRAW, int cbClsExtra = 0, int cbWndExtra = 0, HBRUSH hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH), HCURSOR hCursor = LoadCursor(NULL, IDC_ARROW), HICON hIcon = 0, LPCWSTR lpszMenuName = L"DirectUIWndMenu");
	ATOM RegisterDirectUIWndClass();
private:

	static CDirectUIWndClass* m_Instance;
	WNDCLASS m_WNDClass;
	std::vector<ATOM> m_ClassVec;
};



class CDirectUIWnd
{
public:
	CDirectUIWnd(HINSTANCE hinstance);
	~CDirectUIWnd();
	
	HWND CreateDirectUIWnd(ATOM classAtom, LPCWSTR lpWindowName = L"DirectUIWnd");
	void ShowDirectUIWnd();

	static CDirectUIRect m_Rect;
public:
	static HINSTANCE m_Hinstance;
	HWND m_HWND;
private:

	

};