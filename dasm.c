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
// $Id: dasm.c 23 2004-08-08 22:39:12Z dietsche $

#include "tiams.h"
#include "undoc.h"
#include "kflash.h"
#include "dasm.h"

//If defined, movem statments will read movem.l -(sp),a0-a5/d0-d7 instead of something like movem.l -(sp),$1234
//#define TRANSLATE_MOVEM

//static prototypes
static char* make_hex_str(unsigned short val);
static char *make_special_single_ea(unsigned short *pc, unsigned short *size, short which_ea, short imm_bytes_wide);

//macros for individual nibble access (read left to right)
#define NIBBLE_4(n)(n&0x000f)
#define NIBBLE_3(n)((n&0x00f0)>>4)
#define NIBBLE_2(n)((n&0x0f00)>>8)
#define NIBBLE_1(n)((n&0xf000)>>12)

//For Easy EA mode decoding in disassemble_one
#define make_double_ea(sz) make_ea(pc, &count, EA_SRC_AND_DEST, sz)
#define make_single_ea(sz) make_ea(pc, &count, EA_SRC_ONLY, sz)

void disassemble_one(unsigned short *pc, DASM_DAT *buff)
{
//the invalid size array of '\n' should end up directly in front of this array in the ASM code...	
	const char	UNUSED_invalid_size[]	={'\n'};const char   SIZES[7]		={'b','w','l','\n','\n','\n','\n'};
	
	const char * const BCC[2]	={"ra","sr"};
	const char * const CC[16]	={"t","f","hi","ls","cc","cs","ne","eq",
								  "vc","vs","pl","mi","ge","lt","gt","le"
								 };//TABLE 3-19
	char *txt;
	unsigned short count=0;	//number of bytes to increment the pc after a make_ea call
	//unsigned short ea_src=*pc&0x3F;	//last 6 bits of first word of the instruction
	//unsigned short ea_dest=(*pc&0xFC0)>>6;	//second to last set of 6 bits of the first word of the instruction
	unsigned short word=*pc;
	unsigned short n1=NIBBLE_1(word);
	unsigned short n2=NIBBLE_2(word);
	unsigned short n3=NIBBLE_3(word);
	unsigned short n4=NIBBLE_4(word);
	
	txt=buff->text;
	*txt++=' ';
	buff->pc=pc;
	
	switch(n1)
	{
		case  0:	//%0000 Bit Manipulation/MOVEP/Immediate
		
		if(word==0x23c){ sprintf(txt, "andi.b #$%x,ccr",pc[1]); count=1; break; } else
		if(word==0xa3c){ sprintf(txt, "eori.b #$%x,ccr",pc[1]); count=1; break; } else
		if(word==0x3c) { sprintf(txt, "ori.b #$%x,ccr",pc[1]); count=1; break;  } else
		
		if(word==0x27c){ sprintf(txt, "andi.b #$%x,sr",pc[1]); count=1; break; } else
		if(word==0xa7c){ sprintf(txt, "eori.b #$%x,sr",pc[1]); count=1; break; } else
		if(word==0x7c) { sprintf(txt, "ori.b #$%x,sr",pc[1]);  count=1; break; }
		
		if((word&0xf038)==0x8)
		{
			if(word&0x80)
				sprintf(txt, "movep.%c d%d,$%x(a%d)", SIZES[((n3&4)>>2)+1], (n2&0xe)>>1, pc[1], n4&0x7);
			else
				sprintf(txt, "movep.%c $%x(a%d),d%d", SIZES[((n3&4)>>2)+1], pc[1], n4&0x7, (n2&0xe)>>1);
				
			count=1;
			break;
		}
				
		{//scope brackets for variables specific to these operators
			USHORT size=(n3&0xc)>>2;	//helps out the cases under the following switch statement
			switch(word&0xff00)
			{	
				case 0x600:
						switch(size)
						{
							case 0:
								count=1;
								sprintf(txt, "addi.b #$%x,%s", (UCHAR)pc[1], make_single_ea(IMM_BYTE)); 
								break;
							case 1:
								count=1;
								sprintf(txt, "addi.w #$%x,%s", pc[1], make_single_ea(IMM_WORD)); 
								break;
							case 2:
								count=2;
								sprintf(txt, "addi.l #$%lx,%s", *(ULONG*)&pc[1], make_single_ea(IMM_LONG)); 
								break;
							default:
								sprintf(txt,"dc.w $%x",word);
								break;
						};
					break;
				
				case 0x200:
					switch(size)
					{
						case 0:
							count=1;
							sprintf(txt, "andi.b #$%x,%s", (UCHAR)pc[1], make_single_ea(IMM_BYTE)); 
							break;
						case 1:
							count=1;
							sprintf(txt, "andi.w #$%x,%s", pc[1], make_single_ea(IMM_WORD)); 
							break;
						case 2:
							count=2;
							sprintf(txt, "andi.l #$%lx,%s", *(ULONG*)&pc[1], make_single_ea(IMM_LONG)); 
							break;
						default:
							sprintf(txt,"dc.w $%x",word);
							break;
					};
					break;
			
				case 0xc00:
					switch(size)
					{
						case 0:
							count=1;
							sprintf(txt, "cmpi.b #$%x,%s", (UCHAR)pc[1], make_single_ea(IMM_BYTE)); 
							break;
						case 1:
							count=1;
							sprintf(txt, "cmpi.w #$%x,%s", pc[1], make_single_ea(IMM_WORD)); 
							break;
						case 2:
							count=2;
							sprintf(txt, "cmpi.l #$%lx,%s", *(ULONG*)&pc[1], make_single_ea(IMM_LONG)); 
							break;
						default:
							sprintf(txt,"dc.w $%x",word);
							break;
					};
					break;
				
				case 0xa00:
					switch(size)
					{
						case 0:
							count=1;
							sprintf(txt, "eori.b #$%x,%s", (UCHAR)pc[1], make_single_ea(IMM_BYTE)); 
							break;
						case 1:
							count=1;
							sprintf(txt, "eori.w #$%x,%s", pc[1], make_single_ea(IMM_WORD)); 
							break;
						case 2:
							count=2;
							sprintf(txt, "eori.l #$%lx,%s", *(ULONG*)&pc[1], make_single_ea(IMM_LONG)); 
							break;
						default:
							sprintf(txt,"dc.w $%x",word);
							break;
					};
					break;
				
				case 0x0:
					switch(size)
					{
						case 0:
							count=1;
							sprintf(txt, "ori.b #$%x,%s", (UCHAR)pc[1], make_single_ea(IMM_BYTE)); 
							break;
						case 1:
							count=1;
							sprintf(txt, "ori.w #$%x,%s", pc[1], make_single_ea(IMM_WORD)); 
							break;
						case 2:
							count=2;
							sprintf(txt, "ori.l #$%lx,%s", *(ULONG*)&pc[1], make_single_ea(IMM_LONG)); 
							break;
						default:
							sprintf(txt,"dc.w $%x",word);
							break;
					};
					break;
				
				case 0x400:
					switch(size)
					{
						case 0:
							count=1;
							sprintf(txt, "subi.b #$%x,%s", (UCHAR)pc[1], make_single_ea(IMM_BYTE)); 
							break;
						case 1:
							count=1;
							sprintf(txt, "subi.w #$%x,%s", pc[1], make_single_ea(IMM_WORD)); 
							break;
						case 2:
							count=2;
							sprintf(txt, "subi.l #$%lx,%s", *(ULONG*)&pc[1], make_single_ea(IMM_LONG)); 
							break;
						default:
							sprintf(txt,"dc.w $%x",word);
							break;
					};
					break;
				
				default:
				//handle other possibilities here				
					switch(word&0xffc0)
					{
						case 0x840:
							count=1;
							sprintf(txt, "bchg #$%x,%s", pc[1], make_single_ea(IMM_LONG));
							break;
						case 0x880:
							count=1;
							sprintf(txt, "bclr #$%x,%s", pc[1], make_single_ea(IMM_LONG));
							break;
						case 0x8c0:
							count=1;
							sprintf(txt, "bset #$%x,%s", pc[1], make_single_ea(IMM_LONG));
							break;
						case 0x800:
							count=1;
							sprintf(txt, "btst #$%x,%s", pc[1], make_single_ea(IMM_LONG));
							break;
							
						default:
						//handle other possibilities here						
							switch(word&0x1c0)
							{
								case 0x140:
									sprintf(txt, "bchg d%d,%s", (n2&0xe)>>1, make_single_ea(IMM_LONG));
									break;
								case 0x180:
									sprintf(txt, "bclr d%d,%s", (n2&0xe)>>1, make_single_ea(IMM_LONG));
									break;
								case 0x1c0:
									sprintf(txt, "bset d%d,%s", (n2&0xe)>>1, make_single_ea(IMM_LONG));
									break;
								case 0x100:
									sprintf(txt, "btst d%d,%s", (n2&0xe)>>1, make_single_ea(IMM_LONG));
									break;
								default:
									sprintf(txt,"dc.w $%x",word);
									break;
							};
						break;
					};
			};//end switch
		}//end scope brackets

		break;
		
		case  1:	//%0001 Move Byte
			sprintf(txt,"move.b %s", make_double_ea(IMM_BYTE));
			break;
		case  2:	//%0010 Move Long
			if((word&0x1c0)==0x40)
			{//scope brackets for special rom call name guessing code...
				char *ptr=RomCallIdxToStr(pc[1]>>2);
				
				if((word&0x38)==0x28 && ptr && (word&7)!=7)	//only try if mode is 101, the lookup was a success and we are not using a7
				{
					sprintf(txt,"movea.l %s ;%s", make_double_ea(IMM_LONG), ptr);
				}
				else
					sprintf(txt,"movea.l %s", make_double_ea(IMM_LONG));
			}
			else
				sprintf(txt,"move.l %s", make_double_ea(IMM_LONG));
			break;
			
		case  3:	//%0011 Move Word
			if((word&0x1c0)==0x40)
				sprintf(txt,"movea.w %s", make_double_ea(IMM_WORD));
			else
				sprintf(txt,"move.w %s", make_double_ea(IMM_WORD));
			break;
			
		case  4:	//%0100 Miscellaneous
			switch(word)
			{//handle op codes with no operands
			
				case 0x4E70:	//RESET
					strcpy(txt,"reset");
					break;
				case 0x4E71:	//NOP
					strcpy(txt,"nop");
					break;
				case 0x4E72:	//STOP
					sprintf(txt, "stop #$%x",pc[1]);
					count=1;
					break;
				case 0x4E73:	//RTE
					strcpy(txt,"rte");
					break;
				case 0x4E75:	//RTS
					strcpy(txt,"rts");
					break;
				case 0x4e76:	//TRAPV
					strcpy(txt,"trapv");
					break;
				case 0x4E77:	//RTR
					strcpy(txt,"rtr");
					break;
				case 0x4AFC:	//ILLEGAL
					strcpy(txt,"illegal");
					break;
	
				default:
				
					if((word&0xfff8)==0x4e50){ sprintf(txt, "link a%d,#$%x", word&7, pc[1]); count=1; break; } else
					//if((word&0xfff8)==0x4808){ sprintf(txt, "link a%d,#$%lx", word&7, *(ULONG*)&pc[1]); count=2; break; } else	//not legal on the M68000
					if((word&0xfff8)==0x4840){ sprintf(txt, "swap.w d%d",n4&7); break; } else
					if((word&0xfff8)==0x4e58){ sprintf(txt, "unlk a%d", n4&7); break; } else
					
					if((word&0xFFF0)==0x4e40){ sprintf(txt,"trap #%d",(unsigned short)word&0xF); break; } else
					if((word&0xFFF0)==0x4E60)
					{
						if(n4&0x8)
						{
							sprintf(txt,"move.l usp,a%d",n4&0x7);
							break;
						}
						else
						{
							sprintf(txt,"move.l a%d,usp",n4&0x7);
							break;
						}
					} else
					
					switch(word&0xFFC0)
					{
						case 0x4800:
							sprintf(txt,"nbcd %s",make_single_ea(IMM_WORD));
							break;
							
						case 0x44c0:
							sprintf(txt,"move.w %s,ccr",make_single_ea(IMM_WORD));
							break;
						
						case 0x40C0:
							sprintf(txt,"move.w sr,%s",make_single_ea(IMM_WORD));
							break;
						
						case 0x46C0:
							sprintf(txt,"move.w %s,sr",make_single_ea(IMM_WORD));
							break;
						
						case 0x4ec0: 
							//sprintf(txt, "jmp %s", make_single_ea(IMM_LONG));
							sprintf(txt, "jmp %s", make_special_single_ea(pc, &count, EA_SRC_ONLY, IMM_LONG));
							break;
							
						case 0x4e80:
							//sprintf(txt, "jsr %s", make_single_ea(IMM_LONG));
							sprintf(txt, "jsr %s", make_special_single_ea(pc, &count, EA_SRC_ONLY, IMM_LONG));
							break;
						
						case 0x4840:
							sprintf(txt, "pea %s", make_single_ea(IMM_LONG));
							break;
						
						case 0x4ac0:
							sprintf(txt, "tas.b %s", make_single_ea(IMM_BYTE));
							break;
							
						default:
							if((word&0xfe38)==0x4800)
							{
								short opmode = ((word&0xc0)>>6)-1;
								
								if(opmode==2 || opmode==3)
								{
										sprintf(txt, "ext.%c d%d", SIZES[opmode], n4&7);
										break;
								}
							}
							else if((word&0xfb80)==0x4880)
							{//movem
								
								//#ifdef TRANSLATE_MOVEM
									const char movem_txt[]="movem.%c %s,%s";
								//#endif	//TRANSLATE_MOVEM
								
								count=1;
								
								if(global.VerboseDisassembler)
								{
									if(n2&4)
										sprintf(txt, movem_txt, SIZES[(n3>>2)-1], make_single_ea(IMM_LONG), MovemDecoder(n2&4, pc[1]));
									else
										sprintf(txt, movem_txt, SIZES[(n3>>2)-1], MovemDecoder(n2&4, pc[1]), make_single_ea(IMM_LONG));
								}
								else	//TRANSLATE_MOVEM
								{
									if(n2&4)
										sprintf(txt, "movem.%c %s,#$%x", SIZES[(n3>>2)-1], make_single_ea(IMM_LONG), pc[1]);	//movem_reg_list(n2&4, pc[1])
									else
										sprintf(txt, "movem.%c #$%x,%s", SIZES[(n3>>2)-1], pc[1], make_single_ea(IMM_LONG));	//movem_reg_list(n2&4, pc[1])
								}	//TRANSLATE_MOVEM

								break;
							}
							else
							if((word&0xff00)==0x4200){ sprintf(txt, "clr.%c %s", SIZES[n3>>2], make_single_ea(n3>>2)); break; } else
							if((word&0xff00)==0x4a00){ sprintf(txt, "tst.%c %s", SIZES[n3>>2], make_single_ea(n3>>2)); break; } else
							if((word&0xff00)==0x4400){ sprintf(txt, "neg.%c %s", SIZES[n3>>2], make_single_ea(n3>>2)); break; } else
							if((word&0xff00)==0x4000){ sprintf(txt, "negx.%c %s", SIZES[n3>>2], make_single_ea(n3>>2)); break; } else
							if((word&0xff00)==0x4600){ sprintf(txt, "not.%c %s", SIZES[n3>>2], make_single_ea(n3>>2)); break; } else
							if((word&0xf1c0)==0x41c0){ sprintf(txt, "lea %s,a%d", make_single_ea(IMM_LONG), n2>>1); break; } else
							if((word&0xf040)==0x4000){ sprintf(txt, "chk.%c %s,d%d", SIZES[((word&0x180)>>7)==3?1:2], make_single_ea(((word&0x180)>>7)==3?1:2), n2>>1); break; }	//the long word format is not supported by the MC68000, but i have supported it here....
							
							sprintf(txt,"dc.w $%x",word);
							break;
					};//switch(word&0xFFC0)
			};//switch(word)
			break;
			
		case  5:	//%0101 ADDQ/SUBQ/Scc/DBcc
		{//scope brackets
			USHORT size=n3>>2;
			
			if((word&0xf0f8)==0x50c8)
			{
				//sprintf(txt, "db%s d%d,#$%x  ($%lx)",n2==1?BCC[0]:CC[n2], n4&7, pc[1], (ULONG)pc+(signed short)pc[1]+2);
				sprintf(txt, "db%s d%d,$%lx",n2==1?BCC[0]:CC[n2], n4&7, (ULONG)pc+(signed short)pc[1]+2);
				count=1;
				break;
			}else
			if(size==3)
			{
				sprintf(txt, "s%s %s", CC[n2], make_single_ea(IMM_LONG));
				break;
			}else
			{
				if(n2&1)
				{
					sprintf(txt, "subq.%c #$%x,%s", SIZES[size], (n2>>1)==0?8:n2>>1, make_single_ea(size));
					break;
				}
				else
				{
					sprintf(txt, "addq.%c #$%x,%s", SIZES[size], (n2>>1)==0?8:n2>>1, make_single_ea(size));
					break;
				}
			}
			break;
		}//end scope brackets
		case  6:	//%0110 Bcc/BSR
			{
				signed short displacement=(char)pc[0];
				char displacement_type='b';

				if(!displacement)
				{
					//16 bit displacement field present
					displacement=(signed short)pc[1];
					displacement_type='w';
					count=1;
				}

				displacement=displacement>>1;	// /=2;
				displacement++;
				sprintf(txt,"b%s.%c $%lx",n2<2?BCC[n2]:CC[n2],displacement_type,(unsigned long)&pc[displacement]);
				
			}
		
			break;
			
		case  7:	//%0111 MOVEQ
			sprintf(txt,"moveq.l #$%x,d%d",word&0xff, n2>>1);
			break;
			
		case  8:	//%1000 OR/DIV/SBCD
			if((word&0xf1f0)==0x8100)
			{
				if(n4&8)
					sprintf(txt, "sbcd -(a%d),-(a%d)", n4&7, n2>>1);
				else
					sprintf(txt, "sbcd d%d,d%d", n4&7, n2>>1);
				
				break;
			}else
			if((word&0x1c0)==0x1c0)
			{
				sprintf(txt, "divs.w %s,d%d", make_single_ea(IMM_WORD), n2>>1);
				break;
			}else
			if((word&0x1c0)==0xc0)
			{
				sprintf(txt, "divu.w %s,d%d", make_single_ea(IMM_WORD), n2>>1);
				break;
			}else
			{
				if(n2&1)
					sprintf(txt, "or.%c d%d,%s", SIZES[n3>>2], n2>>1, make_single_ea(n3>>2));
				else
					sprintf(txt, "or.%c %s,d%d", SIZES[n3>>2], make_single_ea(n3>>2), n2>>1);
				
				break;
			}
			break;		
		case  9:	//%1001 SUB/SUBX/SUBA
		{//scope brackets
			USHORT reg=n2>>1;
			
			if((word&0xf130)==0x9100 && n3<=0x8)	//make sure the size is in range ... sub x handles (n3>>2) must not be larger than 0b10
			{
				if(n4&0x8)	//check bit 4
				{
					 sprintf(txt,"subx.%c -(a%d),-(a%d)",SIZES[n3>>2], n4&7, reg);
					 break;
				}
				else
				{
					sprintf(txt,"subx.%c d%d,d%d",SIZES[n3>>2], n4&7, reg);
					break;
				}
			}
			else
			{
				USHORT opmode=(word&0x1c0)>>6;
				if(opmode==0x3 || opmode==0x7)
				{
					sprintf(txt, "suba.%c %s,a%d", SIZES[opmode==3?1:2], make_single_ea(opmode==3?1:2), reg);
					break;
				}
				else
				{
					if(opmode&4)
						sprintf(txt, "sub.%c d%d,%s", SIZES[opmode&3], reg, make_single_ea(opmode&3));
					else
						sprintf(txt, "sub.%c %s,d%d", SIZES[opmode&3], make_single_ea(opmode&3), reg);
				}
			}
			}//end scope brackets
			break;
			
		case 10:	//%1010 (Unassigned)
			//sprintf(txt,"dc.w $%x ;Line $A Exception",word);
			sprintf(txt, "ER_throw $%x ;%s",word&~0xa000, find_error_message(word&~0xa000));
			break;
			
		case 11:	//%1011 CMP/EOR
			{//scope brackets
				USHORT reg=n2>>1;
				USHORT opmode=(word&0x1c0)>>6;
				USHORT cmpa_size=opmode==3?1:2;

				if(opmode<3){ sprintf(txt, "cmp.%c %s,d%d", SIZES[opmode], make_single_ea(opmode), reg); break; } else
				if(opmode==3 || opmode==7){ sprintf(txt, "cmpa.%c %s,a%d", SIZES[cmpa_size], make_single_ea(cmpa_size), reg); break; } else
				if((word&0xf138)==0xb108) { sprintf(txt, "cmpm.%c (a%d)+,(a%d)+", SIZES[n3>>2], n4&7, reg); break; } else
				sprintf(txt, "eor.%c d%d,%s", SIZES[opmode&3], reg, make_single_ea(opmode&3));
			break;	
			}//end scope brackets
		case 12:	//%1100 AND/MUL/ABCD/EXG
			{//scope brackets for some nice locals
		USHORT reg=(n2&0xe)>>1;
		
		//ABCD
			if((word&0xf1f0)==0xc100)
			{
				if(n4&8)
					sprintf(txt, "abcd -(a%d),-(a%d)", n4&7, reg);
				else
					sprintf(txt, "abcd d%d,d%d", n4&7, reg);
					
				break;
			}
		//MULU.w
			else if((word&0xf1c0)==0xc0c0)
			{
				sprintf(txt, "mulu.w %s,d%d", make_single_ea(IMM_WORD), reg);
				break;
			}
		//MULS.w
			else if((word&0xf1c0)==0xc1c0)
			{
				sprintf(txt, "muls.w %s,d%d", make_single_ea(IMM_WORD), reg);
				break;
			}
		//EXG
			else if((word&0xf100)==0xc100)
			{
				switch(word&0xf8)
				{
					case 0x40:	//data
						sprintf(txt, "exg d%d,d%d", reg, word&7);
						break;
					case 0x48:	//address
						sprintf(txt, "exg a%d,a%d", reg, word&7);
						break;
					case 0x88:	//both
						sprintf(txt, "exg d%d,a%d", reg, word&7);				
						break;
					default:
				//its invalid for exg, so it must be AND, and by virtue of word&0x100 being tested, i hereby delclare thee as and dx,ea
							sprintf(txt, "and.%c d%d,%s" , SIZES[(n3&0xc)>>2], reg, make_single_ea((n3&0xc)>>2));
						break;				
				};
				break;
			}
			else
			{//when all else fails, it must be "and ea,dx"
				sprintf(txt, "and.%c %s,d%d" , SIZES[(n3&0xc)>>2], make_single_ea((n3&0xc)>>2), reg);
			}
			
			}//end scope brackets
			break;
		case 13:	//%1101 ADD/ADDX
		{//scope brackets
			USHORT size=n3>>2;
			USHORT srcreg=word&7;
			USHORT destreg=n2>>1;
			
			if((word&0xF130)==0xD100 && (word&0x1c0)!=0x1c0)
			{//ADDX
				if(n4&8)
				{
					sprintf(txt,"addx.%c -(a%d),-(a%d)", SIZES[size], srcreg, destreg);
				}
				else
				{
					sprintf(txt,"addx.%c d%d,d%d", SIZES[size], srcreg, destreg);
				}

			}
			else
			{//ADD, ADDA
				size=(word&0x1c0)>>6;
				if(n2&1)//byte #8 (opmode)
				{
					if(size==0x7)
						sprintf(txt, "adda.l %s,a%d", make_single_ea(IMM_LONG), destreg);
					else
						sprintf(txt, "add.%c d%d,%s", SIZES[size&3], destreg, make_single_ea(size&3));
				}
				else
				{
					if(size==0x3)
						sprintf(txt, "adda.w %s,a%d", make_single_ea(IMM_WORD), destreg);
					else
						sprintf(txt, "add.%c %s,d%d", SIZES[size&3], make_single_ea(size&3), destreg);
				}
			}
		}//end scope brackets
			break;
		case 14:	//%1110 Shift/Rotate
		{//scope brackets
			USHORT dir=n2&1;
			USHORT ir=(n3>>1)&1;
			USHORT count_or_reg=n2>>1;
			USHORT reg=n4&7;
			USHORT size=n3>>2;
			const char ea_str[]="%s%c.w %s";
			const char dxdy_str[]="%s%c.%c d%d,d%d";
			const char imm_str[]="%s%c.%c #%d,d%d";
			
			const char direction[2]={'r','l'};
			
			//check ea only
			if((word&0xfec0)==0xe0c0)
			{
				sprintf(txt, ea_str, "as", direction[dir], make_single_ea(IMM_WORD));
				break;
			} else
			if((word&0xcfec0)==0xe2c0)
			{
				sprintf(txt,ea_str, "ls", direction[dir], make_single_ea(IMM_WORD));
				break;
			} else
			if((word&0xcfec0)==0xe6c0)
			{
				sprintf(txt,ea_str, "ro", direction[dir], make_single_ea(IMM_WORD));
				break;
			}else
			if((word&0xcfec0)==0xe4c0)
			{
				sprintf(txt,ea_str, "rox", direction[dir], make_single_ea(IMM_WORD));
				break;
			}
			
			//prepare for the last tests...
			//in terms of x, 0 really means 8 if we are doing an #$x,dy instruction
			if(!ir) count_or_reg=count_or_reg==0?8:count_or_reg;
			
			switch(word&0xf018)
			{
				case 0xe000:
					if(ir)
						sprintf(txt, dxdy_str, "as", direction[dir], SIZES[size], count_or_reg, reg);
					else
						sprintf(txt, imm_str, "as", direction[dir], SIZES[size], count_or_reg, reg);
				break;
				case 0xe008:
					if(ir)
						sprintf(txt, dxdy_str, "ls", direction[dir], SIZES[size], count_or_reg, reg);
					else
						sprintf(txt, imm_str, "ls", direction[dir], SIZES[size], count_or_reg, reg);
				break;
				case 0xe018:
					if(ir)
						sprintf(txt, dxdy_str, "ro", direction[dir], SIZES[size], count_or_reg, reg);
					else
						sprintf(txt, imm_str, "ro", direction[dir], SIZES[size], count_or_reg, reg);
				break;
				case 0xe010:
					if(ir)
						sprintf(txt, dxdy_str, "rox", direction[dir], SIZES[size], count_or_reg, reg);
					else
						sprintf(txt, imm_str, "rox", direction[dir], SIZES[size], count_or_reg, reg);
				break;
				default:
					sprintf(txt,"dc.w $%x",word);
				break;
			};
			}//end scope brackets
			break;
			
		case 15:	//%1111 (Unassigned)
			//sprintf(txt,"dc.w $%x ;Line $F Exception",word);
			if(word==0xFFF0)
			{
				sprintf(txt,"F_bsr $%lx",(*(ULONG*)&pc[1])+ pc - 2);
				count=2;
			}
			else if(word==0xFFF2)
			{
				USHORT rcall=pc[1]>>2;
				char *ptr=RomCallIdxToStr(rcall);
				if(ptr)
					sprintf(txt,"FCall $%x ;%s", rcall, ptr);
				else
					sprintf(txt,"FCall $%x", rcall);
				count=1;
			}
			else if(word==(0xF800 + 0x7F1))
			{
				sprintf(txt,"F_bra $%lx",(*(ULONG*)&pc[1])+ pc - 2);
				count=2;
			}
			else
			{
				USHORT rcall=word-0xF800;
				char *ptr=RomCallIdxToStr(rcall);
				
				if(ptr)
					sprintf(txt,"FCall $%x ;%s",rcall, ptr);
				else
					sprintf(txt,"FCall $%x",rcall);
			}
				
			break;
			
		default:	//handle unknown op code as data
			sprintf(txt,"dc.w $%x",word);
			break;
	}
	
	if(strchr(txt,'\n'))	//the \n signals that an invalid opcode was detected
	{
		sprintf(txt,"dc.w $%x",word);
		count=0;
	}
	
	buff->pc+=(count+1);
	return;
}

