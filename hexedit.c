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
// $Id: hexedit.c 4 2004-08-05 19:06:59Z dietsche $

#include <tiams.h>
#include "KFLASHr1.h"
#include "KFLASH.h"
#include "undoc.h"
#include "eggs.h"
#include "dasm.h"

#define FIND_STRING 0xFF

typedef enum {SCROLL_UP=-1, SCROLL_DOWN=1 } SCROLL_MODE;

//most internal functions have a window parameter passed to them... this is to save space, and leave room for future implementations which may force the hex editor to use a different window
static void WinPaint(WINDOW *w);
static void Cursor(WINDOW *w);
static BOOL CheckCursorBounds(WINDOW *w);
static void RemoveNull(register char *str, short start, short end);
static void HandlePasteStr(WINDOW *w, HANDLE h);
static void JumpTo(WINDOW *w, char *address);
static char *HexBuff(short width, short offset, unsigned short *h);
static void ScrollVertical(WINDOW *w, SCROLL_MODE dir);
static void RefreshCurLine(WINDOW *w);
static void DoJumpToDialog(WINDOW *w);
static void DoHexEditDialog(WINDOW *w);
static void DoFindDialog(WINDOW *w);
static void *Search(register ULONG value, short width,  register char *start, register short dir, register char * stop_addr);
static void FindDir(WINDOW *w, register short dir);
static void SetEditorWidth(WINDOW *w);
static void DoResizeHandleDialog(void);
static void showJumpToVar(WINDOW *w);
static void showJumpToCommonMem(WINDOW *w);
static void *Trap9(unsigned short index);

static CU_STATE cu;		//internal cursor flash status

static short ShowWantToDerefPtrQuestion(void) { return DlgMessage(XR_stringPtr(XR_ShortAppName),XR_stringPtr(XR_WantDerefPointerQ),PDB_YES,PDB_NO)==KB_ENTER; }

