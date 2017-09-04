/*******************************************************************************
* File Name: Quad_2.c  
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the Quadrature Decoder
*  component.
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

#if (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT)
    #include "Quad_2_PVT.h"
#endif /* Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT */

uint8 Quad_2_initVar = 0u;


/*******************************************************************************
* Function Name: Quad_2_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default QuadDec configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Quad_2_Init(void) 
{
    #if (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT)
        /* Disable Interrupt. */
        CyIntDisable(Quad_2_ISR_NUMBER);
        /* Set the ISR to point to the Quad_2_isr Interrupt. */
        (void) CyIntSetVector(Quad_2_ISR_NUMBER, & Quad_2_ISR);
        /* Set the priority. */
        CyIntSetPriority(Quad_2_ISR_NUMBER, Quad_2_ISR_PRIORITY);
    #endif /* Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: Quad_2_Enable
********************************************************************************
*
* Summary:
*  This function enable interrupts from Component and also enable Component's
*  ISR in case of 32-bit counter.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Quad_2_Enable(void) 
{
    uint8 enableInterrupts;

    Quad_2_SetInterruptMask(Quad_2_INIT_INT_MASK);

    /* Clear pending interrupts. */
    (void) Quad_2_GetEvents();
    
    enableInterrupts = CyEnterCriticalSection();

    /* Enable interrupts from Statusi register */
    Quad_2_SR_AUX_CONTROL |= Quad_2_INTERRUPTS_ENABLE;

    CyExitCriticalSection(enableInterrupts);        

    #if (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT)
        /* Enable Component interrupts */
        CyIntEnable(Quad_2_ISR_NUMBER);
    #endif /* Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: Quad_2_Start
********************************************************************************
*
* Summary:
*  Initializes UDBs and other relevant hardware.
*  Resets counter, enables or disables all relevant interrupts.
*  Starts monitoring the inputs and counting.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Quad_2_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Quad_2_Start(void) 
{
    #if (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT)
        Quad_2_Cnt8_Start();
        Quad_2_Cnt8_WriteCounter(Quad_2_COUNTER_INIT_VALUE);
    #else
        /* (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_16_BIT) || 
        *  (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT) 
        */
        Quad_2_Cnt16_Start();
        Quad_2_Cnt16_WriteCounter(Quad_2_COUNTER_INIT_VALUE);
    #endif /* Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT */
    
    #if (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT)        
       Quad_2_count32SoftPart = 0;
    #endif /* Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT */

    if (Quad_2_initVar == 0u)
    {
        Quad_2_Init();
        Quad_2_initVar = 1u;
    }

    Quad_2_Enable();
}


/*******************************************************************************
* Function Name: Quad_2_Stop
********************************************************************************
*
* Summary:
*  Turns off UDBs and other relevant hardware.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Quad_2_Stop(void) 
{
    uint8 enableInterrupts;

    #if (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT)
        Quad_2_Cnt8_Stop();
    #else 
        /* (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_16_BIT) ||
        *  (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT)
        */
        Quad_2_Cnt16_Stop();    /* counter disable */
    #endif /* (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT) */
 
    enableInterrupts = CyEnterCriticalSection();

    /* Disable interrupts interrupts from Statusi register */
    Quad_2_SR_AUX_CONTROL &= (uint8) (~Quad_2_INTERRUPTS_ENABLE);

    CyExitCriticalSection(enableInterrupts);

    #if (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT)
        CyIntDisable(Quad_2_ISR_NUMBER);    /* interrupt disable */
    #endif /* Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: Quad_2_GetCounter
********************************************************************************
*
* Summary:
*  Reports the current value of the counter.
*
* Parameters:
*  None.
*
* Return:
*  The counter value. Return type is signed and per the counter size setting.
*  A positive value indicates clockwise movement (B before A).
*
* Global variables:
*  Quad_2_count32SoftPart - used to get hi 16 bit for current value
*  of the 32-bit counter, when Counter size equal 32-bit.
*
*******************************************************************************/
int16 Quad_2_GetCounter(void) 
{
    int16 count;
    uint16 tmpCnt;

    #if (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT)
        int16 hwCount;

        CyIntDisable(Quad_2_ISR_NUMBER);

        tmpCnt = Quad_2_Cnt16_ReadCounter();
        hwCount = (int16) ((int32) tmpCnt - (int32) Quad_2_COUNTER_INIT_VALUE);
        count = Quad_2_count32SoftPart + hwCount;

        CyIntEnable(Quad_2_ISR_NUMBER);
    #else 
        /* (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT) || 
        *  (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_16_BIT)
        */
        #if (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT)
            tmpCnt = Quad_2_Cnt8_ReadCounter();
        #else /* (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_16_BIT) */
            tmpCnt = Quad_2_Cnt16_ReadCounter();
        #endif  /* Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT */

        count = (int16) ((int32) tmpCnt -
                (int32) Quad_2_COUNTER_INIT_VALUE);

    #endif /* Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT */ 

    return (count);
}


/*******************************************************************************
* Function Name: Quad_2_SetCounter
********************************************************************************
*
* Summary:
*  Sets the current value of the counter.
*
* Parameters:
*  value:  The new value. Parameter type is signed and per the counter size
*  setting.
*
* Return:
*  None.
*
* Global variables:
*  Quad_2_count32SoftPart - modified to set hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Quad_2_SetCounter(int16 value) 
{
    #if ((Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT) || \
         (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_16_BIT))
        uint16 count;
        
        if (value >= 0)
        {
            count = (uint16) value + Quad_2_COUNTER_INIT_VALUE;
        }
        else
        {
            count = Quad_2_COUNTER_INIT_VALUE - (uint16)(-value);
        }
        #if (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT)
            Quad_2_Cnt8_WriteCounter(count);
        #else /* (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_16_BIT) */
            Quad_2_Cnt16_WriteCounter(count);
        #endif  /* Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT */
    #else /* (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT) */
        CyIntDisable(Quad_2_ISR_NUMBER);

        Quad_2_Cnt16_WriteCounter(Quad_2_COUNTER_INIT_VALUE);
        Quad_2_count32SoftPart = value;

        CyIntEnable(Quad_2_ISR_NUMBER);
    #endif  /* (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_8_BIT) ||
             * (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_16_BIT)
             */
}


