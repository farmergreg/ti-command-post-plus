/**************************************************
***	Project Title: Command Post (KFLASH)		***
***	Author: Greg Dietsche						***
***	Date:	07/23/2002							***
***	Description: An application designed for	***
*** use with the TI-89 and TI-92 Plus Graphing	***
*** calculators during the testing and			***
*** debugging phases of FLASH APPS and RAM      ***
*** programs									***
***************************************************/
// $Id: dasm_driver.c 15 2004-08-05 21:00:59Z dietsche $

#include <tiams.h>
#include "KFLASHr1.h"
#include "KFLASH.h"
#include "undoc.h"
#include "eggs.h"
#include "dasm.h"
#include "hexedit.h"

typedef struct {
	unsigned short *baseaddr;
	unsigned short *pc;
	USHORT entries;
	USHORT max_entries;
	HANDLE hOffsetTable;
}BACKGROUND_DAT;

static void ScrollFromBottom(WINDOW *w, HEX_DAT *d);
static void ScrollFromTop(WINDOW *w, HEX_DAT *d);
static void WinPaint(WINDOW *w, HEX_DAT *d);
static void Activate_Deactivate(void);
static void DoBackgroundProcessing(HEX_DAT *hex_dat);

//static char * top_addr;		d->top
static char * bottom_addr;
static BACKGROUND_DAT gBGDAT;
static short ScrollFromBottom_helper;	//this tells me exactly where the last line should be drawn. I can count on it because the window must be fully painted in order to swith screen sizes via the mode dialog.

void DASMEditorEventLoop(pFrame self, PEvent e)
{
	HEX_DAT *d=&global.hex_dat;
	
	switch(e->command)
	{
		case CM_BACKGROUND:
			DoBackgroundProcessing(d);
			break;
			
		case CM_ACTIVATE:
		{
			ACB *myid=(ACB*)HeapDeref(GetMyAppID());
			
			d->top+=d->addr;
			d->addr=0;
			if(((unsigned long)d->top)%2)d->top--;	//watch out for odd addresses
			global.BgEventMask|=BG_Disassemble;
			myid->flags|=ACB_BG;
			Activate_Deactivate();
			break;
		}	
		case CM_DEACTIVATE:
			HeapFreeIndir(&gBGDAT.hOffsetTable);
			global.BgEventMask&= ~BG_Disassemble;
			Activate_Deactivate();
			appW.Flags|=WF_VIRTUAL;
			WinClr(&appW);
			break;
			
		case ACM_Defaults:
			break;
		case CM_INSTALL:
			break;
		case ACM_New_Formats:	//the user changed something in the FORMATS dialog
			break;
			
		case CM_WPAINT:
			WinPaint(&appW, d);
			break;
		case CM_KEY_PRESS:
			switch(e->info.keyInfo.keyCode)
			{
				case KB_PGUP:
				{
					void *old_top=d->top;
					
					while(bottom_addr>old_top)
					{
						ScrollFromTop(&appW, d);
					}
				}
					break;
					
				case KB_PGDN:
					d->top=bottom_addr;
					WinPaint(&appW, d);
					break;
					
				case KB_TOP:
					d->top=d->kb_left_most + 2;
					WinPaint(&appW, d);
					break;
					
				case KB_BOTTOM:
					d->top=d->kb_right_most;
					WinPaint(&appW, d);
					//pushkey(KB_PGUP);
					break;
					
				case KB_DOWN:	//scroll the screen up
					ScrollFromBottom(&appW, d);
					HexSTShowMemStr();
					break;
				
				case KB_UP: //scroll the screen down
					ScrollFromTop(&appW, d);
					break;
					
				case '+':
					d->top+=2;
					WinPaint(&appW, d);
					break;
				case '-':
					d->top-=2;
					WinPaint(&appW, d);
					break;
					
				case KB_BEGIN:
				case KB_END:
					HexEditorEventLoop(self, e);
					WinPaint(&appW, d);
				break;
			};
			
			break;
		
		case ACM_Hex_Refresh:
			appW.Flags|=WF_VIRTUAL;	//don't show the cleared screen (WinPaint will unset this flag)
	    	WinClr(&appW);				//Clear The ENTIRE window	    	
	    	WinPaint(&appW, d);			//redraw the WHOLE window
			break;
		
		case ACM_Hex_SetBookMark1:
			d->kb_left_most-=2;
			HeapFreeIndir(&gBGDAT.hOffsetTable);
			HexEditorEventLoop(self, e);
			break;
			
		case CM_PASTE_HANDLE:
		{ 	char *old=d->top;
		
			HeapFreeIndir(&gBGDAT.hOffsetTable);
			HexEditorEventLoop(self, e);
			
			if(d->top != old)	//if it changed, then adjust by 2 bytes since the hex editor will point us at the length bytes, and not the code.
				d->top+=2;		//not 100% fool proof ... if the cursor is already at the new d->top for instance...
		}
			break;
			
		case ACM_Hex_JumpBookMark2:
			HexEditorEventLoop(self, e);
			//pushkey(KB_PGUP);
			WinPaint(&appW, d);
			break;
			
		case ACM_Hex_SetBookMark2:
			HeapFreeIndir(&gBGDAT.hOffsetTable);
			HexEditorEventLoop(self, e);
			break;
			
		case ACM_Hex_JumpBookMark1:
			HexEditorEventLoop(self, e);
			d->top+=2;
			WinPaint(&appW, d);
			break;
					
		case ACM_Hex_JumpVar:
		case ACM_Hex_JumpTo:
		case ACM_Hex_ResizeHandle:
		case ACM_Hex_AMS_GlobalVars:
		case ACM_Hex_JumpCommon:		
			HexEditorEventLoop(self, e);
			break;
				
	};	//end switch
}

