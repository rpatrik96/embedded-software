; Reizinger Patrik
; W5PDBR
; Feladatki�r�s:
; Bels� mem�ri�ban 32 karakteres gy�r�s t�rol� k�sz�t�se bet�teli �s kiv�teli lehet�s�ggel.
; �r� �s olvas� pointer mutatja a k�vetkez� szabad hely ill. kivehet� karakter c�m�t.
; CY=1 jelzi, ha a t�rol� betelt.
; A program k�t szubrutint tartalmazzon: puffer �r�sa �s puffer olvas�sa.
; A puffer glob�lis adatter�letk�nt �lland�an l�tezik, indul�skor �res.
; Bemenet mindk�t rutinnak: t�rol� kezd�c�me a mem�ri�ban (mutat�),
; �r� �s olvas� pointer aktu�lis �llapota, beteend� karakter (�r�s eset�n).
; Kimenet: kivett karakter (olvas�s), pointerek aktu�lis �llapota, CY.

BUF_BEGIN EQU 0x30		;buffer kezd�c�me (IRAM)
BUF_END EQU 0x4F		;buffer utols� elem�nek c�me (0x30 + 32 - 1)
BUF_LEN EQU 32			;a buffer hossza
		
BUF_RD EQU R0			;olvas� pointer
BUF_WR EQU R1			;�r� pointer
DATA_IN_OUT EQU R2		;regiszter a be-, ill. kimenetnek
NUM_DATA EQU R3			;a karakterek sz�m�t t�rol� regiszter
IS_EMPTY EQU F0			;a specifik�ci� kib�v�t�se: visszajelz�s, ha �res a buffer



ORG 00H
JMP main

main:
	MOV BUF_RD, #BUF_BEGIN		;pointer inicializ�ci�k
	MOV BUF_WR, #BUF_BEGIN
	MOV NUM_DATA, #0x00			;elemsz�m null�z�sa

	MOV DATA_IN_OUT, #0x66		;adatok a teszthez
	MOV R4, #BUF_LEN
	INC R4
fill_loop:						;felt�ltj�k a buffert, a v�g�n CY=1
	CALL write_buf
	DJNZ R4, fill_loop

	MOV R4, #BUF_LEN
	INC R4
read_loop:						;olvas�s,a  v�g�m F0=1
	CALL read_buf
	DJNZ R4, read_loop

infinity_loop:
	JMP $


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;write_buf
;Funkci�:
;			- a cirkul�ris bufferbe t�rt�n� �r�s kezel�se
;			- teli buffer jelz�se (CY flag)
;Bemenetek:
;			- BUF_WR: az �r�st v�gz� pointer
;			- DATA_IN_OUT: az �rni k�v�nt adatbyte
;			- NUM_DATA: a bufferben l�v� byteok sz�ma	
;			- BUF_BEGIN: a buffer kezd�c�me
;			- BUF_END: a buffer befejez� c�me
;			- BUF_LEN: a buffer hossza
;Kimenetek:
;			- BUF_WR: az �r�st v�gz� pointer eggyel n�velve (ha nem volt m�r tele a buffer)
;			- NUM_DATA: a bufferen l�v� byteok sz�ma	eggyel n�velve (ha nem volt m�r tele a buffer)
;			- CY: a tele buffert jelz� flag
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
write_buf:
	MOV A, #BUF_LEN		;teli buffer ellen�rz�se (ebben a sorrendben CY nem �ll�t�dik)
	SUBB A, NUM_DATA
	JZ full_buf
	MOV A, DATA_IN_OUT	;karakter �r�sa
	MOV @BUF_WR, A
	INC BUF_WR			;pointer posztinkremens
	INC NUM_DATA		;elemsz�mot is n�velj�k
	MOV A, #BUF_END		;megn�zz�k, hogy a pointer "t�lcsordult-e"
	SUBB A, BUF_WR
	JNC write_ready
	MOV BUF_WR, #BUF_BEGIN	;pointer vissza�ll�t�sa a cirkul�ris buffer elej�re
	CLR C				;t�r�lj�k a carryt (a cirkularit�s ellen�rz�s be�ll�tja)
	JMP write_ready
full_buf:
	SETB C				;teli buffer jelz�se
write_ready:
	RET


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;read_buf
;Funkci�:
;			- a cirkul�ris bufferb�l t�rt�n� olvas�s kezel�se
;			- �res buffer jelz�se (F0 flag, a programban IS_EMPTY aliassal)
;Bemenetek:
;			- BUF_RD: az olvas�st v�gz� pointer
;			- NUM_DATA: a bufferben l�v� byteok sz�ma	
;			- BUF_BEGIN: a buffer kezd�c�me
;			- BUF_END: a buffer befejez� c�me
;Kimenetek:
;			- BUF_RD: az �r�st v�gz� pointer eggyel n�velve (ha nem volt m�r �res a buffer)
;			- NUM_DATA: a bufferen l�v� byteok sz�ma	eggyel cs�kkentve (ha nem volt m�r �res a buffer)
;			- DATA_IN_OUT: a kiolvasott adatbyte
;			- IS_EMPTY: az �res buffert jelz� flag
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
read_buf:
	MOV A, NUM_DATA		;�res buffer ellen�rz�se
	JZ empty_buf
	MOV A, @BUF_RD		;ha nem �res a buffer, akkor bet�ltj�k az adatot
	MOV DATA_IN_OUT, A
	INC BUF_RD			;pointer posztinkremens
	DEC NUM_DATA		;elemsz�mot cs�kkentj�k
	MOV A, #BUF_END		;megn�zz�k, hogy a pointer "t�lcsordult-e"
	SUBB A, BUF_RD
	JNC read_ready
	MOV BUF_RD, #BUF_BEGIN	;pointer vissza�ll�t�sa a cirkul�ris buffer elej�re
	CLR C				;t�r�lj�k a carryt (a cirkularit�s ellen�rz�s be�ll�tja)
	JMP read_ready
empty_buf:
	SETB IS_EMPTY		;be�ll�tjuk a buffer �res flaget
read_ready:
	RET

END


