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
#include "Ultrasonics.h"
#include "utils.h"
#include "pathing.h"

void PathForward(bool path){
 //This function assumes that the bot is positioned at 20 cm from back wall & 20cm from side wall
 //near the stacking zone,facing away from the stacking zone.
    
    //path determines which path must be taken to avoid the brick
    if(!path){  // path==0 -> using shorter path
        //drive forward 5s
        MovementPivotLeft90();
        CyDelay(20);
        //MoveAlign(15,false,0,0.8);
        MoveAlign(15,false,0,0.8); //true to false..
        CyDelay(20);
        MovementPivotRight90();
        CyDelay(20);
        MovementForward(10000);
        //use wall_align to get to 20 cm from far wall
        //MoveAlign(20,false,0,0.8);
        MoveAlign(12,false,0,0.8);//true to false..
        // pivot right 90
        MovementPivotRight90();
        
    }else{ // path==1 -> using longer path
        //pivot right 90 degrees
        MovementPivotRight90();
        //drive forward 7s
        MovementForward(8000);
        //use wall_align to get to 20cm from side wall
        //MoveAlign(15,false,0,0.8);
        MoveAlign(10,false,0,0.8);//true to false..
        //pivot left 90
        MovementPivotLeft90();
        //drive forward 5s
        MovementForward(8000);
        //use wall_align to get to 20 cm from far wall
       //MoveAlign(20,false,0,0.8);
        MoveAlign(12,false,0,0.8);//true to false..
        // pivot left 90
        MovementPivotLeft90();
        
    }
    
}


void PathBackward(bool path){
    //path determines which path must be taken to avoid the brick
    if(!path){  // path==0 -> using shorter path
        //pivot 180
        MovementPivotRight90();
        CyDelay(100);
        MovementPivotRight(85);
        CyDelay(20);
        //use wall_align to get 20 cm from side wall
        //MoveAlign(18,false,0,0.8);
        MoveAlign(10,false,0,0.8);
        CyDelay(20);
        //pivot left 90
        MovementPivotLeft(86);
        CyDelay(20);
        //drive forward for 4 sec (4 sec to be safer)
        MovementForward(10000); //
        CyDelay(20);
        //Remove Extra Check: 
        /*MovementPivotRight90();
        CyDelay(20);
        MoveAlign(10,false,0,0.4);
        CyDelay(20);
        MovementPivotLeft90();
        CyDelay(20);
        */
        
        //use wall_align to get 20 cm from back wall
        //MoveAlign(23,false,1,0.8);
        MoveAlign(15,false,1,0.8);//true to false..
        //new
        MovementPivotRight90();
        MoveAlign(13,true,0,0.8);
        MovementPivotLeft90();
        /*MoveAlign(10,true,1); //Coded added to the main function. Depends on puck counter...
        Beep(2);
        CyDelay(100);
        Beep(2);*/
        
    }else{      // path==1 -> using longer path
        //pivot 180
        MovementPivotLeft90();
        CyDelay(50);
        MovementPivotLeft(80);
        //use wall_align to get 20 cm from side wall 
        CyDelay(20);
        //MoveAlign(18,false,0,0.8);
        MoveAlign(15,false,0,0.8);//true to false..
        CyDelay(20);
        //pivot right 90
        MovementPivotRight(90);
        CyDelay(20);
        //drive forward for 4 sec (4 sec to be safer)
        MovementForward(7000);
        //use wall_align to get 25 cm from back wall (once again on safe side)
        //MoveAlign(23,false,0,0.8);
        MoveAlign(25,false,0,0.8);//true to false..
        MoveAlign(25,true,0,0.8);
        //pivot right 90
        MovementPivotRight(90);
        //drive forward for 7 sec
        MovementForward(11000);
        //use wall_align to get 20 cm from side wall 
        MoveAlign(13,false,0,0.8);
        MoveAlign(13,true,0,0.8);
        //pivot left 90
        MovementPivotLeft90();
    }
}

/* [] END OF FILE */