//  \/
//there is an address error somewhere in this routine.				
static void ScrollFromTop(WINDOW *w, HEX_DAT *d)
{
	WIN_RECT wr={ 0, 0, 0, 0 };
	BACKGROUND_DAT *bg=&gBGDAT;
	USHORT result_top;
	USHORT result_bottom;
	USHORT *ptr;
	char buff[150];
	DASM_DAT dasm;

	wr.x1=WinWidth(w);
	wr.y1=ScrollFromBottom_helper+C(6-1,8-1);
	
	if((ULONG)bg->baseaddr && (ULONG)d->top>(ULONG)bg->baseaddr && bg->hOffsetTable)
	{
		ptr=HeapDeref(bg->hOffsetTable);
		result_top=bsearch(ptr, (ULONG)d->top - (ULONG)bg->baseaddr, bg->entries-1);
		result_bottom=bsearch(ptr, (ULONG)bottom_addr - (ULONG)bg->baseaddr, bg->entries-1);
		
		if(result_top==USHRT_MAX || result_bottom==USHRT_MAX)
		{
			d->top-=2;
			WinPaint(w, d);
			
			#ifdef DEBUG
				ST_helpMsg("Address Not In Buffer.");
			#endif
			
			return;
		}			
		
		if(result_top)
		{
			result_top--;	//the previous instruction
			result_bottom--;
		}
		
		d->top=(char*)&bg->baseaddr[ptr[result_top]>>1];
		bottom_addr=(char*)&bg->baseaddr[ptr[result_bottom]>>1];

		WinScrollV(w, &wr, C(-6,-8));
		
		disassemble_one((unsigned short*)d->top, &dasm);
		sprintf(buff, "%lx%s", d->top, dasm.text);
		WinStrXY(w, 1, 1, buff);
	}
	else
	{
		d->top-=2;
		WinPaint(w,d);
	}
}
 
// /\
static void ScrollFromBottom(WINDOW *w, HEX_DAT *d)
{//scope brackets
	WIN_RECT wr={ 0, 0, 0, 0 };	
	char buff[150];
	DASM_DAT dat;
	
	wr.x1=WinWidth(w);
	wr.y1=ScrollFromBottom_helper+C(6,8);
	
	disassemble_one((unsigned short*)d->top, &dat);
	d->top=(char*)dat.pc;			//update the top pointer
	disassemble_one((unsigned short*)bottom_addr, &dat);					//disassemble and update bottom pointer
	
	sprintf(buff, "%lx%s", bottom_addr, dat.text);
	
	WinScrollV(w, &wr, C(6,8));
	

	WinStrXY(w, 1, ScrollFromBottom_helper, buff);//+2	//89	
				    
	bottom_addr=(char*)dat.pc;
}//end scope brackets

