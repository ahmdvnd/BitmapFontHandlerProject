#define PIXEL_MODE	1
//#include <svc.h>
#include "FontHandler.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>


#include "AdobeBold24.h"
#include "AdobeBold32.h"
#include "AdobeBold42.h"

#include "Background.h"
#include <stdarg.h>
#include <math.h>
#include <errno.h>

int Language=RightToLeft;//0 is Farsi
struct FontAttributes
{
	int id;
	int x;
	int y;
	int width;
	int height;
	int xoffset;
	int yoffset;
};
struct FontAttributes* Coordinates_FontTahoma_18;
struct FontAttributes* Coordinates_FontTahoma_20;
struct FontAttributes* Coordinates_FontTahoma_24;
struct FontAttributes* Coordinates_FontTahoma_30;
struct FontAttributes* Coordinates_FontTahoma_36;
struct FontAttributes* Coordinates_FontTahoma_44;
struct FontAttributes* Coordinates_AdobeBold_36;
struct FontAttributes* Coordinates_AdobeBold_32;
struct FontAttributes* Coordinates_AdobeBold_42;
struct FontAttributes* Coordinates_AdobeRegular_20;
struct FontAttributes* Coordinates_AdobeRegular_24;
struct FontAttributes* Coordinates_AdobeBold_24;

cv::Mat ImageDisplay = cv::Mat(Pixel_HEIGHT, Pixel_WIDTH, CV_8UC1);

struct FontAttributes* Coordinates_BYekan_30;
unsigned int	AVCharMap[500*4];
unsigned int	PAVCharMap[300];
int CharCount;
/* create 16 bit 5/6/5 format pixel from RGB triplet */
#define RGB2PIXEL565(r,g,b) \
	((((r) & 0xf8) << 8) | (((g) & 0xfc) << 3) | (((b) & 0xf8) >> 3))
short	ChangeBrightness(short  num,int amt)
{	
	short ret=0;
	short R = ((num >> 11)& 0x1F)  ;
	short G = ((num >> 5 )& 0x7E0) ;
	short B = ((num & 0x1F))       ;
	
	R*=amt/100.;
	G*=amt/100.;
	B*=amt/100.;

	/*return (((31*(R+amt))/255)<<11) | 
		(((63*(G+amt))/255)<<5) | 
		((31*(B+amt))/255);*/
	
	ret= ((R>31?31:R) << 11) | ((G>63?63:G) << 5) | (B>31?31:B);	
	return ret&num;

}

