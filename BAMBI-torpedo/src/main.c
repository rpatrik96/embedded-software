/*
 * main.c
 *
 *  Created on: 2017. okt. 26.
 *      Author: Marosvári Kristóf & Reizinger Patrik
 */


#include "main.h"


int main(void)
{

	/* Chip errata */
	CHIP_Init();

	/*Configure systick with arbitrarily chosen value*/
	SysTick_Config(0xFFFFFF);

	/*Config settings*/
	enter_DefaultMode_from_RESET();


#if DEBUG
	/*Set LED0*/
	GPIO_PinOutSet(LED0_PORT, LED0_PIN);
#endif

	/*Init LCD*/
	SegmentLCD_Init(false);

	/*IT enable*/
	USART_IntEnable(UART0, USART_IF_RXDATAV);
	NVIC_EnableIRQ(UART0_RX_IRQn);

	/*Game init*/
	//initialize ship positions
	init_ships();
	Init_Game();

	/* Infinite loop */
	while (1)
	{
		if (data_received)
		{
			data_received = false;

			switch (data)
			{
				case RESET:
				{
					Init_Game();
					break;
				}
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
				case UP:
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
				case DOWN:
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
						if(ships[actual_ship][digit_sel].raw & actual_segment)
						{
							//count hits
							num_hit++;

							//blink A-Ring if hit
							for(uint8_t j = 0; j < 4; j++)
							{
								for(uint8_t i = 0; i < 7; i++)
								{
									SegmentLCD_ARing(i, 1);
								}
								delay(200000);
								for(uint8_t i = 0; i < 7; i++)
								{
									SegmentLCD_ARing(i, 0);
								}
								delay(200000);
							}
						}
					}
					else
					{
						//blink the lock icon if segment was targeted before
						for(uint8_t i = 0; i < 3; i++)
						{
							SegmentLCD_Symbol(LCD_SYMBOL_PAD0, 1);
							SegmentLCD_Symbol(LCD_SYMBOL_PAD1, 1);
							delay(200000);
							SegmentLCD_Symbol(LCD_SYMBOL_PAD0, 0);
							SegmentLCD_Symbol(LCD_SYMBOL_PAD1, 0);
							delay(200000);
						}
					}

					break;
				}

				default:
				{
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

		//update displayed segments
		for(uint8_t i = 0; i < NUM_DIGIT; i++)
		{
			displayed_segments[i].raw = actual_shots[i].raw & ships[actual_ship][i].raw;
		}


		//Blinking effect
		if(toggle_flag)
		{
			toggle_flag = false;
			displayed_segments[digit_sel].raw ^= actual_segment; //display actual segment and hit ship parts
			displaySegmentField(displayed_segments);
		}
		else
		{
			toggle_flag = true;
			displaySegmentField(displayed_segments); //display hit ship parts
		}
		delay(200000);

		//start new game if all ships are destroyed
		if(num_hit == 8)
		{
			SegmentLCD_Write("YOU WIN");
			while(!data_received){}; //starting new game when any key pressed
			Init_Game();
		}
	}
}
