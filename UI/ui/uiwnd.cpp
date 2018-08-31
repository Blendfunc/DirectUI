#include "uiwnd.h"
#include"Windowsx.h"
CDirectUIPositionManager* CDirectUIPositionManager::m_Manager = 0;

LRESULT CALLBACK DirectUIWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT rect_validate;
	//hWnd需要区分吗
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
	{
		HDC dc0 = BeginPaint(hWnd, &ps);
		//HDC main = GetDC(hWnd);
		HDC dc = CDirectUIPositionManager::GetDirectUIPositionManagerInstance()->GetWindowMemoryDC(hWnd);
		int width = ps.rcPaint.right - ps.rcPaint.left;
		int height = ps.rcPaint.bottom - ps.rcPaint.top;
		BitBlt(dc0, ps.rcPaint.left, ps.rcPaint.top, width, height, dc, ps.rcPaint.left, ps.rcPaint.top, SRCCOPY);
		EndPaint(hWnd, &ps);
		//ReleaseDC(hWnd, main);
		break;
	}
		
	case WM_MOUSEMOVE:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		CDirectUIBase* base = CDirectUIPositionManager::GetDirectUIPositionManagerInstance()->GetPointUI(hWnd, xPos, yPos);
		CDirectUIBase* current_base = CDirectUIPositionManager::GetDirectUIPositionManagerInstance()->GetCurrentUIBase(hWnd);
		if (base != current_base)
		{
			if (current_base)
			{
				if (current_base->GetClassNameType() == DIRECTUI_BUTTON)
				{
					CDirectUIButton* bt = static_cast<CDirectUIButton*>(current_base);

					RESULTCALLBACK result = DONOTHING;
					if (bt->GetEventCallBack())
						result = bt->GetEventCallBack()->OnMouseLeft(bt);

					if (result == DONOTPAINT)
					{

					}
					else if (result == CONTINUE || result == DONOTHING)
					{
						CDirectUIRect* rt = const_cast<CDirectUIRect*>(bt->GetDirectUIButtonRect());
						rt->UpdateDC(DUI_MOUSE_REMAINON);
						CDirectUIWnd* dwnd = CDirectUIPositionManager::GetDirectUIPositionManagerInstance()->GetDirectUIWnd(hWnd);
						dwnd->UpdateMemoryDC(current_base);
						rect_validate.left = bt->GetXPosition();
						rect_validate.top = bt->GetYPosition();
						rect_validate.right = rect_validate.left + rt->GetWidth();
						rect_validate.bottom = rect_validate.top + rt->GetHeight();
						::InvalidateRect(hWnd, &rect_validate, FALSE);
					}

					CDirectUIPositionManager::GetDirectUIPositionManagerInstance()->SetCurrentUIBase(hWnd, 0);
				}
			}
			if (base && base->GetClassNameType() == DIRECTUI_BUTTON)
			{
				CDirectUIPositionManager::GetDirectUIPositionManagerInstance()->SetCurrentUIBase(hWnd, base);

				CDirectUIButton* button = static_cast<CDirectUIButton*>(base);

				RESULTCALLBACK result = DONOTHING;
				if (button->GetEventCallBack())
					result = button->GetEventCallBack()->OnMouseMoveStartIn(button);

				if (result == DONOTPAINT)
				{

				}
				else if(result == CONTINUE || result == DONOTHING)
				{
					CDirectUIRect* rect = const_cast<CDirectUIRect*>(button->GetDirectUIButtonRect());
					rect->UpdateDC(DUI_MOUSE_MOVE);
					CDirectUIWnd* duiwnd = CDirectUIPositionManager::GetDirectUIPositionManagerInstance()->GetDirectUIWnd(hWnd);
					duiwnd->UpdateMemoryDC(base);
					//HDC dc = CDirectUIPositionManager::GetDirectUIPositionManagerInstance()->GetWindowMemoryDC(hWnd);
					rect_validate.left = button->GetXPosition();
					rect_validate.top = button->GetYPosition();
					rect_validate.right = rect_validate.left + rect->GetWidth();
					rect_validate.bottom = rect_validate.top + rect->GetHeight();
					::InvalidateRect(hWnd, &rect_validate, FALSE);
				}
			}
		}
		break;
	}

	case WM_LBUTTONDOWN:
	{
		CDirectUIBase* current_base = CDirectUIPositionManager::GetDirectUIPositionManagerInstance()->GetCurrentUIBase(hWnd);
		if (current_base && current_base->GetClassNameType() == DIRECTUI_BUTTON)
		{
			CDirectUIButton* bt = static_cast<CDirectUIButton*>(current_base);
			RESULTCALLBACK result = DONOTHING;
			if (bt->GetEventCallBack())
				result = bt->GetEventCallBack()->OnLeftButtonClickDown(bt);

			if (result == DONOTPAINT)
			{

			}
			else if (result == CONTINUE || result == DONOTHING)
			{
				CDirectUIRect* rt = const_cast<CDirectUIRect*>(bt->GetDirectUIButtonRect());
				rt->UpdateDC(DUI_MOUSE_LEFT_CLICK_DOWN);
				CDirectUIWnd* dwnd = CDirectUIPositionManager::GetDirectUIPositionManagerInstance()->GetDirectUIWnd(hWnd);
				dwnd->UpdateMemoryDC(current_base);
				rect_validate.left = bt->GetXPosition();
				rect_validate.top = bt->GetYPosition();
				rect_validate.right = rect_validate.left + rt->GetWidth();
				rect_validate.bottom = rect_validate.top + rt->GetHeight();
				::InvalidateRect(hWnd, &rect_validate, FALSE);
			}
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		CDirectUIBase* current_base = CDirectUIPositionManager::GetDirectUIPositionManagerInstance()->GetCurrentUIBase(hWnd);
		if (current_base && current_base->GetClassNameType() == DIRECTUI_BUTTON)
		{
			CDirectUIButton* bt = static_cast<CDirectUIButton*>(current_base);
			RESULTCALLBACK result = DONOTHING;
			if (bt->GetEventCallBack())
				result = bt->GetEventCallBack()->OnLeftButtonClickUp(bt);

			if (result == DONOTPAINT)
			{

			}
			else if (result == CONTINUE || result == DONOTHING)
			{
				CDirectUIRect* rt = const_cast<CDirectUIRect*>(bt->GetDirectUIButtonRect());
				rt->UpdateDC(DUI_MOUSE_LEFT_CLICK_UP);
				CDirectUIWnd* dwnd = CDirectUIPositionManager::GetDirectUIPositionManagerInstance()->GetDirectUIWnd(hWnd);
				dwnd->UpdateMemoryDC(current_base);
				rect_validate.left = bt->GetXPosition();
				rect_validate.top = bt->GetYPosition();
				rect_validate.right = rect_validate.left + rt->GetWidth();
				rect_validate.bottom = rect_validate.top + rt->GetHeight();
				::InvalidateRect(hWnd, &rect_validate, FALSE);
			}
		}


		break;
	}
	 

	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

HINSTANCE CDirectUIWnd::m_Hinstance = 0;

CDirectUIWndClass* CDirectUIWndClass::m_Instance = 0;



CDirectUIWnd::CDirectUIWnd(HINSTANCE hinstance, int width, int height)
{
	m_Hinstance = hinstance;
	m_window_height = height;
	m_window_width = width;

	m_window_memory_dc = CreateCompatibleDC(NULL);
	CDCControl::GetDCControlInstance()->SwitchDCColorMode(CDCControl::color, m_window_memory_dc, L"D:\\1.bmp");
	m_window_memory_dc_bitmap = CreateCompatibleBitmap(m_window_memory_dc, width, height);
	HBITMAP old_bitmap = (HBITMAP)SelectObject(m_window_memory_dc, m_window_memory_dc_bitmap);
	DeleteObject(old_bitmap);

	HBITMAP bitmap = (HBITMAP)LoadImage(NULL, L"D:\\Aurora.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	bitmap = 0;
	bitmap = CDCControl::GetDCControlInstance()->CreateCompatibleDCColorBitmapWith24Bits(m_window_memory_dc, width, height, CDCControl::white);



	HBITMAP oldBitmap = (HBITMAP)SelectObject(m_window_memory_dc, bitmap);
	CDCControl::GetDCControlInstance()->WriteBmp(L"c:\\123.bmp", m_window_memory_dc);
	DeleteObject(oldBitmap);

	InitUIMap(height, width);

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
	m_HWND = CreateWindow(wndClass.lpszClassName, lpWindowName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, m_window_width, m_window_height, NULL, NULL, m_Hinstance, NULL);
	LONG style = ::GetWindowLongPtr(m_HWND, GWL_STYLE);
	style = style &~WS_CAPTION &~WS_SYSMENU&~WS_SIZEBOX;
	::SetWindowLongPtr(m_HWND, GWL_STYLE, style);

	CDirectUIPositionManager::GetDirectUIPositionManagerInstance()->RegisterDirectUIPositionManager(m_HWND, this);
	CDirectUIPositionManager::GetDirectUIPositionManagerInstance()->SetWindowMemoryDCMap(m_HWND, m_window_memory_dc);
	return m_HWND;
	
}

void CDirectUIWnd::ShowDirectUIWnd()
{
	ShowWindow(m_HWND, SW_SHOW);
	UpdateWindow(m_HWND);
	//HDC main = GetDC(m_HWND);
	////m_Rect.SetOwnerDC(main);
	//m_Rect.SetWidthHeight(39, 224);
	//m_Rect.SetUIAttributeImg(DUI_MOUSE_REMAINON, L"D:\\bitmap_s.bmp");
	//m_Rect.UpdateDC(DUI_MOUSE_REMAINON);
	//ReleaseDC(m_HWND, main);
}

void CDirectUIWnd::AddDirectUIButton(CDirectUIButton * button, int x, int y)
{
	for (int i = x; i < x + button->GetDirectUIButtonRect()->GetWidth(); i++)
	{
		for (int j = y; j < y + button->GetDirectUIButtonRect()->GetHeight(); j++)
		{
			UpdateUIMap(i, j, button);
		}
	}
	

	button->SetXPosition(x);
	button->SetYPosition(y);

	CDirectUIRect* rect = const_cast<CDirectUIRect*>(button->GetDirectUIButtonRect());
	rect->UpdateDC(DUI_MOUSE_REMAINON);
	UpdateMemoryDC(dynamic_cast<CDirectUIBase*>(button));
}

void CDirectUIWnd::UpdateMemoryDC(CDirectUIBase* base)
{
	if (base->GetClassNameType() == DIRECTUI_BUTTON)
	{
		CDirectUIButton* button = static_cast<CDirectUIButton*>(base);
		const CDirectUIRect* rect = button->GetDirectUIButtonRect();
		HDC button_dc = rect->GetDirectUIRectDC();
		::BitBlt(m_window_memory_dc, button->GetXPosition(), button->GetYPosition(), rect->GetWidth(), rect->GetHeight(), button_dc, 0, 0, SRCCOPY);
	}
}

std::map<int, std::map<int, CDirectUIBase*>>* CDirectUIWnd::GetWndUIMap()
{
	return nullptr;
}

void CDirectUIWnd::UpdateUIMap(int x, int y, CDirectUIBase * base)
{
	m_ui_map[x][y] = base;
}

void CDirectUIWnd::InitUIMap(int height, int width)
{
	for (int w = 0; w < width; w++)
	{
		std::map<int, CDirectUIBase*> map;
		m_ui_map[w] = map;
		for (int h = 0; h < height; h++)
		{
			(m_ui_map[w])[h] = 0;
		}
	}
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


CDirectUIPositionManager::CDirectUIPositionManager()
{
	/*m_Current_UI = 0;*/
}

CDirectUIPositionManager::~CDirectUIPositionManager()
{
}

CDirectUIPositionManager * CDirectUIPositionManager::GetDirectUIPositionManagerInstance()
{
	if (!m_Manager)
		m_Manager = new CDirectUIPositionManager;
	return m_Manager;
}

void CDirectUIPositionManager::RegisterDirectUIPositionManager(HWND h, CDirectUIWnd* wnd)
{
	m_Data[h] = GetData(*wnd);
	SetWindowDirectUIWindow(h, wnd);
}

void CDirectUIPositionManager::SetWindowMemoryDCMap(HWND h, HDC dc)
{
	m_Window_MemoryDC[h] = dc;
}

HDC CDirectUIPositionManager::GetWindowMemoryDC(HWND h)
{
	return m_Window_MemoryDC[h];
}

CDirectUIBase * CDirectUIPositionManager::GetPointUI(HWND h, int x, int y)
{
	return m_Data.at(h)->at(x).at(y);

}

CDirectUIWnd * CDirectUIPositionManager::GetDirectUIWnd(HWND h)
{
	return m_Window_DirectUIWindow.at(h);
}

CDirectUIBase * CDirectUIPositionManager::GetCurrentUIBase(HWND h)
{
	if(m_Current_UI_Map.count(h))
	return m_Current_UI_Map[h];
	return 0;

}

void CDirectUIPositionManager::SetCurrentUIBase(HWND h, CDirectUIBase * base)
{
	m_Current_UI_Map[h] = base;
}

window_ui_position CDirectUIPositionManager::GetData(CDirectUIWnd& wnd)
{
	return &wnd.m_ui_map;
}

void CDirectUIPositionManager::SetWindowDirectUIWindow(HWND h, CDirectUIWnd * wnd)
{
	m_Window_DirectUIWindow[h] = wnd;
}