void HexEditorEventLoop(pFrame self, PEvent e)
{
	Access_AMS_Global_Variables;
	HEX_DAT *g=&global.hex_dat;
	HEX_EDIT_DAT *hed=&global.hex_edit_dat;
	WINDOW *w=&appW;
    
	switch(e->command)
	{
	    case CM_ACTIVATE:
	    	WinFont(w, F_6x8);
			SetEditorWidth(w);
	    	g->height=(WinHeight(w)>>3)-1;
	    	WinAttr(w, A_REPLACE);
	    	WinPaint(w);
	    	CU_start();
	    	cu=CU_CURSOR_ON;
	    	Cursor(w);
	    break;
	    
	    case CM_DEACTIVATE:
	    	if(cu) {
	    		Cursor(w);
	    		cu=CU_CURSOR_OFF;
	    	}
	    	CU_stop();
	    break;
	    
	    case CM_CURSOR_FLASH:
	    	Cursor(w);
	    	cu=!cu;
	    break;
	    
	    case CM_CUT:	//handle a cut the same as a copy
	    case CM_COPY:
	    {
	    	WORD result;
	    	void *ptr = &g->top[g->addr];
	    	char buff[50];
	    	
	    	if((ULONG)ptr%2)
	    		result=MenuPopup(&pupCopySpecialOdd, -1, -1, 0);
	    	else
	    		result=MenuPopup(&pupCopySpecialEven, -1, -1, 0);
	    		
		    switch(result)
		    {
		    	case COPY_CHAR:
		    		sprintf(buff, "%u", *(UCHAR *)ptr);
		    		CB_replaceTEXT(buff, strlen(buff), FALSE);
		    		hed->optList[0]=EDIT_CHAR;
		    	break;
		    	
		    	case COPY_SHORT:
		    		sprintf(buff, "%u", *(USHORT *)ptr);
		    		CB_replaceTEXT(buff, strlen(buff), FALSE);
		    		hed->optList[0]=EDIT_SHORT;
		    	break;
		    	
		    	case COPY_LONG:
		    		sprintf(buff, "%lu", *(ULONG *)ptr);
		    		CB_replaceTEXT(buff, strlen(buff), FALSE);
		    		hed->optList[0]=EDIT_LONG;
		    	break;
		    	
	    		case COPY_STRING:
	    			CB_replaceTEXT(&g->top[g->addr], strlen(&g->top[g->addr]), FALSE);
	    			hed->optList[0]=EDIT_STRING;
	    		break;
	    	};
	    }
	    break;
	    
	    case CM_PASTE:	//paste special
	    	{
	    		HANDLE hClipboard;
	    		size_t size;
	    		char *clip;
	    		
		    	if(CB_fetchTEXT(&hClipboard, &size))
		    	{
			    	hed->dlgtitle=XR_stringPtr(XR_PasteSpecial);
			    	
			    	//if(HeapRealloc(hClipboard, ++size)==H_NULL) ER_throw(ER_MEMORY);
			    	hed->dlginitstr=clip=HeapDeref(hClipboard);
			    	clip[size]=0;
			    	
			    	if(cu) Cursor(w);
			    	if(size>HEDIT_BUFF_SIZE)DlgNotice(XR_stringPtr(XR_LongAppName), XR_stringPtr(XR_PasteTruncated));
			    	DoHexEditDialog(w);
			    	cu=CU_CURSOR_ON; Cursor(w);
				}
			}
	    break;
	    
	    case CM_PASTE_HANDLE:	//used to jump to a particular file selected with the var-link
			HandlePasteStr(w, e->info.pasteHandleInfo.pasteHandle);
	    break;
	    
	    case ACM_Defaults:
	    	global.hex_dat.byteswide=0;	//because SetHexEditorDefaults won't function correctly without it
	    	//... fall through ...
	    case CM_INSTALL:
	    	SetHexEditorDefaults(w);
	    break;
	    
	    case ACM_New_Formats:	//the user changed something in the FORMATS dialog
			SetEditorWidth(w);
			w->Flags|=WF_DIRTY;
			CheckCursorBounds(w);	    
	    break;
	    
	    case ACM_Hex_Refresh:		//this code is designed to remove any graphical errors
	    case CM_WPAINT:
	    	w->Flags|=WF_VIRTUAL;	//don't show the cleared screen (WinPaint will unset this flag)
	    	WinClr(w);				//Clear The ENTIRE window
	    	CheckCursorBounds(w);	//force the cursor to be within bounds
	    	WinPaint(w);			//redraw the WHOLE window
	    	if(cu)	Cursor(w);		//if the cursor was showing, then redraw it
	    break;
	    
	    case ACM_Hex_JumpTo:	//show jump dialog
	    	DoJumpToDialog(w);
	    	HexSTShowMemStr();
	    break;
	    
	    case ACM_Hex_Edit:	//show edit dialog
	    	if(cu) Cursor(w);
	    	hed->dlgtitle=XR_stringPtr(XR_Edit);
	    	hed->dlginitstr=NULL;
	    	DoHexEditDialog(w);
	    	if(cu)Cursor(w);
	    break;
	    
	    case ACM_Hex_JumpVar:
	    	handleVarLinkKey(SDT_ALL);
	    	HexSTShowMemStr();
	    break;
	    
	    case ACM_Hex_Find:
	    	DoFindDialog(w);
	    	HexSTShowMemStr();
	    break;
	    
	    case ACM_Hex_FindNext:
	    	FindDir(w, DIR_FOREWARD);
	    	HexSTShowMemStr();
	    break;
	    
	    case ACM_Hex_FindPrevious:
	    	FindDir(w, DIR_BACKWARD);
	    	HexSTShowMemStr();
	    break;
	    
	    case ACM_Hex_ResizeHandle:
	    	DoResizeHandleDialog();
	    break;
	    
	    case ACM_Hex_AMS_GlobalVars:
	    	showJumpToVar(w);
	    	HexSTShowMemStr();
	    break;
	    
	    case ACM_Hex_JumpCommon:
	    	showJumpToCommonMem(w);
	    	HexSTShowMemStr();
	    break;
	    
	    case ACM_Hex_SetBookMark1:
	    	g->kb_left_most=g->addr+g->top;
	    break;
	    
	    case ACM_Hex_SetBookMark2:
	    	g->kb_right_most=g->addr+g->top;
	    break;
	    
	    case ACM_Hex_JumpBookMark1:
	    	e->command=CM_KEY_PRESS;
	    	e->info.keyInfo.keyCode=KB_TOP;
	    	HexEditorEventLoop(self,e);
	    break;
	    
	    case ACM_Hex_JumpBookMark2:
	    	e->command=CM_KEY_PRESS;
	    	e->info.keyInfo.keyCode=KB_BOTTOM;
	    	HexEditorEventLoop(self,e);
	    break;
	    
	    case CM_KEY_PRESS:
	    	
			if(cu)//force the cursor to be off
				Cursor(w);

		    switch(e->info.keyInfo.keyCode)
		    {
		    	case KB_ENTER:	//show hex edit dialog
		    		hed->dlgtitle=XR_stringPtr(XR_Edit);
		    		hed->dlginitstr=NULL;
		    		DoHexEditDialog(w);
		    	break;
		    	
		    	case KB_ENTER + KB_OPTION:	//show FIND dialog
		    		DoFindDialog(w);
		    		HexSTShowMemStr();
		    	break;
                
                case KB_CLEAR:		//find next
                	FindDir(w, DIR_FOREWARD);
                	HexSTShowMemStr();
                break;
                
                case KB_CLEAR + KB_OPTION:	//find previous
                	FindDir(w, DIR_BACKWARD);
                	HexSTShowMemStr();
                break;
                
		    	case KB_PGUP:	//page up
		    		g->top-=(g->height*g->width);
		    		CheckCursorBounds(w);
		    		WinPaint(w);
		    	break;

		    	case KB_PGDN: //page down
		    		g->top+=(g->height*g->width);
		    		CheckCursorBounds(w);
		    		WinPaint(w);
		    	break;
		    	
		    	case KB_UP:	//up one line
		    		g->addr-=g->width;
		    		if(CheckCursorBounds(w))
		    			ScrollVertical(w, SCROLL_UP);
		    			
		    		HexSTShowMemStr();
		    	break;
		    	
		    	case KB_DOWN:	//down one line
		    		g->addr+=g->width;
		    			
		    		if(CheckCursorBounds(w))
		    			ScrollVertical(w, SCROLL_DOWN);
		    			
		    		HexSTShowMemStr();
		    	break;
		    	
		    	case KB_LEFT:	//move left
		    	case KB_DELETE:
		    		if(g->nibble)
		    			g->nibble=0;
		    		else {
		    			g->nibble=1;
		    			g->addr--;
		    			
		    			if(CheckCursorBounds(w))
		    				ScrollVertical(w, SCROLL_UP);
		    		}
		    		
		    		HexSTShowMemStr();
		    	break;
		    	
		    	case KB_RIGHT:	//move right
		    		if(g->nibble) {
		    			g->nibble=0;
		    			g->addr++;
		    			
		    			if(CheckCursorBounds(w))
		    				ScrollVertical(w, SCROLL_DOWN);
		    		}
		    		else
		    			g->nibble=1;
		    			
		    		HexSTShowMemStr();
		    	break;
		    	
		    	case KB_BEGIN:	//move to start of current line
			    	g->addr-=(g->addr%g->width);
			    	g->nibble=0;
			    	if(CheckCursorBounds(w))
		    			WinPaint(w);
		    		else
		    			HexSTShowMemStr();
		    		
		    	break;
		    	
		    	case KB_END:	//move to end of current line
		    		g->addr=g->addr-(g->addr%g->width)+g->width-1;
		    		g->nibble=1;
		    		if(CheckCursorBounds(w))
		    			WinPaint(w);
	    			else
		    			HexSTShowMemStr();
		    	break;
		    	
		    	case KB_LEFT_MOST:	//jump 2 bytes backwards
		    		g->addr-=2;
		    		
		    		if(CheckCursorBounds(w))
		    			ScrollVertical(w, SCROLL_UP);
		    			
		    		HexSTShowMemStr();
		    	break;
		    	
		    	case KB_RIGHT_MOST:	//jump 2 bytes foreword	
		    		g->addr+=2;
		    		
		    		if(CheckCursorBounds(w))
		    			ScrollVertical(w, SCROLL_DOWN);
		    		
		    		HexSTShowMemStr();
		    	break;
		    	
		    	case KB_TOP:	//relative jump to kb_left_most (extra code adds tons of speed when the jump is a long distance)	
		    	{
		    		long addr=(g->width*g->height) + (g->width-2);
		    		
		    		if(g->kb_left_most > g->top + addr || g->kb_left_most < g->top)
		    		{
		    			JumpTo(w, g->kb_left_most);
		    		}
		    		else
		    		{
		    			g->addr=g->kb_left_most-g->top;		//this line
						g->nibble=0;						//and this line are the only necessary lines of code in this handler
						
						if(CheckCursorBounds(w))
		    				WinPaint(w);
					}
		    	}
		    	HexSTShowMemStr();
			    break;
			    
			    case KB_BOTTOM:	//relative jump to kb_right_most (extra code adds tons of speed when the jump is a long distance)
					{
						long addr=(g->width*g->height) + (g->width-2);
						char *tmptop=(char *)(g->kb_right_most - addr);
						
						if(g->kb_right_most > g->top + addr || g->kb_right_most < g->top)
						{//offscreen
							JumpTo(w, tmptop);
							g->addr=addr;
							if((ULONG)tmptop%2)g->addr++;		//account for an odd jump address
							CheckCursorBounds(w);
						}
						else
						{//on screen relative addr
							g->addr=g->kb_right_most-g->top;	//this line
							g->nibble=0;						//and this line are the only necessary lines of code in this handler
							
							if(CheckCursorBounds(w))
		    					WinPaint(w);
						}
					}
					HexSTShowMemStr();
		    	break;
		    			
	#ifdef _89
		    	case '=':
		    		e->info.keyInfo.keyCode='A';
		    		goto special_break;
		    	case '(':
		    		e->info.keyInfo.keyCode='B';
		    		goto special_break;
		    	case ')':
		    		e->info.keyInfo.keyCode='C';
		    		goto special_break;
		    	case ',':
		    		e->info.keyInfo.keyCode='D';
		    		goto special_break;
		    	case '/':
		    		e->info.keyInfo.keyCode='E';
		    		goto special_break;
		    	case '|':
		    		e->info.keyInfo.keyCode='F';
	#endif
		    	case 'a':
		    	case 'b':
		    	case 'c':
		    	case 'd':
		    	case 'e':
		    	case 'f':
		    		toupper(e->info.keyInfo.keyCode);
		    	case 'A':
		    	case 'B':
		    	case 'C':
		    	case 'D':
		    	case 'E':
		    	case 'F':
special_break:	//yay, a good case for a goto?
					e->info.keyInfo.keyCode-=0x37;	//convert to hex val
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					TRY		//handle protected memory violation's so cursor handling does not mess up
						e->info.keyInfo.keyCode-=0x30;	//convert to hex val
						e->info.keyInfo.keyCode&=0x0f;	//mask out any garbage
						if(g->nibble)
						{//apply  nibble mask
							g->top[g->addr]&=0xf0;
						}
						else
						{
							g->top[g->addr]&=0x0f;
							e->info.keyInfo.keyCode=e->info.keyInfo.keyCode<<4;	//adjust by one nibble
						}
						g->top[g->addr]|=e->info.keyInfo.keyCode;	//write the new value at the current nibble
						
					//update the current display line with the newly edited nibble
			    		RefreshCurLine(w);
					
					//advance to next nibble if there was no error during the write process
						pushkey(KB_RIGHT);

					ONERR
						EV_errorCode=errCode;
					ENDTRY
		    break;
		    };//end switch(e->info.keyInfo.keyCode)
	   
	    cu=CU_CURSOR_ON;
		Cursor(w);
	    	 	
	break;//end case CM_KEYPRESS
	};//end switch(e->command)
	
	return;
}

