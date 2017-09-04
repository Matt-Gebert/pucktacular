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
#include <stdbool.h>
#include <stdlib.h>
#include "movement_functions.h"

/*Internal FUNCTION DECLARATIONS*/
void Movement(uint8 direction, uint16 duration);
void MovementLinearCorrected(uint8 direction, uint16 duration);
void MovementAquireQuadCount();
void MovementCorrectionFunction(bool fwd, int SEL, int SER);

//To Keep Track Of Wheels & Quadrature.
int16 SERight=0; //Attached to Pin2&3 of J8, SE1 A&B
int16 SELeft=0; //Pin4&5, SE2 A&B.
int SELeftTot=0;
int SERightTot=0;


/*  General Information
        Movement is controlled through 2nd Bus Address.
        Last 4 bits of 8 bit bus control motor inputs.
        0x50 -> Both forward.
        0xA0 -> Both backward.
        0x10 -> Right wheel forward.
        0x20 -> Right wheel backward.
        0x40 -> Left wheel forward.
        0x80 -> Left wheel backward.
        0x90 -> Pivot Left
        0x60 -> Pivot Right
*/

//Defines Movements
uint8 const FORWARD = 0xA0;
uint8 const BACKWARD = 0x50;
uint8 const RIGHT_FORWARD = 0x20;
uint8 const RIGHT_BACKWARD = 0x10;
uint8 const LEFT_FORWARD = 0x80;
uint8 const LEFT_BACKWARD = 0x40;
uint8 const PIVOT_LEFT = 0x60;
uint8 const PIVOT_RIGHT = 0x90;
uint8 const STOP = 0x00;

//Time value to split movement into steps.
uint16 const STEP_SIZE = 1000; //ms.
uint8 const MIN_DIF = 20; //Minimum "Don't Care" difference between phases.
uint16 const deg90 = 3600;//(11265*18)/19/3; //Amount of steps to roughtly turn 90 degrees.

/* ------------------------------------- LINEAR MOTION -------------------------------------------------*/


void Movement(uint8 direction, uint16 duration) {    
    //Write to Bus to start Movement:
    CS_Write(2);
    OE_Control=3;
    Data_Out_Control=direction;
    CS_Write(8);
    OE_Control=0;
    CyDelay(duration/3);
    duration = 0;
    CS_Write(2);                    
    OE_Control=3;
    Data_Out_Control=STOP;
    CS_Write(8);
    OE_Control=0;
    CyDelay(10); //10ms Delay to make sure we get steady values for phases.
}

void MovementLinearCorrected (uint8 direction, uint16 duration) {
    //Splits correction into parts, rather than run for ages and then halt.
    uint8 i;
    int SELeftCompound=0;
    int SERightCompound=0;
    
    for (i=0; duration>0; i++) {
        //Reset Quadrature.
        MovementResetQuadCount();
        //Move
        //if(duration>STEP_SIZE){
        //    Movement(direction, STEP_SIZE);
        //    duration = (duration - STEP_SIZE);
        //} else {
        if (duration > 420)
            duration = duration*3/4;
        Movement(direction, duration);
        duration=0;
        //}
        //Aquire Quadrature
        //MovementAquireQuadCount();
        //SERightCompound+=SERight;
        //SELeftCompound+=SELeft;
        //Compute Difference & Correct:
        //MovementCorrectionFunction(direction==FORWARD, SELeft, SERight);
        //SERightCompound+=SERight;
        //SELeftCompound+=SELeft;
    }
    //MovementCorrectionFunction(direction&FORWARD, SELeftCompound, SERightCompound); //Final Correction for whole span.
    SELeftCompound=0;
    SERightCompound=0;
    
}

void MovementForward(uint16 msec){
    MovementLinearCorrected(FORWARD, msec);
}

void MovementBackward(uint16 msec){
    MovementLinearCorrected(BACKWARD, msec);
}

/* --------------------------------------- PIVOT ROTATION ------------------------------------------------*/

void MovementPivot(uint8 direction, double angle) {
    MovementResetQuadCount();
    CS_Write(2);
    OE_Control=3;
    Data_Out_Control=direction;
    CS_Write(8);
    OE_Control=0;
    if(direction==PIVOT_RIGHT)
        while(SELeft>-deg90*angle/90 && SERight<deg90*angle/90){
            CyDelay(30);
            MovementAquireQuadCount();
            
        }
    else //PIVOT_LEFT
        while(SERight>-deg90*angle/90 && SELeft<deg90*angle/90){
            CyDelay(30);
            MovementAquireQuadCount();
        }
    CS_Write(2);                    
    OE_Control=3;
    Data_Out_Control=STOP;
    CS_Write(8);
    OE_Control=0;
    CyDelay(10); //10ms Delay to make sure we get steady values for phases.
    
    //Reset Counters to prevent Correction of ForwardMovement.
}

void MovementPivotRight90(){
    MovementPivot(PIVOT_RIGHT,90);
}

void MovementPivotLeft90(){
    MovementPivot(PIVOT_LEFT,90);
}

void MovementPivotRight(double deg) {
    MovementPivot(PIVOT_RIGHT,deg);
}

void MovementPivotLeft(double deg) {
    MovementPivot(PIVOT_LEFT,deg);
}

/*------------------------------------------ ONE-WHEEL ROTATION -----------------------------------------------*/
void MovementLeftForward(uint16 msec){
    Movement(LEFT_FORWARD, msec);
}

void MovementRightForward(uint16 msec){
    Movement(RIGHT_FORWARD, msec);
}

void MovementRightBack(uint16 msec){
    Movement(RIGHT_BACKWARD,msec);
}

void MovementLeftBack(uint16 msec){
    Movement(LEFT_BACKWARD,msec);
}


/*------------------------------------------ CORRECTION FUNCTIONALITY ------------------------------------------*/

void MovementResetQuadCount() {
    SERightTot+=SERight;
    SELeftTot+=SELeft;
    
    Quad_1_SetCounter(0);
    Quad_2_SetCounter(0);
    SERight=Quad_1_GetCounter(); //SE1 A&B
    SELeft=Quad_2_GetCounter(); //SE2 A&B
}

void MovementAquireQuadCount() {
    SERight=Quad_1_GetCounter(); //SE1 A&B
    SELeft=Quad_2_GetCounter(); //SE2 A&B
}

void MovementCorrectionFunction(bool fwd, int SEL, int SER) {
    /* 1s of Movement Forward: 
        Se1 -> 0x0C7D = 3197 //Right Wheel
	    Se2 -> 0xBCD = 3021
		Difference = 173
    */
    int diff = SEL-SER;
    const int ratio = 3; //Approx 3 Revolutions per Millisecond.
    
    //While outside of appropiate bounds:
    while (diff > MIN_DIF || diff < -MIN_DIF) {//  &&(abs(diff))// Doesn't work for some reason...((abs(diff) > MIN_DIF))
        //Start Counters..
        MovementResetQuadCount();
        //Figure out direction of Correction.
        if (diff > 0) { //Right ahead of Left
            if(fwd){//Correct by adjusting Right back to left.
               MovementRightBack(diff/ratio);
            } else { //Correct by adjusting left forward to right.
               MovementLeftForward(diff/ratio);
            }
        } else { //Left ahead of Right. Difference is negative, so need to invert sign.
            if(fwd){ //Correct by adjusting left back to right.
                MovementLeftBack(-diff/ratio);
            } else { //Correct by adusting right forward to left.
                MovementRightForward(-diff/ratio);
            }
        }
        MovementAquireQuadCount();
        diff = diff + (SELeft-SERight); //Add new diff to counter.
    }
}

/* [] END OF FILE */