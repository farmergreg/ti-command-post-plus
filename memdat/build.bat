:: $Id: build.bat 13 2004-08-05 20:26:49Z dietsche $
del MemDat.89y
del MemDat.9xy

tigcc MemDat.asm -outputbin
ttbin2hex -ss 2 -se 1 MemDat.bin MemDat.hex
tthex2bin MemDat.hex MemDat.bin
ttbin2oth -89 CPDB MemDat.bin MemDat
ttbin2oth -92 CPDB MemDat.bin MemDat

del MemDat.bin
del MemDat.hex

