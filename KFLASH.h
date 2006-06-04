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
// $Id: KFLASH.h 25 2004-08-16 05:13:42Z dietsche $

#ifndef _KFLASH_H_
#define _KFLASH_H_

//Version Control and Internal/External App Name
#define APP_VERSION "2.02"
#define APP_TITLE "Command Post Plus"
#define APP_INTERNAL "CMDPOST"
#define NEED_AMS_MAJOR (2)
#define NEED_AMS_MINOR (5)

//#define DEBUG					//enable extra debugging code
//#define NO_EASTER_EGGS		//complile without the easter eggs

#ifdef DEBUG
	//#warning DEBUG mode
	#define TRACE(s)ST_helpMsg(s);
#else
	#define TRACE(s)
#endif

#ifndef _89
#ifndef _92
	#error Please '#define _89' or '#define _92'
#endif
#endif

#ifdef _89
#ifdef _92
	#error '#define _89' and '#define _92' are mutually exclusive
#endif
#endif

#ifdef _89
	#define C(x,y)(x)
#endif
#ifdef _92
	#define C(x,y)(y)
#endif

//check the results of HeapDeref on a handle to determine if it is valid
#define CheckInvalidHandle(DerefedHandle)((ULONG)DerefedHandle==0 || (ULONG)DerefedHandle==0xffffffff || (ULONG)DerefedHandle==0x40000)

//This header requires certain other header files
#include "hexedit.h"
#include "ram.h"
#include "oo.h"
#include "leakwatch.h"
#include "AppInfo.h"
#include "xr.h"		//technically part of this header file; isolated for ease of editing


//return values for HW2PatchInstalled()
#define HW3_Patch		3
#define HW2_Patch_ROM	2
#define HW2_Patch_RAM	1
#define HW2_Patch_None	0

#define CheckKernel()(*(USHORT*)0x32)

//general purpose bit masks
#define BIT_0 0x1
#define BIT_1 0x2
#define BIT_2 0x4
#define BIT_3 0x8
#define BIT_4 0x10
#define BIT_5 0x20
#define BIT_6 0x40
#define BIT_7 0x80

//For determining what goes on during a CM_BACKGROUND event.
#define BG_KernelCheck BIT_0
#define BG_Disassemble BIT_1

//Internal event IDs 
#define ACM_H_WALK_STATUS		(0x500 + 0)
#define ACM_H_WALK_DUMP			(0x500 + 1)
#define ACM_H_WALK_SYM			(0x500 + 2)
#define ACM_New_Formats			(0x500 + 3)	//sent when the user modifies the FORMATS dialog (nothing to do with 'set defaults'
#define ACM_RAMStats			(0x500 + 4)
#define ACM_RAMStressDialog		(0x500 + 5)
#define ACM_Defaults			(0x500 + 6)
#define ACM_SysInfo				(0x500 + 7)
#define ACM_AMS_Info			(0x500 + 8)
#define ACM_BasecodePB			(0x500 + 9)
#define ACM_HW_PB				(0x500 + 10)
#define ACM_LeakWatch			(0x500 + 11)
#define ACM_Hex_Refresh			(0x500 + 12)
#define ACM_Hex_JumpTo			(0x500 + 13)
#define ACM_Hex_Edit			(0x500 + 14)
#define ACM_Hex_JumpVar			(0x500 + 15)
#define ACM_Hex_Find			(0x500 + 16)
#define ACM_Hex_FindNext		(0x500 + 17)
#define ACM_Hex_ResizeHandle	(0x500 + 18)
#define ACM_Hex_AMS_GlobalVars	(0x500 + 19)
#define ACM_Hex_FindPrevious	(0x500 + 20)
#define ACM_AppInfo				(0x500 + 21)
#define ACM_Hex_JumpCommon		(0x500 + 22)
#define ACM_DisASMViewToggle	(0x500 + 23)
#define ACM_UNUSED_FIND_INDEX	(0x500 + 24)	//used by the disassembler to disable the FIND top level menu item
#define ACM_LinkPortLogger		(0x500 + 25)
#define ACM_DisassemblyTools	(0x500 + 26)
#define ACM_Hex_SetBookMark1	(0x500 + 27)
#define ACM_Hex_SetBookMark2	(0x500 + 28)
#define ACM_Hex_JumpBookMark1	(0x500 + 29)
#define ACM_Hex_JumpBookMark2	(0x500 + 30)
#define ACM_UNUSED_BOOKMARK_INDEX (0x500+31)	//used by the disassembler to disable the Bookmark top level menu item

