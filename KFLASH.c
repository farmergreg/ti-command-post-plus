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
// $Id: KFLASH.c 21 2004-08-06 21:30:03Z dietsche $

#include <tiams.h>
#include "undoc.h"
#include "crash.h"
#include "KFLASHr1.h"
#include "KFLASH.h"
#include "AppInfo.h"
#include "dasm_driver.h"
#include "dasm.h"
 
////////////////////////////////////////////////////
//static function prototypes                    ///
//////////////////////////////////////////////////
static char* About(void);
static void ShowAboutScr(void);
static void appExtHelp(AppID self, USHORT strnum);
static void Event_Handler(pFrame self, PEvent e);
static BOOL CanDelete(AppID self);
static BOOL CanMove(AppID self);
static SINT GetAppErrorContext(void);
static void SetDefaults(void);
static void ShowSysInfo(void);
static void ShowAMSInfo(void);
static void ShowBasecode_PB(void);
static void ShowHW_PB(void);
static void DoFormatDialog(void);
static void InstallResetMagic(void);
static void RemoveResetMagic(void);
static BOOL CheckResetMagicInstalled(void);
static void EnforceResetMagicRules(void);
static void HideResetMagicVar(BOOL hidden);
static void LinkPortLogger(void);
static void DisassemblyToolsDialog(void);
static ULONG * InitializeRomCallAddrToStrDB(void);
static void disassemble_one_ext_wrapper(unsigned short *pc, DASM_DAT *buff);
static void OpenAllDatabases(void);
static void CloseAllDatabases(void);
static BOOL HW3PatchInstalled(void);
static void UseTurboKeys(BOOL on);

//////////////////////////////////////////////////////
//static data                                     ///
////////////////////////////////////////////////////
static const short AppIcon[];
static const short DSIcon[];

//////////////////////////////////////////////////

#define FRAME_SIZE (13 + NUM_XR_STRINGS + NUM_OO_USED + NUM_ER_USED + (NUM_EXTENSIONS*3))

APP_EXTENSION const appExtensions[]={
/*		func name #, 										help string # 						func index */
	{OO_FIRST_APP_STRING + XR_extbclr,			OO_FIRST_APP_STRING + XR_extHelpbclr,			EXT_BCLR},
	{OO_FIRST_APP_STRING + XR_extbset,			OO_FIRST_APP_STRING + XR_extHelpbset,			EXT_BSET},
	{OO_FIRST_APP_STRING + XR_extbtst,			OO_FIRST_APP_STRING + XR_extHelpbtst,			EXT_BTST},
	{OO_FIRST_APP_STRING + XR_extHeapDeref,		OO_FIRST_APP_STRING + XR_extHelpHeapDeref,		EXT_HEAPDEREF},
	{OO_FIRST_APP_STRING + XR_extLowMem,		OO_FIRST_APP_STRING + XR_extHelpLowMem,			EXT_LOWMEM},
	{OO_FIRST_APP_STRING + XR_extPeekB,			OO_FIRST_APP_STRING + XR_extHelpPeekB,			EXT_PEEKB},
	{OO_FIRST_APP_STRING + XR_extPeekL,			OO_FIRST_APP_STRING + XR_extHelpPeekL,			EXT_PEEKL},
	{OO_FIRST_APP_STRING + XR_extPeekW,			OO_FIRST_APP_STRING + XR_extHelpPeekW,			EXT_PEEKW},
	{OO_FIRST_APP_STRING + XR_extPokeB,			OO_FIRST_APP_STRING + XR_extHelpPokeB,			EXT_POKEB},
	{OO_FIRST_APP_STRING + XR_extPokeL,			OO_FIRST_APP_STRING + XR_extHelpPokeL,			EXT_POKEL},
	{OO_FIRST_APP_STRING + XR_extPokeW,			OO_FIRST_APP_STRING + XR_extHelpPokeW,			EXT_POKEW},
	{OO_FIRST_APP_STRING + XR_extHeapShuffle,	OO_FIRST_APP_STRING + XR_extHelpHeapShuffle,	EXT_HEAPSHUFFLE}
};

APP_EXT_ENTRY const appExtEntries[]={
/*		&Function(),		type	*/
	{ext_bclr,			APP_EXT_FUNCTION},
	{ext_bset,			APP_EXT_FUNCTION},
	{ext_btst,			APP_EXT_FUNCTION},
	{ext_HeapDeref,		APP_EXT_FUNCTION},
	{ext_StressTest, 	APP_EXT_FUNCTION},
	{ext_PeekB,			APP_EXT_FUNCTION},
	{ext_PeekL,			APP_EXT_FUNCTION},					
	{ext_PeekW,			APP_EXT_FUNCTION},
	{ext_PokeB,			APP_EXT_FUNCTION},
	{ext_PokeL,			APP_EXT_FUNCTION},
	{ext_PokeW,			APP_EXT_FUNCTION},
	{ext_HeapShuffle, 	APP_EXT_PROGRAM}
};

FRAME(appObj, OO_SYSTEM_FRAME, 0, OO_APP_FLAGS, FRAME_SIZE)
	ATTR(OO_APP_FLAGS, 					APP_INTERACTIVE) 				//0x0001 APP_BACKGROUND
	ATTR(OO_APP_NAME, 					APP_TITLE)                      //0x0002
	ATTR(OO_APP_TOK_NAME, 				"cmdpost")						//0x0003
	ATTR(OO_APP_PROCESS_EVENT, 			&Event_Handler)                 //0x0004
	ATTR(OO_APP_DEFAULT_MENU, 			&AppMenu)						//0x0005
	ATTR(OO_APP_EXT_COUNT, 				NUM_EXTENSIONS)					//0x0007
	ATTR(OO_APP_EXTENSIONS, 			appExtensions)					//0x0008
	ATTR(OO_APP_EXT_ENTRIES, 			appExtEntries)					//0x0009
	ATTR(OO_APP_CAN_DELETE,				CanDelete)						//0x000C
	ATTR(OO_APP_CAN_MOVE,				CanMove)						//0x000D
	//ATTR(OO_APP_VIEWER,				AppViewer)						//0x000E
	ATTR(OO_APP_ICON,					&AppIcon)						//0c000F
	ATTR(OO_APP_EXT_HELP,				appExtHelp)						//0x0010
	ATTR(OO_APP_ABOUT,					About)							//0x0012
    
//Application Error Strings
    STRING_ATTR(XR_ADDRESS,				"Address Error")
    STRING_ATTR(XR_ILLEGAL,				"Illegal Instruction")
    STRING_ATTR(XR_DIVIDE,				"Divide by Zero")
    STRING_ATTR(XR_CHK,					"CHK Instruction")
    STRING_ATTR(XR_TRAPV,				"TRAPV Instruction")
    STRING_ATTR(XR_PRIV,				"Privilege Violation")
    STRING_ATTR(XR_TRACEINT,			"Trace Interrupt")
    STRING_ATTR(XR_SINT,				"Spurious Interrupt")
	STRING_ATTR(XR_InvalidHandle,		"Invalid Handle")
	STRING_ATTR(XR_InvalidHistItem,		"Invalid History Item")
	STRING_ATTR(XR_ResetMagicFailedInstall,	APP_TITLE " was unable to activate Reset Magic due to low memory")
	STRING_ATTR(XR_ResetMagicFailedRemove,	APP_TITLE " was unable to deactivate Reset Magic due to low memory")
	STRING_ATTR(XR_CantRemoveIfKernel,	"You cannot change the status of Crash Guard when a kernel is installed!")	
	STRING_ATTR(XR_LinkLog,				"Failed to open the Link Log in APPEND mode. Please check the variable \'main\\Link_Log\' if it exists (archived, locked, type!=\'log\') and/or check for low memory conditions.")
	
