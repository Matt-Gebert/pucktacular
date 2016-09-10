/*******************************************************************************
* File Name: Camera_Threshold_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Camera_Threshold.h"

/* Check for removal by optimization */
#if !defined(Camera_Threshold_Sync_ctrl_reg__REMOVED)

static Camera_Threshold_BACKUP_STRUCT  Camera_Threshold_backup = {0u};

    
/*******************************************************************************
* Function Name: Camera_Threshold_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Camera_Threshold_SaveConfig(void) 
{
    Camera_Threshold_backup.controlState = Camera_Threshold_Control;
}


/*******************************************************************************
* Function Name: Camera_Threshold_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void Camera_Threshold_RestoreConfig(void) 
{
     Camera_Threshold_Control = Camera_Threshold_backup.controlState;
}


/*******************************************************************************
* Function Name: Camera_Threshold_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Camera_Threshold_Sleep(void) 
{
    Camera_Threshold_SaveConfig();
}


/*******************************************************************************
* Function Name: Camera_Threshold_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Camera_Threshold_Wakeup(void)  
{
    Camera_Threshold_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
