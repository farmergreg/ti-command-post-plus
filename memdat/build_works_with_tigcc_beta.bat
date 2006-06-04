:: $Id$
del memdat.89y
del memdat.9xy
tigcc memdat.asm -outputbin
ttbin2hex -ss 2 -se 1 memdat.z89 memdat.hex
tthex2bin memdat.hex memdat.bin
ttbin2oth -89 CPDB memdat.bin memdat
ttbin2oth -92 CPDB memdat.bin memdat
del memdat.bin
del memdat.z89
del memdat.hex
