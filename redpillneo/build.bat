del MatrixCode.bin

tigcc -Os -Wall -W -Wwrite-strings -Wpointer-arith -mpcrel -fomit-frame-pointer -mpcrel -outputbin MatrixCode.c extgraph.a
ttbin2hex -a redpillneo -ss 2 -se 1 MatrixCode.bin RedPillNeo.h

