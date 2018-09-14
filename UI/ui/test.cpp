#include "uiwnd.h"
#include "uitext.h"
#include <time.h>
#include "uiedit.h"

class DIRECTUIBUTTONCALLBACK : public IDirectUIButtonUICallBack
{
public:
	virtual RESULTCALLBACK OnLeftButtonClickDown(CDirectUIButton* button);

	virtual RESULTCALLBACK OnMouseMoveStartIn(CDirectUIButton* button);

	virtual RESULTCALLBACK OnLeftButtonClickUp(CDirectUIButton* button);

	virtual RESULTCALLBACK OnMouseMoveIn(CDirectUIButton* buttonn);

	virtual RESULTCALLBACK OnMouseLeft(CDirectUIButton* button);
};

DIRECTUIBUTTONCALLBACK cb, cb2, cb3, cb4;
CDirectUIWnd wnd(0, 1920, 1080);

int i_font = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, PSTR szCmdLine, int iCmdShow)
{
	wnd.m_Hinstance = hInstance;
	CDirectUIText::GetFonts();
	srand((int)time(NULL));


	CDirectUIWndClass::GetCDirectUIWndClassInstance()->SetDirectUIWndAttribute(L"MyDirectUIWnd", hInstance);
	ATOM atom = CDirectUIWndClass::GetCDirectUIWndClassInstance()->RegisterDirectUIWndClass();
	

	CDirectUIButton button;
	button.SetEventCallBack(&cb);
	CDirectUIRect * rect = (CDirectUIRect*)button.GetDirectUIButtonRect();
	rect->SetWidth(100);
	rect->SetHeight(50);
	rect->SetUIAttributeImg(DUI_MOUSE_REMAINON, L"D:\\texture.bmp");
	rect->SetUIAttributeImg(DUI_MOUSE_MOVE, L"D:\\Terrain1.bmp");
	rect->SetUIAttributeImg(DUI_MOUSE_LEFT_CLICK_DOWN, L"D:\\l_button_click_down.bmp");
	rect->SetUIAttributeImg(DUI_MOUSE_LEFT_CLICK_UP, L"D:\\Terrain1.bmp");
	CDirectUIText* text = const_cast<CDirectUIText*>(button.GetDirectUIButtonText());
	text->SetDCBKColor(RGB(255, 255, 255));
	text->SetDirectUITextColor(RGB(0, 0, 0));
	text->SetDCHeight(30);
	text->SetDCWidth(80);
	text->SetText(L"");
	//text->SetFontName("微软雅黑");
	text->SetFontHeight(30);
	text->SetFontWidth(30);
	button.SetXPosition(0);
	button.SetYPosition(0);
	
	text->SetDirectUITextFont(&(CDirectUIText::vt_font.at(100).lfa));

	CDirectUIEdit edit;
	edit.SetEditBKColor(RGB(166, 166, 166));
	edit.SetEditTextColor(RGB(0, 0, 0));
	edit.SetEditHeight(100);
	edit.SetEditWidth(300);
	//edit.SetText(L"");
	//edit.SetFontHeight(30);
	//edit.SetFontWidth(30);
	edit.SetXPosition(100);
	edit.SetYPosition(50);

	//CDirectUIText::vt_font.at(100).lfa.lfQuality = NONANTIALIASED_QUALITY;
	LOGFONTW lfw;
	memcpy(&lfw, &(CDirectUIText::vt_font.at(100).lfa), sizeof(LOGFONTW));
	//lfw.lfQuality = NONANTIALIASED_QUALITY;
	edit.SetEditFont(&lfw);
	//edit.Add('S');
	/*for (int j = 0; j < 500; j += 30)
	{
		for (int i = 0; i < 600; i += 50)
		{
			CDirectUIButton* button_new = new CDirectUIButton;
			button_new->SetEventCallBack(&cb);
			CDirectUIRect * rect = (CDirectUIRect*)button_new->GetDirectUIButtonRect();
			rect->SetWidth(50);
			rect->SetHeight(30);
			rect->SetUIAttributeImg(DUI_MOUSE_REMAINON, L"D:\\texture.bmp");
			rect->SetUIAttributeImg(DUI_MOUSE_MOVE, L"D:\\Terrain1.bmp");
			rect->SetUIAttributeImg(DUI_MOUSE_LEFT_CLICK_DOWN, L"D:\\l_button_click_down.bmp");
			rect->SetUIAttributeImg(DUI_MOUSE_LEFT_CLICK_UP, L"D:\\Terrain1.bmp");
			CDirectUIText* text = const_cast<CDirectUIText*>(button_new->GetDirectUIButtonText());
			text->SetDCBKColor(RGB(255, 255, 255));
			text->SetDirectUITextColor(RGB(255, 0, 0));
			text->SetDCHeight(30);
			text->SetDCWidth(50);
			text->SetText("123");
			text->SetFontName("微软雅黑");
			text->SetFontHeight(14);
			text->SetFontWidth(14);
			button_new->SetXPosition(i);
			button_new->SetYPosition(j);
			wnd.AddDirectUIButton(button_new);
		}
	}*/




	/*CDirectUIButton button1;
	button1.SetEventCallBack(&cb);
	CDirectUIRect * rect1 = (CDirectUIRect*)button1.GetDirectUIButtonRect();
	rect1->SetWidthHeight(30, 50);
	rect1->SetUIAttributeImg(DUI_MOUSE_REMAINON, L"D:\\texture.bmp");
	rect1->SetUIAttributeImg(DUI_MOUSE_MOVE, L"D:\\Terrain1.bmp");
	rect1->SetUIAttributeImg(DUI_MOUSE_LEFT_CLICK_DOWN, L"D:\\l_button_click_down.bmp");
	rect1->SetUIAttributeImg(DUI_MOUSE_LEFT_CLICK_UP, L"D:\\Terrain1.bmp");

	CDirectUIButton button2;
	button2.SetEventCallBack(&cb);
	CDirectUIRect * rect2 = (CDirectUIRect*)button2.GetDirectUIButtonRect();
	rect2->SetWidthHeight(30, 50);
	rect2->SetUIAttributeImg(DUI_MOUSE_REMAINON, L"D:\\texture.bmp");
	rect2->SetUIAttributeImg(DUI_MOUSE_MOVE, L"D:\\Terrain1.bmp");
	rect2->SetUIAttributeImg(DUI_MOUSE_LEFT_CLICK_DOWN, L"D:\\l_button_click_down.bmp");
	rect2->SetUIAttributeImg(DUI_MOUSE_LEFT_CLICK_UP, L"D:\\Terrain1.bmp");


	CDirectUIButton button3;
	button3.SetEventCallBack(&cb);
	CDirectUIRect * rect3 = (CDirectUIRect*)button3.GetDirectUIButtonRect();
	rect3->SetWidthHeight(30, 50);
	rect3->SetUIAttributeImg(DUI_MOUSE_REMAINON, L"D:\\texture.bmp");
	rect3->SetUIAttributeImg(DUI_MOUSE_MOVE, L"D:\\Terrain1.bmp");
	rect3->SetUIAttributeImg(DUI_MOUSE_LEFT_CLICK_DOWN, L"D:\\l_button_click_down.bmp");
	rect3->SetUIAttributeImg(DUI_MOUSE_LEFT_CLICK_UP, L"D:\\Terrain1.bmp");*/

	
	wnd.AddDirectUIButton(&button);
	wnd.AddDirectUIEdit(&edit);
	/*wnd.AddDirectUIButton(&button1, 50, 0);
	wnd.AddDirectUIButton(&button2, 100, 0);
	wnd.AddDirectUIButton(&button3, 150, 0);*/
	wnd.CreateDirectUIWnd(atom, L"摸鱼");
	wnd.ShowDirectUIWnd();

	/*CDirectUIWnd wnd2(hInstance, 500, 500);
	wnd2.AddDirectUIButton(&button, 0, 0);
	wnd2.AddDirectUIButton(&button1, 50, 0);
	wnd2.AddDirectUIButton(&button2, 100, 0);
	wnd2.AddDirectUIButton(&button3, 150, 0);
	wnd2.CreateDirectUIWnd(atom);
	wnd2.ShowDirectUIWnd();*/

	/*CDirectUIWnd wnd2(hInstance);
	wnd2.AddDirectUIButton(&button, 0, 0);
	wnd2.CreateDirectUIWnd(atom, L"123456");
	wnd2.ShowDirectUIWnd();*/
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//翻译消息

		TranslateMessage(&msg);



		//分发消息

		DispatchMessage(&msg);

	}





	return msg.wParam;

}




