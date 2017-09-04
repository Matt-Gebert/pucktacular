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
 * Useful information
 * Lift going up
   LiftA_Write(0);
   LiftB_Write(1);
 * Lift going down
   LiftA_Write(1);
   LiftB_Write(0);
 * Lift Stop
   LiftA_Write(0);
   LiftB_Write(0);

*/

#include <project.h>
void LiftInital();
void LiftSetGround();
void LiftDownReset();
void LiftUpReset();
void LiftLv0();
void LiftLv1();
void LiftLv2();
void LiftLv3();
void LiftLv4();
void LiftLvMax();
void LiftLvN(uint8 lvl);

/* [] END OF FILE */
