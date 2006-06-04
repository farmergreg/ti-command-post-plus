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
// $Id: ram.c 4 2004-08-05 19:06:59Z dietsche $

#include <tiams.h>
#include "KFLASH.h"
#include "KFLASHr1.h"
#include "ram.h"
#include "undoc.h"

void do_LowMemStressTest(void)
{
	HSYM sym;
	volatile HANDLE h;
	STRESS_DAT *gdat=&global.stress_dat;
	DWORD freemem;
	char varbuff[MAX_SYM_LEN];
	char tvarbuff[MAX_SYM_LEN];
	BYTE *ptr;
	unsigned short counter;
	unsigned short alloc;
		
	for(counter=0;counter<STRESS_MAX_VARS;counter++)
	{//remove any previously created files
	 // this has a dual purpose: 1 handle STRESS_DISABLE
	 // and two: prepare to handle STRESS_ENABLE if applicable
		sprintf(varbuff, OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_LowMemFmtStr), counter);
		ptr=StrToTokN((BYTE*)varbuff, (BYTE*)tvarbuff);
		SymDel(ptr);
	}

//rezero counter
	counter=0;
		
	if(gdat->optList[OPT_STATUS]==STRESS_ENABLE)
	{
		freemem=StrToEStackToLong(gdat->txtBytes);
		
		if(gdat->optList[OPT_MODE]==STRESS_MODE_USE)
		{//internally, the app operates in STRESS_MODE_FILL
			freemem=HeapAvail()-freemem;
		}
		else
			freemem+=2;//adjust by two to get correct debugging HeapAvail results (before vs after);
		
		while(freemem<=HeapAvail())
		{   
			sprintf(varbuff, OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_LowMemFmtStr), counter++);
			ptr=StrToTokN((BYTE*)varbuff, (BYTE*)tvarbuff);
				
		//create the variable
			if(!(sym=SymAdd(ptr)))
				break;		

		//Calculate amount to allocate
		alloc=HeapMax();
		if(HeapAvail()-alloc<=freemem)	//if projected mem usage less than wanted
			alloc=HeapAvail()-freemem;	//then allocate the difference to get exact amount
						
		if(!(h=HeapAlloc(alloc)))		//allocate the memory
			break;	//just exit on error--no cleanup required

			ptr=HeapDeref(h);
			alloc-=2;					//prepare to set variable size (2 less than actual)
			ptr[0]=alloc >> 8;			//set the variable size
			ptr[1]=alloc & 0xff;		//set the variable size
			
			ptr+=(alloc-4);			//move to 6 before var end and set the variable type
			ptr[0]= 0;
			ptr[1]='t';
			ptr[2]='m';
			ptr[3]='p';
			ptr[4]= 0;
			ptr[5]=GEN_DATA_TAG;

			DerefSym(sym)->hVal=h;	//Attach the memory to the previously created variable
			
			if(counter>=STRESS_MAX_VARS)break;
		}
	}
}

