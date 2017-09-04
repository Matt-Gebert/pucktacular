/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include "lift_functions.h"
int16 pucklvl =0x1270;
int16 groundlvl = -0x6fff;

void LiftInital(){
    Quad_3_Start();
    CyDelay(10);
    Quad_3_SetCounter(groundlvl);
}

void LiftSetGround(){
    Quad_3_SetCounter(groundlvl);
}

void LiftDownReset(){
    LiftA_Write(1);
    LiftB_Write(0);
    CyDelay(500);
    LiftA_Write(0);
    LiftB_Write(0);
}

void LiftUpReset(){
    LiftA_Write(0);
    LiftB_Write(1);
    CyDelay(500);
    LiftB_Write(0);
    LiftA_Write(0);
    
}

void LiftLv0(){
    
    if(Quad_3_GetCounter()>groundlvl){
        LiftA_Write(1);
        LiftB_Write(0);
        while (Quad_3_GetCounter()>groundlvl){
        CyDelay(100);
        }
        LiftA_Write(0);
        LiftB_Write(0);
    }
}

void LiftLv1(){
    LiftLvN(1);
}

void LiftLv2(){
    LiftLvN(2);
}

void LiftLv3(){
    LiftLvN(3);
}

void LiftLv4(){
    LiftLvN(4);
}

void LiftLvMax(){
    LiftLvN(9);
}

void LiftLvN(uint8 lvl){
    if(Quad_3_GetCounter()>(groundlvl+lvl*pucklvl)){
        LiftA_Write(1);
        LiftB_Write(0);
        while (Quad_3_GetCounter()>(groundlvl+lvl*pucklvl)){
        CyDelay(100);
        }
        LiftA_Write(0);
        LiftB_Write(0);
    }else{
        LiftA_Write(0);
        LiftB_Write(1);
        while (Quad_3_GetCounter()<(groundlvl+lvl*pucklvl)){
        CyDelay(100);
        }
        LiftB_Write(0);
        LiftA_Write(0);
    }
}


/* [] END OF FILE */
