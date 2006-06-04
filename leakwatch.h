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
// $Id: leakwatch.h 13 2004-08-05 20:26:49Z dietsche $

#ifndef _LEAKWATCH_H_
#define _LEAKWATCH_H_
	
	typedef struct{
		DWORD mem_used;		//bytes of memory used by in ram variables
		DWORD handles_used;	//number of handles used by in ram variables
	}VAR_TABLE_INFO;
	
	typedef struct {
		DWORD ram;
		VAR_TABLE_INFO vtbl;
		short freehandles;
	}LEAK_INFO;
	
	typedef struct {
	    HANDLE next;
    	AppID	app;
    	pFrame	frame;
    }LEAK_NODE;
    
	typedef struct {
		LEAK_INFO external;
		LEAK_INFO internal;
		pFrame internalFrame;		//frame pointer for internal leak watch
		WORD optList[2];			//Popup Menu Values
		HANDLE pupApps;				//handle of dynamic popup menu for dialog
		LEAK_NODE head;				//list of apps with a leak watch hook installed (head.next points to first 'real' node)
	}LEAK_DAT;
    
	void LeakWatchDialog(void);
	void export_LeakWatchBegin(void);
	DWORD export_LeakWatchEnd(char *title);
	DWORD LeakWatchEnd(char *title, LEAK_INFO *w);
    void LeakWatchNone(void);
    BOOL LeakWatchAppsNotActive(void);
    
  //conditions of AppID app which need to be met before leak watch can be used on app
	#ifdef DEBUG
  		#define IsLeakWatchable(app) (GetAppFlags(app)&APP_INTERACTIVE && !AppHasLeakWatch(app))
	#else
		#define IsLeakWatchable(app) (GetAppFlags(app)&APP_INTERACTIVE && !(((ACB*)HeapDeref(app))->flags&ACB_BUILTIN) && (app)!=MY_APP_ID(pAppObj) && !AppHasLeakWatch(app))
	#endif
	
	
#endif
 