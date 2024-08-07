#pragma once
#define My_Color_Black           0x0000      /*   0,   0,   0 */
#define My_Color_Navy            0x0009      /*   0,   0, 128 */
#define My_Color_DarkGreen       0x03E0      /*   0, 128,   0 */
#define My_Color_DarkCyan        0x03EF      /*   0, 128, 128 */
#define My_Color_Maroon          0x7800      /* 128,   0,   0 */
#define My_Color_Purple          0x780F      /* 128,   0, 128 */
#define My_Color_Olive           0x7BE0      /* 128, 128,   0 */
#define My_Color_LightGrey       0xC618      /* 192, 192, 192 */
#define My_Color_DarkGrey        0x7BEF      /* 128, 128, 128 */
#define My_Color_Blue            0x001F      /*   0,   0, 255 */
#define My_Color_Green           0x07E0      /*   0, 255,   0 */
#define My_Color_Cyan            0x07FF      /*   0, 255, 255 */
#define My_Color_Red             0xF800      /* 255,   0,   0 */
#define My_Color_Magenta         0xF81F      /* 255,   0, 255 */
#define My_Color_Yellow          0xFFE0      /* 255, 255,   0 */
#define My_Color_White           0xFFFF      /* 255, 255, 255 */
#define My_Color_Orange          0xFD20      /* 255, 165,   0 */
#define My_Color_GreenYellow     0xAFE5      /* 173, 255,  47 */
#define My_Color_Pink            0xF81F

#define My_Color_Test00			  0xF600
#define My_Color_Test0			  0xF700
#define My_Color_Test1			  0xF900
#define My_Color_Test2			  0xFA00
#define My_Color_Test3			  0xFB00
#define My_Color_Test4			  0xFC00
#ifdef vx820
#define Pixel_WIDTH  240
#define Pixel_HEIGHT  320
#define icFooterWidth  32
#define tempHeight 0
//#define Pixel_HEIGHT  320

#else
#define Pixel_WIDTH  320
#define Pixel_HEIGHT  240
#define icFooterWidth  32
#define tempHeight 0
//#define Pixel_HEIGHT  320
#endif

#define Char_WIDTH 40	
#define Char_HEIGHT 25
#define ROW_SIZE    25
#define COL_SIZE    40
#define HeaderX	0
#define HeaderY 0
#ifdef vx820
#define HeaderHeight 30
#define FOOTERHeight 30
#define LineSize	39

#else
#define HeaderHeight 30
#define FOOTERHeight 30
#define LineSize	45
#endif


#define HeaderWidth	Pixel_WIDTH  
#define FOOTERWidth	Pixel_WIDTH  




#define Simple_Line	0
#define Center_Line	1
#define Fill_Line	2

#define FONT_SEPTAHOMA_18  0  
#define FONT_SEPTAHOMA_20  1 
#define FONT_SEPTAHOMA_24  2 
#define FONT_SEPTAHOMA_30  3 
#define FONT_SEPTAHOMA_36  4 
#define FONT_SEPTAHOMA_44  5
#define FONT_ADOBE_BOLD_24 6
#define FONT_ADOBE_BOLD_32  7
#define FONT_ADOBE_BOLD_36  8
#define FONT_ADOBE_BOLD_42  9
#define FONT_ADOBE_REGULAR_20 10

#define LeftToRight	1
#define RightToLeft	0


#define SPACECHAR 32
#define NUL 0

#include <stdlib.h>
#include <stdio.h>
void	FontsLoader();
void	PrintText(char* txt,int Row,int Col,int FontName,int ForeColor,int BackColor,char ApparentMode);
void	PrintBackGround(int Row,int Col,int Height,int MyColor);
void	ClearScreen(int x,int y,int height,int width);
void	SetFontsLanguage(int lang);
char*	IntToString(int	num);
void	setDebug(char val);