//Application Strings   
	STRING_ATTR(XR_ShortAppName,		APP_TITLE)
	STRING_ATTR(XR_LongAppName,			APP_TITLE " (v" APP_VERSION ")")
	STRING_ATTR(XR_AppVersion,			APP_VERSION)
	STRING_ATTR(XR_Protection,			"Crash Guard")
	STRING_ATTR(XR_ProtectionE,			"Crash Guard" RF_ELLIPSIS)
	STRING_ATTR(XR_On,					"On")
	STRING_ATTR(XR_Off,					"Off")
	STRING_ATTR(XR_PasteSpecial,		"Paste Special")
	STRING_ATTR(XR_About_Me,			APP_TITLE "\n\n""Version "APP_VERSION"\nCopyright " RF_COPYRIGHT " 2002, 2003\nBy: Gregory L. Dietsche.\ncmdpost@detachedsolutions.com\n\nDetached Solutions:\nwww.detachedsolutions.com")
	STRING_ATTR(XR_MemoryInfo,			"RAM Info:\nFree RAM: %lu\nLargest Avail Handle: %lu\nUnused Handles: %d\nHeap Status: %s\n\nFlash Info:\nFlash Memory End: 0x%lx")
	STRING_ATTR(XR_MemoryStatus,		"Memory Status" RF_ELLIPSIS)
	STRING_ATTR(XR_RAMStress,			"Low RAM Simulation")
	STRING_ATTR(XR_RAMStressE,			"Low RAM Simulation" RF_ELLIPSIS)
	STRING_ATTR(XR_Status,				"Status")
	STRING_ATTR(XR_Bytes,				"Bytes")
	STRING_ATTR(XR_Enabled,				"Enabled")
	STRING_ATTR(XR_Disabled,			"Disabled")
	STRING_ATTR(XR_UseXbytes,			"Use")
	STRING_ATTR(XR_LeaveBytesFree,		"All Except")
	STRING_ATTR(XR_HexEditor,			"Editor")
    STRING_ATTR(XR_HeapCorrupted,		"WARNING:\nThe Heap Has Been Corrupted! Resetting This Calculator Is Strongly Recommended.")
    STRING_ATTR(XR_LowMemFmtStr,		"main\\lowmem%02x")	//'@' is a fast way of hiding the var
    STRING_ATTR(XR_ResetMagic,			"Reset Magic")
    STRING_ATTR(XR_HeapVaild,			"Valid")
    STRING_ATTR(XR_HeapInvalid,			"Corrupt")
    STRING_ATTR(XR_SetDefaults,			"Set Defaults")
    STRING_ATTR(XR_SystemInfo,			"ASM PRGM Support" RF_ELLIPSIS)
    STRING_ATTR(XR_Refresh,				"Refresh")
	STRING_ATTR(XR_UnknownKernel,		"Unknown Kernel")
	STRING_ATTR(XR_NoKernelFound,		"No Kernel Found")
	STRING_ATTR(XR_h220xtsr,			"h220xtsr")
	STRING_ATTR(XR_HW2Patch,			"HW2 Patch")
	STRING_ATTR(XR_NoHwPatchFound,		"No HW Patch Found")
	STRING_ATTR(XR_NotApplicable,		"Not Applicable")
	STRING_ATTR(XR_SysInfoStr,			"Extended ASM PRGM Support Info:\n\nHW Version: %lu.00\nKernel: %s\nHW Patch: %s")
	STRING_ATTR(XR_LeakWatchStr,		C(	"Leak Watch Report:\n\nDelta RAM: %ld\nDelta Vars: %ld\nAdjusted Delta RAM: %ld\n\nDelta Handles: %d",
											"Leak Watch Report:\n\n Delta RAM: %ld\nDelta Vars: %ld\nAdjusted Delta RAM: %ld\n\nDelta Handles: %d"))
	STRING_ATTR(XR_LeakWatch,			"Leak Watch")
	STRING_ATTR(XR_LeakWatchE,			"Leak Watch" RF_ELLIPSIS)
	STRING_ATTR(XR_InstallHook,			"Install Hook")
	STRING_ATTR(XR_RemoveHook,			"Remove Hook")
	STRING_ATTR(XR_Action,				"Action")
	STRING_ATTR(XR_Application,			"Application")
	STRING_ATTR(XR_AllApps,				"All Applications")
	STRING_ATTR(XR_JumpTo,				"Jump To")
    STRING_ATTR(XR_Handle,				"Handle")
    STRING_ATTR(XR_Address,				"Address")
	STRING_ATTR(XR_ValueC,				"Value:")
	STRING_ATTR(XR_LeakPackInfo,		"The Command Post leak watch module has been uninstalled to allow this application (%s) to pack and move to a new memory location.\nIf continued monitoring is desired, the leak watch module must be reinstalled manually.")
	STRING_ATTR(XR_LeakWatchInstall,	"Leak Watch is now monitoring %s.")
	STRING_ATTR(XR_LeakWatchRemove,		"Leak Watch is no longer monitoring %s.")
	STRING_ATTR(XR_Byte,				"Byte")
	STRING_ATTR(XR_Word,				"Word")
	STRING_ATTR(XR_Long,				"Long")
	STRING_ATTR(XR_PasteSpecialO,		C("Paste Special" RF_ELLIPSIS,
										  "Paste Special" RF_ELLIPSIS "\t" RF_OPTION "V"))
	STRING_ATTR(XR_PasteTruncated,		"Warning: Paste string truncated!")
	STRING_ATTR(XR_KernelWarning,		"Warning: A kernel has been detected.\n\nPlease temporarily uninstall the kernel and wait for a message confirming the successful backup of the system vector table.")
	STRING_ATTR(XR_SuccessfulBackup,	"A backup of the system vector table has been made. Any kernel that was previously removed may be reinstalled if desired.")
	STRING_ATTR(XR_AMSInfo,				"AMS Info" RF_ELLIPSIS)
	STRING_ATTR(XR_BasecodePB,			"Basecode Parm Block:\nLength: 0x%x\nVersion Number: 0x%x\nVersion Date: 0x%lx")
	STRING_ATTR(XR_BasecodePBE,			"Basecode Parm Block" RF_ELLIPSIS)
	STRING_ATTR(XR_HardwarePB,			"Hardware Parm Block")
	STRING_ATTR(XR_HardwarePBE,			"Hardware Parm Block" RF_ELLIPSIS)
	STRING_ATTR(XR_HardwarePBStr,		C("  Hardware ID:\n  Hardware Revision:\n  Boot Major:\n  Boot Revision:\n  Boot Build:\n  Gate Array:\n  Logical LCD Width:\n  Logical LCD Height:\n  Physical LCD Width:\n  Physical LCD Height:", 
										  " Hardware ID:\n Hardware Revision:\n Boot Major:\n Boot Revision:\n Boot Build:\n Gate Array:\n Logical LCD Width:\n Logical LCD Height:\n Physical LCD Width:\n Physical LCD Height:"))
	STRING_ATTR(XR_HWPBTooLong,			"HW Parm Block is longer than expected")
	STRING_ATTR(XR_Variable,			"Variable" RF_ELLIPSIS)
	STRING_ATTR(XR_JumpToE,				"Address or Handle" RF_ELLIPSIS)
	STRING_ATTR(XR_EditE,				"Edit" RF_ELLIPSIS "\t \n")
	STRING_ATTR(XR_JUMPTO,				"JUMP TO")
	STRING_ATTR(XR_Data,				"Data")
	STRING_ATTR(XR_SymEntry,			"Sym Entry")
	STRING_ATTR(XR_Find,				"Find")
	STRING_ATTR(XR_Foreword,			"Forward")
	STRING_ATTR(XR_Backward,			"Backward")
	STRING_ATTR(XR_CantDelete_1,		"Please disable leak watch monitoring from all active applications before uninstalling " APP_TITLE ".")
	STRING_ATTR(XR_SearchingEstr,		"Searching" RF_ELLIPSIS "  Press <ON> to abort")
	STRING_ATTR(XR_FindNextO,			"Find Next\t<CLR>")
	STRING_ATTR(XR_HexEditorWidth,		"Max Hex Editor Width")
	STRING_ATTR(XR_TwoBytes,			"Two Bytes")
	STRING_ATTR(XR_FourBytes,			"Four Bytes")
	STRING_ATTR(XR_SixBytes,			"Six Bytes")
	STRING_ATTR(XR_EightBytes,			"Eight Bytes")
	STRING_ATTR(XR_TenBytes,			"Ten Bytes")
	STRING_ATTR(XR_HeapWalk,			"Heap Walk")
	STRING_ATTR(XR_ResizeHandleE,		"Resize Handle" RF_ELLIPSIS)
	STRING_ATTR(XR_NewSize,				"New Size")
	STRING_ATTR(XR_RESIZEHANDLE,		"RESIZE HANDLE")
	STRING_ATTR(XR_NewValue,			"New Value")
	STRING_ATTR(XR_Direction,			"Direction")
	STRING_ATTR(XR_BOTTOM_ESTACK,		"bottom_estack")
    STRING_ATTR(XR_CU_CURSOR_STATE,		"CU_cursorState")
    STRING_ATTR(XR_ERRNO,				"errno")
    STRING_ATTR(XR_ESTACK_MAX_INDEX,	"estack_max_index")
    STRING_ATTR(XR_EV_APPA,				"EV_appA")
    STRING_ATTR(XR_EV_APPB,				"EV_appB")			
    STRING_ATTR(XR_EV_ERROR_CODE,		"EV_errorCode")
    STRING_ATTR(XR_EV_FLAGS,			"EV_flags")
    STRING_ATTR(XR_EV_RUNNINGAPP,		"EV_runningApp")
    STRING_ATTR(XR_FLASHMEMORYEND,		"FlashMemoryEnd")
    STRING_ATTR(XR_MO_OPTION,			"MO_option")
    STRING_ATTR(XR_NG_CONTROL,			"NG_control")
    STRING_ATTR(XR_OO_FIRST_ACB,		"OO_firstACB")		
    STRING_ATTR(XR_OO_SUPERFRAME,		"OO_SuperFrame")
    STRING_ATTR(XR_OSFASTARROWS,		"OSFastArrows")		
    STRING_ATTR(XR_OSMODKEYSTATUS,		"OSModKeyStatus")
    STRING_ATTR(XR_ST_FLAGS,			"ST_flags")
    STRING_ATTR(XR_TOP_ESTACK,			"top_estack")
    STRING_ATTR(XR_HistoryItem,			"History Item")
    STRING_ATTR(XR_HS_getAns,			"HS_getAns")
    STRING_ATTR(XR_HS_getEntry,			"HS_getEntry")
    STRING_ATTR(XR_JumpAMSGlobalVar,	"AMS Global Variable" RF_ELLIPSIS)
    STRING_ATTR(XR_JumpTable,			"Jump Table")
    STRING_ATTR(XR_FindPreviousO,		"Find Previous\t" RF_OPTION "<CLR>")
    STRING_ATTR(XR_Jump,				"Jump")
    STRING_ATTR(XR_FindO,				"Find" RF_ELLIPSIS "\t" RF_OPTION "\n")
    STRING_ATTR(XR_CopySpecialO,		C("Copy Special" RF_ELLIPSIS, 
    									  "Copy Special" RF_ELLIPSIS "\t" RF_OPTION "C"))
    STRING_ATTR(XR_COPYSPECIAL,			"COPY SPECIAL")
    STRING_ATTR(XR_H_WALK_STATUS,		"H_WALK_STATUS")
    STRING_ATTR(XR_H_WALK_DUMP,			"H_WALK_DUMP")
    STRING_ATTR(XR_H_WALK_SYM,			"H_WALK_SYM")
    STRING_ATTR(XR_CantDelete_2,		"Warning:\n Deleting "APP_TITLE" may cause the currently installed kernel to malfunction. You must uninstall the kernel before deleting "APP_TITLE".")
    STRING_ATTR(XR_AppInfoE,			"App Info"RF_ELLIPSIS)
    STRING_ATTR(XR_AppACB,				"ACB")
    STRING_ATTR(XR_AppHDR,				"HDR")
    STRING_ATTR(XR_BUILTIN,				"BUILTIN,")
	STRING_ATTR(XR_INSTALLED,			"INSTALLED,")
	STRING_ATTR(XR_LOCALIZER,			"LOCALIZER,")
	STRING_ATTR(XR_LOCK,				"LOCK,")
	STRING_ATTR(XR_JT_VERSION,			"JT_VERSION,")
	STRING_ATTR(XR_SELECTED,			"SELECTED,")
	STRING_ATTR(XR_COLLAPSE,			"COLLAPSE,")
	STRING_ATTR(XR_BG,					"BG,")
	STRING_ATTR(XR_COMPRESS,			"COMPRESS,")
	STRING_ATTR(XR_DELETE,				"DELETE,")
	STRING_ATTR(XR_APP_ACB,				"USHORT flags=0x%x\nAppID myID=0x%x\nAppID next=0x%x\nAppID prev=0x%x\nULONG publicstorage=0x%lx\nAppHdr *appHeader=0x%lx\nBYTE *certhdr=0x%lx\npFrame appData=0x%lx")
	STRING_ATTR(XR_APP_HDR,				"ULONG magic=0x%lx\nUCHAR name[8]=\"%s\"\nUSHORT flags=0x%x\nULONG dataLen=0x%lx\nULONG codeOffset=0x%lx\nULONG initDataOffset=0x%lx\nULONG initDataLen=0x%lx\nULONG optlen=0x%lx")
	STRING_ATTR(XR_nAppHeaderFlagsn,	" }\n\nApp Header Flags={ ")
	STRING_ATTR(XR_Localizer,			"LOCALIZER\n")
	STRING_ATTR(XR_nAppFlags,			" }\n\nApp Flags (pFrame)={ ")
	STRING_ATTR(XR_Interactive,			"INTERACTIVE,")
	STRING_ATTR(XR_Con,					"CON,")
	STRING_ATTR(XR_AccessSysVars,		"ACCESS_SYSVARS,")
	STRING_ATTR(XR_Background,			"APP_BACKGROUND,")
	STRING_ATTR(XR_ACBFlags,			"ACB Flags={ ")
	STRING_ATTR(XR_AppInfo,				"App Info")
	STRING_ATTR(XR_Flags,				"Flags")
	STRING_ATTR(XR_SelectApp,			"Select App")
	STRING_ATTR(XR_JumpCommonMem,		"Other Address"RF_ELLIPSIS)
	STRING_ATTR(XR_LCD_MEM,				"LCD_MEM")
	STRING_ATTR(XR_ROM_CALL,			"Rom Call")
	STRING_ATTR(XR_HW1_Ports,			"HW1/2 Mem Mapped IO")
	STRING_ATTR(XR_HW2_Ports,			"HW2 Mem Mapped IO")
	STRING_ATTR(XR_KEY_QUEUE,			"KEY_QUEUE KeyBuffer")
	STRING_ATTR(XR_EVector,				"Exception Vector #")
	STRING_ATTR(XR_AutoInt,				"Auto Interrupt #") 
	STRING_ATTR(XR_Trap,				"Trap #")
	STRING_ATTR(XR_WantDerefPointerQ,	"Would you like to dereference the pointer?")
	STRING_ATTR(XR_OSContrast,			"OS Contrast")
	STRING_ATTR(XR_WantDerefHandleQ,	"Would you like to dereference the handle?")
	STRING_ATTR(XR_RelAddr,				"Relative Address")
	STRING_ATTR(XR_AND,					"AND")
	STRING_ATTR(XR_OR,					"OR")
	STRING_ATTR(XR_XOR,					"XOR")
	STRING_ATTR(XR_Disassembly,			"View Disassembly")
	STRING_ATTR(XR_LinkPortLogger,		"Link Port Logger"RF_ELLIPSIS)
	STRING_ATTR(XR_LinkLogMessage,		"Link Port Logging In Progress.\nResults will be written to \'%s\'.\nPress ON to exit the link port logger.\n")
	STRING_ATTR(XR_BytesReceived,		"%lu Bytes Received")
	STRING_ATTR(XR_CrashLinkDump,		"Send debugging information to the link port?")
	STRING_ATTR(XR_JumpToDisassembly,	"Jump To Disassembly?")
	STRING_ATTR(XR_DumpUSP,				"Send User Stack to the link port? (This operation can take several seconds)")
	STRING_ATTR(XR_DumpSSP,				"Send Supervisor Stack to the link port? (This operation can take several seconds)")
	STRING_ATTR(XR_DasmToolsE,			"Disassembly Tools"RF_ELLIPSIS)
	STRING_ATTR(XR_movem,				"Movem Register Decoder")
	STRING_ATTR(XR_PreDecrement,		"movem predecrement")
	STRING_ATTR(XR_PostIncrement,		"movem postincrement")	
	STRING_ATTR(XR_Bookmarks,			"Bookmarks")
	STRING_ATTR(XR_JumpBookMark1,		"Jump To Bookmark 1\t" RF_OPTION RF_ARROW_UP)
	STRING_ATTR(XR_JumpBookMark2,		"Jump To Bookmark 2\t" RF_OPTION RF_ARROW_DOWN)
	STRING_ATTR(XR_SetBookMark1,		"Set Bookmark 1")
	STRING_ATTR(XR_SetBookMark2,		"Set Bookmark 2")
	STRING_ATTR(XR_HighAddr,			"End Address")
	STRING_ATTR(XR_NotFound,			"Not Found")
	STRING_ATTR(XR_RomCallToStr,		"Rom Call To String")
	STRING_ATTR(XR_DasmTools,			"Disassembly Tools")
	STRING_ATTR(XR_NoDatabase,			"Rom Call database main\\romcalls does not exist.")
	STRING_ATTR(XR_Tool,				"Tool")
	STRING_ATTR(XR_DASM_Buffering,		"Buffering" RF_ELLIPSIS" %3.0f%%")
	STRING_ATTR(XR_VerboseDasm,			"Verbose movem")
	STRING_ATTR(XR_HW3Patch,			"HW3 Patch")
   	
