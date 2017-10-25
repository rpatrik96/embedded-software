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

#define NUM_DIGIT 7
#define NUM_SEGMENT 14

#define MIDDLE_SEG ((1<< 10) | (1 << 6))

volatile unsigned char data;
volatile bool data_received;

// variable to store the ship configurations (at this stage contains only one)
SegmentLCD_SegmentData_TypeDef ships[7];

void init_ships(void)
{
	ships[0].g = 1;
	ships[0].m = 1;

	ships[1].g = 1;
	ships[1].g = 1;

	ships[2].k = 1;
	ships[2].q = 1;

	ships[3].b = 1;
	ships[3].c = 1;

	ships[5].a = 1;

	ships[6].a = 1;
}


void UART0_RX_IRQHandler(void)
{
	data = USART_RxDataGet(UART0);
	data_received = true;
	USART_IntClear(UART0, USART_IF_RXDATAV);
}

//needed to replace with a systick IT
void delay(int length)
{
	for(int d=0;d<length;d++);
}

int main(void)
{
	/*Variables*/
	uint16_t num_try = 0;									//number of shots fired (one segment counted only once)
	SegmentLCD_SegmentData_TypeDef actual_shots[7];			//stored shots

	SegmentLCD_SegmentData_TypeDef displayed_segments[7];	//temporary variable to store segments for displaying
	uint16_t actual_segment = 1;							//actual blinking segment
	uint8_t segment_idx = 0;								//index of segment (0-13)
	uint8_t digit_sel = 0;									//digit select signal (0-6)
	bool toggle_flag = true;								//flag used for the blinking effect

	//Reset variable (it was a problem that the array had init values != 0
	for(unsigned char i = 0; i < 7; i++)
	{
		actual_shots[i].raw = 0;
	}


	/* Chip errata */
	CHIP_Init();

	/*Config settings*/
	enter_DefaultMode_from_RESET();

#if DEBUG
	/*Set LED0*/
	GPIO_PinOutSet(LED0_PORT, LED0_PIN);
#endif

	/*Init LCD*/
	SegmentLCD_Init(false);
	SegmentLCD_Number(num_try);

	/*IT enable*/
	USART_IntEnable(UART0, USART_IF_RXDATAV);
	NVIC_EnableIRQ(UART0_RX_IRQn);

	/* Infinite loop */
	while (1)
	{
		if (data_received)
		{
			data_received = false;

			////clear last segment
			//actual_ships[digit_sel].raw = 0;
			switch (data)
			{
				case LEFT:
				{
					digit_sel--;

					//correct if the index have gone around
					if(digit_sel == 255)
					{
						digit_sel = NUM_DIGIT - 1;
					}
					break;
				}
				case RIGHT:
				{
					digit_sel++;

					//correct if the index have been wrapped around
					if(digit_sel == NUM_DIGIT)
					{
						digit_sel = 0;
					}
					break;
				}
				case DOWN:
				{
					//handle middle segment as one entity
					if((segment_idx - 1 ==  6) || (segment_idx - 1 == 10))
					{
						segment_idx--;

						//update variable for the segment structure
						actual_segment = MIDDLE_SEG; //segments 6 and 10
					}
					else
					{
						//check whether segment should have wrap around
						if(!segment_idx)
						{
							segment_idx = NUM_SEGMENT - 1;
						}
						else
						{
							segment_idx--;
						}

						//update variable for the segment structure
						actual_segment = (1 << segment_idx);
					}
					break;
				}
				case UP:
				{
					//handle middle segment as one entity
					if((segment_idx + 1 ==  6) || (segment_idx + 1 == 10))
					{
						segment_idx++;

						//update variable for the segment structure
						actual_segment = MIDDLE_SEG; //segments 6 and 10
					}
					else
					{
						segment_idx = ((segment_idx + 1) % NUM_SEGMENT);

						//update variable for the segment structure
						actual_segment = (1 << segment_idx);
					}
					break;
				}
				case FIRE:
				{
					//if segment was not targeted before
					if(!(actual_shots[digit_sel].raw & actual_segment))
					{
						//count the shots
						SegmentLCD_Number(++num_try);

						//set segment as targeted
						actual_shots[digit_sel].raw |= actual_segment;

						//turn on A-Ring
						for(uint8_t i = 0; i < 7; i++)
						{
							SegmentLCD_ARing(i, 1);
							delay(100000);
						}
						for(uint8_t i = 0; i < 7; i++)
						{
							SegmentLCD_ARing(i, 0);
						}


						//if target was hit
						if(ships[digit_sel].raw & actual_segment)
						{
							//blink A-Ring if hit
							for(uint8_t j = 0; j < 4; j++)
							{
								for(uint8_t i = 0; i < 7; i++)
								{
									SegmentLCD_ARing(i, 1);
								}
								delay(500000);
								for(uint8_t i = 0; i < 7; i++)
								{
									SegmentLCD_ARing(i, 0);
								}
							}
						}
					}
					else
					{
						//blink the lock icon if segment was targeted before
						for(uint8_t i = 0; i < 4; i++)
						{
							SegmentLCD_Symbol(LCD_SYMBOL_PAD0, 1);
							SegmentLCD_Symbol(LCD_SYMBOL_PAD1, 1);
							delay(500000);
							SegmentLCD_Symbol(LCD_SYMBOL_PAD0, 0);
							SegmentLCD_Symbol(LCD_SYMBOL_PAD1, 0);
						}
					}

					break;
				}

				default:
				{
					//set 0 segment
					break;
				}
			}

#if DEBUG
			/*Displaying traffic via UART*/
			GPIO_PinOutToggle(LED0_PORT, LED0_PIN);
			GPIO_PinOutToggle(LED1_PORT, LED1_PIN);

			//Resend data
			USART_Tx(UART0, data);
#endif
		}

		//COMMENTED OUT, ONE SINGLE STEP IS ENOUGH, NO LOOP NEEDED
		/*for(uint8_t i = 0; i < NUM_DIGIT; i++)
		{
			displayed_segments[i].raw = actual_shots[i].raw & ships[i].raw;
		}*/

		//update displayed segments (only the actual one, the other is unnecessary)
		displayed_segments[digit_sel].raw = actual_shots[digit_sel].raw & ships[digit_sel].raw;

		if(toggle_flag)
		{
			toggle_flag = false;
			displayed_segments[digit_sel].raw ^= actual_segment;
			displaySegmentField(displayed_segments);
		}
		else
		{
			toggle_flag = true;
			//actual_shots[digit_sel].raw = 0;
			displaySegmentField(displayed_segments);
		}
		delay(200000);
	}
}
