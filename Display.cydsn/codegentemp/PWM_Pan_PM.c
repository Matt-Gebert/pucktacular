/*******************************************************************************
* File Name: PWM_Pan_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_Pan.h"

static PWM_Pan_backupStruct PWM_Pan_backup;


/*******************************************************************************
* Function Name: PWM_Pan_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Pan_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Pan_SaveConfig(void) 
{

    #if(!PWM_Pan_UsingFixedFunction)
        #if(!PWM_Pan_PWMModeIsCenterAligned)
            PWM_Pan_backup.PWMPeriod = PWM_Pan_ReadPeriod();
        #endif /* (!PWM_Pan_PWMModeIsCenterAligned) */
        PWM_Pan_backup.PWMUdb = PWM_Pan_ReadCounter();
        #if (PWM_Pan_UseStatus)
            PWM_Pan_backup.InterruptMaskValue = PWM_Pan_STATUS_MASK;
        #endif /* (PWM_Pan_UseStatus) */

        #if(PWM_Pan_DeadBandMode == PWM_Pan__B_PWM__DBM_256_CLOCKS || \
            PWM_Pan_DeadBandMode == PWM_Pan__B_PWM__DBM_2_4_CLOCKS)
            PWM_Pan_backup.PWMdeadBandValue = PWM_Pan_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Pan_KillModeMinTime)
             PWM_Pan_backup.PWMKillCounterPeriod = PWM_Pan_ReadKillTime();
        #endif /* (PWM_Pan_KillModeMinTime) */

        #if(PWM_Pan_UseControl)
            PWM_Pan_backup.PWMControlRegister = PWM_Pan_ReadControlRegister();
        #endif /* (PWM_Pan_UseControl) */
    #endif  /* (!PWM_Pan_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Pan_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Pan_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Pan_RestoreConfig(void) 
{
        #if(!PWM_Pan_UsingFixedFunction)
            #if(!PWM_Pan_PWMModeIsCenterAligned)
                PWM_Pan_WritePeriod(PWM_Pan_backup.PWMPeriod);
            #endif /* (!PWM_Pan_PWMModeIsCenterAligned) */

            PWM_Pan_WriteCounter(PWM_Pan_backup.PWMUdb);

            #if (PWM_Pan_UseStatus)
                PWM_Pan_STATUS_MASK = PWM_Pan_backup.InterruptMaskValue;
            #endif /* (PWM_Pan_UseStatus) */

            #if(PWM_Pan_DeadBandMode == PWM_Pan__B_PWM__DBM_256_CLOCKS || \
                PWM_Pan_DeadBandMode == PWM_Pan__B_PWM__DBM_2_4_CLOCKS)
                PWM_Pan_WriteDeadTime(PWM_Pan_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Pan_KillModeMinTime)
                PWM_Pan_WriteKillTime(PWM_Pan_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Pan_KillModeMinTime) */

            #if(PWM_Pan_UseControl)
                PWM_Pan_WriteControlRegister(PWM_Pan_backup.PWMControlRegister);
            #endif /* (PWM_Pan_UseControl) */
        #endif  /* (!PWM_Pan_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Pan_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Pan_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Pan_Sleep(void) 
{
    #if(PWM_Pan_UseControl)
        if(PWM_Pan_CTRL_ENABLE == (PWM_Pan_CONTROL & PWM_Pan_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Pan_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Pan_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Pan_UseControl) */

    /* Stop component */
    PWM_Pan_Stop();

    /* Save registers configuration */
    PWM_Pan_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Pan_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Pan_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Pan_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Pan_RestoreConfig();

    if(PWM_Pan_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Pan_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