static int	CountRightZero(short int number)
{
	int i,num_zeroes = 0;

	for ( i = 0; i < 8 * sizeof number; ++i)
	{
		if ((number & (1 << i)) == 0)
			++num_zeroes;
	}
	return num_zeroes;
}
void	initial()
{
	memset(AVCharMap,0,sizeof(AVCharMap));
	AVCharMap[(uchar)'A'*4]=0x41;
	AVCharMap[(uchar)'B'*4]=0x42;
	AVCharMap[(uchar)'C'*4]=0x43;
	AVCharMap[(uchar)'D'*4]=0x44;
	AVCharMap[(uchar)'E'*4]=0x45;
	AVCharMap[(uchar)'F'*4]=0x46;
	AVCharMap[(uchar)'G'*4]=0x47;
	AVCharMap[(uchar)'H'*4]=0x48;
	AVCharMap[(uchar)'I'*4]=0x49;
	AVCharMap[(uchar)'J'*4]=0x4a;
	AVCharMap[(uchar)'K'*4]=0x4b;
	AVCharMap[(uchar)'L'*4]=0x4c;
	AVCharMap[(uchar)'M'*4]=0x4d;
	AVCharMap[(uchar)'N'*4]=0x4e;
	AVCharMap[(uchar)'O'*4]=0x4f;
	AVCharMap[(uchar)'P'*4]=0x50;
	AVCharMap[(uchar)'Q'*4]=0x51;
	AVCharMap[(uchar)'R'*4]=0x52;
	AVCharMap[(uchar)'S'*4]=0x53;
	AVCharMap[(uchar)'T'*4]=0x54;
	AVCharMap[(uchar)'U'*4]=0x55;
	AVCharMap[(uchar)'V'*4]=0x56;
	AVCharMap[(uchar)'W'*4]=0x57;
	AVCharMap[(uchar)'X'*4]=0x58;
	AVCharMap[(uchar)'Y'*4]=0x59;
	AVCharMap[(uchar)'Z'*4]=0x5a;

	AVCharMap[(uchar)'a'*4]=0x61;
	AVCharMap[(uchar)'b'*4]=0x62;
	AVCharMap[(uchar)'c'*4]=0x63;
	AVCharMap[(uchar)'d'*4]=0x64;
	AVCharMap[(uchar)'e'*4]=0x65;
	AVCharMap[(uchar)'f'*4]=0x66;
	AVCharMap[(uchar)'g'*4]=0x67;
	AVCharMap[(uchar)'h'*4]=0x68;
	AVCharMap[(uchar)'i'*4]=0x69;
	AVCharMap[(uchar)'j'*4]=0x6a;
	AVCharMap[(uchar)'k'*4]=0x6b;
	AVCharMap[(uchar)'l'*4]=0x6c;
	AVCharMap[(uchar)'m'*4]=0x6d;
	AVCharMap[(uchar)'n'*4]=0x6e;
	AVCharMap[(uchar)'o'*4]=0x6f;
	AVCharMap[(uchar)'p'*4]=0x70;
	AVCharMap[(uchar)'q'*4]=0x71;
	AVCharMap[(uchar)'r'*4]=0x72;
	AVCharMap[(uchar)'s'*4]=0x73;
	AVCharMap[(uchar)'t'*4]=0x74;
	AVCharMap[(uchar)'u'*4]=0x75;
	AVCharMap[(uchar)'v'*4]=0x76;
	AVCharMap[(uchar)'w'*4]=0x77;
	AVCharMap[(uchar)'x'*4]=0x78;
	AVCharMap[(uchar)'y'*4]=0x79;
	AVCharMap[(uchar)'z'*4]=0x7a;
	
	AVCharMap[(uchar)'~'*4]=(char)'~';
	AVCharMap[(uchar)'!'*4]=(char)'!';
	AVCharMap[(uchar)'@'*4]=(char)'@';
	AVCharMap[(uchar)'#'*4]=(char)'#';
	AVCharMap[(uchar)'$'*4]=(char)'$';
	AVCharMap[(uchar)'%'*4]=(char)'%';
	AVCharMap[(uchar)'^'*4]=(char)' ';
	AVCharMap[(uchar)'&'*4]=(char)'&';
	AVCharMap[(uchar)'('*4]=(char)'(';
	AVCharMap[(uchar)')'*4]=(char)')';
	AVCharMap[(uchar)'-'*4]=(char)'-';
	AVCharMap[(uchar)'='*4]=(char)'=';
	AVCharMap[(uchar)'+'*4]=(char)'+';
	AVCharMap[(uchar)'`'*4]=(char)'`';
	AVCharMap[(uchar)'['*4]=(char)'[';
	AVCharMap[(uchar)']'*4]=(char)']';
	AVCharMap[(uchar)'{'*4]=(char)'{';
	AVCharMap[(uchar)'}'*4]=(char)'}';
	AVCharMap[(uchar)'/'*4]=(char)'/';
	AVCharMap[(uchar)'\\'*4]=(char)'\\';
	AVCharMap[(uchar)'.'*4]=(char)'.';
	AVCharMap[(uchar)','*4]=(char)',';
	AVCharMap[(uchar)'?'*4]=(char)'?';
	AVCharMap[(uchar)'|'*4]=(char)'|';
	AVCharMap[(uchar)':'*4]=(char)':';
	AVCharMap[(uchar)'"'*4]=(char)'"';
	AVCharMap[(uchar)'*'*4]=(char)'*';
	AVCharMap[(uchar)' '*4]=(char)' ';



	AVCharMap[(uchar)'Â'*4]=0xFE81;

	AVCharMap[(uchar)'Ç'*4]=0xFE8D;
	AVCharMap[(uchar)'Ç'*4+1]=0xFE8E;
	AVCharMap[(uchar)'Ç'*4+2]=0xFE8E;
	AVCharMap[(uchar)'Ç'*4+3]=0xFE8D;

	AVCharMap[(uchar)'È'*4]=0xFE91;
	AVCharMap[(uchar)'È'*4+1]=0xFE92;
	AVCharMap[(uchar)'È'*4+2]=0xFE90;
	AVCharMap[(uchar)'È'*4+3]=0xFE8F;
	
	AVCharMap[(uchar)''*4]=  0xFB58;
	AVCharMap[(uchar)''*4+1]=0xFB59;
	AVCharMap[(uchar)''*4+2]=0xFB57;
	AVCharMap[(uchar)''*4+3]=0xFB56;
	
	AVCharMap[(uchar)'Ê'*4]=0xFE97;
	AVCharMap[(uchar)'Ê'*4+1]=0xFE98;
	AVCharMap[(uchar)'Ê'*4+2]=0xFE96;
	AVCharMap[(uchar)'Ê'*4+3]=0xFE95;
	
	AVCharMap[(uchar)'Ë'*4]=0xFE9B;
	AVCharMap[(uchar)'Ë'*4+1]=0xFE9C;
	AVCharMap[(uchar)'Ë'*4+2]=0xFE9A;
	AVCharMap[(uchar)'Ë'*4+3]=0xFE99;

	AVCharMap[(uchar)'Ì'*4]=0xFE9F;
	AVCharMap[(uchar)'Ì'*4+1]=0xFEA0;
	AVCharMap[(uchar)'Ì'*4+2]=0xFE9E;
	AVCharMap[(uchar)'Ì'*4+3]=0xFE9D;
	
	AVCharMap[(uchar)''*4]=0xFB7C;
	AVCharMap[(uchar)''*4+1]=0xFB7D;
	AVCharMap[(uchar)''*4+2]=0xFB7B;
	AVCharMap[(uchar)''*4+3]=0xFB7A;
	
	AVCharMap[(uchar)'Í'*4]=0xFEA3;
	AVCharMap[(uchar)'Í'*4+1]=0xFEA4;
	AVCharMap[(uchar)'Í'*4+2]=0xFEA2;
	AVCharMap[(uchar)'Í'*4+3]=0xFEA1;
	
	AVCharMap[(uchar)'Î'*4]=0xFEA7;
	AVCharMap[(uchar)'Î'*4+1]=0xFEA8;
	AVCharMap[(uchar)'Î'*4+2]=0xFEA6;
	AVCharMap[(uchar)'Î'*4+3]=0xFEA5;
	
	AVCharMap[(uchar)'Ï'*4]=0xFEA9;
	AVCharMap[(uchar)'Ï'*4+1]=0xFEAA;
	AVCharMap[(uchar)'Ï'*4+2]=0xFEAA;
	AVCharMap[(uchar)'Ï'*4+3]=0xFEA9;
	
	AVCharMap[(uchar)'Ð'*4]=0xFEAB;
	AVCharMap[(uchar)'Ð'*4+1]=0xFEAC;
	AVCharMap[(uchar)'Ð'*4+2]=0xFEAC;
	AVCharMap[(uchar)'Ð'*4+3]=0xFEAB;
	
	AVCharMap[(uchar)'Ñ'*4]=0xFEAD;
	AVCharMap[(uchar)'Ñ'*4+1]=0xFEAE;
	AVCharMap[(uchar)'Ñ'*4+2]=0xFEAE;
	AVCharMap[(uchar)'Ñ'*4+3]=0xFEAD;
	
	AVCharMap[(uchar)'Ò'*4]=0xFEAF;
	AVCharMap[(uchar)'Ò'*4+1]=0xFEB0;
	AVCharMap[(uchar)'Ò'*4+2]=0xFEB0;
	AVCharMap[(uchar)'Ò'*4+3]=0xFEAF;
	
	AVCharMap[(uchar)'Ž'*4]=0xFB8A;
	AVCharMap[(uchar)'Ž'*4+1]=0xFB8B;
	AVCharMap[(uchar)'Ž'*4+2]=0xFB8B;
	AVCharMap[(uchar)'Ž'*4+3]=0xFB8A;
	
	AVCharMap[(uchar)'Ó'*4]=0xFEB3;
	AVCharMap[(uchar)'Ó'*4+1]=0xFEB4;
	AVCharMap[(uchar)'Ó'*4+2]=0xFEB2;
	AVCharMap[(uchar)'Ó'*4+3]=0xFEB1;

	AVCharMap[(uchar)'Ô'*4]=0xFEB7;
	AVCharMap[(uchar)'Ô'*4+1]=0xFEB8;
	AVCharMap[(uchar)'Ô'*4+2]=0xFEB6;
	AVCharMap[(uchar)'Ô'*4+3]=0xFEB5;
	
	AVCharMap[(uchar)'Õ'*4]=0xFEBB;
	AVCharMap[(uchar)'Õ'*4+1]=0xFEBC;
	AVCharMap[(uchar)'Õ'*4+2]=0xFEBA;
	AVCharMap[(uchar)'Õ'*4+3]=0xFEB9;
	
	AVCharMap[(uchar)'Ö'*4]=0xFEBF;
	AVCharMap[(uchar)'Ö'*4+1]=0xFEC0;
	AVCharMap[(uchar)'Ö'*4+2]=0xFEBE;
	AVCharMap[(uchar)'Ö'*4+3]=0xFEBD;
	
	AVCharMap[(uchar)'Ø'*4]=0xFEC3;
	AVCharMap[(uchar)'Ø'*4+1]=0xFEC4;
	AVCharMap[(uchar)'Ø'*4+2]=0xFEC2;
	AVCharMap[(uchar)'Ø'*4+3]=0xFEC1;
	
	AVCharMap[(uchar)'Ù'*4]=0xFEC7;
	AVCharMap[(uchar)'Ù'*4+1]=0xFEC8;
	AVCharMap[(uchar)'Ù'*4+2]=0xFEC6;
	AVCharMap[(uchar)'Ù'*4+3]=0xFEC5;
	
	AVCharMap[(uchar)'Ú'*4]=0xFECB;
	AVCharMap[(uchar)'Ú'*4+1]=0xFECC;
	AVCharMap[(uchar)'Ú'*4+2]=0xFECA;
	AVCharMap[(uchar)'Ú'*4+3]=0xFEC9;
	
	AVCharMap[(uchar)'Û'*4]=0xFECF;
	AVCharMap[(uchar)'Û'*4+1]=0xFED0;
	AVCharMap[(uchar)'Û'*4+2]=0xFECE;
	AVCharMap[(uchar)'Û'*4+3]=0xFECD;

	AVCharMap[(uchar)'Ý'*4]=0xFED3;
	AVCharMap[(uchar)'Ý'*4+1]=0xFED4;
	AVCharMap[(uchar)'Ý'*4+2]=0xFED2;
	AVCharMap[(uchar)'Ý'*4+3]=0xFED1;
	
	AVCharMap[(uchar)'Þ'*4]=0xFED7;
	AVCharMap[(uchar)'Þ'*4+1]=0xFED8;
	AVCharMap[(uchar)'Þ'*4+2]=0xFED6;
	AVCharMap[(uchar)'Þ'*4+3]=0xFED5;
	
	AVCharMap[(uchar)'˜'*4]=0xFEDb;	
	AVCharMap[(uchar)'˜'*4+1]=0xFEDC;	
	AVCharMap[(uchar)'˜'*4+2]=0xFEDA;	
	AVCharMap[(uchar)'˜'*4+3]=0xFED9;	
	
	AVCharMap[(uchar)''*4]=0xFB94;
	AVCharMap[(uchar)''*4+1]=0xFB95;
	AVCharMap[(uchar)''*4+2]=0xFB93;
	AVCharMap[(uchar)''*4+3]=0xFB92;
	
	AVCharMap[(uchar)'á'*4]=0xFEDF;
	AVCharMap[(uchar)'á'*4+1]=0xFEE0;
	AVCharMap[(uchar)'á'*4+2]=0xFEDE;
	AVCharMap[(uchar)'á'*4+3]=0xFEDD;
	
	AVCharMap[(uchar)'ã'*4]=0xFEE3;
	AVCharMap[(uchar)'ã'*4+1]=0xFEE4;
	AVCharMap[(uchar)'ã'*4+2]=0xFEE2;
	AVCharMap[(uchar)'ã'*4+3]=0xFEE1;
	
	AVCharMap[(uchar)'ä'*4]=0xFEE7;
	AVCharMap[(uchar)'ä'*4+1]=0xFEE8;
	AVCharMap[(uchar)'ä'*4+2]=0xFEE6;
	AVCharMap[(uchar)'ä'*4+3]=0xFEE5;

	AVCharMap[(uchar)'æ'*4]=0xFEED;
	AVCharMap[(uchar)'æ'*4+1]=0xFEEE;
	AVCharMap[(uchar)'æ'*4+2]=0xFEEE;
	AVCharMap[(uchar)'æ'*4+3]=0xFEED;

	AVCharMap[(uchar)'å'*4]=0xFEEB;
	AVCharMap[(uchar)'å'*4+1]=0xFEEC;
	AVCharMap[(uchar)'å'*4+2]=0xFEEA;
	AVCharMap[(uchar)'å'*4+3]=0xFEE9;


	/*AVCharMap[(uchar)'?'*4]=0xFEF3;
	AVCharMap[(uchar)'?'*4+1]=0xFEF4;
	AVCharMap[(uchar)'?'*4+2]=0xFEF2;
	AVCharMap[(uchar)'?'*4+3]=0xFEF1;*/
	
	AVCharMap[(uchar)'í'*4]=0xFEF3;
	AVCharMap[(uchar)'í'*4+1]=0xFEF4;
	AVCharMap[(uchar)'í'*4+2]=0xFEF2;
	AVCharMap[(uchar)'í'*4+3]=0xFEF1;

	AVCharMap[(uchar)'Æ'*4]=0xFE8B;
	AVCharMap[(uchar)'Æ'*4+1]=0xFE8C;
	AVCharMap[(uchar)'Æ'*4+2]=0xFE8A;
	AVCharMap[(uchar)'Æ'*4+3]=0xFE89;

	AVCharMap[(uchar)'0'*4]=0x660;
	AVCharMap[(uchar)'1'*4]=0x661;
	AVCharMap[(uchar)'2'*4]=0x662;
	AVCharMap[(uchar)'3'*4]=0x663;
	AVCharMap[(uchar)'4'*4]=0x664;
	AVCharMap[(uchar)'5'*4]=0x665;
	AVCharMap[(uchar)'6'*4]=0x666;
	AVCharMap[(uchar)'7'*4]=0x667;
	AVCharMap[(uchar)'8'*4]=0x668;
	AVCharMap[(uchar)'9'*4]=0x669;
	AVCharMap[(uchar)'¿'*4]=0x61F;

}
void	swap_int(int* str, int i, int j){
	int t = str[i];
	str[i] = str[j];
	str[j] = t;
}

