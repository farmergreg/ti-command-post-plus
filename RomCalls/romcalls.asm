; $Id: romcalls.asm 13 2004-08-05 20:26:49Z dietsche $

_nostub
_ti89

 xdef _nostub
 xdef _ti89

Begin:
 dc.w (LookupTableEnd-LookupTable-4)/4
LookupTable:
 dc.w $0
 dc.w .LC0-Begin
 dc.w $1
 dc.w .LC1-Begin
 dc.w $2
 dc.w .LC2-Begin
 dc.w $3
 dc.w .LC3-Begin
 dc.w $4
 dc.w .LC4-Begin
 dc.w $5
 dc.w .LC5-Begin
 dc.w $6
 dc.w .LC6-Begin
 dc.w $7
 dc.w .LC7-Begin
 dc.w $8
 dc.w .LC8-Begin
 dc.w $9
 dc.w .LC9-Begin
 dc.w $A
 dc.w .LC10-Begin
 dc.w $B
 dc.w .LC11-Begin
 dc.w $C
 dc.w .LC12-Begin
 dc.w $D
 dc.w .LC13-Begin
 dc.w $E
 dc.w .LC14-Begin
 dc.w $F
 dc.w .LC15-Begin
 dc.w $10
 dc.w .LC16-Begin
 dc.w $11
 dc.w .LC17-Begin
 dc.w $12
 dc.w .LC18-Begin
 dc.w $13
 dc.w .LC19-Begin
 dc.w $14
 dc.w .LC20-Begin
 dc.w $15
 dc.w .LC21-Begin
 dc.w $16
 dc.w .LC22-Begin
 dc.w $17
 dc.w .LC23-Begin
 dc.w $18
 dc.w .LC24-Begin
 dc.w $19
 dc.w .LC25-Begin
 dc.w $1A
 dc.w .LC26-Begin
 dc.w $1B
 dc.w .LC27-Begin
 dc.w $1C
 dc.w .LC28-Begin
 dc.w $1D
 dc.w .LC29-Begin
 dc.w $1E
 dc.w .LC30-Begin
 dc.w $1F
 dc.w .LC31-Begin
 dc.w $20
 dc.w .LC32-Begin
 dc.w $21
 dc.w .LC33-Begin
 dc.w $22
 dc.w .LC34-Begin
 dc.w $23
 dc.w .LC35-Begin
 dc.w $24
 dc.w .LC36-Begin
 dc.w $25
 dc.w .LC37-Begin
 dc.w $26
 dc.w .LC38-Begin
 dc.w $27
 dc.w .LC39-Begin
 dc.w $28
 dc.w .LC40-Begin
 dc.w $29
 dc.w .LC41-Begin
 dc.w $2A
 dc.w .LC42-Begin
 dc.w $2B
 dc.w .LC43-Begin
 dc.w $2C
 dc.w .LC44-Begin
 dc.w $2D
 dc.w .LC45-Begin
 dc.w $2E
 dc.w .LC46-Begin
 dc.w $2F
 dc.w .LC47-Begin
 dc.w $30
 dc.w .LC48-Begin
 dc.w $31
 dc.w .LC49-Begin
 dc.w $32
 dc.w .LC50-Begin
 dc.w $33
 dc.w .LC51-Begin
 dc.w $34
 dc.w .LC52-Begin
 dc.w $35
 dc.w .LC53-Begin
 dc.w $36
 dc.w .LC54-Begin
 dc.w $37
 dc.w .LC55-Begin
 dc.w $38
 dc.w .LC56-Begin
 dc.w $39
 dc.w .LC57-Begin
 dc.w $3A
 dc.w .LC58-Begin
 dc.w $3B
 dc.w .LC59-Begin
 dc.w $3C
 dc.w .LC60-Begin
 dc.w $3D
 dc.w .LC61-Begin
 dc.w $3E
 dc.w .LC62-Begin
 dc.w $3F
 dc.w .LC63-Begin
 dc.w $40
 dc.w .LC64-Begin
 dc.w $41
 dc.w .LC65-Begin
 dc.w $42
 dc.w .LC66-Begin
 dc.w $43
 dc.w .LC67-Begin
 dc.w $44
 dc.w .LC68-Begin
 dc.w $45
 dc.w .LC69-Begin
 dc.w $46
 dc.w .LC70-Begin
 dc.w $47
 dc.w .LC71-Begin
 dc.w $48
 dc.w .LC72-Begin
 dc.w $49
 dc.w .LC73-Begin
 dc.w $4A
 dc.w .LC74-Begin
 dc.w $4B
 dc.w .LC75-Begin
 dc.w $4C
 dc.w .LC76-Begin
 dc.w $4D
 dc.w .LC77-Begin
 dc.w $4E
 dc.w .LC78-Begin
 dc.w $4F
 dc.w .LC79-Begin
 dc.w $50
 dc.w .LC80-Begin
 dc.w $51
 dc.w .LC81-Begin
 dc.w $52
 dc.w .LC82-Begin
 dc.w $53
 dc.w .LC83-Begin
 dc.w $54
 dc.w .LC84-Begin
 dc.w $55
 dc.w .LC85-Begin
 dc.w $56
 dc.w .LC86-Begin
 dc.w $57
 dc.w .LC87-Begin
 dc.w $58
 dc.w .LC88-Begin
 dc.w $59
 dc.w .LC89-Begin
 dc.w $5A
 dc.w .LC90-Begin
 dc.w $5B
 dc.w .LC91-Begin
 dc.w $5C
 dc.w .LC92-Begin
 dc.w $5D
 dc.w .LC93-Begin
 dc.w $5E
 dc.w .LC94-Begin
 dc.w $5F
 dc.w .LC95-Begin
 dc.w $60
 dc.w .LC96-Begin
 dc.w $61
 dc.w .LC97-Begin
 dc.w $62
 dc.w .LC98-Begin
 dc.w $63
 dc.w .LC99-Begin
 dc.w $64
 dc.w .LC100-Begin
 dc.w $65
 dc.w .LC101-Begin
 dc.w $66
 dc.w .LC102-Begin
 dc.w $67
 dc.w .LC103-Begin
 dc.w $68
 dc.w .LC104-Begin
 dc.w $69
 dc.w .LC105-Begin
 dc.w $6A
 dc.w .LC106-Begin
 dc.w $6B
 dc.w .LC107-Begin
 dc.w $6C
 dc.w .LC108-Begin
 dc.w $6D
 dc.w .LC109-Begin
 dc.w $6E
 dc.w .LC110-Begin
 dc.w $6F
 dc.w .LC111-Begin
 dc.w $70
 dc.w .LC112-Begin
 dc.w $71
 dc.w .LC113-Begin
 dc.w $72
 dc.w .LC114-Begin
 dc.w $73
 dc.w .LC115-Begin
 dc.w $74
 dc.w .LC116-Begin
 dc.w $75
 dc.w .LC117-Begin
 dc.w $76
 dc.w .LC118-Begin
 dc.w $77
 dc.w .LC119-Begin
 dc.w $78
 dc.w .LC120-Begin
 dc.w $79
 dc.w .LC121-Begin
 dc.w $7A
 dc.w .LC122-Begin
 dc.w $7B
 dc.w .LC123-Begin
 dc.w $7C
 dc.w .LC124-Begin
 dc.w $7D
 dc.w .LC125-Begin
 dc.w $7E
 dc.w .LC126-Begin
 dc.w $7F
 dc.w .LC127-Begin
 dc.w $80
 dc.w .LC128-Begin
 dc.w $81
 dc.w .LC129-Begin
 dc.w $82
 dc.w .LC130-Begin
 dc.w $83
 dc.w .LC131-Begin
 dc.w $84
 dc.w .LC132-Begin
 dc.w $85
 dc.w .LC133-Begin
 dc.w $86
 dc.w .LC134-Begin
 dc.w $87
 dc.w .LC135-Begin
 dc.w $88
 dc.w .LC136-Begin
 dc.w $89
 dc.w .LC137-Begin
 dc.w $8A
 dc.w .LC138-Begin
 dc.w $8B
 dc.w .LC139-Begin
 dc.w $8C
 dc.w .LC140-Begin
 dc.w $8D
 dc.w .LC141-Begin
 dc.w $8E
 dc.w .LC142-Begin
 dc.w $8F
 dc.w .LC143-Begin
 dc.w $90
 dc.w .LC144-Begin
 dc.w $91
 dc.w .LC145-Begin
 dc.w $92
 dc.w .LC146-Begin
 dc.w $93
 dc.w .LC147-Begin
 dc.w $94
 dc.w .LC148-Begin
 dc.w $95
 dc.w .LC149-Begin
 dc.w $96
 dc.w .LC150-Begin
 dc.w $97
 dc.w .LC151-Begin
 dc.w $98
 dc.w .LC152-Begin
 dc.w $99
 dc.w .LC153-Begin
 dc.w $9A
 dc.w .LC154-Begin
 dc.w $9B
 dc.w .LC155-Begin
 dc.w $9C
 dc.w .LC156-Begin
 dc.w $9D
 dc.w .LC157-Begin
 dc.w $9E
 dc.w .LC158-Begin
 dc.w $9F
 dc.w .LC159-Begin
 dc.w $A0
 dc.w .LC160-Begin
 dc.w $A1
 dc.w .LC161-Begin
 dc.w $A2
 dc.w .LC162-Begin
 dc.w $A3
 dc.w .LC163-Begin
 dc.w $A4
 dc.w .LC164-Begin
 dc.w $A5
 dc.w .LC165-Begin
 dc.w $A6
 dc.w .LC166-Begin
 dc.w $A7
 dc.w .LC167-Begin
 dc.w $A8
 dc.w .LC168-Begin
 dc.w $A9
 dc.w .LC169-Begin
 dc.w $AA
 dc.w .LC170-Begin
 dc.w $AB
 dc.w .LC171-Begin
 dc.w $AC
 dc.w .LC172-Begin
 dc.w $AD
 dc.w .LC173-Begin
 dc.w $AE
 dc.w .LC174-Begin
 dc.w $AF
 dc.w .LC175-Begin
 dc.w $B0
 dc.w .LC176-Begin
 dc.w $B1
 dc.w .LC177-Begin
 dc.w $B2
 dc.w .LC178-Begin
 dc.w $B3
 dc.w .LC179-Begin
 dc.w $B4
 dc.w .LC180-Begin
 dc.w $B5
 dc.w .LC181-Begin
 dc.w $B6
 dc.w .LC182-Begin
 dc.w $B7
 dc.w .LC183-Begin
 dc.w $B8
 dc.w .LC184-Begin
 dc.w $B9
 dc.w .LC185-Begin
 dc.w $BA
 dc.w .LC186-Begin
 dc.w $BB
 dc.w .LC187-Begin
 dc.w $BC
 dc.w .LC188-Begin
 dc.w $BD
 dc.w .LC189-Begin
 dc.w $BE
 dc.w .LC190-Begin
 dc.w $BF
 dc.w .LC191-Begin
 dc.w $C0
 dc.w .LC192-Begin
 dc.w $C1
 dc.w .LC193-Begin
 dc.w $C2
 dc.w .LC194-Begin
 dc.w $C3
 dc.w .LC195-Begin
 dc.w $C4
 dc.w .LC196-Begin
 dc.w $C5
 dc.w .LC197-Begin
 dc.w $C6
 dc.w .LC198-Begin
 dc.w $C7
 dc.w .LC199-Begin
 dc.w $C8
 dc.w .LC200-Begin
 dc.w $C9
 dc.w .LC201-Begin
 dc.w $CA
 dc.w .LC202-Begin
 dc.w $CB
 dc.w .LC203-Begin
 dc.w $CC
 dc.w .LC204-Begin
 dc.w $CD
 dc.w .LC205-Begin
 dc.w $CE
 dc.w .LC206-Begin
 dc.w $CF
 dc.w .LC207-Begin
 dc.w $D0
 dc.w .LC208-Begin
 dc.w $D1
 dc.w .LC209-Begin
 dc.w $D2
 dc.w .LC210-Begin
 dc.w $D3
 dc.w .LC211-Begin
 dc.w $D4
 dc.w .LC212-Begin
 dc.w $D5
 dc.w .LC213-Begin
 dc.w $D6
 dc.w .LC214-Begin
 dc.w $D7
 dc.w .LC215-Begin
 dc.w $D8
 dc.w .LC216-Begin
 dc.w $D9
 dc.w .LC217-Begin
 dc.w $DA
 dc.w .LC218-Begin
 dc.w $DB
 dc.w .LC219-Begin
 dc.w $DC
 dc.w .LC220-Begin
 dc.w $DD
 dc.w .LC221-Begin
 dc.w $DE
 dc.w .LC222-Begin
 dc.w $DF
 dc.w .LC223-Begin
 dc.w $E0
 dc.w .LC224-Begin
 dc.w $E1
 dc.w .LC225-Begin
 dc.w $E2
 dc.w .LC226-Begin
 dc.w $E3
 dc.w .LC227-Begin
 dc.w $E4
 dc.w .LC228-Begin
 dc.w $E5
 dc.w .LC229-Begin
 dc.w $E6
 dc.w .LC230-Begin
 dc.w $E7
 dc.w .LC231-Begin
 dc.w $E8
 dc.w .LC232-Begin
 dc.w $E9
 dc.w .LC233-Begin
 dc.w $EA
 dc.w .LC234-Begin
 dc.w $EB
 dc.w .LC235-Begin
 dc.w $EC
 dc.w .LC236-Begin
 dc.w $ED
 dc.w .LC237-Begin
 dc.w $EE
 dc.w .LC238-Begin
 dc.w $EF
 dc.w .LC239-Begin
 dc.w $F0
 dc.w .LC240-Begin
 dc.w $F1
 dc.w .LC241-Begin
 dc.w $F2
 dc.w .LC242-Begin
 dc.w $F3
 dc.w .LC243-Begin
 dc.w $F4
 dc.w .LC244-Begin
 dc.w $F5
 dc.w .LC245-Begin
 dc.w $F6
 dc.w .LC246-Begin
 dc.w $F7
 dc.w .LC247-Begin
 dc.w $F8
 dc.w .LC248-Begin
 dc.w $F9
 dc.w .LC249-Begin
 dc.w $FA
 dc.w .LC250-Begin
 dc.w $FB
 dc.w .LC251-Begin
 dc.w $FC
 dc.w .LC252-Begin
 dc.w $FD
 dc.w .LC253-Begin
 dc.w $FE
 dc.w .LC254-Begin
 dc.w $FF
 dc.w .LC255-Begin
 dc.w $100
 dc.w .LC256-Begin
 dc.w $101
 dc.w .LC257-Begin
 dc.w $102
 dc.w .LC258-Begin
 dc.w $103
 dc.w .LC259-Begin
 dc.w $104
 dc.w .LC260-Begin
 dc.w $105
 dc.w .LC261-Begin
 dc.w $106
 dc.w .LC262-Begin
 dc.w $107
 dc.w .LC263-Begin
 dc.w $108
 dc.w .LC264-Begin
 dc.w $109
 dc.w .LC265-Begin
 dc.w $10A
 dc.w .LC266-Begin
 dc.w $10B
 dc.w .LC267-Begin
 dc.w $10C
 dc.w .LC268-Begin
 dc.w $10D
 dc.w .LC269-Begin
 dc.w $10E
 dc.w .LC270-Begin
 dc.w $10F
 dc.w .LC271-Begin
 dc.w $110
 dc.w .LC272-Begin
 dc.w $111
 dc.w .LC273-Begin
 dc.w $112
 dc.w .LC274-Begin
 dc.w $113
 dc.w .LC275-Begin
 dc.w $114
 dc.w .LC276-Begin
 dc.w $115
 dc.w .LC277-Begin
 dc.w $116
 dc.w .LC278-Begin
 dc.w $117
 dc.w .LC279-Begin
 dc.w $118
 dc.w .LC280-Begin
 dc.w $119
 dc.w .LC281-Begin
 dc.w $11A
 dc.w .LC282-Begin
 dc.w $11B
 dc.w .LC283-Begin
 dc.w $11C
 dc.w .LC284-Begin
 dc.w $11D
 dc.w .LC285-Begin
 dc.w $11E
 dc.w .LC286-Begin
 dc.w $11F
 dc.w .LC287-Begin
 dc.w $120
 dc.w .LC288-Begin
 dc.w $121
 dc.w .LC289-Begin
 dc.w $122
 dc.w .LC290-Begin
 dc.w $123
 dc.w .LC291-Begin
 dc.w $124
 dc.w .LC292-Begin
 dc.w $125
 dc.w .LC293-Begin
 dc.w $126
 dc.w .LC294-Begin
 dc.w $127
 dc.w .LC295-Begin
 dc.w $128
 dc.w .LC296-Begin
 dc.w $129
 dc.w .LC297-Begin
 dc.w $12A
 dc.w .LC298-Begin
 dc.w $12B
 dc.w .LC299-Begin
 dc.w $12C
 dc.w .LC300-Begin
 dc.w $12D
 dc.w .LC301-Begin
 dc.w $12E
 dc.w .LC302-Begin
 dc.w $12F
 dc.w .LC303-Begin
 dc.w $130
 dc.w .LC304-Begin
 dc.w $131
 dc.w .LC305-Begin
 dc.w $132
 dc.w .LC306-Begin
 dc.w $133
 dc.w .LC307-Begin
 dc.w $134
 dc.w .LC308-Begin
 dc.w $135
 dc.w .LC309-Begin
 dc.w $136
 dc.w .LC310-Begin
 dc.w $137
 dc.w .LC311-Begin
 dc.w $138
 dc.w .LC312-Begin
 dc.w $139
 dc.w .LC313-Begin
 dc.w $13A
 dc.w .LC314-Begin
 dc.w $13B
 dc.w .LC315-Begin
 dc.w $13C
 dc.w .LC316-Begin
 dc.w $13D
 dc.w .LC317-Begin
 dc.w $13E
 dc.w .LC318-Begin
 dc.w $13F
 dc.w .LC319-Begin
 dc.w $140
 dc.w .LC320-Begin
 dc.w $141
 dc.w .LC321-Begin
 dc.w $142
 dc.w .LC322-Begin
 dc.w $143
 dc.w .LC323-Begin
 dc.w $144
 dc.w .LC324-Begin
 dc.w $145
 dc.w .LC325-Begin
 dc.w $146
 dc.w .LC326-Begin
 dc.w $147
 dc.w .LC327-Begin
 dc.w $148
 dc.w .LC328-Begin
 dc.w $149
 dc.w .LC329-Begin
 dc.w $14A
 dc.w .LC330-Begin
 dc.w $14B
 dc.w .LC331-Begin
 dc.w $14C
 dc.w .LC332-Begin
 dc.w $14D
 dc.w .LC333-Begin
 dc.w $14E
 dc.w .LC334-Begin
 dc.w $14F
 dc.w .LC335-Begin
 dc.w $150
 dc.w .LC336-Begin
 dc.w $151
 dc.w .LC337-Begin
 dc.w $152
 dc.w .LC338-Begin
 dc.w $153
 dc.w .LC339-Begin
 dc.w $154
 dc.w .LC340-Begin
 dc.w $155
 dc.w .LC341-Begin
 dc.w $156
 dc.w .LC342-Begin
 dc.w $157
 dc.w .LC343-Begin
 dc.w $158
 dc.w .LC344-Begin
 dc.w $159
 dc.w .LC345-Begin
 dc.w $15A
 dc.w .LC346-Begin
 dc.w $15B
 dc.w .LC347-Begin
 dc.w $15C
 dc.w .LC348-Begin
 dc.w $15D
 dc.w .LC349-Begin
 dc.w $15E
 dc.w .LC350-Begin
 dc.w $15F
 dc.w .LC351-Begin
 dc.w $160
 dc.w .LC352-Begin
 dc.w $161
 dc.w .LC353-Begin
 dc.w $162
 dc.w .LC354-Begin
 dc.w $163
 dc.w .LC355-Begin
 dc.w $164
 dc.w .LC356-Begin
 dc.w $165
 dc.w .LC357-Begin
 dc.w $166
 dc.w .LC358-Begin
 dc.w $167
 dc.w .LC359-Begin
 dc.w $168
 dc.w .LC360-Begin
 dc.w $169
 dc.w .LC361-Begin
 dc.w $16A
 dc.w .LC362-Begin
 dc.w $16B
 dc.w .LC363-Begin
 dc.w $16C
 dc.w .LC364-Begin
 dc.w $16D
 dc.w .LC365-Begin
 dc.w $16E
 dc.w .LC366-Begin
 dc.w $16F
 dc.w .LC367-Begin
 dc.w $170
 dc.w .LC368-Begin
 dc.w $171
 dc.w .LC369-Begin
 dc.w $172
 dc.w .LC370-Begin
 dc.w $173
 dc.w .LC371-Begin
 dc.w $174
 dc.w .LC372-Begin
 dc.w $175
 dc.w .LC373-Begin
 dc.w $176
 dc.w .LC374-Begin
 dc.w $177
 dc.w .LC375-Begin
 dc.w $178
 dc.w .LC376-Begin
 dc.w $179
 dc.w .LC377-Begin
 dc.w $17A
 dc.w .LC378-Begin
 dc.w $17B
 dc.w .LC379-Begin
 dc.w $17C
 dc.w .LC380-Begin
 dc.w $17D
 dc.w .LC381-Begin
 dc.w $17E
 dc.w .LC382-Begin
 dc.w $17F
 dc.w .LC383-Begin
 dc.w $180
 dc.w .LC384-Begin
 dc.w $181
 dc.w .LC385-Begin
 dc.w $182
 dc.w .LC386-Begin
 dc.w $183
 dc.w .LC387-Begin
 dc.w $184
 dc.w .LC388-Begin
 dc.w $185
 dc.w .LC389-Begin
 dc.w $186
 dc.w .LC390-Begin
 dc.w $187
 dc.w .LC391-Begin
 dc.w $188
 dc.w .LC392-Begin
 dc.w $189
 dc.w .LC393-Begin
 dc.w $18A
 dc.w .LC394-Begin
 dc.w $18B
 dc.w .LC395-Begin
 dc.w $18C
 dc.w .LC396-Begin
 dc.w $18D
 dc.w .LC397-Begin
 dc.w $18E
 dc.w .LC398-Begin
 dc.w $18F
 dc.w .LC399-Begin
 dc.w $190
 dc.w .LC400-Begin
 dc.w $191
 dc.w .LC401-Begin
 dc.w $192
 dc.w .LC402-Begin
 dc.w $193
 dc.w .LC403-Begin
 dc.w $194
 dc.w .LC404-Begin
 dc.w $195
 dc.w .LC405-Begin
 dc.w $196
 dc.w .LC406-Begin
 dc.w $197
 dc.w .LC407-Begin
 dc.w $198
 dc.w .LC408-Begin
 dc.w $199
 dc.w .LC409-Begin
 dc.w $19A
 dc.w .LC410-Begin
 dc.w $19B
 dc.w .LC411-Begin
 dc.w $19C
 dc.w .LC412-Begin
 dc.w $19D
 dc.w .LC413-Begin
 dc.w $19E
 dc.w .LC414-Begin
 dc.w $19F
 dc.w .LC415-Begin
 dc.w $1A0
 dc.w .LC416-Begin
 dc.w $1A1
 dc.w .LC417-Begin
 dc.w $1A2
 dc.w .LC418-Begin
 dc.w $1A3
 dc.w .LC419-Begin
 dc.w $1A4
 dc.w .LC420-Begin
 dc.w $1A5
 dc.w .LC421-Begin
 dc.w $1A6
 dc.w .LC422-Begin
 dc.w $1A7
 dc.w .LC423-Begin
 dc.w $1A8
 dc.w .LC424-Begin
 dc.w $1A9
 dc.w .LC425-Begin
 dc.w $1AA
 dc.w .LC426-Begin
 dc.w $1AB
 dc.w .LC427-Begin
 dc.w $1AC
 dc.w .LC428-Begin
 dc.w $1AD
 dc.w .LC429-Begin
 dc.w $1AE
 dc.w .LC430-Begin
 dc.w $1AF
 dc.w .LC431-Begin
 dc.w $1B0
 dc.w .LC432-Begin
 dc.w $1B1
 dc.w .LC433-Begin
 dc.w $1B2
 dc.w .LC434-Begin
 dc.w $1B3
 dc.w .LC435-Begin
 dc.w $1B4
 dc.w .LC436-Begin
 dc.w $1B5
 dc.w .LC437-Begin
 dc.w $1B6
 dc.w .LC438-Begin
 dc.w $1B7
 dc.w .LC439-Begin
 dc.w $1B8
 dc.w .LC440-Begin
 dc.w $1B9
 dc.w .LC441-Begin
 dc.w $1BA
 dc.w .LC442-Begin
 dc.w $1BB
 dc.w .LC443-Begin
 dc.w $1BC
 dc.w .LC444-Begin
 dc.w $1BD
 dc.w .LC445-Begin
 dc.w $1BE
 dc.w .LC446-Begin
 dc.w $1BF
 dc.w .LC447-Begin
 dc.w $1C0
 dc.w .LC448-Begin
 dc.w $1C1
 dc.w .LC449-Begin
 dc.w $1C2
 dc.w .LC450-Begin
 dc.w $1C3
 dc.w .LC451-Begin
 dc.w $1C4
 dc.w .LC452-Begin
 dc.w $1C5
 dc.w .LC453-Begin
 dc.w $1C6
 dc.w .LC454-Begin
 dc.w $1C7
 dc.w .LC455-Begin
 dc.w $1C8
 dc.w .LC456-Begin
 dc.w $1C9
 dc.w .LC457-Begin
 dc.w $1CA
 dc.w .LC458-Begin
 dc.w $1CB
 dc.w .LC459-Begin
 dc.w $1CC
 dc.w .LC460-Begin
 dc.w $1CD
 dc.w .LC461-Begin
 dc.w $1CE
 dc.w .LC462-Begin
 dc.w $1CF
 dc.w .LC463-Begin
 dc.w $1D0
 dc.w .LC464-Begin
 dc.w $1D1
 dc.w .LC465-Begin
 dc.w $1D2
 dc.w .LC466-Begin
 dc.w $1D3
 dc.w .LC467-Begin
 dc.w $1D4
 dc.w .LC468-Begin
 dc.w $1D5
 dc.w .LC469-Begin
 dc.w $1D6
 dc.w .LC470-Begin
 dc.w $1D7
 dc.w .LC471-Begin
 dc.w $1D8
 dc.w .LC472-Begin
 dc.w $1D9
 dc.w .LC473-Begin
 dc.w $1DA
 dc.w .LC474-Begin
 dc.w $1DB
 dc.w .LC475-Begin
 dc.w $1DC
 dc.w .LC476-Begin
 dc.w $1DD
 dc.w .LC477-Begin
 dc.w $1DE
 dc.w .LC478-Begin
 dc.w $1DF
 dc.w .LC479-Begin
 dc.w $1E0
 dc.w .LC480-Begin
 dc.w $1E1
 dc.w .LC481-Begin
 dc.w $1E2
 dc.w .LC482-Begin
 dc.w $1E3
 dc.w .LC483-Begin
 dc.w $1E4
 dc.w .LC484-Begin
 dc.w $1E5
 dc.w .LC485-Begin
 dc.w $1E6
 dc.w .LC486-Begin
 dc.w $1E7
 dc.w .LC487-Begin
 dc.w $1E8
 dc.w .LC488-Begin
 dc.w $1E9
 dc.w .LC489-Begin
 dc.w $1EA
 dc.w .LC490-Begin
 dc.w $1EB
 dc.w .LC491-Begin
 dc.w $1EC
 dc.w .LC492-Begin
 dc.w $1ED
 dc.w .LC493-Begin
 dc.w $1EE
 dc.w .LC494-Begin
 dc.w $1EF
 dc.w .LC495-Begin
 dc.w $1F0
 dc.w .LC496-Begin
 dc.w $1F1
 dc.w .LC497-Begin
 dc.w $1F2
 dc.w .LC498-Begin
 dc.w $1F3
 dc.w .LC499-Begin
 dc.w $1F4
 dc.w .LC500-Begin
 dc.w $1F5
 dc.w .LC501-Begin
 dc.w $1F6
 dc.w .LC502-Begin
 dc.w $1F7
 dc.w .LC503-Begin
 dc.w $1F8
 dc.w .LC504-Begin
 dc.w $1F9
 dc.w .LC505-Begin
 dc.w $1FA
 dc.w .LC506-Begin
 dc.w $1FB
 dc.w .LC507-Begin
 dc.w $1FC
 dc.w .LC508-Begin
 dc.w $1FD
 dc.w .LC509-Begin
 dc.w $1FE
 dc.w .LC510-Begin
 dc.w $1FF
 dc.w .LC511-Begin
 dc.w $200
 dc.w .LC512-Begin
 dc.w $201
 dc.w .LC513-Begin
 dc.w $202
 dc.w .LC514-Begin
 dc.w $203
 dc.w .LC515-Begin
 dc.w $204
 dc.w .LC516-Begin
 dc.w $205
 dc.w .LC517-Begin
 dc.w $206
 dc.w .LC518-Begin
 dc.w $207
 dc.w .LC519-Begin
 dc.w $208
 dc.w .LC520-Begin
 dc.w $209
 dc.w .LC521-Begin
 dc.w $20A
 dc.w .LC522-Begin
 dc.w $20B
 dc.w .LC523-Begin
 dc.w $20C
 dc.w .LC524-Begin
 dc.w $20D
 dc.w .LC525-Begin
 dc.w $20E
 dc.w .LC526-Begin
 dc.w $20F
 dc.w .LC527-Begin
 dc.w $210
 dc.w .LC528-Begin
 dc.w $211
 dc.w .LC529-Begin
 dc.w $212
 dc.w .LC530-Begin
 dc.w $213
 dc.w .LC531-Begin
 dc.w $214
 dc.w .LC532-Begin
 dc.w $215
 dc.w .LC533-Begin
 dc.w $216
 dc.w .LC534-Begin
 dc.w $217
 dc.w .LC535-Begin
 dc.w $218
 dc.w .LC536-Begin
 dc.w $219
 dc.w .LC537-Begin
 dc.w $21A
 dc.w .LC538-Begin
 dc.w $21B
 dc.w .LC539-Begin
 dc.w $21C
 dc.w .LC540-Begin
 dc.w $21D
 dc.w .LC541-Begin
 dc.w $21E
 dc.w .LC542-Begin
 dc.w $21F
 dc.w .LC543-Begin
 dc.w $220
 dc.w .LC544-Begin
 dc.w $221
 dc.w .LC545-Begin
 dc.w $222
 dc.w .LC546-Begin
 dc.w $223
 dc.w .LC547-Begin
 dc.w $224
 dc.w .LC548-Begin
 dc.w $225
 dc.w .LC549-Begin
 dc.w $226
 dc.w .LC550-Begin
 dc.w $227
 dc.w .LC551-Begin
 dc.w $228
 dc.w .LC552-Begin
 dc.w $229
 dc.w .LC553-Begin
 dc.w $22A
 dc.w .LC554-Begin
 dc.w $22B
 dc.w .LC555-Begin
 dc.w $22C
 dc.w .LC556-Begin
 dc.w $22D
 dc.w .LC557-Begin
 dc.w $22E
 dc.w .LC558-Begin
 dc.w $22F
 dc.w .LC559-Begin
 dc.w $230
 dc.w .LC560-Begin
 dc.w $231
 dc.w .LC561-Begin
 dc.w $232
 dc.w .LC562-Begin
 dc.w $233
 dc.w .LC563-Begin
 dc.w $234
 dc.w .LC564-Begin
 dc.w $235
 dc.w .LC565-Begin
 dc.w $236
 dc.w .LC566-Begin
 dc.w $237
 dc.w .LC567-Begin
 dc.w $238
 dc.w .LC568-Begin
 dc.w $239
 dc.w .LC569-Begin
 dc.w $23A
 dc.w .LC570-Begin
 dc.w $23B
 dc.w .LC571-Begin
 dc.w $23C
 dc.w .LC572-Begin
 dc.w $23D
 dc.w .LC573-Begin
 dc.w $23E
 dc.w .LC574-Begin
 dc.w $23F
 dc.w .LC575-Begin
 dc.w $240
 dc.w .LC576-Begin
 dc.w $241
 dc.w .LC577-Begin
 dc.w $242
 dc.w .LC578-Begin
 dc.w $243
 dc.w .LC579-Begin
 dc.w $244
 dc.w .LC580-Begin
 dc.w $245
 dc.w .LC581-Begin
 dc.w $246
 dc.w .LC582-Begin
 dc.w $247
 dc.w .LC583-Begin
 dc.w $248
 dc.w .LC584-Begin
 dc.w $249
 dc.w .LC585-Begin
 dc.w $24A
 dc.w .LC586-Begin
 dc.w $24B
 dc.w .LC587-Begin
 dc.w $24C
 dc.w .LC588-Begin
 dc.w $24D
 dc.w .LC589-Begin
 dc.w $24E
 dc.w .LC590-Begin
 dc.w $24F
 dc.w .LC591-Begin
 dc.w $250
 dc.w .LC592-Begin
 dc.w $251
 dc.w .LC593-Begin
 dc.w $252
 dc.w .LC594-Begin
 dc.w $253
 dc.w .LC595-Begin
 dc.w $254
 dc.w .LC596-Begin
 dc.w $255
 dc.w .LC597-Begin
 dc.w $256
 dc.w .LC598-Begin
 dc.w $257
 dc.w .LC599-Begin
 dc.w $258
 dc.w .LC600-Begin
 dc.w $259
 dc.w .LC601-Begin
 dc.w $25A
 dc.w .LC602-Begin
 dc.w $25B
 dc.w .LC603-Begin
 dc.w $25C
 dc.w .LC604-Begin
 dc.w $25D
 dc.w .LC605-Begin
 dc.w $25E
 dc.w .LC606-Begin
 dc.w $25F
 dc.w .LC607-Begin
 dc.w $260
 dc.w .LC608-Begin
 dc.w $261
 dc.w .LC609-Begin
 dc.w $262
 dc.w .LC610-Begin
 dc.w $263
 dc.w .LC611-Begin
 dc.w $264
 dc.w .LC612-Begin
 dc.w $265
 dc.w .LC613-Begin
 dc.w $266
 dc.w .LC614-Begin
 dc.w $267
 dc.w .LC615-Begin
 dc.w $268
 dc.w .LC616-Begin
 dc.w $269
 dc.w .LC617-Begin
 dc.w $26A
 dc.w .LC618-Begin
 dc.w $26B
 dc.w .LC619-Begin
 dc.w $26C
 dc.w .LC620-Begin
 dc.w $26D
 dc.w .LC621-Begin
 dc.w $26E
 dc.w .LC622-Begin
 dc.w $26F
 dc.w .LC623-Begin
 dc.w $270
 dc.w .LC624-Begin
 dc.w $271
 dc.w .LC625-Begin
 dc.w $272
 dc.w .LC626-Begin
 dc.w $273
 dc.w .LC627-Begin
 dc.w $274
 dc.w .LC628-Begin
 dc.w $275
 dc.w .LC629-Begin
 dc.w $276
 dc.w .LC630-Begin
 dc.w $277
 dc.w .LC631-Begin
 dc.w $278
 dc.w .LC632-Begin
 dc.w $279
 dc.w .LC633-Begin
 dc.w $27A
 dc.w .LC634-Begin
 dc.w $27B
 dc.w .LC635-Begin
 dc.w $27C
 dc.w .LC636-Begin
 dc.w $27D
 dc.w .LC637-Begin
 dc.w $27E
 dc.w .LC638-Begin
 dc.w $27F
 dc.w .LC639-Begin
 dc.w $280
 dc.w .LC640-Begin
 dc.w $281
 dc.w .LC641-Begin
 dc.w $282
 dc.w .LC642-Begin
 dc.w $283
 dc.w .LC643-Begin
 dc.w $284
 dc.w .LC644-Begin
 dc.w $285
 dc.w .LC645-Begin
 dc.w $286
 dc.w .LC646-Begin
 dc.w $287
 dc.w .LC647-Begin
 dc.w $288
 dc.w .LC648-Begin
 dc.w $289
 dc.w .LC649-Begin
 dc.w $28A
 dc.w .LC650-Begin
 dc.w $28B
 dc.w .LC651-Begin
 dc.w $28C
 dc.w .LC652-Begin
 dc.w $28D
 dc.w .LC653-Begin
 dc.w $28E
 dc.w .LC654-Begin
 dc.w $28F
 dc.w .LC655-Begin
 dc.w $290
 dc.w .LC656-Begin
 dc.w $291
 dc.w .LC657-Begin
 dc.w $292
 dc.w .LC658-Begin
 dc.w $293
 dc.w .LC659-Begin
 dc.w $294
 dc.w .LC660-Begin
 dc.w $295
 dc.w .LC661-Begin
 dc.w $296
 dc.w .LC662-Begin
 dc.w $297
 dc.w .LC663-Begin
 dc.w $298
 dc.w .LC664-Begin
 dc.w $299
 dc.w .LC665-Begin
 dc.w $29A
 dc.w .LC666-Begin
 dc.w $29B
 dc.w .LC667-Begin
 dc.w $29C
 dc.w .LC668-Begin
 dc.w $29D
 dc.w .LC669-Begin
 dc.w $29E
 dc.w .LC670-Begin
 dc.w $29F
 dc.w .LC671-Begin
 dc.w $2A0
 dc.w .LC672-Begin
 dc.w $2A1
 dc.w .LC673-Begin
 dc.w $2A2
 dc.w .LC674-Begin
 dc.w $2A3
 dc.w .LC675-Begin
 dc.w $2A4
 dc.w .LC676-Begin
 dc.w $2A5
 dc.w .LC677-Begin
 dc.w $2A6
 dc.w .LC678-Begin
 dc.w $2A7
 dc.w .LC679-Begin
 dc.w $2A8
 dc.w .LC680-Begin
 dc.w $2A9
 dc.w .LC681-Begin
 dc.w $2AA
 dc.w .LC682-Begin
 dc.w $2AB
 dc.w .LC683-Begin
 dc.w $2AC
 dc.w .LC684-Begin
 dc.w $2AD
 dc.w .LC685-Begin
 dc.w $2AE
 dc.w .LC686-Begin
 dc.w $2AF
 dc.w .LC687-Begin
 dc.w $2B0
 dc.w .LC688-Begin
 dc.w $2B1
 dc.w .LC689-Begin
 dc.w $2B2
 dc.w .LC690-Begin
 dc.w $2B3
 dc.w .LC691-Begin
 dc.w $2B4
 dc.w .LC692-Begin
 dc.w $2B5
 dc.w .LC693-Begin
 dc.w $2B6
 dc.w .LC694-Begin
 dc.w $2B7
 dc.w .LC695-Begin
 dc.w $2B8
 dc.w .LC696-Begin
 dc.w $2B9
 dc.w .LC697-Begin
 dc.w $2BA
 dc.w .LC698-Begin
 dc.w $2BB
 dc.w .LC699-Begin
 dc.w $2BC
 dc.w .LC700-Begin
 dc.w $2BD
 dc.w .LC701-Begin
 dc.w $2BE
 dc.w .LC702-Begin
 dc.w $2BF
 dc.w .LC703-Begin
 dc.w $2C0
 dc.w .LC704-Begin
 dc.w $2C1
 dc.w .LC705-Begin
 dc.w $2C2
 dc.w .LC706-Begin
 dc.w $2C3
 dc.w .LC707-Begin
 dc.w $2C4
 dc.w .LC708-Begin
 dc.w $2C5
 dc.w .LC709-Begin
 dc.w $2C6
 dc.w .LC710-Begin
 dc.w $2C7
 dc.w .LC711-Begin
 dc.w $2C8
 dc.w .LC712-Begin
 dc.w $2C9
 dc.w .LC713-Begin
 dc.w $2CA
 dc.w .LC714-Begin
 dc.w $2CB
 dc.w .LC715-Begin
 dc.w $2CC
 dc.w .LC716-Begin
 dc.w $2CD
 dc.w .LC717-Begin
 dc.w $2CE
 dc.w .LC718-Begin
 dc.w $2CF
 dc.w .LC719-Begin
 dc.w $2D0
 dc.w .LC720-Begin
 dc.w $2D1
 dc.w .LC721-Begin
 dc.w $2D2
 dc.w .LC722-Begin
 dc.w $2D3
 dc.w .LC723-Begin
 dc.w $2D4
 dc.w .LC724-Begin
 dc.w $2D5
 dc.w .LC725-Begin
 dc.w $2D6
 dc.w .LC726-Begin
 dc.w $2D7
 dc.w .LC727-Begin
 dc.w $2D8
 dc.w .LC728-Begin
 dc.w $2D9
 dc.w .LC729-Begin
 dc.w $2DA
 dc.w .LC730-Begin
 dc.w $2DB
 dc.w .LC731-Begin
 dc.w $2DC
 dc.w .LC732-Begin
 dc.w $2DD
 dc.w .LC733-Begin
 dc.w $2DE
 dc.w .LC734-Begin
 dc.w $2DF
 dc.w .LC735-Begin
 dc.w $2E0
 dc.w .LC736-Begin
 dc.w $2E1
 dc.w .LC737-Begin
 dc.w $2E2
 dc.w .LC738-Begin
 dc.w $2E3
 dc.w .LC739-Begin
 dc.w $2E4
 dc.w .LC740-Begin
 dc.w $2E5
 dc.w .LC741-Begin
 dc.w $2E6
 dc.w .LC742-Begin
 dc.w $2E7
 dc.w .LC743-Begin
 dc.w $2E8
 dc.w .LC744-Begin
 dc.w $2E9
 dc.w .LC745-Begin
 dc.w $2EA
 dc.w .LC746-Begin
 dc.w $2EB
 dc.w .LC747-Begin
 dc.w $2EC
 dc.w .LC748-Begin
 dc.w $2ED
 dc.w .LC749-Begin
 dc.w $2EE
 dc.w .LC750-Begin
 dc.w $2EF
 dc.w .LC751-Begin
 dc.w $2F0
 dc.w .LC752-Begin
 dc.w $2F1
 dc.w .LC753-Begin
 dc.w $2F2
 dc.w .LC754-Begin
 dc.w $2F3
 dc.w .LC755-Begin
 dc.w $2F4
 dc.w .LC756-Begin
 dc.w $2F5
 dc.w .LC757-Begin
 dc.w $2F6
 dc.w .LC758-Begin
 dc.w $2F7
 dc.w .LC759-Begin
 dc.w $2F8
 dc.w .LC760-Begin
 dc.w $2F9
 dc.w .LC761-Begin
 dc.w $2FA
 dc.w .LC762-Begin
 dc.w $2FB
 dc.w .LC763-Begin
 dc.w $2FC
 dc.w .LC764-Begin
 dc.w $2FD
 dc.w .LC765-Begin
 dc.w $2FE
 dc.w .LC766-Begin
 dc.w $2FF
 dc.w .LC767-Begin
 dc.w $300
 dc.w .LC768-Begin
 dc.w $301
 dc.w .LC769-Begin
 dc.w $302
 dc.w .LC770-Begin
 dc.w $303
 dc.w .LC771-Begin
 dc.w $304
 dc.w .LC772-Begin
 dc.w $305
 dc.w .LC773-Begin
 dc.w $306
 dc.w .LC774-Begin
 dc.w $307
 dc.w .LC775-Begin
 dc.w $308
 dc.w .LC776-Begin
 dc.w $309
 dc.w .LC777-Begin
 dc.w $30A
 dc.w .LC778-Begin
 dc.w $30B
 dc.w .LC779-Begin
 dc.w $30C
 dc.w .LC780-Begin
 dc.w $30D
 dc.w .LC781-Begin
 dc.w $30E
 dc.w .LC782-Begin
 dc.w $30F
 dc.w .LC783-Begin
 dc.w $310
 dc.w .LC784-Begin
 dc.w $311
 dc.w .LC785-Begin
 dc.w $312
 dc.w .LC786-Begin
 dc.w $313
 dc.w .LC787-Begin
 dc.w $314
 dc.w .LC788-Begin
 dc.w $315
 dc.w .LC789-Begin
 dc.w $316
 dc.w .LC790-Begin
 dc.w $317
 dc.w .LC791-Begin
 dc.w $318
 dc.w .LC792-Begin
 dc.w $319
 dc.w .LC793-Begin
 dc.w $31A
 dc.w .LC794-Begin
 dc.w $31B
 dc.w .LC795-Begin
 dc.w $31C
 dc.w .LC796-Begin
 dc.w $31D
 dc.w .LC797-Begin
 dc.w $31E
 dc.w .LC798-Begin
 dc.w $31F
 dc.w .LC799-Begin
 dc.w $320
 dc.w .LC800-Begin
 dc.w $321
 dc.w .LC801-Begin
 dc.w $322
 dc.w .LC802-Begin
 dc.w $323
 dc.w .LC803-Begin
 dc.w $324
 dc.w .LC804-Begin
 dc.w $325
 dc.w .LC805-Begin
 dc.w $326
 dc.w .LC806-Begin
 dc.w $327
 dc.w .LC807-Begin
 dc.w $328
 dc.w .LC808-Begin
 dc.w $329
 dc.w .LC809-Begin
 dc.w $32A
 dc.w .LC810-Begin
 dc.w $32B
 dc.w .LC811-Begin
 dc.w $32C
 dc.w .LC812-Begin
 dc.w $32D
 dc.w .LC813-Begin
 dc.w $32E
 dc.w .LC814-Begin
 dc.w $32F
 dc.w .LC815-Begin
 dc.w $330
 dc.w .LC816-Begin
 dc.w $331
 dc.w .LC817-Begin
 dc.w $332
 dc.w .LC818-Begin
 dc.w $333
 dc.w .LC819-Begin
 dc.w $334
 dc.w .LC820-Begin
 dc.w $335
 dc.w .LC821-Begin
 dc.w $336
 dc.w .LC822-Begin
 dc.w $337
 dc.w .LC823-Begin
 dc.w $338
 dc.w .LC824-Begin
 dc.w $339
 dc.w .LC825-Begin
 dc.w $33A
 dc.w .LC826-Begin
 dc.w $33B
 dc.w .LC827-Begin
 dc.w $33C
 dc.w .LC828-Begin
 dc.w $33D
 dc.w .LC829-Begin
 dc.w $33E
 dc.w .LC830-Begin
 dc.w $33F
 dc.w .LC831-Begin
 dc.w $340
 dc.w .LC832-Begin
 dc.w $341
 dc.w .LC833-Begin
 dc.w $342
 dc.w .LC834-Begin
 dc.w $343
 dc.w .LC835-Begin
 dc.w $344
 dc.w .LC836-Begin
 dc.w $345
 dc.w .LC837-Begin
 dc.w $346
 dc.w .LC838-Begin
 dc.w $347
 dc.w .LC839-Begin
 dc.w $348
 dc.w .LC840-Begin
 dc.w $349
 dc.w .LC841-Begin
 dc.w $34A
 dc.w .LC842-Begin
 dc.w $34B
 dc.w .LC843-Begin
 dc.w $34C
 dc.w .LC844-Begin
 dc.w $34D
 dc.w .LC845-Begin
 dc.w $34E
 dc.w .LC846-Begin
 dc.w $34F
 dc.w .LC847-Begin
 dc.w $350
 dc.w .LC848-Begin
 dc.w $351
 dc.w .LC849-Begin
 dc.w $352
 dc.w .LC850-Begin
 dc.w $353
 dc.w .LC851-Begin
 dc.w $354
 dc.w .LC852-Begin
 dc.w $355
 dc.w .LC853-Begin
 dc.w $356
 dc.w .LC854-Begin
 dc.w $357
 dc.w .LC855-Begin
 dc.w $358
 dc.w .LC856-Begin
 dc.w $359
 dc.w .LC857-Begin
 dc.w $35A
 dc.w .LC858-Begin
 dc.w $35B
 dc.w .LC859-Begin
 dc.w $35C
 dc.w .LC860-Begin
 dc.w $35D
 dc.w .LC861-Begin
 dc.w $35E
 dc.w .LC862-Begin
 dc.w $35F
 dc.w .LC863-Begin
 dc.w $360
 dc.w .LC864-Begin
 dc.w $361
 dc.w .LC865-Begin
 dc.w $362
 dc.w .LC866-Begin
 dc.w $363
 dc.w .LC867-Begin
 dc.w $364
 dc.w .LC868-Begin
 dc.w $365
 dc.w .LC869-Begin
 dc.w $366
 dc.w .LC870-Begin
 dc.w $367
 dc.w .LC871-Begin
 dc.w $368
 dc.w .LC872-Begin
 dc.w $369
 dc.w .LC873-Begin
 dc.w $36A
 dc.w .LC874-Begin
 dc.w $36B
 dc.w .LC875-Begin
 dc.w $36C
 dc.w .LC876-Begin
 dc.w $36D
 dc.w .LC877-Begin
 dc.w $36E
 dc.w .LC878-Begin
 dc.w $36F
 dc.w .LC879-Begin
 dc.w $370
 dc.w .LC880-Begin
 dc.w $371
 dc.w .LC881-Begin
 dc.w $372
 dc.w .LC882-Begin
 dc.w $373
 dc.w .LC883-Begin
 dc.w $374
 dc.w .LC884-Begin
 dc.w $375
 dc.w .LC885-Begin
 dc.w $376
 dc.w .LC886-Begin
 dc.w $377
 dc.w .LC887-Begin
 dc.w $378
 dc.w .LC888-Begin
 dc.w $379
 dc.w .LC889-Begin
 dc.w $37A
 dc.w .LC890-Begin
 dc.w $37B
 dc.w .LC891-Begin
 dc.w $37C
 dc.w .LC892-Begin
 dc.w $37D
 dc.w .LC893-Begin
 dc.w $37E
 dc.w .LC894-Begin
 dc.w $37F
 dc.w .LC895-Begin
 dc.w $380
 dc.w .LC896-Begin
 dc.w $381
 dc.w .LC897-Begin
 dc.w $382
 dc.w .LC898-Begin
 dc.w $383
 dc.w .LC899-Begin
 dc.w $384
 dc.w .LC900-Begin
 dc.w $385
 dc.w .LC901-Begin
 dc.w $386
 dc.w .LC902-Begin
 dc.w $387
 dc.w .LC903-Begin
 dc.w $388
 dc.w .LC904-Begin
 dc.w $389
 dc.w .LC905-Begin
 dc.w $38A
 dc.w .LC906-Begin
 dc.w $38B
 dc.w .LC907-Begin
 dc.w $38C
 dc.w .LC908-Begin
 dc.w $38D
 dc.w .LC909-Begin
 dc.w $38E
 dc.w .LC910-Begin
 dc.w $38F
 dc.w .LC911-Begin
 dc.w $390
 dc.w .LC912-Begin
 dc.w $391
 dc.w .LC913-Begin
 dc.w $392
 dc.w .LC914-Begin
 dc.w $393
 dc.w .LC915-Begin
 dc.w $394
 dc.w .LC916-Begin
 dc.w $395
 dc.w .LC917-Begin
 dc.w $396
 dc.w .LC918-Begin
 dc.w $397
 dc.w .LC919-Begin
 dc.w $398
 dc.w .LC920-Begin
 dc.w $399
 dc.w .LC921-Begin
 dc.w $39A
 dc.w .LC922-Begin
 dc.w $39B
 dc.w .LC923-Begin
 dc.w $39C
 dc.w .LC924-Begin
 dc.w $39D
 dc.w .LC925-Begin
 dc.w $39E
 dc.w .LC926-Begin
 dc.w $39F
 dc.w .LC927-Begin
 dc.w $3A0
 dc.w .LC928-Begin
 dc.w $3A1
 dc.w .LC929-Begin
 dc.w $3A2
 dc.w .LC930-Begin
 dc.w $3A3
 dc.w .LC931-Begin
 dc.w $3A4
 dc.w .LC932-Begin
 dc.w $3A5
 dc.w .LC933-Begin
 dc.w $3A6
 dc.w .LC934-Begin
 dc.w $3A7
 dc.w .LC935-Begin
 dc.w $3A8
 dc.w .LC936-Begin
 dc.w $3A9
 dc.w .LC937-Begin
 dc.w $3AA
 dc.w .LC938-Begin
 dc.w $3AB
 dc.w .LC939-Begin
 dc.w $3AC
 dc.w .LC940-Begin
 dc.w $3AD
 dc.w .LC941-Begin
 dc.w $3AE
 dc.w .LC942-Begin
 dc.w $3AF
 dc.w .LC943-Begin
 dc.w $3B0
 dc.w .LC944-Begin
 dc.w $3B1
 dc.w .LC945-Begin
 dc.w $3B2
 dc.w .LC946-Begin
 dc.w $3B3
 dc.w .LC947-Begin
 dc.w $3B4
 dc.w .LC948-Begin
 dc.w $3B5
 dc.w .LC949-Begin
 dc.w $3B6
 dc.w .LC950-Begin
 dc.w $3B7
 dc.w .LC951-Begin
 dc.w $3B8
 dc.w .LC952-Begin
 dc.w $3B9
 dc.w .LC953-Begin
 dc.w $3BA
 dc.w .LC954-Begin
 dc.w $3BB
 dc.w .LC955-Begin
 dc.w $3BC
 dc.w .LC956-Begin
 dc.w $3BD
 dc.w .LC957-Begin
 dc.w $3BE
 dc.w .LC958-Begin
 dc.w $3BF
 dc.w .LC959-Begin
 dc.w $3C0
 dc.w .LC960-Begin
 dc.w $3C1
 dc.w .LC961-Begin
 dc.w $3C2
 dc.w .LC962-Begin
 dc.w $3C3
 dc.w .LC963-Begin
 dc.w $3C4
 dc.w .LC964-Begin
 dc.w $3C5
 dc.w .LC965-Begin
 dc.w $3C6
 dc.w .LC966-Begin
 dc.w $3C7
 dc.w .LC967-Begin
 dc.w $3C8
 dc.w .LC968-Begin
 dc.w $3C9
 dc.w .LC969-Begin
 dc.w $3CA
 dc.w .LC970-Begin
 dc.w $3CB
 dc.w .LC971-Begin
 dc.w $3CC
 dc.w .LC972-Begin
 dc.w $3CD
 dc.w .LC973-Begin
 dc.w $3CE
 dc.w .LC974-Begin
 dc.w $3CF
 dc.w .LC975-Begin
 dc.w $3D0
 dc.w .LC976-Begin
 dc.w $3D1
 dc.w .LC977-Begin
 dc.w $3D2
 dc.w .LC978-Begin
 dc.w $3D3
 dc.w .LC979-Begin
 dc.w $3D4
 dc.w .LC980-Begin
 dc.w $3D5
 dc.w .LC981-Begin
 dc.w $3D6
 dc.w .LC982-Begin
 dc.w $3D7
 dc.w .LC983-Begin
 dc.w $3D8
 dc.w .LC984-Begin
 dc.w $3D9
 dc.w .LC985-Begin
 dc.w $3DA
 dc.w .LC986-Begin
 dc.w $3DB
 dc.w .LC987-Begin
 dc.w $3DC
 dc.w .LC988-Begin
 dc.w $3DD
 dc.w .LC989-Begin
 dc.w $3DE
 dc.w .LC990-Begin
 dc.w $3DF
 dc.w .LC991-Begin
 dc.w $3E0
 dc.w .LC992-Begin
 dc.w $3E1
 dc.w .LC993-Begin
 dc.w $3E2
 dc.w .LC994-Begin
 dc.w $3E3
 dc.w .LC995-Begin
 dc.w $3E4
 dc.w .LC996-Begin
 dc.w $3E5
 dc.w .LC997-Begin
 dc.w $3E6
 dc.w .LC998-Begin
 dc.w $3E7
 dc.w .LC999-Begin
 dc.w $3E8
 dc.w .LC1000-Begin
 dc.w $3E9
 dc.w .LC1001-Begin
 dc.w $3EA
 dc.w .LC1002-Begin
 dc.w $3EB
 dc.w .LC1003-Begin
 dc.w $3EC
 dc.w .LC1004-Begin
 dc.w $3ED
 dc.w .LC1005-Begin
 dc.w $3EE
 dc.w .LC1006-Begin
 dc.w $3EF
 dc.w .LC1007-Begin
 dc.w $3F0
 dc.w .LC1008-Begin
 dc.w $3F1
 dc.w .LC1009-Begin
 dc.w $3F2
 dc.w .LC1010-Begin
 dc.w $3F3
 dc.w .LC1011-Begin
 dc.w $3F4
 dc.w .LC1012-Begin
 dc.w $3F5
 dc.w .LC1013-Begin
 dc.w $3F6
 dc.w .LC1014-Begin
 dc.w $3F7
 dc.w .LC1015-Begin
 dc.w $3F8
 dc.w .LC1016-Begin
 dc.w $3F9
 dc.w .LC1017-Begin
 dc.w $3FA
 dc.w .LC1018-Begin
 dc.w $3FB
 dc.w .LC1019-Begin
 dc.w $3FC
 dc.w .LC1020-Begin
 dc.w $3FD
 dc.w .LC1021-Begin
 dc.w $3FE
 dc.w .LC1022-Begin
 dc.w $3FF
 dc.w .LC1023-Begin
 dc.w $400
 dc.w .LC1024-Begin
 dc.w $401
 dc.w .LC1025-Begin
 dc.w $402
 dc.w .LC1026-Begin
 dc.w $403
 dc.w .LC1027-Begin
 dc.w $404
 dc.w .LC1028-Begin
 dc.w $405
 dc.w .LC1029-Begin
 dc.w $406
 dc.w .LC1030-Begin
 dc.w $407
 dc.w .LC1031-Begin
 dc.w $408
 dc.w .LC1032-Begin
 dc.w $409
 dc.w .LC1033-Begin
 dc.w $40A
 dc.w .LC1034-Begin
 dc.w $40B
 dc.w .LC1035-Begin
 dc.w $40C
 dc.w .LC1036-Begin
 dc.w $40D
 dc.w .LC1037-Begin
 dc.w $40E
 dc.w .LC1038-Begin
 dc.w $40F
 dc.w .LC1039-Begin
 dc.w $410
 dc.w .LC1040-Begin
 dc.w $411
 dc.w .LC1041-Begin
 dc.w $412
 dc.w .LC1042-Begin
 dc.w $413
 dc.w .LC1043-Begin
 dc.w $414
 dc.w .LC1044-Begin
 dc.w $415
 dc.w .LC1045-Begin
 dc.w $416
 dc.w .LC1046-Begin
 dc.w $417
 dc.w .LC1047-Begin
 dc.w $418
 dc.w .LC1048-Begin
 dc.w $419
 dc.w .LC1049-Begin
 dc.w $41A
 dc.w .LC1050-Begin
 dc.w $41B
 dc.w .LC1051-Begin
 dc.w $41C
 dc.w .LC1052-Begin
 dc.w $41D
 dc.w .LC1053-Begin
 dc.w $41E
 dc.w .LC1054-Begin
 dc.w $41F
 dc.w .LC1055-Begin
 dc.w $420
 dc.w .LC1056-Begin
 dc.w $421
 dc.w .LC1057-Begin
 dc.w $422
 dc.w .LC1058-Begin
 dc.w $423
 dc.w .LC1059-Begin
 dc.w $424
 dc.w .LC1060-Begin
 dc.w $425
 dc.w .LC1061-Begin
 dc.w $426
 dc.w .LC1062-Begin
 dc.w $427
 dc.w .LC1063-Begin
 dc.w $428
 dc.w .LC1064-Begin
 dc.w $429
 dc.w .LC1065-Begin
 dc.w $42A
 dc.w .LC1066-Begin
 dc.w $42B
 dc.w .LC1067-Begin
 dc.w $42C
 dc.w .LC1068-Begin
 dc.w $42D
 dc.w .LC1069-Begin
 dc.w $42E
 dc.w .LC1070-Begin
 dc.w $42F
 dc.w .LC1071-Begin
 dc.w $430
 dc.w .LC1072-Begin
 dc.w $431
 dc.w .LC1073-Begin
 dc.w $432
 dc.w .LC1074-Begin
 dc.w $433
 dc.w .LC1075-Begin
 dc.w $434
 dc.w .LC1076-Begin
 dc.w $435
 dc.w .LC1077-Begin
 dc.w $436
 dc.w .LC1078-Begin
 dc.w $437
 dc.w .LC1079-Begin
 dc.w $438
 dc.w .LC1080-Begin
 dc.w $439
 dc.w .LC1081-Begin
 dc.w $43A
 dc.w .LC1082-Begin
 dc.w $43B
 dc.w .LC1083-Begin
 dc.w $43C
 dc.w .LC1084-Begin
 dc.w $43D
 dc.w .LC1085-Begin
 dc.w $43E
 dc.w .LC1086-Begin
 dc.w $43F
 dc.w .LC1087-Begin
 dc.w $440
 dc.w .LC1088-Begin
 dc.w $441
 dc.w .LC1089-Begin
 dc.w $442
 dc.w .LC1090-Begin
 dc.w $443
 dc.w .LC1091-Begin
 dc.w $444
 dc.w .LC1092-Begin
 dc.w $445
 dc.w .LC1093-Begin
 dc.w $446
 dc.w .LC1094-Begin
 dc.w $447
 dc.w .LC1095-Begin
 dc.w $448
 dc.w .LC1096-Begin
 dc.w $449
 dc.w .LC1097-Begin
 dc.w $44A
 dc.w .LC1098-Begin
 dc.w $44B
 dc.w .LC1099-Begin
 dc.w $44C
 dc.w .LC1100-Begin
 dc.w $44D
 dc.w .LC1101-Begin
 dc.w $44E
 dc.w .LC1102-Begin
 dc.w $44F
 dc.w .LC1103-Begin
 dc.w $450
 dc.w .LC1104-Begin
 dc.w $451
 dc.w .LC1105-Begin
 dc.w $452
 dc.w .LC1106-Begin
 dc.w $453
 dc.w .LC1107-Begin
 dc.w $454
 dc.w .LC1108-Begin
 dc.w $455
 dc.w .LC1109-Begin
 dc.w $456
 dc.w .LC1110-Begin
 dc.w $457
 dc.w .LC1111-Begin
 dc.w $458
 dc.w .LC1112-Begin
 dc.w $459
 dc.w .LC1113-Begin
 dc.w $45A
 dc.w .LC1114-Begin
 dc.w $45B
 dc.w .LC1115-Begin
 dc.w $45C
 dc.w .LC1116-Begin
 dc.w $45D
 dc.w .LC1117-Begin
 dc.w $45E
 dc.w .LC1118-Begin
 dc.w $45F
 dc.w .LC1119-Begin
 dc.w $460
 dc.w .LC1120-Begin
 dc.w $461
 dc.w .LC1121-Begin
 dc.w $462
 dc.w .LC1122-Begin
 dc.w $463
 dc.w .LC1123-Begin
 dc.w $464
 dc.w .LC1124-Begin
 dc.w $465
 dc.w .LC1125-Begin
 dc.w $466
 dc.w .LC1126-Begin
 dc.w $467
 dc.w .LC1127-Begin
 dc.w $468
 dc.w .LC1128-Begin
 dc.w $469
 dc.w .LC1129-Begin
 dc.w $46A
 dc.w .LC1130-Begin
 dc.w $46B
 dc.w .LC1131-Begin
 dc.w $46C
 dc.w .LC1132-Begin
 dc.w $46D
 dc.w .LC1133-Begin
 dc.w $46E
 dc.w .LC1134-Begin
 dc.w $46F
 dc.w .LC1135-Begin
 dc.w $470
 dc.w .LC1136-Begin
 dc.w $471
 dc.w .LC1137-Begin
 dc.w $472
 dc.w .LC1138-Begin
 dc.w $473
 dc.w .LC1139-Begin
 dc.w $474
 dc.w .LC1140-Begin
 dc.w $475
 dc.w .LC1141-Begin
 dc.w $476
 dc.w .LC1142-Begin
 dc.w $477
 dc.w .LC1143-Begin
 dc.w $478
 dc.w .LC1144-Begin
 dc.w $479
 dc.w .LC1145-Begin
 dc.w $47A
 dc.w .LC1146-Begin
 dc.w $47B
 dc.w .LC1147-Begin
 dc.w $47C
 dc.w .LC1148-Begin
 dc.w $47D
 dc.w .LC1149-Begin
 dc.w $47E
 dc.w .LC1150-Begin
 dc.w $47F
 dc.w .LC1151-Begin
 dc.w $480
 dc.w .LC1152-Begin
 dc.w $481
 dc.w .LC1153-Begin
 dc.w $482
 dc.w .LC1154-Begin
 dc.w $483
 dc.w .LC1155-Begin
 dc.w $484
 dc.w .LC1156-Begin
 dc.w $485
 dc.w .LC1157-Begin
 dc.w $486
 dc.w .LC1158-Begin
 dc.w $487
 dc.w .LC1159-Begin
 dc.w $488
 dc.w .LC1160-Begin
 dc.w $489
 dc.w .LC1161-Begin
 dc.w $48A
 dc.w .LC1162-Begin
 dc.w $48B
 dc.w .LC1163-Begin
 dc.w $48C
 dc.w .LC1164-Begin
 dc.w $48D
 dc.w .LC1165-Begin
 dc.w $48E
 dc.w .LC1166-Begin
 dc.w $48F
 dc.w .LC1167-Begin
 dc.w $490
 dc.w .LC1168-Begin
 dc.w $491
 dc.w .LC1169-Begin
 dc.w $492
 dc.w .LC1170-Begin
 dc.w $493
 dc.w .LC1171-Begin
 dc.w $494
 dc.w .LC1172-Begin
 dc.w $495
 dc.w .LC1173-Begin
 dc.w $496
 dc.w .LC1174-Begin
 dc.w $497
 dc.w .LC1175-Begin
 dc.w $498
 dc.w .LC1176-Begin
 dc.w $499
 dc.w .LC1177-Begin
 dc.w $49A
 dc.w .LC1178-Begin
 dc.w $49B
 dc.w .LC1179-Begin
 dc.w $49C
 dc.w .LC1180-Begin
 dc.w $49D
 dc.w .LC1181-Begin
 dc.w $49E
 dc.w .LC1182-Begin
 dc.w $49F
 dc.w .LC1183-Begin
 dc.w $4A0
 dc.w .LC1184-Begin
 dc.w $4A1
 dc.w .LC1185-Begin
 dc.w $4A2
 dc.w .LC1186-Begin
 dc.w $4A3
 dc.w .LC1187-Begin
 dc.w $4A4
 dc.w .LC1188-Begin
 dc.w $4A5
 dc.w .LC1189-Begin
 dc.w $4A6
 dc.w .LC1190-Begin
 dc.w $4A7
 dc.w .LC1191-Begin
 dc.w $4A8
 dc.w .LC1192-Begin
 dc.w $4A9
 dc.w .LC1193-Begin
 dc.w $4AA
 dc.w .LC1194-Begin
 dc.w $4AB
 dc.w .LC1195-Begin
 dc.w $4AC
 dc.w .LC1196-Begin
 dc.w $4AD
 dc.w .LC1197-Begin
 dc.w $4AE
 dc.w .LC1198-Begin
 dc.w $4AF
 dc.w .LC1199-Begin
 dc.w $4B0
 dc.w .LC1200-Begin
 dc.w $4B1
 dc.w .LC1201-Begin
 dc.w $4B2
 dc.w .LC1202-Begin
 dc.w $4B3
 dc.w .LC1203-Begin
 dc.w $4B4
 dc.w .LC1204-Begin
 dc.w $4B5
 dc.w .LC1205-Begin
 dc.w $4B6
 dc.w .LC1206-Begin
 dc.w $4B7
 dc.w .LC1207-Begin
 dc.w $4B8
 dc.w .LC1208-Begin
 dc.w $4B9
 dc.w .LC1209-Begin
 dc.w $4BA
 dc.w .LC1210-Begin
 dc.w $4BB
 dc.w .LC1211-Begin
 dc.w $4BC
 dc.w .LC1212-Begin
 dc.w $4BD
 dc.w .LC1213-Begin
 dc.w $4BE
 dc.w .LC1214-Begin
 dc.w $4BF
 dc.w .LC1215-Begin
 dc.w $4C0
 dc.w .LC1216-Begin
 dc.w $4C1
 dc.w .LC1217-Begin
 dc.w $4C2
 dc.w .LC1218-Begin
 dc.w $4C3
 dc.w .LC1219-Begin
 dc.w $4C4
 dc.w .LC1220-Begin
 dc.w $4C5
 dc.w .LC1221-Begin
 dc.w $4C6
 dc.w .LC1222-Begin
 dc.w $4C7
 dc.w .LC1223-Begin
 dc.w $4C8
 dc.w .LC1224-Begin
 dc.w $4C9
 dc.w .LC1225-Begin
 dc.w $4CA
 dc.w .LC1226-Begin
 dc.w $4CB
 dc.w .LC1227-Begin
 dc.w $4CC
 dc.w .LC1228-Begin
 dc.w $4CD
 dc.w .LC1229-Begin
 dc.w $4CE
 dc.w .LC1230-Begin
 dc.w $4CF
 dc.w .LC1231-Begin
 dc.w $4D0
 dc.w .LC1232-Begin
 dc.w $4D1
 dc.w .LC1233-Begin
 dc.w $4D2
 dc.w .LC1234-Begin
 dc.w $4D3
 dc.w .LC1235-Begin
 dc.w $4D4
 dc.w .LC1236-Begin
 dc.w $4D5
 dc.w .LC1237-Begin
 dc.w $4D6
 dc.w .LC1238-Begin
 dc.w $4D7
 dc.w .LC1239-Begin
 dc.w $4D8
 dc.w .LC1240-Begin
 dc.w $4D9
 dc.w .LC1241-Begin
 dc.w $4DA
 dc.w .LC1242-Begin
 dc.w $4DB
 dc.w .LC1243-Begin
 dc.w $4DC
 dc.w .LC1244-Begin
 dc.w $4DD
 dc.w .LC1245-Begin
 dc.w $4DE
 dc.w .LC1246-Begin
 dc.w $4DF
 dc.w .LC1247-Begin
 dc.w $4E0
 dc.w .LC1248-Begin
 dc.w $4E1
 dc.w .LC1249-Begin
 dc.w $4E2
 dc.w .LC1250-Begin
 dc.w $4E3
 dc.w .LC1251-Begin
 dc.w $4E4
 dc.w .LC1252-Begin
 dc.w $4E5
 dc.w .LC1253-Begin
 dc.w $4E6
 dc.w .LC1254-Begin
 dc.w $4E7
 dc.w .LC1255-Begin
 dc.w $4E8
 dc.w .LC1256-Begin
 dc.w $4E9
 dc.w .LC1257-Begin
 dc.w $4EA
 dc.w .LC1258-Begin
 dc.w $4EB
 dc.w .LC1259-Begin
 dc.w $4EC
 dc.w .LC1260-Begin
 dc.w $4ED
 dc.w .LC1261-Begin
 dc.w $4EE
 dc.w .LC1262-Begin
 dc.w $4EF
 dc.w .LC1263-Begin
 dc.w $4F0
 dc.w .LC1264-Begin
 dc.w $4F1
 dc.w .LC1265-Begin
 dc.w $4F2
 dc.w .LC1266-Begin
 dc.w $4F3
 dc.w .LC1267-Begin
 dc.w $4F4
 dc.w .LC1268-Begin
 dc.w $4F5
 dc.w .LC1269-Begin
 dc.w $4F6
 dc.w .LC1270-Begin
 dc.w $4F7
 dc.w .LC1271-Begin
 dc.w $4F8
 dc.w .LC1272-Begin
 dc.w $4F9
 dc.w .LC1273-Begin
 dc.w $4FA
 dc.w .LC1274-Begin
 dc.w $4FB
 dc.w .LC1275-Begin
 dc.w $4FC
 dc.w .LC1276-Begin
 dc.w $4FD
 dc.w .LC1277-Begin
 dc.w $4FE
 dc.w .LC1278-Begin
 dc.w $4FF
 dc.w .LC1279-Begin
 dc.w $500
 dc.w .LC1280-Begin
 dc.w $501
 dc.w .LC1281-Begin
 dc.w $502
 dc.w .LC1282-Begin
 dc.w $503
 dc.w .LC1283-Begin
 dc.w $504
 dc.w .LC1284-Begin
 dc.w $505
 dc.w .LC1285-Begin
 dc.w $506
 dc.w .LC1286-Begin
 dc.w $507
 dc.w .LC1287-Begin
 dc.w $508
 dc.w .LC1288-Begin
 dc.w $509
 dc.w .LC1289-Begin
 dc.w $50A
 dc.w .LC1290-Begin
 dc.w $50B
 dc.w .LC1291-Begin
 dc.w $50C
 dc.w .LC1292-Begin
 dc.w $50D
 dc.w .LC1293-Begin
 dc.w $50E
 dc.w .LC1294-Begin
 dc.w $50F
 dc.w .LC1295-Begin
 dc.w $510
 dc.w .LC1296-Begin
 dc.w $511
 dc.w .LC1297-Begin
 dc.w $512
 dc.w .LC1298-Begin
 dc.w $513
 dc.w .LC1299-Begin
 dc.w $514
 dc.w .LC1300-Begin
 dc.w $515
 dc.w .LC1301-Begin
 dc.w $516
 dc.w .LC1302-Begin
 dc.w $517
 dc.w .LC1303-Begin
 dc.w $518
 dc.w .LC1304-Begin
 dc.w $519
 dc.w .LC1305-Begin
 dc.w $51A
 dc.w .LC1306-Begin
 dc.w $51B
 dc.w .LC1307-Begin
 dc.w $51C
 dc.w .LC1308-Begin
 dc.w $51D
 dc.w .LC1309-Begin
 dc.w $51E
 dc.w .LC1310-Begin
 dc.w $51F
 dc.w .LC1311-Begin
 dc.w $520
 dc.w .LC1312-Begin
 dc.w $521
 dc.w .LC1313-Begin
 dc.w $522
 dc.w .LC1314-Begin
 dc.w $523
 dc.w .LC1315-Begin
 dc.w $524
 dc.w .LC1316-Begin
 dc.w $525
 dc.w .LC1317-Begin
 dc.w $526
 dc.w .LC1318-Begin
 dc.w $527
 dc.w .LC1319-Begin
 dc.w $528
 dc.w .LC1320-Begin
 dc.w $529
 dc.w .LC1321-Begin
 dc.w $52A
 dc.w .LC1322-Begin
 dc.w $52B
 dc.w .LC1323-Begin
 dc.w $52C
 dc.w .LC1324-Begin
 dc.w $52D
 dc.w .LC1325-Begin
 dc.w $52E
 dc.w .LC1326-Begin
 dc.w $52F
 dc.w .LC1327-Begin
 dc.w $530
 dc.w .LC1328-Begin
 dc.w $531
 dc.w .LC1329-Begin
 dc.w $532
 dc.w .LC1330-Begin
 dc.w $533
 dc.w .LC1331-Begin
 dc.w $534
 dc.w .LC1332-Begin
 dc.w $535
 dc.w .LC1333-Begin
 dc.w $536
 dc.w .LC1334-Begin
 dc.w $537
 dc.w .LC1335-Begin
 dc.w $538
 dc.w .LC1336-Begin
 dc.w $539
 dc.w .LC1337-Begin
 dc.w $53A
 dc.w .LC1338-Begin
 dc.w $53B
 dc.w .LC1339-Begin
 dc.w $53C
 dc.w .LC1340-Begin
 dc.w $53D
 dc.w .LC1341-Begin
 dc.w $53E
 dc.w .LC1342-Begin
 dc.w $53F
 dc.w .LC1343-Begin
 dc.w $540
 dc.w .LC1344-Begin
 dc.w $541
 dc.w .LC1345-Begin
 dc.w $542
 dc.w .LC1346-Begin
 dc.w $543
 dc.w .LC1347-Begin
 dc.w $544
 dc.w .LC1348-Begin
 dc.w $545
 dc.w .LC1349-Begin
 dc.w $546
 dc.w .LC1350-Begin
 dc.w $547
 dc.w .LC1351-Begin
 dc.w $548
 dc.w .LC1352-Begin
 dc.w $549
 dc.w .LC1353-Begin
 dc.w $54A
 dc.w .LC1354-Begin
 dc.w $54B
 dc.w .LC1355-Begin
 dc.w $54C
 dc.w .LC1356-Begin
 dc.w $54D
 dc.w .LC1357-Begin
 dc.w $54E
 dc.w .LC1358-Begin
 dc.w $54F
 dc.w .LC1359-Begin
 dc.w $550
 dc.w .LC1360-Begin
 dc.w $551
 dc.w .LC1361-Begin
 dc.w $552
 dc.w .LC1362-Begin
 dc.w $553
 dc.w .LC1363-Begin
 dc.w $554
 dc.w .LC1364-Begin
 dc.w $555
 dc.w .LC1365-Begin
 dc.w $556
 dc.w .LC1366-Begin
 dc.w $557
 dc.w .LC1367-Begin
 dc.w $558
 dc.w .LC1368-Begin
 dc.w $559
 dc.w .LC1369-Begin
 dc.w $55A
 dc.w .LC1370-Begin
 dc.w $55B
 dc.w .LC1371-Begin
 dc.w $55C
 dc.w .LC1372-Begin
 dc.w $55D
 dc.w .LC1373-Begin
 dc.w $55E
 dc.w .LC1374-Begin
 dc.w $55F
 dc.w .LC1375-Begin
 dc.w $560
 dc.w .LC1376-Begin
 dc.w $561
 dc.w .LC1377-Begin
 dc.w $562
 dc.w .LC1378-Begin
 dc.w $563
 dc.w .LC1379-Begin
 dc.w $564
 dc.w .LC1380-Begin
 dc.w $565
 dc.w .LC1381-Begin
 dc.w $566
 dc.w .LC1382-Begin
 dc.w $567
 dc.w .LC1383-Begin
 dc.w $568
 dc.w .LC1384-Begin
 dc.w $569
 dc.w .LC1385-Begin
 dc.w $56A
 dc.w .LC1386-Begin
 dc.w $56B
 dc.w .LC1387-Begin
 dc.w $56C
 dc.w .LC1388-Begin
 dc.w $56D
 dc.w .LC1389-Begin
 dc.w $56E
 dc.w .LC1390-Begin
 dc.w $56F
 dc.w .LC1391-Begin
 dc.w $570
 dc.w .LC1392-Begin
 dc.w $571
 dc.w .LC1393-Begin
 dc.w $572
 dc.w .LC1394-Begin
 dc.w $573
 dc.w .LC1395-Begin
 dc.w $574
 dc.w .LC1396-Begin
 dc.w $575
 dc.w .LC1397-Begin
 dc.w $576
 dc.w .LC1398-Begin
 dc.w $577
 dc.w .LC1399-Begin
 dc.w $578
 dc.w .LC1400-Begin
 dc.w $579
 dc.w .LC1401-Begin
 dc.w $57A
 dc.w .LC1402-Begin
 dc.w $57B
 dc.w .LC1403-Begin
 dc.w $57C
 dc.w .LC1404-Begin
 dc.w $57D
 dc.w .LC1405-Begin
 dc.w $57E
 dc.w .LC1406-Begin
 dc.w $57F
 dc.w .LC1407-Begin
 dc.w $580
 dc.w .LC1408-Begin
 dc.w $581
 dc.w .LC1409-Begin
 dc.w $582
 dc.w .LC1410-Begin
 dc.w $583
 dc.w .LC1411-Begin
 dc.w $584
 dc.w .LC1412-Begin
 dc.w $585
 dc.w .LC1413-Begin
 dc.w $586
 dc.w .LC1414-Begin
 dc.w $587
 dc.w .LC1415-Begin
 dc.w $588
 dc.w .LC1416-Begin
 dc.w $589
 dc.w .LC1417-Begin
 dc.w $58A
 dc.w .LC1418-Begin
 dc.w $58B
 dc.w .LC1419-Begin
 dc.w $58C
 dc.w .LC1420-Begin
 dc.w $58D
 dc.w .LC1421-Begin
 dc.w $58E
 dc.w .LC1422-Begin
 dc.w $58F
 dc.w .LC1423-Begin
 dc.w $590
 dc.w .LC1424-Begin
 dc.w $591
 dc.w .LC1425-Begin
 dc.w $592
 dc.w .LC1426-Begin
 dc.w $593
 dc.w .LC1427-Begin
 dc.w $594
 dc.w .LC1428-Begin
 dc.w $595
 dc.w .LC1429-Begin
 dc.w $596
 dc.w .LC1430-Begin
 dc.w $597
 dc.w .LC1431-Begin
 dc.w $598
 dc.w .LC1432-Begin
 dc.w $599
 dc.w .LC1433-Begin
 dc.w $59A
 dc.w .LC1434-Begin
 dc.w $59B
 dc.w .LC1435-Begin
 dc.w $59C
 dc.w .LC1436-Begin
 dc.w $59D
 dc.w .LC1437-Begin
 dc.w $59E
 dc.w .LC1438-Begin
 dc.w $59F
 dc.w .LC1439-Begin
 dc.w $5A0
 dc.w .LC1440-Begin
 dc.w $5A1
 dc.w .LC1441-Begin
 dc.w $5A2
 dc.w .LC1442-Begin
 dc.w $5A3
 dc.w .LC1443-Begin
 dc.w $5A4
 dc.w .LC1444-Begin
 dc.w $5A5
 dc.w .LC1445-Begin
 dc.w $5A6
 dc.w .LC1446-Begin
 dc.w $5A7
 dc.w .LC1447-Begin
 dc.w $5A8
 dc.w .LC1448-Begin
 dc.w $5A9
 dc.w .LC1449-Begin
 dc.w $5AA
 dc.w .LC1450-Begin
 dc.w $5AB
 dc.w .LC1451-Begin
 dc.w $5AC
 dc.w .LC1452-Begin
 dc.w $5AD
 dc.w .LC1453-Begin
 dc.w $5AE
 dc.w .LC1454-Begin
 dc.w $5AF
 dc.w .LC1455-Begin
 dc.w $5B0
 dc.w .LC1456-Begin
 dc.w $5B1
 dc.w .LC1457-Begin
 dc.w $5B2
 dc.w .LC1458-Begin
 dc.w $5B3
 dc.w .LC1459-Begin
 dc.w $5B4
 dc.w .LC1460-Begin
 dc.w $5B5
 dc.w .LC1461-Begin
 dc.w $5B6
 dc.w .LC1462-Begin
 dc.w $5B7
 dc.w .LC1463-Begin
 dc.w $5B8
 dc.w .LC1464-Begin
 dc.w $5B9
 dc.w .LC1465-Begin
 dc.w $5BA
 dc.w .LC1466-Begin
 dc.w $5BB
 dc.w .LC1467-Begin
 dc.w $5BC
 dc.w .LC1468-Begin
 dc.w $5BD
 dc.w .LC1469-Begin
 dc.w $5BE
 dc.w .LC1470-Begin
 dc.w $5BF
 dc.w .LC1471-Begin
 dc.w $5C0
 dc.w .LC1472-Begin
 dc.w $5C1
 dc.w .LC1473-Begin
 dc.w $5C2
 dc.w .LC1474-Begin
 dc.w $5C3
 dc.w .LC1475-Begin
 dc.w $5C4
 dc.w .LC1476-Begin
 dc.w $5C5
 dc.w .LC1477-Begin
 dc.w $5C6
 dc.w .LC1478-Begin
 dc.w $5C7
 dc.w .LC1479-Begin
 dc.w $5C8
 dc.w .LC1480-Begin
 dc.w $5C9
 dc.w .LC1481-Begin
 dc.w $5CA
 dc.w .LC1482-Begin
 dc.w $5CB
 dc.w .LC1483-Begin
 dc.w $5CC
 dc.w .LC1484-Begin
 dc.w $5CD
 dc.w .LC1485-Begin
 dc.w $5CE
 dc.w .LC1486-Begin
 dc.w $5CF
 dc.w .LC1487-Begin
 dc.w $5D0
 dc.w .LC1488-Begin
 dc.w $5D1
 dc.w .LC1489-Begin
 dc.w $5D2
 dc.w .LC1490-Begin
 dc.w $5D3
 dc.w .LC1491-Begin
 dc.w $5D4
 dc.w .LC1492-Begin
 dc.w $5D5
 dc.w .LC1493-Begin
 dc.w $5D6
 dc.w .LC1494-Begin
 dc.w $5D7
 dc.w .LC1495-Begin
 dc.w $5D8
 dc.w .LC1496-Begin
 dc.w $5D9
 dc.w .LC1497-Begin
 dc.w $5DA
 dc.w .LC1498-Begin
 dc.w $5DB
 dc.w .LC1499-Begin
 dc.w $5DC
 dc.w .LC1500-Begin
 dc.w $5DD
 dc.w .LC1501-Begin
 dc.w $5DE
 dc.w .LC1502-Begin
 dc.w $5DF
 dc.w .LC1503-Begin
 dc.w $5E0
 dc.w .LC1504-Begin
 dc.w $5E1
 dc.w .LC1505-Begin
 dc.w $5E2
 dc.w .LC1506-Begin
 dc.w $5E3
 dc.w .LC1507-Begin
 dc.w $5E4
 dc.w .LC1508-Begin
 dc.w $5E5
 dc.w .LC1509-Begin
 dc.w $5E6
 dc.w .LC1510-Begin
 dc.w $5E7
 dc.w .LC1511-Begin
 dc.w $5E8
 dc.w .LC1512-Begin
 dc.w $5E9
 dc.w .LC1513-Begin
 dc.w $5EA
 dc.w .LC1514-Begin
 dc.w $5EB
 dc.w .LC1515-Begin
 dc.w $5EC
 dc.w .LC1516-Begin
 dc.w $5ED
 dc.w .LC1517-Begin
 dc.w $5EE
 dc.w .LC1518-Begin
 dc.w $5EF
 dc.w .LC1519-Begin
 dc.w $5F0
 dc.w .LC1520-Begin
 dc.w $5F1
 dc.w .LC1521-Begin
 dc.w $5F2
 dc.w .LC1522-Begin
 dc.w $5F3
 dc.w .LC1523-Begin
 dc.w $5F4
 dc.w .LC1524-Begin
 dc.w $5F5
 dc.w .LC1525-Begin
 dc.w $5F6
 dc.w .LC1526-Begin
 dc.w $5F7
 dc.w .LC1527-Begin
 dc.w $5F8
 dc.w .LC1528-Begin
 dc.w $5F9
 dc.w .LC1529-Begin
 dc.w $5FA
 dc.w .LC1530-Begin
 dc.w $5FB
 dc.w .LC1531-Begin
 dc.w $5FC
 dc.w .LC1532-Begin
 dc.w $5FD
 dc.w .LC1533-Begin
 dc.w $5FE
 dc.w .LC1534-Begin
 dc.w $5FF
 dc.w .LC1535-Begin
 dc.w $600
 dc.w .LC1536-Begin
 dc.w $601
 dc.w .LC1537-Begin
 dc.w $602
 dc.w .LC1538-Begin
 dc.w $603
 dc.w .LC1539-Begin
 dc.w $604
 dc.w .LC1540-Begin
 dc.w $605
 dc.w .LC1541-Begin
 dc.w $606
 dc.w .LC1542-Begin
 dc.w $607
 dc.w .LC1543-Begin
