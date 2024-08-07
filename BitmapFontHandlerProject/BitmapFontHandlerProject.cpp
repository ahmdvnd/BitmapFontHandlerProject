// BitmapFontHandlerProject.cpp : Defines the entry point for the application.
//

#include "BitmapFontHandlerProject.h"
#include "FontHandler/FontHandler.h"
#include "FontHandler/FontHandler.cpp"
using namespace std;

int main()
{
	FontsLoader();
	SetFontsLanguage(RightToLeft);
	PrintText((char*)"سلام دوست من  !", 0, 0, FONT_ADOBE_BOLD_42, My_Color_Blue, My_Color_Black, Simple_Line);
	PrintText((char*)"1234567890  !", 150, 0, FONT_ADOBE_BOLD_42, My_Color_Blue, My_Color_Black, Simple_Line);
	SetFontsLanguage(LeftToRight);
	PrintText((char*)"Hello World", 50, 0, FONT_ADOBE_BOLD_42, My_Color_Blue, My_Color_Black, Fill_Line);
	PrintText((char*)"1234567890", 100, 0, FONT_ADOBE_BOLD_42, My_Color_Blue, My_Color_Black, Center_Line);
	cv::waitKey(0);
	return 0;
}
