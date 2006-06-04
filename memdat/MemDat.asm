; $Id: MemDat.asm 13 2004-08-05 20:26:49Z dietsche $

_nostub
_ti89

 xdef _nostub
 xdef _ti89

Begin:
	dc.w (LookupTableEnd-LookupTable-6)/6
LookupTable:
	dc.l $0
	dc.w .LC0-Begin
	dc.l $8
	dc.w .LC1-Begin
	dc.l $C
	dc.w .LC2-Begin
	dc.l $10
	dc.w .LC3-Begin
	dc.l $14
	dc.w .LC4-Begin
	dc.l $18
	dc.w .LC5-Begin
	dc.l $1c
	dc.w .LC6-Begin
	dc.l $20
	dc.w .LC7-Begin
	dc.l $24
	dc.w .LC8-Begin
	dc.l $28
	dc.w .LC9-Begin
	dc.l $2C
	dc.w .LC10-Begin
	dc.l $30
	dc.w .LC11-Begin

	dc.l $32
	dc.w .LC50-Begin
	dc.l $34
	dc.w .LC51-Begin

	dc.l $3C
	dc.w .LC12-Begin
	dc.l $40
	dc.w .LC13-Begin
	dc.l $60
	dc.w .LC14-Begin
	dc.l $64
	dc.w .LC15-Begin
	dc.l $68
	dc.w .LC16-Begin
	dc.l $6c
	dc.w .LC17-Begin
	dc.l $70
	dc.w .LC18-Begin
	dc.l $74
	dc.w .LC19-Begin
	dc.l $78
	dc.w .LC20-Begin
	dc.l $7c
	dc.w .LC21-Begin
	dc.l $80
	dc.w .LC22-Begin
	dc.l $84
	dc.w .LC23-Begin
	dc.l $88
	dc.w .LC24-Begin
	dc.l $8c
	dc.w .LC25-Begin
	dc.l $90
	dc.w .LC26-Begin
	dc.l $94
	dc.w .LC27-Begin
	dc.l $98
	dc.w .LC28-Begin
	dc.l $9c
	dc.w .LC29-Begin
	dc.l $a0
	dc.w .LC30-Begin
	dc.l $a4
	dc.w .LC31-Begin
	dc.l $a8
	dc.w .LC32-Begin
	dc.l $ac
	dc.w .LC33-Begin
	dc.l $b0
	dc.w .LC34-Begin
	dc.l $b4
	dc.w .LC35-Begin
	dc.l $b8
	dc.w .LC36-Begin
	dc.l $bc
	dc.w .LC37-Begin
	dc.l $c0
	dc.w .LC38-Begin
	dc.l $c8
	dc.w .LC39-Begin
	dc.l $cc
	dc.w .LC40-Begin

	dc.l $100
	dc.w .LC41-Begin

	dc.l $11F
	dc.w .LC52-Begin

	dc.l $400
	dc.w .LC42-Begin
	dc.l $401
	dc.w .LC43-Begin

	dc.l $41FF
	dc.w .LC44-Begin
	dc.l $4200
	dc.w .LC45-Begin
	dc.l $4204
	dc.w .LC46-Begin

	dc.l $4BFF
	dc.w .LC47-Begin
	dc.l $4C00
	dc.w .LC48-Begin

	dc.l $5AFF
	dc.w .LC49-Begin

	dc.l $600000
	dc.w .LC55-Begin
	dc.l $600001
	dc.w .LC56-Begin
	dc.l $600002
	dc.w .Unknown-Begin
	dc.l $600003
	dc.w .LC53-Begin
	dc.l $600004
	dc.w .Unknown-Begin
	dc.l $600005
	dc.w .LC54-Begin
	dc.l $600006
	dc.w .Unknown-Begin
	dc.l $600007
	dc.w .Unknown-Begin
	dc.l $600008
	dc.w .Unknown-Begin
	dc.l $600009
	dc.w .Unknown-Begin
	dc.l $60000A
	dc.w .Unknown-Begin
	dc.l $60000B
	dc.w .Unknown-Begin
	dc.l $60000C
	dc.w .LC57-Begin
	dc.l $60000D
	dc.w .LC58-Begin
	dc.l $60000E
	dc.w .LC59-Begin
	dc.l $60000F
	dc.w .LC60-Begin
	dc.l $600010
	dc.w .LC61-Begin
	dc.l $600012
	dc.w .LC62-Begin
	dc.l $600013
	dc.w .LC62-Begin
	dc.l $600014
	dc.w .Unknown-Begin
	dc.l $600015
	dc.w .LC64-Begin
	dc.l $600016
	dc.w .Unknown-Begin
	dc.l $600017
	dc.w .LC65-Begin
	dc.l $600018
	dc.w .LC66-Begin
	dc.l $600019
	dc.w .Unknown-Begin
	dc.l $60001A
	dc.w .LC67-Begin
	dc.l $60001B
	dc.w .LC68-Begin
	dc.l $60001C
	dc.w .LC69-Begin
	dc.l $60001D
	dc.w .LC70-Begin

	dc.l $700000
	dc.w .LC73-Begin
	dc.l $700001
	dc.w .LC73-Begin
	dc.l $700002
	dc.w .LC73-Begin
	dc.l $700003
	dc.w .LC73-Begin
	dc.l $700004
	dc.w .LC73-Begin
	dc.l $700005
	dc.w .LC73-Begin
	dc.l $700006
	dc.w .LC73-Begin
	dc.l $700007
	dc.w .LC73-Begin
	dc.l $700008
	dc.w .LC73-Begin
	dc.l $700009
	dc.w .LC73-Begin
	dc.l $70000A
	dc.w .LC73-Begin
	dc.l $70000B
	dc.w .LC73-Begin
	dc.l $70000C
	dc.w .LC73-Begin
	dc.l $70000D
	dc.w .LC73-Begin
	dc.l $70000E
	dc.w .LC73-Begin
	dc.l $70000F
	dc.w .LC73-Begin
	dc.l $700010
	dc.w .Unknown-Begin
	dc.l $700011
	dc.w .LC74-Begin
	dc.l $700012
	dc.w .LC75-Begin
	dc.l $700013
	dc.w .LC75-Begin
	dc.l $700014
	dc.w .LC76-Begin
	dc.l $700016
	dc.w .Unknown-Begin
	dc.l $700017
	dc.w .Unknown-Begin
	dc.l $700018
	dc.w .Unknown-Begin
	dc.l $700019
	dc.w .Unknown-Begin
	dc.l $70001a
	dc.w .Unknown-Begin
	dc.l $70001b
	dc.w .Unknown-Begin
	dc.l $70001C
	dc.w .Unknown-Begin
	dc.l $70001D
	dc.w .LC72-Begin
	dc.l $70001E
	dc.w .Unknown-Begin
	dc.l $70001F
	dc.w .LC77-Begin

