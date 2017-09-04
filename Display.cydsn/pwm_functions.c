/*
 * Copyright @Pucktacular, 2016
 * @Matt Gebert, Daniel Hranilovic & Kevin Duxbury
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include "pwm_functions.h"
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
   PWM_Claw_WriteCompare(80);
}

void ClawClose() {
   PWM_Claw_WriteCompare(50);
}

void ClawHalf(){
   PWM_Claw_WriteCompare(65);
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
    TiltUp();   
    CyDelay(400);
    PWM_Pan_WriteCompare(zerodegrees);
}
void PanMid(){
    PWM_Pan_WriteCompare(120); //Halfway 125 was too much.
}

/*Not being used with current lift motor
 * Have kept just incase need servo option again
void LiftGround(){
     PWM_Lift_WriteCompare(65);
}

void LiftHalf(){
    PWM_Lift_WriteCompare((max+65)/2);
}

void LiftTop(){
     PWM_Lift_WriteCompare(max);
}*/

/* [] END OF FILE */
