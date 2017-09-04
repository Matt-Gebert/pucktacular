/*******************************************************************************
* File Name: Quad_1_PM.c
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

#include "Quad_1.h"

static Quad_1_BACKUP_STRUCT Quad_1_backup = {0u};


/*******************************************************************************
* Function Name: Quad_1_SaveConfig
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
void Quad_1_SaveConfig(void) 
{
    #if (Quad_1_COUNTER_SIZE == Quad_1_COUNTER_SIZE_8_BIT)
        Quad_1_Cnt8_SaveConfig();
    #else 
        /* (Quad_1_COUNTER_SIZE == Quad_1_COUNTER_SIZE_16_BIT) || 
         * (Quad_1_COUNTER_SIZE == Quad_1_COUNTER_SIZE_32_BIT)
         */
        Quad_1_Cnt16_SaveConfig();
    #endif /* (Quad_1_COUNTER_SIZE == Quad_1_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: Quad_1_RestoreConfig
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
void Quad_1_RestoreConfig(void) 
{
    #if (Quad_1_COUNTER_SIZE == Quad_1_COUNTER_SIZE_8_BIT)
        Quad_1_Cnt8_RestoreConfig();
    #else 
        /* (Quad_1_COUNTER_SIZE == Quad_1_COUNTER_SIZE_16_BIT) || 
         * (Quad_1_COUNTER_SIZE == Quad_1_COUNTER_SIZE_32_BIT) 
         */
        Quad_1_Cnt16_RestoreConfig();
    #endif /* (Quad_1_COUNTER_SIZE == Quad_1_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: Quad_1_Sleep
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
*  Quad_1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Quad_1_Sleep(void) 
{
    if (0u != (Quad_1_SR_AUX_CONTROL & Quad_1_INTERRUPTS_ENABLE))
    {
        Quad_1_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        Quad_1_backup.enableState = 0u;
    }

    Quad_1_Stop();
    Quad_1_SaveConfig();
}


/*******************************************************************************
* Function Name: Quad_1_Wakeup
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
*  Quad_1_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void Quad_1_Wakeup(void) 
{
    Quad_1_RestoreConfig();

    if (Quad_1_backup.enableState != 0u)
    {
        #if (Quad_1_COUNTER_SIZE == Quad_1_COUNTER_SIZE_8_BIT)
            Quad_1_Cnt8_Enable();
        #else 
            /* (Quad_1_COUNTER_SIZE == Quad_1_COUNTER_SIZE_16_BIT) || 
            *  (Quad_1_COUNTER_SIZE == Quad_1_COUNTER_SIZE_32_BIT) 
            */
            Quad_1_Cnt16_Enable();
        #endif /* (Quad_1_COUNTER_SIZE == Quad_1_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        Quad_1_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

