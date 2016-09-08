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
Important information
    The PWM Channels to the Microservers run on a 20ms period.
    To Achieve accuracy in the pwm duty width, we use a freq much higher than this.
    Thereby we have 2000 counts at 100kHz.
    Cycles:
        max = 200;  eg cam left (bot perspective) or tilt face down
        halfway = 125;
        zerodegrees = 50;  eg cam right (bot perspective) or tilt face up
*/
uint8 max = 200;
uint8 halfway = 125;
uint8 zerodegrees = 50;

void ClawOpen() {
   PWM_Claw_WriteCompare(65);
}

void ClawClose() {
   PWM_Claw_WriteCompare(zerodegrees);
}

void TiltUp(){
    PWM_Tilt_WriteCompare(zerodegrees);
}
void TiltStraight(){
    PWM_Tilt_WriteCompare(halfway);
}
void TiltDown(){
    PWM_Tilt_WriteCompare(max);
}
void TiltDown45(){
    PWM_Tilt_WriteCompare(162);
}

void PanRight(){
    TiltUp();   // good logic Dan
    CyDelay(100);
    PWM_Pan_WriteCompare(zerodegrees);
}
void PanMid(){
    PWM_Pan_WriteCompare(halfway);
}

void LiftGround(){
     PWM_Lift_WriteCompare(zerodegrees);
}

void LiftTop(){
     PWM_Lift_WriteCompare(max);
}

/* [] END OF FILE */