void	reverse_int(int* src, int length){
	int i = 0;
	for(i=0; i<length/2; i++)
	{
		swap_int(src, i, length-i-1);
	}
}
void	reverse(int* src, int length)
{
	int i,j,temp;
	j = length - 1;   // j will Point to last Element
	i = 0;       // i will be pointing to first element

	while (i < j) {
		temp = src[i];
		src[i] = src[j];
		src[j] = temp;
		i++;             // increment i
		j--;          // decrement j
	}

}
__inline	unsigned char  SingleShape(int Current)
{
	return (Current==(char)'æ')||(Current==(char)'Ò')||(Current==(char)'Ñ')||(Current==(char)'Ž')||(Current==(char)'Ï')||(Current==(char)'Ð');
}

__inline	unsigned char IS_NUMBER(int Current) 
{
	return ((Current>1631) && (Current<1642)) || ((Current>47) && (Current<58));
}

__inline	unsigned char IS_LATIN(int Current)
{
	return	(((Current>64)&&(Current<91))||((Current>96)&&(Current<123)));
}

__inline unsigned char IS_SYMBOL(int Current)
{
	return (
	(Current==(char)'~')||
	(Current==(char)'!')||
	(Current==(char)'@')||
	(Current==(char)'#')||
	(Current==(char)'$')||
	(Current==(char)'%')||
	(Current==(char)'^')||
	(Current==(char)'&')||
	(Current==(char)'(')||
	(Current==(char)')')||
	(Current==(char)'-')||
	(Current==(char)'=')||
	(Current==(char)'+')||
	(Current==(char)'`')||
	(Current==(char)'[')||
	(Current==(char)']')||
	(Current==(char)'{')||
	(Current==(char)'}')||
	(Current==(char)'/')||
	(Current==(char)'\\')|
	(Current==(char)'.')||
	(Current==(char)',')||
	(Current==(char)'?')||
	(Current==(char)'|')||
	(Current==(char)':')||
	(Current==(char)'"')||
	(Current==(char)'¿')||
	(Current==(char)'*')||
	(Current>0&&Current<32)
	);
}

