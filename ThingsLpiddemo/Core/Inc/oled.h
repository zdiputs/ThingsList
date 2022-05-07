#ifndef __OLED_H
#define __OLED_H			  	 
#include "main.h"
#include "stdlib.h"	    	



#define KEY1            ((GPIOB->IDR&(1<<3))==0)//1  esc
#define KEY2            ((GPIOB->IDR&(1<<2))==0)//2  down
#define KEY3            ((GPIOB->IDR&(1<<1))==0)//3  enter
#define KEY4            ((GPIOB->IDR&(1<<0))==0)//4  up
#define SCL_L         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET)//(GPIOB->BRR  = (1<<8))
#define SCL_H         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET)//(GPIOB->BSRR = (1<<8))
#define SDA_L         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET)//(GPIOB->BRR  = (1<<9))
#define SDA_H         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET)//(GPIOB->BSRR = (1<<9))
#define SDA_READ      ((GPIOB->IDR&(1<<9))>>9) 

#define TRUE		1
#define FALSE		0
typedef enum KeyType
{
	KEY_NULL,
    KEY_ESC,// 
	KEY_UP,
	KEY_ENTER,
	KEY_DOWN

}KEYTYPE_FRAME;
typedef enum	KeySta
{
	KEY_STA_NULL,
	KEY_STA_RELEASE,
	KEY_STA_PUSH

}KEYSTA_FRAME;
typedef struct Key
{
	unsigned short keyScanCode;//这里要改成unsigned short
	KEYSTA_FRAME	ekeySta; 
	unsigned int keyNum;

}KEYBUF_FARME; 
typedef struct gbx16         // 汉字字模数据结构
{
	char Index[2];
	char Msk[32];
}GBX16;

typedef enum {
	V_NOP,            //null variable type
	V_CHAR,           //char
	V_UCHAR,          //unsigned char
	V_SHORT,            //integer
	V_USHORT,           //unsigned integer
	V_STRING,         //string
	V_ENUM          //enumeration

}VAR_TYPE;

typedef enum {
	REC_TOP,        //the top record in menu
	REC_MIDDLE,     //the middle record in menu
	REC_END         //the end record in menu
}REC_RANGE;
typedef enum {
	LINE_TOP,       //the top record in one line which made up with muliti-record
	LINE_MIDDLE,    //the middle record in one line with muliti-record
	LINE_END,       //the end record in one line with muliti-record
	LINE_TOPEND     //the line made up with only one record
}LINE_RANGE;
typedef enum {
	RECTP_DISP,       //记录的显示属性       record type is display, only for display
	RECTP_NOCUR,	  //记录的不能被选中属性  不能成为当前记录
	RECTP_EDIT,       //记录为编辑属性       record type is edit, display and can be edited
	RECTP_LINK        //记录的连接属性       record type is link, link to top record in anther menu
}REC_TYPE;
typedef enum {

	MENU_DISP,        //current stage is in displaying
	MENU_EDIT         //current stage is in editing
}MENU_STA;

typedef struct RecFrame{
      char      *pTitle;             //point to string of title
      unsigned char      ucTitleX;            //x coordinate which title displayed at
      unsigned char      ucTitleRevX;         //x coordinate which title reverse video at
      unsigned char      ucTitleRevLen;       //length of title string reverse video at
      volatile void               *pVar;               //point to the variable
      unsigned char      ucVarX;              //the x coordinate which the variable string displayed at
      unsigned char      ucVarLen;            //the length of variable string, include sign, decimal point
      unsigned char      ucVarDecLen;         //the length of decimal part, exclude decimal point
      VAR_TYPE           VarType;             //the variable type, enumeration
      int                siVarMax;            //the maximum of variable
      int                siVarMin;            //the minimum of variable
      char  **pEnumStr;             //point to the enumeration string
      char      (* pEventFunc)();
      REC_RANGE          RecRange;            //record range of a menu
      LINE_RANGE         LineRange;           //line range on one LCD row 
      REC_TYPE           RecType;             //the type of record(display, edit, title, link)
     const struct RecFrame    *pLinkEnter;         //link address to sub-menu if the record is RECTP_LINK
     const struct RecFrame    *pLinkEsc;           //
     
}REC_FRAME;


