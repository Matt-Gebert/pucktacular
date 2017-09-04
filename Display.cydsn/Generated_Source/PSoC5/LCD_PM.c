/*******************************************************************************
* File Name: LCD_PM.c
* Version 1.70
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD.h" 

#if (CY_UDB_V0)
    static LCD_BACKUP_STRUCT LCD_backup = 
    {
        LCD_READ_LOW_PULSE,
        LCD_READ_HIGH_PULSE 
    };
#endif /* (CY_UDB_V0) */


/*******************************************************************************
* Function Name: LCD_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the user configuration of GraphicLCDIntf.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  LCD_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_SaveConfig(void) 
{   
    /* Saves D0/D1 Regs are non-retention for the UDB array version 0 */
    #if (CY_UDB_V0)                       
        LCD_backup.lowPulseWidth  = LCD_READ_LO_PULSE_REG;
        LCD_backup.highPulseWidth = LCD_READ_HI_PULSE_REG;      
    #endif /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: LCD_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the user configuration of GraphicLCDIntf.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  LCD_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void LCD_RestoreConfig(void) 
{    
    /* Restores D0/D1 Regs are non-retention for the UDB array version 0 */
    #if (CY_UDB_V0)                         
        LCD_READ_LO_PULSE_REG = LCD_backup.lowPulseWidth;
        LCD_READ_HI_PULSE_REG = LCD_backup.highPulseWidth;
    #endif /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: LCD_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  prior to entering sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  LCD_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Sleep(void) 
{
    LCD_Stop();
    LCD_SaveConfig();
}


/*******************************************************************************
* Function Name: LCD_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  after awaking from sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  LCD_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void LCD_Wakeup(void) 
{
    LCD_RestoreConfig();
    LCD_Enable();
}


/* [] END OF FILE */
