#ifndef `$INSTANCE_NAME`_H
#define `$INSTANCE_NAME`_H

#include <cyfitter.h>

#define `$INSTANCE_NAME`_U (*(reg8*)`$INSTANCE_NAME`_dp__D0_REG)
#define `$INSTANCE_NAME`_V (*(reg8*)`$INSTANCE_NAME`_dp__D1_REG)

#define `$INSTANCE_NAME`_SetThresholds(u,v) {\
	`$INSTANCE_NAME`_U=u;\
	`$INSTANCE_NAME`_V=v;}

#define `$INSTANCE_NAME`_Start() {*(reg8*)`$INSTANCE_NAME`_dp__DP_AUX_CTL_REG|=1;}

#endif
