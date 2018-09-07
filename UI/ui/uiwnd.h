#pragma once
#include <windows.h>
#include <vector>
#include "uibutton.h"

class CDirectUIWnd;
typedef const std::map<int, std::map<int, CDirectUIBase*>>* window_ui_position;
class CDirectUIPositionManager
{
public:
	friend class CDirectUIWnd;
	CDirectUIPositionManager();
	~CDirectUIPositionManager();
	static CDirectUIPositionManager* GetDirectUIPositionManagerInstance();
	
	
	void RegisterDirectUIPositionManager(HWND h, CDirectUIWnd* wnd);
	void SetWindowMemoryDCMap(HWND h, HDC dc);
	
	HDC GetWindowMemoryDC(HWND h);
	CDirectUIBase* GetPointUI(HWND h, int x, int y);
	CDirectUIWnd* GetDirectUIWnd(HWND h);
	
	CDirectUIBase* GetCurrentUIBase(HWND h);

	void SetCurrentUIBase(HWND h, CDirectUIBase* base);

private:
	window_ui_position GetData(CDirectUIWnd& wnd);

	std::map<HWND, window_ui_position> m_Data;

	static CDirectUIPositionManager* m_Manager;

	std::map<HWND, HDC> m_Window_MemoryDC;

	std::map<HWND, CDirectUIWnd*> m_Window_DirectUIWindow;

	void SetWindowDirectUIWindow(HWND h, CDirectUIWnd* wnd);

	//CDirectUIBase* m_Current_UI;
	std::map<HWND, CDirectUIBase*> m_Current_UI_Map;
}; 


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
	CDirectUIWnd(HINSTANCE hinstance, int width = 400, int height = 300);
	~CDirectUIWnd();
	
	HWND CreateDirectUIWnd(ATOM classAtom, LPCWSTR lpWindowName = L"DirectUIWnd");
	void ShowDirectUIWnd();

	void AddDirectUIButton(CDirectUIButton* button);

	void RemoveDirectUIButton(CDirectUIButton** button);

	void UpdateMemoryDC(CDirectUIBase* base);
public:
	static HINSTANCE m_Hinstance;
	HWND m_HWND;
protected:
	std::map<int, std::map<int, CDirectUIBase*>>* GetWndUIMap();
private:
	friend window_ui_position CDirectUIPositionManager::GetData(CDirectUIWnd& wnd);
private:
	/*std::map<int, std::map<int, CDirectUIBase*>>* GetWndUIMap();*/
	typedef struct x_y_position
	{
		int x;
		int y;
	};
private:

	std::vector<CDirectUIButton*> m_button_map;

	std::map<int, std::map<int, CDirectUIBase*>> m_ui_map;

	void InitUIMap(int height, int width);

	int m_window_height;

	int m_window_width;

	HDC m_window_memory_dc;

	HBITMAP m_window_memory_dc_bitmap;


	void UpdateUIMap(int x, int y, CDirectUIBase* base);

	
};
