#ifndef Camera_B_H
#define Camera_B_H

#include <cyfitter.h>

#define Camera_B_U (*(reg8*)Camera_B_dp__D0_REG)
#define Camera_B_V (*(reg8*)Camera_B_dp__D1_REG)

#define Camera_B_SetThresholds(u,v) {\
	Camera_B_U=u;\
	Camera_B_V=v;}

#define Camera_B_Start() {*(reg8*)Camera_B_dp__DP_AUX_CTL_REG|=1;}

#endif
