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
// $Id: leakwatch.c 4 2004-08-05 19:06:59Z dietsche $

#include <tiams.h>
#include "KFLASH.h"
#include "KFLASHr1.H"
#include "leakwatch.h"
#include "undoc.h"

static void LeakWatch_Event_Handler(pFrame self, PEvent e);
static BOOL LeakWatchAppCanDelete(AppID self);
static BOOL LeakWatchAppCanMove(AppID self);
static BOOL AppHasLeakWatch(AppID app);
static void InstallLeakWatch(AppID app);
static void UninstallLeakWatch(AppID app);
static void LeakWatchAll(void);
static VAR_TABLE_INFO *VarTableSize(void);
static void LeakWatchStart(LEAK_INFO *w);

FRAME(LeakWatchFrame, OO_SYSTEM_FRAME, 0, OO_APP_PROCESS_EVENT, 1)
	ATTR(OO_APP_PROCESS_EVENT, 		&LeakWatch_Event_Handler)	//0x0004
//	ATTR(OO_APP_CAN_DELETE,			&LeakWatchAppCanDelete)		//0x000C
//	ATTR(OO_APP_CAN_MOVE,			&LeakWatchAppCanMove)		//0x000D
ENDFRAME

void LeakWatchDialog(void)
{
	Access_AMS_Global_Variables;
	LEAK_DAT *d=&global.leak_dat;
	char *pupText;
	char buff[250];
	
	d->optList[1]=1;	//force currently selected app to be index #1
	
	TRY
		switch(Dialog(&dlgLeakWatch, -1, -1, NULL, d->optList))
		{
			case KB_ENTER:				
				if(strlen(pupText=PopupText(d->pupApps, d->optList[1])))
					switch(d->optList[0])
					{
						case LEAK_INSTALL:
							if(!strcmp(XR_stringPtr(XR_AllApps), pupText))
								LeakWatchAll();
							else
		 						InstallLeakWatch(OO_AppNameToACB((UCHAR *)pupText, TRUE));
		 					sprintf(buff, XR_stringPtr(XR_LeakWatchInstall), pupText);
		 					DlgNotice(XR_stringPtr(XR_LongAppName), buff); 
						break;
						
						case LEAK_UNINSTALL:
							if(!strcmp(XR_stringPtr(XR_AllApps), pupText))
								LeakWatchNone();
							else
								UninstallLeakWatch(OO_AppNameToACB((UCHAR *)pupText, TRUE));
							
							sprintf(buff, XR_stringPtr(XR_LeakWatchRemove), pupText);
		 					DlgNotice(XR_stringPtr(XR_LongAppName), buff);
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
	
	HeapFreeIndir(&d->pupApps);
}

HANDLE pupLeakWatchApps(WORD index)
{
	Access_AMS_Global_Variables;
	LEAK_DAT *d=&global.leak_dat;
	HANDLE *h=&d->pupApps;
	AppID appid;
	
	HeapFreeIndir(h);
	*h=PopupNew(NULL, 0);
	
	for(appid=OO_firstACB; appid; appid=OO_NextACB(appid))
	{	
		switch(d->optList[0])
		{
			case LEAK_INSTALL:
				if(IsLeakWatchable(appid))
					PopupAddText(*h, -1,  (char *)GetAppName(appid), 0); 
			break;
			
			case LEAK_UNINSTALL:
				if(AppHasLeakWatch(appid))
					PopupAddText(*h, -1,  (char *)GetAppName(appid), 0); 					
			break;
		};
	}
	
	if(strlen(PopupText(*h, 2)))//if there is more than 1 item in the dynamic popup
		PopupAddText(*h, -1, XR_stringPtr(XR_AllApps), 0);//add the All Apps option
	
	return *h;	
}

static void LeakWatchAll(void)
{
	Access_AMS_Global_Variables;
	AppID appid;
	
	for(appid=OO_firstACB; appid; appid=OO_NextACB(appid))
	{	
		if(IsLeakWatchable(appid))
			InstallLeakWatch(appid); 					
	}	
}

void LeakWatchNone(void)
{
	Access_AMS_Global_Variables;
	AppID appid;
	
	for(appid=OO_firstACB; appid; appid=OO_NextACB(appid))
	{	
		if(AppHasLeakWatch(appid))
			UninstallLeakWatch(appid); 					
	}	

}

//this routine may throw a low memory error
static void InstallLeakWatch(AppID app)
{
	LEAK_DAT *d=&global.leak_dat;
	LEAK_NODE *node=&d->head;
	LEAK_NODE *previous;
	
	while(node->next)node=HeapDeref(node->next);	//find the last node
	
	previous=node;
	previous->next=HeapAllocThrow(sizeof(LEAK_NODE));
	node=HeapDeref(previous->next);
	
	node->app=app;
	node->next=H_NULL;
	
	if(!OO_InstallAppHook(app, (pFrame)&LeakWatchFrame, &node->frame))
	{
		HeapFreeIndir(&previous->next);
		ER_throw(ER_MEMORY);
	}
}

static void UninstallLeakWatch(AppID app)
{
	LEAK_DAT *d=&global.leak_dat;
	LEAK_NODE *node=&d->head;
	LEAK_NODE *previous=node;
	HANDLE not_the_whales;
	
	do {
		if(app==node->app)break;
		previous=node;
	}while(node=node->next?HeapDeref(node->next):NULL);
	
	OO_UninstallAppHook(app, node->frame);	//unhook
	not_the_whales=previous->next;
	previous->next=node->next;				//adjust linked list
	HeapFree(not_the_whales);				//free this node
}

//returns true if a app has a leak watch frame installed
static BOOL AppHasLeakWatch(AppID app)
{
	LEAK_DAT *d=&global.leak_dat;
	LEAK_NODE *node=&d->head;

	while(node=node->next?HeapDeref(node->next):NULL) {
		if(app==node->app)
			return TRUE;
	}
	
	return FALSE;
}

BOOL LeakWatchAppsNotActive(void)
{
	Access_AMS_Global_Variables;
	LEAK_DAT *d=&global.leak_dat;
	LEAK_NODE *node=&d->head;

	while(node=node->next?HeapDeref(node->next):NULL) {
		if(EV_runningApp==node->app)		//use of Running App is important! i.e. background events, etc...
			return FALSE;
	}
	
	return TRUE;
}

//callback routine for dlgLeakWatch
DWORD cbLeakWatch(WORD DlgId, DWORD dValue)
{
	if(DlgId==0)	return DB_REDRAW_AND_CONTINUE;
	return TRUE;
}

void export_LeakWatchBegin(void)
{
	LEAK_DAT *d=&global.leak_dat;
	LeakWatchStart(&d->external);
}

DWORD export_LeakWatchEnd(char *title)
{
	LEAK_DAT *d=&global.leak_dat;
	return LeakWatchEnd(title, &d->external);
}

static void LeakWatchStart(LEAK_INFO *w)
{
	w->ram=HeapAvail();
	w->vtbl.mem_used=VarTableSize()->mem_used;
	w->vtbl.handles_used=VarTableSize()->handles_used;
	w->freehandles=FreeHandles();
}

DWORD LeakWatchEnd(char *title, LEAK_INFO *w)
{
	DWORD deltamem=HeapAvail()-w->ram;
	DWORD deltavar=VarTableSize()->mem_used-w->vtbl.mem_used;
	DWORD deltavarhandle=VarTableSize()->handles_used-w->vtbl.handles_used;
	short deltahandles=FreeHandles()-w->freehandles;
	char buff[500];
	
	deltahandles+=deltavarhandle;	//adjust deltahandles to negate any vartable size change

	if(deltamem || deltahandles || deltavar)
	{
		sprintf(buff, OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_LeakWatchStr), 
		deltamem,
		deltavar,
		deltamem+deltavar,	//adjust to negate any vartable size
		deltahandles);
		DlgNotice(title, buff);
	}
	return deltamem;
}

static void LeakWatch_Event_Handler(pFrame self, PEvent e)
{//when passing events on, it is very important to check OO_SuperFrame, or
//seemingly random errors can occur
	Access_AMS_Global_Variables;
	LEAK_DAT *d=&global.leak_dat;
	pFrame super = OO_SuperFrame;
	char *appname=OO_GetAttr(self, OO_APP_NAME);
	char buff[500];
	
	switch (e->command)
	{
		case CM_START:
			LeakWatchStart(&d->internal);
			if(super) AppProcessEvent(super, e);
			break;
			
		case CM_QUIT:
			if(super) AppProcessEvent(super, e);
			LeakWatchEnd((char *)appname, &d->internal);
		break;
		
		case CM_PACK:
			sprintf(buff, OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_LeakPackInfo) , appname);
			DlgNotice(appname, buff);
			
		case CM_UNINSTALL:
			UninstallLeakWatch(((ACB*)HeapDeref(OO_AppNameToACB((UCHAR*)appname, TRUE)))->myID);
			if(super) AppProcessEvent(super, e);
		break;
		
		default:
			if(super) AppProcessEvent(super, e);

	};
}

