/*******************************************************************************
* File Name: SW_Comparator.c
* Version 2.0
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "SW_Comparator.h"

static SW_Comparator_backupStruct SW_Comparator_backup;


/*******************************************************************************
* Function Name: SW_Comparator_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
*******************************************************************************/
void SW_Comparator_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: SW_Comparator_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
********************************************************************************/
void SW_Comparator_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: SW_Comparator_Sleep
********************************************************************************
*
* Summary:
*  Stop and Save the user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
* Global variables:
*  SW_Comparator_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void SW_Comparator_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(SW_Comparator_ACT_PWR_EN == (SW_Comparator_PWRMGR & SW_Comparator_ACT_PWR_EN))
    {
        /* Comp is enabled */
        SW_Comparator_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        SW_Comparator_backup.enableState = 0u;
    }    
    
    SW_Comparator_Stop();
    SW_Comparator_SaveConfig();
}


/*******************************************************************************
* Function Name: SW_Comparator_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SW_Comparator_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void SW_Comparator_Wakeup(void) 
{
    SW_Comparator_RestoreConfig();
    
    if(SW_Comparator_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        SW_Comparator_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