//#include <windows.h>
//#define DIVISIONS 5
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//	PSTR szCmdLine, int iCmdShow)
//{
//	static TCHAR szAppName[] = TEXT("RECT");
//	HWND         hwnd;
//	MSG          msg;
//	WNDCLASS     wndclass;
//
//	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;//客户区想要响应双击，则CS_DBLCLKS得注册进去
//	wndclass.lpfnWndProc = WndProc;
//	wndclass.cbClsExtra = 0;
//	wndclass.cbWndExtra = 0;
//	wndclass.hInstance = hInstance;
//	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	wndclass.lpszMenuName = NULL;
//	wndclass.lpszClassName = szAppName;
//
//	if (!RegisterClass(&wndclass))
//	{
//		MessageBox(NULL, TEXT("This program requires Windows NT!"),
//			szAppName, MB_ICONERROR);
//		return 0;
//	}
//
//	hwnd = CreateWindow(szAppName, TEXT("RECT TEST"),
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, CW_USEDEFAULT,
//		CW_USEDEFAULT, CW_USEDEFAULT,
//		NULL, NULL, hInstance, NULL);
//
//	ShowWindow(hwnd, iCmdShow);
//	UpdateWindow(hwnd);
//
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//	return msg.wParam;
//}
//static int     cxClient, cyClient;
//static BOOL state[DIVISIONS][DIVISIONS];
//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//
//	HDC            hdc;
//	HPEN hpen;
//	PAINTSTRUCT    ps;
//	RECT     rect;
//	int i, j;
//	int x, y;
//	//INT a;
//	//char buf[10];
//	char szAppName[] = "RECTANGLE";
//	LRESULT b;
//
//	switch (message)
//	{
//	case WM_CREATE:
//		//a=GetDoubleClickTime();
//		//itoa(a,buf,10);
//		//MessageBoxA(hwnd,buf,"hi",0);// 得到鼠标双击的间隔
//		return 0;
//
//
//	case WM_SIZE:
//		cxClient = LOWORD(lParam) / DIVISIONS;
//		cyClient = HIWORD(lParam) / DIVISIONS;
//		//if(IsIconic(hwnd))
//		//MessageBox(hwnd,TEXT("窗口已然最小化"),TEXT("情况"),0);
//		//if(IsZoomed(hwnd))
//		//MessageBox(hwnd,TEXT("窗口已然最大化"),TEXT("情况"),0);
//		return 0;
//	case WM_LBUTTONDBLCLK:
//		POINT point;
//		point.x = LOWORD(lParam);
//		point.y = HIWORD(lParam);
//		PostMessage(hwnd, WM_NCLBUTTONDBLCLK, HTCAPTION, MAKELPARAM(point.x, point.y));//实行欺骗
//																					   //SetWindowPos(hwnd,
//		return 0;
//	case WM_LBUTTONDOWN:
//	{
//		x = LOWORD(lParam);
//		y = HIWORD(lParam);
//		i = j = 0;
//		while (!(x<i*cxClient))
//		{
//			++i;
//		}
//		while (!(y<j*cyClient))
//		{
//			++j;
//		}
//		if (state[i - 1][j - 1] == TRUE)
//		{
//			state[i - 1][j - 1] = FALSE;
//		}
//		else
//		{
//			state[i - 1][j - 1] = TRUE;
//		}
//		InvalidateRect(hwnd, NULL, TRUE);
//		POINT point;
//		point.x = LOWORD(lParam);
//		point.y = HIWORD(lParam);
//		PostMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));//实行欺骗
//	}
//	return 0;
//
//	case WM_PAINT:
//		hdc = BeginPaint(hwnd, &ps);
//		GetClientRect(hwnd, &rect);
//		hpen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
//
//		for (j = 0; j<DIVISIONS; j++)
//			for (i = 0; i<DIVISIONS; i++)
//			{
//				Rectangle(hdc, i*cxClient, j*cyClient, (i + 1)*cxClient, (j + 1)*cyClient);
//				if (state[i][j])
//				{
//					SelectObject(hdc, hpen);
//					MoveToEx(hdc, i*cxClient, j*cyClient, NULL);
//					LineTo(hdc, (i + 1)*cxClient, (j + 1)*cyClient);
//					MoveToEx(hdc, i*cxClient, (j + 1)*cyClient, NULL);
//					LineTo(hdc, (i + 1)*cxClient, j*cyClient);
//					SelectObject(hdc, GetStockObject(BLACK_PEN));
//
//
//				}
//			}
//		DeleteObject(hpen);
//		EndPaint(hwnd, &ps);
//
//		return 0;
//		//case WM_NCLBUTTONDOWN:
//		//return (LRESULT)HTCAPTION;
//	case WM_NCHITTEST:
//
//		b = DefWindowProc(hwnd, message, wParam, lParam);
//		switch (b)
//		{
//		case HTCLIENT:
//			SetWindowText(hwnd, TEXT("点击的是客户区"));
//			return b;
//		case HTCAPTION:
//			SetWindowText(hwnd, TEXT("点击的是标题栏"));
//			return b;
//		case HTBOTTOM:
//			SetWindowText(hwnd, TEXT("点击的是下边框"));
//			return b;
//		case HTBOTTOMLEFT:
//			SetWindowText(hwnd, TEXT("点击的是左下边框"));
//			return b;
//		case HTCLOSE:
//			SetWindowText(hwnd, TEXT("点击的是关闭按钮"));
//			return b;
//		case HTLEFT:
//			SetWindowText(hwnd, TEXT("点击的是左边框"));
//			return b;
//		case HTMAXBUTTON:
//			SetWindowText(hwnd, TEXT("点击的是最大化按钮"));
//			return b;
//		case HTMINBUTTON:
//			SetWindowText(hwnd, TEXT("点击的是最小化按钮"));
//			return b;
//		case HTRIGHT:
//			SetWindowText(hwnd, TEXT("点击的是右边框"));
//			return b;
//		case HTSYSMENU:
//			SetWindowText(hwnd, TEXT("点击的是系统菜单"));
//			return b;
//		case HTTOP:
//			SetWindowText(hwnd, TEXT("点击的是上边框"));
//			return b;
//		case HTBOTTOMRIGHT:
//			SetWindowText(hwnd, TEXT("点击的是右下边框"));
//			return b;
//		default:
//			return b;
//		}
//
//
//
//	case WM_DESTROY:
//
//		PostQuitMessage(0);
//		return 0;
//	}
//	return DefWindowProc(hwnd, message, wParam, lParam);
//}

