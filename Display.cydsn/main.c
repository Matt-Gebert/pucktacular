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
#include <math.h>
//#include <tgmath.h>
#include "camera_display.h"
#include "camera_functions.h"
#include "movement_functions.h"
#include "pwm_functions.h"
#include "puck_functions.h"
#include "Ultrasonics.h"
#include "pathing.h"
#include "initial_path_sequence.h"
#include "lift_functions.h"
#include "utils.h"
 
void Initialise();
void Headlights();
void HeadlightsOff();
void Beep(int x);
void BiDirPortOutPut();
void BiDirPortInPut();


/*Variables from Camera Functions:
---------------------------------*/
/*extern uint16 closestX;
extern uint16 closestY;
extern const uint8 numRows;
extern const uint16 numCols; */
extern const uint8 RED;
extern const uint8 GREEN;
extern const uint8 BLUE;
extern uint8 orderedScaledClr[5];
/*-------------------------------*/



int main()
{
    HeadlightsOff();
    
    SW_Start();
    
    LCD_Start();
    LCD_DMA_Start();

    Camera_Start();
    Camera_WriteReg(0x41,0x02); //double colour matrix (more saturation)
    Camera_SetBlankTime(1000); //increase blanking time if image is corrupted; range is 0-2047
    
    CyGlobalIntEnable; //interrupts must be enabled for camera to work
        
    
    //3 lines taht set up loop for button presses
    uint8 buttons=0xff;;
    uint8 buttons_old=0xff;
    bool start =false;
    bool block;
    display_mode=THRESHOLDED; //start displaying image
    
    //Camera_SetEGWB(80,0,128,128); //set exposure, gain and white balance //ORIGNIAL VALUES...
    Camera_SetEGWB(160,0,128,128); //set exposure, gain and white balance
    Camera_SetThresholds(-32,64,0,-64,48,-32,-16,32); //set thresholds for the 4 colours
    
    //Loop until button press
    Beep(3);
    LiftInital();
    while(start==false){        
        buttons=Buttons_Status;
        if(buttons&~buttons_old&4)  start=true;
        if(buttons&~buttons_old&2)  LiftUpReset();
        if(buttons&~buttons_old&1)  LiftDownReset();
        
        buttons_old=buttons;
    }
    
    //Setup PWM Channels
    Initialise();
    Beep(2);
    CyDelay(200); //Wait for PWM's to initialize position correctly.
    ClawClose();
    Beep(2);
    Beep(2);
    CyDelay(200);
    ClawOpen();
    
    //TEMP STUFF
    /*
    orderedScaledClr[0]=0;
    orderedScaledClr[1]=1;
    orderedScaledClr[2]=2;
    orderedScaledClr[3]=2;
    orderedScaledClr[4]=1;
    block=0;
    */
    
    Beep(2);
    CyDelay(200);
    PanRight();
    CyDelay(200);
    block = PathInitialSequence();
    CyDelay(20);
    
    uint8 n=0;
    //for(n=0;n<5;n++)
    for(n=0;n<5;n++)
    {
        PathForward(block);
        PuckResetAngleTotal();
        PuckAquire(orderedScaledClr[n],block);
        MovementResetQuadCount();
        PathBackward(block);
        
        if(n==0){
            MoveAlign(4.0,1,0,0.5);
            ClawOpen();
            CyDelay(200);
            MovementBackward(4000);
            MovementPivotLeft(180);
            CyDelay(20);
        } else {
            PanRight();
            CyDelay(50);
            LiftLvMax();
            //Camera to check and position!
            PuckPositionToStack(orderedScaledClr[0]); //orderedScaledClr[4] //PWM's... 45 & ? -> 162 & 180 
            PanRight();
            CyDelay(50);
            LiftLvN(n);
            ClawOpen();
            CyDelay(200);
            MovementBackward(4000);
            ClawClose();
            LiftLvN(0);
            MovementPivotLeft(180);
            PanMid();
            ClawOpen();
            CyDelay(20);
        }
        
    }
    
    MovementPivotRight(360);
}

void Initialise(){
    Timer_1_Start();
    Timer_2_Start();
    Quad_1_Start();
    Quad_2_Start();
    PWM_Pan_Start();
    CyDelay(10);
    PWM_Tilt_Start();
    CyDelay(10);
    PWM_Claw_Start();
    CyDelay(10);
    LiftSetGround();
}


