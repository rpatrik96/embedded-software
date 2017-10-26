/*
 * torpedo.c
 *
 *  Created on: 2017. okt. 26.
 *      Author: Marosvári Kristóf & Reizinger Patrik
 */

#include "torpedo.h"

/*Ship configuration init
 * it is done manually to control the placement of the segments*/
void init_ships(void)
{
	// SHIP 0
	ships[0][0].g = 1;
	ships[0][0].m = 1;

	ships[0][1].g = 1;
	ships[0][1].m = 1;

	ships[0][2].k = 1;
	ships[0][2].q = 1;

	ships[0][3].b = 1;
	ships[0][3].c = 1;

	ships[0][5].a = 1;

	ships[0][6].a = 1;

	// SHIP 1
	ships[1][0].a = 1;

	ships[1][1].a = 1;

	ships[1][2].k = 1;
	ships[1][2].q = 1;

	ships[1][3].b = 1;
	ships[1][3].c = 1;

	ships[1][4].a = 1;

	ships[1][5].a = 1;
	// SHIP 2
	ships[2][0].a = 1;

	ships[2][1].a = 1;

	ships[2][2].k = 1;
	ships[2][2].q = 1;

	ships[2][3].b = 1;
	ships[2][3].c = 1;

	ships[2][4].d = 1;

	ships[2][5].d = 1;
	// SHIP 3
	ships[3][0].f = 1;
	ships[3][0].e = 1;

	ships[3][1].j = 1;
	ships[3][1].p = 1;

	ships[3][2].j = 1;
	ships[3][2].p = 1;

	ships[3][4].h = 1;
	ships[3][4].n = 1;

	// SHIP 4
	ships[4][0].b = 1;
	ships[4][0].c = 1;

	ships[4][1].j = 1;
	ships[4][1].p = 1;

	ships[4][2].j = 1;
	ships[4][2].p = 1;

	ships[4][3].h = 1;
	ships[4][3].n = 1;

	// SHIP 5
	ships[5][0].b = 1;
	ships[5][0].c = 1;

	ships[5][3].h = 1;
	ships[5][3].n = 1;

	ships[5][5].j = 1;
	ships[5][5].p = 1;

	ships[5][6].j = 1;
	ships[5][6].p = 1;

	// SHIP 6
	ships[6][0].j = 1;
	ships[6][0].p = 1;

	ships[6][1].a = 1;

	ships[6][2].a = 1;

	ships[6][3].d = 1;

	ships[6][4].d = 1;

	ships[6][5].g = 1;
	ships[6][5].m = 1;

	ships[6][6].g = 1;
	ships[6][6].m = 1;
	// SHIP 7
	ships[7][0].g = 1;
	ships[7][0].m = 1;

	ships[7][1].g = 1;
	ships[7][1].m = 1;

	ships[7][2].g = 1;
	ships[7][2].m = 1;

	ships[7][3].g = 1;
	ships[7][3].m = 1;

	ships[7][4].g = 1;
	ships[7][4].m = 1;

	ships[7][5].g = 1;
	ships[7][5].m = 1;

	ships[7][6].f = 1;
	ships[7][6].e = 1;
	// SHIP 8
	ships[8][0].g = 1;
	ships[8][0].m = 1;

	ships[8][1].g = 1;
	ships[8][1].m = 1;

	ships[8][2].f = 1;
	ships[8][2].e = 1;

	ships[8][4].b = 1;
	ships[8][4].c =	1;

	ships[8][5].g = 1;
	ships[8][5].m = 1;

	ships[8][6].g = 1;
	ships[8][6].m = 1;
	// SHIP 9
	ships[9][0].f = 1;
	ships[9][0].e = 1;

	ships[9][1].g = 1;
	ships[9][1].m = 1;

	ships[9][2].g = 1;
	ships[9][2].m = 1;

	ships[9][4].g = 1;
	ships[9][4].m =	1;

	ships[9][5].g = 1;
	ships[9][5].m = 1;

	ships[9][6].b = 1;
	ships[9][6].c = 1;
	// SHIP 10
	ships[10][0].b = 1;
	ships[10][0].c = 1;

	ships[10][1].a = 1;

	ships[10][2].a = 1;

	ships[10][4].d = 1;

	ships[10][5].d = 1;

	ships[10][6].f = 1;
	ships[10][6].e = 1;
	// SHIP 11
	ships[11][0].b = 1;
	ships[11][0].c = 1;

	ships[11][1].d = 1;

	ships[11][2].d = 1;

	ships[11][4].a = 1;

	ships[11][5].a = 1;

	ships[11][6].f = 1;
	ships[11][6].e = 1;
	// SHIP 12
	ships[12][0].a = 1;

	ships[12][1].a = 1;

	ships[12][2].a = 1;

	ships[12][3].a = 1;

	ships[12][4].a = 1;

	ships[12][5].a = 1;

	ships[12][6].q = 1;
	ships[12][6].k = 1;
	// SHIP 13
	ships[13][0].h = 1;
	ships[13][0].n = 1;

	ships[13][1].q = 1;
	ships[13][1].k = 1;

	ships[13][2].h = 1;
	ships[13][2].n = 1;

	ships[13][3].q = 1;
	ships[13][3].k = 1;
	// SHIP 14
	ships[14][0].q = 1;
	ships[14][0].k = 1;

	ships[14][1].a = 1;

	ships[14][2].a = 1;

	ships[14][3].h = 1;
	ships[14][3].n = 1;

	ships[14][4].d = 1;

	ships[14][5].d = 1;
	// SHIP 15
	ships[15][0].h = 1;
	ships[15][0].n = 1;

	ships[15][1].d = 1;

	ships[15][2].d = 1;

	ships[15][3].q = 1;
	ships[15][3].k = 1;

	ships[15][4].a = 1;

	ships[15][5].a = 1;
}


/*UART0 IT Handler redefinition
 * for data traffic*/
void UART0_RX_IRQHandler(void)
{
	data = USART_RxDataGet(UART0);
	data_received = true;
	USART_IntClear(UART0, USART_IF_RXDATAV);
}

/*SysTick Handler redefinition
 * used only for ship configuartion select*/
void SysTick_Handler(void)
{
  msTicks++;       /* increment counter necessary in Delay()*/
}

/*Software delay for led/A-Ring/Lock Pad blinking*/
void delay(int length)
{
	for(int d=0;d<length;d++);
}

/*Game (re)initialization routine
 * used at the beginning and at every restart*/
void Init_Game()
{
	num_try = 0;
	num_hit = 0;
	actual_segment = 1;
	actual_ship = (msTicks % NUM_SHIPS);
	segment_idx = 0;
	digit_sel = 0;
	toggle_flag = true;
	data_received = false;
	SegmentLCD_Number(num_try);
	for(uint8_t i = 0; i < 7; i++)
	{
		actual_shots[i].raw = 0;
	}

}
