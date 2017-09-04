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

void ClawOpen();
//  Moves claw to open pos
void ClawClose();
//  Moves claw to close/grip pos
void ClawHalf();
//  Half open claw for when stacking as frame prevents full opening
void TiltUp();
//  Tilts camera to face up pos
void TiltStraight();
//  Tilts camera to face directly forward pos
void TiltDown();

void TiltDown45();

void PanRight();

void PanMid();

//void LiftGround();

//void LiftHalf();

//void LiftTop();

/* [] END OF FILE */