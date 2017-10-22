NUMLOW EQU R2
NUMHIGH EQU R3
RESLOW EQU R4
RESHIGH EQU R5

;Accumulator stores after mul the L byte of the result
ORG 00h
JMP main

main:
	MOV NUMHIGH, #0x00
	MOV NUMLOW, #0xFF
	CALL square_ushort
infinity_loop:
	JMP $


square_ushort:
	CLR F0				;clear the flag bit which will hold the carry value, so the addition can not change it
same_bytes_low:
	MOV A, NUMLOW		;multiply the low bytes with each other
	MOV B, A
	MUL AB
	MOV RESLOW, A
	MOV RESHIGH, B
same_bytes_high:
	MOV A, NUMHIGH		;multiply the low bytes with each other, they won't fit into 16 bits, so this is only for the overflow check
	MOV B, A
	MUL AB
	ORL A, B
	JZ different_bytes	;if the higher bytes are not zero, then the overflow flag should be set
	SETB F0
different_bytes:
	MOV A, NUMLOW
	MOV B, NUMHIGH
	MUL AB
	RLC A				;calculating the square of a number needs l*h + h*l, which equals 2*h*l
	ORL C, F0			;if a bit was shifted out, taht would have been caused overflow
	MOV F0, C
	ADD A, RESHIGH
	ORL C, F0			;save the carry of the addition
	MOV F0, C
	MOV RESHIGH, A
	MOV A, B			;the value in B - if not zero - will cause overflow
	JZ b_carry
	SETB F0

b_carry:
	MOV A, RESLOW
	MOV NUMLOW, A
	MOV A, RESHIGH
	MOV NUMHIGH, A
	MOV C, F0
	
	RET

END



	
