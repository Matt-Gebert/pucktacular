#ifndef Camera_R_H
#define Camera_R_H

#include <cyfitter.h>

#define Camera_R_U (*(reg8*)Camera_R_dp__D0_REG)
#define Camera_R_V (*(reg8*)Camera_R_dp__D1_REG)

#define Camera_R_SetThresholds(u,v) {\
	Camera_R_U=u;\
	Camera_R_V=v;}

#define Camera_R_Start() {*(reg8*)Camera_R_dp__DP_AUX_CTL_REG|=1;}

#endif
