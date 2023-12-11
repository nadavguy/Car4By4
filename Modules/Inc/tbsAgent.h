/*
 * tbsAgent.h
 *
 *  Created on: Nov 1, 2022
 *      Author: raing
 */

#ifndef INC_TBSAGENT_H_
#define INC_TBSAGENT_H_

typedef struct sPWMChannels {
	uint16_t Rotate;
	uint16_t Throttle;
	uint16_t DroneThrottle;
	uint16_t Strafe;
	uint16_t SafetySW;
	uint16_t Channel6;
	uint16_t Channel7;
	uint16_t Channel8;
} tPWMChannels;

extern tPWMChannels pwmInputValueLast;
extern tPWMChannels pwmInputValuePrevious;
extern tPWMChannels pwmOutputValueLast;

extern void parseTBS(uint8_t * input, uint16_t inputLength);
#endif /* INC_TBSAGENT_H_ */
