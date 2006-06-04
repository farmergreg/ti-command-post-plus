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
// $Id: crash.c 10 2004-08-05 19:49:20Z dietsche $

#include <tiams.h>
#include "crash.h"
#include "oo.h"
#include "ram.h"
#include "KFLASH.h"
#include "undoc.h"

typedef struct
{
	unsigned long  a0;
	unsigned long  a1;
	unsigned long  a2;
	
	unsigned short sr;		/* STATUS REGISTER */
	unsigned long  pc;		/* PROGRAM COUNTER */

	unsigned long  a3;
	unsigned long  a4;
	unsigned long  a5;
	unsigned long  a6;
	
	unsigned long  d0;
	unsigned long  d1;
	unsigned long  d2;
	unsigned long  d3;
	unsigned long  d4;
	unsigned long  d5;
	unsigned long  d6;
	unsigned long  d7;
	
	unsigned long usp;		/* USER STACK POINTER */
	unsigned long ssp;		/* SUPERVISOR STACK POINTER */
	
}VECTOR_ELSE;

typedef struct
{
	unsigned long  a0;
	unsigned long  a1;
	unsigned long  a2;
	
	unsigned short flags;	/* only bits 0-4 are used */
	unsigned long  address;	/* ACCESS ADDRESS */
	unsigned short ir;		/* INSTRUCTION REGISTER */
	unsigned short sr;		/* STATUS REGISTER */
	unsigned long  pc;		/* PROGRAM COUNTER */
	
	unsigned long  a3;
	unsigned long  a4;
	unsigned long  a5;
	unsigned long  a6;
	
	unsigned long  d0;
	unsigned long  d1;
	unsigned long  d2;
	unsigned long  d3;
	unsigned long  d4;
	unsigned long  d5;
	unsigned long  d6;
	unsigned long  d7;
	
	unsigned long usp;		/* USER STACK POINTER */
	unsigned long ssp;		/* SUPERVISOR STACK POINTER */
	
}VECTOR_ZERO;
	
static void RestoreLCD(void);
	 
