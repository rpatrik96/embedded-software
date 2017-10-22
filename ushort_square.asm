; Reizinger Patrik
; W5PDBR
; Feladatkiírás:
;Regiszterekben kapott 16 bites előjel nélküli szám négyzetre emelése, túlcsordulás figyelése.
;Az eredmény is 16 biten legyen ábrázolva, a túlcsordulás ennek figyelembevételével állítandó.
;Bemenet: 2 regiszterben a szám.
;Kimenet: 2 regiszterben az eredmény, CY

;Megfontolások: 
;a négyzetre emelés felbontható 4 szorzásra, melyek közül 2
;megegyezik értékét tekintve (high-low byteok szorzása), így egyszerűsíthető a feladat.
;Továbbá a túlcsordulás ellenőrzésekor figyelembe vehetjük, hogy amikor shiftelnünk kell,
;akkor a kishiftelt bitek 0-val való komparálása jelzi a túlcsordulást.
;A carry flaget a program végrehajtása közben az ADD utasítások állíthatják,
;így az F0 szabadon felhasználható flag lett kijelölve a carry átmeneti tárolójaként,
;mivel bitmódosító uatsítások segítségével könnyen módosítható

;A program a 34 sorban található infinity_loop címkénél elhelyzett breakpointnál már
;előállította a szükséges eredményt.

NUMLOW EQU R2	;a bemenet alacsony byteját tároló regiszter
NUMHIGH EQU R3	;a bemenet magas byteját táoló regiszter
RESLOW EQU R4	;a műveletvégzés során az eredmény alsó bíteját tároló regiszter
RESHIGH EQU R5	;a műveletvégzés során az eredmény alsó bíteját tároló regiszter

;A szegmenskezelő direktívákat nem ismeri a szimulátor, így azok nem kerültek felhasználásra
;Kódmemória elejére pozícionálás és ugrótábla a main függvényre
ORG 00h
JMP main

main:
	MOV NUMHIGH, #0x00
	MOV NUMLOW, #0xFF
	CALL square_16_bit
infinity_loop:
	JMP $


;A square_16_bit szubrutin a teljes feladat megoldásáért felel
;Bemenetek: 
;-16 bites előjel nélküli egész a (NUMHIGH,NUMLOW) regiszterekben,
;az elnevezésnek megfelelően rendezve az alsó, illetve a felső byteokat
;Kimenetek: 
;-a bemenet négyzete 16 biten a (NUMHIGH,NUMLOW) regiszterpárosban, az előzőeknek
;megfelelő elrendezésben
;-CY flag, mely a túlcsordulás tényét (1) jelzi
;Módosított regiszterek:
;-NUMHIGH
;-NUMLOW
;-RESHIGH
;-RESLOW
;-A
;-B
;-F0 flag
;-CY flag

square_16_bit:
	CLR F0				;F0 flag törlése, ebben kerül tárolásra átmenetileg a carry flag
same_bytes_low:
	MOV A, NUMLOW		;az alsó byte szorzása önmagával
	MOV B, A			;másoljuk A-t, hogy véletlenül se törhénhessen meg, hogy csak egy helyen változtatjuk meg az értéket
	MUL AB
	MOV RESLOW, A		;nem kell összeadni, mivel ez az első lépése a négyzetre emelésnek
	MOV RESHIGH, B
same_bytes_high:
	MOV A, NUMHIGH		;a magasabb helyiértékű byteok szorzása
	MOV B, A			;másoljuk A-t, hogy véletlenül se törhénhessen meg, hogy csak egy helyen változtatjuk meg az értéket
	MUL AB
	ORL A, B			;mivel itt 16 bitet kellene balra shiftelni, ami mindenképp túlcsordulást eredményez, így elegendő A OR B-t vizsgálni a túlcsordulás tényéhez
	JZ different_bytes	;ha 0 az akkumulátor, akkor nem történik overflow
	SETB F0
different_bytes:
	MOV A, NUMLOW		;az alsó byte szorzása a felsővel
	MOV B, NUMHIGH
	MUL AB
	RLC A				;mivel a (HIGH<<8)*LOW = (LOW<<8)*HIGH, így egy bit balra shiftelésével a két lépés össze lett vonva
	ORL C, F0			;ráadásul így a carry biten keresztül shiftelve az overflow is egyszerűen ellenőrizhető
	MOV F0, C
	ADD A, RESHIGH		;itt RESHIGH-hoz adjuk hozzá a szorzás eredméynének alsó byteját, mivel a felső nem fér 16 bitbe (a 8 bitnyi balra shift miatt, amit fizikailag nem hajtunk végre, hanem ezt megkerülve RESHIGH-hoz adjuk hozzá az eredményt)
	ORL C, F0			;az összeadás miatt újra ellenőrizni kell a carryt
	MOV F0, C
	MOV RESHIGH, A
	MOV A, B			;a felső byte itt szintén nem fér bele a 16 bitbe, így ha nem 0, akkor az túlcsordulást jelent
	JZ b_carry
	SETB F0

b_carry:
	MOV A, RESLOW		;bemásoljuk a bemeneti regiszterekbe az eredményt
	MOV NUMLOW, A
	MOV A, RESHIGH
	MOV NUMHIGH, A
	MOV C, F0			;valamint beállítjuk a túlcsordulást jelző flaget is
	
	RET

END



	