//App Extensions
	STRING_ATTR(XR_extbclr,				"bclr")
	STRING_ATTR(XR_extbset,				"bset")
	STRING_ATTR(XR_extbtst,				"btst")
    STRING_ATTR(XR_extHeapDeref,		"HeapDRef")
    STRING_ATTR(XR_extLowMem,			"LowMem")
    STRING_ATTR(XR_extPeekB,			"PeekB")
    STRING_ATTR(XR_extPeekL,			"PeekL")
    STRING_ATTR(XR_extPeekW,			"PeekW")
    STRING_ATTR(XR_extPokeB,			"PokeB")
    STRING_ATTR(XR_extPokeL,			"PokeL")
    STRING_ATTR(XR_extPokeW,			"PokeW")
	STRING_ATTR(XR_extHeapShuffle,		"Shuffle")
	    
//App extension help strings
	STRING_ATTR(XR_extHelpbclr,			"any address, bit number")
	STRING_ATTR(XR_extHelpbset,			"any address, bit number")
	STRING_ATTR(XR_extHelpbtst,			"any address, bit number")
	STRING_ATTR(XR_extHelpHeapDeref,	"Peforms HeapCompress();HeapDeref(int)")
    STRING_ATTR(XR_extHelpLowMem,		"[enabled], [mode], [bytes]")
    STRING_ATTR(XR_extHelpPeekB,		"any address")
	STRING_ATTR(XR_extHelpPeekL,		"even address")
    STRING_ATTR(XR_extHelpPeekW,		"even address")
    STRING_ATTR(XR_extHelpPokeB,		"any address, new value")
	STRING_ATTR(XR_extHelpPokeL,		"even address, new value")
    STRING_ATTR(XR_extHelpPokeW,		"even address, new value")
    STRING_ATTR(XR_extHelpHeapShuffle,	"Shuffle memory blocks in the heap")