//Implements thisapp.LowMem
//returns previous settings as a list
//if no input, returns current settings
void ext_StressTest(void)
{
	Access_AMS_Global_Variables;
	EStackIndex oldtop;
	EStackIndex argptr, topstack;
	STRESS_DAT *gdat=&global.stress_dat;
	STRESS_DAT s_dat=*gdat;
	unsigned long  args;
    short argcount;

//Init estack variables
	oldtop=argptr=top_estack;		
	argcount=remaining_element_count(argptr);

//Error Checking
	if(argcount>3)	ER_throw(TOO_MANY_ARGS_ERROR);

	TRY
		
	//push the current info onto the estack as the return value	
		push_quantum(END_TAG);
	 	push_long_to_integer(strtol(s_dat.txtBytes, NULL, 0));
	 	push_ushort_to_integer(s_dat.optList[OPT_MODE]);
	 	push_ushort_to_integer(s_dat.optList[OPT_STATUS] - 1);
	 	push_quantum(LIST_TAG);
		 	
	//no arguments? do not process any further
	 	if(argcount==0)
	 		return;
		
		topstack=top_estack;
		
			
	//Get arg1 and check for immediate error
		push_simplify(argptr);			
		args=GetValue(top_estack, 0, 3);
		
	//handle arg1	
		switch(args)
		{//used a switch in case i want to use 1 instead of default for the STRESS_ENABLE trigger
			case 0:		//Turn Off	Stress Test
				s_dat.optList[OPT_STATUS]=STRESS_DISABLE;
			break;
			
			//case 1:
			default:	//Turn ON Stress Test	(any number except zero)
				s_dat.optList[OPT_STATUS]=STRESS_ENABLE;
			//break;
			//case 2:
			//case 3:
			
		};
			
		if(argcount>1)//if more than one argument, then all three must be present
		{
			push_simplify(argptr=next_expression_index(argptr));
			args=GetValue(top_estack, 1, 2);		
	
		//handle arg2		
			switch(args)
			{
				case 1:			//leave x bytes free
					s_dat.optList[OPT_MODE]=STRESS_MODE_FILL;
				break;
				
				case 2:			//use at most x bytes total
					s_dat.optList[OPT_MODE]=STRESS_MODE_USE;
				break;
			};
			
		}//end if(argcount>1)
		
		if(argcount>2)
		{
			push_simplify(argptr=next_expression_index(argptr));
			args=GetValue(top_estack, 0, LONG_MAX);
			sprintf(s_dat.txtBytes, "%ld", args);
		}// end if(argcount>2)
	
	//restore the estack
		top_estack=topstack;	
		
	//copy the updated local struct to the global struct
		*gdat=s_dat;
	
	//Activate any changes
		do_LowMemStressTest();
		
	ONERR
		top_estack=oldtop;	//is this right...
		PASS;
	ENDTRY			 
}

void DoStressTestDialog(void)
{   
	Access_AMS_Global_Variables;
	
	STRESS_DAT *gdat=&global.stress_dat;
	STRESS_DAT localdat=*gdat;				//make a local backup copy
	
	switch(Dialog(&dlgStressTest, -1, -1, gdat->txtBytes, gdat->optList))
	{
		case KB_ESC:				//discard the changes
			*gdat=localdat;
			break;
			
		case DB_MEMFULL:			//handle low memory error
			EV_errorCode=ER_MEMORY;
			break;
	}

//Activate any changes
	do_LowMemStressTest();	
}

//callback routine for dlgStressTest
DWORD cbStressTest(WORD DlgId, DWORD dValue)
{
	STRESS_DAT *gdat=&global.stress_dat;	//pointer to the global data (saves space)
	long val;
		
	switch(DlgId)
	{
		case DB_QACTIVE:	//is (dValue) active?
			if(gdat->optList[0]==STRESS_DISABLE && dValue!=STRESS_POP_STATUS && dValue!=STRESS_HEADER)	//disable every item except STRESS_POP_STATUS and Header
				return FALSE;
			/*else
				return TRUE;*/
				
		default:
			return DB_REDRAW_AND_CONTINUE;
		break;
	};
}

//Displays The largest allocatable block of ram, and amount of available ram
void DoRAMStatsDialog(void)
{
	Access_AMS_Global_Variables;
	char buff[500];
	//>>10 to get (K) by integer division
	sprintf(buff,
				XR_stringPtr(XR_MemoryInfo),
				HeapAvail(), 
				HeapMax(),
				FreeHandles(), 
				HeapWalk(H_WALK_VERIFY)?XR_stringPtr(XR_HeapVaild):XR_stringPtr(XR_HeapInvalid),
				FlashMemoryEnd);
				
	DlgNotice(XR_stringPtr(XR_LongAppName),buff);
}

void ext_HeapShuffle(void)
{
	HeapShuffle();
}

void ext_HeapDeref(void)
{
	Access_AMS_Global_Variables;
	EStackIndex oldtop;	
	EStackIndex argptr;
	HANDLE h;
	void *addr;
	short argcount;
	
	HeapCompress();
	oldtop=argptr=top_estack;
	
	TRY	
		argcount=remaining_element_count(argptr);
		
		if(argcount>1) ER_throw(TOO_MANY_ARGS_ERROR);
		if(argcount<1) ER_throw(TOO_FEW_ARGS_ERROR);
		
		push_quantum(END_TAG);
		push_simplify(argptr);			
		h=(HANDLE)GetLongArg(top_estack, 0, ULONG_MAX);
		
		top_estack=oldtop;
		
		addr=HeapDeref(h);
		if(CheckInvalidHandle(addr)) ER_throwFrame(ER_InvalidHandle, pAppObj);
		push_ulong_to_integer((ULONG)addr);
	ONERR
		top_estack=oldtop;
		PASS;
	ENDTRY
}