static void WinPaint(WINDOW *w)
{
	HEX_DAT d=global.hex_dat;
	register short i;
	short offset=0;
	register unsigned short *h;

	h=(unsigned short*)d.top;
	
	w->Flags|=WF_VIRTUAL;	//hide the drawing process
        	
	for(i=0;i<d.height;i++)
	{
		WinStrXY(w, 5, 1+(i<<3), HexBuff(d.width, offset, h));
		offset++;
	}
    
	w->Flags&=((~WF_VIRTUAL) & (~WF_DIRTY));
	WinBackupToScr(w);	//w->Flags|=WF_DIRTY;
	HexSTShowMemStr();
}

//pleasantly slow, but faster than redrawing the whole screen
static void ScrollVertical(WINDOW *w, SCROLL_MODE dir)
{
	HEX_DAT *d=&global.hex_dat;
	WIN_RECT wr={ 0, 0, 0, 0 };

	wr.x1=WinWidth(w);
	wr.y1=d->height<<3;
	
	w->Flags|=WF_VIRTUAL;	//hide the drawing process
	
	WinScrollV(w, &wr, dir<<3);
	d->height--;
	
	if(dir==SCROLL_DOWN)
		WinStrXY(w, 5, 1+((d->height)<<3), HexBuff(d->width, d->height, (unsigned short*)d->top)); 
	else {
		wr.y0=wr.y1;
    	WinAttr(w, A_REVERSE);
     	WinLine(w, &wr);	//clean up the bottom row of garbage from scrolling
     	WinAttr(w, A_REPLACE);
     	WinStrXY(w, 5, 1, HexBuff(d->width, 0, (unsigned short*)d->top));
	}
	
	d->height++;	
	w->Flags&= ~WF_VIRTUAL; 
	WinBackupToScr(w);
}