LookupTableEnd:

Strings:
.Unknown dc.b 'Unknown',0
;.LC dc.b '',0

.LC77 dc.b 'AI & RTC Control, Contrast',0

.LC0: dc.b 'Reset Vector - Initial SSP & PC',0
.LC1: dc.b 'Bus Error Vector',0
.LC2: dc.b 'Address Error Vector',0
.LC3: dc.b 'Illegal Instruction Vector',0
.LC4: dc.b 'Zero Divide Vector',0
.LC5: dc.b 'CHK Instruction Vector',0
.LC6: dc.b 'TRAPV Instruction Vector',0
.LC7: dc.b 'Privilege Violation Vector',0
.LC8: dc.b 'Trace Vector',0
.LC9: dc.b 'Line 1010 Emulator Vector',0
.LC10: dc.b 'Line 1111 Emulator Vector',0
.LC11: dc.b 'Unassigned: Reserved by Motorola',0
.LC12: dc.b 'Uninitialized Interrupt Vector',0
.LC13: dc.b 'Unassigned: Reserved by Motorola',0
.LC14: dc.b 'Spurious Interrupt',0
.LC15: dc.b 'Level 1 Interrupt Autovector',0
.LC16: dc.b 'Level 2 Interrupt Autovector',0
.LC17: dc.b 'Level 3 Interrupt Autovector',0
.LC18: dc.b 'Level 4 Interrupt Autovector',0
.LC19: dc.b 'Level 5 Interrupt Autovector',0
.LC20: dc.b 'Level 6 Interrupt Autovector',0
.LC21: dc.b 'Level 7 Interrupt Autovector',0
.LC22: dc.b 'Trap #0 Vector',0
.LC23: dc.b 'Trap #1 Vector',0
.LC24: dc.b 'Trap #2 Vector',0
.LC25: dc.b 'Trap #3 Vector',0
.LC26: dc.b 'Trap #4 Vector',0
.LC27: dc.b 'Trap #5 Vector',0
.LC28: dc.b 'Trap #6 Vector',0
.LC29: dc.b 'Trap #7 Vector',0
.LC30: dc.b 'Trap #8 Vector',0
.LC31: dc.b 'Trap #9 Vector',0
.LC32: dc.b 'Trap #10 Vector',0
.LC33: dc.b 'Trap #11 Vector',0
.LC34: dc.b 'Trap #12 Vector',0
.LC35: dc.b 'Trap #13 Vector',0
.LC36: dc.b 'Trap #14 Vector',0
.LC37: dc.b 'Trap #15 Vector',0
.LC38: dc.b 'Unassigned: Reserved by Motorola',0
.LC39: dc.b 'AMS Jump Table Pointer',0
.LC40: dc.b 'Unassigned: Reserved by Motorola',0
.LC41: dc.b 'User Interrupt Vectors',0
.LC42: dc.b 'End of Exception Vector Table',0
.LC43 dc.b 'User Stack - Last Byte',0
.LC44 dc.b 'User Stack - First Byte',0
.LC45 dc.b '4 Byte Fence Between Stacks',0
.LC46 dc.b 'Supervisor Stack - Last Byte',0
.LC47 dc.b 'Supervisor Stack - First Byte',0
.LC48 dc.b 'Beginning of LCD Memory',0
.LC49 dc.b 'End of LCD Memory',0
.LC50 dc.b '2 Byte Identfier Used By Kernels',0
.LC51 dc.b 'Kernel Exec Function Pointer',0
.LC52 dc.b 'Last Byte of Protected Memory',0
.LC53 dc.b 'Bus Wait States (Default=$FF)',0
.LC54 dc.b 'Auto Interrupt Control Mask',0
.LC55 dc.b 'Batter Voltage Check - Bit 2',0
.LC56 dc.b 'Vector Table Protection - Bit 2',0
.LC57 dc.b 'DBus Control Bits',0
.LC58 dc.b 'DBus Status Bits',0
.LC59 dc.b 'Direct DBus Access',0
.LC60 dc.b '1 Byte DBus Buffer',0
.LC61 dc.b 'HW1 LCD Buff Addr / 8 (2 bytes)',0
.LC62 dc.b 'LCD Logical Width (64-n)*2 bytes',0
.LC63 dc.b 'LCD Logical Height (256-n) lines',0
.LC64 dc.b 'AI 1,3,5 (Speed/Enable/Disable), DMA',0
.LC65 dc.b 'AI 5 Timer  257-n sets rate',0
.LC66 dc.b 'Battery Voltage Level Trigger',0
.LC67 dc.b 'ON Key Status & ACK',0
.LC68 dc.b 'Keyboard Row Mask',0
.LC69 dc.b 'LCD row sync, sth',0
.LC70 dc.b 'LCD Voltage Mult, Scr Disable, Contrast',0
.LC71 dc.b 'Display Mem Snoop Range',0
.LC72 dc.b 'Screen, Battery',0
.LC73 dc.b 'Execution Protection - RAM',0
.LC74 dc.b 'DBus Transfer Speed?',0
.LC75 dc.b 'Execution Protection - FLASH',0
.LC76 dc.b 'RTC Related, Period=2^13 seconds',0