static void ProcessException(short exception, short frametype)
{
	VECTOR_ELSE *ve=NULL;
	VECTOR_ZERO *vz=NULL;
	char buff[512];
	
	const char xml_begin[]="<ErrorReport>\r\n\t<ErrorTitle>%s</ErrorTitle>\r\n\t<Registers>\r\n";
	
	const char xml_registers[]="\t\t<d0>0x%08lx</d0>\r\n"	//391
		"\t\t<d1>0x%08lx</d1>\r\n"
		"\t\t<d2>0x%08lx</d2>\r\n"
		"\t\t<d3>0x%08lx</d3>\r\n"
		"\t\t<d4>0x%08lx</d4>\r\n"
		"\t\t<d5>0x%08lx</d5>\r\n"
		"\t\t<d6>0x%08lx</d6>\r\n"
		"\t\t<d7>0x%08lx</d7>\r\n"
		"\t\t<a0>0x%08lx</a0>\r\n"
		"\t\t<a1>0x%08lx</a1>\r\n"
		"\t\t<a2>0x%08lx</a2>\r\n"
		"\t\t<a3>0x%08lx</a3>\r\n"
		"\t\t<a4>0x%08lx</a4>\r\n"
		"\t\t<a5>0x%08lx</a5>\r\n"
		"\t\t<a6>0x%08lx</a6>\r\n"
		"\t\t<usp>0x%08lx</usp>\r\n"
		"\t\t<ssp>0x%08lx</ssp>\r\n"
		"\t</Registers>\r\n";
		
	const char xml_frame[]="\t<ErrorFrame type=\"%u\">\r\n"
		"\t\t<Flags>0x%04hx</Flags>\r\n"
		"\t\t<AccessAddress>0x%08lx</AccessAddress>\r\n"
		"\t\t<InstructionRegister>0x%04hx</InstructionRegister>\r\n"
		"\t\t<ProgramCounter>0x%08lx</ProgramCounter>\r\n"
		"\t\t<StatusRegister>0x%04hx</StatusRegister>\r\n"
		"\t</ErrorFrame>\r\n";
    
	const char xml_4[]="\t<UserStack>\r\n";
	const char xml_5[]="\t\t<address>0x%08lx</address>\r\n\t\t<value>0x%04hx</value>\r\n";
	const char xml_6[]="\t</UserStack>\r\n";
    
    /*
	const char xml_7[]="\t<SupervisorStack>\r\n";
	//const char xml_8[]="\t\t<value>0x%04hx</value>\r\n";	//see xml_5
	const char xml_9[]="\t</SupervisorStack>\r\n";
*/
	/*
	const char xml_10[]="\t<Disassembly>\r\n";
	const char xml_11[]="\t\t<instruction>%s</instruction>\r\n";
	const char xml_12[]="\t</Disassembly>\r\n";
	*/
	
	const char xml_end[]="</ErrorReport>\r\n";
	
//Restore saved state info and attempt crash recovery
	SetExceptionVectors(OO_AbsoluteGet(OO_VECTORS), OO_AbsoluteGet(OO_OLD_VECTORS),     (short)OO_AbsoluteGet(OO_VECT_SAVED));
	SetExceptionVectors(OO_AbsoluteGet(OO_VECTORS), OO_AbsoluteGet(OO_REDIRECTED_VECT), (short)OO_AbsoluteGet(OO_VECT_REDIR));
	
	PortRestore();
	OSSetSR(0);			//a little dangerous, but i need to ensure that the OS can display dialogs, etc...
	
//check the heap for validity
	if(!HeapWalk(H_WALK_VERIFY))
		DlgNotice(OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_LongAppName), OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_HeapCorrupted));

	if(frametype)	ve=(VECTOR_ELSE*)&gBuff;
	else			vz=(VECTOR_ZERO*)&gBuff;
		
	if(DlgMessage(OO_AbsoluteGet(OO_FIRST_APP_STRING + exception),OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_CrashLinkDump), PDB_YES, PDB_NO)==KB_ENTER)
	{
	
		if(!OSCheckLinkOpen())
			OSLinkOpen();
		
		sprintf(buff, xml_begin, OO_AbsoluteGet(OO_FIRST_APP_STRING + exception));
		LIO_SendData((BYTE*)buff,strlen(buff));
		
		if(frametype)
		{//FRAME_ELSE (Frame 1 or 2)			
			sprintf(buff, xml_registers,
				ve->d0,ve->d1,ve->d2,ve->d3,
				ve->d4,ve->d5,ve->d6,ve->d7,
				ve->a0,ve->a1,ve->a2,ve->a3,
				ve->a4,ve->a5,ve->a6,ve->usp,
				ve->ssp);
			LIO_SendData((BYTE*)buff,strlen(buff));

		//we always report the error as error frame 1 even if it should be 2 on occasion...
			sprintf(buff, xml_frame, 1, (USHORT)0, (ULONG)0, (USHORT)0, ve->pc, ve->sr);
			LIO_SendData((BYTE*)buff,strlen(buff));
		}
		else
		{//FRAME_ZERO
			sprintf(buff, xml_registers,
				vz->d0,vz->d1,vz->d2,vz->d3,
				vz->d4,vz->d5,vz->d6,vz->d7,
				vz->a0,vz->a1,vz->a2,vz->a3,
				vz->a4,vz->a5,vz->a6,vz->usp,
				vz->ssp);
			LIO_SendData((BYTE*)buff,strlen(buff));
			
			sprintf(buff, xml_frame, 0, vz->flags&0x1f, vz->address, vz->ir, vz->pc, vz->sr);
			LIO_SendData((BYTE*)buff, strlen(buff));
		}
/*		
//dump usp?
	if(DlgMessage(OO_AbsoluteGet(OO_FIRST_APP_STRING + exception), OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_DumpUSP), PDB_YES, PDB_NO)==KB_ENTER)
	{*/	
	/*
		LIO_SendData((BYTE*)xml_4, strlen(xml_4));		
		{
			short * ptr;
			
			ptr=&(vz?(short*)vz->usp:(short*)ve->usp)[128];			//output the user stack (256 bytes maximum)
			if(ptr>(short*)0x4200)ptr=(short*)0x4200;
			//ptr=(short*)0x4200;											//output the entire stack
			
			while(ptr> (vz?(short*)vz->usp:(short*)ve->usp))
			{
				ptr--;
				sprintf(buff, xml_5, ptr, *ptr);
				LIO_SendData((BYTE*)buff, strlen(buff));
			}
		}
		LIO_SendData((BYTE*)xml_6, strlen(xml_6)); 
	*/
	/*
	 }

//dump ssp?	 
	 if(DlgMessage(OO_AbsoluteGet(OO_FIRST_APP_STRING + exception), OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_DumpSSP), PDB_YES, PDB_NO)==KB_ENTER)
	 {
		LIO_SendData((BYTE*)xml_7, strlen(xml_4));
		{
			short * ptr;
			
			//ptr=&(vz?(short*)vz->ssp:(short*)ve->ssp)[128];			//output the supervisor stack (256 bytes maximum)
			//if(ptr>(short*)0x4200)ptr=(short*)0x4C00;
			
			ptr=(short*)0x4c00;											//output the entire stack
			
			while(ptr> (vz?(short*)vz->ssp:(short*)ve->ssp))
			{
				ptr--;
				sprintf(buff, xml_5, ptr, *ptr);
				LIO_SendData((BYTE*)buff, strlen(buff));
			}
		}
		LIO_SendData((BYTE*)xml_9, strlen(xml_6));
	}
*/		
		LIO_SendData((BYTE*)xml_end, strlen(xml_end));
	}

	OSLinkClose();	
	RestoreLCD();		//This will force the AMS to repaint windows (eventually)... also, redraw that one pesky line
	