#define MODE_TEXT 1
#define  M_LCDLINE               4//2
#define  M_LCDTOPSCRLINE         1
#define  M_LCDENDSCRLINE         3
#define  M_LCDWIDTH              30
#define  M_LCDCHARWID            8
#define  M_LCDOFFTIME            20000  //ms
#define  M_FLUSHCYCLE            1
#define  M_STARTOVERTIME         100
#define STARTMENU_MAX_TIME    6 //sec
#define STARTMENU_OVERTIME   100
#define NORMAL			0
#define REVERSE			1
#define CGRAM			1
#define CGROM			2
		    

void SDA_Out(void);
void SDA_In(void);
void IIC_Start(void);
void IIC_Stop(void);
unsigned char Read_Ask(void);
void Write_OneByte(unsigned char Dat);
void WriteCmd(unsigned char IIC_Cmd);
void WriteDat(unsigned char IIC_Dat);
void OLED_Init(void);
void OLED_Set_Pos(unsigned char x,unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x,unsigned char y,unsigned char ch[],unsigned char TextSize);
void OLED_ShowCHinese(unsigned char  x,unsigned char  y,unsigned char *chn,unsigned char revshow);
void OLED_ShowCharNomAndRev(unsigned char x,unsigned char y,unsigned char chr,unsigned char rev);
int PrintHZ(unsigned short  ucY, unsigned short ucX,  char *ptr, unsigned short ucRevX, unsigned char ucDispMode, unsigned short ucRevLen, unsigned char ucCodeGen);
void MenuCtrl(void);
void MenuInit(void);






#define SAVEPAGEADDR    0x800F800
#define SAVEPAGEADDRCOE 0x800FC00//保存系数的那一页
extern unsigned short SaveCalaCoefficient[16][6];
extern unsigned short MenuCoefficient[6];

typedef struct
{
	unsigned char Awarm;//0
        unsigned char Bwarm;//1
        unsigned char Cwarm;//2
        unsigned char DcWarm;//3直流报警开关
        unsigned char DacOut;//4是否输出直流补偿
        unsigned char DacVal;//5补偿电压的值
        unsigned short DcHig;//6直流过压值
        unsigned short DcLow;//7直流欠压值
        unsigned short DcRig;//8直流触发
        unsigned short  AcHig;//9直流过压值
        unsigned char  AcLow;//10直流欠压值
        unsigned char Bdrate;//11波特率
        unsigned char Addr;//12地址


}SAVEPARA;


#define VcoeMax 4000
#define VcoeMin 2000
#define VcoeZ   3000
#define IcoeMax 4000
#define IcoeMin 2000
#define IcoeZ   3700
#define WarnOnOffMax  1
#define WarnOnOffMin  0
#define WarnOnOffZ    1
#define DacValMax   50
#define DacValMin   0
#define DacValZ     50
#define DcHigMax    589
#define DcHigMin    565
#define DcHigZ      569
#define DcLowMax    520
#define DcLowMin    470
#define DcLowZ      495
#define DcRigMax    510
#define DcRigMin    440
#define DcRigZ      475
#define AcHigMax    280
#define AcHigMin    230
#define AcHigZ      265
#define AcLowMax    190
#define AcLowMin     90
#define AcLowZ      175
#define BdrateMax     1
#define BdrateMin     1
#define BdrateZ       1
#define AddrMax      15
#define AddrMin	      0
#define AddrZ         1

typedef struct
{
  unsigned short DcV;
  unsigned char  SysSta;
}MAINPARA;
typedef  struct RcvFrame{
  unsigned short V1;
  unsigned short V2;
  unsigned short V3;
  unsigned short I1;
  unsigned short I2;
  unsigned short I3;
  unsigned short DAC;
  unsigned short STA1;
  unsigned short STA2;
}RCV_FRAME;
extern MAINPARA MainPara;
extern SAVEPARA SavePara;






#endif  
	 



