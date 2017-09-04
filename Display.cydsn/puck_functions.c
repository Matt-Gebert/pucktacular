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
 * TODO: Do another angle function to make sure claw can pick up, a bit lower than 45'.
 * Change pixle offset on the X didrection, to accomodate for centre of robot.
*/

#include <project.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "camera_functions.h"
#include "camera_display.h"
#include "movement_functions.h"
#include "pwm_functions.h"
#include "puck_functions.h"
#include "utils.h"

/*Variables from Camera Functions:
---------------------------------*/
extern uint16 closestX;
extern uint16 closestY;
extern uint16 lowestY;
extern const uint8 numRows;
extern const uint16 numCols;
extern const uint8 RED;
extern const uint8 GREEN;
extern const uint8 BLUE;
extern const uint8 blobThresholdSizeDefault;
extern uint8 lrgClr[5];
extern uint16 lrgY[5];
/*-------------------------------*/
const uint8 CAMERA_Y_OFFSET = 160;
const uint8 CAMERA_X_OFFSET = 10;
const double PI = 3.1415926535;
const double corrFact = 4.0/5/2;
/*--------------------------------*/
uint16 angleTotal=0; //Negative Is Left, Positive is Right!
/*--------------------------------*/
bool PuckPositionToStack2(uint8 clr);

/*******************************************************************************
* Function Name: PuckCloseScan
****************************************************************************//**
*
* Tilts the camera to 45' to find & pick up a puck, Scanning for a target.
* Scanning works of rotating right in 10 degree increments.
* Returns True if a puck of the specified colour is found.
* Final Position will be in the ~ direction of the puck.
*
*******************************************************************************/

bool PuckCloseScan(uint8 clr) {
    TiltDown45();
    CyDelay(100);
    
    uint8 rotation; //degrees
    rotation=0;
    CaptureFrameWithLights();
    bool ClrOnScreen = CamScanClosest(clr, blobThresholdSizeDefault);
    
    while (!ClrOnScreen && rotation<5){
        if(rotation==0){ //Initial Rotation offset.
            MovementPivotLeft(28); 
            angleTotal-=28;
        } else {
            //Keep rotating to scan while finding nothing.
            angleTotal+=14;
            CyDelay(20);    
            MovementPivotRight(14); //14 is because of overturning...
        }
        CaptureFrameWithLights();
        ClrOnScreen = CamScanClosest(clr, blobThresholdSizeDefault);
        rotation=rotation+1;
    }
    if(!ClrOnScreen){
        MovementPivotLeft(28);
        angleTotal-=28;
    }
    return ClrOnScreen;
}

/*******************************************************************************
* Function Name: PuckCloseAquire
****************************************************************************//**
*
* Tilts the camera to 45' to find & pick up a puck, somewhere in front of the target.
*
*******************************************************************************/
bool PuckCloseAquire(uint8 clr, bool path) {
    TiltDown45();
    CyDelay(20);
    
    bool found = false;
    
    //Find Puck (this was previously a while loops, while not found.
    CaptureFrameWithLights();
    bool ClrOnScreen = CamScanClosest(clr, blobThresholdSizeDefault);
    
    if (ClrOnScreen) {
        //Found a puck..
        //..Turn to puck!
        double angle;
        double XYRatio;
        while(((abs(closestX - numCols/2 - CAMERA_X_OFFSET) > 15) && (240-closestY) > 65)) { //Keep turning untill we get a decent alignment //(abs(closestX - numCols/2 - CAMERA_X_OFFSET) > 20) || 
            if (closestX > numCols/2 + CAMERA_X_OFFSET) {
                XYRatio = ((double)(closestX-numCols/2-CAMERA_X_OFFSET))/(240-closestY + CAMERA_Y_OFFSET);
                angle = (atan(XYRatio)*180)/PI*corrFact;
                MovementPivotRight(angle);
                angleTotal+=angle;
            } else {
                XYRatio=((double)(numCols/2-closestX-CAMERA_X_OFFSET))/(240-closestY + CAMERA_Y_OFFSET);
                angle = (atan(XYRatio)*180)/PI*corrFact;
                MovementPivotLeft(angle);
                angleTotal-=angle;
            }
            //Rescan for new position.
            CaptureFrameWithLights(); 
            CamScanClosest(clr, blobThresholdSizeDefault);
        }
        //Close enough to pick up?
        if (240-closestY < 65){
            //Pickup.
            found=true; 
            return true;
        } else { //Puck inbetween 65 and 100.
            //Drive closer.
            //MovementForward(240-closestY);
            if (240-closestY < 160) {
                CamSeqOperations(); //Find Largest 5 Pucks with default threshold.
                if(lrgClr[0]!=clr && lrgY[0] > closestY) //TODO: Won't Handle RED, due to default array val.
                {
                    //Pickup Puck, Turn around, release, turn back.
                    ClawClose();
                    MovementBackward(3000);
                    if(path)
                        MovementPivotLeft(90);
                    else
                        MovementPivotRight(90);
                    
                    MovementForward(500);
                    ClawOpen();
                    MovementBackward(500);
                    MovementBackward(1000);
                    if(path)
                        MovementPivotRight(90);
                    else
                        MovementPivotLeft(90);
                } else {
                    MovementForward(pow(((CAMERA_Y_OFFSET + 240.0-closestY)/140),2)*400);
                }
            } else {
                MovementForward(pow(((CAMERA_Y_OFFSET + 240.0-closestY)/140),2)*550);
            }
            CaptureFrameWithLights(); 
            CamScanClosest(clr, blobThresholdSizeDefault);
        }
    } else {
        MovementPivotLeft(10);
        angleTotal-=10;
    }
    return found;
}
/*******************************************************************************
* Function Name: PuckFarScan
****************************************************************************//**
*
* Tilts the camera to ~ 20' to find pucks that are far away.
* Rotates 10 degree increments to align to a discovered puck.
* Returns TRUE if a puck is found.
*
*******************************************************************************/

