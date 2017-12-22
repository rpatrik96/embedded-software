/*
 * torpedo.h
 *
 *  Created on: 2017. okt. 26.
 *      Author: Marosvári Kristóf & Reizinger Patrik
 */

#ifndef SRC_TORPEDO_H_
#define SRC_TORPEDO_H_

//Includes
#include "em_device.h"
#include "em_chip.h"
#include "InitDevice.h"
#include "em_usart.h"
#include "em_gpio.h"
#include "em_emu.h"
#include "segmentlcd.h"
#include "segmentlcdconfig.h"
#include "segmentlcd_spec.h"

//flag for debug purposes
#define DEBUG 0

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

/*Variables*/
extern volatile unsigned char data;
extern volatile bool data_received;
extern uint16_t num_try;										//number of shots fired (one segment counted only once)
extern uint8_t num_hit;											//number of hit ship parts (max 4*2 = 8)
extern SegmentLCD_SegmentData_TypeDef actual_shots[7];			//stored shots
extern uint8_t actual_ship;										//randomly selected ship index
extern SegmentLCD_SegmentData_TypeDef displayed_segments[7];	//temporary variable to store segments for displaying
extern uint16_t actual_segment;									//actual blinking segment
extern uint8_t segment_idx;										//index of segment (0-13)
extern uint8_t digit_sel;										//digit select signal (0-6)
extern bool toggle_flag ;										//flag used for the blinking effect
extern volatile uint32_t msTicks;

// variable to store the ship configurations
SegmentLCD_SegmentData_TypeDef ships[16][7];

/*Functions*/
void init_ships(void);
void UART0_RX_IRQHandler(void);
void SysTick_Handler(void);
void delay(int length);
void Init_Game();

#endif /* SRC_TORPEDO_H_ */
