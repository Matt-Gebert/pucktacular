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
 *
 * Contains all utility code used in made functions
 * Beeps, headlights and control of output driver
*/


#include <project.h>

void Headlights();
//Takes control of bus and chip to turn on headlight
void HeadlightsOff();
//Takes control of bus and chip to turn off headlight
void BiDirPortOutPut();
//enable output driver and switch to user output
void BiDirPortInPut();
//disable output driver
void Beep(int x);
//Cause beep for x number of for loop ticks
void CaptureFrameWithLights();
/* [] END OF FILE */