bool PuckFarScan(uint8 clr) {
    PWM_Tilt_WriteCompare(135);
    CyDelay(20);
    
    uint8 rotation; //degrees
    rotation=0;
    
    CaptureFrameWithLights();
    bool ClrOnScreen = CamScanClosest(clr, blobThresholdSizeDefault);
    
    while (!ClrOnScreen && rotation<3){
        if(rotation==0){
            MovementPivotLeft(10);//Initialize Turning Arc.
            angleTotal-=10;
        } else {
            //Keep rotating to scan while finding nothing.
            MovementPivotRight(10);
            angleTotal+=10;
        }
        CaptureFrameWithLights();
        ClrOnScreen = CamScanClosest(clr, blobThresholdSizeDefault);
        rotation=rotation+1;
    }
    if(!ClrOnScreen){ //Rotate back straight if not seeing anyhing.
        MovementPivotLeft(10);
        angleTotal-=10;
    }
    return ClrOnScreen;
}

/*******************************************************************************
* Function Name: PuckFarAquire
****************************************************************************//**
*
* Tilts the camera to ~ 20' to find pucks that are far away.
* Moves towards the a found puck.
*
*******************************************************************************/

bool PuckFarAquire(uint8 clr) {
    PWM_Tilt_WriteCompare(135);
    CyDelay(20);
    
    CaptureFrameWithLights();
    bool ClrOnScreen = CamScanClosest(clr, blobThresholdSizeDefault);
    
    if (ClrOnScreen) {
        //Found a puck..
        //..Turn to puck!
        double angle;
        double XYRatio;
        
        while(closestY  < (numRows-60)){
            while(abs(closestX - numCols/2 - CAMERA_X_OFFSET) > 20) { //Keep turning untill we get a decent alignment
                if (closestX > numCols/2 + CAMERA_X_OFFSET) {
                    XYRatio = ((double)(closestX-numCols/2))/(240-closestY + CAMERA_Y_OFFSET);
                    angle = (atan(XYRatio)*180)/PI*corrFact;
                    MovementPivotRight(angle);
                } else {
                    XYRatio=((double)(numCols/2-closestX))/(240-closestY + CAMERA_Y_OFFSET);
                    angle = (atan(XYRatio)*180)/PI*corrFact;
                    MovementPivotLeft(angle);
                }
                //Rescan for new position.
                CaptureFrameWithLights(); 
                CamScanClosest(clr, blobThresholdSizeDefault);
            }
            //Move Towards Puck   
            MovementForward(pow(((double)(240-closestY)/120),2)*3000.0);
            CaptureFrameWithLights(); 
            CamScanClosest(clr, blobThresholdSizeDefault);
        }
    }
    return ClrOnScreen;
}
/*******************************************************************************
* Function Name: PuckCanCollect
****************************************************************************//**
*
* Checks if the puck is able to be picked up, at close proximity.
*
*******************************************************************************/
bool PuckCanCollect(uint8 clr, bool path) {
    PWM_Tilt_WriteCompare(177); //Halfway=162, Upwards = 135
    const uint16 detectHeight = 240*6/8;
    
    CaptureFrameWithLights();
    bool ClrOnScreen = CamScanClosest(clr, 1200);
    uint8 const range = 40;
    uint8 const yOffset = 60;
    if(ClrOnScreen){
        while (240-closestY > detectHeight) { //A quarter of the screen
            MovementForward(100);
            CaptureFrameWithLights();
            ClrOnScreen=CamScanClosest(clr,5000);
        }
        uint8 i;
        bool consistent = true;
        for (i=0; i<2; i++) {
            CaptureFrameWithLights();
            ClrOnScreen=CamScanClosest(clr,5000);
            if (240-closestY > detectHeight) {//|| closestY > (numRows/2+range+yOffset)
                consistent = false;
                i=5;
                MovementBackward(2000);
            } else if (!ClrOnScreen) {
                CamSeqOperations(); //Find Largest 5 Pucks with default threshold.
                if(lrgClr[0]!=clr && lrgY[0]>closestY) //TODO: Won't Handle RED, due to default array val.
                {
                    //Pickup Puck, Turn around, release, turn back.
                    ClawClose();
                    MovementBackward(2000);
                    if(path)
                        MovementPivotLeft(90);
                    else
                        MovementPivotRight(90);
                    
                     MovementForward(500);
                    ClawOpen();
                    MovementBackward(500);
                    MovementBackward(1000);
                    if(path)
                        MovementPivotRight(90);
                    else
                        MovementPivotLeft(90);
                    MovementForward(900);
                }
            }
        }
        if (consistent && ClrOnScreen){
            ClawClose();
            return true;
        }
    }
    return false;
}

