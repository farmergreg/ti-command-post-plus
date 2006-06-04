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
// $Id: ram.h 13 2004-08-05 20:26:49Z dietsche $

#ifndef _RAM_H_
#define _RAM_H_

#define STRESS_MAX_VARS 0x32

typedef struct {
	char txtBytes[21];	//Number of Bytes to leave free or use up (as a asciz string)
	WORD optList[2];	//Popup Menu Values
	//HANDLE h;			//Handle of last handle used for handle stress tests
}STRESS_DAT;

typedef struct {
	HANDLE previous;
}STRESS_HANDLES;

//ID's of each field in dlgStressTest	
	enum { STRESS_POP_STATUS=0, STRESS_POP_MODE, STRESS_BYTES, STRESS_HEADER };
    enum { OPT_STATUS=0, OPT_MODE };
    
//public functions
void DoRAMStatsDialog(void);

void ext_bclr(void);
void ext_bset(void);
void ext_btst(void);
void ext_StressTest(void);
void ext_PeekB(void);
void ext_PeekW(void);
void ext_PeekL(void);
void ext_PokeB(void);
void ext_PokeW(void);
void ext_PokeL(void);
void ext_HeapDeref(void);
void ext_HeapShuffle(void);

void DoStressTestDialog(void);
DWORD cbStressTest(WORD DlgId, DWORD dValue);
void do_LowMemStressTest(void);

#endif
 