//this function wrapps make_ea, and provides rom_call translation for instructions such as jmp and jsr when possible
static char *make_special_single_ea(unsigned short *pc, unsigned short *size, short which_ea, short imm_bytes_wide)
{
	char *dasm;
	char *rom_call;
	char buff[1024];
	ULONG addr=0;
	USHORT sz=*size+1;
	USHORT reg=pc[0]&7;

	dasm=make_ea(pc, size, which_ea, imm_bytes_wide);
	
	if( ((pc[0]&0x38)>>3) == 7)	//check if mode=%111
	{
		switch(reg)
		{
			case 0:	//%000
				addr=(ULONG)pc[sz];
			break;
			
			case 1:	//%001
				addr=*(unsigned long*)&pc[sz];
			break;
			
			case 2:	//%010
				addr=(ULONG)pc + (short)pc[sz];
			break;
			
			default:
				return dasm;
			break;
		}
	}
	
	rom_call=ABSAddressToRomCall((void*)addr);
	
	if(rom_call && addr)
	{
		sprintf(buff, " ;%s", rom_call);
		strcat(dasm, buff);
	}
	
	return dasm;
}

//this function is recursive under some situations
//pc=current program counter
//size=should be initialized to zero normally, and will contain the offset to the next instruction
//		upon return	
//which_ea=EA_SRC_ONLY if only a src ea is present; if src and dest ea are present, pass EA_SRC_AND_DEST
//imm_bytes_wide=IMM_BYTE, IMM_WORD, or IMM_LONG depending on the instruction size (b,w,l)
char *make_ea(unsigned short *pc, unsigned short *size, short which_ea, short imm_bytes_wide)
{
	const char * const EA_MODE[5] ={"d%d",				//Dn			0
									"a%d",				//An			1
									"(a%d)",			//(An)			2
									"(a%d)+",			//(An)+			3
									"-(a%d)",			//-(An)			4
									};
	const char err_flag[]="\n";	// the character \n is used to signal an error condition
	static char buff[50];
	char *txt;
	unsigned short mode;
	unsigned short reg;
	unsigned short tmp_size=*size + 1;
	static short self_call=FALSE;
	
	short ex_reg,ex_reg_displacement;	//used for d8(an,xn) and similar
	char ex_reg_type, ex_reg_size;		//used for d8(an,xn) and similar
    
    if(self_call)
    {
    	self_call=FALSE;
    	txt=&buff[strlen(buff)];
    	*txt++=',';
    	
    	reg=(*pc&0xE00)>>9;
		mode=(*pc&0x1C0)>>6;
    }
    else
    {
    	txt=buff;
    	
    	mode=(*pc&0x38)>>3;
		reg=*pc&0x7;
    }

	switch(mode==7?mode+reg:mode)
	{
		case 0:case 1:case 2:case 3:case 4:
			sprintf(txt,EA_MODE[mode],reg);
			break;
		case 5:
			//sprintf(txt,"$%x(a%d)",pc[tmp_size],reg);
			sprintf(txt,"%s(a%d)",make_hex_str(pc[tmp_size]),reg);
			(*size)++;
			break;
		case 6:
			ex_reg_displacement=pc[tmp_size]&0xff;
			ex_reg_type=pc[tmp_size]&0x8000?'a':'d';
			ex_reg=(pc[tmp_size]&0x7000)>>12;
			ex_reg_size=pc[tmp_size]&0x800?'l':'w';
			//sprintf(txt,"$%x(a%d,%c%d.%c)", ex_reg_displacement, reg, ex_reg_type, ex_reg, ex_reg_size);
			sprintf(txt,"%s(a%d,%c%d.%c)", make_hex_str(ex_reg_displacement), reg, ex_reg_type, ex_reg, ex_reg_size);
			(*size)++;
			break;
		case 7:	//.w
			sprintf(txt,"($%x).w",pc[tmp_size]);
			(*size)++;
			break;
		case 8:	//.l
			sprintf(txt,"($%lx).l",*(unsigned long*)&pc[tmp_size]);
			(*size)+=2;
			break;
		case 9:
			//sprintf(txt,"$%x(pc)",pc[tmp_size]);
			sprintf(txt,"%s(pc)",make_hex_str(pc[tmp_size]));
			(*size)++;
			break;
		case 10:
			ex_reg_displacement=pc[tmp_size]&0xff;
			ex_reg_type=pc[tmp_size]&0x8000?'a':'d';
			ex_reg=(pc[tmp_size]&0x7000)>>12;
			ex_reg_size=pc[tmp_size]&0x800?'l':'w';
			//sprintf(txt,"$%x(pc,%c%d.%c)", ex_reg_displacement, ex_reg_type, ex_reg, ex_reg_size);
			sprintf(txt,"%s(pc,%c%d.%c)", make_hex_str(ex_reg_displacement), ex_reg_type, ex_reg, ex_reg_size);
			(*size)++;
			break;
		case 11:
			switch(imm_bytes_wide)
			{
				case 0:case 1:	//immediate byte or word
					sprintf(txt,"#$%x",pc[tmp_size]);
					(*size)++;
					break;
				case 2:			//immediate long
					sprintf(txt,"#$%lx",*(unsigned long*)&pc[tmp_size]);
					(*size)+=2;
					break;
				default:
					//sprintf(txt,"ea error imm_bytes_wide=%d",imm_bytes_wide);
					strcpy(txt, err_flag);
					break;
			}
			break;
		default:
			//sprintf(txt,"ea error: mode+reg=0x%x",mode);
			strcpy(txt, err_flag);
			break;
	};
    
    if(which_ea)
    {
    	self_call=TRUE;
    	make_ea(pc, size, 0, imm_bytes_wide);
    }

	return txt;
}

