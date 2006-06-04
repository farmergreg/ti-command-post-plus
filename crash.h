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
// $Id: crash.h 13 2004-08-05 20:26:49Z dietsche $

#ifndef _CRASH_H_
#define _CRASH_H_
 
void DisableCrashProtection(void);
void EnableCrashProtection(void);
void SetExceptionVectors(const short vect_list[], const long new_vect[], short num);
void BackupExceptionVectors(const short vlist[], long vsaved[], short num);
void MakeExceptionVectorBackup(void);

void Exception_0(void);
void Exception_1(void);
void Exception_2(void);
void Exception_3(void);
void Exception_4(void);
void Exception_5(void);
void Exception_6(void);
void Exception_7(void);

#endif
