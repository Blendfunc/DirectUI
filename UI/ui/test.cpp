#include "uiwnd.h"


class DIRECTUIBUTTONCALLBACK : public IDirectUIButtonUICallBack
{
public:
	virtual RESULTCALLBACK OnLeftButtonClickDown(CDirectUIButton* button);

	virtual RESULTCALLBACK OnMouseMoveStartIn(CDirectUIButton* button);

	virtual RESULTCALLBACK OnLeftButtonClickUp(CDirectUIButton* button);

	virtual RESULTCALLBACK OnMouseMoveIn(CDirectUIButton* buttonn);

	virtual RESULTCALLBACK OnMouseLeft(CDirectUIButton* button);
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, PSTR szCmdLine, int iCmdShow)
{
	CDirectUIWndClass::GetCDirectUIWndClassInstance()->SetDirectUIWndAttribute(L"MyDirectUIWnd", hInstance);
	ATOM atom = CDirectUIWndClass::GetCDirectUIWndClassInstance()->RegisterDirectUIWndClass();
	DIRECTUIBUTTONCALLBACK cb, cb2, cb3, cb4;

	CDirectUIButton button;
	button.SetEventCallBack(&cb);
	CDirectUIRect * rect = (CDirectUIRect*)button.GetDirectUIButtonRect();
	rect->SetWidthHeight(30, 50);
	rect->SetUIAttributeImg(DUI_MOUSE_REMAINON, L"D:\\texture.bmp");
	rect->SetUIAttributeImg(DUI_MOUSE_MOVE, L"D:\\Terrain1.bmp");
	rect->SetUIAttributeImg(DUI_MOUSE_LEFT_CLICK_DOWN, L"D:\\l_button_click_down.bmp");
	rect->SetUIAttributeImg(DUI_MOUSE_LEFT_CLICK_UP, L"D:\\Terrain1.bmp");

	CDirectUIButton button1;
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
	rect3->SetUIAttributeImg(DUI_MOUSE_LEFT_CLICK_UP, L"D:\\Terrain1.bmp");

	CDirectUIWnd wnd(hInstance, 500, 300);
	wnd.AddDirectUIButton(&button, 0, 0);
	wnd.AddDirectUIButton(&button1, 50, 0);
	wnd.AddDirectUIButton(&button2, 100, 0);
	wnd.AddDirectUIButton(&button3, 150, 0);
	wnd.CreateDirectUIWnd(atom);
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
		//������Ϣ

		TranslateMessage(&msg);



		//�ַ���Ϣ

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
//	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;//�ͻ�����Ҫ��Ӧ˫������CS_DBLCLKS��ע���ȥ
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
//		//MessageBoxA(hwnd,buf,"hi",0);// �õ����˫���ļ��
//		return 0;
//
//
//	case WM_SIZE:
//		cxClient = LOWORD(lParam) / DIVISIONS;
//		cyClient = HIWORD(lParam) / DIVISIONS;
//		//if(IsIconic(hwnd))
//		//MessageBox(hwnd,TEXT("������Ȼ��С��"),TEXT("���"),0);
//		//if(IsZoomed(hwnd))
//		//MessageBox(hwnd,TEXT("������Ȼ���"),TEXT("���"),0);
//		return 0;
//	case WM_LBUTTONDBLCLK:
//		POINT point;
//		point.x = LOWORD(lParam);
//		point.y = HIWORD(lParam);
//		PostMessage(hwnd, WM_NCLBUTTONDBLCLK, HTCAPTION, MAKELPARAM(point.x, point.y));//ʵ����ƭ
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
//		PostMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));//ʵ����ƭ
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
//			SetWindowText(hwnd, TEXT("������ǿͻ���"));
//			return b;
//		case HTCAPTION:
//			SetWindowText(hwnd, TEXT("������Ǳ�����"));
//			return b;
//		case HTBOTTOM:
//			SetWindowText(hwnd, TEXT("��������±߿�"));
//			return b;
//		case HTBOTTOMLEFT:
//			SetWindowText(hwnd, TEXT("����������±߿�"));
//			return b;
//		case HTCLOSE:
//			SetWindowText(hwnd, TEXT("������ǹرհ�ť"));
//			return b;
//		case HTLEFT:
//			SetWindowText(hwnd, TEXT("���������߿�"));
//			return b;
//		case HTMAXBUTTON:
//			SetWindowText(hwnd, TEXT("���������󻯰�ť"));
//			return b;
//		case HTMINBUTTON:
//			SetWindowText(hwnd, TEXT("���������С����ť"));
//			return b;
//		case HTRIGHT:
//			SetWindowText(hwnd, TEXT("��������ұ߿�"));
//			return b;
//		case HTSYSMENU:
//			SetWindowText(hwnd, TEXT("�������ϵͳ�˵�"));
//			return b;
//		case HTTOP:
//			SetWindowText(hwnd, TEXT("��������ϱ߿�"));
//			return b;
//		case HTBOTTOMRIGHT:
//			SetWindowText(hwnd, TEXT("����������±߿�"));
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
	::OutputDebugString(L"���������� :");
	::OutputDebugString(ch);
	::OutputDebugString(L"\n");
	return CONTINUE;
}

RESULTCALLBACK DIRECTUIBUTTONCALLBACK::OnMouseMoveStartIn(CDirectUIButton* button)
{
	TCHAR ch[100];
	swprintf_s(ch, 100, L"button = %p", button);
	::OutputDebugString(L"������� :");
	::OutputDebugString(ch);
	::OutputDebugString(L"\n");
	return CONTINUE;
}

RESULTCALLBACK DIRECTUIBUTTONCALLBACK::OnLeftButtonClickUp(CDirectUIButton* button)
{
	TCHAR ch[100];
	swprintf_s(ch, 100, L"button = %p", button);
	::OutputDebugString(L"������̧�� :");
	::OutputDebugString(ch);
	::OutputDebugString(L"\n");
	return CONTINUE;
}

RESULTCALLBACK DIRECTUIBUTTONCALLBACK::OnMouseMoveIn(CDirectUIButton* button)
{
	TCHAR ch[100];
	swprintf_s(ch, 100, L"button = %p", button);
	::OutputDebugString(L"��������ƶ� :");
	::OutputDebugString(ch);
	::OutputDebugString(L"\n");
	return CONTINUE;
}

RESULTCALLBACK DIRECTUIBUTTONCALLBACK::OnMouseLeft(CDirectUIButton* button)
{
	TCHAR ch[100];
	swprintf_s(ch, 100, L"button = %p", button);
	::OutputDebugString(L"����뿪 :");
	::OutputDebugString(ch);
	::OutputDebugString(L"\n");
	return CONTINUE;
}