//Start Command Post for the disassembly view if requested
	if(DlgMessage(OO_AbsoluteGet(OO_FIRST_APP_STRING + exception), OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_JumpToDisassembly), PDB_YES, PDB_NO)==KB_ENTER)
	{
		global.DisassemblerActive=TRUE;
		global.hex_dat.top=(char *)((vz?(ULONG)vz->pc:(ULONG)ve->pc) & 0xffffffffUL);
		global.hex_dat.addr=0;
		EV_startApp(GetMyAppID(), AP_START_CURRENT);
	}

//Finally, Throw the error	
	ER_throwFrame(exception, pAppObj);
}

static void ProcessExceptionElse(void)
{
asm(
   "move.w #0x2700,sr\n"	//Set interrupt mask
   
	"move.l a2,-(sp)\n"		//
	"move.l a1,-(sp)\n"		//Save a0 - a2 because they will be destroyed shortly
	"move.l a0,-(sp)\n"		//
	
	"lea _gBuff,a0\n"		//placing this entire structure in _gBuff
	
	"move.l (sp)+,(a0)+\n"	//a0
	"move.l (sp)+,(a0)+\n"	//a1
	"move.l (sp)+,(a0)+\n"	//a2
	
	"move.l (sp)+,a1\n"		//The return address
	
	"move.w (sp)+,(a0)+\n"	//sr
	"move.l (sp)+,(a0)+\n"	//pc
	
	
	"move.l a3,(a0)+\n"
	"move.l a4,(a0)+\n"
	"move.l a5,(a0)+\n"
	"move.l a6,(a0)+\n"
	
	"move.l d0,(a0)+\n"
	"move.l d1,(a0)+\n"
	"move.l d2,(a0)+\n"
	"move.l d3,(a0)+\n"
	"move.l d4,(a0)+\n"
	"move.l d5,(a0)+\n"
	"move.l d6,(a0)+\n"
	"move.l d7,(a0)+\n"
	
	"move.l usp,a2\n"
	"move.l a2,(a0)+\n"	//Save a7, the user stack pointer
	
	"move.l a7,(a0)+\n"	//Save the Supervisor Stack Pointer
	
	"move.w #0x700,sr\n"//set the interrupt mask back to user mode
	"move.l a1,-(sp)\n"	//place the return value back on the stack	
	,300);
}

static void ProcessExceptionZero(void)
{
asm(
   "move.w #0x2700,sr\n"	//Set interrupt mask
   
	"move.l a2,-(sp)\n"		//
	"move.l a1,-(sp)\n"		//Save a0 - a2 because they will be destroyed shortly
	"move.l a0,-(sp)\n"		//
	
	"lea _gBuff,a0\n"		//placing this entire structure in _gBuff
	
	"move.l (sp)+,(a0)+\n"	//a0
	"move.l (sp)+,(a0)+\n"	//a1
	"move.l (sp)+,(a0)+\n"	//a2
	
	"move.l (sp)+,a1\n"		//The return address
	
	"move.w (sp)+,(a0)+\n"	//flags
	"move.l (sp)+,(a0)+\n"	//access address
	"move.w (sp)+,(a0)+\n"	//ir
	"move.w (sp)+,(a0)+\n"	//sr
	"move.l (sp)+,(a0)+\n"	//pc
	
	
	"move.l a3,(a0)+\n", 150);
	
asm(//second asm statement to avoid string too long error
	"move.l a4,(a0)+\n"
	"move.l a5,(a0)+\n"
	"move.l a6,(a0)+\n"
	
	"move.l d0,(a0)+\n"
	"move.l d1,(a0)+\n"
	"move.l d2,(a0)+\n"
	"move.l d3,(a0)+\n"
	"move.l d4,(a0)+\n"
	"move.l d5,(a0)+\n"
	"move.l d6,(a0)+\n"
	"move.l d7,(a0)+\n"
	
	"move.l usp,a2\n"
	"move.l a2,(a0)+\n"	//Save a7, the user stack pointer
	
	"move.l a7,(a0)+\n"	//Save the Supervisor Stack Pointer
	
	"move.w #0x700,sr\n"//set the interrupt mask back to user mode
	"move.l a1,-(sp)\n"	//place the return value back on the stack
	,150);
}

