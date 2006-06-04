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
// $Id: xr.h 19 2004-08-06 20:11:46Z dietsche $

#ifndef _XR_H_
#define _XR_H_
																		
//Application Defined Error Strings
#define XR_ADDRESS			(OO_FIRST_APP_STRING + 0)
#define XR_ILLEGAL			(OO_FIRST_APP_STRING + 1)
#define XR_DIVIDE			(OO_FIRST_APP_STRING + 2)
#define XR_CHK				(OO_FIRST_APP_STRING + 3)
#define XR_TRAPV			(OO_FIRST_APP_STRING + 4)
#define XR_PRIV				(OO_FIRST_APP_STRING + 5)
#define XR_TRACEINT			(OO_FIRST_APP_STRING + 6)
#define XR_SINT				(OO_FIRST_APP_STRING + 7)
#define XR_InvalidHandle	(OO_FIRST_APP_STRING + 8)
#define XR_InvalidHistItem	(OO_FIRST_APP_STRING + 9)
#define XR_ResetMagicFailedInstall	(OO_FIRST_APP_STRING + 10)
#define XR_ResetMagicFailedRemove	(OO_FIRST_APP_STRING + 11)
#define XR_CantRemoveIfKernel		(OO_FIRST_APP_STRING + 12)
#define XR_LinkLog					(OO_FIRST_APP_STRING + 13)

#define LAST_USED_ER_STRING     XR_LinkLog			//KEEP THIS UP TO DATE!!
#define FIRST_USED_ER_STRING	XR_ADDRESS
#define NUM_ER_USED			   (LAST_USED_ER_STRING - FIRST_USED_ER_STRING + 1)

enum { 	ER_Address=XR_ADDRESS, ER_Illegal, ER_Divide, ER_CHK, ER_TrapV, ER_Priv, 
		ER_TraceInt, ER_SpIntr, ER_InvalidHandle, ER_InvalidHistItem, 
		ER_ResetMagicFailedInstall, ER_ResetMagicFailedRemove, ER_CantRemoveIfKernel,
		ER_LinkLog
	};
								
