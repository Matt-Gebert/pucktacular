/*******************************************************************************
* File Name: PWM_Claw_PM.c
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

#include "PWM_Claw.h"

static PWM_Claw_backupStruct PWM_Claw_backup;


/*******************************************************************************
* Function Name: PWM_Claw_SaveConfig
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
*  PWM_Claw_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Claw_SaveConfig(void) 
{

    #if(!PWM_Claw_UsingFixedFunction)
        #if(!PWM_Claw_PWMModeIsCenterAligned)
            PWM_Claw_backup.PWMPeriod = PWM_Claw_ReadPeriod();
        #endif /* (!PWM_Claw_PWMModeIsCenterAligned) */
        PWM_Claw_backup.PWMUdb = PWM_Claw_ReadCounter();
        #if (PWM_Claw_UseStatus)
            PWM_Claw_backup.InterruptMaskValue = PWM_Claw_STATUS_MASK;
        #endif /* (PWM_Claw_UseStatus) */

        #if(PWM_Claw_DeadBandMode == PWM_Claw__B_PWM__DBM_256_CLOCKS || \
            PWM_Claw_DeadBandMode == PWM_Claw__B_PWM__DBM_2_4_CLOCKS)
            PWM_Claw_backup.PWMdeadBandValue = PWM_Claw_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Claw_KillModeMinTime)
             PWM_Claw_backup.PWMKillCounterPeriod = PWM_Claw_ReadKillTime();
        #endif /* (PWM_Claw_KillModeMinTime) */

        #if(PWM_Claw_UseControl)
            PWM_Claw_backup.PWMControlRegister = PWM_Claw_ReadControlRegister();
        #endif /* (PWM_Claw_UseControl) */
    #endif  /* (!PWM_Claw_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Claw_RestoreConfig
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
*  PWM_Claw_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Claw_RestoreConfig(void) 
{
        #if(!PWM_Claw_UsingFixedFunction)
            #if(!PWM_Claw_PWMModeIsCenterAligned)
                PWM_Claw_WritePeriod(PWM_Claw_backup.PWMPeriod);
            #endif /* (!PWM_Claw_PWMModeIsCenterAligned) */

            PWM_Claw_WriteCounter(PWM_Claw_backup.PWMUdb);

            #if (PWM_Claw_UseStatus)
                PWM_Claw_STATUS_MASK = PWM_Claw_backup.InterruptMaskValue;
            #endif /* (PWM_Claw_UseStatus) */

            #if(PWM_Claw_DeadBandMode == PWM_Claw__B_PWM__DBM_256_CLOCKS || \
                PWM_Claw_DeadBandMode == PWM_Claw__B_PWM__DBM_2_4_CLOCKS)
                PWM_Claw_WriteDeadTime(PWM_Claw_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Claw_KillModeMinTime)
                PWM_Claw_WriteKillTime(PWM_Claw_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Claw_KillModeMinTime) */

            #if(PWM_Claw_UseControl)
                PWM_Claw_WriteControlRegister(PWM_Claw_backup.PWMControlRegister);
            #endif /* (PWM_Claw_UseControl) */
        #endif  /* (!PWM_Claw_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Claw_Sleep
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
*  PWM_Claw_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Claw_Sleep(void) 
{
    #if(PWM_Claw_UseControl)
        if(PWM_Claw_CTRL_ENABLE == (PWM_Claw_CONTROL & PWM_Claw_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Claw_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Claw_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Claw_UseControl) */

    /* Stop component */
    PWM_Claw_Stop();

    /* Save registers configuration */
    PWM_Claw_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Claw_Wakeup
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
*  PWM_Claw_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Claw_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Claw_RestoreConfig();

    if(PWM_Claw_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Claw_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