/*******************************************************************************
* Function Name: PuckFindEndzone
****************************************************************************//**
*
* Moves the robot to the endzone if it's visible.
*
*******************************************************************************/

bool PuckFindEndzone() {
    //Set new Threshold for Magenta.
    Camera_SetEGWB(160,0,128,128); //set exposure, gain and white balance
    Camera_SetThresholds(-32,64,0,-64,48,-32,-16,16); //set thresholds for the 4 colours - last two are magenta U and V.
    TiltDown45();
    CaptureFrameWithLights();
    if (CamIdentifyEndzone()) {
        while(lowestY < 230) {
            MovementForward( pow(((double)(240-lowestY))/240.0,3)*300.0); 
            CaptureFrameWithLights();
            CamIdentifyEndzone();
        }
        
        //Return to old Threshold: DONT MODIFY.
        Camera_SetEGWB(160,0,128,128);
        Camera_SetThresholds(-32,64,0,-64,48,-32,-16,32);
        return true;
    }
    //Return to old Threshold: DONT MODIFY.
    Camera_SetEGWB(160,0,128,128);
    Camera_SetThresholds(-32,64,0,-64,48,-32,-16,32);
    return false;
}
/*******************************************************************************
* Function Name: PuckAquire
****************************************************************************//**
*
* Uses puck function libraries to aquire a puck (find & pickup).
*
*******************************************************************************/
void PuckAquire(uint8 clr, bool path) {
    
    PanMid();
    CyDelay(50);
    
    bool found = false;
    PuckFarScan(clr);
    PuckFarAquire(clr);
    while(!found) {
            if (PuckCloseScan(clr)){
                if(PuckCloseAquire(clr,path))
                    found=PuckCanCollect(clr,path);
            } else if(PuckFarScan(clr)){
                PuckFarAquire(clr);
            }
            CamDisplaySeq();
            CyDelay(500);
        }
    MovementBackward(3000);
    if(angleTotal > 0)
        MovementPivotLeft(angleTotal%360);
    else
        MovementPivotRight((-angleTotal)%360);
    PuckResetAngleTotal();
}
/*******************************************************************************
* Function Name: PuckResetAngleTotal.
****************************************************************************//**
*
* Resets angle counter.
*
*******************************************************************************/
void PuckResetAngleTotal() {
    angleTotal=0;
}

