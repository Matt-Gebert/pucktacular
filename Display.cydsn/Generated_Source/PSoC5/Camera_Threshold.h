/*******************************************************************************
* File Name: Camera_Threshold.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_Camera_Threshold_H) /* CY_CONTROL_REG_Camera_Threshold_H */
#define CY_CONTROL_REG_Camera_Threshold_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} Camera_Threshold_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    Camera_Threshold_Write(uint8 control) ;
uint8   Camera_Threshold_Read(void) ;

void Camera_Threshold_SaveConfig(void) ;
void Camera_Threshold_RestoreConfig(void) ;
void Camera_Threshold_Sleep(void) ; 
void Camera_Threshold_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define Camera_Threshold_Control        (* (reg8 *) Camera_Threshold_Sync_ctrl_reg__CONTROL_REG )
#define Camera_Threshold_Control_PTR    (  (reg8 *) Camera_Threshold_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_Camera_Threshold_H */


/* [] END OF FILE */
