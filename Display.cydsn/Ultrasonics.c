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

/*******************************************************************************
* Function Name: Ultrasonics
****************************************************************************//**
*
* Takes input of which sensor to use (1 for left, else of right (use 0 or 2))
* Will output a float for distance from ultrasonic sensors
*
*******************************************************************************/

double Ultrasonics(uint8 sensor){
    uint16 countstart,countend, diff;
    double time, dist;
        Beep(3);
        BiDirPortInPut();
        CS_Write(0x01);
        if (sensor==1){
            USTX_Write(1);
            CyDelayUs(10);
            USTX_Write(0);
            while (!(D_Read()&0x1)){
            }
            countstart=Timer_1_ReadCounter();
            while ((D_Read()&0x1)==0x1){
            }
            countend=Timer_1_ReadCounter();
        }else{ 
            USTX2_Write(1);
            CyDelayUs(10);
            USTX2_Write(0);
            while (!(D_Read()&0x4)){
            }
            countstart=Timer_1_ReadCounter();
            while ((D_Read()&0x4)==0x4){
            }
            countend=Timer_1_ReadCounter();
        }

        CS_Write(8);
        diff=countstart-countend;
        BiDirPortOutPut();
        
        //time=0.002731*diff/65536; //this is in seconds (0.002731 for 24 MHz clock)
        time=0.006372*diff/65536; //this is in seconds (0.006372 for 10 MHz clock)
        dist=time*34300/2;    //in cm -> note /2 because there and back again (a hobbits journey)
        
        return dist;
}

double UltrasonicsSensitive(uint8 sensor){
    uint16 countstart,countend, diff;
    double time, dist;
        Beep(3);
        BiDirPortInPut();
        CS_Write(0x01);
        if (sensor==1){
            USTX_Write(1);
            CyDelayUs(10);
            USTX_Write(0);
            while (!(D_Read()&0x1)){
            }
            countstart=Timer_2_ReadCounter();
            while ((D_Read()&0x1)==0x1){
            }
            countend=Timer_2_ReadCounter();
        }else{ 
            USTX2_Write(1);
            CyDelayUs(10);
            USTX2_Write(0);
            while (!(D_Read()&0x4)){
            }
            countstart=Timer_2_ReadCounter();
            while ((D_Read()&0x4)==0x4){
            }
            countend=Timer_2_ReadCounter();
        }

        CS_Write(8);
        diff=countstart-countend;
        BiDirPortOutPut();
        
        //time=0.002731*diff/65536; //this is in seconds (0.002731 for 24 MHz clock)
        time=0.00182*diff/65536; //this is in seconds (0.00182 for 36 MHz clock)
        dist=time*34300/2;    //in cm -> note /2 because there and back again (a hobbits journey)
        
        return dist;
}

double Wall_Align(bool sense,bool sensors){
    const double PI = 3.1415926535;
    const double supression = 0.5;
    double distance1=0;
    double distance2=0;
    double dist_diff=0;
    double alpha;
    int n = 0;
    uint8 i;
    uint8 check = 1;
    uint8 finish = 0;
    double precision;
    
    while(!finish){
        if (sense) distance1 = UltrasonicsSensitive(0);
        else distance1 = Ultrasonics(0);
        CyDelay(50);
        if (sense) distance2 = UltrasonicsSensitive(1);
        else distance2 = Ultrasonics(1);
        dist_diff = (distance1 - distance2);
        precision = pow((distance2+distance1)/2/10,0.2);
        if(fabs(dist_diff)>precision && sensors==0){
            //alpha =  (asin(fabs(dist_diff)/14.0)) * 180.0/PI;
            alpha =  pow(((asin(fabs(dist_diff)/14.0)*180/PI)/60),1.8)*60;
            if(dist_diff>0){
                //right side close than left
                MovementPivotLeft(0.6*alpha*supression); 
            }else{
                //left side closer than right
                MovementPivotRight(0.6*alpha*supression);
            }
        }else{
            check = 0;
            for(i=0;i<5;i++){
                if (sense) distance1 = UltrasonicsSensitive(0);
                else distance1 = Ultrasonics(0);
                CyDelay(100);
                if (sense) distance2 =UltrasonicsSensitive(1);
                else distance2 = Ultrasonics(1);
                dist_diff = (distance1 - distance2);
                precision = pow((distance2+distance1)/2/10,0.2);
                if(fabs(dist_diff)>precision){
                    check = 1;
                    i = 5;
                }
            }
        }
        n++;
        if(!check || sensors==1){
            finish = 1;
            
        }
    }
    return distance1;
}


void MoveAlign(double distance, bool sense, bool sensors, float prec){    //distance in cm
    double dist = Wall_Align(sense,sensors);
    while(fabs(distance-dist)>prec)
    {
        //3s/14.5cm
        if (dist-distance>0){
            MovementForward(3000.0/14.5*pow((dist-distance)/10.0,1.25)*10.0);
            dist = Wall_Align(sense,sensors);
        }else{
            MovementBackward(-3000.0/14.5*(dist-distance));
            //OLD CORRECTION FCN: MovementBackward(3000.0/14.5*(distance-dist)*0.75);
            dist = Wall_Align(sense,0);
        }
        //dist = Wall_Align();
    }
}


/* [] END OF FILE */
