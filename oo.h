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
// $Id: oo.h 13 2004-08-05 20:26:49Z dietsche $

//you are highly encouraged NOT to use these unless I have specifically documented
//what and how each entry point works in the "Shared-Code Library" section.
//certain entry points were of value at some time or another, but have been depreciated since that
//time
#ifndef __OO_H__
#define __OO_H__

//Application Frame Object Attribute Data Slots
#define OO_PROTECTION_ACTIVE	(OO_FIRST_APP_ATTR + 0)		//pointer to BOOL AntiCrashInstalled (**READ ONLY**)
#define OO_REDIRECTED_VECT		(OO_FIRST_APP_ATTR + 1)		//pointer to long gRedirect[NUM_VECT_REDIR]
#define OO_VECTORS				(OO_FIRST_APP_ATTR + 2)		//pointer to short gVectors[NUM_VECT_SAVED]
#define OO_OLD_VECTORS			(OO_FIRST_APP_ATTR + 3)		//poitner to long old_vectors[NUM_VECT_SAVED]
#define OO_VECT_REDIR			(OO_FIRST_APP_ATTR + 4)		//(short) NUM_VECT_REDIR
#define OO_VECT_SAVED			(OO_FIRST_APP_ATTR + 5)		//(short) NUM_VECT_SAVED			
#define OO_BACKUP_VECTORS		(OO_FIRST_APP_ATTR + 6)		//void MakeExceptionVectorBackup(void);
#define OO_INSTALL_VECTORS		(OO_FIRST_APP_ATTR + 7)		//void EnableCrashProtection(void);
#define OO_UNINSTALL_VECTORS	(OO_FIRST_APP_ATTR + 8)		//void DisableCrashProtection(void);
#define OO_KERNELS				(OO_FIRST_APP_ATTR + 9)		//pointer to char * gKernels[NUM_KERNELS];
#define OO_KERNELIDS			(OO_FIRST_APP_ATTR + 10)	//poitner to USHORT *gKernelID[NUM_KERNELS]
#define OO_NUM_KERNELS			(OO_FIRST_APP_ATTR + 11)	//(USHORT)Number of Known Kernels
#define OO_LEAK_WATCH_BEGIN		(OO_FIRST_APP_ATTR + 12)	//void export_LeakWatchBegin(void);
#define OO_LEAK_WATCH_END		(OO_FIRST_APP_ATTR + 13)	//DWORD export_LeakWatchEnd(char *);
#define OO_DASM_ONE				(OO_FIRST_APP_ATTR + 14)	//void disassemble_one(unsigned short *pc, DASM_DAT *buff);
#define OO_OPEN_DATABASES		(OO_FIRST_APP_ATTR + 15)	//void OpenAllDatabases(void);
#define OO_CLOSE_DATABASES		(OO_FIRST_APP_ATTR + 16)	//void CloseAllDatabases(void);

#define LAST_USED_OO	OO_CLOSE_DATABASES
#define FIRST_USED_OO	OO_PROTECTION_ACTIVE
#define NUM_OO_USED	(LAST_USED_OO - FIRST_USED_OO + 1)


//Public Function Prototypes
AppID GetMyAppID(void);
void *OO_AbsoluteGet(ULONG selector);
BOOL OO_AbsoluteSet(ULONG selector, void *value);

#endif