LookupTableEnd:

Strings:
.LC0: dc.b 'FirstWindow',0
.LC1: dc.b 'WinActivate',0
.LC2: dc.b 'WinAttr',0
.LC3: dc.b 'WinBackupToScr',0
.LC4: dc.b 'WinBackground',0
.LC5: dc.b 'WinBegin',0
.LC6: dc.b 'WinBitmapGet',0
.LC7: dc.b 'WinBitmapPut',0
.LC8: dc.b 'WinBitmapSize',0
.LC9: dc.b 'WinCharXY',0
.LC10: dc.b 'WinChar',0
.LC11: dc.b 'WinClose',0
.LC12: dc.b 'WinClr',0
.LC13: dc.b 'WinDeactivate',0
.LC14: dc.b 'WinDupStat',0
.LC15: dc.b 'WinEllipse',0
.LC16: dc.b 'WinFill',0
.LC17: dc.b 'WinFillLines2',0
.LC18: dc.b 'WinFillTriangle',0
.LC19: dc.b 'WinFont',0
.LC20: dc.b 'WinGetCursor',0
.LC21: dc.b 'WinHide',0
.LC22: dc.b 'WinHome',0
.LC23: dc.b 'WinLine',0
.LC24: dc.b 'WinLineNC',0
.LC25: dc.b 'WinLineTo',0
.LC26: dc.b 'WinLineRel',0
.LC27: dc.b 'WinMoveCursor',0
.LC28: dc.b 'WinMoveTo',0
.LC29: dc.b 'WinMoveRel',0
.LC30: dc.b 'WinOpen',0
.LC31: dc.b 'WinPixGet',0
.LC32: dc.b 'WinPixSet',0
.LC33: dc.b 'WinRect',0
.LC34: dc.b 'WinReOpen',0
.LC35: dc.b 'WinScrollH',0
.LC36: dc.b 'WinScrollV',0
.LC37: dc.b 'WinStr',0
.LC38: dc.b 'WinStrXY',0
.LC39: dc.b 'DrawWinBorder',0
.LC40: dc.b 'ScrRectDivide',0
.LC41: dc.b 'RectWinToWin',0
.LC42: dc.b 'RectWinToScr',0
.LC43: dc.b 'UpdateWindows',0
.LC44: dc.b 'MakeWinRect',0
.LC45: dc.b 'ScrToWin',0
.LC46: dc.b 'ScrToHome',0
.LC47: dc.b 'ScrRect',0
.LC48: dc.b 'Dialog',0
.LC49: dc.b 'ROM_CALL_31',0
.LC50: dc.b 'DialogDo',0
.LC51: dc.b 'DialogAdd',0
.LC52: dc.b 'DialogNew',0
.LC53: dc.b 'DrawStaticButton',0
.LC54: dc.b 'MenuBegin',0
.LC55: dc.b 'MenuCheck',0
.LC56: dc.b 'MenuEnd',0
.LC57: dc.b 'MenuKey',0
.LC58: dc.b 'MenuOn',0
.LC59: dc.b 'MenuPopup',0
.LC60: dc.b 'MenuSubStat',0
.LC61: dc.b 'MenuTopStat',0
.LC62: dc.b 'MenuTopSelect',0
.LC63: dc.b 'MenuTopRedef',0
.LC64: dc.b 'MenuGetTopRedef',0
.LC65: dc.b 'MenuAddText',0
.LC66: dc.b 'MenuAddIcon',0
.LC67: dc.b 'MenuNew',0
.LC68: dc.b 'PopupAddText',0
.LC69: dc.b 'PopupNew',0
.LC70: dc.b 'PopupClear',0
.LC71: dc.b 'PopupDo',0
.LC72: dc.b 'PopupText',0
.LC73: dc.b 'MenuUpdate',0
.LC74: dc.b 'Parse2DExpr',0
.LC75: dc.b 'Parse2DMultiExpr',0
.LC76: dc.b 'Print2DExpr',0
.LC77: dc.b 'Parms2D',0
.LC78: dc.b 'display_statements',0
.LC79: dc.b 'Parse1DExpr',0
.LC80: dc.b 'pushkey',0
.LC81: dc.b 'ngetchx',0
.LC82: dc.b 'kbhit',0
.LC83: dc.b 'sprintf',0
.LC84: dc.b 'getcalc',0
.LC85: dc.b 'sendcalc',0
.LC86: dc.b 'LIO_Send',0
.LC87: dc.b 'LIO_Get',0
.LC88: dc.b 'LIO_Receive',0
.LC89: dc.b 'LIO_GetMultiple',0
.LC90: dc.b 'LIO_SendData',0
.LC91: dc.b 'LIO_RecvData',0
.LC92: dc.b 'SymAdd',0
.LC93: dc.b 'SymAddMain',0
.LC94: dc.b 'SymDel',0
.LC95: dc.b 'HSymDel',0
.LC96: dc.b 'SymFind',0
.LC97: dc.b 'SymFindMain',0
.LC98: dc.b 'SymFindHome',0
.LC99: dc.b 'SymMove',0
.LC100: dc.b 'FolderAdd',0
.LC101: dc.b 'FolderCur',0
.LC102: dc.b 'FolderDel',0
.LC103: dc.b 'FolderFind',0
.LC104: dc.b 'FolderGetCur',0
.LC105: dc.b 'FolderOp',0
.LC106: dc.b 'FolderRename',0
.LC107: dc.b 'FolderCount',0
.LC108: dc.b 'SymFindFirst',0
.LC109: dc.b 'SymFindNext',0
.LC110: dc.b 'SymFindPrev',0
.LC111: dc.b 'SymFindFoldername',0
.LC112: dc.b 'AddSymToFolder',0
.LC113: dc.b 'FindSymInFolder',0
.LC114: dc.b 'FolderCurTemp',0
.LC115: dc.b 'FolderAddTemp',0
.LC116: dc.b 'FolderDelTemp',0
.LC117: dc.b 'FolderDelAllTemp',0
.LC118: dc.b 'TempFolderName',0
.LC119: dc.b 'IsMainFolderStr',0
.LC120: dc.b 'ParseSymName',0
.LC121: dc.b 'DerefSym',0
.LC122: dc.b 'HSYMtoName',0
.LC123: dc.b 'StrToTokN',0
.LC124: dc.b 'TokToStrN',0
.LC125: dc.b 'CheckGraphRef',0
.LC126: dc.b 'ClearUserDef',0
.LC127: dc.b 'CheckLinkLockFlag',0
.LC128: dc.b 'TokenizeSymName',0
.LC129: dc.b 'SymCmp',0
.LC130: dc.b 'SymCpy',0
.LC131: dc.b 'SymCpy0',0
.LC132: dc.b 'ValidateSymName',0
.LC133: dc.b 'VarRecall',0
.LC134: dc.b 'VarStore',0
.LC135: dc.b 'VarStoreLink',0
.LC136: dc.b 'QSysProtected',0
.LC137: dc.b 'CheckSysFunc',0
.LC138: dc.b 'GetSysGraphRef',0
.LC139: dc.b 'CheckReservedName',0
.LC140: dc.b 'SymSysVar',0
.LC141: dc.b 'ValidateStore',0
.LC142: dc.b 'ResetSymFlags',0
.LC143: dc.b 'HeapAvail',0
.LC144: dc.b 'HeapAlloc',0
.LC145: dc.b 'HeapAllocESTACK',0
.LC146: dc.b 'HeapAllocHigh',0
.LC147: dc.b 'HeapAllocThrow',0
.LC148: dc.b 'HeapAllocHighThrow',0
.LC149: dc.b 'HeapCompress',0
.LC150: dc.b 'HeapDeref',0
.LC151: dc.b 'HeapFree',0
.LC152: dc.b 'HeapFreeIndir',0
.LC153: dc.b 'HLock',0
.LC154: dc.b 'HeapLock',0
.LC155: dc.b 'HeapGetLock',0
.LC156: dc.b 'HeapMax',0
.LC157: dc.b 'HeapRealloc',0
.LC158: dc.b 'HeapSize',0
.LC159: dc.b 'HeapUnlock',0
.LC160: dc.b 'HeapMoveHigh',0
.LC161: dc.b 'HeapEnd',0
.LC162: dc.b 'HeapAllocPtr',0
.LC163: dc.b 'HeapFreePtr',0
.LC164: dc.b 'NeedStack',0
.LC165: dc.b 'TE_close',0
.LC166: dc.b 'TE_checkSlack',0
.LC167: dc.b 'TE_empty',0
.LC168: dc.b 'TE_focus',0
.LC169: dc.b 'TE_handleEvent',0
.LC170: dc.b 'TE_indicateReadOnly',0
.LC171: dc.b 'TE_isBlank',0
.LC172: dc.b 'TE_open',0
.LC173: dc.b 'TE_openFixed',0
.LC174: dc.b 'TE_pasteText',0
.LC175: dc.b 'TE_reopen',0
.LC176: dc.b 'TE_reopenPlain',0
.LC177: dc.b 'TE_select',0
.LC178: dc.b 'TE_shrinkWrap',0
.LC179: dc.b 'TE_unfocus',0
.LC180: dc.b 'TE_updateCommand',0
.LC181: dc.b '_bcd_math',0
.LC182: dc.b 'bcdadd',0
.LC183: dc.b 'bcdsub',0
.LC184: dc.b 'bcdmul',0
.LC185: dc.b 'bcddiv',0
.LC186: dc.b 'bcdneg',0
.LC187: dc.b 'bcdcmp',0
.LC188: dc.b 'bcdlong',0
.LC189: dc.b 'bcdbcd',0
.LC190: dc.b 'EX_getArg',0
.LC191: dc.b 'EX_getBCD',0
.LC192: dc.b 'EX_stoBCD',0
.LC193: dc.b 'CB_replaceTEXT',0
.LC194: dc.b 'CB_fetchTEXT',0
.LC195: dc.b 'CU_restore',0
.LC196: dc.b 'CU_start',0
.LC197: dc.b 'CU_stop',0
.LC198: dc.b 'EV_captureEvents',0
.LC199: dc.b 'EV_clearPasteString',0
.LC200: dc.b 'EV_getc',0
.LC201: dc.b 'EV_getSplitRect',0
.LC202: dc.b 'EV_notifySwitchGraph',0
.LC203: dc.b 'EV_paintOneWindow',0
.LC204: dc.b 'EV_paintWindows',0
.LC205: dc.b 'EV_restorePainting',0
.LC206: dc.b 'EV_sendEvent',0
.LC207: dc.b 'EV_sendEventSide',0
.LC208: dc.b 'EV_sendString',0
.LC209: dc.b 'EV_setCmdCheck',0
.LC210: dc.b 'EV_setCmdState',0
.LC211: dc.b 'EV_setFKeyState',0
.LC212: dc.b 'EV_startApp',0
.LC213: dc.b 'EV_startSide',0
.LC214: dc.b 'EV_startTask',0
.LC215: dc.b 'EV_suspendPainting',0
.LC216: dc.b 'EV_switch',0
.LC217: dc.b 'MO_currentOptions',0
.LC218: dc.b 'MO_defaults',0
.LC219: dc.b 'MO_digestOptions',0
.LC220: dc.b 'MO_isMultigraphTask',0
.LC221: dc.b 'MO_modeDialog',0
.LC222: dc.b 'MO_notifyModeChange',0
.LC223: dc.b 'MO_sendQuit',0
.LC224: dc.b 'ST_angle',0
.LC225: dc.b 'ST_batt',0
.LC226: dc.b 'ST_busy',0
.LC227: dc.b 'ST_eraseHelp',0
.LC228: dc.b 'ST_folder',0
.LC229: dc.b 'ST_graph',0
.LC230: dc.b 'ST_helpMsg',0
.LC231: dc.b 'ST_modKey',0
.LC232: dc.b 'ST_precision',0
.LC233: dc.b 'ST_readOnly',0
.LC234: dc.b 'ST_stack',0
.LC235: dc.b 'ST_refDsp',0
.LC236: dc.b 'OSCheckBreak',0
.LC237: dc.b 'OSClearBreak',0
.LC238: dc.b 'OSEnableBreak',0
.LC239: dc.b 'OSDisableBreak',0
.LC240: dc.b 'OSRegisterTimer',0
.LC241: dc.b 'OSFreeTimer',0
.LC242: dc.b 'OSTimerCurVal',0
.LC243: dc.b 'OSTimerExpired',0
.LC244: dc.b 'OSTimerRestart',0
.LC245: dc.b 'acos',0
.LC246: dc.b 'asin',0
.LC247: dc.b 'atan',0
.LC248: dc.b 'atan2',0
.LC249: dc.b 'cos',0
.LC250: dc.b 'sin',0
.LC251: dc.b 'tan',0
.LC252: dc.b 'cosh',0
.LC253: dc.b 'sinh',0
.LC254: dc.b 'tanh',0
.LC255: dc.b 'exp',0
.LC256: dc.b 'log',0
.LC257: dc.b 'log10',0
.LC258: dc.b 'modf',0
.LC259: dc.b 'pow',0
.LC260: dc.b 'sqrt',0
.LC261: dc.b 'ceil',0
.LC262: dc.b 'fabs',0
.LC263: dc.b 'floor',0
.LC264: dc.b 'fmod',0
.LC265: dc.b 'top_estack',0
.LC266: dc.b 'next_expression_index',0
.LC267: dc.b 'gr_active',0
.LC268: dc.b 'gr_other',0
.LC269: dc.b 'ABT_dialog',0
.LC270: dc.b 'HomeExecute',0
.LC271: dc.b 'HomePushEStack',0
.LC272: dc.b 'SP_Define',0
.LC273: dc.b 'store_data_var',0
.LC274: dc.b 'recall_data_var',0
.LC275: dc.b 'CharNumber',0
.LC276: dc.b 'spike_optionD',0
.LC277: dc.b 'spike_geo_titles',0
.LC278: dc.b 'spike_in_editor',0
.LC279: dc.b 'dv_create_graph_titles',0
.LC280: dc.b 'spike_titles_in_editor',0
.LC281: dc.b 'dv_findColumn',0
.LC282: dc.b 'spike_chk_gr_dirty',0
.LC283: dc.b 'GetStatValue',0
.LC284: dc.b 'partial_len',0
.LC285: dc.b 'paint_all_except',0
.LC286: dc.b 'EQU_select',0
.LC287: dc.b 'EQU_setStyle',0
.LC288: dc.b 'EQU_getNameInfo',0
.LC289: dc.b 'checkCurrent',0
.LC290: dc.b 'BN_power17Mod',0
.LC291: dc.b 'BN_powerMod',0
.LC292: dc.b 'BN_prodMod',0
.LC293: dc.b 'CAT_dialog',0
.LC294: dc.b 'ROM_CALL_126',0
.LC295: dc.b 'cdecrypt',0
.LC296: dc.b 'ceof',0
.LC297: dc.b 'handleVarLinkKey',0
.LC298: dc.b 'cfindfield',0
.LC299: dc.b 'cgetc',0
.LC300: dc.b 'HeapWalk',0
.LC301: dc.b 'cgetflen',0
.LC302: dc.b 'cgetfnl',0
.LC303: dc.b 'cgetnl',0
.LC304: dc.b 'cgetns',0
.LC305: dc.b 'ROM_CALL_131',0
.LC306: dc.b 'copen',0
.LC307: dc.b 'copensub',0
.LC308: dc.b 'cputhdr',0
.LC309: dc.b 'cputnl',0
.LC310: dc.b 'cputns',0
.LC311: dc.b 'cread',0
.LC312: dc.b 'ctell',0
.LC313: dc.b 'cwrite',0
.LC314: dc.b 'cacos',0
.LC315: dc.b 'casin',0
.LC316: dc.b 'catan',0
.LC317: dc.b 'cacosh',0
.LC318: dc.b 'casinh',0
.LC319: dc.b 'catanh',0
.LC320: dc.b 'ccos',0
.LC321: dc.b 'csin',0
.LC322: dc.b 'ctan',0
.LC323: dc.b 'ccosh',0
.LC324: dc.b 'csinh',0
.LC325: dc.b 'ctanh',0
.LC326: dc.b 'csqrt',0
.LC327: dc.b 'cln',0
.LC328: dc.b 'clog10',0
.LC329: dc.b 'cexp',0
.LC330: dc.b 'CustomBegin',0
.LC331: dc.b 'CustomMenuItem',0
.LC332: dc.b 'CustomEnd',0
.LC333: dc.b 'ReallocExprStruct',0
.LC334: dc.b 'SearchExprStruct',0
.LC335: dc.b 'handleRclKey',0
.LC336: dc.b 'CustomFree',0
.LC337: dc.b 'ERD_dialog',0
.LC338: dc.b 'ERD_process',0
.LC339: dc.b 'ER_throwVar',0
.LC340: dc.b 'ER_catch',0
.LC341: dc.b 'ER_success',0
.LC342: dc.b 'EV_centralDispatcher',0
.LC343: dc.b 'EV_defaultHandler',0
.LC344: dc.b 'EV_eventLoop',0
.LC345: dc.b 'EV_registerMenu',0
.LC346: dc.b 'EX_patch',0
.LC347: dc.b 'EM_abandon',0
.LC348: dc.b 'OSFastArrows',0
.LC349: dc.b 'EM_blockVerifyErase',0
.LC350: dc.b 'AB_getGateArrayVersion',0
.LC351: dc.b 'EM_findEmptySlot',0
.LC352: dc.b 'EM_GC',0
.LC353: dc.b 'EM_moveSymFromExtMem',0
.LC354: dc.b 'EM_moveSymToExtMem',0
.LC355: dc.b 'SetAlphaStatus',0
.LC356: dc.b 'GetAlphaStatus',0
.LC357: dc.b 'EM_survey',0
.LC358: dc.b 'EM_twinSymFromExtMem',0
.LC359: dc.b 'EM_write',0
.LC360: dc.b 'ROM_CALL_168',0
.LC361: dc.b 'FL_addCert',0
.LC362: dc.b 'FL_download',0
.LC363: dc.b 'FL_getHardwareParmBlock',0
.LC364: dc.b 'FL_getCert',0
.LC365: dc.b 'FL_getVerNum',0
.LC366: dc.b 'EQU_deStatus',0
.LC367: dc.b 'cmpstri',0
.LC368: dc.b 'fix_loop_displacements',0
.LC369: dc.b 'FL_write',0
.LC370: dc.b 'fpisanint',0
.LC371: dc.b 'fpisodd',0
.LC372: dc.b 'round12',0
.LC373: dc.b 'round14',0
.LC374: dc.b 'GD_Circle',0
.LC375: dc.b 'GD_Line',0
.LC376: dc.b 'GD_HVLine',0
.LC377: dc.b 'GD_Pen',0
.LC378: dc.b 'GD_Eraser',0
.LC379: dc.b 'GD_Text',0
.LC380: dc.b 'GD_Select',0
.LC381: dc.b 'GD_Contour',0
.LC382: dc.b 'GKeyIn',0
.LC383: dc.b 'GKeyDown',0
.LC384: dc.b 'GKeyFlush',0
.LC385: dc.b 'HelpKeys',0
.LC386: dc.b 'QModeKey',0
.LC387: dc.b 'QSysKey',0
.LC388: dc.b 'WordInList',0
.LC389: dc.b 'BitmapGet',0
.LC390: dc.b 'BitmapInit',0
.LC391: dc.b 'BitmapPut',0
.LC392: dc.b 'BitmapSize',0
.LC393: dc.b 'ScrRectFill',0
.LC394: dc.b 'ScrRectOverlap',0
.LC395: dc.b 'ScrRectScroll',0
.LC396: dc.b 'ScrRectShift',0
.LC397: dc.b 'QScrRectOverlap',0
.LC398: dc.b 'FontGetSys',0
.LC399: dc.b 'FontSetSys',0
.LC400: dc.b 'FontCharWidth',0
.LC401: dc.b 'DrawClipChar',0
.LC402: dc.b 'DrawClipEllipse',0
.LC403: dc.b 'DrawClipLine',0
.LC404: dc.b 'DrawClipPix',0
.LC405: dc.b 'DrawClipRect',0
.LC406: dc.b 'DrawMultiLines',0
.LC407: dc.b 'DrawStrWidth',0
.LC408: dc.b 'FillTriangle',0
.LC409: dc.b 'FillLines2',0
.LC410: dc.b 'SetCurAttr',0
.LC411: dc.b 'SetCurClip',0
.LC412: dc.b 'LineTo',0
.LC413: dc.b 'MoveTo',0
.LC414: dc.b 'ScreenClear',0
.LC415: dc.b 'GetPix',0
.LC416: dc.b 'SaveScrState',0
.LC417: dc.b 'RestoreScrState',0
.LC418: dc.b 'PortSet',0
.LC419: dc.b 'PortRestore',0
.LC420: dc.b 'DrawChar',0
.LC421: dc.b 'DrawFkey',0
.LC422: dc.b 'DrawIcon',0
.LC423: dc.b 'DrawLine',0
.LC424: dc.b 'DrawPix',0
.LC425: dc.b 'DrawStr',0
.LC426: dc.b 'GM_Value',0
.LC427: dc.b 'GM_Intersect',0
.LC428: dc.b 'GM_Integrate',0
.LC429: dc.b 'GM_Inflection',0
.LC430: dc.b 'GM_TanLine',0
.LC431: dc.b 'GM_Math1',0
.LC432: dc.b 'GM_Derivative',0
.LC433: dc.b 'GM_DistArc',0
.LC434: dc.b 'GM_Shade',0
.LC435: dc.b 'YCvtFtoWin',0
.LC436: dc.b 'DlgMessage',0
.LC437: dc.b 'SetGraphMode',0
.LC438: dc.b 'Regraph',0
.LC439: dc.b 'GrAxes',0
.LC440: dc.b 'gr_xres_pixel',0
.LC441: dc.b 'CptFuncX',0
.LC442: dc.b 'XCvtPtoF',0
.LC443: dc.b 'YCvtPtoF',0
.LC444: dc.b 'YCvtFtoP',0
.LC445: dc.b 'XCvtFtoP',0
.LC446: dc.b 'GrLineFlt',0
.LC447: dc.b 'FuncLineFlt',0
.LC448: dc.b 'GrClipLine',0
.LC449: dc.b 'CptDeltax',0
.LC450: dc.b 'CptDeltay',0
.LC451: dc.b 'CkValidDelta',0
.LC452: dc.b 'GR_Pan',0
.LC453: dc.b 'FindFunc',0
.LC454: dc.b 'FindGrFunc',0
.LC455: dc.b 'grFuncName',0
.LC456: dc.b 'gr_initCondName',0
.LC457: dc.b 'CptIndep',0
.LC458: dc.b 'gr_CptIndepInc',0
.LC459: dc.b 'gr_del_locals',0
.LC460: dc.b 'gr_DelFolder',0
.LC461: dc.b 'gr_openFolder',0
.LC462: dc.b 'setup_more_graph_fun',0
.LC463: dc.b 'unlock_more_graph_fun',0
.LC464: dc.b 'execute_graph_func',0
.LC465: dc.b 'cpt_gr_fun',0
.LC466: dc.b 'cpt_gr_param',0
.LC467: dc.b 'cpt_gr_polar',0
.LC468: dc.b 'gr_execute_seq',0
.LC469: dc.b 'CountGrFunc',0
.LC470: dc.b 'FirstSeqPlot',0
.LC471: dc.b 'cleanup_seq_mem',0
.LC472: dc.b 'time_loop',0
.LC473: dc.b 'InitTimeSeq',0
.LC474: dc.b 'seqWebInit',0
.LC475: dc.b 'run_one_seq',0
.LC476: dc.b 'gr_seq_value',0
.LC477: dc.b 'StepCk',0
.LC478: dc.b 'seqStepCk',0
.LC479: dc.b 'rngLen',0
.LC480: dc.b 'gdb_len',0
.LC481: dc.b 'gdb_store',0
.LC482: dc.b 'gdb_recall',0
.LC483: dc.b 'gr_DispLabels',0
.LC484: dc.b 'GraphOrTableCmd',0
.LC485: dc.b 'ck_valid_float',0
.LC486: dc.b 'CreateEmptyList',0
.LC487: dc.b 'QSkipGraphErr',0
.LC488: dc.b 'gr_find_de_result',0
.LC489: dc.b 'InitDEAxesRng',0
.LC490: dc.b 'InitDEMem',0
.LC491: dc.b 'de_loop',0
.LC492: dc.b 'cleanup_de_mem',0
.LC493: dc.b 'gr_de_value',0
.LC494: dc.b 'gr_find_func_index',0
.LC495: dc.b 'CptLastIndepDE',0
.LC496: dc.b 'de_initRes',0
.LC497: dc.b 'gr_del_vars_in_folder',0
.LC498: dc.b 'gr_de_axes_lbl',0
.LC499: dc.b 'gr_execute_de',0
.LC500: dc.b 'gr_delete_fldpic',0
.LC501: dc.b 'gr_remove_fldpic',0
.LC502: dc.b 'gr_add_fldpic',0
.LC503: dc.b 'gr_stopic',0
.LC504: dc.b 'gr_find_el',0
.LC505: dc.b 'deStepCk',0
.LC506: dc.b 'gr_ck_solvergraph',0
.LC507: dc.b 'GR3_addContours',0
.LC508: dc.b 'GraphActivate',0
.LC509: dc.b 'GR3_freeDB',0
.LC510: dc.b 'GR3_handleEvent',0
.LC511: dc.b 'GR3_paint3d',0
.LC512: dc.b 'GR3_xyToWindow',0
.LC513: dc.b 'GS_PlotTrace',0
.LC514: dc.b 'GS_PlotAll',0
.LC515: dc.b 'PlotDel',0
.LC516: dc.b 'PlotPut',0
.LC517: dc.b 'PlotGet',0
.LC518: dc.b 'PlotInit',0
.LC519: dc.b 'PlotDup',0
.LC520: dc.b 'PlotSize',0
.LC521: dc.b 'PlotLookup',0
.LC522: dc.b 'QActivePlots',0
.LC523: dc.b 'QPlotActive',0
.LC524: dc.b 'GT_BackupToScr',0
.LC525: dc.b 'GT_CalcDepVals',0
.LC526: dc.b 'GT_CenterGraphCursor',0
.LC527: dc.b 'GT_CursorKey',0
.LC528: dc.b 'GT_DspFreeTraceCoords',0
.LC529: dc.b 'GT_DspTraceCoords',0
.LC530: dc.b 'GT_DspMsg',0
.LC531: dc.b 'GT_Error',0
.LC532: dc.b 'GT_Format',0
.LC533: dc.b 'GT_FreeTrace',0
.LC534: dc.b 'GT_IncXY',0
.LC535: dc.b 'GT_KeyIn',0
.LC536: dc.b 'GT_QFloatCursorsInRange',0
.LC537: dc.b 'GT_Regraph',0
.LC538: dc.b 'GT_Regraph_if_neccy',0
.LC539: dc.b 'GT_Open',0
.LC540: dc.b 'GT_SaveAs',0
.LC541: dc.b 'GT_SelFunc',0
.LC542: dc.b 'GT_SetGraphRange',0
.LC543: dc.b 'GT_SetCursorXY',0
.LC544: dc.b 'GT_ShowMarkers',0
.LC545: dc.b 'GT_Trace',0
.LC546: dc.b 'GT_ValidGraphRanges',0
.LC547: dc.b 'GT_WinBound',0
.LC548: dc.b 'GT_WinCursor',0
.LC549: dc.b 'GYcoord',0
.LC550: dc.b 'GXcoord',0
.LC551: dc.b 'round12_err',0
.LC552: dc.b 'GT_Set_Graph_Format',0
.LC553: dc.b 'GT_PrintCursor',0
.LC554: dc.b 'GT_DE_Init_Conds',0
.LC555: dc.b 'GZ_Box',0
.LC556: dc.b 'GZ_Center',0
.LC557: dc.b 'GZ_Decimal',0
.LC558: dc.b 'GZ_Fit',0
.LC559: dc.b 'GZ_InOut',0
.LC560: dc.b 'GZ_Integer',0
.LC561: dc.b 'GZ_Previous',0
.LC562: dc.b 'GZ_Recall',0
.LC563: dc.b 'GZ_SetFactors',0
.LC564: dc.b 'GZ_Square',0
.LC565: dc.b 'GZ_Standard',0
.LC566: dc.b 'GZ_Stat',0
.LC567: dc.b 'GZ_Store',0
.LC568: dc.b 'GZ_Trig',0
.LC569: dc.b 'HeapGetHandle',0
.LC570: dc.b 'HeapPtrToHandle',0
.LC571: dc.b 'FreeHandles',0
.LC572: dc.b 'HS_chopFIFO',0
.LC573: dc.b 'HS_countFIFO',0
.LC574: dc.b 'HS_deleteFIFONode',0
.LC575: dc.b 'HS_freeAll',0
.LC576: dc.b 'HS_freeFIFONode',0
.LC577: dc.b 'HS_getAns',0
.LC578: dc.b 'HS_getEntry',0
.LC579: dc.b 'HS_getFIFONode',0
.LC580: dc.b 'HS_popEStack',0
.LC581: dc.b 'HS_newFIFONode',0
.LC582: dc.b 'HS_pushFIFONode',0
.LC583: dc.b 'HToESI',0
.LC584: dc.b 'OSInitKeyInitDelay',0
.LC585: dc.b 'OSInitBetweenKeyDelay',0
.LC586: dc.b 'OSCheckSilentLink',0
.LC587: dc.b 'OSLinkCmd',0
.LC588: dc.b 'OSLinkReset',0
.LC589: dc.b 'OSLinkOpen',0
.LC590: dc.b 'OSLinkClose',0
.LC591: dc.b 'OSReadLinkBlock',0
.LC592: dc.b 'OSWriteLinkBlock',0
.LC593: dc.b 'OSLinkTxQueueInquire',0
.LC594: dc.b 'OSLinkTxQueueActive',0
.LC595: dc.b 'LIO_SendProduct',0
.LC596: dc.b 'MD5Init',0
.LC597: dc.b 'MD5Update',0
.LC598: dc.b 'MD5Final',0
.LC599: dc.b 'MD5Done',0
.LC600: dc.b 'convert_to_TI_92',0
.LC601: dc.b 'gen_version',0
.LC602: dc.b 'is_executable',0
.LC603: dc.b 'NG_RPNToText',0
.LC604: dc.b 'NG_approxESI',0
.LC605: dc.b 'NG_execute',0
.LC606: dc.b 'NG_graphESI',0
.LC607: dc.b 'NG_rationalESI',0
.LC608: dc.b 'NG_tokenize',0
.LC609: dc.b 'NG_setup_graph_fun',0
.LC610: dc.b 'NG_cleanup_graph_fun',0
.LC611: dc.b 'push_END_TAG',0
.LC612: dc.b 'push_LIST_TAG',0
.LC613: dc.b 'tokenize_if_TI_92_or_text',0
.LC614: dc.b 'setjmp',0
.LC615: dc.b 'longjmp',0
.LC616: dc.b 'VarGraphRefBitsClear',0
.LC617: dc.b 'is0',0
.LC618: dc.b 'memcpy',0
.LC619: dc.b 'memmove',0
.LC620: dc.b 'strcpy',0
.LC621: dc.b 'strncpy',0
.LC622: dc.b 'strcat',0
.LC623: dc.b 'strncat',0
.LC624: dc.b 'memcmp',0
.LC625: dc.b 'strcmp',0
.LC626: dc.b 'strncmp',0
.LC627: dc.b 'memchr',0
.LC628: dc.b 'strchr',0
.LC629: dc.b 'strcspn',0
.LC630: dc.b 'strpbrk',0
.LC631: dc.b 'strrchr',0
.LC632: dc.b 'strspn',0
.LC633: dc.b 'strstr',0
.LC634: dc.b 'strtok',0
.LC635: dc.b '_memset',0
.LC636: dc.b 'memset',0
.LC637: dc.b 'strerror',0
.LC638: dc.b 'strlen',0
.LC639: dc.b 'SymAddTwin',0
.LC640: dc.b 'SymDelTwin',0
.LC641: dc.b 'LoadSymFromFindHandle',0
.LC642: dc.b 'MakeHsym',0
.LC643: dc.b 'SymFindPtr',0
.LC644: dc.b '*OSVRegisterTimer*',0
.LC645: dc.b '*OSVFreeTimer*',0
.LC646: dc.b 'sincos',0
.LC647: dc.b 'asinh',0
.LC648: dc.b 'acosh',0
.LC649: dc.b 'atanh',0
.LC650: dc.b 'itrig',0
.LC651: dc.b 'trig',0
.LC652: dc.b 'VarOpen',0
.LC653: dc.b 'VarSaveAs',0
.LC654: dc.b 'VarNew',0
.LC655: dc.b 'VarCreateFolderPopup',0
.LC656: dc.b 'VarSaveTitle',0
.LC657: dc.b 'WinWidth',0
.LC658: dc.b 'WinHeight',0
.LC659: dc.b 'XR_stringPtr',0
.LC660: dc.b 'OSReset',0
.LC661: dc.b 'SumStoChkMem',0
.LC662: dc.b 'OSContrastUp',0
.LC663: dc.b 'OSContrastDn',0
.LC664: dc.b 'OSKeyScan',0
.LC665: dc.b 'OSGetStatKeys',0
.LC666: dc.b 'off',0
.LC667: dc.b 'idle',0
.LC668: dc.b 'OSSetSR',0
.LC669: dc.b 'AB_prodid',0
.LC670: dc.b 'AB_prodname',0
.LC671: dc.b 'AB_serno',0
.LC672: dc.b 'cgetcertrevno',0
.LC673: dc.b 'cgetsn',0
.LC674: dc.b 'de_rng_no_graph',0
.LC675: dc.b 'EV_hook',0
.LC676: dc.b '_ds16u16',0
.LC677: dc.b '_ms16u16',0
.LC678: dc.b '_du16u16',0
.LC679: dc.b '_mu16u16',0
.LC680: dc.b '_ds32s32',0
.LC681: dc.b '_ms32s32',0
.LC682: dc.b '_du32u32',0
.LC683: dc.b '_mu32u32',0
.LC684: dc.b 'assign_between',0
.LC685: dc.b 'did_push_var_val',0
.LC686: dc.b 'does_push_fetch',0
.LC687: dc.b 'delete_list_element',0
.LC688: dc.b 'push_ans_entry',0
.LC689: dc.b 'index_after_match_endtag',0
.LC690: dc.b 'push_indir_name',0
.LC691: dc.b 'push_user_func',0
.LC692: dc.b 'store_func_def',0
.LC693: dc.b 'store_to_subscripted_element',0
.LC694: dc.b 'index_below_display_expression_aux',0
.LC695: dc.b 'get_key_ptr',0
.LC696: dc.b 'get_list_indices',0
.LC697: dc.b 'get_matrix_indices',0
.LC698: dc.b 'init_list_indices',0
.LC699: dc.b 'init_matrix_indices',0
.LC700: dc.b 'push_float_qr_fact',0
.LC701: dc.b 'push_lu_fact',0
.LC702: dc.b 'push_symbolic_qr_fact',0
.LC703: dc.b 'are_expressions_identical',0
.LC704: dc.b 'compare_expressions',0
.LC705: dc.b 'find_error_message',0
.LC706: dc.b 'check_estack_size',0
.LC707: dc.b 'delete_between',0
.LC708: dc.b 'deleted_between',0
.LC709: dc.b 'delete_expression',0
.LC710: dc.b 'deleted_expression',0
.LC711: dc.b 'estack_to_short',0
.LC712: dc.b 'estack_to_ushort',0
.LC713: dc.b 'factor_base_index',0
.LC714: dc.b 'factor_exponent_index',0
.LC715: dc.b 'GetValue',0
.LC716: dc.b 'im_index',0
.LC717: dc.b 'index_numeric_term',0
.LC718: dc.b 'index_of_lead_base_of_lead_term',0
.LC719: dc.b 'index_main_var',0
.LC720: dc.b 'is_advanced_tag',0
.LC721: dc.b 'is_antisymmetric',0
.LC722: dc.b 'is_complex_number',0
.LC723: dc.b 'is_complex0',0
.LC724: dc.b 'is_free_of_tag',0
.LC725: dc.b 'is_independent_of',0
.LC726: dc.b 'is_independent_of_de_seq_vars',0
.LC727: dc.b 'is_independent_of_tail',0
.LC728: dc.b 'is_independent_of_elements',0
.LC729: dc.b 'is_monomial',0
.LC730: dc.b 'is_monomial_in_kernel',0
.LC731: dc.b 'is_narrowly_independent_of',0
.LC732: dc.b 'is_symmetric',0
.LC733: dc.b 'is_tail_independent_of',0
.LC734: dc.b 'lead_base_index',0
.LC735: dc.b 'lead_exponent_index',0
.LC736: dc.b 'lead_factor_index',0
.LC737: dc.b 'lead_term_index',0
.LC738: dc.b 'main_gen_var_index',0
.LC739: dc.b 'map_unary_over_comparison',0
.LC740: dc.b 'min_quantum',0
.LC741: dc.b 'move_between_to_top',0
.LC742: dc.b 'moved_between_to_top',0
.LC743: dc.b 'numeric_factor_index',0
.LC744: dc.b 'push_between',0
.LC745: dc.b 'push_expr_quantum',0
.LC746: dc.b 'push_expr2_quantum',0
.LC747: dc.b 'push_next_arb_int',0
.LC748: dc.b 'push_next_arb_real',0
.LC749: dc.b 'push_next_internal_var',0
.LC750: dc.b 'push_quantum',0
.LC751: dc.b 'push_quantum_pair',0
.LC752: dc.b 'Reductum_index',0
.LC753: dc.b 'Remaining_factors_index',0
.LC754: dc.b 'Re_index',0
.LC755: dc.b 'Reset_estack_size',0
.LC756: dc.b 'Reset_control_flags',0
.LC757: dc.b 'can_be_approxed',0
.LC758: dc.b 'compare_complex_magnitudes',0
.LC759: dc.b 'compare_Floats',0
.LC760: dc.b 'did_push_cnvrt_Float_to_integer',0
.LC761: dc.b 'estack_number_to_Float',0
.LC762: dc.b 'float_class',0
.LC763: dc.b 'frexp10',0
.LC764: dc.b 'gcd_exact_whole_Floats',0
.LC765: dc.b 'is1',0
.LC766: dc.b 'is_Float_exact_whole_number',0
.LC767: dc.b 'is_float_infinity',0
.LC768: dc.b 'is_float_negative_zero',0
.LC769: dc.b 'is_float_positive_zero',0
.LC770: dc.b 'is_float_signed_infinity',0
.LC771: dc.b 'is_float_transfinite',0
.LC772: dc.b 'is_float_unsigned_inf_or_nan',0
.LC773: dc.b 'is_float_unsigned_zero',0
.LC774: dc.b 'is_nan',0
.LC775: dc.b 'likely_approx_to_complex_number',0
.LC776: dc.b 'likely_approx_to_number',0
.LC777: dc.b 'norm1_complex_Float',0
.LC778: dc.b 'push_Float',0
.LC779: dc.b 'push_Float_to_nonneg_int',0
.LC780: dc.b 'push_Float_to_rat',0
.LC781: dc.b 'push_cnvrt_integer_if_whole_nmb',0
.LC782: dc.b 'push_overflow_to_infinity',0
.LC783: dc.b 'push_pow',0
.LC784: dc.b 'push_round_Float',0
.LC785: dc.b 'should_and_did_push_approx_arg2',0
.LC786: dc.b 'signum_Float',0
.LC787: dc.b 'did_push_to_polar',0
.LC788: dc.b 'push_degrees',0
.LC789: dc.b 'push_format',0
.LC790: dc.b 'push_getkey',0
.LC791: dc.b 'push_getfold',0
.LC792: dc.b 'push_getmode',0
.LC793: dc.b 'push_gettype',0
.LC794: dc.b 'push_instring',0
.LC795: dc.b 'push_mrow_aux',0
.LC796: dc.b 'push_part',0
.LC797: dc.b 'push_pttest',0
.LC798: dc.b 'push_pxltest',0
.LC799: dc.b 'push_rand',0
.LC800: dc.b 'push_randpoly',0
.LC801: dc.b 'push_setfold',0
.LC802: dc.b 'push_setgraph',0
.LC803: dc.b 'push_setmode',0
.LC804: dc.b 'push_settable',0
.LC805: dc.b 'push_str_to_expr',0
.LC806: dc.b 'push_string',0
.LC807: dc.b 'push_switch',0
.LC808: dc.b 'push_to_cylin',0
.LC809: dc.b 'push_to_sphere',0
.LC810: dc.b 'cmd_andpic',0
.LC811: dc.b 'cmd_blddata',0
.LC812: dc.b 'cmd_circle',0
.LC813: dc.b 'cmd_clrdraw',0
.LC814: dc.b 'cmd_clrerr',0
.LC815: dc.b 'cmd_clrgraph',0
.LC816: dc.b 'cmd_clrhome',0
.LC817: dc.b 'cmd_clrio',0
.LC818: dc.b 'cmd_clrtable',0
.LC819: dc.b 'cmd_copyvar',0
.LC820: dc.b 'cmd_cubicreg',0
.LC821: dc.b 'cmd_custmoff',0
.LC822: dc.b 'cmd_custmon',0
.LC823: dc.b 'cmd_custom',0
.LC824: dc.b 'cmd_cycle',0
.LC825: dc.b 'cmd_cyclepic',0
.LC826: dc.b 'cmd_delfold',0
.LC827: dc.b 'cmd_delvar',0
.LC828: dc.b 'cmd_dialog',0
.LC829: dc.b 'cmd_disp',0
.LC830: dc.b 'cmd_dispg',0
.LC831: dc.b 'cmd_disphome',0
.LC832: dc.b 'cmd_disptbl',0
.LC833: dc.b 'cmd_drawfunc',0
.LC834: dc.b 'cmd_drawinv',0
.LC835: dc.b 'cmd_drawparm',0
.LC836: dc.b 'cmd_drawpol',0
.LC837: dc.b 'cmd_else',0
.LC838: dc.b 'cmd_endfor',0
.LC839: dc.b 'cmd_endloop',0
.LC840: dc.b 'cmd_endtry',0
.LC841: dc.b 'cmd_endwhile',0
.LC842: dc.b 'cmd_exit',0
.LC843: dc.b 'cmd_expreg',0
.LC844: dc.b 'cmd_fill',0
.LC845: dc.b 'cmd_fnoff',0
.LC846: dc.b 'cmd_fnon',0
.LC847: dc.b 'cmd_for',0
.LC848: dc.b 'cmd_get',0
.LC849: dc.b 'cmd_getcalc',0
.LC850: dc.b 'cmd_goto',0
.LC851: dc.b 'cmd_graph',0
.LC852: dc.b 'cmd_if',0
.LC853: dc.b 'cmd_ifthen',0
.LC854: dc.b 'cmd_input',0
.LC855: dc.b 'cmd_inputstr',0
.LC856: dc.b 'cmd_line',0
.LC857: dc.b 'cmd_linehorz',0
.LC858: dc.b 'cmd_linetan',0
.LC859: dc.b 'cmd_linevert',0
.LC860: dc.b 'cmd_linreg',0
.LC861: dc.b 'cmd_lnreg',0
.LC862: dc.b 'cmd_local',0
.LC863: dc.b 'cmd_lock',0
.LC864: dc.b 'cmd_logistic',0
.LC865: dc.b 'cmd_medmed',0
.LC866: dc.b 'cmd_movevar',0
.LC867: dc.b 'cmd_newdata',0
.LC868: dc.b 'cmd_newfold',0
.LC869: dc.b 'cmd_newpic',0
.LC870: dc.b 'cmd_newplot',0
.LC871: dc.b 'cmd_newprob',0
.LC872: dc.b 'cmd_onevar',0
.LC873: dc.b 'cmd_output',0
.LC874: dc.b 'cmd_passerr',0
.LC875: dc.b 'cmd_pause',0
.LC876: dc.b 'cmd_plotsoff',0
.LC877: dc.b 'cmd_plotson',0
.LC878: dc.b 'cmd_popup',0
.LC879: dc.b 'cmd_powerreg',0
.LC880: dc.b 'cmd_printobj',0
.LC881: dc.b 'cmd_prompt',0
.LC882: dc.b 'cmd_ptchg',0
.LC883: dc.b 'cmd_ptoff',0
.LC884: dc.b 'cmd_pton',0
.LC885: dc.b 'cmd_pttext',0
.LC886: dc.b 'cmd_pxlchg',0
.LC887: dc.b 'cmd_pxlcircle',0
.LC888: dc.b 'cmd_pxlhorz',0
.LC889: dc.b 'cmd_pxlline',0
.LC890: dc.b 'cmd_pxloff',0
.LC891: dc.b 'cmd_pxlon',0
.LC892: dc.b 'cmd_pxltext',0
.LC893: dc.b 'cmd_pxlvert',0
.LC894: dc.b 'cmd_quadreg',0
.LC895: dc.b 'cmd_quartreg',0
.LC896: dc.b 'cmd_randseed',0
.LC897: dc.b 'cmd_rclgdb',0
.LC898: dc.b 'cmd_rclpic',0
.LC899: dc.b 'cmd_rename',0
.LC900: dc.b 'cmd_request',0
.LC901: dc.b 'cmd_return',0
.LC902: dc.b 'cmd_rplcpic',0
.LC903: dc.b 'cmd_send',0
.LC904: dc.b 'cmd_sendcalc',0
.LC905: dc.b 'cmd_sendchat',0
.LC906: dc.b 'cmd_shade',0
.LC907: dc.b 'cmd_showstat',0
.LC908: dc.b 'cmd_sinreg',0
.LC909: dc.b 'cmd_slpline',0
.LC910: dc.b 'cmd_sorta',0
.LC911: dc.b 'cmd_sortd',0
.LC912: dc.b 'cmd_stogdb',0
.LC913: dc.b 'cmd_stopic',0
.LC914: dc.b 'cmd_style',0
.LC915: dc.b 'cmd_table',0
.LC916: dc.b 'cmd_text',0
.LC917: dc.b 'cmd_toolbar',0
.LC918: dc.b 'cmd_trace',0
.LC919: dc.b 'cmd_try',0
.LC920: dc.b 'cmd_twovar',0
.LC921: dc.b 'cmd_unlock',0
.LC922: dc.b 'cmd_while',0
.LC923: dc.b 'cmd_xorpic',0
.LC924: dc.b 'cmd_zoombox',0
.LC925: dc.b 'cmd_zoomdata',0
.LC926: dc.b 'cmd_zoomdec',0
.LC927: dc.b 'cmd_zoomfit',0
.LC928: dc.b 'cmd_zoomin',0
.LC929: dc.b 'cmd_zoomint',0
.LC930: dc.b 'cmd_zoomout',0
.LC931: dc.b 'cmd_zoomprev',0
.LC932: dc.b 'cmd_zoomrcl',0
.LC933: dc.b 'cmd_zoomsqr',0
.LC934: dc.b 'cmd_zoomstd',0
.LC935: dc.b 'cmd_zoomsto',0
.LC936: dc.b 'cmd_zoomtrig',0
.LC937: dc.b 'OSenqueue',0
.LC938: dc.b 'OSdequeue',0
.LC939: dc.b 'OSqinquire',0
.LC940: dc.b 'OSqhead',0
.LC941: dc.b 'OSqclear',0
.LC942: dc.b 'did_push_divide_units',0
.LC943: dc.b 'has_unit_base',0
.LC944: dc.b 'init_unit_system',0
.LC945: dc.b 'is_units_term',0
.LC946: dc.b 'push_auto_units_conversion',0
.LC947: dc.b 'push_unit_system_list',0
.LC948: dc.b 'setup_unit_system',0
.LC949: dc.b 'all_tail',0
.LC950: dc.b 'any_tail',0
.LC951: dc.b 'is_matrix',0
.LC952: dc.b 'is_square_matrix',0
.LC953: dc.b 'is_valid_smap_aggregate',0
.LC954: dc.b 'last_element_index',0
.LC955: dc.b 'map_tail',0
.LC956: dc.b 'map_tail_Int',0
.LC957: dc.b 'push_list_plus',0
.LC958: dc.b 'push_list_times',0
.LC959: dc.b 'push_reversed_tail',0
.LC960: dc.b 'push_sq_matrix_to_whole_number',0
.LC961: dc.b 'push_transpose_aux',0
.LC962: dc.b 'push_zero_partial_column',0
.LC963: dc.b 'remaining_element_count',0
.LC964: dc.b 'push_offset_array',0
.LC965: dc.b 'push_matrix_product',0
.LC966: dc.b 'is_pathname',0
.LC967: dc.b 'next_token',0
.LC968: dc.b 'nonblank',0
.LC969: dc.b 'push_parse_prgm_or_func_text',0
.LC970: dc.b 'push_parse_text',0
.LC971: dc.b 'push_var',0
.LC972: dc.b 'memucmp',0
.LC973: dc.b 'ROM_CALL_3CD',0
.LC974: dc.b 'ROM_CALL_3CE',0
.LC975: dc.b '"EM_GetArchiveMemoryBeginning"',0
.LC976: dc.b 'LIO_SendIdList',0
.LC977: dc.b 'ROM_CALL_3D1',0
.LC978: dc.b '"OO_GetEndOfAllFlashApps"',0
.LC979: dc.b 'ROM_CALL_3D3',0
.LC980: dc.b 'FAccess',0
.LC981: dc.b 'FClose',0
.LC982: dc.b 'FCreate',0
.LC983: dc.b 'FDelete',0
.LC984: dc.b 'FEof',0
.LC985: dc.b 'FFindFirst',0
.LC986: dc.b 'FFindNext',0
.LC987: dc.b 'FGetC',0
.LC988: dc.b 'FGetPos',0
.LC989: dc.b 'FGetSize',0
.LC990: dc.b 'FOpen',0
.LC991: dc.b 'FPutC',0
.LC992: dc.b 'FRead',0
.LC993: dc.b 'FSetPos',0
.LC994: dc.b 'FSetBufSize',0
.LC995: dc.b 'FSetSize',0
.LC996: dc.b 'FSetVer',0
.LC997: dc.b 'FStatus',0
.LC998: dc.b 'FType',0
.LC999: dc.b 'FWrite',0
.LC1000: dc.b 'ROM_CALL_3E8',0
.LC1001: dc.b 'TokenizeName',0
.LC1002: dc.b 'ROM_CALL_3EA',0
.LC1003: dc.b 'KeyYesOrNo',0
.LC1004: dc.b 'ROM_CALL_3EC',0
.LC1005: dc.b 'ROM_CALL_3ED',0
.LC1006: dc.b 'DrawStrWidthP',0
.LC1007: dc.b 'CalcBitmapSize',0
.LC1008: dc.b 'DynMenuChange',0
.LC1009: dc.b 'DynMenuAdd',0
.LC1010: dc.b 'MenuLoad',0
.LC1011: dc.b 'MenuItemDef',0
.LC1012: dc.b 'MenuFlags',0
.LC1013: dc.b 'PopupBegin',0
.LC1014: dc.b 'PopupBeginDo',0
.LC1015: dc.b 'ROM_CALL_3F7',0
.LC1016: dc.b 'ROM_CALL_3F8',0
.LC1017: dc.b 'init_float',0
.LC1018: dc.b 'OO_CondGetAttr',0
.LC1019: dc.b 'OO_Deref',0
.LC1020: dc.b 'OO_GetAppAttr',0
.LC1021: dc.b 'OO_GetAttr',0
.LC1022: dc.b 'OO_HasAttr',0
.LC1023: dc.b 'OO_New',0
.LC1024: dc.b 'OO_SetAppAttr',0
.LC1025: dc.b 'OO_SetAttr',0
.LC1026: dc.b 'OO_NextACB',0
.LC1027: dc.b 'OO_PrevACB',0
.LC1028: dc.b 'OO_InstallSystemHook',0
.LC1029: dc.b 'OO_UninstallSystemHook',0
.LC1030: dc.b 'OO_AppNameToACB',0
.LC1031: dc.b 'stricmp',0
.LC1032: dc.b 'statStart',0
.LC1033: dc.b 'statEnd',0
.LC1034: dc.b 'statFree',0
.LC1035: dc.b 'QstatRcl',0
.LC1036: dc.b 'ROM_CALL_40C',0
.LC1037: dc.b 'ROM_CALL_40D',0
.LC1038: dc.b 'ROM_CALL_40E',0
.LC1039: dc.b 'are_units_consistent',0
.LC1040: dc.b 'ROM_CALL_410',0
.LC1041: dc.b 'WinBitmapSizeExt',0
.LC1042: dc.b 'ROM_CALL_412',0
.LC1043: dc.b 'ROM_CALL_413',0
.LC1044: dc.b 'WinRemove',0
.LC1045: dc.b 'RectWinToScrExt',0
.LC1046: dc.b 'ROM_CALL_416',0
.LC1047: dc.b 'ROM_CALL_417',0
.LC1048: dc.b 'ROM_CALL_418',0
.LC1049: dc.b 'MenuOff',0
.LC1050: dc.b 'QMenuTopSelect',0
.LC1051: dc.b 'ROM_CALL_41B',0
.LC1052: dc.b 'ROM_CALL_41C',0
.LC1053: dc.b 'ROM_CALL_41D',0
.LC1054: dc.b 'ROM_CALL_41E',0
.LC1055: dc.b 'ROM_CALL_41F',0
.LC1056: dc.b 'ROM_CALL_420',0
.LC1057: dc.b 'ROM_CALL_421',0
.LC1058: dc.b 'ROM_CALL_422',0
.LC1059: dc.b 'OO_Destroy',0
.LC1060: dc.b 'ROM_CALL_424',0
.LC1061: dc.b 'OO_appGetPublicStorage',0
.LC1062: dc.b 'OO_appIsMarkedDelete',0
.LC1063: dc.b 'OO_appMarkDelete',0
.LC1064: dc.b 'ROM_CALL_428',0
.LC1065: dc.b 'OO_appSetPublicStorage',0
.LC1066: dc.b 'ROM_CALL_42A',0
.LC1067: dc.b 'ROM_CALL_42B',0
.LC1068: dc.b 'ClientToScr',0
.LC1069: dc.b 'MakeScrRect',0
.LC1070: dc.b 'SetWinClip',0
.LC1071: dc.b 'ROM_CALL_42F',0
.LC1072: dc.b 'pSymPG',0
.LC1073: dc.b 'OSModKeyStatus',0
.LC1074: dc.b 'bottom_estack',0
.LC1075: dc.b 'ROM_CALL_433',0
.LC1076: dc.b 'BatTooLowFlash',0
.LC1077: dc.b 'GetDataType',0
.LC1078: dc.b 'SmapTypeStrings',0
.LC1079: dc.b 'ROM_CALL_437',0
.LC1080: dc.b 'ROM_CALL_438',0
.LC1081: dc.b 'ROM_CALL_439',0
.LC1082: dc.b 'GetFuncPrgmBodyPtr',0
.LC1083: dc.b 'DataTypeNames',0
.LC1084: dc.b 'AM_Beginning_AMS1xx w/o MaxMem',0
.LC1085: dc.b 'FlashMemoryEnd',0
.LC1086: dc.b 'CertificateMemory',0
.LC1087: dc.b 'ReleaseDate',0
.LC1088: dc.b 'ReleaseVersion',0
.LC1089: dc.b '"HeapTable"',0
.LC1090: dc.b 'CTypeTable',0
.LC1091: dc.b 'ST_flags',0
.LC1092: dc.b 'VarOptList',0
.LC1093: dc.b 'ROM_CALL_445',0
.LC1094: dc.b 'ROM_CALL_446',0
.LC1095: dc.b 'MO_option',0
.LC1096: dc.b 'cmd_archive',0
.LC1097: dc.b 'cmd_unarchiv',0
.LC1098: dc.b 'ROM_CALL_44A',0
.LC1099: dc.b 'ROM_CALL_44B',0
.LC1100: dc.b 'clear_error_context',0
.LC1101: dc.b 'push_expression',0
.LC1102: dc.b 'push_simplify',0
.LC1103: dc.b 'push_simplify_statements',0
.LC1104: dc.b 'push_simplify_expressions',0
.LC1105: dc.b 'OO_firstACB',0
.LC1106: dc.b 'EV_appA',0
.LC1107: dc.b 'EV_appB',0
.LC1108: dc.b 'EV_getAppID',0
.LC1109: dc.b 'ROM_CALL_455',0
.LC1110: dc.b 'SetOK',0
.LC1111: dc.b 'ROM_CALL_457',0
.LC1112: dc.b 'EV_appSide',0
.LC1113: dc.b 'ROM_CALL_459',0
.LC1114: dc.b 'ROM_CALL_45A',0
.LC1115: dc.b 'ROM_CALL_45B',0
.LC1116: dc.b 'EV_currentApp',0
.LC1117: dc.b 'EV_runningApp',0
.LC1118: dc.b 'ROM_CALL_45E',0
.LC1119: dc.b 'hStrAppend',0
.LC1120: dc.b 'ROM_CALL_460',0
.LC1121: dc.b 'ROM_CALL_461',0
.LC1122: dc.b 'ROM_CALL_462',0
.LC1123: dc.b 'gr_flags',0
.LC1124: dc.b 'FLOATTAB',0
.LC1125: dc.b 'is_cFloat_agg',0
.LC1126: dc.b 'NG_control',0
.LC1127: dc.b 'primary_tag_list',0
.LC1128: dc.b 'ROM_CALL_468',0
.LC1129: dc.b 'estack_to_float',0
.LC1130: dc.b 'ROM_CALL_46A',0
.LC1131: dc.b 'ROM_CALL_46B',0
.LC1132: dc.b 'GetTagStr',0
.LC1133: dc.b 'EV_errorCode',0
.LC1134: dc.b 'OSOnBreak',0
.LC1135: dc.b 'ROM_CALL_46F',0
.LC1136: dc.b 'ROM_CALL_470',0
.LC1137: dc.b 'ROM_CALL_471',0
.LC1138: dc.b 'LCD_MEM',0
.LC1139: dc.b 'ROM_CALL_473',0
.LC1140: dc.b 'HeapShuffle',0
.LC1141: dc.b 'ERD_notice',0
.LC1142: dc.b 'ERD_dismissNotice',0
.LC1143: dc.b '"OO_GetFlashAppSize"',0
.LC1144: dc.b 'ROM_CALL_478',0
.LC1145: dc.b 'ROM_CALL_479',0
.LC1146: dc.b 'ROM_CALL_47A',0
.LC1147: dc.b 'ROM_CALL_47B',0
.LC1148: dc.b 'WinLineExt',0
.LC1149: dc.b 'ForceFloat',0
.LC1150: dc.b 'ROM_CALL_47E',0
.LC1151: dc.b 'ROM_CALL_47F',0
.LC1152: dc.b 'ROM_CALL_480',0
.LC1153: dc.b 'alphaLockOn',0
.LC1154: dc.b 'alphaLockOff',0
.LC1155: dc.b 'restoreAlphaLock',0
.LC1156: dc.b '"cmd_lu_fact"',0
.LC1157: dc.b '"cmd_qr_fact"',0
.LC1158: dc.b 'ROM_CALL_486',0
.LC1159: dc.b 'ROM_CALL_487',0
.LC1160: dc.b 'is_variable',0
.LC1161: dc.b 'push_substitute_no_simplify',0
.LC1162: dc.b 'push_zstr',0
.LC1163: dc.b 'is_complex_Float',0
.LC1164: dc.b 'ROM_CALL_48C',0
.LC1165: dc.b 'ROM_CALL_48D',0
.LC1166: dc.b 'EV_quit',0
.LC1167: dc.b 'OO_SuperFrame',0
.LC1168: dc.b 'OO_InstallAppHook',0
.LC1169: dc.b 'OO_UninstallAppHook',0
.LC1170: dc.b 'OO_InstallAppHookByName',0
.LC1171: dc.b 'OO_UninstallAppHookByName',0
.LC1172: dc.b 'ROM_CALL_494',0
.LC1173: dc.b 'ROM_CALL_495',0
.LC1174: dc.b 'push_augment',0
.LC1175: dc.b 'push_char',0
.LC1176: dc.b 'push_coldim',0
.LC1177: dc.b 'push_colnorm',0
.LC1178: dc.b 'push_cumsum',0
.LC1179: dc.b '"push_cylin_vector"',0
.LC1180: dc.b 'push_dense_poly_eval',0
.LC1181: dc.b 'push_determinant',0
.LC1182: dc.b 'push_diag',0
.LC1183: dc.b 'push_dimension',0
.LC1184: dc.b 'push_dot_add',0
.LC1185: dc.b 'push_dot_mult',0
.LC1186: dc.b 'push_dot_sub',0
.LC1187: dc.b 'push_dotproduct',0
.LC1188: dc.b 'push_identity_mat',0
.LC1189: dc.b 'push_left',0
.LC1190: dc.b 'push_list_to_mat',0
.LC1191: dc.b 'push_matnorm',0
.LC1192: dc.b 'push_mat_to_list',0
.LC1193: dc.b 'push_mean',0
.LC1194: dc.b 'push_median',0
.LC1195: dc.b 'push_mid',0
.LC1196: dc.b 'push_mrow',0
.LC1197: dc.b 'push_mrowadd',0
.LC1198: dc.b 'push_newlist',0
.LC1199: dc.b 'push_newmat',0
.LC1200: dc.b 'push_ord',0
.LC1201: dc.b '"push_polar_vector"',0
.LC1202: dc.b 'push_prodlist',0
.LC1203: dc.b 'push_radians',0
.LC1204: dc.b 'push_randmat',0
.LC1205: dc.b 'push_randnorm',0
.LC1206: dc.b 'push_red_row_ech',0
.LC1207: dc.b 'push_right',0
.LC1208: dc.b 'push_rotate',0
.LC1209: dc.b 'push_round',0
.LC1210: dc.b 'push_rowadd',0
.LC1211: dc.b 'push_rowdim',0
.LC1212: dc.b 'push_rownorm',0
.LC1213: dc.b 'push_rowswap',0
.LC1214: dc.b 'push_row_echelon',0
.LC1215: dc.b 'push_sequence',0
.LC1216: dc.b 'push_shift',0
.LC1217: dc.b 'push_simult',0
.LC1218: dc.b '"push_sphere_vector"',0
.LC1219: dc.b 'push_stddev',0
.LC1220: dc.b 'push_submat',0
.LC1221: dc.b 'push_sumlist',0
.LC1222: dc.b '"push_to_dd"',0
.LC1223: dc.b '"push_to_dms"',0
.LC1224: dc.b 'push_unitv',0
.LC1225: dc.b 'push_variance',0
.LC1226: dc.b 'ROM_CALL_4CA',0
.LC1227: dc.b 'ROM_CALL_4CB',0
.LC1228: dc.b 'ROM_CALL_4CC',0
.LC1229: dc.b 'push_dot_div',0
.LC1230: dc.b 'push_cross_product',0
.LC1231: dc.b 'push_eigvc',0
.LC1232: dc.b 'push_eigvl',0
.LC1233: dc.b 'ROM_CALL_4D1',0
.LC1234: dc.b '"push_transpose"',0
.LC1235: dc.b 'sf_width',0
.LC1236: dc.b 'strtod',0
.LC1237: dc.b 'ROM_CALL_4D5',0
.LC1238: dc.b 'freeIdList',0
.LC1239: dc.b 'ROM_CALL_4D7',0
.LC1240: dc.b 'ST_progressBar',0
.LC1241: dc.b 'ST_progressUpdate',0
.LC1242: dc.b 'ST_progressIncrement',0
.LC1243: dc.b 'ST_progressDismiss',0
.LC1244: dc.b 'ROM_CALL_4DC',0
.LC1245: dc.b 'push_assignment',0
.LC1246: dc.b 'FirstNonblank',0
.LC1247: dc.b '"is_negative_number"',0
.LC1248: dc.b '"is_positive_number_or_neg0frac"',0
.LC1249: dc.b '"is_negative_number_or_pos0frac_or_pos0int"',0
.LC1250: dc.b '"is_positive_number"',0
.LC1251: dc.b 'push_long_to_integer',0
.LC1252: dc.b 'push_ulong_to_integer',0
.LC1253: dc.b 'push_ushort_to_integer',0
.LC1254: dc.b 'ROM_CALL_4E6',0
.LC1255: dc.b 'push0',0
.LC1256: dc.b 'push1',0
.LC1257: dc.b '"push0_tag"',0
.LC1258: dc.b '"push1_tag"',0
.LC1259: dc.b '"push_half"',0
.LC1260: dc.b '"push_exact0"',0
.LC1261: dc.b '"push_exact_minus1"',0
.LC1262: dc.b '"push_minus1"',0
.LC1263: dc.b '"push_minus1_tag"',0
.LC1264: dc.b '"push_minus_half"',0
.LC1265: dc.b 'push_negate_quantum_as_negint',0
.LC1266: dc.b '"push_exact1"',0
.LC1267: dc.b '"OO_GetFirstFlashAppSectorAddress"',0
.LC1268: dc.b 'ROM_CALL_4F4',0
.LC1269: dc.b 'OO_DestroyAll',0
.LC1270: dc.b 'ROM_CALL_4F6',0
.LC1271: dc.b 'push_approx',0
.LC1272: dc.b 'push_internal_simplify',0
.LC1273: dc.b '"push_polar_to_rect_x"',0
.LC1274: dc.b '"push_polar_to_rect_y"',0
.LC1275: dc.b 'ROM_CALL_4FB',0
.LC1276: dc.b 'FiftyMsecTick',0
.LC1277: dc.b 'ROM_CALL_4FD',0
.LC1278: dc.b 'ROM_CALL_4FE',0
.LC1279: dc.b 'strtol',0
.LC1280: dc.b 'WinBeginPaint',0
.LC1281: dc.b 'WinEndPaint',0
.LC1282: dc.b 'ROM_CALL_502',0
.LC1283: dc.b 'CU_cursorState',0
.LC1284: dc.b 'ROM_CALL_504',0
.LC1285: dc.b 'ROM_CALL_505',0
.LC1286: dc.b 'HomeAlone',0
.LC1287: dc.b 'ER_throwFrame',0
.LC1288: dc.b 'is_minus1',0
.LC1289: dc.b 'is_pos_int_and_eq_quantum',0
.LC1290: dc.b 'is_reciprocal_of_quantum',0
.LC1291: dc.b 'is_whole_number',0
.LC1292: dc.b 'integer_non_unknown',0
.LC1293: dc.b 'compare_numbers',0
.LC1294: dc.b 'push_quantum_as_nonnegative_int',0
.LC1295: dc.b 'push_reciprocal_of_quantum',0
.LC1296: dc.b 'push_minus_recip_of_quantum',0
.LC1297: dc.b 'push_quantum_pair_as_pos_frac',0
.LC1298: dc.b 'push_pi',0
.LC1299: dc.b 'push_pi_on_quantum',0
.LC1300: dc.b 'push_gcd_numbers',0
.LC1301: dc.b 'push_is_prime',0
.LC1302: dc.b 'get_lb',0
.LC1303: dc.b 'get_ub',0
.LC1304: dc.b 'add_to_top',0
.LC1305: dc.b 'replace_top2_with_sum',0
.LC1306: dc.b 'push_difference',0
.LC1307: dc.b 'subtract_from_top',0
.LC1308: dc.b 'replace_top2_with_difference',0
.LC1309: dc.b 'add1_to_top',0
.LC1310: dc.b 'subtract1_from_top',0
.LC1311: dc.b 'push_arg_plus_1',0
.LC1312: dc.b 'push_arg_minus_1',0
.LC1313: dc.b 'push_product',0
.LC1314: dc.b 'times_top',0
.LC1315: dc.b 'replace_top2_with_prod',0
.LC1316: dc.b 'push_negate',0
.LC1317: dc.b 'negate_top',0
.LC1318: dc.b 'push_ratio',0
.LC1319: dc.b 'divide_top',0
.LC1320: dc.b 'replace_top2_with_ratio',0
.LC1321: dc.b 'raise_to_top',0
.LC1322: dc.b 'replace_top2_with_pow',0
.LC1323: dc.b 'push_sqrt',0
.LC1324: dc.b 'push_square',0
.LC1325: dc.b 'replace_top_with_reciprocal',0
.LC1326: dc.b 'push_exp',0
.LC1327: dc.b 'push_ln',0
.LC1328: dc.b 'push_log10',0
.LC1329: dc.b 'push_sin2',0
.LC1330: dc.b 'push_sin',0
.LC1331: dc.b 'push_cos',0
.LC1332: dc.b 'push_tan',0
.LC1333: dc.b 'push_trig',0
.LC1334: dc.b 'push_asin',0
.LC1335: dc.b 'push_acos',0
.LC1336: dc.b 'push_atan',0
.LC1337: dc.b 'push_rec_to_angle',0
.LC1338: dc.b 'push_sinh',0
.LC1339: dc.b 'push_cosh',0
.LC1340: dc.b 'push_tanh',0
.LC1341: dc.b 'push_asinh',0
.LC1342: dc.b 'push_acosh',0
.LC1343: dc.b 'push_atanh',0
.LC1344: dc.b 'push_factorial',0
.LC1345: dc.b 'push_perm',0
.LC1346: dc.b 'push_comb',0
.LC1347: dc.b 'push_abs',0
.LC1348: dc.b 'push_sign',0
.LC1349: dc.b 'push_re',0
.LC1350: dc.b 'push_im',0
.LC1351: dc.b 'push_conj',0
.LC1352: dc.b 'push_phase',0
.LC1353: dc.b 'push_r_cis',0
.LC1354: dc.b 'push_floor',0
.LC1355: dc.b 'push_ceiling',0
.LC1356: dc.b 'push_mod',0
.LC1357: dc.b 'push_integer_part',0
.LC1358: dc.b 'push_fractional_part',0
.LC1359: dc.b 'push_integer_quotient',0
.LC1360: dc.b 'push_integer_remainder',0
.LC1361: dc.b 'push_integer_gcd',0
.LC1362: dc.b 'push_integer_lcm',0
.LC1363: dc.b 'push_min1',0
.LC1364: dc.b 'push_max1',0
.LC1365: dc.b 'push_percent',0
.LC1366: dc.b 'is_term_improper',0
.LC1367: dc.b 'push_make_proper',0
.LC1368: dc.b 'push_standardize',0
.LC1369: dc.b 'replace_top2_with_imre',0
.LC1370: dc.b 'push_numerator',0
.LC1371: dc.b 'push_denominator',0
.LC1372: dc.b 'push_nonnumeric_factors',0
.LC1373: dc.b 'push_constant_factors',0
.LC1374: dc.b 'push_nonconstant_factors',0
.LC1375: dc.b 'push_dependent_factors',0
.LC1376: dc.b 'push_independent_factors',0
.LC1377: dc.b 'push_but_factor',0
.LC1378: dc.b 'index_rmng_fctrs_start_fctr_tag',0
.LC1379: dc.b 'index_rmng_fctrs_start_base_tag',0
.LC1380: dc.b 'index_rmng_fctrs_start_base',0
.LC1381: dc.b 'index_rmng_factor',0
.LC1382: dc.b 'push_constant_terms',0
.LC1383: dc.b 'push_nonconstant_terms',0
.LC1384: dc.b 'push_dependent_terms',0
.LC1385: dc.b 'push_independent_terms',0
.LC1386: dc.b 'push_but_term',0
.LC1387: dc.b 'is_polynomial_in_var_or_kern',0
.LC1388: dc.b 'is_totally_polynomial',0
.LC1389: dc.b 'is_neg_lead_numr_coef_re_part',0
.LC1390: dc.b 'next_var_or_kernel_index',0
.LC1391: dc.b 'push_var_kern_tail',0
.LC1392: dc.b 'push_poly_deg_in_var_or_kernel',0
.LC1393: dc.b 'linear_degree',0
.LC1394: dc.b 'did_push_lincf',0
.LC1395: dc.b 'is_positive',0
.LC1396: dc.b 'is_nonnegative',0
.LC1397: dc.b 'is_negative',0
.LC1398: dc.b 'is_nonpositive',0
.LC1399: dc.b 'is_never0',0
.LC1400: dc.b 'is_equivalent_to',0
.LC1401: dc.b 'and_onto_top',0
.LC1402: dc.b 'replace_top2_with_and',0
.LC1403: dc.b 'or_onto_top',0
.LC1404: dc.b 'replace_top2_with_or',0
.LC1405: dc.b 'push_when',0
.LC1406: dc.b 'lead_disjunct_term_index',0
.LC1407: dc.b 'remaining_disjuncts_index',0
.LC1408: dc.b 'lead_conjunct_factor_index',0
.LC1409: dc.b 'remaining_conjuncts_index',0
.LC1410: dc.b 'push_but_conjunct_factor',0
.LC1411: dc.b 'push_nSolve',0
.LC1412: dc.b 'push_solve',0
.LC1413: dc.b 'push_csolve',0
.LC1414: dc.b 'push_zeros',0
.LC1415: dc.b 'push_czeros',0
.LC1416: dc.b 'did_push_series',0
.LC1417: dc.b 'push_min',0
.LC1418: dc.b 'push_max',0
.LC1419: dc.b 'push_desolve',0
.LC1420: dc.b 'push_div_dif_1f',0
.LC1421: dc.b 'push_div_dif_1c',0
.LC1422: dc.b 'ROM_CALL_58E',0
.LC1423: dc.b 'LOC_getLocalDateFormat',0
.LC1424: dc.b 'LOC_formatDate',0
.LC1425: dc.b 'LOC_localVersionDate',0
.LC1426: dc.b 'FKeyI_H',0
.LC1427: dc.b 'is_constant',0
.LC1428: dc.b 'push_sum',0
.LC1429: dc.b 'push_exponentiate',0
.LC1430: dc.b 'push_dot_exponentiate',0
.LC1431: dc.b 'push_reciprocal',0
.LC1432: dc.b 'push_min2',0
.LC1433: dc.b 'push_max2',0
.LC1434: dc.b 'push_expand',0
.LC1435: dc.b 'push_comdenom',0
.LC1436: dc.b 'push_factor',0
.LC1437: dc.b 'push_poly_qr',0
.LC1438: dc.b 'push_gcd_then_cofactors',0
.LC1439: dc.b 'index_reductum_with_tag_base',0
.LC1440: dc.b 'has_different_variable',0
.LC1441: dc.b 'index_if_pushed_binomial_info',0
.LC1442: dc.b 'index_if_pushed_qquad_info',0
.LC1443: dc.b 'push_equals',0
.LC1444: dc.b 'push_not_equals',0
.LC1445: dc.b 'push_greater_than',0
.LC1446: dc.b 'push_less_than',0
.LC1447: dc.b 'push_greater_than_or_equals',0
.LC1448: dc.b 'push_less_than_or_equals',0
.LC1449: dc.b 'is_real',0
.LC1450: dc.b 'push_not',0
.LC1451: dc.b 'push_and',0
.LC1452: dc.b 'push_or',0
.LC1453: dc.b 'push_lim',0
.LC1454: dc.b 'push_1st_derivative',0
.LC1455: dc.b 'push_nth_derivative',0
.LC1456: dc.b 'did_push_approx_inflection_point',0
.LC1457: dc.b 'did_push_anti_deriv',0
.LC1458: dc.b 'push_def_int',0
.LC1459: dc.b 'push_nint',0
.LC1460: dc.b 'push_summation',0
.LC1461: dc.b 'push_extended_prod',0
.LC1462: dc.b 'replace_top_with_post_simplified',0
.LC1463: dc.b 'is_undefined',0
.LC1464: dc.b 'did_map_aggregate_arg',0
.LC1465: dc.b 'push_substitute_simplify',0
.LC1466: dc.b 'abs',0
.LC1467: dc.b 'div',0
.LC1468: dc.b 'labs',0
.LC1469: dc.b 'ldiv',0
.LC1470: dc.b 'push_substitute_using_such_that',0
.LC1471: dc.b 'estack_max_index',0
.LC1472: dc.b 'RAtionalize_tol',0
.LC1473: dc.b 'IM_re_tol',0
.LC1474: dc.b 'ARb_real_count',0
.LC1475: dc.b 'ARb_int_count',0
.LC1476: dc.b 'ROM_CALL_5C4',0
.LC1477: dc.b 'ROM_CALL_5C5',0
.LC1478: dc.b 'ROM_CALL_5C6',0
.LC1479: dc.b 'ROM_CALL_5C7',0
.LC1480: dc.b 'ROM_CALL_5C8',0
.LC1481: dc.b 'ROM_CALL_5C9',0
.LC1482: dc.b 'ROM_CALL_5CA',0
.LC1483: dc.b 'ROM_CALL_5CB',0
.LC1484: dc.b 'ROM_CALL_5CC',0
.LC1485: dc.b 'Integer0Index',0
.LC1486: dc.b 'Integer1Index',0
.LC1487: dc.b 'IntegerMinus1Index',0
.LC1488: dc.b 'Float0Index',0
.LC1489: dc.b 'Float1Index',0
.LC1490: dc.b 'FloatMinus1Index',0
.LC1491: dc.b 'FloatPiIndex',0
.LC1492: dc.b 'FloatExp1Index',0
.LC1493: dc.b 'index_true',0
.LC1494: dc.b 'index_false',0
.LC1495: dc.b 'NG_such_that_index',0
.LC1496: dc.b 'ROM_CALL_5D8',0
.LC1497: dc.b 'errno',0
.LC1498: dc.b 'EX_getBasecodeParmBlock',0
.LC1499: dc.b 'WinStrXYWrap',0
.LC1500: dc.b 'RM_Type',0
.LC1501: dc.b '"HS_FirstFIFONodeHandle"',0
.LC1502: dc.b '"HS_MaxExpressions"',0
.LC1503: dc.b 'EV_flags',0
.LC1504: dc.b 'FloatHalfIndex',0
.LC1505: dc.b 'Integer2Index',0
.LC1506: dc.b 'ROM_CALL_5E2',0
.LC1507: dc.b 'OSCheckLinkOpen',0
.LC1508: dc.b 'ROM_CALL_5E4',0
.LC1509: dc.b 'ROM_CALL_5E5',0
.LC1510: dc.b 'ROM_CALL_5E6',0
.LC1511: dc.b 'ROM_CALL_5E7',0
.LC1512: dc.b 'ROM_CALL_5E8',0
.LC1513: dc.b 'ROM_CALL_5E9',0
.LC1514: dc.b 'ROM_CALL_5EA',0
.LC1515: dc.b 'ROM_CALL_5EB',0
.LC1516: dc.b 'ROM_CALL_5EC',0
.LC1517: dc.b 'ROM_CALL_5ED',0
.LC1518: dc.b 'ROM_CALL_5EE',0
.LC1519: dc.b 'ROM_CALL_5EF',0
.LC1520: dc.b 'ROM_CALL_5F0',0
.LC1521: dc.b 'DateAndTime_SetDlg',0
.LC1522: dc.b 'DateAndTime_Set',0
.LC1523: dc.b 'DateAndTime_Get',0
.LC1524: dc.b 'DayOfTheWeek',0
.LC1525: dc.b 'ClockOn',0
.LC1526: dc.b 'ClockOff',0
.LC1527: dc.b 'IsClockOn',0
.LC1528: dc.b 'Timer_Start',0
.LC1529: dc.b 'Timer_Value',0
.LC1530: dc.b 'TimeZone_Get',0
.LC1531: dc.b 'TimeZone_Set',0
.LC1532: dc.b 'DateFormat_Get',0
.LC1533: dc.b 'DateFormat_Set',0
.LC1534: dc.b 'DateStr',0
.LC1535: dc.b 'TimeFormat_Get',0
.LC1536: dc.b 'TimeFormat_Set',0
.LC1537: dc.b 'TimeStr',0
.LC1538: dc.b '*readHandshake*',0
.LC1539: dc.b '*writeHandshake*',0
.LC1540: dc.b '*startBPTimer*',0
.LC1541: dc.b '*stopBPTimer*',0
.LC1542: dc.b 'ROM_CALL_606',0
.LC1543: dc.b '"GetFlashMemoryEnd"',0