static void RefreshCurLine(WINDOW *w)
{
	register HEX_DAT *d=&global.hex_dat;
	register short y;

	y=d->addr/d->width;
	WinStrXY(w, 5, 1+((y)<<3), HexBuff(d->width, y, (unsigned short*)d->top));
}

//using unsigned pointers so the compiler generates optimal code in the sprintf calls
//otherwise it plays around with sign extending etc...
static char * HexBuff(short width, register short offset, register unsigned short *h)
{
	register char *buff=gBuff;
	register unsigned char *c=(unsigned char *)h;
	register short offsetb;
	
	switch(width)
	{//handle largest possibility first for speed (hopefully our compiler picks up on this :)
	
#ifdef _92
	case 10:
		offset*=5;
		offsetb=offset*2;
		sprintf(buff, "%04x %04x %04x %04x %04x  %c%c%c%c%c%c%c%c%c%c",
					h[offset], h[1 + offset], h[2 + offset], h[3 + offset], h[4 + offset], 
					c[offsetb],     c[1 + offsetb], c[2 + offsetb], c[3 + offsetb],
					c[4 + offsetb], c[5 + offsetb], c[6 + offsetb], c[7 + offsetb],
					c[8 + offsetb], c[9 + offsetb]
					);
					
		RemoveNull(buff, 26, 36);
	break;
	
	case 8:	//this width is normally only availiable if the user picks 8 bytes wide in the format dialog box
		offset*=4;
		offsetb=offset*2;
		sprintf(buff, "%04x %04x %04x %04x  %c%c%c%c%c%c%c%c",
					h[offset], h[1 + offset], h[2 + offset], h[3 + offset], 
					c[offsetb],     c[1 + offsetb], c[2 + offsetb], c[3 + offsetb],
					c[4 + offsetb], c[5 + offsetb], c[6 + offsetb], c[7 + offsetb]
					);
					
		RemoveNull(buff, 21, 29);
	break;
	
#endif

	case 6:
		offset*=3;
		offsetb=offset*2;
		sprintf(buff, "%04x %04x %04x  %c%c%c%c%c%c",
					h[offset], h[1 + offset], h[2 + offset],
					c[offsetb], c[1 + offsetb], c[2 + offsetb], c[3 + offsetb], c[4 + offsetb], c[5 + offsetb]
					);
		RemoveNull(buff, 16, 22);
	break;
	
	case 4:
		offset*=2;
		offsetb=offset*2;
		sprintf(buff, "%04x %04x  %c%c%c%c",
					h[offset], h[1 + offset], 
					c[offsetb], c[1 + offsetb], c[2 + offsetb], c[3 + offsetb]
					);
		RemoveNull(buff, 11, 15);
		offset+=2;
		offsetb+=4;
	break;
	
	case 2:
		offsetb=offset*2;
		sprintf(buff, "%04x  %c%c",
					h[offset], 
					c[offsetb], c[1 + offsetb]
					);
		RemoveNull(buff, 6, 8);
	break;
	
	};

	return buff;
}

static void Cursor(WINDOW *w)
{
	register HEX_DAT *d=&global.hex_dat;
	WIN_RECT cursor = { 5, 0, 11, 8 };
	char buff[100];
	register unsigned short offsety;
	register unsigned short offsetx;
	
    if(d->addr)//avoid Divide by Zero
    {	
    	offsetx=(d->addr%d->width)*2;	 	//x offset   -
    	offsetx+= offsetx/3;
    	if(offsetx && (!(offsetx%8) || !(offsetx%13) || !(offsetx%18)))offsetx--;
    	if(offsetx && (!(offsetx%0x15) || !(offsetx%0x17)))offsetx--;
		offsetx*=6;
		    	
    	offsety=(d->addr/d->width)<<3;
    	
    	 					//y offset   |
	    cursor.x0+=offsetx;
	    cursor.x1+=offsetx;
	    cursor.y0+=offsety;
	    cursor.y1+=offsety;
    }
     
	/*if(d->addr<=d->width)
    {//clear the very top (horizontal) pixel line of the screen
    	WIN_RECT topline = {0, 0, 0, 0};
    	topline.x1=d->width*6;
    	WinAttr(w, A_REVERSE);
     	WinLine(w, &topline);
     	WinAttr(w, A_REPLACE);
    }*/
    
    if(d->nibble) {
    	cursor.x0+=6;
    	cursor.x1+=6;
    }
    
    
	WinFill(w, &cursor, A_XOR);
     
    sprintf(buff, "0x%08lx    ", d->top+d->addr);//each space is 2 pixels wide
	WinFont(w, F_4x6);
    WinStrXY(w, 5, 1+(d->height<<3), buff);
    WinFont(w, F_6x8);
}

//returns TRUE if the window needs to be repainted
static BOOL CheckCursorBounds(WINDOW *w)
{
	HEX_DAT *g=&global.hex_dat;
	
    if(g->addr<0)
    {//low bound check
		do {
			g->addr+=g->width;
			g->top-=g->width;
		}
		while(g->addr<0);
		return TRUE;
    }
    else if(g->addr >= g->width*g->height)
    {//high bound check
    	do {
			g->addr-=g->width;
			g->top+=g->width;
		}while(g->addr >= g->width*g->height);	//repeat until within bounds ie window change from large to small
		return TRUE;
    }
    
    return FALSE;
}

//replaces null characters with spaces from str[start] to str[end]
static void RemoveNull(register char *str, register short start, register short end)
{
	for(;start<end;start++)
	{
		if(!str[start])str[start]=' ';
	}
}