//App ext extension help strings
//RF_ARROW_RIGHT    
    STRING_ATTR(XR_extextHelpbclr,			"bclr(address, bitnum)\n\nClears the bit at the given address. This is a BYTE operation. The value of the bit prior to the operation is returned.")
    STRING_ATTR(XR_extextHelpbset,			"bset(address, bitnum)\n\nSets the bit at the given address. This is a BYTE operation. The value of the bit prior to the operation is returned.")
    STRING_ATTR(XR_extextHelpbtst,			"btst(address, bitnum)\n\nTests the bit at the given address. This is a BYTE operation. The current value of the bit is returned.")
    STRING_ATTR(XR_extextHelpHeapDeref,		"HeapDRef(handle)\n\nDereference a handle.\nPesudo Code:\nHeapCompress();\nreturn HeapDeref(handle);")
    STRING_ATTR(XR_extextHelpLowMem,		"LowMem([enabled], [mode], [bytes])"RF_ARROW_RIGHT"list\n\nenabled = {1=ON, 0=OFF}\nmode = {1=All Except, 2=Use}\nbytes = {Number of Bytes}\n\nThe previous"
    										" (or current if no arguments are passed) mode settings will be returned as a list.")
    STRING_ATTR(XR_extextHelpPeekB,			"PeekB(address)"RF_ARROW_RIGHT"int\n\nReads one byte from the specified memory address and returns the result.")
    STRING_ATTR(XR_extextHelpPeekL,			"PeekL(address)"RF_ARROW_RIGHT"int\n\nReads one long (4 bytes) from the given memory address and returns the result. If the passed address is odd, an Address Error is thrown.")
    STRING_ATTR(XR_extextHelpPeekW,			"PeekW(address)"RF_ARROW_RIGHT"int\n\nReads one word (2 bytes) from the given memory address and returns the result. If the passed address is odd, an Address Error is thrown.")
    STRING_ATTR(XR_extextHelpPokeB,			"PokeB(address, new value)"RF_ARROW_RIGHT"int\n\nWrites one byte to the given memory address. The previous (BYTE) value pointed to by the given address is returned.")
    STRING_ATTR(XR_extextHelpPokeL,			"PokeL(address, new value)"RF_ARROW_RIGHT"int\n\nWrites one long (4 bytes) to the specified memory address. The previous (long) value pointed to by the given address is returned.")
    STRING_ATTR(XR_extextHelpPokeW,			"PokeW(address, new value)"RF_ARROW_RIGHT"int\n\nWrites one word (2 bytes) to the specified memory address. The previous (WORD) value pointed to by the given address is returned.")
    STRING_ATTR(XR_extextHelpHeapShuffle,	"Shuffle()\n\nShuffle memory blocks in the heap. Equivalent to AMS rom call HeapShuffle();")

//App Data Interface      
	ATTR(OO_PROTECTION_ACTIVE,			&global.AntiCrashInstalled)		//0x10000
	ATTR(OO_REDIRECTED_VECT,			gRedirect)
	ATTR(OO_VECTORS,					gVectors)
	ATTR(OO_OLD_VECTORS,				global.old_vectors)
	ATTR(OO_VECT_REDIR,					NUM_VECT_REDIR)
	ATTR(OO_VECT_SAVED,					NUM_VECT_SAVED)
	ATTR(OO_BACKUP_VECTORS,				MakeExceptionVectorBackup)
	ATTR(OO_INSTALL_VECTORS,			EnableCrashProtection)
	ATTR(OO_UNINSTALL_VECTORS,			DisableCrashProtection)
	ATTR(OO_KERNELS,					gKernels)
	ATTR(OO_KERNELIDS,					gKernelID)
	ATTR(OO_NUM_KERNELS,				NUM_KERNELS)
	ATTR(OO_LEAK_WATCH_BEGIN,			export_LeakWatchBegin)			
	ATTR(OO_LEAK_WATCH_END,				export_LeakWatchEnd)
	ATTR(OO_DASM_ONE,					disassemble_one_ext_wrapper)
	ATTR(OO_OPEN_DATABASES,				OpenAllDatabases)
	ATTR(OO_CLOSE_DATABASES,			CloseAllDatabases)
	
ENDFRAME

//////////////////////////////////////////////////
//Application Data Section					  ///
////////////////////////////////////////////////

/* Pointer to the Frame object */
	pFrame pAppObj = (pFrame)&appObj;  /* Must be first! */

//This is a bitmap structure, NOT an icon as suggested by the FRAME entry
static const short AppIcon[]={
	0x0012,	//Num Rows	/\
	0x0014,	//Num Cols	<->
	//icon data            	
	0x01fe,0x0007,0xff80,0x3c09,0xc069,0x50e0,0xe027,0x60c5,0x1f30,0xd077,
	0x70e5,0xec30,0xc8f9,0x70c2,0xf030,0xe904,0xe072,0xa1e0,0x690b,0xc03f,
	0xff80,0x3ffc,0x0009,0x2600,0x1b33,0x0032,0x1180
};

//16x16 Detached Solutions BITMAP
static const short DSIcon[]={
	0x0010,
	0x0010,
	0x0000,0x0000,0x7e00,0x7f00,0x7780,0x7380,0x779c,0x77fe,
	0x7f77,0x7c7e,0x403f,0x7ff7,0x007f,0x003e,0x0000,0x0000
};


/* The Primary Window For The GUI portion of this app */
	WINDOW appW;
		
/* New Exception Vector Handlers */
	long gRedirect[NUM_VECT_REDIR]={
		(long)Exception_0,
		(long)Exception_1,
		(long)Exception_2,
		(long)Exception_3,
		(long)Exception_4,
		(long)Exception_5,
		(long)Exception_6,
		(long)Exception_7
	};

/* A Global List Of Vectors  */
	short gVectors[NUM_VECT_SAVED]={
	/* Addresses of Exceptions to be Trapped */
		VECT_ADDR_sh(3),		//Address Error									Type 0
		VECT_ADDR_sh(4),		//Illegal Instruction 							Type 1
		VECT_ADDR_sh(5),		//Divide by Zero								Type 2
		VECT_ADDR_sh(6),		//CHK Instruction								Type 2
		VECT_ADDR_sh(7),		//TRAPV Instruction								Type 2
		VECT_ADDR_sh(8),		//Privilege Violation							Type 1
		VECT_ADDR_sh(9),		//Trace											Type 1
		VECT_ADDR_sh(24),		//Spurious Interrupt							Type 1
		
	/* Other Vectors That Need To Be Backed Up */
		VECT_ADDR_sh(25),		//AI 1
		VECT_ADDR_sh(26),		//AI 2
		VECT_ADDR_sh(27),		//AI 3
		VECT_ADDR_sh(28),		//AI 4
		VECT_ADDR_sh(29),		//AI 5
		VECT_ADDR_sh(30)		//AI 6
	};

/* List of Known Kernel String Pointers */
char * gKernels[NUM_KERNELS]={
	"KerNO",		/* KerNO is not a true kernel, but it mimicks some features found in 'real' kernels */
	"Universal OS",
	"Lex OS",
	"TEOS",
	"Plusshell",	/* A Piece of History: Plusshell was the _first_ kernel for the 89/92p */
	"Doors OS",
	"PreOS",
};

/* Corresponds to gKernels this number should be found at 0x32.w */
USHORT gKernelID[NUM_KERNELS]={
	0x4B4E,	//#'KN'
	0x554F,	//#'UO'
	0x4c58,	//#'LX'
	0x544F,	//#'TO'
	0x5053,	//#'PS'
	0x4454,	//#'DN'
	0x504F,	//#'PO'
};

/* All Variables that need to be saved with CM_PACK and restored later with CM_UNPACK */
	PACK_DAT global;

/* For Delayed Handling of Errors */
	SINT gDelayedErrorNum;

/* For Routines that need to return a pointer to a static(locked) buffer */
	char gBuff[MISC_BUFF_LEN + 1];
	//char *gBuff=NULL;
	//HANDLE ghBuff=H_NULL;

	const char var_type[]="CPDB";
	const char romcalldb_var_name[]="romcalls";
	const char memdatdb_var_name[]="memdat";
	
	char *gROM_CALL_DB_PTR=NULL;					//external database (romcalldb_var_name)
	ULONG *gROM_CALL_ADDR_PTR=NULL;					//internal database - list of rom call addresses - references romcalldb
	char *gMEM_DAT_DB_PTR=NULL;						//external database (memdatdb_var_name)
	
//////////////////////////////////////////////////

//My own debuged replacment for TI's OS_NeedMinimumVersion macro
//removed redundant line:       Access_AMS_Global_Variables;									\
#define CheckAMS(frame, major, minor)								\
{																	\
   static BOOL _OSVersionOK_ = FALSE;								\
   if (! _OSVersionOK_)												\
   {																\
      if (((long const *)AMS_Global_Variables)[-1] < 1499 ||		\
          ((BASECODE_PARM_BLOCK const *(* const)(void))AMS_Global_Variables[1498])()->version_number	\
            < (((major) << 8) + (minor)))							\
         {															\
            MY_ACB(frame)->flags |= (ACB_JT_VERSION|ACB_DELETE);	\
            return;													\
         }															\
      else															\
         _OSVersionOK_ = TRUE;										\
   }																\
}

