/*******************************************************************************
* File Name: Quad_2_PM.c
* Version 3.0
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Quad_2.h"

static Quad_2_BACKUP_STRUCT Quad_2_backup = {0u};


/*******************************************************************************
* Function Name: Quad_2_SaveConfig
********************************************************************************
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Quad_2_SaveConfig(void) 
{
    #if (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT)
        Quad_2_Cnt8_SaveConfig();
    #else 
        /* (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_16_BIT) || 
         * (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT)
         */
        Quad_2_Cnt16_SaveConfig();
    #endif /* (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: Quad_2_RestoreConfig
********************************************************************************
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Quad_2_RestoreConfig(void) 
{
    #if (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT)
        Quad_2_Cnt8_RestoreConfig();
    #else 
        /* (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_16_BIT) || 
         * (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT) 
         */
        Quad_2_Cnt16_RestoreConfig();
    #endif /* (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: Quad_2_Sleep
********************************************************************************
* 
* Summary:
*  Prepare Quadrature Decoder Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Quad_2_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Quad_2_Sleep(void) 
{
    if (0u != (Quad_2_SR_AUX_CONTROL & Quad_2_INTERRUPTS_ENABLE))
    {
        Quad_2_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        Quad_2_backup.enableState = 0u;
    }

    Quad_2_Stop();
    Quad_2_SaveConfig();
}


/*******************************************************************************
* Function Name: Quad_2_Wakeup
********************************************************************************
*
* Summary:
*  Prepare Quadrature Decoder Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Quad_2_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void Quad_2_Wakeup(void) 
{
    Quad_2_RestoreConfig();

    if (Quad_2_backup.enableState != 0u)
    {
        #if (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT)
            Quad_2_Cnt8_Enable();
        #else 
            /* (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_16_BIT) || 
            *  (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT) 
            */
            Quad_2_Cnt16_Enable();
        #endif /* (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        Quad_2_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

