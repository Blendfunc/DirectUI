#include "uiwnd.h"

CDirectUIRect CDirectUIWnd::m_Rect;

LRESULT CALLBACK DirectUIWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	//hWnd需要区分吗
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		HDC main = GetDC(hWnd);
		BitBlt(main, 0, 0, 1024, 724, CDirectUIWnd::m_Rect.GetDirectUIRectDC(), 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, main);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

HINSTANCE CDirectUIWnd::m_Hinstance = 0;

CDirectUIWndClass* CDirectUIWndClass::m_Instance = 0;



CDirectUIWnd::CDirectUIWnd(HINSTANCE hinstance)
{
	m_Hinstance = hinstance;
}

CDirectUIWnd::~CDirectUIWnd()
{
}

HWND CDirectUIWnd::CreateDirectUIWnd(ATOM classAtom, LPCWSTR lpWindowName)
{
	WNDCLASS wndClass;
	memset(&wndClass, 0, sizeof(WNDCLASS));
	LPCWSTR lpcwstr = (LPCWSTR)classAtom;

	GetClassInfo(m_Hinstance, lpcwstr, &wndClass);
	m_HWND = CreateWindow(wndClass.lpszClassName, lpWindowName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, m_Hinstance, NULL);
	return m_HWND;
	
}

void CDirectUIWnd::ShowDirectUIWnd()
{
	ShowWindow(m_HWND, SW_SHOW);
	UpdateWindow(m_HWND);
	HDC main = GetDC(m_HWND);
	m_Rect.SetOwnerDC(main);
	m_Rect.SetWidthHeight(724, 1024);
	m_Rect.SetUIAttributeImg(DUI_MOUSE_REMAINON, L"D:\\texture.bmp");
	m_Rect.UpdateDC(DUI_MOUSE_REMAINON);
	ReleaseDC(m_HWND, main);
}

CDirectUIWndClass * CDirectUIWndClass::GetCDirectUIWndClassInstance()
{
	if (!m_Instance)
		m_Instance = new CDirectUIWndClass;
	return m_Instance;
}

void CDirectUIWndClass::SetDirectUIWndAttribute(LPCWSTR lpszClassName, HINSTANCE hinstance, UINT style, int cbClsExtra, int cbWndExtra, HBRUSH hbrBackground, HCURSOR hCursor, HICON hIcon, LPCWSTR lpszMenuName)
{
	m_WNDClass.style = style;
	m_WNDClass.cbClsExtra = cbClsExtra;
	m_WNDClass.cbWndExtra = cbWndExtra;
	m_WNDClass.hbrBackground = hbrBackground;
	m_WNDClass.hCursor = hCursor;

	m_WNDClass.hIcon = hIcon;
	m_WNDClass.hInstance = hinstance;
	m_WNDClass.lpfnWndProc = DirectUIWndProc;
	m_WNDClass.lpszClassName = lpszClassName;
	m_WNDClass.lpszMenuName = lpszMenuName;
}

ATOM CDirectUIWndClass::RegisterDirectUIWndClass()
{
	ATOM atom = RegisterClass(&m_WNDClass);
	if (atom)
	{
		m_ClassVec.push_back(atom);
	}
	return atom;
}