/*
0 ÈÜ
1 ÜÈÜ 
2 Ü˜
3 ˜
*/
int		CharPosition(char Current,char Left,char Right)
{

	unsigned char t = 0x00; // Left Modifier
	char C1,C2,C3,C4,AfterTheseStartFirst,AfterTheseFinish,Numbers,RightNumbers,RightLatin,RightSymbol,LeftSymbol,LeftLatin,CurrentIsLatin,CurrentIsSymbols,LeftNumber;
	
	RightNumbers=IS_NUMBER(Right);
	RightSymbol=IS_SYMBOL(Right);
	RightLatin=IS_LATIN(Right);
	Numbers=IS_NUMBER(Current);
	LeftNumber=IS_NUMBER(Left);
	LeftSymbol=IS_SYMBOL(Left);
	LeftLatin=IS_LATIN(Left);
	CurrentIsLatin=IS_LATIN(Current) ;
	CurrentIsSymbols=IS_SYMBOL(Current) ;
	AfterTheseFinish=LeftLatin || (Right==(char)'Â') || (Right==(char)'Ç') || SingleShape(Right);
	AfterTheseStartFirst=(RightLatin)||(RightSymbol)||(Right==(char)'Â')||(Right==(char)'Ç')||SingleShape(Right);

	C1=(Left!=NUL)&&(Left!=SPACECHAR);//Not Finisher Char
	C2=(Left==NUL)||(Left==SPACECHAR);//to be Finisher Char
	C3=(Right==NUL)||(Right==SPACECHAR);//to be Starter Char
	C4=(Right!=NUL)&&(Right!=SPACECHAR);//Not Starter Char

	if (Numbers || CurrentIsSymbols || RightNumbers || RightSymbol  || CurrentIsLatin || Current==SPACECHAR)
	{
		//printf("im here1\n");
		return	0;
	}
	if(C1 && C3)//ÈÜ
	{
		//printf("im here2\n");		
		return 0;
	}else	if(C1 && C4)//ÜÈÜ
	{
		if(AfterTheseStartFirst)//æÈÜ ÇÈÜ
		{
			//printf("im here3\n");
			if (LeftSymbol)
			{
				return	3;
			}

			return	0;
		}else if(LeftNumber||LeftSymbol||LeftLatin)
		{			
			if (SingleShape(Current)||LeftSymbol)
			{
				return 2;
			}
			return	3;
		}
		return	1;
	}else	if(C2 && C4)//ÜÈ
	{
		if (AfterTheseFinish)//æå
		{
			return	3;
		}
		return	2;
	}else	if (C2&&C3)//å
	{
		return	3;
	}
	return t;
}
//Detect charachter polymorphis and LTR numbers
void	PersianNormalize2(int* output, char *input1, int len){
	int i = 0;
	int i2 = 0;
	int c=0,WordCount=0;
	int f=0;//First Char in word
	int x1=0,x2=0,CharachterCount=0,WordLen=0,k=0,DoReverse=0,WordProgressed=0;
	int* tmp=(int*)malloc(len*sizeof(int));
	memset(tmp,0,len*sizeof(int));
	
#pragma region Charachter Mapping
	for (i = 0;i <len; i++) 
	{
		int chr;
		int R=0;
		int L=0;		
		char C1,C2,C3,C4;
		
		if (((char)input1[i])==SPACECHAR)
		{
			//f=0;
		}

		C1=(f==0);
		C2=(i+1<len);
		C3=!C2;
		C4=(i>0);


		if (C1 && C2)
		{
			R=NUL;
			L=input1[i+1];
		} 
		else if(C1 && C3)
		{
			L=R=NUL;			
		}
		else if(C4 && C2)
		{
			R=input1[i-1];
			L=input1[i+1];
		}
		else if(C4 && C3)
		{
			R=input1[i-1];
			L=NUL;
		}
		f++;
		
		chr =CharPosition(input1[i],L,R);
		
		output[i] = AVCharMap[((uchar)input1[i])*4+chr];
		C1=IS_NUMBER(input1[i]);
		if (C1 && (Language==LeftToRight))
		{
			output[i]=input1[i];
		}
	}
#pragma endregion Charachter Mapping

	
#pragma region  Reverse English And Number Charachter
	for (i=0;i<len;i++)
	{
		char C1=0,C2=0,C3=0,C4=0;		
		C1=IS_SYMBOL(output[i]);		
		C2=IS_LATIN(output[i]);
		C4=IS_NUMBER(output[i]);			

		if (Language==LeftToRight)
		{		
			C3 = (output[i] == SPACECHAR) && 
				(
				(output[i+1] == SPACECHAR)||
				IS_LATIN (output[i + 1])  ||
				IS_NUMBER(output[i + 1])  || 
				IS_SYMBOL(output[i + 1])
				);
		}
		else
		{
			C3 = (output[i] == SPACECHAR) && (i + 1<len) && (output[i] == ':') && (IS_LATIN(output[i + 1]) || (output[i + 1] == SPACECHAR) || IS_NUMBER(output[i + 1]));
		}
		if (C1 || C2 || C3 || C4)
		{
			tmp[c++]=i;			
		}else if (c>1 )
		{
			reverse_int(&output[tmp[0]],c);
			c=0;
		}else
		{
			c=0;
		}
	}
	if (c>1)
	{
		reverse_int(&output[tmp[0]],c);
		c=0;
	}
#pragma endregion  Reverse English And Number Charachter

	
#pragma region  Reverse English And Number Word
i2=0;
f=0;
	for (i = 0;i<len && 0;i++)
	{

		char C0 = (output[i] == SPACECHAR);
		char C1 = (output[i] >= 48) && (output[i] <= 57);//Numbers
		char C2 = (output[i] >= 65) && (output[i] <= 90);
		char C3 = (output[i] >= 91) && (output[i] <= 122);
		char C4 = (output[i] >= 33) && (output[i] <= 64);//	Symbols *+/\...
		char AllowdSpace = C0 && (i>0) && (output[i - 1] != SPACECHAR);
		char ReverseChar = C1 || C2 || C3 || C4;
		char LastChar = i == (len - 1);

		if (ReverseChar&&LastChar)//Last Single ReverseChar
		{
			tmp[i2++] = i;
			f++;
			CharachterCount++;
			WordCount++;
			if (f == 1)//Single ReverseChar
			{
				tmp[i2++] = (i);
			}
			f = 0;
			//printf("LastChar ReverseChar :%d\n", i);
			DoReverse = 1;
			//printf("3:%d\n",(i));

		}
		else if (ReverseChar && (f == 0))//First ReverseChar
		{
			tmp[i2++] = i;
			f++;
			CharachterCount++;
			//printf("1:%d\n",i);
		}
		else if (ReverseChar)//ReverseChar between word
		{
			f++;
			CharachterCount++;
			if (LastChar)
			{
				tmp[i2++] = (i);
				WordCount++;
				if (f == 1)//Single ReverseChar
				{
					tmp[i2++] = (i);
					//printf("LastChar :%d\n",i);					
				}
				f = 0;

				//printf("3:%d\n",(i));
			}
			//printf("2:%d\n",i);					
		}
		else if (AllowdSpace && f>0)
		{
			if (LastChar)
			{
				DoReverse = 1;
			}
			tmp[i2++] = (i - 1);
			WordCount++;
			CharachterCount++;
			f = 0;
			//printf("4 End:%d\n",(i-1));
		}
		else
		{
			DoReverse = 1;
		}
		if (DoReverse == 1)
		{
			int PassedChar = 0;
			int* SelectedWord =(int*)malloc(sizeof(int) * (CharachterCount + 1));//charCount+spaceCount]
			memset(SelectedWord, 0, sizeof(int)*(CharachterCount + 1));
			for (k = WordCount - 1;k>-1;k--)
			{
				x1 = tmp[(k + WordProgressed) * 2];
				x2 = tmp[(k + WordProgressed) * 2 + 1];
				WordLen = x2 - x1 + 1/*space in after word*/;

				//printf("%d,%d%,%d,%d\n",x1,x2,WordLen,CharachterCount);

				memcpy(SelectedWord + PassedChar, output + x1, WordLen*sizeof(int));
				PassedChar += WordLen;
				SelectedWord[PassedChar++] = SPACECHAR;

			}
			if (WordCount>0)
			{				
				memcpy(output + ((int)tmp[WordProgressed * 2]), SelectedWord, CharachterCount * sizeof(int));
				WordProgressed += WordCount;
				CharachterCount = WordCount = 0;
				f = 0;
			}
			free(SelectedWord);
			DoReverse = 0;
		}
	}
#pragma endregion  Reverse English And Number Word
	free(tmp);
}

