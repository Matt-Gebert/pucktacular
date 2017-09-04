#ifndef Camera_M_H
#define Camera_M_H

#include <cyfitter.h>

#define Camera_M_U (*(reg8*)Camera_M_dp__D0_REG)
#define Camera_M_V (*(reg8*)Camera_M_dp__D1_REG)

#define Camera_M_SetThresholds(u,v) {\
	Camera_M_U=u;\
	Camera_M_V=v;}

#define Camera_M_Start() {*(reg8*)Camera_M_dp__DP_AUX_CTL_REG|=1;}

#endif
