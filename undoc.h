#ifndef _NOT_DOCUMENTED_H_
#define _NOT_DOCUMENTED_H_
//these are functions that are either NOT documented by TI,
//or are poorly documented.
//i also have a few defines that could be useful if found in tiams.h
// $Id: undoc.h 13 2004-08-05 20:26:49Z dietsche $

#ifndef _TIAMS_H
	#error Please include tiams.h before this header file
#endif

#define FirstWindow (*(WINDOW **)AMS_Global_Variables[0])

#define PortRestore tiamsapi_419
void tiamsapi_419(void);

#define FreeHandles tiamsapi_571
short tiamsapi_571(void);

#define CU_start tiamsapi_196
CU_STATE tiamsapi_196(void);

#define CU_stop tiamsapi_197
CU_STATE tiamsapi_197(void);

#define CU_restore tiamsapi_195
void tiamsapi_195(CU_STATE);

#define EX_patch tiamsapi_346
void tiamsapi_346(void *base, void *tag_ptr);

#define AtLeastAMS(major,minor)((long const *)AMS_Global_Variables)[-1] < 1499 || ((BASECODE_PARM_BLOCK const *(* const)(void))AMS_Global_Variables[1498])()->version_number < (((major) << 8) + (minor))

//this is a documented rom call, but the implementation dosen't allow getting the address of the function
//so i have fixed the problem...
#define addr_EX_stoBCD ((char *)AMS_Global_Variables[0xC0])

#endif
 