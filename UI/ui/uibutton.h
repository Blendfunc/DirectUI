#pragma once
#include "uirect.h"
#include "uitype.h"

enum RESULTCALLBACK
{
	DONOTHING = 0 ,
	CONTINUE = 1  ,
	DONOTPAINT = 2
};

class IDirectUIButtonUICallBack
{
	virtual RESULTCALLBACK OnLeftButtonClickDown() = 0 ;

	virtual RESULTCALLBACK OnMouseMoveStartIn() = 0;

	virtual RESULTCALLBACK OnLeftButtonClickUp() = 0;

	virtual RESULTCALLBACK OnMouseMoveIn() = 0;

	virtual RESULTCALLBACK OnMouseLeft() = 0;
};

class CDirectUIButton : public CDirectUIBase
{
public:

	//void SetPosition(int left, int up, int right, int down);

	//void SetDirectUIButtonHeightWidth(int height, int width);

	//int GetDirectUIButtonHeight();


	//void SetDirectUIButtonWidth(int width);

	//int GetDirectUIButtonWidth();

	IDirectUIButtonUICallBack * GetEventCallBack();

	void SetEventCallBack(IDirectUIButtonUICallBack * callback);

	virtual void SetClassNameType(DIRECTUITYPE type);

	virtual DIRECTUITYPE GetClassNameType();

	void SetXPosition(int x);
	
	int GetXPosition();

	void SetYPosition(int y);

	int GetYPosition();

	const CDirectUIRect* GetDirectUIButtonRect();
private:
	CDirectUIRect m_Rect;
	IDirectUIButtonUICallBack * m_callback;
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};