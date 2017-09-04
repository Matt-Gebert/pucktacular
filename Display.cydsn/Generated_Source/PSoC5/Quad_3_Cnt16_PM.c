/*******************************************************************************
* File Name: Quad_3_Cnt16_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Quad_3_Cnt16.h"

static Quad_3_Cnt16_backupStruct Quad_3_Cnt16_backup;


/*******************************************************************************
* Function Name: Quad_3_Cnt16_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Quad_3_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Quad_3_Cnt16_SaveConfig(void) 
{
    #if (!Quad_3_Cnt16_UsingFixedFunction)

        Quad_3_Cnt16_backup.CounterUdb = Quad_3_Cnt16_ReadCounter();

        #if(!Quad_3_Cnt16_ControlRegRemoved)
            Quad_3_Cnt16_backup.CounterControlRegister = Quad_3_Cnt16_ReadControlRegister();
        #endif /* (!Quad_3_Cnt16_ControlRegRemoved) */

    #endif /* (!Quad_3_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Quad_3_Cnt16_RestoreConfig
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
* Global variables:
*  Quad_3_Cnt16_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Quad_3_Cnt16_RestoreConfig(void) 
{      
    #if (!Quad_3_Cnt16_UsingFixedFunction)

       Quad_3_Cnt16_WriteCounter(Quad_3_Cnt16_backup.CounterUdb);

        #if(!Quad_3_Cnt16_ControlRegRemoved)
            Quad_3_Cnt16_WriteControlRegister(Quad_3_Cnt16_backup.CounterControlRegister);
        #endif /* (!Quad_3_Cnt16_ControlRegRemoved) */

    #endif /* (!Quad_3_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Quad_3_Cnt16_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Quad_3_Cnt16_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Quad_3_Cnt16_Sleep(void) 
{
    #if(!Quad_3_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Quad_3_Cnt16_CTRL_ENABLE == (Quad_3_Cnt16_CONTROL & Quad_3_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Quad_3_Cnt16_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Quad_3_Cnt16_backup.CounterEnableState = 0u;
        }
    #else
        Quad_3_Cnt16_backup.CounterEnableState = 1u;
        if(Quad_3_Cnt16_backup.CounterEnableState != 0u)
        {
            Quad_3_Cnt16_backup.CounterEnableState = 0u;
        }
    #endif /* (!Quad_3_Cnt16_ControlRegRemoved) */
    
    Quad_3_Cnt16_Stop();
    Quad_3_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: Quad_3_Cnt16_Wakeup
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
*  Quad_3_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Quad_3_Cnt16_Wakeup(void) 
{
    Quad_3_Cnt16_RestoreConfig();
    #if(!Quad_3_Cnt16_ControlRegRemoved)
        if(Quad_3_Cnt16_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Quad_3_Cnt16_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Quad_3_Cnt16_ControlRegRemoved) */
    
}


/* [] END OF FILE */
