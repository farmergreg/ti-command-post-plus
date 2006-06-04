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
// $Id: hexedit.h 13 2004-08-05 20:26:49Z dietsche $

#ifndef _HEXEDIT_H_
#define _HEXEDIT_H_

 #define HEDIT_BUFF_SIZE 51
 
typedef struct {
	char *top;				//very first displayed address on screen
	long addr;				//offset from top
	short nibble;			//which nibble (0,1) in the byte pointed to by &top[addr]
	short width;			//num display bytes wide
	short height;			//num display bytes tall
	char *kb_left_most;		//where KB_LEFT_MOST jumps to
	char *kb_right_most;	//where KB_RIGHT_MOST jumps to	
	WORD byteswide;			//how wide should the editor be
}HEX_DAT;

typedef struct {
	char txtAddr[21];	//effective address, or handle to jump to
	WORD optList[1];	//Popup Menu Value
}HEX_JUMP_DAT;

typedef struct {
	char txtValue[HEDIT_BUFF_SIZE];
	WORD optList[2];
	char *dlgtitle;
	char *dlginitstr;
}HEX_EDIT_DAT;

typedef struct {
	char txtValue[HEDIT_BUFF_SIZE];
	char txtStopAddr[HEDIT_BUFF_SIZE];
	WORD optList[2];
}HEX_FIND_DAT;

typedef struct {
	char txtValue[42];
}HEX_RESIZE_HANDLE;

typedef struct {
	WORD optList[1];
	char txtValue[21];
}HEX_JUMP_GLOBAL_VAR;

typedef struct {
	WORD optList[1];
	char txtValue[21];
}HEX_JUMP_COMMON_MEM;


	typedef struct {
		void * ptr;
		USHORT str_offset;
	}MEMDAT_LOOKUP_TABLE;
	
	typedef struct {
		USHORT file_size;
		USHORT num_entries;
		MEMDAT_LOOKUP_TABLE mem_locations[0xffff-1];
	}MEMDAT_DATA_FILE;
	

	void HexEditorEventLoop(pFrame self, PEvent e);
	void SetHexEditorDefaults(WINDOW *w);
	DWORD cbHexEdit(WORD DlgId, DWORD dValue);
	DWORD cbJumpAMSVar(WORD DlgId, DWORD dValue);
	
	char * MemoryToStr(register void* key);
	void STShowMemStr(register void *key);
	void HexSTShowMemStr(void);
	unsigned long binsearch(unsigned long *array, unsigned long key, unsigned long last);
	
#endif
 