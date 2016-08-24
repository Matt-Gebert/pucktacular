/*******************************************************************************
* File Name: OE_PM.c
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

#include "OE.h"

/* Check for removal by optimization */
#if !defined(OE_Sync_ctrl_reg__REMOVED)

static OE_BACKUP_STRUCT  OE_backup = {0u};

    
/*******************************************************************************
* Function Name: OE_SaveConfig
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
void OE_SaveConfig(void) 
{
    OE_backup.controlState = OE_Control;
}


/*******************************************************************************
* Function Name: OE_RestoreConfig
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
void OE_RestoreConfig(void) 
{
     OE_Control = OE_backup.controlState;
}


/*******************************************************************************
* Function Name: OE_Sleep
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
void OE_Sleep(void) 
{
    OE_SaveConfig();
}


/*******************************************************************************
* Function Name: OE_Wakeup
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
void OE_Wakeup(void)  
{
    OE_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