//Application XR strings
#define XR_ShortAppName 	(LAST_USED_ER_STRING + 1)
#define XR_LongAppName 		(LAST_USED_ER_STRING + 2)
#define XR_AppVersion 		(LAST_USED_ER_STRING + 3)
#define XR_Protection		(LAST_USED_ER_STRING + 4)
#define XR_ProtectionE		(LAST_USED_ER_STRING + 5)		
#define XR_On				(LAST_USED_ER_STRING + 6)
#define XR_Off				(LAST_USED_ER_STRING + 7)
#define XR_PasteSpecial		(LAST_USED_ER_STRING + 8)
#define XR_About_Me			(LAST_USED_ER_STRING + 9)  			
#define XR_MemoryInfo		(LAST_USED_ER_STRING + 10)		
#define XR_MemoryStatus		(LAST_USED_ER_STRING + 11)		
#define XR_RAMStress		(LAST_USED_ER_STRING + 12)				
#define XR_RAMStressE		(LAST_USED_ER_STRING + 13)
#define XR_Status           (LAST_USED_ER_STRING + 14)
#define XR_Bytes	        (LAST_USED_ER_STRING + 15)
#define XR_Enabled          (LAST_USED_ER_STRING + 16)
#define XR_Disabled         (LAST_USED_ER_STRING + 17)
#define XR_UseXbytes        (LAST_USED_ER_STRING + 18)
#define XR_LeaveBytesFree   (LAST_USED_ER_STRING + 19)
#define XR_HexEditor		(LAST_USED_ER_STRING + 20)
#define XR_HeapCorrupted	(LAST_USED_ER_STRING + 21)
#define XR_LowMemFmtStr		(LAST_USED_ER_STRING + 22)
#define XR_ResetMagic		(LAST_USED_ER_STRING + 23)
#define XR_HeapVaild		(LAST_USED_ER_STRING + 24)
#define XR_HeapInvalid		(LAST_USED_ER_STRING + 25)
#define XR_SetDefaults		(LAST_USED_ER_STRING + 26)
#define XR_SystemInfo		(LAST_USED_ER_STRING + 27)
#define XR_Refresh			(LAST_USED_ER_STRING + 28)
#define XR_UnknownKernel	(LAST_USED_ER_STRING + 29)
#define XR_NoKernelFound	(LAST_USED_ER_STRING + 30)
#define XR_h220xtsr			(LAST_USED_ER_STRING + 31)
#define XR_HW2Patch			(LAST_USED_ER_STRING + 32)
#define XR_NoHwPatchFound 	(LAST_USED_ER_STRING + 33)
#define XR_NotApplicable	(LAST_USED_ER_STRING + 34)
#define XR_SysInfoStr		(LAST_USED_ER_STRING + 35)
#define XR_LeakWatchStr		(LAST_USED_ER_STRING + 36)
#define XR_LeakWatch		(LAST_USED_ER_STRING + 37)
#define XR_LeakWatchE		(LAST_USED_ER_STRING + 38)
#define XR_InstallHook		(LAST_USED_ER_STRING + 39)
#define XR_RemoveHook		(LAST_USED_ER_STRING + 40)
#define XR_Action			(LAST_USED_ER_STRING + 41)
#define XR_Application		(LAST_USED_ER_STRING + 42)
#define XR_AllApps			(LAST_USED_ER_STRING + 43)
#define XR_JumpTo			(LAST_USED_ER_STRING + 44)
#define XR_Handle			(LAST_USED_ER_STRING + 45)
#define XR_Address			(LAST_USED_ER_STRING + 46)
#define XR_ValueC			(LAST_USED_ER_STRING + 47)
#define XR_LeakPackInfo		(LAST_USED_ER_STRING + 48)
#define XR_LeakWatchInstall	(LAST_USED_ER_STRING + 49)
#define XR_LeakWatchRemove	(LAST_USED_ER_STRING + 50)		
#define XR_Byte				(LAST_USED_ER_STRING + 51)
#define XR_Word				(LAST_USED_ER_STRING + 52)
#define XR_Long				(LAST_USED_ER_STRING + 53)
#define XR_PasteSpecialO	(LAST_USED_ER_STRING + 54)
#define XR_PasteTruncated	(LAST_USED_ER_STRING + 55)
#define XR_KernelWarning	(LAST_USED_ER_STRING + 56)
#define XR_SuccessfulBackup	(LAST_USED_ER_STRING + 57)
#define XR_AMSInfo			(LAST_USED_ER_STRING + 58)
#define XR_BasecodePB		(LAST_USED_ER_STRING + 59)
#define XR_BasecodePBE		(LAST_USED_ER_STRING + 60)
#define XR_HardwarePB		(LAST_USED_ER_STRING + 61)
#define XR_HardwarePBE		(LAST_USED_ER_STRING + 62)
#define XR_HardwarePBStr	(LAST_USED_ER_STRING + 63)
#define XR_HWPBTooLong		(LAST_USED_ER_STRING + 64)
#define XR_Variable			(LAST_USED_ER_STRING + 65)
#define XR_JumpToE			(LAST_USED_ER_STRING + 66)
#define XR_EditE			(LAST_USED_ER_STRING + 67)
#define XR_JUMPTO			(LAST_USED_ER_STRING + 68)
#define XR_Data				(LAST_USED_ER_STRING + 69)
#define XR_SymEntry			(LAST_USED_ER_STRING + 70)
#define XR_Find				(LAST_USED_ER_STRING + 71)
#define XR_Foreword			(LAST_USED_ER_STRING + 72)
#define XR_Backward			(LAST_USED_ER_STRING + 73)
#define XR_CantDelete_1		(LAST_USED_ER_STRING + 74)
#define XR_SearchingEstr	(LAST_USED_ER_STRING + 75)
#define XR_FindNextO		(LAST_USED_ER_STRING + 76)
#define XR_HexEditorWidth	(LAST_USED_ER_STRING + 77)
#define XR_TwoBytes			(LAST_USED_ER_STRING + 78)
#define XR_FourBytes		(LAST_USED_ER_STRING + 79)
#define XR_SixBytes			(LAST_USED_ER_STRING + 80)
#define XR_EightBytes		(LAST_USED_ER_STRING + 81)
#define XR_TenBytes			(LAST_USED_ER_STRING + 82)
#define XR_HeapWalk			(LAST_USED_ER_STRING + 83)
#define XR_ResizeHandleE	(LAST_USED_ER_STRING + 84)
#define XR_NewSize			(LAST_USED_ER_STRING + 85)
#define XR_RESIZEHANDLE		(LAST_USED_ER_STRING + 86)
#define XR_NewValue			(LAST_USED_ER_STRING + 87)
#define XR_Direction		(LAST_USED_ER_STRING + 88)
#define XR_BOTTOM_ESTACK	(LAST_USED_ER_STRING + 89)
#define XR_CU_CURSOR_STATE	(LAST_USED_ER_STRING + 90)
#define XR_ERRNO			(LAST_USED_ER_STRING + 91)
#define XR_ESTACK_MAX_INDEX	(LAST_USED_ER_STRING + 92)
#define XR_EV_APPA			(LAST_USED_ER_STRING + 93)
#define XR_EV_APPB			(LAST_USED_ER_STRING + 94)
#define XR_EV_ERROR_CODE	(LAST_USED_ER_STRING + 95)
#define XR_EV_FLAGS			(LAST_USED_ER_STRING + 96)
#define XR_EV_RUNNINGAPP	(LAST_USED_ER_STRING + 97)
#define XR_FLASHMEMORYEND	(LAST_USED_ER_STRING + 98)
#define XR_MO_OPTION		(LAST_USED_ER_STRING + 99)
#define XR_NG_CONTROL		(LAST_USED_ER_STRING + 100)
#define XR_OO_FIRST_ACB		(LAST_USED_ER_STRING + 101)
#define XR_OO_SUPERFRAME	(LAST_USED_ER_STRING + 102)
#define XR_OSFASTARROWS		(LAST_USED_ER_STRING + 103)
#define XR_OSMODKEYSTATUS	(LAST_USED_ER_STRING + 104)
#define XR_ST_FLAGS			(LAST_USED_ER_STRING + 105)
#define XR_TOP_ESTACK		(LAST_USED_ER_STRING + 106)
#define XR_HistoryItem		(LAST_USED_ER_STRING + 107)
#define XR_HS_getAns		(LAST_USED_ER_STRING + 108)
#define XR_HS_getEntry		(LAST_USED_ER_STRING + 109)
#define XR_JumpAMSGlobalVar	(LAST_USED_ER_STRING + 110)
#define XR_JumpTable		(LAST_USED_ER_STRING + 111)
#define XR_FindPreviousO	(LAST_USED_ER_STRING + 112)
#define XR_Jump				(LAST_USED_ER_STRING + 113)
#define XR_FindO			(LAST_USED_ER_STRING + 114)
#define XR_CopySpecialO		(LAST_USED_ER_STRING + 115)
#define XR_COPYSPECIAL		(LAST_USED_ER_STRING + 116)
#define XR_H_WALK_STATUS	(LAST_USED_ER_STRING + 117)
#define XR_H_WALK_DUMP		(LAST_USED_ER_STRING + 118)
#define XR_H_WALK_SYM		(LAST_USED_ER_STRING + 119)
#define XR_CantDelete_2		(LAST_USED_ER_STRING + 120)
#define XR_AppInfoE			(LAST_USED_ER_STRING + 121)
#define XR_AppACB			(LAST_USED_ER_STRING + 122)
#define XR_AppHDR			(LAST_USED_ER_STRING + 123)
#define XR_BUILTIN			(LAST_USED_ER_STRING + 124)
#define XR_INSTALLED		(LAST_USED_ER_STRING + 125)
#define XR_LOCALIZER		(LAST_USED_ER_STRING + 126)
#define XR_LOCK				(LAST_USED_ER_STRING + 127)
#define XR_JT_VERSION		(LAST_USED_ER_STRING + 128)
#define XR_SELECTED			(LAST_USED_ER_STRING + 129)
#define XR_COLLAPSE			(LAST_USED_ER_STRING + 130)
#define XR_BG				(LAST_USED_ER_STRING + 131)
#define XR_COMPRESS			(LAST_USED_ER_STRING + 132)
#define XR_DELETE			(LAST_USED_ER_STRING + 133)
#define XR_APP_ACB			(LAST_USED_ER_STRING + 134)
#define XR_APP_HDR			(LAST_USED_ER_STRING + 135)
#define XR_nAppHeaderFlagsn	(LAST_USED_ER_STRING + 136)
#define XR_Localizer		(LAST_USED_ER_STRING + 137)
#define XR_nAppFlags		(LAST_USED_ER_STRING + 138)
#define XR_Interactive		(LAST_USED_ER_STRING + 139)
#define XR_Con				(LAST_USED_ER_STRING + 140)
#define XR_AccessSysVars	(LAST_USED_ER_STRING + 141)
#define XR_Background		(LAST_USED_ER_STRING + 142)
#define XR_ACBFlags			(LAST_USED_ER_STRING + 143)
#define XR_AppInfo			(LAST_USED_ER_STRING + 144)
#define XR_Flags			(LAST_USED_ER_STRING + 145)
#define XR_SelectApp		(LAST_USED_ER_STRING + 146)
#define XR_JumpCommonMem	(LAST_USED_ER_STRING + 147)
#define XR_LCD_MEM			(LAST_USED_ER_STRING + 148)
#define XR_ROM_CALL			(LAST_USED_ER_STRING + 149)
#define XR_HW1_Ports		(LAST_USED_ER_STRING + 150)
#define XR_HW2_Ports		(LAST_USED_ER_STRING + 151)
#define XR_KEY_QUEUE		(LAST_USED_ER_STRING + 152)
#define XR_EVector			(LAST_USED_ER_STRING + 153)
#define XR_AutoInt			(LAST_USED_ER_STRING + 154)
#define XR_Trap				(LAST_USED_ER_STRING + 155)
#define XR_WantDerefPointerQ (LAST_USED_ER_STRING + 156)
#define XR_OSContrast		(LAST_USED_ER_STRING + 157)
#define XR_WantDerefHandleQ (LAST_USED_ER_STRING + 158)
#define XR_RelAddr			(LAST_USED_ER_STRING + 159)
#define XR_AND				(LAST_USED_ER_STRING + 160)
#define XR_OR				(LAST_USED_ER_STRING + 161)
#define XR_XOR				(LAST_USED_ER_STRING + 162)
#define XR_Disassembly		(LAST_USED_ER_STRING + 163)
#define XR_LinkPortLogger	(LAST_USED_ER_STRING + 164)
#define XR_LinkLogMessage	(LAST_USED_ER_STRING + 165)
#define XR_BytesReceived	(LAST_USED_ER_STRING + 166)
#define XR_CrashLinkDump	(LAST_USED_ER_STRING + 167)
#define XR_JumpToDisassembly (LAST_USED_ER_STRING + 168)
#define XR_DumpUSP			(LAST_USED_ER_STRING + 169)
#define XR_DumpSSP			(LAST_USED_ER_STRING + 170)
#define XR_DasmToolsE		(LAST_USED_ER_STRING + 171)
#define XR_movem			(LAST_USED_ER_STRING + 172)
#define XR_PreDecrement		(LAST_USED_ER_STRING + 173)
#define XR_PostIncrement	(LAST_USED_ER_STRING + 174)
#define XR_Bookmarks		(LAST_USED_ER_STRING + 175)
#define XR_JumpBookMark1	(LAST_USED_ER_STRING + 176)
#define XR_JumpBookMark2	(LAST_USED_ER_STRING + 177)
#define XR_SetBookMark1		(LAST_USED_ER_STRING + 178)
#define XR_SetBookMark2		(LAST_USED_ER_STRING + 179)
#define XR_HighAddr			(LAST_USED_ER_STRING + 180)
#define XR_NotFound			(LAST_USED_ER_STRING + 181)
#define XR_RomCallToStr		(LAST_USED_ER_STRING + 182)
#define XR_DasmTools		(LAST_USED_ER_STRING + 183)
#define XR_NoDatabase		(LAST_USED_ER_STRING + 184)
#define XR_Tool				(LAST_USED_ER_STRING + 185)
#define XR_DASM_Buffering	(LAST_USED_ER_STRING + 186)
#define XR_VerboseDasm		(LAST_USED_ER_STRING + 187)
#define XR_HW3Patch			(LAST_USED_ER_STRING + 188)

   
#define LAST_USED_XR_STRING		XR_HW3Patch		//KEEP THIS UP TO DATE!!
#define FIRST_USED_XR_STRING 	XR_ShortAppName                          	
#define NUM_XR_STRINGS (LAST_USED_XR_STRING - FIRST_USED_XR_STRING + 1)	//Used to keep frame up-to-date

