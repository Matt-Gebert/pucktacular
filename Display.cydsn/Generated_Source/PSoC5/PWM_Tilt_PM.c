/*******************************************************************************
* File Name: PWM_Tilt_PM.c
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

#include "PWM_Tilt.h"

static PWM_Tilt_backupStruct PWM_Tilt_backup;


/*******************************************************************************
* Function Name: PWM_Tilt_SaveConfig
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
*  PWM_Tilt_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Tilt_SaveConfig(void) 
{

    #if(!PWM_Tilt_UsingFixedFunction)
        #if(!PWM_Tilt_PWMModeIsCenterAligned)
            PWM_Tilt_backup.PWMPeriod = PWM_Tilt_ReadPeriod();
        #endif /* (!PWM_Tilt_PWMModeIsCenterAligned) */
        PWM_Tilt_backup.PWMUdb = PWM_Tilt_ReadCounter();
        #if (PWM_Tilt_UseStatus)
            PWM_Tilt_backup.InterruptMaskValue = PWM_Tilt_STATUS_MASK;
        #endif /* (PWM_Tilt_UseStatus) */

        #if(PWM_Tilt_DeadBandMode == PWM_Tilt__B_PWM__DBM_256_CLOCKS || \
            PWM_Tilt_DeadBandMode == PWM_Tilt__B_PWM__DBM_2_4_CLOCKS)
            PWM_Tilt_backup.PWMdeadBandValue = PWM_Tilt_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Tilt_KillModeMinTime)
             PWM_Tilt_backup.PWMKillCounterPeriod = PWM_Tilt_ReadKillTime();
        #endif /* (PWM_Tilt_KillModeMinTime) */

        #if(PWM_Tilt_UseControl)
            PWM_Tilt_backup.PWMControlRegister = PWM_Tilt_ReadControlRegister();
        #endif /* (PWM_Tilt_UseControl) */
    #endif  /* (!PWM_Tilt_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Tilt_RestoreConfig
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
*  PWM_Tilt_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Tilt_RestoreConfig(void) 
{
        #if(!PWM_Tilt_UsingFixedFunction)
            #if(!PWM_Tilt_PWMModeIsCenterAligned)
                PWM_Tilt_WritePeriod(PWM_Tilt_backup.PWMPeriod);
            #endif /* (!PWM_Tilt_PWMModeIsCenterAligned) */

            PWM_Tilt_WriteCounter(PWM_Tilt_backup.PWMUdb);

            #if (PWM_Tilt_UseStatus)
                PWM_Tilt_STATUS_MASK = PWM_Tilt_backup.InterruptMaskValue;
            #endif /* (PWM_Tilt_UseStatus) */

            #if(PWM_Tilt_DeadBandMode == PWM_Tilt__B_PWM__DBM_256_CLOCKS || \
                PWM_Tilt_DeadBandMode == PWM_Tilt__B_PWM__DBM_2_4_CLOCKS)
                PWM_Tilt_WriteDeadTime(PWM_Tilt_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Tilt_KillModeMinTime)
                PWM_Tilt_WriteKillTime(PWM_Tilt_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Tilt_KillModeMinTime) */

            #if(PWM_Tilt_UseControl)
                PWM_Tilt_WriteControlRegister(PWM_Tilt_backup.PWMControlRegister);
            #endif /* (PWM_Tilt_UseControl) */
        #endif  /* (!PWM_Tilt_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Tilt_Sleep
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
*  PWM_Tilt_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Tilt_Sleep(void) 
{
    #if(PWM_Tilt_UseControl)
        if(PWM_Tilt_CTRL_ENABLE == (PWM_Tilt_CONTROL & PWM_Tilt_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Tilt_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Tilt_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Tilt_UseControl) */

    /* Stop component */
    PWM_Tilt_Stop();

    /* Save registers configuration */
    PWM_Tilt_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Tilt_Wakeup
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
*  PWM_Tilt_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Tilt_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Tilt_RestoreConfig();

    if(PWM_Tilt_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Tilt_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
