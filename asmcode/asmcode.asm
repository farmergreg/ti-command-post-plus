; Assembly Source File
; Created 6/19/2002, 3:51:31 PM

	section ".data"

 include "os.h"

;;;;;;;;;;;;;;;;;;;;;
;;my macros... these aren't found in os.h at the moment...
;;;;;;;;;;;;;;;;;;;;;
;this macro requires that a4 be initialized with move.l $c8,a4
;prior to its use
ROM_CALL3 macro
 move.l \1*4(a4),a0
 jsr (a0)
 endm

;this macro makes use of the line 1111 emulator for making rom calls...
;There are several other F-line instructions available, but this is the most usefull at the moment
;so i have only defined a macro for this instruction
ROM_CALLF macro
 dc.w $F800+\1
 endm

;makes use of the line 1010 emulator... error codes are those listed in the calc's guide book...
ERR_THROW macro
 dc.w $A000+\1
 endm
;;;;;;;;;;;;;;;;;;;;;;
 xdef _main
 xdef _ti89
 xdef _ti92plus
 xdef _nostub
FL_getHardwareParmBloc equ $16b

;SMALL set 0

_main:
 rts
 nbcd d3
 movem.w a0-a6,-(sp)
 movem.w d0-d5,-(sp)
 
 movem.l a0-a6/d0-d7,-(sp) 
 movem.l a0-a2/a4-a6/d1-d3/d5-d7,-(sp)
 movem.l a0-a2/a4-a6/d1-d3/d5/d7,-(sp)
 movem.l a0/a2/a4/a6/a7/d0/d2/d4/d6/d7,-(sp)
 
 movem.l (sp)+,a0-a6/d0-d7
 movem.l (sp)+,a0-a2/a4-a6/d1-d3/d5-d7
 movem.l (sp)+,a0-a2/a4-a6/d1-d3/d5/d7
 movem.l (sp)+,a0/a2/a4/a6/a7/d0/d2/d4/d6/d7
 
 tst.b (a0)
 tst.l d0
 unlk a6
 unlk a0
 
 trapv
 tas (a0)+
 swap d0
 swap d7
jmb:
 or.b (a7)+,d0
 or.w (a4),d2
 or.l d3,(a4)
 or.w d2,d3
 
 sbcd d0,d1
 sbcd -(a3),-(a4)
 divu (a0),d0
 divs (a1),d3
 
 dbra d0,jma
 subq.b #8,d0
 addq.l #8,d1
 subq.w #1,d7
 
 sf d0
 scc 7(a7)
 beq.s jma
 bgt.s jma
 bsr jma
 bra.w jma
 dbra d0,jmb
  
 sub.l d1,d0
 sub.l $5678,d7
 sub.w d7,$5678
 suba.w (a7),a0
 
 suba.l a3,a3		;$97cb
 suba.l a0,a0		;$91c8
 suba.l a1,a1		;$93c9
 
 subx d0,d1
 subx.l -(a0),-(a4)
 
 cmpm.w (a1)+,(a2)+
 cmp.b (a4),d2
 cmpa.l $28,a3
 cmpa.l a2,a3
 eor.l d0,-(sp)
 
 pea jma(pc)
 jsr jma(pc)
 jmp jma(pc)
 not.w d0
jma:
 not.l 7(a5)
 not.b d1
 
 negx d0
 negx.b (a2)
 negx.l $f(a0,a5.l)
 neg d0
 neg.b (a2)
 neg.l $f(a0,a5.l)
 
 move.b #$56,d0
 move.w d0,$56
 link a0,#$fffa
 link a1,#$ffff2
 ext.w d0
 ext.l d6
 
 lea jm(pc),a0
 jsr (a0)
 jsr jm
 jmp jm
