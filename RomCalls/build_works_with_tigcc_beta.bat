:: $Id: build_works_with_tigcc_beta.bat 13 2004-08-05 20:26:49Z dietsche $
del RomCalls.89y
del RomCalls.9xy
tigcc romcalls.asm -outputbin
ttbin2hex -ss 2 -se 1 romcalls.z89 romcalls.hex
tthex2bin romcalls.hex romcalls.bin
ttbin2oth -89 CPDB romcalls.bin RomCalls
ttbin2oth -92 CPDB romcalls.bin RomCalls
del romcalls.bin
del romcalls.z89
del romcalls.hex