RESULTCALLBACK DIRECTUIBUTTONCALLBACK::OnLeftButtonClickDown(CDirectUIButton* button)
{
	TCHAR ch[100];
	swprintf_s(ch, 100, L"button = %p", button);
	::OutputDebugString(L"鼠标左键按下 :");
	::OutputDebugString(ch);
	::OutputDebugString(L"\n");
	CDirectUIText* text = const_cast<CDirectUIText*>(button->GetDirectUIButtonText());

	text->SetDirectUITextFont(&(CDirectUIText::vt_font.at(1).lfa));

	std::wstring str1;
	std::wstring str2;
	wchar_t ch1[33];
	str1 = _itow(i_font, ch1, 10);
	str2 = CDirectUIText::vt_font.at(i_font).lfa.lfFaceName;
	std::wstring str3 = str1 + L"  :  " + str2;

	text->SetText(str3.data());
	
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;
	text->SetDirectUITextColor(RGB(r, g, b));
	text->SetDCBKColor(RGB(255, 255, 255));
	return CONTINUE;
}

RESULTCALLBACK DIRECTUIBUTTONCALLBACK::OnMouseMoveStartIn(CDirectUIButton* button)
{
	TCHAR ch[100];
	swprintf_s(ch, 100, L"button = %p", button);
	::OutputDebugString(L"鼠标移入 :");
	::OutputDebugString(ch);
	::OutputDebugString(L"\n");
	return CONTINUE;
}