static void WinPaint(WINDOW *w, HEX_DAT *d)
{
	register char *next;
	char buff[200];
	WIN_COORDS height=WinHeight(w)-C(6,8);
	USHORT counter;
	DASM_DAT dat;

	next=d->top;
	
	w->Flags|=WF_VIRTUAL;	//hide the drawing process
	
	WinClr(w);
	
	#ifdef _89
		WinFont(&appW, F_4x6);
	#endif
        	
	for(counter=1;counter<height;counter+=C(6,8))
	{
		disassemble_one((unsigned short*)next, &dat);
		sprintf(buff, "%lx%s", next, dat.text);
		WinStrXY(w, 1, counter, buff);
		next=(char*)dat.pc;
		
		ScrollFromBottom_helper=counter;
	}

    bottom_addr=next;
    
	w->Flags&=((~WF_VIRTUAL) & (~WF_DIRTY));
	WinBackupToScr(w);	//w->Flags|=WF_DIRTY;
	HexSTShowMemStr();
}

static void DoBackgroundProcessing(HEX_DAT *hex_dat)
{
//#ifdef SADF
	BACKGROUND_DAT * d=&gBGDAT;
	USHORT *ptr;
	DASM_DAT dasm;
	char buff[100];
	
	if(!d->hOffsetTable)
	{
		d->max_entries=(hex_dat->kb_right_most - hex_dat->kb_left_most)>>1;		
		if(d->max_entries==0) return;
		
		d->entries=0;
		d->baseaddr=(unsigned short*)(hex_dat->kb_left_most);
		d->baseaddr++;	//skip the 2 length bytes
		d->pc=d->baseaddr;
		
		if(!(d->hOffsetTable=HeapAllocHigh(d->max_entries<<1)))
			return;
		
		memset(HLock(d->hOffsetTable), 0xff, HeapSize(d->hOffsetTable));
	}
	
	if(!d->hOffsetTable) return;
	if(d->entries>=d->max_entries) return;
	
	ptr=HLock(d->hOffsetTable);
	
	if(d->entries==0) ptr[0]=0;


	#ifdef DEBUG
		if(&d->baseaddr[d->entries]<d->baseaddr)
		{
			ST_helpMsg("Error in Background DASM processing!");
			ngetchx();
		}
	#endif

	disassemble_one(d->pc, &dasm);
	ptr[d->entries++]=(char*)d->pc-(char*)d->baseaddr;	
	d->pc=dasm.pc;
	
	if(!(d->entries%100))
	{
		if(d->max_entries - d->entries < 100)
			ST_eraseHelp();//clean up the status line if *almost* done buffering...
		else
		{
			sprintf(buff, XR_stringPtr(XR_DASM_Buffering), (double)d->entries/(double)d->max_entries*100. );
			ST_helpMsg(buff);
		}
	}

//#endif
}

USHORT bsearch(USHORT * array, USHORT key, USHORT last)
{
	register USHORT mid;
	register USHORT first=0;
	
	while(first <= last)
	{
		mid=(first+last)>>1;
		
		if (key>array[mid])			first=mid+1;
		else if (key<array[mid])	last=mid-1;
		else						return mid;
	}
	
	return USHRT_MAX;
}

static void Activate_Deactivate(void)
{
	BOOL DISAM_Disable=!global.DisassemblerActive;
	HANDLE h_menu=GetAppDefaultMenuHandle(GetMyAppID());
	
	if(h_menu)
	{
		MenuCheck(h_menu, ACM_DisASMViewToggle, MC_FLIP);
		
		
		//MenuTopStat(h_menu, 4, DISAM_Disable);	//F5
		//MenuSubStat(h_menu, ACM_Hex_Refresh, DISAM_Disable);
			
		MenuSubStat(h_menu, CM_COPY, DISAM_Disable);
		MenuSubStat(h_menu, CM_PASTE, DISAM_Disable);			
		MenuSubStat(h_menu, ACM_UNUSED_FIND_INDEX, DISAM_Disable);
		//MenuSubStat(h_menu, ACM_UNUSED_BOOKMARK_INDEX, DISAM_Disable);
		MenuSubStat(h_menu, ACM_Hex_Edit, DISAM_Disable);			
		
		
		MenuOn(h_menu);	//redraw the top level menu items
	}
	
	appW.Flags|=WF_DIRTY;
}