void ext_PeekB(void)
{
	Access_AMS_Global_Variables;
	EStackIndex oldtop;	
	EStackIndex argptr;
	unsigned char *address;
	short argcount;
	
	oldtop=argptr=top_estack;
	
	TRY	
		argcount=remaining_element_count(argptr);
		
		if(argcount>1) ER_throw(TOO_MANY_ARGS_ERROR);
		if(argcount<1) ER_throw(TOO_FEW_ARGS_ERROR);
		
		push_quantum(END_TAG);
		push_simplify(argptr);			
		address=(UCHAR*)(long)GetLongArg(top_estack, 0, ULONG_MAX);
		
		top_estack=oldtop;
		push_ushort_to_integer(*address&0xff);
	ONERR
		top_estack=oldtop;
		PASS;
	ENDTRY
}

void ext_PeekW(void)
{
	Access_AMS_Global_Variables;
	EStackIndex oldtop;	
	EStackIndex argptr;
	short *address;
	short argcount;
	
	oldtop=argptr=top_estack;
	
	TRY	
		argcount=remaining_element_count(argptr);
		
		if(argcount>1) ER_throw(TOO_MANY_ARGS_ERROR);
		if(argcount<1) ER_throw(TOO_FEW_ARGS_ERROR);

		push_simplify(argptr);			
		address=(short*)(long)GetLongArg(top_estack, 0, ULONG_MAX);
		top_estack=oldtop;
		
		if((long)address%2)ER_throwFrame(ER_Address, pAppObj); //ER_throw(ER_ARGUMENT);
		push_ushort_to_integer(*address);		
	ONERR
		top_estack=oldtop;
		PASS;
	ENDTRY
}

void ext_PeekL(void)
{
	Access_AMS_Global_Variables;
	EStackIndex oldtop;	
	EStackIndex argptr;
	ULONG *address;
	short argcount;
	
	oldtop=argptr=top_estack;
	
	TRY	
		argcount=remaining_element_count(argptr);
		
		if(argcount>1) ER_throw(TOO_MANY_ARGS_ERROR);
		if(argcount<1) ER_throw(TOO_FEW_ARGS_ERROR);

		push_simplify(argptr);			
		address=(ULONG*)(long)GetLongArg(top_estack, 0, ULONG_MAX);
		top_estack=oldtop;
		
		if((long)address%2)ER_throwFrame(ER_Address, pAppObj); //ER_throw(ER_ARGUMENT);
		push_ulong_to_integer(*address);		
	ONERR
		top_estack=oldtop;
		PASS;
	ENDTRY
}

void ext_PokeB(void)
{
	Access_AMS_Global_Variables;
	EStackIndex oldtop;	
	EStackIndex argptr, top;
	char *address;
	char value;
	short argcount;
	
	oldtop=argptr=top_estack;
	
	TRY	
		argcount=remaining_element_count(argptr);
		
		if(argcount>2) ER_throw(TOO_MANY_ARGS_ERROR);
		if(argcount<2) ER_throw(TOO_FEW_ARGS_ERROR);

		push_simplify(argptr);			
		address=(char*)(long)GetLongArg(top_estack, 0, ULONG_MAX);
		push_simplify(next_expression_index(argptr));
		value=(char)GetLongArg(top_estack, 0, USHRT_MAX);
		top_estack=oldtop;
		
		push_ushort_to_integer(*address&0xff);
        
		*address=value;
	ONERR
		top_estack=oldtop;
		PASS;
	ENDTRY
}

void ext_PokeW(void)
{
	Access_AMS_Global_Variables;
	EStackIndex oldtop;	
	EStackIndex argptr, top;
	short *address;
	short value;
	short argcount;
	
	oldtop=argptr=top_estack;
	
	TRY	
		argcount=remaining_element_count(argptr);
		
		if(argcount>2) ER_throw(TOO_MANY_ARGS_ERROR);
		if(argcount<2) ER_throw(TOO_FEW_ARGS_ERROR);
		
		push_simplify(argptr);

		address=(short*)(long)GetLongArg(top_estack, 0, LONG_MAX);
		push_simplify(next_expression_index(argptr));
		value=(short)GetLongArg(top_estack, 0, USHRT_MAX);
		top_estack=oldtop;
		
		if((long)address%2)ER_throwFrame(ER_Address, pAppObj); //ER_throw(ER_ARGUMENT);
		
		push_ushort_to_integer(*address);
		
		*address=value;		
	ONERR
		top_estack=oldtop;
		PASS;
	ENDTRY
}

