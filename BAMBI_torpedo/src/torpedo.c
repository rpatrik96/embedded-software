/*
 * torpedo.c
 *
 *  Created on: 2017. okt. 26.
 *      Author: Reizinger Patrik
 */

#include "torpedo.h"


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

	// SHIP 0
	ships[1][0].g = 1;
	ships[1][0].m = 1;

	ships[1][1].g = 1;
	ships[1][1].m = 1;

	ships[1][2].k = 1;
	ships[1][2].q = 1;

	ships[1][3].b = 1;
	ships[1][3].c = 1;

	ships[1][5].a = 1;

	ships[1][6].a = 1;
	// SHIP 0
	ships[2][0].g = 1;
	ships[2][0].m = 1;

	ships[2][1].g = 1;
	ships[2][1].m = 1;

	ships[2][2].k = 1;
	ships[2][2].q = 1;

	ships[2][3].b = 1;
	ships[2][3].c = 1;

	ships[2][5].a = 1;

	ships[2][6].a = 1;
	// SHIP 0
	ships[3][0].g = 1;
	ships[3][0].m = 1;

	ships[3][1].g = 1;
	ships[3][1].m = 1;

	ships[3][2].k = 1;
	ships[3][2].q = 1;

	ships[3][3].b = 1;
	ships[3][3].c = 1;

	ships[3][5].a = 1;

	ships[3][6].a = 1;
	// SHIP 0
	ships[4][0].g = 1;
	ships[4][0].m = 1;

	ships[4][1].g = 1;
	ships[4][1].m = 1;

	ships[4][2].k = 1;
	ships[4][2].q = 1;

	ships[4][3].b = 1;
	ships[4][3].c = 1;

	ships[4][5].a = 1;

	ships[4][6].a = 1;
	// SHIP 0
	ships[5][0].g = 1;
	ships[5][0].m = 1;

	ships[5][1].g = 1;
	ships[5][1].m = 1;

	ships[5][2].k = 1;
	ships[5][2].q = 1;

	ships[5][3].b = 1;
	ships[5][3].c = 1;

	ships[5][5].a = 1;

	ships[5][6].a = 1;
	// SHIP 0
	ships[6][0].g = 1;
	ships[6][0].m = 1;

	ships[6][1].g = 1;
	ships[6][1].m = 1;

	ships[6][2].k = 1;
	ships[6][2].q = 1;

	ships[6][3].b = 1;
	ships[6][3].c = 1;

	ships[6][5].a = 1;

	ships[6][6].a = 1;
	// SHIP 0
	ships[7][0].g = 1;
	ships[7][0].m = 1;

	ships[7][1].g = 1;
	ships[7][1].m = 1;

	ships[7][2].k = 1;
	ships[7][2].q = 1;

	ships[7][3].b = 1;
	ships[7][3].c = 1;

	ships[7][5].a = 1;

	ships[7][6].a = 1;
	// SHIP 0
	ships[8][0].g = 1;
	ships[8][0].m = 1;

	ships[8][1].g = 1;
	ships[8][1].m = 1;

	ships[8][2].k = 1;
	ships[8][2].q = 1;

	ships[8][3].b = 1;
	ships[8][3].c = 1;

	ships[8][5].a = 1;

	ships[8][6].a = 1;
	// SHIP 0
	ships[9][0].g = 1;
	ships[9][0].m = 1;

	ships[9][1].g = 1;
	ships[9][1].m = 1;

	ships[9][2].k = 1;
	ships[9][2].q = 1;

	ships[9][3].b = 1;
	ships[9][3].c = 1;

	ships[9][5].a = 1;

	ships[9][6].a = 1;
	// SHIP 0
	ships[10][0].g = 1;
	ships[10][0].m = 1;

	ships[10][1].g = 1;
	ships[10][1].m = 1;

	ships[10][2].k = 1;
	ships[10][2].q = 1;

	ships[10][3].b = 1;
	ships[10][3].c = 1;

	ships[10][5].a = 1;

	ships[10][6].a = 1;
	// SHIP 0
	ships[11][0].g = 1;
	ships[11][0].m = 1;

	ships[11][1].g = 1;
	ships[11][1].m = 1;

	ships[11][2].k = 1;
	ships[11][2].q = 1;

	ships[11][3].b = 1;
	ships[11][3].c = 1;

	ships[11][5].a = 1;

	ships[11][6].a = 1;
	// SHIP 0
	ships[12][0].g = 1;
	ships[12][0].m = 1;

	ships[12][1].g = 1;
	ships[12][1].m = 1;

	ships[12][2].k = 1;
	ships[12][2].q = 1;

	ships[12][3].b = 1;
	ships[12][3].c = 1;

	ships[12][5].a = 1;

	ships[12][6].a = 1;
	// SHIP 0
	ships[13][0].g = 1;
	ships[13][0].m = 1;

	ships[13][1].g = 1;
	ships[13][1].m = 1;

	ships[13][2].k = 1;
	ships[13][2].q = 1;

	ships[13][3].b = 1;
	ships[13][3].c = 1;

	ships[13][5].a = 1;

	ships[13][6].a = 1;
	// SHIP 0
	ships[14][0].g = 1;
	ships[14][0].m = 1;

	ships[14][1].g = 1;
	ships[14][1].m = 1;

	ships[14][2].k = 1;
	ships[14][2].q = 1;

	ships[14][3].b = 1;
	ships[14][3].c = 1;

	ships[14][5].a = 1;

	ships[14][6].a = 1;
	// SHIP 0
	ships[15][0].g = 1;
	ships[15][0].m = 1;

	ships[15][1].g = 1;
	ships[15][1].m = 1;

	ships[15][2].k = 1;
	ships[15][2].q = 1;

	ships[15][3].b = 1;
	ships[15][3].c = 1;

	ships[15][5].a = 1;

	ships[15][6].a = 1;
}


void UART0_RX_IRQHandler(void)
{
	data = USART_RxDataGet(UART0);
	data_received = true;
	USART_IntClear(UART0, USART_IF_RXDATAV);
}

void SysTick_Handler(void)
{
  msTicks++;       /* increment counter necessary in Delay()*/
}

//needed to replace with a systick IT
void delay(int length)
{
	for(int d=0;d<length;d++);
}

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