void	FontsMapLoader(char* Path,struct FontAttributes** Treasury)
{	
	FILE * pFile;
	uchar tmp[4]={0};
	int i;
	initial();
	pFile = fopen(Path, "r");
	if (pFile != NULL)
	{		
		long hm=0;
		CharCount = 0;
		fread(tmp,sizeof(int) , 1, pFile);
		CharCount=(tmp[3]<<24)|(tmp[2]<<16)|(tmp[1]<<8)|tmp[0];
		Treasury[0]=(struct FontAttributes*)malloc(CharCount*sizeof(struct FontAttributes));		
		if (!Treasury[0])
		{
			printf("err: %s\n",strerror(errno));
			return;
		}
		for (i = 0; i < CharCount; i++)
		{

			uchar tmp[4]={0};
			struct FontAttributes item ;
			fread(tmp,		sizeof(int), 1, pFile);			 
			item.id=(tmp[3]<<24)|(tmp[2]<<16)|(tmp[1]<<8)|tmp[0];
			
			fread(tmp,		sizeof(int), 1, pFile);
			item.x=(tmp[3]<<24)|(tmp[2]<<16)|(tmp[1]<<8)|tmp[0];

			fread(tmp,		sizeof(int), 1, pFile);
			item.y=(tmp[3]<<24)|(tmp[2]<<16)|(tmp[1]<<8)|tmp[0];

			fread(tmp,		sizeof(int), 1, pFile);
			item.width=(tmp[3]<<24)|(tmp[2]<<16)|(tmp[1]<<8)|tmp[0];

			fread(tmp,		sizeof(int), 1, pFile);
			item.height=(tmp[3]<<24)|(tmp[2]<<16)|(tmp[1]<<8)|tmp[0];

			fread(tmp,		sizeof(int), 1, pFile);
			item.xoffset=(tmp[3]<<24)|(tmp[2]<<16)|(tmp[1]<<8)|tmp[0];

			fread(tmp,		sizeof(int), 1, pFile);
			item.yoffset=(tmp[3]<<24)|(tmp[2]<<16)|(tmp[1]<<8)|tmp[0];							
			
			fseek(pFile, (i + 1) * 7 * sizeof(int)+ sizeof(int), 0);//IN C++ Shall be used
			Treasury[0][i]= item;					
		}
		fclose(pFile);		
	}
}
/*********************************************************************\

in The Font Header the Charachters should be apparent as BLACK
Font Paddings for All Direction are 0;
Spacings are 1 
*/
void	ExtractFromTreasury(int x,int y,int width,int height,short _TextColor,short _BackColor,short* FontTreasury,int FontTreasury_Width,uchar* dst)
{
	int i;
	int j;
	int c=0;
	//int shiftCount=CountRightZero(_TextColor);
	for (i=y;i<y+height;i++)
	{
		for (j=x;j<x+width;j++)
		{
			//dst[c++]=(byekan_0[i][j]>0)?_TextColor:_BackColor;
			//dst[c++]=(FontTreasury[i* FontTreasury_Width+ j]>0)?_TextColor:_BackColor;
			int tmp=(FontTreasury[i* FontTreasury_Width+ j]);
			if (tmp>100)
			{
				dst[c++] = 255;// _TextColor;
			}else if (tmp>0)
			{
				dst[c++]=_TextColor+(128-(short)tmp/2.);							
			}			
			else
			{
				dst[c++]=_BackColor;
			}
		}		
	}
}
void	BackGroundDrawer(int x,int y,int width,int height,short color,char PasteOnCenter)
{
	int i;
	int c=0;
	int j;
	int tmp=0;
	if (PasteOnCenter>0)
	{
		width=Pixel_WIDTH;
		x=0;		
	}
	
	for (i=0;i<height*width;i++)
	{
		Background[i] =color;
	}
	//TO DO	
	//display_frame_buffer(x,y,width,height,(short*)Background);
	cv::Rect roi(x, y, width, height);
	//Create the cv::Mat with the ROI you need, where "image" is the cv::Mat you want to extract the ROI from
	ImageDisplay(roi)= color;

	//cv::Mat image=cv::Mat(height,width, CV_16UC1, Background);
	//cv::imshow(cv::String("Display Image"), ImageDisplay);

}
int		GetCharCoordinate(int _ID,struct FontAttributes* Treasury)
{
int i;

	for (i=0;i<CharCount;i++)
	{
		if (Treasury[i].id==_ID)
		{
			return	i;
		}
	}
return -1;
}
void	SetFontsLanguage(int lang)
{
	Language=lang;
}
void	DrawingText(int _Row,int _Column,char ApparentMode,struct FontAttributes** _Terms,int _Length, short _TextColor,short _BackColor,int FontName)
{
	int totalWidth=0;
	int MaxHeight=0;
	int Margin=5;
	int i,i2,x,xHelper=0;
	int PastWidth=0;
	short* FontTreasury;
	int FontTreasury_Width;
	switch (FontName)
	{
	case FONT_ADOBE_BOLD_32:
		{
			FontTreasury=AdobeBold32[0];
			FontTreasury_Width = sizeof AdobeBold32[0] / sizeof AdobeBold32[0][0]; 
		}break;
	case FONT_ADOBE_BOLD_42:
		{
			FontTreasury=AdobeBold42[0];
			FontTreasury_Width = sizeof AdobeBold42[0] / sizeof AdobeBold42[0][0]; 
		}break;
	case FONT_ADOBE_BOLD_24:
		{
			FontTreasury=AdobeBold24[0];
			FontTreasury_Width = sizeof AdobeBold24[0] / sizeof AdobeBold24[0][0]; 
		}break;

}
	for (i=0;i<_Length;i++)
	{
		totalWidth+=_Terms[i]->width;
		if ((_Terms[i]->height+abs(_Terms[i]->yoffset)) >MaxHeight)
		{
			MaxHeight=(_Terms[i]->height+abs(_Terms[i]->yoffset));
		}
	}
	//MaxHeight+=Margin;
	//if(get_display_coordinate_mode()!=PIXEL_MODE)
		//set_display_coordinate_mode(PIXEL_MODE);

	//printf("Im Here 1: %d,%d\n",MaxHeight,totalWidth);
	if (Language==RightToLeft)
	{
		x=(Pixel_WIDTH-totalWidth-_Column);
	}else if(Language==LeftToRight)
	{
		x=_Column;
	}
	//BackGroundDrawer(x,_Row,totalWidth,MaxHeight,_BackColor,ApparentMode);	
	switch (ApparentMode)
	{
		case Simple_Line:
		{
			xHelper=0;
		}break;
		case Center_Line://Paste on Center
		{
			xHelper=(Pixel_WIDTH-totalWidth)/2;			
		}break;
		case Fill_Line://Fill Line
		{
			totalWidth=Pixel_WIDTH;
		}break;
	}

	

	for (i2=0;i2<_Length;i2++)
	{
		uchar*	verb;
		if (Language==RightToLeft)//FARSI
		{
			i=i2;
			PastWidth+=_Terms[i]->width;
			x=(Pixel_WIDTH-PastWidth-_Column)+ _Terms[i]->xoffset-xHelper;
		}else if(Language==LeftToRight)//English
		{
			i=_Length-i2-1;
			x=(PastWidth+_Column)+ _Terms[i]->xoffset+xHelper;
			PastWidth+=_Terms[i]->width;
		}	
		if (PastWidth>Pixel_WIDTH)
		{
			break;
		}
		verb=(uchar*)malloc(sizeof(uchar)*(_Terms[i]->width*_Terms[i]->height));
		ExtractFromTreasury(_Terms[i]->x,_Terms[i]->y,_Terms[i]->width,_Terms[i]->height,_TextColor,_BackColor,FontTreasury,FontTreasury_Width,verb);					
		//TO DO
		//display_frame_buffer(x,_Terms[i]->yoffset+_Row,_Terms[i]->width,_Terms[i]->height,verb);//ONLY SHORT, set_display_color Not Affect on it,		
		cv::Mat verbTmp = cv::Mat(_Terms[i]->height, _Terms[i]->width, CV_8UC1, verb);
		cv::Rect roi(x, _Terms[i]->yoffset + _Row, _Terms[i]->width, _Terms[i]->height);
		verbTmp.copyTo(ImageDisplay(roi));
		free(verb);
	}
}

