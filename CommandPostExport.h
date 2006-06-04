/**************************************************
***	Project Title: Command Post Plus (KFLASH)	***
***	Author: Greg Dietsche						***
***	Date:	07/23/2002							***
***	Description: An application designed for	***
*** use with the TI-89 and TI-92 Plus Graphing	***
*** calculators during the testing and			***
*** debugging phases of FLASH APPS and RAM      ***
*** programs									***
***************************************************/
// $Id: CommandPostExport.h 13 2004-08-05 20:26:49Z dietsche $

#ifndef _COMMAND_POST_H_
#define _COMMAND_POST_H_

#ifdef __TIGCC__
	#warning This header file may require some modification to work with TIGCC 
	
	#if MIN_AMS < 204
		#error Command Post Plus Requires AMS 2.04 or later
	#endif
	
	#ifndef OO_GetAppAttr
		#define OO_GetAppAttr _rom_call(void*,(short,long),3FC)
	#endif
	
	#ifndef OO_FIRST_APP_ATTR
		#define OO_FIRST_APP_ATTR 0x10000
	#endif
	
#else
	#ifndef _TIAMS_H
		#error Please include tiams.h before this header file
	#endif
#endif

/*
//Application Frame Object Attribute Data Slots
#define OO_PROTECTION_ACTIVE	(OO_FIRST_APP_ATTR + 0)		//pointer to BOOL AntiCrashInstalled (READ ONLY/cannot/must not be overridden)
#define OO_REDIRECTED_VECT		(OO_FIRST_APP_ATTR + 1)		//pointer to long gRedirect[NUM_VECT_REDIR]
#define OO_VECTORS				(OO_FIRST_APP_ATTR + 2)		//pointer to short gVectors[NUM_VECT_SAVED]
#define OO_OLD_VECTORS			(OO_FIRST_APP_ATTR + 3)		//poitner to long old_vectors[NUM_VECT_SAVED]
#define OO_VECT_REDIR			(OO_FIRST_APP_ATTR + 4)		//(short) NUM_VECT_REDIR
#define OO_VECT_SAVED			(OO_FIRST_APP_ATTR + 5)		//(short) NUM_VECT_SAVED			
#define OO_BACKUP_VECTORS		(OO_FIRST_APP_ATTR + 6)		//void MakeExceptionVectorBackup(void);
#define OO_INSTALL_VECTORS		(OO_FIRST_APP_ATTR + 7)		//void EnableCrashProtection(void);
#define OO_UNINSTALL_VECTORS	(OO_FIRST_APP_ATTR + 8)		//void DisableCrashProtection(void);
#define OO_KERNELS				(OO_FIRST_APP_ATTR + 9)		//pointer to char * gKernels[NUM_KERNELS];
#define OO_KERNELIDS			(OO_FIRST_APP_ATTR + 10)	//pointer to USHORT *gKernelID[NUM_KERNELS]
#define OO_NUM_KERNELS			(OO_FIRST_APP_ATTR + 11)	//(USHORT)Number of Known Kernels
#define OO_LEAK_WATCH_BEGIN		(OO_FIRST_APP_ATTR + 12)	//void export_LeakWatchBegin(void);
#define OO_LEAK_WATCH_END		(OO_FIRST_APP_ATTR + 13)	//DWORD export_LeakWatchEnd(char *);
#define OO_DASM_ONE				(OO_FIRST_APP_ATTR + 14)	//void disassemble_one(unsigned short *pc, DASM_DAT *buff);
#define OO_OPEN_DATABASES		(OO_FIRST_APP_ATTR + 15)	//void OpenAllDatabases(void);
#define OO_CLOSE_DATABASES		(OO_FIRST_APP_ATTR + 16)	//void CloseAllDatabases(void);
*/

/*
	See TI's documentation for the FDL compiler (ghostware) to learn how to use these functions in a project

  casting a pointer to a function is simple:
  ((return_type (* const)(parameter_1_type, parameter_2_type, ...))
*/

#define MAX_DASM_TEXT_LEN (1024)

typedef struct{
	unsigned short *pc;						//the next address to be disassembled
	char text[MAX_DASM_TEXT_LEN];			//human readable disassembly code ie "move.l a0,-(sp)"
}DASM_DAT;


#define CMDPOST_CrashGuardState(obj) \
(*(BOOL*)OO_GetAppAttr(obj,OO_FIRST_APP_ATTR + 0))

#define CMDPOST_MakeExceptionVectorBackup(obj) \
((void (* const)(void))OO_GetAppAttr(obj,OO_FIRST_APP_ATTR + 6))()

#define CMDPOST_EnableCrashGuard(obj) \
((void (* const)(void))OO_GetAppAttr(obj,OO_FIRST_APP_ATTR + 7))()

#define CMDPOST_DisableCrashGuard(obj) \
((void (* const)(void))OO_GetAppAttr(obj,OO_FIRST_APP_ATTR + 8))()

#define CMDPOST_LeakWatch_Begin(obj) \
((void (* const)(void))OO_GetAppAttr(obj,OO_FIRST_APP_ATTR + 12))()

#define CMDPOST_LeakWatch_End(obj,a) \
((DWORD (* const)(char *))OO_GetAppAttr(obj,OO_FIRST_APP_ATTR + 13))(a)

#define CMDPOST_Disassemble_One(obj,pc,buffer) \
((void (* const)(unsigned short *, DASM_DAT *))OO_GetAppAttr(obj,OO_FIRST_APP_ATTR + 14))(pc, buffer)

#define CMDPOST_OpenDisassemblyDatabases(obj) \
((void (* const)(void))OO_GetAppAttr(obj,OO_FIRST_APP_ATTR + 15))()

#define CMDPOST_CloseDisassemblyDatabases(obj) \
((void (* const)(void))OO_GetAppAttr(obj,OO_FIRST_APP_ATTR + 16))()

/*
//to make LeakWatch work in a tigcc project, use this:
//This requires a current version of TIGCC such as Version 0.94 Beta 19
#undef OO_GetAppAttr
#define OO_GetAppAttr _rom_call(void*,(short,unsigned long),3FC)
#undef OO_FIRST_APP_ATTR
#define OO_FIRST_APP_ATTR 0x10000

#define LeakWatch_begin(obj) \
((void (* __ATTR_TIOS__ const)(void))OO_GetAppAttr(obj,OO_FIRST_APP_ATTR + 12))()

#define LeakWatch_end(obj,a) \
((DWORD (* __ATTR_TIOS__ const)(const char *))OO_GetAppAttr(obj,OO_FIRST_APP_ATTR + 13))(a)

HANDLE cmdpost_appid=TIOS_EV_getAppID("CMDPOST");
if(cmdpost_appid)LeakWatch_begin(cmdpost_appid);
...Program Code Goes Here...
if(cmdpost_appid)LeakWatch_end(cmdpost_appid,"Your Program's Name");

MIN_AMS should be set to at least 205
*/

#endif
