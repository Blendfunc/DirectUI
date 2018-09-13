#pragma once
enum DIRECTUITYPE
{
	DIRECTUI_BUTTON = 0 ,
	DIRECTUI_LABEL = 1 ,
	DIRECTUI_LIST = 2 ,

	DIRECTUI_EDIT = 3 ,



	DIRECTUI_UNDEFINE = 100
};

class CDirectUIBase
{
public:
	virtual void SetClassNameType(DIRECTUITYPE type) = 0;

	virtual DIRECTUITYPE GetClassNameType() = 0;

};