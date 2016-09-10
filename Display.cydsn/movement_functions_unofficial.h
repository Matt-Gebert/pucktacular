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

/*  Exteral Variables Declarations
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


void MovementTest() {
    /*Purposes of testing movement functions*/
    
    CS_Write(2);                    //Bus address set to LatchDevices {Hbridge, LEDG, Buzzer etc.}
    Data_Out_Control=0xA0;          //Writes 1010 to the four HBridge Pins, so both motors spin.
    CS_Write(8);                    //Bus address deactivated.
    CyDelay(1000);                  //Tick Toc... for a second.
    CS_Write(2);                    //Repeat.
    Data_Out_Control=0x50;          //Reverse motors.
    CS_Write(8);
    CyDelay(1000);
    CS_Write(2);                    //Repeat.
    Data_Out_Control=0x00;          //Stop Motors
    CS_Write(8);
    
}

/* [] END OF FILE */