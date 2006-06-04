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
// $Id: AppInfo.c 4 2004-08-05 19:06:59Z dietsche $
#include <tiams.h>
#include "KFLASH.h"
#include "KFLASHr1.H"
#include "AppInfo.h"

char*  AppACB(AppID app);
char* AppHDR(AppID app);
char* AppFlags(AppID app);

//callback routine for dlgLeakWatch
DWORD cbAppInfoSelect(WORD DlgId, DWORD dValue)
{
	APP_INFO_DAT *d=&global.app_info_dat;
	static WINDOW *win=NULL;
	static WIN_RECT wr={0,29,0,0};
	AppID app;
	char *pupText;
	short lastkey;
	
	switch(DlgId)
	{
		case 0:	//Dynamic Text
			win=((OWNER_DRAW_STRUCT *) dValue)->pW;
			if(strlen(pupText=PopupText(d->pupApps, d->optList[0])))
			{
				app=OO_AppNameToACB((UCHAR *)pupText,TRUE);
				wr.x1=WinWidth(win);
				wr.y1=WinHeight(win)-12;
				WinFill(win, &wr, A_REVERSE);
				
				if(d->page==KB_F2)
					WinStrXYWrap(win, 8, 19+(1*10), AppACB(app),WWF_DRAW);
				else if(d->page==KB_F3)
					WinStrXYWrap(win, 8, 19+(1*10), AppHDR(app),WWF_DRAW);
				else if(d->page==KB_F4)
					WinStrXYWrap(win, 8, 19+(1*10), AppFlags(app),WWF_DRAW);
			}
			else
			{
				d->page=KB_F1;
			}
		break;
		case 4:	//Menu
			
			lastkey=d->page;
			switch(d->page=LO_WORD(dValue))
			{
				case KB_F2:
				case KB_F3:
				case KB_F4:
					return 1;
				
				case KB_F1:
					if(win)
						WinFill(win, &wr, A_REVERSE);
					return 0;
				default:
					d->page=lastkey;
					return lastkey==KB_F1?0:1;
			};
		break;
	
	};
	
	return TRUE;
}

char * AppHDR(AppID app)
{
	AppHdr const *head=((ACB*)(HeapDeref((HANDLE)(app))))->appHeader;
	char name[9]={' '};
	char *buff=gBuff;
	
	memcpy(name,head->name,8);
	
	sprintf(buff,XR_stringPtr(XR_APP_HDR),
	head->magic,name,head->flags,head->dataLen,head->codeOffset,
	head->initDataOffset,head->initDataLen,head->optlen);
	
	#ifdef DEBUG
		if(strlen(buff)>MISC_BUFF_LEN)
			DlgNotice("Debug Error","AppHDR buffer overflowed!");
	#endif
	
	return buff;
}

char * AppFlags(AppID app)
{
	ACB *acb=HeapDeref((HANDLE)app);
	USHORT flags=acb->flags;	
	char *flagstr=gBuff;
		
	strcpy(flagstr, XR_stringPtr(XR_ACBFlags));
	
	if(flags&ACB_BUILTIN)
		strcat(flagstr,XR_stringPtr(XR_BUILTIN));
	if(flags&ACB_INSTALLED)
		strcat(flagstr,XR_stringPtr(XR_INSTALLED));
	if(flags&ACB_LOCALIZER)
		strcat(flagstr,XR_stringPtr(XR_LOCALIZER));
	if(flags&ACB_LOCK)
		strcat(flagstr,XR_stringPtr(XR_LOCK));
	if(flags&ACB_JT_VERSION)
		strcat(flagstr,XR_stringPtr(XR_JT_VERSION));
	if(flags&ACB_SELECTED)
		strcat(flagstr,XR_stringPtr(XR_SELECTED));
	if(flags&ACB_COLLAPSE)
		strcat(flagstr,XR_stringPtr(XR_COLLAPSE));
	if(flags&ACB_BG)
		strcat(flagstr,XR_stringPtr(XR_BG));
	if(flags&ACB_COMPRESS)
		strcat(flagstr,XR_stringPtr(XR_COMPRESS));
	if(flags&ACB_DELETE)
		strcat(flagstr,XR_stringPtr(XR_DELETE));
	
	flagstr[strlen(flagstr)-1]=0;
	strcat(flagstr,XR_stringPtr(XR_nAppHeaderFlagsn));
	flags=acb->appHeader->flags;
	
	if(flags&APPHDR_LOCALIZER)
		strcat(flagstr,XR_stringPtr(XR_Localizer));
		
	strcat(flagstr,XR_stringPtr(XR_nAppFlags));
	flags=GetAppFlags(app);
	
	if(flags&APP_INTERACTIVE)
		strcat(flagstr,XR_stringPtr(XR_Interactive));
	if(flags&APP_CON)
		strcat(flagstr,XR_stringPtr(XR_Con));
	if(flags&APP_ACCESS_SYSVARS)
		strcat(flagstr,XR_stringPtr(XR_AccessSysVars));
	if(flags&APP_BACKGROUND)
		strcat(flagstr,XR_stringPtr(XR_Background));
	
	flagstr[strlen(flagstr)-1]=0;
	strcat(flagstr," }");
	
	#ifdef DEBUG
		if(strlen(flagstr)>MISC_BUFF_LEN)
			DlgNotice("Debug Error","AppFlags buffer overflowed! ref: 1");
	#endif
	
	return flagstr;
}

char* AppACB(AppID app)
{
	ACB *acb=HeapDeref((HANDLE)app);
	char *buff=gBuff;
		
	sprintf(buff,XR_stringPtr(XR_APP_ACB),
	acb->flags,acb->myID,acb->next,acb->prev,acb->publicstorage,
	acb->appHeader,acb->certhdr,acb->appData);
	
	#ifdef DEBUG
		if(strlen(buff)>MISC_BUFF_LEN)
			DlgNotice("Debug Error","AppACB buffer overflowed! ref: 2");
	#endif
	
	return buff;
}
	
void DoAppInfoDialog(void)
{
	Access_AMS_Global_Variables;
	char *pupText;
	char buff[250];
	APP_INFO_DAT *d=&global.app_info_dat;

	//force these as default settings for each instance
	if(!d->optList[0])d->optList[0]=1;	
	d->page=KB_F1;
	
	TRY
		switch(Dialog(&dlgAppInfoSelect, -1, -1, NULL, d->optList))
		{	
			case DB_MEMFULL:			//handle low memory error
				EV_errorCode=ER_MEMORY;
			break;
		}
	ONERR
		EV_errorCode=errCode;
	ENDTRY
	
	HeapFreeIndir(&d->pupApps);
}

HANDLE pupAppInfoApps(WORD index)
{
	Access_AMS_Global_Variables;
	HANDLE *h=&global.app_info_dat.pupApps;
	AppID appid;
	
	HeapFreeIndir(h);
	*h=PopupNew(NULL, 0);
	
	for(appid=OO_firstACB; appid; appid=OO_NextACB(appid))
	{	
		PopupAddText(*h, -1,  (char *)GetAppName(appid), 0);
	}
	
	return *h;	
}