void	PrintText(char* txt,int Row,int Col,int FontName,int ForeColor,int BackColor,char ApparentMode)
{

	int i;
	int tmp;
	int* buff;	
	struct FontAttributes** SelectedChar;
	int CharachterCount;
	struct FontAttributes* CoordinatesTreasury;
	if (txt==0)
	{
		return;
	}
	CharachterCount=strlen(txt);
	buff=(int*)malloc(CharachterCount*sizeof(int));
	//
	PersianNormalize2(buff,txt,CharachterCount);
	SelectedChar=(struct FontAttributes**)malloc(sizeof(struct FontAttributes*)*CharachterCount);

	switch (FontName)
	{
	case FONT_SEPTAHOMA_18:
		{
			CoordinatesTreasury=Coordinates_FontTahoma_18;			
		}break;
	case 	FONT_SEPTAHOMA_20:
		{
			CoordinatesTreasury=Coordinates_FontTahoma_20;			
		}break;
	case 	FONT_SEPTAHOMA_24:
		{
			CoordinatesTreasury=Coordinates_FontTahoma_24;			
		}break;
	case 	FONT_SEPTAHOMA_30:
		{
			CoordinatesTreasury=Coordinates_FontTahoma_30;			
		}break;
	case 	FONT_SEPTAHOMA_36:
		{
			CoordinatesTreasury=Coordinates_FontTahoma_36;			
		}break;
	case 	FONT_SEPTAHOMA_44:
		{
			CoordinatesTreasury=Coordinates_FontTahoma_44;			
		}break;
	case 	FONT_ADOBE_BOLD_36:
		{
			CoordinatesTreasury=Coordinates_AdobeBold_36;
		}break;
	case 	FONT_ADOBE_BOLD_32:
		{
			CoordinatesTreasury=Coordinates_AdobeBold_32;
		}break;
	case 	FONT_ADOBE_BOLD_42:
		{
			CoordinatesTreasury=Coordinates_AdobeBold_42;
		}break;
	case 	FONT_ADOBE_REGULAR_20:
		{
			CoordinatesTreasury=Coordinates_AdobeRegular_20;			
		}break;
	case 	FONT_ADOBE_BOLD_24:
		{
			CoordinatesTreasury=Coordinates_AdobeBold_24;			
		}break;

	}

	for (i = 0; i < CharachterCount; i++) 
	{
		//printf("%d\n",buff[i]);
		tmp=GetCharCoordinate(buff[i],CoordinatesTreasury);
		if (tmp==-1)
		{
			tmp=GetCharCoordinate(SPACECHAR,CoordinatesTreasury);
		}
		SelectedChar[i]=&CoordinatesTreasury[tmp];		
	}
	free(buff);
	DrawingText(Row,Col,ApparentMode,SelectedChar,CharachterCount,ForeColor,BackColor,FontName);		
	free(SelectedChar);
	//printf("im here 1\n",tmp);

	
	cv::imshow(cv::String("Display Image"), ImageDisplay);
	///cv::waitKey(0);
	//cv::imwrite("c:/test.bmp", ImageDisplay);

}

