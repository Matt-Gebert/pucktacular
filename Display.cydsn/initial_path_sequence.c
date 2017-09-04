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
#include <math.h>
#include <stdlib.h>
#include "movement_functions.h"
#include "camera_display.h"
#include "camera_functions.h"
#include "pwm_functions.h"
#include "Ultrasonics.h"
#include "initial_path_sequence.h"
#include "utils.h"


bool PathInitialSequence(){
    bool block = false;
    double check_angle = 5;
    double dist1,dist2;
    uint8 i;
    //move back
    MovementBackward(6000);
    //move back to 25cm
    //CyDelay(50);
    //MoveAlignBack(21,1);
    //camera sequence code here
    PanMid();
    CyDelay(50);
    TiltStraight();
    CyDelay(100);
    PWM_Pan_WriteCompare(125);//Adjusted Cam Angle for Puck Seq
    CyDelay(100);
    CaptureFrameWithLights();
    CyDelay(100);
    CamGetSequence();
    PanMid();
    CyDelay(100);
    MovementForward(200);
    CyDelay(50);
    //pivot right 90
    MovementPivotRight(80);
    //move to side wall
    MovementForward(3000);
    MoveAlign(16,0,0,0.8);
    //pivot right 90
    MovementPivotRight90();
    //check distance for brick
    for(i=0;i<3;i++){
        if(i==1){
            MovementPivotLeft(check_angle);
        }
        
        if(i==2){
            MovementPivotRight(check_angle);
        }
        dist1 = Ultrasonics(1);
        dist2 = Ultrasonics(0);
        if(i==1){
            MovementPivotRight(check_angle);
        }
        
        if(i==2){
            MovementPivotLeft(check_angle);
        }
        //dist_diff = fabs(dist1-dist2);
        if( (dist2<30) || (dist1<30) ){
           block = true;
           return block;
        }
    }
    return block;
}

/* [] END OF FILE */