void SetHexEditorDefaults(WINDOW *w)
{
	HEX_DAT *g=&global.hex_dat;
	HEX_JUMP_DAT *j=&global.hex_jump_dat;
	HEX_FIND_DAT *f=&global.hex_find_dat;
	HEX_EDIT_DAT *h=&global.hex_edit_dat;
	HEX_JUMP_GLOBAL_VAR *hjgv=&global.hex_jump_global_var;
	HEX_JUMP_COMMON_MEM *hjcm=&global.hex_jump_common_mem;
	
	j->optList[0]=JUMP_ADDRESS;
	j->txtAddr[0]=0;
	
	h->txtValue[0]=0;
	h->optList[0]=EDIT_CHAR;
	h->optList[1]=MASK_NONE;
	if(!g->byteswide)//if it is initialized, it is because of ResetMagic
		#ifdef _92
			g->byteswide=TEN_WIDE;
		#else
			g->byteswide=SIX_WIDE;
		#endif
		
	
	f->txtValue[0]=0;
	strcpy(f->txtStopAddr, "0hffffffff");
	f->optList[0]=EDIT_CHAR;
	f->optList[1]=DIR_FOREWARD;
	
	hjgv->optList[0]=1;
	hjgv->txtValue[0]=0;
	
	hjcm->optList[0]=1;
	hjcm->txtValue[0]=0;
    
	SetEditorWidth(w);
	
	g->kb_left_most=0;
	g->kb_right_most=0;	
	
	JumpTo(w, g->top);

}

static void JumpTo(WINDOW *w, char *address)
{
	HEX_DAT *g=&global.hex_dat;
	
	if(((unsigned long)address)%2)
	{//if the address is odd
		g->top=(char*)address-1;
		g->addr=1;
	}
	else
	{
		g->top=address;
		g->addr=0;
	}
	
	g->nibble=0;
	w->Flags|=WF_DIRTY;
}

static void DoJumpToDialog(WINDOW *w)
{   
	Access_AMS_Global_Variables;
	
	HEX_JUMP_DAT *j=&global.hex_jump_dat;
	HEX_DAT *g=&global.hex_dat;
	void *handle;
	HANDLE h;
		
	switch(Dialog(&dlgJumpTo, -1, -1, j->txtAddr, j->optList))
	{
		case KB_ENTER:
		switch(j->optList[0])
		{
			case JUMP_ADDRESS:
				JumpTo(w, (char*)((unsigned long)StrToEStackToLong(j->txtAddr)));
			break;
			
			case JUMP_REL_ADDR:
				JumpTo(w, (char*)(long)global.hex_dat.top+(long)global.hex_dat.addr+((long)StrToEStackToLong(j->txtAddr)));
			break;
			
			case JUMP_HANDLE:
				h=(HANDLE)StrToEStackToLong(j->txtAddr);
				handle=HeapDeref(h);
				if(CheckInvalidHandle(handle)) ER_throwFrame(ER_InvalidHandle, pAppObj);
				JumpTo(w, handle);
				
				g->kb_left_most=handle;
				g->kb_right_most=(void*)((ULONG)handle+(ULONG)HeapSize(h));
				
			break;
		};
		break;
			
		case DB_MEMFULL:			//handle low memory error
			EV_errorCode=ER_MEMORY;
		break;
	}
}

static void DoHexEditDialog(WINDOW *w)
{   
	Access_AMS_Global_Variables;
	WORD popup;
	
	unsigned long newval=0;	//to satisfy the compiler
	HEX_DAT *g=&global.hex_dat;
	HEX_EDIT_DAT *h=&global.hex_edit_dat;
	long bytestoend=g->addr;
	
	while(bytestoend>g->width)bytestoend-=g->width;
	bytestoend=g->width-bytestoend;
	
	if(h->dlginitstr)
	{
		memcpy(h->txtValue, h->dlginitstr, HEDIT_BUFF_SIZE);
	}
	
	TRY
		switch(Dialog(&dlgHexEditCur, -1, -1, h->txtValue, h->optList))
		{
			case KB_ENTER:
				
				if(h->optList[0]!=EDIT_STRING)
				{
					if(h->txtValue[0]==0)
						strcpy(h->txtValue, "0");
					newval=StrToEStackToLong(h->txtValue);
				}
						
				switch(h->optList[0])		//speed, not size my friend
				{//editing even address
								
					case EDIT_CHAR:
						switch(h->optList[1])
						{
							case MASK_NONE:
								g->top[g->addr]  = newval;						//handle char
								break;
							case MASK_AND:
								g->top[g->addr] &= newval;						//handle char
								break;
							case MASK_OR:
								g->top[g->addr] |= newval;						//handle char
								break;
							case MASK_XOR:
								g->top[g->addr] ^= newval;						//handle char
								break;
						};

						RefreshCurLine(w);
					break;
					
					case EDIT_SHORT:
						switch(h->optList[1])
						{
							case MASK_NONE:
								*(USHORT*)(&g->top[g->addr])  = newval;						//handle word
								break;
							case MASK_AND:
								*(USHORT*)(&g->top[g->addr]) &= newval;						//handle word
								break;
							case MASK_OR:
								*(USHORT*)(&g->top[g->addr]) |= newval;						//handle word
								break;
							case MASK_XOR:
								*(USHORT*)(&g->top[g->addr]) ^= newval;						//handle word
								break;
						};					
					
						RefreshCurLine(w);
					break;
					
					case EDIT_LONG:
					
						switch(h->optList[1])
						{
							case MASK_NONE:
								*(ULONG*)(&g->top[g->addr])  = newval;						//handle long
								break;
							case MASK_AND:
								*(ULONG*)(&g->top[g->addr]) &= newval;						//handle long
								break;
							case MASK_OR:
								*(ULONG*)(&g->top[g->addr]) |= newval;						//handle long
								break;
							case MASK_XOR:
								*(ULONG*)(&g->top[g->addr]) ^= newval;						//handle long
								break;
						};
						
						if(bytestoend>3)
							RefreshCurLine(w);
						else
							WinPaint(w);
					break;
					
					case EDIT_STRING:
					    #ifndef NO_EASTER_EGGS
							if(!stricmp(h->txtValue,"RedPillNeo"))   RedPillNeo();
							//if(!stricmp(h->txtValue,"GreenLightGo")) GreenLightGo();
						#endif
							
						strcpy(&g->top[g->addr], h->txtValue);
						if(bytestoend>strlen(h->txtValue))
							RefreshCurLine(w);
						else
							WinPaint(w);
					break;
				};
				
			break;
				
			case DB_MEMFULL:			//handle low memory error
				EV_errorCode=ER_MEMORY;
			break;
		}
	ONERR
		EV_errorCode=errCode;
	ENDTRY		
}