void	FontsLoader()
{	
	Coordinates_FontTahoma_18=
	Coordinates_FontTahoma_20=
	Coordinates_FontTahoma_24=
	Coordinates_FontTahoma_30=
	Coordinates_FontTahoma_36=
	Coordinates_FontTahoma_44=
	Coordinates_AdobeRegular_20=
	Coordinates_AdobeBold_24=
	Coordinates_AdobeBold_32=
	Coordinates_AdobeBold_42=
	Coordinates_AdobeBold_36=0;

	FontsMapLoader((char*)"AdobeBold24.bin",&Coordinates_AdobeBold_24);	
	FontsMapLoader((char*)"AdobeBold32.bin",&Coordinates_AdobeBold_32);	
	FontsMapLoader((char*)"AdobeBold42.bin",&Coordinates_AdobeBold_42);	

	ImageDisplay.setTo(cv::Scalar::all(0));

	//FontsMapLoader("Font_BYEKAN30.bin",&Coordinates_BYekan_30);	
	//FontsMapLoader("SepTahoma.bin",Coordinates_SepTahoma_36);	
	//FontsMapLoader("Font.bin");	
	//FontsMapLoader("Font.bin");	
}

void	ClearScreen(int x,int y,int height,int width)
{
int i=0;
	for (i=0;i<height*width;i++)
	{
		Background[i] =My_Color_White;
	}
	// TO DO
	//display_frame_buffer(x,y,width,height,(short*)Background);		
}

void	PrintBackGround(int Row,int Col,int Height,int SepColor)
{
	BackGroundDrawer(Col,Row,Pixel_WIDTH,Height,SepColor,Fill_Line);
}

char*	IntToString(int	i)
{
	char str[15];
	char const digit[] = "0123456789";
	char* p = str;
	int shifter;
	if (i < 0) {
		*p++ = '-';
		i *= -1;
	}
	shifter = i;
	do { //Move to where representation ends
		++p;
		shifter = shifter / 10;
	} while (shifter);
	*p = '\0';
	do { //Move back, inserting digits as u go
		*--p = digit[i % 10];
		i = i / 10;
	} while (i);
	return str;

}



