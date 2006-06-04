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
// $Id$

#include "ram.h"
#include "KFLASH.h"
#include "tiams.h"

TOOLBOX AppMenu, RC_NO_IDS, 0, 240
{
   //Command Post Menu-Icon
   [[16, 20,
   	0x01,0xfe,0x00,0x07,0xff,0x80,0x3c,0x09,0xc0,0x69,
	0x50,0xe0,0xe0,0x27,0x60,0xc5,0x1f,0x30,0xd0,0x77,
	0x70,0xe5,0xec,0x30,0xc8,0xf9,0x70,0xc2,0xf0,0x30,
	0xe9,0x04,0xe0,0x72,0xa1,0xe0,0x69,0x0b,0xc0,0x3f,
	0xff,0x80,0x3f,0xfc,0x00,0x0e,0xee,0x00]]
	{
		XR_CopySpecialO,		CM_COPY
		XR_PasteSpecialO,		CM_PASTE	
	    XR_SetDefaults,			ACM_Defaults
	    XR_FormatO,				CM_FORMAT
	    XR_AboutE,				CM_ABOUT
   	}
	
    XR_HexEditor
    {
		XR_Jump
    	{
    		XR_JumpToE,			ACM_Hex_JumpTo
    		XR_JumpAMSGlobalVar,ACM_Hex_AMS_GlobalVars
    		XR_JumpCommonMem,	ACM_Hex_JumpCommon
    		XR_Variable,		ACM_Hex_JumpVar
    	}
    	XR_Find,	ACM_UNUSED_FIND_INDEX
    	{
    		XR_FindO,			ACM_Hex_Find
    		XR_FindNextO,		ACM_Hex_FindNext
    		XR_FindPreviousO,	ACM_Hex_FindPrevious
    	}
    	
    	XR_Bookmarks,		ACM_UNUSED_BOOKMARK_INDEX
    	{
    		XR_JumpBookMark1,	ACM_Hex_JumpBookMark1
    		XR_JumpBookMark2,	ACM_Hex_JumpBookMark2
    		XR_SetBookMark1,	ACM_Hex_SetBookMark1
    		XR_SetBookMark2,	ACM_Hex_SetBookMark2
    		
    	}
    	
    	XR_EditE,			ACM_Hex_Edit
    	XR_ResizeHandleE,	ACM_Hex_ResizeHandle
    	XR_Refresh,			ACM_Hex_Refresh
		XR_Disassembly,		ACM_DisASMViewToggle
    }
	
    XR_Tools
	{
		XR_RAMStressE,			ACM_RAMStressDialog
		XR_LeakWatchE,			ACM_LeakWatch
		XR_AppInfoE,			ACM_AppInfo
		XR_LinkPortLogger,		ACM_LinkPortLogger
		XR_DasmToolsE,			ACM_DisassemblyTools
		XR_HeapWalk
		{
			XR_H_WALK_STATUS,	ACM_H_WALK_STATUS
			XR_H_WALK_DUMP,		ACM_H_WALK_DUMP
			XR_H_WALK_SYM,		ACM_H_WALK_SYM
		}
	}
	
	XR_vtSystem
	{
		XR_AMSInfo,				ACM_AMS_Info
		XR_SystemInfo,			ACM_SysInfo
		XR_MemoryStatus,		ACM_RAMStats
		XR_BasecodePBE,			ACM_BasecodePB
		XR_HardwarePBE,			ACM_HW_PB
	}
	
	XR_Refresh,		ACM_Hex_Refresh	  					//don't forget about the push_key in the formats dialog if this gets moved...
}

DIALOG dlgAppInfoSelect, 0, 0, cbAppInfoSelect
{	
	TEXT,		{DF_OWNER_DRAW,0,0}
	DYNPOPUP,	{DF_SCROLLABLE,		12,		30},		XR_Application,		pupAppInfoApps, 	0 //last num is index
	TEXT,		{DF_SCROLLABLE,		12,		19+(5*10)},""
	HEADER,		{0, 				0,	 	0}, 			XR_AppInfo, 		PDB_OK, PDB_CANCEL
	MENU,		{0,5,11},	tbAppInfo
	SCROLL_REGION, {0,10,30},50,100,	1,2,1,2,0
}

TOOLBOX tbAppInfo, RC_NO_IDS, 0, 140
{
	XR_SelectApp, 1
	XR_AppACB, 2
	XR_AppHDR, 3
	XR_Flags,4
}