static char* make_hex_str(unsigned short val)
{
	char *str=&gBuff[300];		//this is a nasty hack to avoid problems with the movea.l special rom call guessing code

	#ifdef DEBUG
		ULONG _blen_=MISC_BUFF_LEN;
		if(_blen_<325)
		{
			DlgNotice("Debug Error","make_hex_str requires a longer buffer!");
		}
	#endif
	
	
	if(val == 0x8000)
		strcpy(str, "-$8000");
	else if(val & 0x8000)
		sprintf(str, "\xad$%x", (0-val) & 0x7fff);
	else
		sprintf(str, "$%x", val & 0x7fff);

	return str;
}

//The translation dialog relies on these routines
//#ifdef TRANSLATE_MOVEM
static USHORT MovemDecoderBitSwap(USHORT val)
{
	USHORT x,y,result;
	
	for(x=result=0,y=15;x<16;x++,y--)
		if(val&(1<<x))
			result|=1<<y;
			
	return result;
}

char* MovemDecoder(USHORT dr, WORD list)
{
	static char buff[50];
	USHORT pos=0;
	USHORT shift;
	
	if(!dr)list=MovemDecoderBitSwap(list);
	
//The Data Registers
	for(shift=0;shift<8;shift++)
	{
		if(list&(1<<shift))	//test the bit
		{
			if(shift!=7 && list&(1<<(shift+1)))
			{
				buff[pos++]='d';
				buff[pos++]='0' + shift;
				buff[pos++]='-';
			
				while(list&(1<<shift) && shift<8)shift++;
				shift--;
			}
			
			buff[pos++]='d';
			buff[pos++]='0' + shift;
			buff[pos++]='/';
		}
	}

	#ifdef _92
		if(buff[pos-1]=='/')
		{
			buff[pos-1]=' ';
			buff[pos++]='/';	//the extra spaces make long strings such as 0habab break correctly in DlgNotice
			buff[pos++]=' ';
		}
	#endif		//_92
	
//The Address Registers
	for(shift=8;shift<17;shift++)
	{
		if(list&(1<<shift))	//test the bit
		{
			if(shift!=16 && list&(1<<(shift+1)))
			{
				buff[pos++]='a';
				buff[pos++]='0' + shift - 8;
				buff[pos++]='-';
			
				while(list&(1<<shift) && shift<17)shift++;
				shift--;
			}
			
			buff[pos++]='a';
			buff[pos++]='0' + shift - 8;
			buff[pos++]='/';
		}
	}
	
	#ifdef _92
		if(buff[pos-1]==' ')	buff[pos-3]=0;
	#endif
	
	buff[pos-1]=0;
	
	return buff;
}
//#endif //TRANSLATE_MOVEM