//Application Defined TI-Basic Extensions
//Keep in ABC order
enum
{
    EXT_BCLR,
    EXT_BSET,
    EXT_BTST,
    EXT_HEAPDEREF,
    EXT_LOWMEM,
    EXT_PEEKB,
    EXT_PEEKL,
    EXT_PEEKW,
    EXT_POKEB,
    EXT_POKEL,
    EXT_POKEW,
    EXT_HEAPSHUFFLE,
	NUM_EXTENSIONS
};

#define HELP_OFFSET NUM_EXTENSIONS
#define FIRST_EXT_HELP_STR (XR_extextHelpbclr)

//App Extensions			
#define XR_extbclr				(LAST_USED_XR_STRING + 1 + EXT_BCLR)
#define XR_extbset				(LAST_USED_XR_STRING + 1 + EXT_BSET)
#define XR_extbtst				(LAST_USED_XR_STRING + 1 + EXT_BTST)
#define XR_extHeapDeref			(LAST_USED_XR_STRING + 1 + EXT_HEAPDEREF)
#define XR_extLowMem			(LAST_USED_XR_STRING + 1 + EXT_LOWMEM)
#define XR_extPeekB				(LAST_USED_XR_STRING + 1 + EXT_PEEKB)
#define XR_extPeekL				(LAST_USED_XR_STRING + 1 + EXT_PEEKL)
#define XR_extPeekW				(LAST_USED_XR_STRING + 1 + EXT_PEEKW)
#define XR_extPokeB				(LAST_USED_XR_STRING + 1 + EXT_POKEB)
#define XR_extPokeL				(LAST_USED_XR_STRING + 1 + EXT_POKEL)
#define XR_extPokeW				(LAST_USED_XR_STRING + 1 + EXT_POKEW)
#define XR_extHeapShuffle		(LAST_USED_XR_STRING + 1 + EXT_HEAPSHUFFLE)