DIALOG dlgJumpCommonMem, 0, 0, cbJumpCommonMem
{
	POPUP,		{DF_TAB_SPACES,   12, 14+(0*10)},		XR_Var,			pupJumpToCommonMem,			0 //last num is index
	EDIT,		{DF_TAB_SPACES, 	12, 14+(1*10)},		XR_Value,		0, 20, 12	//offset in buff, buff len, display character width
	HEADER,		{0, 				0,	0}, 			XR_JumpTo, 		PDB_OK, PDB_CANCEL
	XFLAGS,		{0,					0,	0}, 			XF_NO_ALPHA_LOCK | XF_ALLOW_VARLINK, 0, 0, 0
}

POPUP pupJumpToCommonMem, 0, 0 {	// flags, selected index
   XR_EVector,		JVAR_EVECTOR
   XR_AutoInt,		JVAR_AUTO_INT
   XR_Trap,			JVAR_TRAP   
   XR_LCD_MEM,		JVAR_LCD_MEM
   XR_OSContrast,	JVAR_OS_CONTRAST
   XR_HW1_Ports,	JVAR_HW1_PORTS
   XR_HW2_Ports,	JVAR_HW2_PORTS
   XR_KEY_QUEUE,	JVAR_KEY_QUEUE
   XR_ROM_CALL,		JVAR_ROM_CALL
}

DIALOG dlgJumpAMSVar, 0, 0, cbJumpAMSVar
{
	POPUP,		{DF_TAB_ELLIPSES,   12, 14+(0*10)},		XR_Var,					pupJumpToAMSVar,			0 //last num is index
	EDIT,		{DF_TAB_ELLIPSES, 	12, 14+(1*10)},		XR_HistoryItem,		0, 20, 12	//offset in buff, buff len, display character width
	HEADER,		{0, 				0,	0}, 			XR_JumpTo, 		PDB_OK, PDB_CANCEL
	XFLAGS,		{0,					0,	0}, 			XF_NO_ALPHA_LOCK | XF_ALLOW_VARLINK, 0, 0, 0
}

POPUP pupJumpToAMSVar, 0, 0 {	// flags, selected index
   XR_BOTTOM_ESTACK,	JVAR_BOTTOM_ESTACK
   XR_CU_CURSOR_STATE,	JVAR_CU_CURSOR_STATE
   XR_ERRNO,			JVAR_ERRNO
   XR_ESTACK_MAX_INDEX,	JVAR_ESTACK_MAX_INDEX
   XR_EV_APPA,			JVAR_EV_APPA
   XR_EV_APPB,			JVAR_EV_APPB
   XR_EV_ERROR_CODE,	JVAR_EV_ERROR_CODE
   XR_EV_FLAGS,			JVAR_EV_FLAGS
   XR_EV_RUNNINGAPP,	JVAR_EV_RUNNINGAPP
   XR_FLASHMEMORYEND,	JVAR_FLASHMEMORYEND
   XR_HS_getAns,		JVAR_HS_GETANS
   XR_HS_getEntry,		JVAR_HS_GETENTRY
   XR_JumpTable,		JVAR_JUMPTABLE
   XR_MO_OPTION,		JVAR_MO_OPTION
   XR_NG_CONTROL,		JVAR_NG_CONTROL
   XR_OO_FIRST_ACB,		JVAR_OO_FIRST_ACB
   XR_OO_SUPERFRAME,	JVAR_OO_SUPERFRAME
   XR_OSFASTARROWS,		JVAR_OSFASTARROWS
   XR_OSMODKEYSTATUS,	JVAR_OSMODKEYSTATUS
   XR_ST_FLAGS,			JVAR_ST_FLAGS
   XR_TOP_ESTACK,		JVAR_TOP_ESTACK
}

DIALOG dlgResizeHandle, 0, 0, NoCallBack
{
	EDIT,		{DF_TAB_SPACES, 	12, 14+(0*10)},		XR_Handle,								0, 20, 12	//offset in buff, buff len, display character width
	EDIT,		{DF_TAB_SPACES, 	12, 14+(1*10)},		XR_NewSize,								22, 20, 12	//offset in buff, buff len, display character width
	HEADER,		{0, 				0,	0}, 			XR_RESIZEHANDLE, 		PDB_OK, PDB_CANCEL
	XFLAGS,		{0,					0,	0}, 			XF_NO_ALPHA_LOCK | XF_ALLOW_VARLINK, 0, 0, 0
}

