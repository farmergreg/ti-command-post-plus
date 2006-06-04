REM By Greg Dietsche
REM Cleanup intermediate files
REM In some versions of TIFS running this
REM script liberally will result in better stabliity

del *.app
del *.lst
del *.l
del *.clc
del *.o
del *.map
del *.err
del *.OUT
del *.s_
del *.s
del *r1.h

REM sometimes, it is useful to comment/uncomment out the rest of these
REM del *.fso
del sdk-92p\* /Q
del sdk-89\* /Q

