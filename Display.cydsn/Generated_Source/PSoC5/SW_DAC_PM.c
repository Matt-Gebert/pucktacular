/*******************************************************************************
* File Name: SW_DAC_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
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

#include "SW_DAC.h"

static SW_DAC_backupStruct SW_DAC_backup;


/*******************************************************************************
* Function Name: SW_DAC_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void SW_DAC_SaveConfig(void) 
{
    if (!((SW_DAC_CR1 & SW_DAC_SRC_MASK) == SW_DAC_SRC_UDB))
    {
        SW_DAC_backup.data_value = SW_DAC_Data;
    }
}


/*******************************************************************************
* Function Name: SW_DAC_RestoreConfig
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
*******************************************************************************/
void SW_DAC_RestoreConfig(void) 
{
    if (!((SW_DAC_CR1 & SW_DAC_SRC_MASK) == SW_DAC_SRC_UDB))
    {
        if((SW_DAC_Strobe & SW_DAC_STRB_MASK) == SW_DAC_STRB_EN)
        {
            SW_DAC_Strobe &= (uint8)(~SW_DAC_STRB_MASK);
            SW_DAC_Data = SW_DAC_backup.data_value;
            SW_DAC_Strobe |= SW_DAC_STRB_EN;
        }
        else
        {
            SW_DAC_Data = SW_DAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: SW_DAC_Sleep
********************************************************************************
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
*  SW_DAC_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void SW_DAC_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(SW_DAC_ACT_PWR_EN == (SW_DAC_PWRMGR & SW_DAC_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        SW_DAC_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        SW_DAC_backup.enableState = 0u;
    }
    
    SW_DAC_Stop();
    SW_DAC_SaveConfig();
}


/*******************************************************************************
* Function Name: SW_DAC_Wakeup
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
*  SW_DAC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void SW_DAC_Wakeup(void) 
{
    SW_DAC_RestoreConfig();
    
    if(SW_DAC_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        SW_DAC_Enable();

        /* Restore the data register */
        SW_DAC_SetValue(SW_DAC_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