DIALOG dlgFormat, 0, 0, cbFormatDialog
{
	POPUP,		{DF_TAB_ELLIPSES,   	12, 14+(0*10)},		XR_HexEditorWidth,	pupHexBytesWide,	0	//last num is index
	POPUP,		{DF_TAB_ELLIPSES,		12,	14+(1*10)},		XR_Protection,		pupOnOff,			1	//last num is index
	POPUP,		{DF_TAB_ELLIPSES,		12,	14+(2*10)},		XR_VerboseDasm,		pupOnOff,			3	//last num is index
	POPUP,		{DF_TAB_ELLIPSES,		12,	14+(3*10)},		XR_ResetMagic,		pupOnOff,			2	//last num is index
	HEADER,		{0, 					0,	0}, 			XR_FORMATS, 		PDB_OK, PDB_CANCEL
}

POPUP pupOnOff, 0, 0 {
	XR_On,		PUP_ON=2	//subtract one, or let be to get true
	XR_Off,		PUP_OFF=1	//subtract one to get false
}


POPUP pupHexBytesWide, 0, 0 {
	XR_TwoBytes,	TWO_WIDE=2
	XR_FourBytes,	FOUR_WIDE=4
	XR_SixBytes,	SIX_WIDE=6
	XR_EightBytes,	EIGHT_WIDE=8
	XR_TenBytes,	TEN_WIDE=10
}

DIALOG dlgFind, 0, 0, NoCallBack
{
	POPUP,		{DF_TAB_ELLIPSES,   12, 14+(0*10)},		XR_Find,		pupHexEditSize,		0 //last num is index
	POPUP,		{DF_TAB_ELLIPSES,	12, 12+(1*10)},		XR_Direction,	pupDirection,		1 //last num is index
	EDIT,		{DF_TAB_ELLIPSES, 	12, 14+(2*10)},		XR_Value,								HEDIT_BUFF_SIZE*0, HEDIT_BUFF_SIZE-1, 12	//offset in buff, buff len, display character width
	EDIT,		{DF_TAB_ELLIPSES, 	12, 14+(3*10)},		XR_HighAddr,							HEDIT_BUFF_SIZE*1, HEDIT_BUFF_SIZE-1, 12	//offset in buff, buff len, display character width
	HEADER,		{0, 				0,	0}, 			XR_FIND, 		PDB_OK, PDB_CANCEL
	XFLAGS,		{0,					0,	0}, 			XF_NO_ALPHA_LOCK | XF_ALLOW_VARLINK, 0, 0, 0
}

POPUP pupDirection, 0, 0 {
	XR_Foreword,	DIR_FOREWARD
	XR_Backward,	DIR_BACKWARD    
}

DIALOG dlgHexEditCur, 0, 0, cbHexEdit
{
	POPUP,		{DF_TAB_ELLIPSES,   12, 14+(0*10)},		XR_Edit,		pupHexEditSize,			0 //last num is index
	POPUP,		{DF_TAB_ELLIPSES,   12, 14+(1*10)},		"Mask",			pupHexEditMask,			1 //last num is index
	EDIT,		{DF_TAB_ELLIPSES, 	12, 14+(2*10)},		XR_NewValue,							0, HEDIT_BUFF_SIZE-1, 12	//offset in buff, buff len, display character width
	DYNHEADER,	{0, 				0,	0},  			PDB_OK, PDB_CANCEL
	XFLAGS,		{0,					0,	0}, 			XF_NO_ALPHA_LOCK | XF_ALLOW_VARLINK, 0, 0, 0
}

POPUP pupHexEditSize, 0, 0 {
   XR_Byte,		EDIT_CHAR
   XR_Word,		EDIT_SHORT
   XR_Long,		EDIT_LONG
   XR_String,	EDIT_STRING
}

POPUP pupHexEditMask, 0, 0 {
   XR_NONE,		MASK_NONE
   XR_AND,		MASK_AND
   XR_OR,		MASK_OR
   XR_XOR,		MASK_XOR
}

