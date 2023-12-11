/*
 * ControlAgent.h
 *
 *  Created on: Jun 10, 2021
 *      Author: raing
 */

#ifndef INC_CONTROLAGENT_H_
#define INC_CONTROLAGENT_H_

//#include "PIDController.h"

typedef struct sMOTORS{
	int16_t motorLF;
	int16_t motorRF;
	int16_t motorLB;
	int16_t motorRB;
}tMOTORS;

extern tMOTORS droneAltOnlyMotorsPWM;
extern tMOTORS droneLinearMotorsPWM;
extern tMOTORS dronePIDMotorsPWM;



//extern PIDController pitchPID;
extern void initPIDs(void);
extern void updatePIDs(void);
extern float pwmToAngle(uint16_t pwmValue);
extern uint16_t angleToPWM(float angleValue);
extern void updateLinear(void);
extern void updateAltOnly(void);
extern void updatePWMToFC(void);

extern void updateMotors(eDirection newDirection, eMOTOR motorToUpdate);

#endif /* INC_CONTROLAGENT_H_ */
