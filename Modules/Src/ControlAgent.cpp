/*
 * ControlAgent.cpp
 *
 *  Created on: Jun 10, 2021
 *      Author: raing
 */

#include "main.h"
#include "ControlAgent.h"

tMOTORS droneAltOnlyMotorsPWM = {992};
tMOTORS droneLinearMotorsPWM = {992};
tMOTORS dronePIDMotorsPWM = {992};

tMOTORS droneOffsetMotorsPWM = {992};

bool newPWMValueAvailabe = false;

uint32_t lastPWMUpdate = 0;

float motorMin = 0;
float motorMax = 0;
float motorFactor = 0.0f;

int16_t localMotorMinOffset = 0;
int16_t localMotorDist = 0;
int16_t localMaxThrutle = 0;


void updatePWMToFC(void)
{
	if (pwmInputValueLast.SafetySW < 1200)
	{
		TIM1->CCR1 = (uint16_t)(0); // LF
		TIM1->CCR2 = (uint16_t)(0); // RF
		TIM1->CCR3 = (uint16_t)(0); // RB
		TIM1->CCR4 = (uint16_t)(0); // LB

		HAL_GPIO_WritePin(GPIO_Motor_FL_IN1_GPIO_Port, GPIO_Motor_FL_IN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIO_Motor_FL_IN2_GPIO_Port, GPIO_Motor_FL_IN2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIO_Motor_FR_IN3_GPIO_Port, GPIO_Motor_FR_IN3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIO_Motor_FR_IN4_GPIO_Port, GPIO_Motor_FR_IN4_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(GPIO_Motor_BL_IN1_GPIO_Port, GPIO_Motor_BL_IN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIO_Motor_BL_IN2_GPIO_Port, GPIO_Motor_BL_IN2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIO_Motor_BR_IN3_GPIO_Port, GPIO_Motor_BR_IN3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIO_Motor_BR_IN4_GPIO_Port, GPIO_Motor_BR_IN4_Pin, GPIO_PIN_RESET);

		return;
	}
	if (newPWMValueAvailabe)
	{
		int16_t localThrottle = pwmInputValueLast.Throttle - centerThrottle;
		int16_t localRotate = pwmInputValueLast.Rotate - centerRotate;
		int16_t localStrafe = pwmInputValueLast.Strafe - centerStrafe;


		if (fabs((float)localThrottle) < 5)
		{
			localThrottle = 0;
		}

		if (fabs((float)localRotate) < 5)
		{
			localRotate = 0;
		}

		if ( (fabs((float)localStrafe) < 5) || (localThrottle >= 5) || (localRotate >= 5) )
		{
			localStrafe = 0;
		}

		int32_t leftSidePWM = 0;
		int32_t rightSidePWM = 0;
		int32_t frontSidePWM = 0;
		int32_t backSidePWM = 0;

		//Forwards
		if (localThrottle >= 0 )
		{
			leftSidePWM = (localThrottle + localRotate) * 20 * sign(localThrottle + localRotate);
			rightSidePWM = (localThrottle - localRotate) * 20 * sign(localThrottle - localRotate);
			//Right
			if (leftSidePWM > 0)
			{
				updateMotors(FORWARD, LEFTSIDE);
			}
			else
			{
				updateMotors(BACKWARD, LEFTSIDE);
			}

			if (rightSidePWM > 0)
			{
				updateMotors(FORWARD, RIGHTSIDE);
			}
			else
			{
				updateMotors(BACKWARD, RIGHTSIDE);
			}
		}
		else // Backward
		{
			leftSidePWM = (localThrottle - localRotate) * 20 * sign(localThrottle - localRotate);
			rightSidePWM = (localThrottle + localRotate) * 20 * sign(localThrottle + localRotate);
			//Right
			if (leftSidePWM > 0)
			{
				updateMotors(BACKWARD, LEFTSIDE);
			}
			else
			{
				updateMotors(FORWARD, LEFTSIDE);
			}

			if (rightSidePWM > 0)
			{
				updateMotors(BACKWARD, RIGHTSIDE);
			}
			else
			{
				updateMotors(FORWARD, RIGHTSIDE);
			}
		}

		if (localStrafe != 0)
		{
			if (localStrafe > 0)
			{

			}
			else
			{

			}
		}


		if (localStrafe == 0)
		{
			TIM1->CCR1 = (uint16_t)(leftSidePWM); // LF
			TIM1->CCR2 = (uint16_t)(rightSidePWM); // RF
			TIM1->CCR3 = (uint16_t)(rightSidePWM); // RB
			TIM1->CCR4 = (uint16_t)(leftSidePWM); // LB
		}
		else
		{

		}
	}
	newPWMValueAvailabe = false;

}

void updateMotors(eDirection newDirection, eMOTOR motorToUpdate)
{
	switch (motorToUpdate)
	{
	case LEFTSIDE:
	{
		if (newDirection == FORWARD) //Counter clock wise
		{
			HAL_GPIO_WritePin(GPIO_Motor_FL_IN1_GPIO_Port, GPIO_Motor_FL_IN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIO_Motor_FL_IN2_GPIO_Port, GPIO_Motor_FL_IN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIO_Motor_BL_IN1_GPIO_Port, GPIO_Motor_BL_IN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIO_Motor_BL_IN2_GPIO_Port, GPIO_Motor_BL_IN2_Pin, GPIO_PIN_SET);

		}
		else if (newDirection == BACKWARD) // Clock wise
		{
			HAL_GPIO_WritePin(GPIO_Motor_FL_IN1_GPIO_Port, GPIO_Motor_FL_IN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIO_Motor_FL_IN2_GPIO_Port, GPIO_Motor_FL_IN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIO_Motor_BL_IN1_GPIO_Port, GPIO_Motor_BL_IN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIO_Motor_BL_IN2_GPIO_Port, GPIO_Motor_BL_IN2_Pin, GPIO_PIN_RESET);
		}
		else if (newDirection == ESTOP)
		{
			HAL_GPIO_WritePin(GPIO_Motor_FL_IN1_GPIO_Port, GPIO_Motor_FL_IN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIO_Motor_FL_IN2_GPIO_Port, GPIO_Motor_FL_IN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIO_Motor_BL_IN1_GPIO_Port, GPIO_Motor_BL_IN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIO_Motor_BL_IN2_GPIO_Port, GPIO_Motor_BL_IN2_Pin, GPIO_PIN_RESET);

			TIM1->CCR1 = 20000;
			TIM1->CCR4 = 20000;

		}
		else if (newDirection == FREESTOP)
		{

		}
		break;
	}
	case RIGHTSIDE:
	{
		if (newDirection == FORWARD) //Counter clock wise
		{
			HAL_GPIO_WritePin(GPIO_Motor_FR_IN3_GPIO_Port, GPIO_Motor_FR_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIO_Motor_FR_IN4_GPIO_Port, GPIO_Motor_FR_IN4_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIO_Motor_BR_IN3_GPIO_Port, GPIO_Motor_BR_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIO_Motor_BR_IN4_GPIO_Port, GPIO_Motor_BR_IN4_Pin, GPIO_PIN_SET);

		}
		else if (newDirection == BACKWARD) // Clock wise
		{
			HAL_GPIO_WritePin(GPIO_Motor_FR_IN3_GPIO_Port, GPIO_Motor_FR_IN3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIO_Motor_FR_IN4_GPIO_Port, GPIO_Motor_FR_IN4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIO_Motor_BR_IN3_GPIO_Port, GPIO_Motor_BR_IN3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIO_Motor_BR_IN4_GPIO_Port, GPIO_Motor_BR_IN4_Pin, GPIO_PIN_RESET);
		}
		else if (newDirection == ESTOP)
		{
			HAL_GPIO_WritePin(GPIO_Motor_FR_IN3_GPIO_Port, GPIO_Motor_FR_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIO_Motor_FR_IN4_GPIO_Port, GPIO_Motor_FR_IN4_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIO_Motor_BR_IN3_GPIO_Port, GPIO_Motor_BR_IN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIO_Motor_BR_IN4_GPIO_Port, GPIO_Motor_BR_IN4_Pin, GPIO_PIN_RESET);

			TIM1->CCR2 = 20000;
			TIM1->CCR3 = 20000;

		}
		else if (newDirection == FREESTOP)
		{

		}
		break;
	}
	default:
	{

		break;
	}
	}
}
