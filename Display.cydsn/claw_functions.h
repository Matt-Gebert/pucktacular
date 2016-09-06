/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <project.h>

/*
    Claw referenced at Pin 12.0

    Timings.
        255 == 20ms.
        Positions:
        Left:   1ms == 13
        Right:  2ms == 26
        Middle: 1.5ms == 19
*/

void OpenClaw() {
    PWM_Claw_WriteCompare(40);
}

void CloseClaw() {
    PWM_Claw_WriteCompare(13);
}

void ClawAngle() {
    
}



/* [] END OF FILE */
