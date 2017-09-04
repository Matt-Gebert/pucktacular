/*******************************************************************************
* File Name: LiftB.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LiftB_H) /* Pins LiftB_H */
#define CY_PINS_LiftB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LiftB_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LiftB__PORT == 15 && ((LiftB__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LiftB_Write(uint8 value);
void    LiftB_SetDriveMode(uint8 mode);
uint8   LiftB_ReadDataReg(void);
uint8   LiftB_Read(void);
void    LiftB_SetInterruptMode(uint16 position, uint16 mode);
uint8   LiftB_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LiftB_SetDriveMode() function.
     *  @{
     */
        #define LiftB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LiftB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LiftB_DM_RES_UP          PIN_DM_RES_UP
        #define LiftB_DM_RES_DWN         PIN_DM_RES_DWN
        #define LiftB_DM_OD_LO           PIN_DM_OD_LO
        #define LiftB_DM_OD_HI           PIN_DM_OD_HI
        #define LiftB_DM_STRONG          PIN_DM_STRONG
        #define LiftB_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LiftB_MASK               LiftB__MASK
#define LiftB_SHIFT              LiftB__SHIFT
#define LiftB_WIDTH              1u

/* Interrupt constants */
#if defined(LiftB__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LiftB_SetInterruptMode() function.
     *  @{
     */
        #define LiftB_INTR_NONE      (uint16)(0x0000u)
        #define LiftB_INTR_RISING    (uint16)(0x0001u)
        #define LiftB_INTR_FALLING   (uint16)(0x0002u)
        #define LiftB_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LiftB_INTR_MASK      (0x01u) 
#endif /* (LiftB__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LiftB_PS                     (* (reg8 *) LiftB__PS)
/* Data Register */
#define LiftB_DR                     (* (reg8 *) LiftB__DR)
/* Port Number */
#define LiftB_PRT_NUM                (* (reg8 *) LiftB__PRT) 
/* Connect to Analog Globals */                                                  
#define LiftB_AG                     (* (reg8 *) LiftB__AG)                       
/* Analog MUX bux enable */
#define LiftB_AMUX                   (* (reg8 *) LiftB__AMUX) 
/* Bidirectional Enable */                                                        
#define LiftB_BIE                    (* (reg8 *) LiftB__BIE)
/* Bit-mask for Aliased Register Access */
#define LiftB_BIT_MASK               (* (reg8 *) LiftB__BIT_MASK)
/* Bypass Enable */
#define LiftB_BYP                    (* (reg8 *) LiftB__BYP)
/* Port wide control signals */                                                   
#define LiftB_CTL                    (* (reg8 *) LiftB__CTL)
/* Drive Modes */
#define LiftB_DM0                    (* (reg8 *) LiftB__DM0) 
#define LiftB_DM1                    (* (reg8 *) LiftB__DM1)
#define LiftB_DM2                    (* (reg8 *) LiftB__DM2) 
/* Input Buffer Disable Override */
#define LiftB_INP_DIS                (* (reg8 *) LiftB__INP_DIS)
/* LCD Common or Segment Drive */
#define LiftB_LCD_COM_SEG            (* (reg8 *) LiftB__LCD_COM_SEG)
/* Enable Segment LCD */
#define LiftB_LCD_EN                 (* (reg8 *) LiftB__LCD_EN)
/* Slew Rate Control */
#define LiftB_SLW                    (* (reg8 *) LiftB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LiftB_PRTDSI__CAPS_SEL       (* (reg8 *) LiftB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LiftB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LiftB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LiftB_PRTDSI__OE_SEL0        (* (reg8 *) LiftB__PRTDSI__OE_SEL0) 
#define LiftB_PRTDSI__OE_SEL1        (* (reg8 *) LiftB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LiftB_PRTDSI__OUT_SEL0       (* (reg8 *) LiftB__PRTDSI__OUT_SEL0) 
#define LiftB_PRTDSI__OUT_SEL1       (* (reg8 *) LiftB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LiftB_PRTDSI__SYNC_OUT       (* (reg8 *) LiftB__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LiftB__SIO_CFG)
    #define LiftB_SIO_HYST_EN        (* (reg8 *) LiftB__SIO_HYST_EN)
    #define LiftB_SIO_REG_HIFREQ     (* (reg8 *) LiftB__SIO_REG_HIFREQ)
    #define LiftB_SIO_CFG            (* (reg8 *) LiftB__SIO_CFG)
    #define LiftB_SIO_DIFF           (* (reg8 *) LiftB__SIO_DIFF)
#endif /* (LiftB__SIO_CFG) */

/* Interrupt Registers */
#if defined(LiftB__INTSTAT)
    #define LiftB_INTSTAT            (* (reg8 *) LiftB__INTSTAT)
    #define LiftB_SNAP               (* (reg8 *) LiftB__SNAP)
    
	#define LiftB_0_INTTYPE_REG 		(* (reg8 *) LiftB__0__INTTYPE)
#endif /* (LiftB__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LiftB_H */


/* [] END OF FILE */
