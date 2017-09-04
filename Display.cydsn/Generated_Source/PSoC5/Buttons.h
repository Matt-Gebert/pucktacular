/*******************************************************************************
* File Name: Buttons.h  
* Version 1.90
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_Buttons_H) /* CY_STATUS_REG_Buttons_H */
#define CY_STATUS_REG_Buttons_H

#include "cytypes.h"
#include "CyLib.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} Buttons_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 Buttons_Read(void) ;
void Buttons_InterruptEnable(void) ;
void Buttons_InterruptDisable(void) ;
void Buttons_WriteMask(uint8 mask) ;
uint8 Buttons_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define Buttons_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define Buttons_INPUTS              3


/***************************************
*             Registers
***************************************/

/* Status Register */
#define Buttons_Status             (* (reg8 *) Buttons_sts_sts_reg__STATUS_REG )
#define Buttons_Status_PTR         (  (reg8 *) Buttons_sts_sts_reg__STATUS_REG )
#define Buttons_Status_Mask        (* (reg8 *) Buttons_sts_sts_reg__MASK_REG )
#define Buttons_Status_Aux_Ctrl    (* (reg8 *) Buttons_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_Buttons_H */


/* [] END OF FILE */