//For simplified exception vector access
#define VECT_ADDR(n)    ((void**)((n)*4))
#define VECT_ADDR_sh(s) ((short)VECT_ADDR(s))
#define GET_VECTOR(v)	(*(long*)(v))
#define SET_VECTOR(v,n)	((*(long*)((long)(v))=(n)))//make sure to disable the vector protection first using the memory mapped ports!!
#define ENABLE_VECTOR_PROTECTION() asm("bset.b #2,$600001",8);
#define DISABLE_VECTOR_PROTECTION() asm("bclr.b #2,$600001",8);

//Number of Vectors Redirected, and total number of vector addrs saved
#define NUM_VECT_REDIR (14-6)
#define NUM_VECT_SAVED ((NUM_VECT_REDIR)+6)
#define NUM_KERNELS (7)
#define MISC_BUFF_LEN (400)

//The Reset Magic Variable
#define RM_DATA_VAR "main\\cmdpost"
#define RM_DATA_VAR_TYPE "INT"

//this is a very special, breakable macro
#define SYMSTR_CONST(s)((BYTE*)("\0"s)+sizeof(s)-1))

typedef struct {
		WORD optList[1];
		char buff[21];
	}MOVEM_DECODE;
	
//this structure handles every setting that Command Post
//may need to save in the event of PACKing, etc...
typedef struct {
	long old_vectors[NUM_VECT_SAVED];
	BOOL AntiCrashInstalled;
	BOOL DisassemblerActive;		//TRUE if viewing disassembly else false (normal hex edit view)
	BOOL VerboseDisassembler;		//a sort of generic variable :)  Currently if true, then convert movem instructions into the human readable form... even though they can be longer than the screen.
	STRESS_DAT stress_dat;
	HEX_DAT hex_dat;
	LEAK_DAT leak_dat;
	HEX_JUMP_DAT hex_jump_dat;
	HEX_EDIT_DAT hex_edit_dat;
	HEX_FIND_DAT hex_find_dat;
	HEX_RESIZE_HANDLE hex_resize_handle;
	HEX_JUMP_GLOBAL_VAR hex_jump_global_var;
	HEX_JUMP_COMMON_MEM hex_jump_common_mem;
	APP_INFO_DAT app_info_dat;
	MOVEM_DECODE movem_decode;
	char BgEventMask;			//what process(s) needs to be executed during CM_BACKGROUND events
}PACK_DAT;

typedef struct {
	BOOL AntiCrashInstalled;
	WORD byteswide;
	BOOL VerboseDisassembler;
}RESET_MAGIC_DAT;


enum {CPP_DB_OPEN, CPP_DB_CLOSE};

//Variables (data section)
extern pFrame pAppObj;
extern WINDOW appW;
extern const char * const gCrashText[NUM_VECT_REDIR];
extern long gRedirect[NUM_VECT_REDIR];
extern short gVectors[NUM_VECT_SAVED];
extern char * gKernels[NUM_KERNELS];
extern USHORT gKernelID[NUM_KERNELS];
extern PACK_DAT global;
extern char gBuff[MISC_BUFF_LEN + 1];
extern char *gROM_CALL_DB_PTR;
extern ULONG *gROM_CALL_ADDR_PTR;
extern char *gMEM_DAT_DB_PTR;

//global functions
DWORD NoCallBack( WORD DlgId, DWORD Value );
unsigned long GetLongArg(EStackIndex index, unsigned long rLow, unsigned long rHigh);
long StrToEStackToLong(char *str);
BOOL h220xtsrInstalled(void);
BOOL HW2PatchInstalled(void);
DWORD cbFormatDialog(WORD DlgId, DWORD dValue);
char * DataBase(const char *var_name, const char *var_type, USHORT mode);

#endif
