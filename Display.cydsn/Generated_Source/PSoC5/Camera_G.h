#ifndef Camera_G_H
#define Camera_G_H

#include <cyfitter.h>

#define Camera_G_U (*(reg8*)Camera_G_dp__D0_REG)
#define Camera_G_V (*(reg8*)Camera_G_dp__D1_REG)

#define Camera_G_SetThresholds(u,v) {\
	Camera_G_U=u;\
	Camera_G_V=v;}

#define Camera_G_Start() {*(reg8*)Camera_G_dp__DP_AUX_CTL_REG|=1;}

#endif