void ext_PokeL(void)
{
	Access_AMS_Global_Variables;
	EStackIndex oldtop;	
	EStackIndex argptr, top;
	ULONG *address;
	ULONG value;
	short argcount;
	
	oldtop=argptr=top_estack;
	
	TRY	
		argcount=remaining_element_count(argptr);
		
		if(argcount>2) ER_throw(TOO_MANY_ARGS_ERROR);
		if(argcount<2) ER_throw(TOO_FEW_ARGS_ERROR);
		
		push_simplify(argptr);

		address=(ULONG*)(long)GetLongArg(top_estack, 0, LONG_MAX);
		push_simplify(next_expression_index(argptr));
		value=(ULONG)GetLongArg(top_estack, 0, ULONG_MAX);
		top_estack=oldtop;
		
		if((long)address%2)ER_throwFrame(ER_Address, pAppObj); //ER_throw(ER_ARGUMENT);
		
		push_ulong_to_integer(*address);
		
		*address=value;		
	ONERR
		top_estack=oldtop;
		PASS;
	ENDTRY
}

void ext_bclr(void)
{
	Access_AMS_Global_Variables;
	EStackIndex oldtop;	
	EStackIndex argptr, top;
	char *address;
	char bitnum;
	short argcount;
	
	oldtop=argptr=top_estack;
	
	TRY	
		argcount=remaining_element_count(argptr);
		
		if(argcount>2) ER_throw(TOO_MANY_ARGS_ERROR);
		if(argcount<2) ER_throw(TOO_FEW_ARGS_ERROR);

		push_simplify(argptr);			
		address=(char*)(long)GetLongArg(top_estack, 0, ULONG_MAX);
		push_simplify(next_expression_index(argptr));
		bitnum=(char)GetLongArg(top_estack, 0, 7);
		top_estack=oldtop;

		if(*address&(1<<bitnum))
			push_ushort_to_integer(1);
		else
			push_ushort_to_integer(0);
			
		*address&= ~(1<<bitnum);
			
	ONERR
		top_estack=oldtop;
		PASS;
	ENDTRY
}

void ext_bset(void)
{
	Access_AMS_Global_Variables;
	EStackIndex oldtop;	
	EStackIndex argptr, top;
	char *address;
	char bitnum;
	short argcount;
	
	oldtop=argptr=top_estack;
	
	TRY	
		argcount=remaining_element_count(argptr);
		
		if(argcount>2) ER_throw(TOO_MANY_ARGS_ERROR);
		if(argcount<2) ER_throw(TOO_FEW_ARGS_ERROR);

		push_simplify(argptr);			
		address=(char*)(long)GetLongArg(top_estack, 0, ULONG_MAX);
		push_simplify(next_expression_index(argptr));
		bitnum=(char)GetLongArg(top_estack, 0, 7);
		top_estack=oldtop;

		if(*address&(1<<bitnum))
			push_ushort_to_integer(1);
		else
			push_ushort_to_integer(0);
			
		*address|=(1<<bitnum);
	
	ONERR
		top_estack=oldtop;
		PASS;
	ENDTRY
}

void ext_btst(void)
{
	Access_AMS_Global_Variables;
	EStackIndex oldtop;	
	EStackIndex argptr, top;
	char *address;
	char bitnum;
	short argcount;
	
	oldtop=argptr=top_estack;
	
	TRY	
		argcount=remaining_element_count(argptr);
		
		if(argcount>2) ER_throw(TOO_MANY_ARGS_ERROR);
		if(argcount<2) ER_throw(TOO_FEW_ARGS_ERROR);

		push_simplify(argptr);			
		address=(char*)(long)GetLongArg(top_estack, 0, ULONG_MAX);
		push_simplify(next_expression_index(argptr));
		bitnum=(char)GetLongArg(top_estack, 0, 7);
		top_estack=oldtop;
		
		if(*address&(1<<bitnum))
			push_ushort_to_integer(1);
		else
			push_ushort_to_integer(0);
	ONERR
		top_estack=oldtop;
		PASS;
	ENDTRY
}