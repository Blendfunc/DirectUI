#include "uiwnd.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, PSTR szCmdLine, int iCmdShow)
{
	CDirectUIWndClass::GetCDirectUIWndClassInstance()->SetDirectUIWndAttribute(L"MyDirectUIWnd", hInstance);
	ATOM atom = CDirectUIWndClass::GetCDirectUIWndClassInstance()->RegisterDirectUIWndClass();

	CDirectUIWnd wnd(hInstance);
	wnd.CreateDirectUIWnd(atom);
	wnd.ShowDirectUIWnd();


	CDirectUIWnd wnd2(hInstance);
	wnd.CreateDirectUIWnd(atom, L"123456");
	wnd.ShowDirectUIWnd();
	
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