/*******************************************************************************
* Function Name: Quad_2_GetEvents
********************************************************************************
* 
* Summary:
*   Reports the current status of events. This function clears the bits of the 
*   status register.
*
* Parameters:
*  None.
*
* Return:
*  The events, as bits in an unsigned 8-bit value:
*    Bit      Description
*     0        Counter overflow.
*     1        Counter underflow.
*     2        Counter reset due to index, if index input is used.
*     3        Invalid A, B inputs state transition.
*
*******************************************************************************/
uint8 Quad_2_GetEvents(void) 
{
    return (Quad_2_STATUS_REG & Quad_2_INIT_INT_MASK);
}


/*******************************************************************************
* Function Name: Quad_2_SetInterruptMask
********************************************************************************
*
* Summary:
*  Enables / disables interrupts due to the events.
*  For the 32-bit counter, the overflow, underflow and reset interrupts cannot
*  be disabled, these bits are ignored.
*
* Parameters:
*  mask: Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*
* Return:
*  None.
*
*******************************************************************************/
void Quad_2_SetInterruptMask(uint8 mask) 
{
    #if (Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT)
        /* Underflow, Overflow and Reset interrupts for 32-bit Counter are always enable */
        mask |= (Quad_2_COUNTER_OVERFLOW | Quad_2_COUNTER_UNDERFLOW |
                 Quad_2_COUNTER_RESET);
    #endif /* Quad_2_COUNTER_SIZE == Quad_2_COUNTER_SIZE_32_BIT */

    Quad_2_STATUS_MASK = mask;
}


/*******************************************************************************
* Function Name: Quad_2_GetInterruptMask
********************************************************************************
*
* Summary:
*  Reports the current interrupt mask settings.
*
* Parameters:
*  None.
*
* Return:
*  Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*  For the 32-bit counter, the overflow, underflow and reset enable bits are
*  always set.
*
*******************************************************************************/
uint8 Quad_2_GetInterruptMask(void) 
{
    return (Quad_2_STATUS_MASK & Quad_2_INIT_INT_MASK);
}


/* [] END OF FILE */