jm:
 
 chk.w (sp),d0
 
 clr.w (sp)
 
 lsl.b d0,d1
 lsr.w #1,d0
 
 roxl.l d0,d1
 roxr.b #1,d0
 
 asl.w d0,d1
 asr.l #1,d0
 
 rol.b d0,d1
 ror.w #1,d0

 rol (a4)
 ror (a5)
 
 roxl (a6)
 roxr (a7)
 
 asl (sp)
 asr -(a0)
 
 lsl (a6)
 lsr (a7)
 
 
 
 and.b (a4),d3
 and.l d0,(sp)
 
 
 mulu.w (a5),d5
 muls.w (a6),d0
 
 exg d0,a0
 exg a1,a2
 exg d3,d7
 
 abcd d1,d7
 abcd -(a0),-(a7)

 btst d0,(sp)
 btst #5,d0
 btst #6,($123456)
 btst #2,(a0)
 
 movep.w d0,0(a0)
 movep.l d0,5(a7)
 movep.l $92(a3),d4
 movep.w $255(a2),d7

 andi #4,sr
 eori #5,sr
 ori #6,sr
 
 andi #$a,ccr
 eori #$4c,ccr
 ori #$10,ccr
 
 bclr d0,(sp)
 bclr #5,d0
 bclr #6,($123456)
 bclr #2,(a0)
 
 bchg d0,(sp)
 bchg #5,d0
 bchg #6,($123456)
 bchg #2,(a0)
 
 subi.b #$32,(255)
 subi.l #$31337,d0
 subi.w #$10,(10)
 
 ori.l #$fffff1,d0
 ori.b #$F1,d7
 ori.w #$fff1,(sp)
  
 eori.b #$32,(255)
 eori.l #$31337,d0
 eori.w #$10,(10)
 
 cmpi.b #$32,(255)
 cmpi.l #$31337,d0
 cmpi.w #$10,(10)
 
 andi.l #$31337,d7
 andi.b #$12,-(sp)
 andi.w #$F0F0,(a1)
 
 addi.l #$fffff1,d0
 addi.b #$F1,d7
 addi.w #$fff1,(sp)

 
 addx.l -(a2),-(a6)
 addx.w -(a1),-(a7)
 addx.b d1,d5
 
 add.w d6,d7
 add.l (a4),d2
 add.b d6,(a5)+
 add.l (a5)+,a6
 add.w d1,a2
 
 move sr,d0
 move d0,sr
 move a0,usp
 move usp,a1

 move d0,ccr
 move.w d0,d1
 subx.w d1,d3
 subx.l -(a3),-(a7)
 bra nop_lbl
 bsr _main

 moveq.w #3,d7
nop_lbl:
 nop
 bgt.w _main
 ble.l _main

 move.l #$56,$346
 move.l (a1)+,-(a2)
 move.l $c8,a4
 move.w #12,ccr

 move.l 14(a1),d3
 move.l $7f(a3,d7.l),8(sp)
 move.l $32(pc,a0.l),d0
 move.l $54(pc),a7

 ROM_CALL3 MenuUpdate

 ifd SMALL
  move.w #10,-(sp)
  ROM_CALL3 ST_refDsp
  ROM_CALL3 ST_eraseHelp
 endc
 ifnd SMALL
  pea.l ProgName(pc)
  ROM_CALL3 ST_helpMsg
 endc

 move.l #30,-(sp)
 move.w #$ff,-(sp)
;Detect Calc, this won't work on TI-92p AMS 1.00
; ROM_CALL3 FL_getHardwareParmBloc
; cmp.l #3,2(a0)
; bne \NotTI89
;Thanks to Extended For this calc detection routine (modified to fit my needs)
 move.l    a4,d0
 andi.l    #$400000,d0
 bne.s     \NotTI89	;TI-92p
 move.l    ScrRect*4(a4),a0
 cmp.b    #239,2(a0)
 beq.s    \NotTI89	;V200

 pea $56e6
 bra \DrawLine
\NotTI89:
 pea $5a2e
\DrawLine:
 ROM_CALL3 memset

 move.l (a4),a0		;FirstWindow
 move.l (a0),a0		;dereference the pointer

\DirtyWindows:
 ori.w #$2000,(a0)	;Set Dirty Flag
 tst.l 34(a0)		;is there another window?
 movea.l 34(a0),a0	;movea doesn't affect ccr
 bne.s \DirtyWindows

 ifd SMALL
  lea 12(sp),sp
 endc
 ifnd SMALL
  lea 14(sp),sp
 endc

 movem.l (sp)+,a0-a6/d0-d7
 rts

 ifnd SMALL
ProgName: dc.b 'HSR v3.0',0
 endc