RESULTCALLBACK DIRECTUIBUTTONCALLBACK::OnLeftButtonClickUp(CDirectUIButton* button)
{
	TCHAR ch[100];
	swprintf_s(ch, 100, L"button = %p", button);
	::OutputDebugString(L"鼠标左键抬起 :");
	::OutputDebugString(ch);
	::OutputDebugString(L"\n");

	/*CDirectUIButton* button_new = new CDirectUIButton;
	button_new->SetEventCallBack(&cb);
	CDirectUIRect * rect = (CDirectUIRect*)button_new->GetDirectUIButtonRect();
	rect->SetWidth(50);
	rect->SetHeight(30);
	rect->SetUIAttributeImg(DUI_MOUSE_REMAINON, L"D:\\texture.bmp");
	rect->SetUIAttributeImg(DUI_MOUSE_MOVE, L"D:\\Terrain1.bmp");
	rect->SetUIAttributeImg(DUI_MOUSE_LEFT_CLICK_DOWN, L"D:\\l_button_click_down.bmp");
	rect->SetUIAttributeImg(DUI_MOUSE_LEFT_CLICK_UP, L"D:\\Terrain1.bmp");
	CDirectUIText* text = const_cast<CDirectUIText*>(button_new->GetDirectUIButtonText());
	text->SetDCBKColor(RGB(255, 255, 255));
	text->SetDirectUITextColor(RGB(255, 0, 0));
	text->SetDCHeight(30);
	text->SetDCWidth(50);
	text->SetText("new");
	text->SetFontName("幼圆");
	text->SetFontHeight(50);
	text->SetFontWidth(50);
	button_new->SetXPosition(button->GetXPosition() + 50);
	button_new->SetYPosition(button->GetYPosition());
	if (button->GetXPosition() + 50 > 1920)
	{
		button_new->SetXPosition(0);
		button_new->SetYPosition(30 + button->GetYPosition());
	}
	wnd.AddDirectUIButton(button_new);*/






	return CONTINUE;
}

RESULTCALLBACK DIRECTUIBUTTONCALLBACK::OnMouseMoveIn(CDirectUIButton* button)
{
	TCHAR ch[100];
	swprintf_s(ch, 100, L"button = %p", button);
	::OutputDebugString(L"鼠标正在移动 :");
	::OutputDebugString(ch);
	::OutputDebugString(L"\n");
	return CONTINUE;
}

RESULTCALLBACK DIRECTUIBUTTONCALLBACK::OnMouseLeft(CDirectUIButton* button)
{
	TCHAR ch[100];
	swprintf_s(ch, 100, L"button = %p", button);
	::OutputDebugString(L"鼠标离开 :");
	::OutputDebugString(ch);
	::OutputDebugString(L"\n");
	return CONTINUE;
}
