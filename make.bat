REM %1 = Build Target (either 89 or 92)
REM %2 = path to key file for signing
REM currently does not accept parameters...

CALL clean
cls
REM Build Command Post

REM Call the Resource Compiler
rc32 -mp KFLASHr1.r

REM Call the Compiler
com68 AppInfo.c   AppInfo.s   -D_92 -Q -l -Oc1f0l3m1p1r2x1  -Xbef3IL
com68 crash.c     crash.s     -D_92 -Q -l -Oc1f0l3m1p1r2x1  -Xbef3IL
com68 dasm.c      dasm.s      -D_92 -Q -l -Oc1f0l3m1p1r2x1  -Xbef3IL
com68 dasm_driver.c dasm_driver.s      -D_92 -Q -l -Oc1f0l3m1p1r2x1  -Xbef3IL
com68 eggs.c      eggs.s      -D_92 -Q -l -Oc1f0l3m1p1r2x1  -Xbef3IL
com68 hexedit.c   hexedit.s   -D_92 -Q -l -Oc1f0l3m1p1r2x1  -Xbef3IL
com68 KFLASH.c    KFLASH.s    -D_92 -Q -l -Oc1f0l3m1p1r2x1  -Xbef3IL
com68 leakwatch.c leakwatch.s -D_92 -Q -l -Oc1f0l3m1p1r2x1  -Xbef3IL
com68 oo.c        oo.s        -D_92 -Q -l -Oc1f0l3m1p1r2x1  -Xbef3IL
com68 ram.c       ram.s       -D_92 -Q -l -Oc1f0l3m1p1r2x1  -Xbef3IL


FLINE the Rom Calls
fline AppInfo.s AppInfo.s_
fline crash.s crash.s_
fline dasm.s dasm.s_
fline dasm_driver.s dasm_driver.s_
fline eggs.s eggs.s_
fline hexedit.s hexedit.s_
fline KFLASH.s KFLASH.s_
fline leakwatch.s leakwatch.s_
fline oo.s oo.s_
fline ram.s ram.s_

REM Call the Assembler
asm68 AppInfo.s_ -Q
asm68 crash.s_ -Q
asm68 dasm.s_ -Q
asm68 dasm_driver -Q
asm68 eggs.s_ -Q
asm68 hexedit.s_ -Q
asm68 KFLASH.s_ -Q
asm68 leakwatch.s_ -Q
asm68 oo.s_ -Q
asm68 ram.s_ -Q


REM Call the Linker
link68 KFLASH.o asmcode.o AppInfo.o crash.o dasm.o eggs.o hexedit.o leakwatc.o oo.o ram.o -o cmdpost.out -Q -m -r

REM Create the Flash App
REM seems like TIFS needs to be open, and have built a project prior to this command to avoid sdkpc crashing!?
sdkpc -O3 -sgreg-92p.key 92 CMDPOST.OUT cmdpost

pause