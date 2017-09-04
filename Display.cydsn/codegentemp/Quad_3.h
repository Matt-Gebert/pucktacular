/*******************************************************************************
* File Name: Quad_3.h  
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the Quadrature
*  Decoder component.
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

#if !defined(CY_QUADRATURE_DECODER_Quad_3_H)
#define CY_QUADRATURE_DECODER_Quad_3_H

#include "cyfitter.h"
#include "CyLib.h"
#include "cytypes.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component QuadDec_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#define Quad_3_COUNTER_SIZE               (16u)
#define Quad_3_COUNTER_SIZE_8_BIT         (8u)
#define Quad_3_COUNTER_SIZE_16_BIT        (16u)
#define Quad_3_COUNTER_SIZE_32_BIT        (32u)

#if (Quad_3_COUNTER_SIZE == Quad_3_COUNTER_SIZE_8_BIT)
    #include "Quad_3_Cnt8.h"
#else 
    /* (Quad_3_COUNTER_SIZE == Quad_3_COUNTER_SIZE_16_BIT) || 
    *  (Quad_3_COUNTER_SIZE == Quad_3_COUNTER_SIZE_32_BIT) 
    */
    #include "Quad_3_Cnt16.h"
#endif /* Quad_3_COUNTER_SIZE == Quad_3_COUNTER_SIZE_8_BIT */

extern uint8 Quad_3_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Quad_3_COUNTER_RESOLUTION         (1u)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} Quad_3_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  Quad_3_Init(void) ;
void  Quad_3_Start(void) ;
void  Quad_3_Stop(void) ;
void  Quad_3_Enable(void) ;
uint8 Quad_3_GetEvents(void) ;
void  Quad_3_SetInterruptMask(uint8 mask) ;
uint8 Quad_3_GetInterruptMask(void) ;
int16 Quad_3_GetCounter(void) ;
void  Quad_3_SetCounter(int16 value)
;
void  Quad_3_Sleep(void) ;
void  Quad_3_Wakeup(void) ;
void  Quad_3_SaveConfig(void) ;
void  Quad_3_RestoreConfig(void) ;

#if (Quad_3_COUNTER_SIZE == Quad_3_COUNTER_SIZE_32_BIT)
    CY_ISR_PROTO(Quad_3_ISR);
#endif /* Quad_3_COUNTER_SIZE == Quad_3_COUNTER_SIZE_32_BIT */


/***************************************
*           API Constants
***************************************/

#if (Quad_3_COUNTER_SIZE == Quad_3_COUNTER_SIZE_32_BIT)
    #define Quad_3_ISR_NUMBER             ((uint8) Quad_3_isr__INTC_NUMBER)
    #define Quad_3_ISR_PRIORITY           ((uint8) Quad_3_isr__INTC_PRIOR_NUM)
#endif /* Quad_3_COUNTER_SIZE == Quad_3_COUNTER_SIZE_32_BIT */


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Quad_3_GLITCH_FILTERING           (1u)
#define Quad_3_INDEX_INPUT                (0u)


/***************************************
*    Initial Parameter Constants
***************************************/

#if (Quad_3_COUNTER_SIZE == Quad_3_COUNTER_SIZE_8_BIT)
    #define Quad_3_COUNTER_INIT_VALUE    (0x80u)
#else 
    /* (Quad_3_COUNTER_SIZE == Quad_3_COUNTER_SIZE_16_BIT) ||
    *  (Quad_3_COUNTER_SIZE == Quad_3_COUNTER_SIZE_32_BIT)
    */
    #define Quad_3_COUNTER_INIT_VALUE    (0x8000u)
    #define Quad_3_COUNTER_MAX_VALUE     (0x7FFFu)
#endif /* Quad_3_COUNTER_SIZE == Quad_3_COUNTER_SIZE_8_BIT */


/***************************************
*             Registers
***************************************/

#define Quad_3_STATUS_REG                 (* (reg8 *) Quad_3_bQuadDec_Stsreg__STATUS_REG)
#define Quad_3_STATUS_PTR                 (  (reg8 *) Quad_3_bQuadDec_Stsreg__STATUS_REG)
#define Quad_3_STATUS_MASK                (* (reg8 *) Quad_3_bQuadDec_Stsreg__MASK_REG)
#define Quad_3_STATUS_MASK_PTR            (  (reg8 *) Quad_3_bQuadDec_Stsreg__MASK_REG)
#define Quad_3_SR_AUX_CONTROL             (* (reg8 *) Quad_3_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)
#define Quad_3_SR_AUX_CONTROL_PTR         (  (reg8 *) Quad_3_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)


/***************************************
*        Register Constants
***************************************/

#define Quad_3_COUNTER_OVERFLOW_SHIFT     (0x00u)
#define Quad_3_COUNTER_UNDERFLOW_SHIFT    (0x01u)
#define Quad_3_COUNTER_RESET_SHIFT        (0x02u)
#define Quad_3_INVALID_IN_SHIFT           (0x03u)
#define Quad_3_COUNTER_OVERFLOW           ((uint8) (0x01u << Quad_3_COUNTER_OVERFLOW_SHIFT))
#define Quad_3_COUNTER_UNDERFLOW          ((uint8) (0x01u << Quad_3_COUNTER_UNDERFLOW_SHIFT))
#define Quad_3_COUNTER_RESET              ((uint8) (0x01u << Quad_3_COUNTER_RESET_SHIFT))
#define Quad_3_INVALID_IN                 ((uint8) (0x01u << Quad_3_INVALID_IN_SHIFT))

#define Quad_3_INTERRUPTS_ENABLE_SHIFT    (0x04u)
#define Quad_3_INTERRUPTS_ENABLE          ((uint8)(0x01u << Quad_3_INTERRUPTS_ENABLE_SHIFT))
#define Quad_3_INIT_INT_MASK              (0x0Fu)


/******************************************************************************************
* Following code are OBSOLETE and must not be used starting from Quadrature Decoder 2.20
******************************************************************************************/
#define Quad_3_DISABLE                    (0x00u)


#endif /* CY_QUADRATURE_DECODER_Quad_3_H */


/* [] END OF FILE */