/*******************************************************************************
* Function Name: PuckPositionToStack
****************************************************************************//**
*
* Aligns the robot to the stack if it's visible.
*
*******************************************************************************/
void PuckPositionToStack(uint8 clr){
    //clr == Colour --> R,G,B == 0,1,2.
    //extern uint8 orderedScaledClr[5]; -> vector of colour sequence
    PanMid(); //Make sure camera is in correct direction.
    CyDelay(200);
    TiltDown45();
    CyDelay(200);
    
    PWM_Tilt_WriteCompare(162);
    CyDelay(20);
    //Hold Weighting Sums & Colours.
    //Initialize Vals.
    int Yend;
    double angle, XYRatio;
    int centreX, centreY;
    CaptureFrameWithLights();
    Yend = CamIdenifyEndzonePuck(clr);
    centreX = closestX-numCols/2;
    centreY = 240-closestY + CAMERA_Y_OFFSET;
    
    bool positioned = false;
    while (!positioned){
        if(240-closestY > numRows*3.0/8.0){ //Align: CloseAquire uses 240-Y > 65...
            while(abs(centreX) > 8) { //Keep turning untill we get a decent alignment //(abs(closestX - numCols/2 - CAMERA_X_OFFSET) > 20) || 
                if (centreX > 0) {
                    XYRatio = ((double)(centreX))/(centreY);
                    angle = cbrt((atan(XYRatio)*180)/PI*corrFact*0.8);
                    MovementPivotRight(angle);
                    angleTotal+=angle;
                } else { //centreX < 0
                    XYRatio=((double)(-centreX))/(centreY);
                    angle = cbrt((atan(XYRatio)*180)/PI*corrFact*0.8);
                    MovementPivotLeft(angle);
                    angleTotal+=angle;
                }
                //Rescan for new position.
                CaptureFrameWithLights();
                Yend = CamIdenifyEndzonePuck(clr);
                centreX = closestX-numCols/2;
                centreY = 240-closestY + CAMERA_Y_OFFSET;
            }
            MovementForward(pow(((240.0-lowestY)/60),2)*300);
            CaptureFrameWithLights();
            Yend = CamIdenifyEndzonePuck(clr);
            centreX = closestX-numCols/2;
            centreY = 240-closestY + CAMERA_Y_OFFSET;
        } else {
            //Close enough to stack?
            if (240 - lowestY < numRows*1.0/8.0 ){
                //Stack.
                positioned=PuckPositionToStack2(clr);
                PWM_Tilt_WriteCompare(162);
                CyDelay(200);
                CaptureFrameWithLights();
                Yend = CamIdenifyEndzonePuck(clr);
                centreX = closestX-numCols/2;
                centreY = 240-closestY + CAMERA_Y_OFFSET;
            } else {
                //Drive closer.
                MovementForward(pow(((240.0-lowestY)/90),2)*300); //From 120 to 90.
                CaptureFrameWithLights();
                Yend = CamIdenifyEndzonePuck(clr);
                centreX = closestX-numCols/2;
                centreY = 240-closestY + CAMERA_Y_OFFSET;
            }
                
        }
    }
}

bool PuckPositionToStack2(uint8 clr){
//clr == Colour --> R,G,B == 0,1,2.
//extern uint8 orderedScaledClr[5]; -> vector of colour sequence
    PWM_Tilt_WriteCompare(180);
    CyDelay(20);
    //Hold Weighting Sums & Colours.
    //Initialize Vals.
    double angle, XYRatio, angleTot=0;
    int centreX, centreY;
    CaptureFrameWithLights();
    bool canSee = CamIdenifyEndzonePuck(clr);
    centreX = closestX-numCols/2;
    centreY = 240-closestY + CAMERA_Y_OFFSET;
    
    
    bool positioned = false;
    while (!positioned && canSee){
        if(240-closestY > numRows*0.33){ //Align: CloseAquire uses 240-Y > 65...
            while(abs(centreX) > 8) { //Keep turning untill we get a decent alignment //(abs(closestX - numCols/2 - CAMERA_X_OFFSET) > 20) || 
                if (centreX > 0) {
                    XYRatio = ((double)(centreX))/(centreY);
                    angle = cbrt((atan(XYRatio)*180)/PI*corrFact/3.0);
                    if (angleTot+angle < 20) {
                        MovementPivotRight(angle);
                        angleTot+=angle;
                    } else {
                        //MovementBackward(1000);
                        return false;
                    }
                } else { //centreX < 0
                    XYRatio=((double)(-centreX))/(centreY);
                    angle = cbrt((atan(XYRatio)*180)/PI*corrFact/3.0);
                    if (angleTot-angle > -20) {
                        MovementPivotLeft(angle);
                        angleTot+=angle;
                    } else {
                        //MovementBackward(1000);
                        return false;
                    }
                }
                //Rescan for new position.
                CaptureFrameWithLights();
                canSee = CamIdenifyEndzonePuck(clr);
                centreX = closestX-numCols/2;
                centreY = 240-closestY + CAMERA_Y_OFFSET;
            }
            MovementForward(pow(((240.0-lowestY)/100),2)*100);
            CaptureFrameWithLights();
            canSee = CamIdenifyEndzonePuck(clr);
            centreX = closestX-numCols/2;
            centreY = 240-closestY + CAMERA_Y_OFFSET;
        } else {
            //Close enough to stack?
            if (240 - lowestY < numRows*0.33 ){
                //Stack.
                MovementForward(400);
                return true;
            } else {
                //Drive closer. SHOULDN'T EXECUTE.
                MovementBackward(500);
            }
                
        }
    }
    if(!canSee) {
        MovementBackward(100);
        return false;
    }
    return positioned;
}

/* [] END OF FILE */