DWORD cbHexEdit(WORD DlgId, DWORD dValue)
{
	HEX_DAT *g=&global.hex_dat;	
    HEX_EDIT_DAT *h=&global.hex_edit_dat;
    
    if(DlgId==DB_GET_TITLE)
    {
    	return (DWORD)h->dlgtitle;
    }
    
	if(((ULONG)(&g->top[g->addr])%2))
	{
		if(h->optList[0]!=EDIT_CHAR && h->optList[0]!=EDIT_STRING)
		{
			h->optList[0]=EDIT_CHAR;
			return DB_REDRAW_AND_CONTINUE;
		}
	}
	
	if(h->optList[0]==EDIT_STRING)
		h->optList[1]=MASK_NONE;
	
	return DB_REDRAW_AND_CONTINUE;
	//return TRUE;	
}

static void HandlePasteStr(WINDOW *w, HANDLE h)
{//a few extra variables here to make future expansion faster
	HEX_DAT *g=&global.hex_dat;
	char *ptr;
	UCHAR *tag_ptr;
	BYTE tokenized[MAX_SYM_LEN];
	HSYM hsym;
	SYM_ENTRY *sym;
	WORD result=0;
	
	ptr=HeapDeref(h);
	if((ptr=strchr(ptr,'(')))*ptr=0;	//sometimes the var-link adds a ( to the pasted string
	
	hsym=SymFind(StrToTokN(HeapDeref(h), tokenized));
	
	if(sym=DerefSym(hsym))
		result=MenuPopup(&pupEditWhat, -1, -1, 0);

	if(!result)
		return;	//low mem, or ESC pressed
	
	switch(result)
	{
		case JUMP_TO_DATA:
			ptr=HeapDeref(sym->hVal);
			tag_ptr=HToESI(sym->hVal);
			
			if(*tag_ptr==ASM_PRGM_TAG)	EX_patch(ptr+2, tag_ptr);
				
			g->kb_right_most=ptr+(*(unsigned short*)ptr) + 1;
		break;
		
		case JUMP_TO_SYM_ENTRY:
			ptr=(char *)sym;
			g->kb_right_most=ptr+(sizeof(SYM_ENTRY)-1);
		break;
	};
	
	if(ptr) {
		JumpTo(w, ptr);
		g->kb_left_most=ptr;
	}
}

static void DoFindDialog(WINDOW *w)
{   
	Access_AMS_Global_Variables;
	WORD popup;
	HEX_FIND_DAT *f=&global.hex_find_dat;
	
	switch(Dialog(&dlgFind, -1, -1, f->txtValue, f->optList))
	{
		case KB_ENTER:
			FindDir(w, f->optList[1]);
		break;
			
		case DB_MEMFULL:			//handle low memory error
			EV_errorCode=ER_MEMORY;
		break;
	}		
}

static void FindDir(WINDOW *w, register short dir)
{
	Access_AMS_Global_Variables;
	HEX_FIND_DAT *f=&global.hex_find_dat;
	HEX_DAT *g=&global.hex_dat;
	long search=0;//to satisfy the compiler
	char * stop_addr;

	TRY	
		if(f->optList[0]!=EDIT_STRING)
		{
			if(f->txtValue[0]==0)
				ER_throw(ER_ARGUMENT);
				
			search=StrToEStackToLong(f->txtValue);	//get the number to find
		}
				
		stop_addr=(char*)(ULONG)StrToEStackToLong(f->txtStopAddr);
		
		switch(f->optList[0])
		{
						
			case EDIT_CHAR:
				JumpTo(w, Search(search, sizeof(char), &g->top[g->addr], dir, stop_addr));
			break;
			
			case EDIT_SHORT:
				JumpTo(w, Search(search, sizeof(short), &g->top[g->addr], dir, stop_addr));
			break;
			
			case EDIT_LONG:
				JumpTo(w, Search(search, sizeof(long), &g->top[g->addr], dir, stop_addr));
			break;
			
			case EDIT_STRING:
				JumpTo(w, Search((long)&f->txtValue, FIND_STRING, &g->top[g->addr], dir, stop_addr));
			break;
		};
	ONERR
		EV_errorCode=errCode;
	ENDTRY
}

static void *Search(register ULONG value, short width,  register char *start, register short dir, register char * stop_addr)
{
	if(width>1)
		if((ULONG)start%2)
			start--;	//get even... its the only way
	
	if(start==stop_addr)	return start;
	
	if(dir==DIR_FOREWARD)
		stop_addr--;

	ERD_notice((UCHAR*)XR_stringPtr(XR_LongAppName), (UCHAR*)XR_stringPtr(XR_SearchingEstr));
	
	TRY
		switch(width)
		{
			case 1:
				do
				{
					if(dir==DIR_FOREWARD)
					{
						start++;	
						if(start>stop_addr)break;
					}
					else
					{
						start--;
						if(start<=stop_addr)break;
					}
						
					if(OSCheckBreak())ER_throw(ER_BREAK);
				}while(*start!=(char)value);
			break;
				
			case 2:
				do
				{
					if(dir==DIR_FOREWARD)
					{
						start+=2;
						if(start>stop_addr)break;
					}
					else
					{
						start-=2;
						if(start<=stop_addr)break;
					}
						
					if(OSCheckBreak())ER_throw(ER_BREAK);
				}while(*(USHORT*)start!=(USHORT)value);
			break;
				
			case 4:
				do
				{
					if(dir==DIR_FOREWARD)
					{
						start+=2;	
						if(start>stop_addr)break;
					}
					else
					{
						start-=2;
						if(start<=stop_addr)break;
					}
						
					if(OSCheckBreak())ER_throw(ER_BREAK);
				}while(LO_WORD(*(ULONG*)start)!=LO_WORD((ULONG)value) || HI_WORD(*(ULONG*)start)!=HI_WORD((ULONG)value));
						
			break;
			
			case FIND_STRING:
				do
				{
					if(dir==DIR_FOREWARD)
					{
						start++;	
						if(start>stop_addr)break;
					}
					else
					{
						start--;
						if(start<=stop_addr)break;
					}
						
					if(OSCheckBreak())ER_throw(ER_BREAK);
				}while(strcmp(start, (char*)value));
			break;
		}
		
	FINALLY
		ERD_dismissNotice();
	ENDFINAL
	
	return start;
}

