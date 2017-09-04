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
/*
  Exteral Variables Declarations
        Write like: "extern int x;"
*/       
        
/*  General Information
        Movement is controlled through 2nd Bus Address.
        Last 4 bits of 8 bit bus control motor inputs.
        0xA0 -> Both forward.
        0x50 -> Both backward.
        0x10 -> Right wheel forward.
        0x20 -> Right wheel backward.
        0x40 -> Left wheel forward.
        0x80 -> Left wheel backward.
        0x90 -> Pivot Left
        0x60 -> Pivot Right
*/

/*External Functions*/
void MovementPivotRight90();
void MovementPivotLeft90();
void MovementPivotRight(double deg);
void MovementPivotLeft(double deg);
void MovementForward(uint16 msec);
void MovementBackward(uint16 msec);
void MovementLeft(uint16 msec);
void MovementRight(uint16 msec);
void MovementRightBack(uint16 msec);
void MovementLeftBack(uint16 msec);
void MovementResetQuadCount();

/*Internal Functions*/
//void Movement(uint8 direction, uint16 duration);
//void MovementLinearCorrected(uint8 direction, uint16 duration);


/* [] END OF FILE */