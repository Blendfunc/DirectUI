#include "uitext.h"
#include <fstream>
#include <string>

std::string GetCharSet(BYTE b);

int CALLBACK EnumFontFamExProc(const LOGFONTA* lpelfe, const TEXTMETRICA* lpntme, DWORD FontType, LPARAM lParam)
{


	/*::MessageBox(0, L"", L"", 0);*/
	//OutputDebugStringA(lpelfe->lfFaceName);
	//OutputDebugStringA(L"\n");

	std::ofstream ofile;
	ofile.open("c:\\font.txt", std::ios::app | std::ios::out);
	
	char chl[33];

	ofile << "�������ƣ�" << lpelfe->lfFaceName << "  ";//<< "\n" << std::flush;//std::endl

	ofile << "�ַ��߶ȣ�" << ltoa(lpelfe->lfHeight, chl, 10) << "  ";
	
	ofile << "�������ַ���ƽ����ȣ�" << ltoa(lpelfe->lfWidth, chl, 10) << "  ";
	
	ofile << "�Ƕȣ�" << ltoa(lpelfe->lfEscapement, chl, 10) << "  ";

	ofile << "�Ƕȣ�" << ltoa(lpelfe->lfOrientation, chl, 10) << "  ";

	ofile << "Ȩ�أ�" << ltoa(lpelfe->lfWeight, chl, 10) << "  ";

	const char* ch = lpelfe->lfItalic == 0 ? "��  " : "��  ";

	ofile << "�Ƿ�б�壺" << ch;

	ch = lpelfe->lfUnderline == 0 ? "��  " : "��  ";

	ofile << "�Ƿ���»��ߣ�" << ch;

	ch = lpelfe->lfStrikeOut == 0 ? "��  " : "��  ";

	ofile << "�Ƿ��ɾ���ߣ�" << ch;

	ofile << "�ַ�����" << GetCharSet(lpelfe->lfCharSet) << "  ";
///
	ofile << "�ַ��߶ȣ�" << ltoa(lpntme->tmHeight, chl, 10) << "  ";

	ofile << "�ַ���������" << ltoa(lpntme->tmAscent, chl, 10) << "  ";

	ofile << "�ַ����½���" << ltoa(lpntme->tmDescent, chl, 10) << "  ";

	ofile << "tmHeight��Ա���õı߽��ڵ�ǰ�����ո�����" << ltoa(lpntme->tmInternalLeading, chl, 10) << "  ";

	ofile << "Ӧ�ó�������֮����ӵĶ���ǰ�����ո�����" << ltoa(lpntme->tmExternalLeading, chl, 10) << "  ";

	ofile << "�������ַ���ƽ����ȣ�" << ltoa(lpntme->tmAveCharWidth, chl, 10) << "  ";

	ofile << "����������ַ��Ŀ�ȣ�" << ltoa(lpntme->tmMaxCharWidth, chl, 10) << "  ";

	ofile << "�����������" << ltoa(lpntme->tmWeight, chl, 10) << "  ";



	ofile << "\n" << std::flush;

	ofile.close();

	
	return 1;
}

std::string GetCharSet(BYTE b)
{
	std::string r;
	switch (b)
	{
	case ANSI_CHARSET :
	{
		r = "ANSI_CHARSET";
	}
	break;
	case BALTIC_CHARSET:
	{
		r = "BALTIC_CHARSET";
	}
	break;
	case CHINESEBIG5_CHARSET:
	{
		r = "CHINESEBIG5_CHARSET";
	}
	break;
	case DEFAULT_CHARSET:
	{
		r = "DEFAULT_CHARSET";
	}
	break;
	case EASTEUROPE_CHARSET:
	{
		r = "EASTEUROPE_CHARSET";
	}
	break;
	case GB2312_CHARSET:
	{
		r = "GB2312_CHARSET";
	}
	break;
	case GREEK_CHARSET:
	{
		r = "GREEK_CHARSET";
	}
	break;
	case HANGUL_CHARSET:
	{
		r = "HANGUL_CHARSET";
	}
	break;
	case MAC_CHARSET:
	{
		r = "MAC_CHARSET";
	}
	break;
	case OEM_CHARSET:
	{
		r = "OEM_CHARSET";
	}
	break;
	case RUSSIAN_CHARSET:
	{
		r = "RUSSIAN_CHARSET";
	}
	break;
	case SHIFTJIS_CHARSET:
	{
		r = "SHIFTJIS_CHARSET";
	}
	break;
	case SYMBOL_CHARSET:
	{
		r = "SYMBOL_CHARSET";
	}
	break;
	case TURKISH_CHARSET:
	{
		r = "TURKISH_CHARSET";
	}
	break;
	case VIETNAMESE_CHARSET:
	{
		r = "VIETNAMESE_CHARSET";
	}
	break;
	}
	return r;
}





void CDirectUIText::GetFonts()
{
	LOGFONTA lf;
	//memset(&lf, 0, sizeof(LOGFONT));
	lf.lfCharSet = DEFAULT_CHARSET;
	//lstrcpyW(lf.lfFaceName, L'\0');

	lf.lfFaceName[0] = '\0';

	lf.lfPitchAndFamily = 0;
	
	HWND hw = 0;
	HDC hdc = GetDC(hw);

	int i = EnumFontFamiliesExA(hdc, &lf, EnumFontFamExProc, 0, 0);

	//int j = EnumFontFamiliesEx(hdc, &lf, EnumFontFamExProc, 0, 0);


}