static void DoResizeHandleDialog(void)
{
	Access_AMS_Global_Variables;
	HEX_RESIZE_HANDLE *g=&global.hex_resize_handle;
	USHORT newsize;
	HANDLE h;
	char *ptr;
	
	switch(Dialog(&dlgResizeHandle, -1, -1, g->txtValue, NULL))
	{
		case KB_ENTER:
			h=(HANDLE)StrToEStackToLong(g->txtValue);
			newsize=StrToEStackToLong(g->txtValue + 22);
			
			ptr=HeapDeref(h);
			if((ULONG)ptr==0 || (ULONG)ptr==0xffffffff)
				ER_throwFrame(ER_InvalidHandle, pAppObj);
			
			if(HeapRealloc(h, newsize)==H_NULL)EV_errorCode=ER_MEMORY;
		break;
		
		case DB_MEMFULL:
			EV_errorCode=ER_MEMORY;
		break;
	};
}

static void SetEditorWidth(WINDOW *w)
{//determine how many bytes wide the editor should be
	HEX_DAT *g=&global.hex_dat;
	unsigned short ww=WinWidth(w);
	
//this also handles 8 byte widths on the ti-92p even though that width should never be chosen automatically
	g->width=C(ww>132?6:ww>90?4:2, ww>215?10:ww>173?8:ww>132?6:ww>90?4:2);
	
	if(g->width>g->byteswide)
		g->width=g->byteswide;
}

static void showJumpToVar(WINDOW *w)
{
	Access_AMS_Global_Variables;
	void *j=NULL;
	HEX_JUMP_GLOBAL_VAR *g=&global.hex_jump_global_var;
	HEX_DAT *hdat=&global.hex_dat;
	short offset=0;
	
	switch(Dialog(&dlgJumpAMSVar, -1, -1, g->txtValue, g->optList))
	{
		case KB_ENTER:
			switch(g->optList[0])
			{
				case JVAR_BOTTOM_ESTACK:
					j=bottom_estack;
					offset=top_estack-bottom_estack;
				break;
				
				case JVAR_CU_CURSOR_STATE:
					j=&CU_cursorState;
					offset=sizeof(CU_STATE)-1;
				break;
				
				case JVAR_ERRNO:
					j=&errno;
					offset=sizeof(int)-1;
				break;
				
				case JVAR_EV_APPA:
					j=&EV_appA;
					offset=sizeof(AppID)-1;
				break;
				
				case JVAR_EV_APPB:
					j=&EV_appB;
					offset=sizeof(AppID)-1;
				break;
				
				case JVAR_EV_ERROR_CODE:
					j=&EV_errorCode;
					offset=sizeof(SINT)-1;
				break;
				
				case JVAR_EV_FLAGS:
					j=&EV_flags;
					offset=sizeof(EV_FLAGS)-1;
				break;
				
				case JVAR_EV_RUNNINGAPP:
					j=&EV_runningApp;
					offset=sizeof(AppID)-1;
				break;
				
				case JVAR_FLASHMEMORYEND:
					j=FlashMemoryEnd;
				break;
				
				case JVAR_JUMPTABLE:
				//page 26, 27...
					j=*(long **)0xc8;
					offset=*(ULONG*)0xc8;
				break;
				
				case JVAR_MO_OPTION:
					MO_currentOptions();
					j=MO_option;
					offset=2*MO_OPT_ITEM_COUNT;
				break;
				
				case JVAR_NG_CONTROL:
					j=&NG_control;
					offset=sizeof(CONTROL_BITS)-1;
				break;
				
				case JVAR_OO_FIRST_ACB:
					if(DlgMessage(XR_stringPtr(XR_ShortAppName),XR_stringPtr(XR_WantDerefHandleQ),PDB_YES,PDB_NO)==KB_ENTER)
					{
						j=HeapDeref((HANDLE)OO_firstACB);
						offset=sizeof(ACB)-1;
					}
					else
					{
						j=&OO_firstACB;
						offset=sizeof(HANDLE)-1;
					}
				break;
				
				case JVAR_OO_SUPERFRAME:
					j=&OO_SuperFrame;
					offset=sizeof(pFrame)-1;
				break;
					
				case JVAR_OSFASTARROWS:
					j=&OSFastArrows;
					//offset=sizeof(BYTE)-1;
				break;
				
				case JVAR_OSMODKEYSTATUS:
					j=&OSModKeyStatus;
					offset=sizeof(WORD)-1;
				break;
				
				case JVAR_ST_FLAGS:
					j=&ST_flags;
					offset=sizeof(ST_FLAGS)-1;
				break;
				
				case JVAR_TOP_ESTACK:
					j=top_estack;
					offset=bottom_estack-top_estack;
				break;
				
				case JVAR_HS_GETANS:
			    	j=HeapDeref(HS_getAns(StrToEStackToLong(g->txtValue)));
			    	if(CheckInvalidHandle(j)) ER_throwFrame(ER_InvalidHistItem, pAppObj);
			    break;
			    
			    case JVAR_HS_GETENTRY:
			    	j=HeapDeref(HS_getEntry(StrToEStackToLong(g->txtValue)));
			    	if(CheckInvalidHandle(j)) ER_throwFrame(ER_InvalidHistItem, pAppObj);
			    break;		
			    
			};
			
		break;	//end case KB_ENTER:
		
		case DB_MEMFULL:
			EV_errorCode=ER_MEMORY;
		break;
	};
	
	
	if(!j) return;
	
	JumpTo(w, j);
	hdat->kb_left_most=j;
	hdat->kb_right_most =(char *)j + offset;
	
}
DWORD cbJumpAMSVar(WORD DlgId, DWORD dValue)
{
	HEX_JUMP_GLOBAL_VAR *g=&global.hex_jump_global_var;
    
    switch(DlgId)
    {
    	case DB_QACTIVE:
    		switch(g->optList[0])
    		{
    			case JVAR_HS_GETANS:
    			case JVAR_HS_GETENTRY:
    			break;
    			
    			default:
    				if(dValue==1)
    					return FALSE;
    		};
    	break;
    
    };
    
    
	return DB_REDRAW_AND_CONTINUE;
}