static void Event_Handler(pFrame self, PEvent e)
{
    
	WIN_RECT appWR;
	volatile HANDLE storage;
	PACK_DAT *pstorage;
	Access_AMS_Global_Variables;
	CheckAMS(pAppObj, NEED_AMS_MAJOR, NEED_AMS_MINOR);	
  
	switch (e->command)
	{	
		case CM_BACKGROUND:
		
			if(global.BgEventMask&BG_KernelCheck)
			{
				if(!CheckKernel())	//if a kernel is not (no longer) installed attempt to make a clean vector backup
				{
					/*
						if kernel no longer installed
						anti crash protection (this app) is in undefined state.. may be off or on regardless of what the global variable says
						the user _should_ not have enough time to beat the CM_BACKGROUND event (subjective) and turn on this apps anti-crash protection
						therefore, implicitly backup current vector table (no checks for installed anti-crash support)
						and if the crash protect enabled flag is set, reinstall this app's crash protection vectors
						this should get a reliable vector backup and restore the crash protection to a known state
					*/
					
					global.BgEventMask&= ~BG_KernelCheck;
					
					BackupExceptionVectors(OO_AbsoluteGet(OO_VECTORS), OO_AbsoluteGet(OO_OLD_VECTORS), (short)OO_AbsoluteGet(OO_VECT_SAVED));
					if(global.AntiCrashInstalled)EnableCrashProtection();
					
					DlgNotice(OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_LongAppName),
						OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_SuccessfulBackup));
				}
			}
			if(global.BgEventMask&BG_Disassemble)
			{
				DASMEditorEventLoop(self, e);
			}
			
			if(!global.BgEventMask)	//no bits are set, so disable the bacground event processing
			{
			
				ACB *self=(ACB*)HeapDeref(GetMyAppID());			//get a pointer to my ACB
				ULONG flags=(ULONG)OO_AbsoluteGet(OO_APP_FLAGS);	//\
				flags&=~APP_BACKGROUND;								//->the os seems to ignore this, but if it ever does get smarter... i will have it covered :)
				OO_AbsoluteSet(OO_APP_FLAGS, (void *)flags);		///
				
				self->flags&=~ACB_BG;	//unset the acb background event flag (the ams listens to this)
			}
		break;
		
		case CM_DEFAULTS:
			SetDefaults();
		break;
		
		case ACM_Defaults:
			SetDefaults();
			RemoveResetMagic();
			DlgNotice(XR_stringPtr(XR_LongAppName), XR_stringPtr(XR_cResetDefaults));
		break;
		
		case CM_FORMAT:
	    	DoFormatDialog();
	    break;
	    				
		case CM_INSTALL:
			//I want a reliable vector backup. If a kernel is installed, i cannot gurantee a good backup
			if(CheckKernel())	// || h220xtsrInstalled() || HW2PatchInstalled!=HW2_Patch_ROM / HW3_Patch
			{//no need to mess with the ACB in the install event because the ams will set that flag for me
			//if the APP_BACKGROUND flag is set in my frame
				ULONG flags=(ULONG)OO_AbsoluteGet(OO_APP_FLAGS);
				flags|=APP_BACKGROUND;
				OO_AbsoluteSet(OO_APP_FLAGS, (void *)flags);
				
				global.BgEventMask|=BG_KernelCheck;
				
				DlgNotice(OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_LongAppName),
					OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_KernelWarning));
			}
			
			MakeExceptionVectorBackup();//backup specific portions of the exception vector table
			SetDefaults();				//Set App Defaults for the first time
			HideResetMagicVar(TRUE);	//the variable will loose its 'inuse' bit after a reset
			EnforceResetMagicRules();	//work the magic and set any sticky settings that need to be set...
		break;
		
		case CM_UNINSTALL:
			DisableCrashProtection();
			LeakWatchNone();
			RemoveResetMagic();
			
			if(storage=OO_appGetPublicStorage())	//free any mem that was used for CM_PACK/UNPACK
				HeapFree(storage);				
		break;
		
		case CM_PACK:
			storage  = OO_appGetPublicStorage();
			pstorage = HeapDeref(storage);
		   *pstorage = global;					
		break;
		
		case CM_UNPACK:
			storage  = OO_appGetPublicStorage();
			pstorage = HeapDeref(storage);
			global   = *pstorage;
			
			//we moved, so the vector table needs an update
			if(pstorage->AntiCrashInstalled)
				EnableCrashProtection();
		break;
		
		case CM_START:
			#ifdef DEBUG
				export_LeakWatchBegin();
			#endif
			
			gDelayedErrorNum=0;	//clear any previous error context
			
			appWR = *(e->info.startInfo.startRect);
			
			MO_currentOptions(); 
			
         	if(!WinOpen(&appW, &appWR,  WF_DUP_SCR | (MO_option[MO_OPT_SPLIT_SCREEN]==D_MODE_SPLIT_FULL?WF_NOBORDER:0)))
            	gDelayedErrorNum=ER_MEMORY;
		break;
		
		case CM_FOCUS:
			if(GetAppErrorContext())
			{
			 	EV_errorCode=GetAppErrorContext();
			 	EV_quit();
			}

			UseTurboKeys(TRUE);
			
			#ifdef DEBUG
				ST_helpMsg("Warning: You are using a DEBUG Build!");
			#endif
			
		break;
		
		case CM_UNFOCUS:
			UseTurboKeys(FALSE);
			break;
			
		case CM_NULL:
			UseTurboKeys(TRUE);
			break;
		
		case CM_QUIT:
			//if(GetAppErrorContext())break;	//the app is exiting in error
			if(appW.Next)
			{
				WinClose(&appW);
				appW.Next=NULL;
			}
		
		//enforce the Stress Test settings
		if(global.stress_dat.optList[OPT_STATUS]==STRESS_ENABLE)
			do_LowMemStressTest();
		
		#ifdef DEBUG
			export_LeakWatchEnd("Command Post DEBUG MODE");
		#endif
			
		break;
		
      	case CM_ACTIVATE:
      		if(GetAppErrorContext())break;	//the app is exiting in error
			
			EV_defaultHandler(e);
			
			WinBeginPaint(&appW);
			WinActivate(&appW);
			OpenAllDatabases();
		break;
		
		case CM_DEACTIVATE:
			if(GetAppErrorContext())break;	//the app is exiting in error
			
			WinEndPaint(&appW);			
			CloseAllDatabases();
			EV_defaultHandler(e);
		break;
		
		case CM_ABOUT:
			ShowAboutScr();
		break;
		
		case ACM_RAMStats:
			DoRAMStatsDialog();		
		break;
		
		case ACM_BasecodePB:
			ShowBasecode_PB();
		break;
		
		case ACM_HW_PB:
			ShowHW_PB();		
		break;
		
		case ACM_RAMStressDialog:
			DoStressTestDialog();		
		break;
		
		case ACM_SysInfo:
			ShowSysInfo();		
		break;
		
		case ACM_AMS_Info:
			ShowAMSInfo();
		break;
		
		case ACM_LeakWatch:
			LeakWatchDialog();
		break;
		
		case ACM_AppInfo:
			DoAppInfoDialog();
		break;
		
		case ACM_H_WALK_STATUS:
			HeapWalk(H_WALK_STATUS);
			break;
			
		case ACM_H_WALK_DUMP:
			HeapWalk(H_WALK_DUMP);
			break;
				
		case ACM_H_WALK_SYM:
			HeapWalk(H_WALK_SYM);
			break;
			
		case ACM_LinkPortLogger:
			LinkPortLogger();
		break;
		
		case ACM_DisassemblyTools:
			DisassemblyToolsDialog();
		break;
		
		case ACM_DisASMViewToggle:
		{//scope brackets
			Event ev;
			global.DisassemblerActive=!global.DisassemblerActive;
			
			ev.command=CM_DEACTIVATE;
			
			if(global.DisassemblerActive)
			{
				HexEditorEventLoop(self, &ev);
				ev.command=CM_ACTIVATE;
				DASMEditorEventLoop(self, &ev);
				
			}
			else
			{
				DASMEditorEventLoop(self, &ev);
				ev.command=CM_ACTIVATE;
				HexEditorEventLoop(self, &ev);
			}

		}//scope brackets
			break;
					
		default:
			if(global.DisassemblerActive)
				DASMEditorEventLoop(self, e);
			else
				HexEditorEventLoop(self, e);	//fix for CM_PASTE_HANDLE Events
				
			EV_defaultHandler(e);
			return;
		break;
	}
	
//pass all other events on to the Hex/DASM Editor portion of this app for possible further processing
	if(!GetAppErrorContext())
	{
		if(global.DisassemblerActive)
			DASMEditorEventLoop(self, e);
		else
			HexEditorEventLoop(self, e);
	}
}

//Implements the About Screen and About Frame Attribute about string
static char* About(void)
{//This app may not be active when this function is called, so use
//a lookup method that will not fail
	return OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_About_Me);
}

static BOOL CanMove(AppID self)
{//This app MUST_NOT_MOVE if it can not save its current state,
 // or the saved exception vector table will be lost!
 // memory allocated here will be HeapFree()d when the app is CM_UNINSTALLed
	HANDLE storage;
	//OO_appSet/GetPublicStorage WILL NOT WORK in this instance because the appid can be different than this apps id
	ULONG *pubstorage=&((ACB*)HeapDeref(GetMyAppID()))->publicstorage;
	
	if(!*pubstorage)				//Handle has not been allocated
	{
		if(!(storage=HeapAllocHigh(sizeof(PACK_DAT))))	//attempt to allocate storage
			return FALSE;
			
		//OO_appSetPublicStorage(storage);			//storage allocated successfully
		*pubstorage=(ULONG)storage;
	}
	
  	return LeakWatchAppsNotActive();	//can't move if a hooked app is active
}

//Another OS_NeedMinimumVersion replacement... for the OO_APP_CAN_DELETE handler
#define DeleteImplicit(frame,major,minor)						\
{																\
  if (((long const *)AMS_Global_Variables)[-1] < 1499 ||		\
      ((BASECODE_PARM_BLOCK const *(* const)(void))AMS_Global_Variables[1498])()->version_number	\
        < (((major) << 8) + (minor)))							\
        return TRUE;											\
}
static BOOL CanDelete(AppID self)
{
//if the ams is bad, then we can't risk calling a non ams 2.xx function, for example...
	Access_AMS_Global_Variables;
	DeleteImplicit(pAppObj, NEED_AMS_MAJOR, NEED_AMS_MINOR);
	
	if(!LeakWatchAppsNotActive())
	{
		DlgNotice(OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_LongAppName),
				  OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_CantDelete_1));
		
		return FALSE;
	}
	
	
//as long as we never do a 'vector backup restore' during the uninstall process, this is fine
//otherwise, this should read if(CheckKernel())
	if(CheckKernel() && global.AntiCrashInstalled)
	{
		DlgNotice(OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_LongAppName),
				  OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_CantDelete_2));
				  
		return FALSE;
	}
				  
	return TRUE;
}

//This leaves room for future expansion while saving a few bytes too
static SINT GetAppErrorContext(void)
{
	return gDelayedErrorNum;
}

