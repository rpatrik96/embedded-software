/*
 * torpedo.h
 *
 *  Created on: 2017. okt. 26.
 *      Author: Reizinger Patrik
 */

#ifndef SRC_TORPEDO_H_
#define SRC_TORPEDO_H_

#include "em_device.h"
#include "em_chip.h"
#include "InitDevice.h"
#include "em_usart.h"
#include "em_gpio.h"
#include "em_emu.h"
#include "segmentlcd.h"
#include "segmentlcdconfig.h"
#include "segmentlcd_spec.h"


#define DEBUG 1

#define LEFT 68
#define RIGHT 67
#define DOWN 66
#define UP 65
#define FIRE 32
#define RESET 114

#define NUM_DIGIT 7
#define NUM_SEGMENT 14
#define NUM_SHIPS 16

#define MIDDLE_SEG ((1<< 10) | (1 << 6))

volatile unsigned char data;
volatile bool data_received;
/*Variables*/
uint16_t num_try = 0;									//number of shots fired (one segment counted only once)
uint8_t num_hit = 0;									//number of hit ship parts (max 4*2 = 8)
SegmentLCD_SegmentData_TypeDef actual_shots[7];			//stored shots
uint8_t actual_ship = 0;

SegmentLCD_SegmentData_TypeDef displayed_segments[7];	//temporary variable to store segments for displaying
uint16_t actual_segment = 1;							//actual blinking segment
uint8_t segment_idx = 0;								//index of segment (0-13)
uint8_t digit_sel = 0;									//digit select signal (0-6)
bool toggle_flag = true;								//flag used for the blinking effect

volatile uint32_t msTicks = 0;

// variable to store the ship configurations (at this stage contains only one)
SegmentLCD_SegmentData_TypeDef ships[16][7];


void init_ships(void);
void UART0_RX_IRQHandler(void);
void SysTick_Handler(void);
void delay(int length);
void Init_Game();

#endif /* SRC_TORPEDO_H_ */
