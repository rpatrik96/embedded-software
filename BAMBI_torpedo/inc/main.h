/*
 * main.h
 *
 *  Created on: 2017. okt. 26.
 *      Author: Marosvári Kristóf & Reizinger Patrik
 */

#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include "torpedo.h"


/*Variables*/
volatile unsigned char data;
volatile bool data_received;
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

// variable to store the ship configurations
SegmentLCD_SegmentData_TypeDef ships[16][7];

#endif /* SRC_MAIN_H_ */