//responsible for restoring 'factory' settings
static void SetDefaults(void)
{
	Access_AMS_Global_Variables;
	PACK_DAT *p_dat=&global;

	p_dat->VerboseDisassembler=TRUE;	//The Default is ON
	
//defaults for LowMem
	p_dat->stress_dat.optList[OPT_STATUS]=STRESS_DISABLE;
	p_dat->stress_dat.optList[OPT_MODE]=STRESS_MODE_FILL;
	strcpy(p_dat->stress_dat.txtBytes,"1000");
	
	p_dat->hex_dat.top=(char*)0x0;
	p_dat->hex_dat.addr=0;

//defaults for leak watch dialog	
	p_dat->leak_dat.optList[0]=1;
	p_dat->leak_dat.optList[1]=1;
	
	p_dat->movem_decode.optList[0]=0;
	p_dat->movem_decode.buff[0]=0;
	
	LeakWatchNone();
	do_LowMemStressTest();
	
	
	if(p_dat->DisassemblerActive)
	{
		Event event;
		AppID aid=GetMyAppID();
		
		if(EV_currentApp==aid)
		{
			event.command=ACM_DisASMViewToggle;
			EV_sendEvent(aid, &event);
		}
		else
		{
			p_dat->DisassemblerActive=FALSE;
		}
	}
	
	//by default, the anti-crash protection will be turned on unless there
	//is a kernel installed. In which case, it will be left off.
	//additionally, the global anti crash protect variable is automatically 
	//initialized to zero (FALSE) by the OS
	//EnableCrashProtection();
	
	//the new default is OFF. This is more future "proof" if the user wants it to
	//be on after a reset, they can always use the reset magic feature
	DisableCrashProtection();
}

static void appExtHelp(AppID self, USHORT strnum)
{
	DlgNotice(OO_AbsoluteGet(OO_FIRST_APP_STRING + XR_LongAppName), 
				OO_AbsoluteGet(OO_FIRST_APP_STRING + FIRST_EXT_HELP_STR + strnum));
}

static void ShowSysInfo(void)
{
	char buff[500];
	char *kptr, *patchptr;
	short kernel;
	USHORT count=(short)OO_AbsoluteGet(OO_NUM_KERNELS);
	char **kstr=(char **)OO_AbsoluteGet(OO_KERNELS);
	USHORT *knum=(USHORT *)OO_AbsoluteGet(OO_KERNELIDS);
	BOOL hwpatch;
	
	for(kernel=0; kernel<count; kernel++)
	{
		if(CheckKernel() == knum[kernel])
			break;
	}
	
	if(kernel==count)
		kptr=*(USHORT *)0x32?XR_stringPtr(XR_UnknownKernel):XR_stringPtr(XR_NoKernelFound);
	else
		kptr=kstr[kernel];
	
	if(FL_getHardwareParmBlock()->hardwareRevision)
	{
		if(h220xtsrInstalled())patchptr=XR_stringPtr(XR_h220xtsr); else
		if(hwpatch=HW2PatchInstalled())
		{
			if(hwpatch==HW3_Patch)
				patchptr=XR_stringPtr(XR_HW3Patch);
			else
				patchptr=XR_stringPtr(XR_HW2Patch);
		}
		else
			patchptr=XR_stringPtr(XR_NoHwPatchFound);
	}
	else
		patchptr=XR_stringPtr(XR_NotApplicable);
	
	sprintf(buff, XR_stringPtr(XR_SysInfoStr), AB_getGateArrayVersion(), kptr, patchptr);
	DlgNotice(XR_stringPtr(XR_LongAppName), buff);

}

static void ShowAMSInfo(void)
{
	Access_AMS_Global_Variables;
	char serno[17];
	char prodname[40];
	char prodid[12];  
	char buff[500];
	
	AB_prodid(prodid);
	AB_prodname(prodname);
	AB_serno(serno);
	
	sprintf(buff, "%s\n%s\n%s %s\n%s %s\n%s %s",
	XR_stringPtr(XR_ModelName), prodname, ReleaseVersion, ReleaseDate, XR_stringPtr(XR_ProductIDCB), prodid,
	XR_stringPtr(XR_SerialNum), serno);
	
	DlgNotice(XR_stringPtr(XR_LongAppName), buff);
}

BOOL h220xtsrInstalled(void)
{		
	switch(*(unsigned long*)(*(unsigned long*)0xAC-8))
	{
		case 0x32547372:	//2Tsr (new signature)
		case 0x32545352:	//2TSR (old signature)
			return TRUE;
		break;
		
		default:
			return FALSE;		
	}
}

BOOL HW2PatchInstalled(void)
{
	Access_AMS_Global_Variables;
	
	register unsigned long *ptr;
	
	if (*(unsigned long *)0xAC == 0x100) return HW2_Patch_RAM;
	
	ptr = (unsigned long *)((addr_EX_stoBCD)+0x52);
	
	if (ptr[0]==0x700000 && ptr[1]!=0x36BCFFDF)
	{
		if(HW3PatchInstalled())
			return HW3_Patch;
			
		return HW2_Patch_ROM;
	}
	
	return HW2_Patch_None;
}

//this is a subroutine of the HW2PatchInstalled function
//i recommend only calling this function if HW2 patch detected a rom 
static BOOL HW3PatchInstalled(void)
{
	/*
	Yes, the HW3Patch also adds a fix for the battery change crash. Here's how to detect it:
	movea.l 0xac.w,%a0
	|Make sure this isn't a RAM installation before inspecting the trap #11.
	cmp.l #0x200000,%a0
	bcs.s nopatch ;lo
	|Check for the HW3Patch only patch (battery change crash fix)
	501:
	cmp.w #0x4e68,(%a0)+
	bne.s 501b
	tst.w 4(%a0)
	jbeq already
*/
//my code based on the asm code given by kevin
	unsigned short *trap = (unsigned short*)(*(unsigned long*)0xac);	//trap #11 pointer
	if(0x200000UL<=(unsigned long)trap)
	{
		while(*trap!=0x4e68)trap++;
		if(trap[2])
			return TRUE;	
	}
	
	return FALSE;
}

DWORD NoCallBack(WORD DlgId, DWORD Value) { return TRUE; }


//replacement for tios GetValue
/*
	Less error checking is done... use push_simplify before calling
*/
unsigned long GetLongArg(EStackIndex index, unsigned long rLow, unsigned long rHigh)
{
	Quantum tag=*index;
	register short quantum;	//number of quantums
	register unsigned long result=0;
	
	if(tag==SECONDARY_TAG)
	{//handle bin and hex numbers
		tag=*--index;
		if(tag!=BIN_NUM_TAG && tag!=HEX_NUM_TAG) ER_throw(ER_DATATYPE);
		tag=*--index;
	}
	
	quantum=*(--index);
	
	if(tag!=NONNEGATIVE_INTEGER_TAG && tag!=NEGATIVE_INTEGER_TAG) ER_throw(ER_DATATYPE);
		
	if(quantum>4) ER_throw(ER_DOMAIN);
	
	while(quantum--)
	{
		result=(result<<8) + *(--index);
	}
	
	result=tag==NONNEGATIVE_INTEGER_TAG?result:-result;
	
	if(result>rHigh)ER_throw(ER_DOMAIN);
	if(result<rLow)ER_throw(ER_DOMAIN);
	
	return result;
}

long StrToEStackToLong(char *str)
{
	Access_AMS_Global_Variables;
	EStackIndex oldtop=top_estack;
	long retval=0;	//satisfy the compiler
	char buff[500];
	
//i'm not sure how to get the equivalent of int(exact(str)) on the estack so this works for me :)
//essentially, this forces the result to be more exact than exact ... ie a _perfect_ integer
	strcpy(buff, XR_stringPtr(XR_intP));
	strcat(buff, XR_stringPtr(XR_exactP));
	strcat(buff, str);
	strcat(buff, "))");

	TRY
		SET_SIDE_EFFECTS_FORBIDDEN;
		push_quantum(END_OF_SEGMENT_TAG);
		push_parse_text((BYTE *)buff);
		push_simplify_statements(top_estack);
		retval=GetLongArg(top_estack, 0, ULONG_MAX);
	FINALLY
		SET_SIDE_EFFECTS_PERMITTED;
		top_estack=oldtop;
	ENDFINAL
		
	return retval;		
}

static void ShowBasecode_PB(void)
{
	char buff[500];
	BASECODE_PARM_BLOCK const *b=EX_getBasecodeParmBlock();
	
	sprintf(buff, XR_stringPtr(XR_BasecodePB), b->len, b->version_number, b->version_date);
	DlgNotice(XR_stringPtr(XR_LongAppName), buff);
}

static void ShowHW_PB(void)
{
	USHORT *pbs=(USHORT*)FL_getHardwareParmBlock();
	ULONG *pb;
	WIN_RECT wRegion={C(10, 30), C(4, 6), C(MAX_X-10, 215), C(88, 113)};
	WINDOW win;
	USHORT len;
	WIN_COORDS ypos=1-C(6, 8);
	char buff[100];
	Event ev;
	
	if(!WinOpen(&win, &wRegion, WF_SAVE_SCR|WF_TTY|WF_TITLE|WF_ROUNDEDBORDER, XR_stringPtr(XR_HardwarePB)))
		ER_throw(ER_MEMORY);
	
	WinBeginPaint(&win);
	
	#ifdef _89
		WinFont(&win, F_4x6);
	#endif
	
	WinClr(&win);
	WinStr(&win, XR_stringPtr(XR_HardwarePBStr));
	DrawStaticButton(&win, PDB_OK, 5);
	
	len=*pbs;
	pbs++;
	pb=(ULONG*)pbs;
	len-=2;
	
	if(len>0x28)
	{
		ST_helpMsg(XR_stringPtr(XR_HWPBTooLong));
		len=0x28;
	}
	
	len=len/4;
	while(len)
	{
		sprintf(buff, "%lu", *pb++);
		WinStrXY(&win, C(75, 131), ypos+=C(6, 8), buff);
		len--;
	}
	
	while(KeyYesOrNo(GKeyIn(NULL, GKF_MODAL | GKF_SYS))==-1);
	
	WinEndPaint(&win);
	WinClose(&win);	
}