//App Extension Help Strings
#define XR_extHelpbclr			(LAST_USED_XR_STRING + 1 + HELP_OFFSET + EXT_BCLR)
#define XR_extHelpbset			(LAST_USED_XR_STRING + 1 + HELP_OFFSET + EXT_BSET)
#define XR_extHelpbtst			(LAST_USED_XR_STRING + 1 + HELP_OFFSET + EXT_BTST)
#define XR_extHelpHeapDeref		(LAST_USED_XR_STRING + 1 + HELP_OFFSET + EXT_HEAPDEREF)
#define XR_extHelpLowMem		(LAST_USED_XR_STRING + 1 + HELP_OFFSET + EXT_LOWMEM)
#define XR_extHelpPeekB			(LAST_USED_XR_STRING + 1 + HELP_OFFSET + EXT_PEEKB)
#define XR_extHelpPeekL			(LAST_USED_XR_STRING + 1 + HELP_OFFSET + EXT_PEEKL)
#define XR_extHelpPeekW			(LAST_USED_XR_STRING + 1 + HELP_OFFSET + EXT_PEEKW)
#define XR_extHelpPokeB			(LAST_USED_XR_STRING + 1 + HELP_OFFSET + EXT_POKEB)
#define XR_extHelpPokeL			(LAST_USED_XR_STRING + 1 + HELP_OFFSET + EXT_POKEL)
#define XR_extHelpPokeW			(LAST_USED_XR_STRING + 1 + HELP_OFFSET + EXT_POKEW)
#define XR_extHelpHeapShuffle	(LAST_USED_XR_STRING + 1 + HELP_OFFSET + EXT_HEAPSHUFFLE)