DIALOG dlgJumpTo, 0, 0, NoCallBack
{
	POPUP,		{DF_TAB_SPACES,   12, 14+(0*10)},		XR_TypeC,		pupJumpToWhat,			0 //last num is index
	EDIT,		{DF_TAB_SPACES, 	12, 14+(1*10)},		XR_ValueC,								0, 20, 12	//offset in buff, buff len, display character width
	HEADER,		{0, 				0,	0}, 			XR_JumpTo, 		PDB_OK, PDB_CANCEL
	XFLAGS,		{0,					0,	0}, 			XF_NO_ALPHA_LOCK | XF_ALLOW_VARLINK, 0, 0, 0
}

POPUP pupJumpToWhat, MF_NO_NUMS, 0 {	// flags, selected index
   XR_Address,	JUMP_ADDRESS
   XR_RelAddr,	JUMP_REL_ADDR
   XR_Handle,	JUMP_HANDLE
}

DIALOG dlgLeakWatch, 0, 0, cbLeakWatch
{	
	POPUP,		{DF_TAB_SPACES,   12, 	14+(0*10)},		XR_Action,			pupLeakWatch,		0 //last num is index
	DYNPOPUP,	{0,					12,		14+(1*10)},		XR_Application,		pupLeakWatchApps, 	1 //last num is index
	HEADER,		{0, 				0,	 	0}, 			XR_LeakWatch, 		PDB_OK, PDB_CANCEL
}

POPUP pupLeakWatch, 0, 0 {	//numbering these two for consistancy with the dynamic popup
   XR_InstallHook,	LEAK_INSTALL
   XR_RemoveHook,	LEAK_UNINSTALL
}
	 
DIALOG dlgStressTest, 0, 0, cbStressTest
{	
	POPUP,		{DF_TAB_SPACES,   12, 14+(0*10)},		XR_Status,				pupStressRelief,	0 //last num is index
	POPUP,		{DF_TAB_SPACES,	12,	14+(1*10)},		XR_Mode, 				pupAllocateMode, 	1 //last num is index
	EDIT,		{DF_TAB_SPACES, 	12, 14+(2*10)},		XR_Bytes,									0, 20, 12
	HEADER,		{0, 				0,	0}, 			XR_RAMStress, 			PDB_OK, PDB_CANCEL
	XFLAGS,		{0,					0,	0}, 			XF_NO_ALPHA_LOCK | XF_ALLOW_VARLINK, 0, 0, 0
}

POPUP pupStressRelief, MF_NO_NUMS, 0 {
   XR_Disabled, STRESS_DISABLE
   XR_Enabled, STRESS_ENABLE
}

POPUP pupAllocateMode, MF_NO_NUMS, 0 {
	XR_LeaveBytesFree,	STRESS_MODE_FILL
	XR_UseXbytes,		STRESS_MODE_USE			
}

POPUP pupEditWhat, 0, 0, XR_JUMPTO {
	XR_Data,		JUMP_TO_DATA
	XR_SymEntry,	JUMP_TO_SYM_ENTRY
}

POPUP pupCopySpecialEven, 0, 0, XR_COPYSPECIAL {
   XR_Byte,		COPY_CHAR
   XR_Word,		COPY_SHORT
   XR_Long,		COPY_LONG
   XR_String,	COPY_STRING
}

POPUP pupCopySpecialOdd, 0, 0, XR_COPYSPECIAL {
   XR_Byte,		COPY_CHAR2=1			//this must equal COPY_CHAR
   XR_String,	COPY_STRING2=4			//this must equal COPY_STRING
}

DIALOG dlgMovemDecode, 0, 0, NoCallBack
{
	POPUP,		{DF_TAB_SPACES,   12, 14+(0*10)},		XR_Tool,		pupTools,			0 //last num is index
	EDIT,		{DF_TAB_SPACES, 	12, 14+(1*10)},		XR_Value,		0, 20, 15	//offset in buff, buff len, display character width
	HEADER,		{0, 				0,	0}, 			XR_DasmTools, 		PDB_OK, PDB_CANCEL
	XFLAGS,		{0,					0,	0}, 			XF_NO_ALPHA_LOCK | XF_ALLOW_VARLINK, 0, 0, 0
}

POPUP pupTools, MF_NO_NUMS, 0 {
	XR_RomCallToStr,		DECODE_RomCallToStr=1
	XR_PreDecrement,		DECODE_PreDecrement=2
	XR_PostIncrement,		DECODE_PostIncrement=3
}