static void ShowAboutScr(void)
{
	const WIN_RECT wRegion={C(10, 30), C(4, 6), C(MAX_X-10, 215), C(90, 113)};
	WINDOW win;
	WIN_POINT ds_pt={4,1}, post_pt;
	#ifndef NO_EASTER_EGGS
		short leet_user=FALSE;
		short key_code='x';			//initialize it with something other than a valid key...
	#endif
	
	
	if(!WinOpen(&win, &wRegion, WF_SAVE_SCR|WF_TTY|WF_TITLE|WF_ROUNDEDBORDER, XR_stringPtr(XR_ABOUT)))
		ER_throw(ER_MEMORY);
	
	WinBeginPaint(&win);
	
	#ifdef _89
		WinFont(&win, F_4x6);
	#endif
	
	post_pt.x0=WinWidth(&win)-4-((BITMAP*)AppIcon)->NumCols;
	post_pt.y0=1;
	
	WinClr(&win);
	WinBitmapPut(&win, ds_pt.x0, ds_pt.y0, (BITMAP*)DSIcon, A_XOR);
	WinBitmapPut(&win, post_pt.x0, post_pt.y0, (BITMAP*)AppIcon, A_XOR);
	
	WinMoveTo(&win,33,7);
	WinStr(&win, About());
	DrawStaticButton(&win, PDB_OK, 5);
	
	#ifdef NO_EASTER_EGGS
		while(KeyYesOrNo(GKeyIn(NULL, GKF_MODAL | GKF_SYS))==-1);
	#else
		while(KeyYesOrNo(key_code)==-1)
		{
			key_code=GKeyIn(NULL, GKF_MODAL | GKF_SYS);
			if(key_code==(0x31337-(0x12F0|0x30000)) && !leet_user)	//$r3 j00 1 31337 H4X0R G
			{
				short dx=1, dy=1, steps;
				
				leet_user=TRUE;
				
				for(steps=0;steps<C(105,218);steps++)//210
				{
					#ifdef _92
					if(steps<155)
					{
					#endif
						WinBitmapPut(&win, post_pt.x0, post_pt.y0, (BITMAP*)AppIcon, A_XOR);
						post_pt.x0--;
						WinBitmapPut(&win, post_pt.x0, post_pt.y0, (BITMAP*)AppIcon, A_XOR);
					#ifdef _92
					}
					else
					{	//this delay is really designed for HW2 calcs, but will
						//work well enough on HW1 calcs.
						short delay;
						for(delay=0;delay<5000;delay++);
					}
					#endif
					
					WinBitmapPut(&win, ds_pt.x0, ds_pt.y0, (BITMAP*)DSIcon, A_XOR);	//erase
					if(ds_pt.x0>WinWidth(&win)-16  || ds_pt.x0<0)dx=-dx;
					if(ds_pt.y0>WinHeight(&win)-16 || ds_pt.y0<0)dy=-dy;
					ds_pt.x0+=dx;	ds_pt.y0+=dy;
					WinBitmapPut(&win, ds_pt.x0, ds_pt.y0, (BITMAP*)DSIcon, A_XOR);	//draw
				}
			}
		}
		#endif
	

	WinEndPaint(&win);
	WinClose(&win);
}

DWORD cbFormatDialog(WORD DlgId, DWORD dValue)
{  
    WORD *options=(WORD*)gBuff;
    
    switch(DlgId)
    {
    	case 1:
    		if(CheckKernel())
    		{
    			if(options[1]!=global.AntiCrashInstalled + 1)
    			{
    				DlgMessage(XR_stringPtr(XR_ERROR),XR_stringPtr(ER_CantRemoveIfKernel),0,PDB_CANCEL);
    				options[1]=global.AntiCrashInstalled + 1;
    				return DB_REDRAW_AND_CONTINUE;
    			}
    		}
    	break;
    
    };
 
	return TRUE;
}

static void DoFormatDialog(void)
{
	Access_AMS_Global_Variables;
	PACK_DAT *d=&global;
	Event event;
	WORD *options=(WORD*)gBuff;
	
	options[0]=d->hex_dat.byteswide;			//width of the hex editor
	options[1]=d->AntiCrashInstalled + 1;		//because of dialog limits, PUP_ON and PUP_OFF are off by one for BOOL variables
	options[2]=CheckResetMagicInstalled() + 1;	//because of dialog limits, PUP_ON and PUP_OFF are off by one for BOOL variables
	options[3]=d->VerboseDisassembler + 1;		//because of dialog limits, PUP_ON and PUP_OFF are off by one for BOOL variables
	
	switch(Dialog(&dlgFormat, -1, -1, NULL, options))
	{       //initialize vars
		case KB_ENTER:
			d->hex_dat.byteswide=options[0];
			d->VerboseDisassembler=options[3]-1;
					
			if(options[1]==PUP_ON)
			{
				EnableCrashProtection();
			}
			else
			{
				DisableCrashProtection();
			}
				
			if(options[2]==PUP_ON)
			{
				InstallResetMagic();
					if(!CheckResetMagicInstalled())
						DlgMessage(XR_stringPtr(XR_ERROR),XR_stringPtr(ER_ResetMagicFailedInstall),0,PDB_CANCEL);
			}
			else
			{
				RemoveResetMagic();
				if(CheckResetMagicInstalled())
					DlgMessage(XR_stringPtr(XR_ERROR),XR_stringPtr(ER_ResetMagicFailedRemove),0,PDB_CANCEL);
			}
					
			event.command=ACM_New_Formats;
			EV_sendEvent(AP_SELF, &event);
			
			pushkey(KB_F5);
			
		break;
		
		case DB_MEMFULL:
			EV_errorCode=ER_MEMORY;
		break;
	};
}

static void InstallResetMagic(void)
{
	Access_AMS_Global_Variables;
	EStackIndex oldtop;
	FILES f;
	PACK_DAT *g=&global;
	RESET_MAGIC_DAT data;
	
	data.AntiCrashInstalled=g->AntiCrashInstalled;
	data.byteswide=g->hex_dat.byteswide;
	data.VerboseDisassembler=g->VerboseDisassembler;
	
	RemoveResetMagic();
	oldtop=TokenizeSymName((BYTE *)RM_DATA_VAR, TSF_ALLOW_RESERVED);
	
	#ifdef DEBUG
		if(oldtop==NULL) DlgNotice("Debug Warning","Failed to Tokenize " RM_DATA_VAR " for Reset Magic - Install");
	#endif
	
	if(FOpen(RM_DATA_VAR, &f, FM_WRITE, RM_DATA_VAR_TYPE)==FS_OK)
	{
		if(FWrite(&data,sizeof(RESET_MAGIC_DAT),&f)!=FS_OK)
		{
			FClose(&f);
			top_estack=oldtop;
			ER_throw(ER_MEMORY);
		}
		FClose(&f);
	}
		
	TRY
		cmd_archive(top_estack);	//for some reason, this is throwing an 'var doesn't exist'
	ONERR
	ENDTRY
	
	HideResetMagicVar(TRUE);	
	top_estack=oldtop;
}

static void RemoveResetMagic(void)
{
	Access_AMS_Global_Variables;
	EStackIndex oldtop;
    
    HideResetMagicVar(FALSE);
	oldtop=TokenizeSymName((BYTE *)RM_DATA_VAR, TSF_ALLOW_RESERVED);
	
	#ifdef DEBUG
		if(oldtop==NULL) DlgNotice("Debug Warning","Failed to Tokenize " RM_DATA_VAR " for Reset Magic - Remove");
	#endif
	
	TRY
		TRY
			cmd_unarchiv(top_estack);
		FINALLY
			cmd_delvar(top_estack);
		ENDFINAL
	ONERR
		top_estack=oldtop;
		HideResetMagicVar(TRUE);
		if(errCode==ER_MEMORY)ER_throw(ER_MEMORY);
	ENDTRY
    
    HideResetMagicVar(TRUE);
	top_estack=oldtop;
}

