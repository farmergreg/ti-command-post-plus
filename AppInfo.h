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
// $Id: AppInfo.h 13 2004-08-05 20:26:49Z dietsche $

#ifndef _APP_INFO_H_
#define _APP_INFO_H_

	typedef struct {
		WORD optList[1];
		HANDLE pupApps;
		short page;
	}APP_INFO_DAT;

	DWORD cbAppInfoSelect(WORD DlgId, DWORD dValue);
	HANDLE pupAppInfoApps(WORD index);
	void DoAppInfoDialog(void);
	
#endif
