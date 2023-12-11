/*
 * tbsAgent.c
 *
 *  Created on: Nov 1, 2022
 *      Author: raing
 */


#include "main.h"

tPWMChannels pwmInputValueLast;
tPWMChannels pwmInputValuePrevious;

tPWMChannels pwmOutputValueLast;

void parseTBS(uint8_t * input, uint16_t inputLength)
{
	for (int i = 0 ; i < 256 - 64 ; i++)
	{
		if ( (input[i] == 0xC8) && (input[i + 1] == 0x18) && (input[i + 2] == 0x16) )
		{
			memcpy(&pwmInputValuePrevious, &pwmInputValueLast, sizeof(pwmInputValueLast));
			//											8				3 | 5
			uint32_t localCh1EncodedValue = (input[i + 3] + ((input[i + 4] & 0x07) << 8));
			//											5				6 | 2 --> 8-5 = 3
			uint32_t localCh2EncodedValue = ( (input[i + 4] & 0xF8) + ((input[i + 5] & 0x3F) << 8)) >> 3;
			//											2				8								1 |7 --> 8 - 2 = 6
			uint32_t localCh3EncodedValue = ( (input[i + 5] & 0x03) + (input[i + 6] << 8) + ((input[i + 7] & 0x01) << 16)) >> 6;
			//											7				4 | 4 --> 8-7 = 1
			uint32_t localCh4EncodedValue = ( (input[i + 7] & 0xFE) + ((input[i + 8] & 0x0F) << 8)) >> 1;
			//											4				7 | 1 --> 8-4 = 4
			uint32_t localCh5EncodedValue = ( (input[i + 8] & 0xF0) + ((input[i + 9] & 0x7F) << 8)) >> 4;
			//											1				8								2 | 6 --> 8 - 1 = 7
			uint32_t localCh6EncodedValue = ( (input[i + 9] & 0x80) + ((input[i + 10] & 0xFF) << 8)  + ((input[i + 11] & 0x03) << 16)) >> 7;
			//											6				5 | 3 --> 8 - 6 = 2
			uint32_t localCh7EncodedValue = ( (input[i + 11] & 0xFC) + ((input[i + 12] & 0x1F) << 8)) >> 2;
			//											3				8 | 0 -- > 8 - 3 = 5
			uint32_t localCh8EncodedValue = ( (input[i + 12] & 0xE0) + ((input[i + 13] & 0xFF) << 8)) >> 5;

			pwmInputValueLast.Rotate = (uint16_t)((localCh1EncodedValue - 992.0) * 5.0 / 8.0 + 1500.0) * 1.0; //Rotate
			pwmInputValueLast.Throttle = (uint16_t)((localCh2EncodedValue - 992.0) * 5.0 / 8.0 + 1500.0) * 1.0; //Throttle
			pwmInputValueLast.DroneThrottle = (uint16_t)((localCh3EncodedValue - 992.0) * 5.0 / 8.0 + 1500.0) * 1.0;
			pwmInputValueLast.Strafe = (uint16_t)((localCh4EncodedValue - 992.0) * 5.0 / 8.0 + 1500.0) * 1.0; //Strafe
			pwmInputValueLast.SafetySW = (uint16_t)((localCh5EncodedValue - 992.0) * 5.0 / 8.0 + 1500.0) * 1.0;
			pwmInputValueLast.Channel6 = (uint16_t)((localCh6EncodedValue - 992.0) * 5.0 / 8.0 + 1500.0) * 1.0;
			pwmInputValueLast.Channel7 = (uint16_t)((localCh7EncodedValue - 992.0) * 5.0 / 8.0 + 1500.0) * 1.0;
			pwmInputValueLast.Channel8 = (uint16_t)((localCh8EncodedValue - 992.0) * 5.0 / 8.0 + 1500.0) * 1.0;
			newPWMValueAvailabe = true;
		}
	}

}