static BOOL CheckResetMagicInstalled(void)
{
	SYM_ENTRY *sym;

	sym=DerefSym(SymFind(SYMSTR_CONST(RM_DATA_VAR));
	
	if(!sym)	//it must exist
		return FALSE;
		
	if(sym->Flags&SF_EXTMEM)	//it must be archived
			return TRUE;
		
	return FALSE;
	
	
}

//this will work once, and only once per reset
//it loads the settings saved with InstallResetMagic
static void EnforceResetMagicRules(void)
{
	static runonce=FALSE;
	PACK_DAT *g=&global;
	RESET_MAGIC_DAT dat;
	FILES f;
	
	if(runonce)return; else runonce=TRUE;
	
	FOpen(RM_DATA_VAR, &f, FM_READ, RM_DATA_VAR_TYPE);
	if(FRead(&dat,sizeof(RESET_MAGIC_DAT),&f)==FS_OK)
	{
		g->hex_dat.byteswide=dat.byteswide;
		g->VerboseDisassembler=dat.VerboseDisassembler;
		
		if(dat.AntiCrashInstalled)
			EnableCrashProtection();
		else
			DisableCrashProtection();
	}
	
	FClose(&f);
	//HideResetMagicVar(TRUE);	//the variable will loose its 'inuse' bit after a reset
	//this is done in the cm_install handler so the user never notices it...
}

//if true then set the SF_INUSE FLAG
//else unset the SF_INUSE flag
static void HideResetMagicVar(BOOL hidden)
{
	SYM_ENTRY *sym;

	sym=DerefSym(SymFind(SYMSTR_CONST(RM_DATA_VAR));
	
	if(!sym) return;

#ifdef DEBUG
	return;
#else
	if(hidden)
		sym->Flags|=SF_INUSE;			//set the flag
	else
		sym->Flags&=(~SF_INUSE);		//unset the flag
#endif
}

static void LinkPortLogger(void)
{
	FILES f;
	BYTE c;
	ULONG BytesReceived=0;
	char buff[100];
	WINDOW *w = &appW;
	WORD oldFlags=w->Flags;
	BYTE oldCurFont=w->CurFont;
	char file_name_buffer[MAX_SYM_LEN];
	char misc_buff[500];
	const BYTE types[]={GEN_DATA_TAG, 0};
	const char * const gen_data_tags[]={"log", NULL};
	
	HSYM hsym;
	SYM_ENTRY *sym;
	
	hsym=VarNew((BYTE *)&types, &gen_data_tags);		//this is extremely silly .. you can choose different types, but how in the world can i as a programmer find out which type was chosen!?
	if(hsym==H_NULL)	return;
	
	sym=DerefSym(hsym);
	
	TRY
		sym->hVal=HeapAllocThrow(8);	//this is to make HSYMtoName happy!!!! yuck!
		if(!HSYMtoName(hsym, (BYTE*)file_name_buffer))ER_throw(ER_MEMORY);
	FINALLY
		if(errCode){PASS;}
		
		HSymDel(hsym);	//we no longer need the hsym ... will recreate it with fopen.
	ENDFINAL
	
	if(FS_OK==FOpen(file_name_buffer, &f, FM_WRITE, (char *)gen_data_tags[0]))
	{
	    TRY	
	    	w->Flags|=WF_TTY;
	    	WinClr(w);
	    	
	    	sprintf(misc_buff, XR_stringPtr(XR_LinkLogMessage), file_name_buffer);
	    	WinStr(w, misc_buff);
	    	WinFont(w, F_4x6);
	    	
		    OSLinkOpen();
		    OSClearBreak();
		    
			while(!OSCheckBreak())
			{
				//i would like to do a 1 second timeout, BUT there seem to be problems if no data is recieved in the first timeout period
				while(!LIO_RecvData(&c, sizeof(BYTE), ONE_SECOND*0))	//recieve data in 1 byte chunks with infinite timeout
				{
					if(FPutC(c, &f)==FS_MEMORY)	ER_throw(ER_MEMORY);
					WinChar(w,c);
					BytesReceived++;
				}
				
				//Tell the user how many bytes we've recieved.
				sprintf(buff, XR_stringPtr(XR_BytesReceived), BytesReceived);
				ST_helpMsg(buff);			
			}
			
		FINALLY
			OSClearBreak();
			OSLinkClose();
			FClose(&f);
			
			WinFont(w, oldCurFont);
			w->Flags=oldFlags|WF_DIRTY;	//also, force a window repaint
		ENDFINAL
	}
	else
		ER_throwFrame(ER_LinkLog, pAppObj);
}

static void DisassemblyToolsDialog(void)
{
	Access_AMS_Global_Variables;
	MOVEM_DECODE *d=&global.movem_decode;
	USHORT code;
	char *txt_ptr;
	
	if(d->optList[0]==0) d->optList[0]=DECODE_RomCallToStr;
	
	switch(Dialog(&dlgMovemDecode, -1, -1, d->buff, d->optList))
	{
		case KB_ENTER:
				
			if(d->buff[0]==0) strcpy(d->buff, "0");
			
			code=StrToEStackToLong(d->buff);
			
			if(StrToEStackToLong(d->buff)>USHRT_MAX)	ER_throw(ER_ARGUMENT);
			
			
			
			if(d->optList[0]==DECODE_RomCallToStr)
			{
				if((txt_ptr=RomCallIdxToStr(code))==NULL)
				{
					DlgNotice(XR_stringPtr(XR_RomCallToStr), XR_stringPtr(XR_NoDatabase));
				}
				else
				{
					DlgNotice(XR_stringPtr(XR_RomCallToStr), txt_ptr);
				}
			}
			else
			{
				if(!code)
					ER_throw(ER_ARGUMENT);
					
				DlgNotice(XR_stringPtr(XR_movem), MovemDecoder(d->optList[0]==DECODE_PostIncrement, code));
			}
			
		break;	//end case KB_ENTER:
		
		case DB_MEMFULL:
			EV_errorCode=ER_MEMORY;
		break;
	};
}

char * DataBase(const char *var_name, const char *var_type, USHORT mode)
{
	SYM_ENTRY * sentry;

	
	if(mode==CPP_DB_OPEN)
		HeapCompress();	//if the variable is found, i want to make sure every thing is tidy before i HLock it.
	
	sentry=SymFindFirst(NULL, FO_RECURSE|FO_NOTEMPS);
	
	while(sentry)
	{
		if(!strcmp((char *)sentry->Name, var_name))
		{
			if(strcmp(var_type, (char*)HToESI(sentry->hVal) - (strlen(var_type)+1) ))
				break;
				
			if(mode==CPP_DB_OPEN)
			{
				#ifndef DEBUG
					sentry->Flags|=SF_INUSE;
				#endif

				return HLock(sentry->hVal);;
			}
			else
			{
				HeapUnlock(sentry->hVal);
				
				#ifndef DEBUG
					sentry->Flags&=(~SF_INUSE);
				#endif
				
				return NULL;
			}
		}
		
		sentry=SymFindNext();
	}
	
	return NULL;
}

static ULONG * InitializeRomCallAddrToStrDB(void)
{
	Access_AMS_Global_Variables;
	ROM_CALL_DATA_FILE *f= (ROM_CALL_DATA_FILE*)gROM_CALL_DB_PTR;
	ULONG *ptr;
	USHORT counter;
		
	if(!f)	return NULL;
	
	ptr=HeapDeref(HeapAllocHigh( (f->num_entries*sizeof(ULONG)) + sizeof(ULONG) ));
	if(!ptr)	return NULL;
	
	for(counter=0;counter<f->num_entries;counter++)
	{
		ptr[counter] = (ULONG)AMS_Global_Variables[f->rcall[counter].idx];
	}
		
	return ptr;
	
}

//this is the wrapper for the disassembler library extension
static void disassemble_one_ext_wrapper(unsigned short *pc, DASM_DAT *buff)
{	
	/*if(gROM_CALL_DB_PTR || gMEM_DAT_DB_PTR || gROM_CALL_ADDR_PTR)	//Check If the Databases are open
	{*/
		disassemble_one(pc, buff);
/*	}
	else
	{//they weren't open, so open the databases...
		OpenAllDatabases();
		disassemble_one(pc, buff);
		CloseAllDatabases();		
	}*/
}

static void OpenAllDatabases(void)
{
	if(!gROM_CALL_DB_PTR)	gROM_CALL_DB_PTR=DataBase(romcalldb_var_name, var_type, CPP_DB_OPEN);
	if(!gMEM_DAT_DB_PTR)	gMEM_DAT_DB_PTR=DataBase(memdatdb_var_name, var_type, CPP_DB_OPEN);
	if(!gROM_CALL_ADDR_PTR)	gROM_CALL_ADDR_PTR=InitializeRomCallAddrToStrDB();
}

static void CloseAllDatabases(void)
{	
	if(gROM_CALL_DB_PTR)	gROM_CALL_DB_PTR=DataBase(romcalldb_var_name, var_type, CPP_DB_CLOSE);
	if(gMEM_DAT_DB_PTR)		gMEM_DAT_DB_PTR=DataBase(memdatdb_var_name, var_type, CPP_DB_CLOSE);
			
	if(gROM_CALL_ADDR_PTR)
	{
		HeapFree(HeapPtrToHandle(gROM_CALL_ADDR_PTR));
		gROM_CALL_ADDR_PTR=NULL;
	}
}

//pass true to turn on TurboKeys
//pass false to turn it off

static void UseTurboKeys(BOOL on)
{
	static WORD init=0;
	static WORD key_delay=0;	
	static BOOL warn=0;
	
	#ifdef DEBUG
	{
		//char buff[200];
		//sprintf(buff, "init=%d kdelay=%d", init, key_delay);
		//ST_helpMsg(buff);
	}
	#endif
		
	if(on)
	{	
		if(key_delay && init)
		{
			OSInitBetweenKeyDelay(20);
			OSInitKeyInitDelay(75);
		}
		else
		{
			WORD tmp;
			
			key_delay=OSInitBetweenKeyDelay(20);
			init=OSInitKeyInitDelay(75);
			
			tmp=OSInitBetweenKeyDelay(20);
			
			if((tmp<<2)/3 == 20)
			{//on some AMS version, the correct return value is multiplied by 3/4
				key_delay=(key_delay<<2)/3;
			} 
			else if(tmp!=20)
			{//this code should never be executed  
			//since it is not known how to correct the problem, the fall back method is to NOT restore original values when the turning off the keyboard speedup
				init=key_delay=0;
				
				if(!warn)
				{
					DlgNotice("Assertion Failed", "Bug detected in OSInitBetweenKeyDelay Rom Call");
					warn=1;
				}
			}
		}
	}
	else if(init && key_delay)
	{
		OSInitBetweenKeyDelay(key_delay);
		OSInitKeyInitDelay(init);
		init=key_delay=0;
	}

}

