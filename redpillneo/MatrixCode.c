// C Source File
// Created 12/8/2001; 5:22:54 PM
	#define OPTIMIZE_ROM_CALLS
	#define NO_EXIT_SUPPORT
	
	#define USE_TI89
	#define USE_TI92PLUS
	#define USE_V200
	
#include "tigcclib.h"
#include "extgraph.h"
#include "MatrixCode.h"

void _main(void)
{
	unsigned int x,y,c,col,counter,char_mode,trails;
	unsigned int char_loop=(lcd_width/FONT_WIDTH)+10;
	void *kbq = kbd_queue();
	unsigned short key;
	unsigned char original_font;
	
	LCD_BUFFER BuffLight,BuffDark,SavedScreen;
	
	char Special[lcd_width/FONT_WIDTH];
	
	for(counter=0;counter<lcd_width/FONT_WIDTH;counter++)
		Special[counter]=0;

//save the screen
	FastCopyScreen(LCD_MEM,(unsigned short *)SavedScreen);

//bla blaa blaaa...
	FastCopyScreen(LCD_MEM,(unsigned short *)BuffLight);
	FastCopyScreen(LCD_MEM,(unsigned short *)BuffDark);
	
	GrayOn();
	PortSet(BuffLight, 239, 127);

	original_font=FontSetSys(MATRIX_FONT);
	
	y=0;	//top of the screen
	
ContinueTheMatrix:

	do
	{
		trails=0;
		
		for(counter=0;counter<char_loop;counter++)
		{
			
			c=rand();
			col=(rand()%lcd_width)/FONT_WIDTH;
			x=col*FONT_WIDTH;
			char_mode=rand()>32300?TRUE:FALSE;
			
			if(Special[col])
			{
				Special[col]--;
				PortSet(BuffDark,239,127);
				DrawChar(x,y,c,A_NORMAL);
				PortSet(BuffLight,239,127);
			}
			else
			{

	//			PortSet(BuffLight, 239, 127);
				DrawChar(x,y,c,A_NORMAL);
			
			
				if(char_mode)
				{
					if(trails++<MAX_TRAILS)
					{
						Special[col]=TRAIL_LENGTH;
						PortSet(BuffDark, 239, 127);
						DrawChar(x,y,c,A_REVERSE);
						PortSet(BuffLight, 239, 127);
					}
				}
				
			}
		}
		
		
	//Scroll the Screen
	for(counter=0;counter<FONT_HEIGHT;counter++)
	{
		DoDelay(DELAY_LONG);
		ScrollDown240((unsigned short*)BuffLight,LCD_HEIGHT);
		ScrollDown240((unsigned short*)BuffDark,LCD_HEIGHT);
		
		FastCopyScreen((unsigned short*)BuffLight,GetPlane(LIGHT_PLANE));
		FastCopyScreen((unsigned short*)BuffDark,GetPlane(DARK_PLANE));
	}

		DoDelay(DELAY_SHORT);
		if(OSTimerExpired(APD_TIMER))
		{
			asm("trap #4");//off() but smaller
			goto ContinueTheMatrix;	//this is bad form, but i couldn't resist
		}
	}
	while (OSdequeue(&key, kbq));
	
	if(key==KEY_ON || key==KEY_OFF || key==KEY_DIAMOND+KEY_ON)
	{
		asm("trap #4");
		goto ContinueTheMatrix;
		
	}

	OSTimerRestart(APD_TIMER);
	PortRestore();
	GrayOff();
	FastCopyScreen((unsigned short*)SavedScreen,LCD_MEM);
	FontSetSys(original_font);
}

void DoDelay(unsigned long delay)
{
	unsigned long counter;
	
		for(counter=0;counter<delay;counter++)
			{
				//pokeIO(0x600005,3);
			}
}