char * RomCallIdxToStr(register unsigned short key)
{
	register ROM_CALL_DATA_FILE *array;
	register unsigned short mid;
	register unsigned short first=0;
	register unsigned short last;


	array=(ROM_CALL_DATA_FILE *)gROM_CALL_DB_PTR;
	if(!array)	return NULL;
	
	last=array->num_entries;
	
	while(first <= last)
	{
		mid=(first+last)>>1;
		
		if (key>array->rcall[mid].idx)		first=mid+1;
		else if (key<array->rcall[mid].idx)	last=mid-1;
		else
		{
			strcpy(gBuff, (char *)array + array->rcall[mid].str_offset + 2);
			return gBuff;
		}
	}
		
	return XR_stringPtr(XR_NotFound);
}	

char *ABSAddressToRomCall(register void *address)
{
	register unsigned short last;
	register USHORT counter;
	
	if(gROM_CALL_ADDR_PTR)
	{
		register ROM_CALL_DATA_FILE *f=(ROM_CALL_DATA_FILE*)gROM_CALL_DB_PTR;
		
		last=f->num_entries;
		
		for(counter=0;counter<last;counter++)
		{
			if(gROM_CALL_ADDR_PTR[counter]==(ULONG)address)
			{
				strcpy(gBuff, (char *)f + f->rcall[counter].str_offset + 2);
				return gBuff;
			}
		}
	}
	
	return NULL;
}    