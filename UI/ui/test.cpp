#include "uiwnd.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, PSTR szCmdLine, int iCmdShow)
{
	CDirectUIWndClass::GetCDirectUIWndClassInstance()->SetDirectUIWndAttribute(L"MyDirectUIWnd", hInstance);
	ATOM atom = CDirectUIWndClass::GetCDirectUIWndClassInstance()->RegisterDirectUIWndClass();


	CDirectUIButton button;
	CDirectUIRect * rect = (CDirectUIRect*)button.GetDirectUIButtonRect();
	rect->SetWidthHeight(100, 200);
	rect->SetUIAttributeImg(DUI_MOUSE_REMAINON, L"D:\\texture.bmp");

	CDirectUIButton button1;
	CDirectUIRect * rect1 = (CDirectUIRect*)button1.GetDirectUIButtonRect();
	rect1->SetWidthHeight(80, 80);
	rect1->SetUIAttributeImg(DUI_MOUSE_REMAINON, L"D:\\texture.bmp");

	CDirectUIButton button2;
	CDirectUIRect * rect2 = (CDirectUIRect*)button2.GetDirectUIButtonRect();
	rect2->SetWidthHeight(50, 30);
	rect2->SetUIAttributeImg(DUI_MOUSE_REMAINON, L"D:\\texture.bmp");

	CDirectUIButton button3;
	CDirectUIRect * rect3 = (CDirectUIRect*)button3.GetDirectUIButtonRect();
	rect3->SetWidthHeight(40, 32);
	rect3->SetUIAttributeImg(DUI_MOUSE_REMAINON, L"D:\\texture.bmp");

	CDirectUIWnd wnd(hInstance, 960, 453);
	wnd.AddDirectUIButton(&button, 0, 0);
	wnd.AddDirectUIButton(&button1, 100, 200);
	wnd.AddDirectUIButton(&button2, 190, 300);
	wnd.AddDirectUIButton(&button3, 400, 400);
	wnd.CreateDirectUIWnd(atom);
	wnd.ShowDirectUIWnd();


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