//Extended Extension Help Strings
#define XR_extextHelpbclr			(LAST_USED_XR_STRING + 1 + (2 * HELP_OFFSET) + EXT_BCLR)
#define XR_extextHelpbset			(LAST_USED_XR_STRING + 1 + (2 * HELP_OFFSET) + EXT_BSET)
#define XR_extextHelpbtst			(LAST_USED_XR_STRING + 1 + (2 * HELP_OFFSET) + EXT_BTST)
#define XR_extextHelpHeapDeref		(LAST_USED_XR_STRING + 1 + (2 * HELP_OFFSET) + EXT_HEAPDEREF)
#define XR_extextHelpLowMem			(LAST_USED_XR_STRING + 1 + (2 * HELP_OFFSET) + EXT_LOWMEM)
#define XR_extextHelpPeekB			(LAST_USED_XR_STRING + 1 + (2 * HELP_OFFSET) + EXT_PEEKB)
#define XR_extextHelpPeekL			(LAST_USED_XR_STRING + 1 + (2 * HELP_OFFSET) + EXT_PEEKL)
#define XR_extextHelpPeekW			(LAST_USED_XR_STRING + 1 + (2 * HELP_OFFSET) + EXT_PEEKW)
#define XR_extextHelpPokeB			(LAST_USED_XR_STRING + 1 + (2 * HELP_OFFSET) + EXT_POKEB)
#define XR_extextHelpPokeL			(LAST_USED_XR_STRING + 1 + (2 * HELP_OFFSET) + EXT_POKEL)
#define XR_extextHelpPokeW			(LAST_USED_XR_STRING + 1 + (2 * HELP_OFFSET) + EXT_POKEW)
#define XR_extextHelpHeapShuffle	(LAST_USED_XR_STRING + 1 + (2 * HELP_OFFSET) + EXT_HEAPSHUFFLE)

#endif
 