//Macros that handle an exception based upon the error frame type stacked
#define ER_FRAME_ZERO(s) { ProcessExceptionZero(); ProcessException(s, 0); }	//this will cause problems on VTI because of bugs in VTI!!
#define ER_FRAME_ELSE(s) { ProcessExceptionElse(); ProcessException(s, 1); }

void Exception_0(void)	{ ER_FRAME_ZERO(ER_Address); } //"Address Error"
void Exception_1(void)  { ER_FRAME_ELSE(ER_Illegal); } //"Illegal Instruction"
void Exception_2(void)  { ER_FRAME_ELSE(ER_Divide);  } //"Divide by Zero"
void Exception_3(void)  { ER_FRAME_ELSE(ER_CHK);     } //"CHK Instruction"
void Exception_4(void)  { ER_FRAME_ELSE(ER_TrapV);   } //"TRAPV Instruction"
void Exception_5(void)  { ER_FRAME_ELSE(ER_Priv);    } //"Privilege Violation"
void Exception_6(void)  { ER_FRAME_ELSE(ER_TraceInt);} //"Trace Interrupt"
void Exception_7(void)  { ER_FRAME_ELSE(ER_SpIntr);  } //"Spurious Interrupt"

	
void SetExceptionVectors(const short vect_list[], const long new_vect[], short num)
{
	short x;
	
	DISABLE_VECTOR_PROTECTION();
	
	for(num--;num>-1;num--)
	{
		SET_VECTOR(vect_list[num], new_vect[num]);
	}
	
	ENABLE_VECTOR_PROTECTION();
}

void BackupExceptionVectors(const short vlist[], long vsaved[], short num)
{
	for(num--;num>-1;num--)
	{
		vsaved[num]=(long)GET_VECTOR((long)vlist[num]);
	}
}

void EnableCrashProtection(void)
{//install own crash protection vectors

//do not change the crash protection status if a kernel is installed
//or we could cause a malfunction, crash, or memory leak...
	if(CheckKernel())	return;
	
	SetExceptionVectors(OO_AbsoluteGet(OO_VECTORS), OO_AbsoluteGet(OO_REDIRECTED_VECT), (short)OO_AbsoluteGet(OO_VECT_REDIR));
	global.AntiCrashInstalled=TRUE;
}

void DisableCrashProtection(void)
{//Restore all changed vectors back to original saved state

//do not change the crash protection status if a kernel is installed
//or we could cause a malfunction, crash, or memory leak...
	if(CheckKernel())	return;
		
	SetExceptionVectors(OO_AbsoluteGet(OO_VECTORS), OO_AbsoluteGet(OO_OLD_VECTORS), (short)OO_AbsoluteGet(OO_VECT_SAVED));
	global.AntiCrashInstalled=FALSE;
}

void MakeExceptionVectorBackup(void)
{//because this func is exported, it does some extra error checking
	register BOOL isProtected=global.AntiCrashInstalled;
	
	if(isProtected)	{ DisableCrashProtection();	}	//Don't want to backup currently installed vectors	
	
	BackupExceptionVectors(OO_AbsoluteGet(OO_VECTORS), OO_AbsoluteGet(OO_OLD_VECTORS), (short)OO_AbsoluteGet(OO_VECT_SAVED));
	
	if(isProtected)	{ EnableCrashProtection();	}	//Re-enable crash protection if it was disabled
}


static void RestoreLCD(void)
{//Binary of HSR v3.0
	asm(" .word 0x48e7,0xfffe,0x2878,0x00c8,0x206c,0x0124,0x4e90,0x3f3c,0x000a\n"
		" .word 0x206c,0x03ac,0x4e90,0x206c,0x038c,0x4e90,0x2f3c,0x0000,0x001e,0x3f3c\n"
		" .word 0x00ff,0x200c,0x0280,0x0040,0x0000,0x6612,0x206c,0x00bc,0x0c28,0x00ef\n"
		" .word 0x0002,0x6706,0x4878,0x56e6,0x6004,0x4878,0x5a2e,0x206c,0x09f0,0x4e90\n"
		" .word 0x2054,0x2050,0x0050,0x2000,0x4aa8,0x0022,0x2068,0x0022,0x66f2,0x4fef\n"
		" .word 0x000c,0x4cdf,0x7fff",104);//,0x4e75 (rts) 0x4e71(nop)
}