static void *Trap9(unsigned short index)
{
		asm(" move.w 4(a7),d0",2);	//2 bytes
		asm(" trap #9",2);			//2 bytes
}

static void showJumpToCommonMem(WINDOW *w)
{
	Access_AMS_Global_Variables;
	void *j=(void*)-1;
	HEX_JUMP_COMMON_MEM *g=&global.hex_jump_common_mem;
	HEX_DAT *hdat=&global.hex_dat;
	short offset=0;
	
	switch(Dialog(&dlgJumpCommonMem, -1, -1, g->txtValue, g->optList))
	{
		case KB_ENTER:
			switch(g->optList[0])
			{
   				case JVAR_EVECTOR:
	   				j=(void*)(4*StrToEStackToLong(g->txtValue));
	   				if(j>(void*)0x3FC) ER_throw(ER_ARGUMENT);
	   				if(ShowWantToDerefPtrQuestion())
	   					j=(void*)*(ULONG**)j;
	   				else
	   					offset=sizeof(ULONG)-1;
   				break;

   				case JVAR_AUTO_INT:
   					j=(void*)(4*(StrToEStackToLong(g->txtValue)+24));
	   				if(j<(void*)0x64 || j>(void*)0x7c) ER_throw(ER_ARGUMENT);
					if(ShowWantToDerefPtrQuestion())
	   					j=(void*)*(ULONG**)j;
	   				else
	   					offset=sizeof(ULONG)-1;
   				break;
   				
   				
   				case JVAR_TRAP:
   				   	j=(void*)(4*(StrToEStackToLong(g->txtValue)+32));
	   				if(j<(void*)0x80 || j>(void*)0xbc) ER_throw(ER_ARGUMENT);
	   				if(ShowWantToDerefPtrQuestion())
	   					j=(void*)*(ULONG**)j;
	   				else
	   					offset=sizeof(ULONG)-1;
   				break;
   				
   				case JVAR_LCD_MEM:
					j=Trap9(14);
					offset=3840-1;	//LCD_MEM_SIZE-1
				break;
				
				case JVAR_OS_CONTRAST:
					j=Trap9(4);
				break;
				
				case JVAR_HW1_PORTS:
					j=(ULONG*)0x600000;
					offset=0x1F-1;
				break;
				
				case JVAR_HW2_PORTS:
					j=(ULONG*)0x700000;
					offset=0x1F-1;
				break;
				
				case JVAR_KEY_QUEUE:
					j=Trap9(12);
				break;
				
				case JVAR_ROM_CALL:
				//{//scope brackets
					//ULONG call=StrToEStackToLong(g->txtValue);
					//char *str=RomCallIdxToStr(call);
			    	//j=AMS_Global_Variables[call];
			    	j=AMS_Global_Variables[StrToEStackToLong(g->txtValue)];
			    	
			    	//if(str)ST_helpMsg(str);
			    	
			    //}//end scope brackets
			    break;   
			};
			
		break;	//end case KB_ENTER:
		
		case DB_MEMFULL:
			EV_errorCode=ER_MEMORY;
		break;
	};
	
	
	if((long)j==-1) return;
	
	JumpTo(w, j);
	hdat->kb_left_most=j;
	hdat->kb_right_most =(char *)j + offset;
	
}
DWORD cbJumpCommonMem(WORD DlgId, DWORD dValue)
{
	HEX_JUMP_COMMON_MEM *g=&global.hex_jump_common_mem;
    
    switch(DlgId)
    {
    	case DB_QACTIVE:
    		switch(g->optList[0])
    		{
    		    case JVAR_ROM_CALL:
    		    case JVAR_EVECTOR:
    			case JVAR_AUTO_INT:
    			case JVAR_TRAP:
    			break;
    			
    			default:
	    			if(dValue==1)
	    				return FALSE;
    		}
    	break;
    
    };
    
    
	return DB_REDRAW_AND_CONTINUE;
}

void HexSTShowMemStr(void)
{
	if(!global.hex_dat.nibble)
		STShowMemStr(global.hex_dat.top + global.hex_dat.addr);
}

void STShowMemStr(register void *key)
{
	char *ptr=MemoryToStr(key);
	if(ptr)	ST_helpMsg(ptr);
}

char * MemoryToStr(register void* key)
{
	register MEMDAT_DATA_FILE *array;
	register unsigned short mid;
	register unsigned short first=0;
	register unsigned short last;
	unsigned long bsearch_result;
	char *ptr;
	
	ptr=ABSAddressToRomCall(key);
	if(ptr)	return ptr;
	
	array=(MEMDAT_DATA_FILE *)gMEM_DAT_DB_PTR;
	if(!array)	return NULL;
	
	last=array->num_entries;
	
	while(first <= last)
	{
		mid=(first+last)>>1;
		
		if (key>array->mem_locations[mid].ptr)		first=mid+1;
		else if (key<array->mem_locations[mid].ptr)	last=mid-1;
		else
		{
			strcpy(gBuff, (char *)array + array->mem_locations[mid].str_offset + 2);
			return gBuff;
		}
	}
	
	return NULL;
}

