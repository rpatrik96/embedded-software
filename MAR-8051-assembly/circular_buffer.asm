; Reizinger Patrik
; W5PDBR
; Feladatkiírás:
; Belsõ memóriában 32 karakteres gyûrûs tároló készítése betételi és kivételi lehetõséggel.
; Író és olvasó pointer mutatja a következõ szabad hely ill. kivehetõ karakter címét.
; CY=1 jelzi, ha a tároló betelt.
; A program két szubrutint tartalmazzon: puffer írása és puffer olvasása.
; A puffer globális adatterületként állandóan létezik, induláskor üres.
; Bemenet mindkét rutinnak: tároló kezdõcíme a memóriában (mutató),
; író és olvasó pointer aktuális állapota, beteendõ karakter (írás esetén).
; Kimenet: kivett karakter (olvasás), pointerek aktuális állapota, CY.

BUF_BEGIN EQU 0x30		;buffer kezdõcíme (IRAM)
BUF_END EQU 0x4F		;buffer utolsó elemének címe (0x30 + 32 - 1)
BUF_LEN EQU 32			;a buffer hossza
		
BUF_RD EQU R0			;olvasó pointer
BUF_WR EQU R1			;író pointer
DATA_IN_OUT EQU R2		;regiszter a be-, ill. kimenetnek
NUM_DATA EQU R3			;a karakterek számát tároló regiszter
IS_EMPTY EQU F0			;a specifikáció kibõvítése: visszajelzés, ha üres a buffer



ORG 00H
JMP main

main:
	MOV BUF_RD, #BUF_BEGIN		;pointer inicializációk
	MOV BUF_WR, #BUF_BEGIN
	MOV NUM_DATA, #0x00			;elemszám nullázása

	MOV DATA_IN_OUT, #0x66		;adatok a teszthez
	MOV R4, #BUF_LEN
	INC R4
fill_loop:						;feltöltjük a buffert, a végén CY=1
	CALL write_buf
	DJNZ R4, fill_loop

	MOV R4, #BUF_LEN
	INC R4
read_loop:						;olvasás,a  végém F0=1
	CALL read_buf
	DJNZ R4, read_loop

infinity_loop:
	JMP $


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;write_buf
;Funkció:
;			- a cirkuláris bufferbe történõ írás kezelése
;			- teli buffer jelzése (CY flag)
;Bemenetek:
;			- BUF_WR: az írást végzõ pointer
;			- DATA_IN_OUT: az írni kívánt adatbyte
;			- NUM_DATA: a bufferben lévõ byteok száma	
;			- BUF_BEGIN: a buffer kezdõcíme
;			- BUF_END: a buffer befejezõ címe
;			- BUF_LEN: a buffer hossza
;Kimenetek:
;			- BUF_WR: az írást végzõ pointer eggyel növelve (ha nem volt már tele a buffer)
;			- NUM_DATA: a bufferen lévõ byteok száma	eggyel növelve (ha nem volt már tele a buffer)
;			- CY: a tele buffert jelzõ flag
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
write_buf:
	MOV A, #BUF_LEN		;teli buffer ellenõrzése (ebben a sorrendben CY nem állítódik)
	SUBB A, NUM_DATA
	JZ full_buf
	MOV A, DATA_IN_OUT	;karakter írása
	MOV @BUF_WR, A
	INC BUF_WR			;pointer posztinkremens
	INC NUM_DATA		;elemszámot is növeljük
	MOV A, #BUF_END		;megnézzük, hogy a pointer "túlcsordult-e"
	SUBB A, BUF_WR
	JNC write_ready
	MOV BUF_WR, #BUF_BEGIN	;pointer visszaállítása a cirkuláris buffer elejére
	CLR C				;töröljük a carryt (a cirkularitás ellenõrzés beállítja)
	JMP write_ready
full_buf:
	SETB C				;teli buffer jelzése
write_ready:
	RET


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;read_buf
;Funkció:
;			- a cirkuláris bufferbõl történõ olvasás kezelése
;			- üres buffer jelzése (F0 flag, a programban IS_EMPTY aliassal)
;Bemenetek:
;			- BUF_RD: az olvasást végzõ pointer
;			- NUM_DATA: a bufferben lévõ byteok száma	
;			- BUF_BEGIN: a buffer kezdõcíme
;			- BUF_END: a buffer befejezõ címe
;Kimenetek:
;			- BUF_RD: az írást végzõ pointer eggyel növelve (ha nem volt már üres a buffer)
;			- NUM_DATA: a bufferen lévõ byteok száma	eggyel csökkentve (ha nem volt már üres a buffer)
;			- DATA_IN_OUT: a kiolvasott adatbyte
;			- IS_EMPTY: az üres buffert jelzõ flag
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
read_buf:
	MOV A, NUM_DATA		;üres buffer ellenõrzése
	JZ empty_buf
	MOV A, @BUF_RD		;ha nem üres a buffer, akkor betöltjük az adatot
	MOV DATA_IN_OUT, A
	INC BUF_RD			;pointer posztinkremens
	DEC NUM_DATA		;elemszámot csökkentjük
	MOV A, #BUF_END		;megnézzük, hogy a pointer "túlcsordult-e"
	SUBB A, BUF_RD
	JNC read_ready
	MOV BUF_RD, #BUF_BEGIN	;pointer visszaállítása a cirkuláris buffer elejére
	CLR C				;töröljük a carryt (a cirkularitás ellenõrzés beállítja)
	JMP read_ready
empty_buf:
	SETB IS_EMPTY		;beállítjuk a buffer üres flaget
read_ready:
	RET

END


