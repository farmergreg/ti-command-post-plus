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
// $Id: oo.c 4 2004-08-05 19:06:59Z dietsche $

#include <tiams.h>
#include "oo.h"
#include "crash.h"
#include "ram.h"
#include "KFLASH.h"

//used when this application is not active to retrieve attributes
AppID GetMyAppID(void)
{
	return EV_getAppID((const UCHAR *)APP_INTERNAL);
}

//retrieves an attribute from this applications frame under nearly any circumstance
void *OO_AbsoluteGet(ULONG selector)
{
	return OO_GetAppAttr(GetMyAppID(), selector);
}

BOOL OO_AbsoluteSet(ULONG selector, void *value)
{
	return OO_SetAppAttr(GetMyAppID(), selector, value);
}