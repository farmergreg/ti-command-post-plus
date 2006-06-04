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
// $Id: dasm.h 13 2004-08-05 20:26:49Z dietsche $

#ifndef _DASM_H_
#define _DASM_H_

enum {EA_SRC_ONLY=0,EA_SRC_AND_DEST=1};
enum {IMM_BYTE=0,IMM_WORD=1,IMM_LONG=2};

#define MAX_DASM_TEXT_LEN (1024)

typedef struct{
	unsigned short *pc;						//the next address to be disassembled
	char text[MAX_DASM_TEXT_LEN];			//human readable disassembly code ie "move.l a0,-(sp)"
}DASM_DAT;

	typedef struct {
		USHORT idx;
		USHORT str_offset;
	}Support_ROM_CALL_LOOKUP_TABLE;
	
	typedef struct {
		USHORT file_size;
		USHORT num_entries;
		Support_ROM_CALL_LOOKUP_TABLE rcall[0xffff-1];
	}ROM_CALL_DATA_FILE;

	void disassemble_one(unsigned short *pc, DASM_DAT *buff);
	char *make_ea(unsigned short *pc, unsigned short *size, short which_ea, short imm_bytes_wide);
	char* MovemDecoder(USHORT dr, WORD list);
	char * RomCallIdxToStr(register unsigned short key);
	char *ABSAddressToRomCall(register void *address);
	USHORT bsearch(USHORT * array, USHORT key, USHORT last);
 	
#endif
