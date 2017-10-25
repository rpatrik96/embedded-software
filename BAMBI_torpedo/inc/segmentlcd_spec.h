/**************************************************************************//**
 * @file
 * @brief EFM32 Segment LCD Display driver, header file
 * @version 4.3.0
 ******************************************************************************
 * @section License
 * <b>Copyright 2015 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/


#ifndef SEGMENTLCD_SPEC_H
#define SEGMENTLCD_SPEC_H

#include "segmentlcdconfig.h"

/***************************************************************************//**
 * @addtogroup kitdrv
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup SegmentLcd
 * @{
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 ********************************   Types   ************************************
 ******************************************************************************/

typedef union _Segment_TypeDef
{
	uint16_t raw;
	struct {
	uint16_t a : 1;
	uint16_t b : 1;
	uint16_t c : 1;
	uint16_t d : 1;
	uint16_t e : 1;
	uint16_t f : 1;
	uint16_t g : 1;
	uint16_t h : 1;
	uint16_t j : 1;
	uint16_t k : 1;
	uint16_t m : 1;
	uint16_t n : 1;
	uint16_t p : 1;
	uint16_t q : 1;
	};
} SegmentLCD_SegmentData_TypeDef;


/*******************************************************************************
 *******************************  FUNCTIONS  ***********************************
 ******************************************************************************/

void displaySegmentField(SegmentLCD_SegmentData_TypeDef* segmentField);

#ifdef __cplusplus
}
#endif

/** @} (end group SegmentLcd) */
/** @} (end group Drivers) */

#endif