//calculate the size of the variables in the var-link
//this is probabbly best treated as an estimate...
static VAR_TABLE_INFO *VarTableSize(void)
{
	register SYM_ENTRY *sym;
	static VAR_TABLE_INFO vtbl;
	vtbl.mem_used=0;
	vtbl.handles_used=0;
	
	FolderOp(NULL, FL_ALL | FL_LOCK);
	
	sym=SymFindFirst(NULL, FO_RECURSE);
	
	while(sym)
	{
		if(!(sym->Flags & SF_EXTMEM))		//don't count archived variables
		{	
			ULONG handle=(ULONG)HeapDeref(sym->hVal);			
			if(handle!=0 && handle!=0xffffffff)	//make sure the handle exists, or HeapSize will crash
			{//some flash apps make variables without giving them handles.... and then context switch to
			//another app... like *cough* CalcTools *cough*
				vtbl.mem_used+=HeapSize(sym->hVal)+2;
				vtbl.handles_used++;
			}
		}
		sym=SymFindNext();
	}
	
	FolderOp(NULL, FL_ALL | FL_UNLOCK);
	return &vtbl;
}

/*

	typedef struct{
		DWORD mem_used;		//size used by homescreen vars
		DWORD handles_used;	//number of handles used by home screen pairs	
	}HOME_INFO;
		
static HOME_INFO *HomeInfo(void)
{
	register short counter=0;
	HANDLE h;
	static HOME_INFO hinf;
	hinf.mem_used=0;
	hinf.handles_used=0;
	
	while(h=HS_getEntry(counter++))
	{
		hinf.mem_used+=HeapSize(h);
		
		if(h=HS_getAns(counter))
		{
			hinf.mem_used+=HeapSize(h);
			hinf.handles_used++;
		}
		hinf.handles_used++;
	}
	
	
	return &hinf;
}

*/
  