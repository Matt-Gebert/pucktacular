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
#include "utils.h"
#include <camera_display.h>

/*******************************************************************************
* Function Name: Headlights
****************************************************************************//**
*
* Turns on Headlights upon function call
*
*******************************************************************************/
void Headlights(){
    CS_Write(2);                    //Bus address set to LatchDevices {Hbridge, LEDG, Buzzer etc.}
    OE_Control=3;
    Data_Out_Control=0x9;          //Writes 1001 to activate the LEDs
    CS_Write(8);                    //Bus address deactivated.
    OE_Control=0;
}
/*******************************************************************************
* Function Name: HeadlightsOff
****************************************************************************//**
*
* Turns off Headlights upon call
*
*******************************************************************************/
void HeadlightsOff(){
    CS_Write(2);                    //Bus address set to LatchDevices {Hbridge, LEDG, Buzzer etc.}
    OE_Control=3;
    Data_Out_Control=0x0;          //Writes 1001 to activate the LEDs
    CS_Write(8);                    //Bus address deactivated.
    OE_Control=0;
}
/*******************************************************************************
* Function Name: BiDirPortOutPut
****************************************************************************//**
*
* Allows user to us bus for output (stops camera use)
*
*******************************************************************************/
void BiDirPortOutPut()
{
    OE_Control=3;                           //enable output driver and switch to user output
}
/*******************************************************************************
* Function Name: BiDirPortInPut
****************************************************************************//**
*
* Disables users ability for output driver
*
*******************************************************************************/
void BiDirPortInPut()
{
   OE_Control=0;                            //disable output driver                    
}
/*******************************************************************************
* Function Name: Beep
****************************************************************************//**
*
* Function that beeps for input number of beep tick (10 timer ticks each)
*
*******************************************************************************/
void Beep(int x) 
{
    BiDirPortOutPut();
    for(;x>0;x--)
    {
        //Data_Out_Write(0x03);      //Turn beeper on
        CS_Write(0x02);  
        Data_Out_Control=0x3;
        CS_Write(0x08);
        CyDelay(10);
    }
    //Data_Out_Write(0x01);      //Turn beeper off
    CS_Write(0x02);
    Data_Out_Control=0x0;
    CS_Write(0x08);
    BiDirPortInPut();
    
}

/*******************************************************************************
* Function Name: CaptureFramesWithLights()
****************************************************************************//**
*
* Turns on and off the headlights, while taking a frame inbetween.
*
*******************************************************************************/

void CaptureFrameWithLights() {
    //Headlights();
    CyDelay(50);
    CaptureFrame();
    CyDelay(50);
    //HeadlightsOff();   
}


/* [] END OF FILE */