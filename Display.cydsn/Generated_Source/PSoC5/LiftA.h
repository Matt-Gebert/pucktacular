/*******************************************************************************
* File Name: LiftA.h  
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

#if !defined(CY_PINS_LiftA_H) /* Pins LiftA_H */
#define CY_PINS_LiftA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LiftA_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LiftA__PORT == 15 && ((LiftA__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LiftA_Write(uint8 value);
void    LiftA_SetDriveMode(uint8 mode);
uint8   LiftA_ReadDataReg(void);
uint8   LiftA_Read(void);
void    LiftA_SetInterruptMode(uint16 position, uint16 mode);
uint8   LiftA_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LiftA_SetDriveMode() function.
     *  @{
     */
        #define LiftA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LiftA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LiftA_DM_RES_UP          PIN_DM_RES_UP
        #define LiftA_DM_RES_DWN         PIN_DM_RES_DWN
        #define LiftA_DM_OD_LO           PIN_DM_OD_LO
        #define LiftA_DM_OD_HI           PIN_DM_OD_HI
        #define LiftA_DM_STRONG          PIN_DM_STRONG
        #define LiftA_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LiftA_MASK               LiftA__MASK
#define LiftA_SHIFT              LiftA__SHIFT
#define LiftA_WIDTH              1u

/* Interrupt constants */
#if defined(LiftA__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LiftA_SetInterruptMode() function.
     *  @{
     */
        #define LiftA_INTR_NONE      (uint16)(0x0000u)
        #define LiftA_INTR_RISING    (uint16)(0x0001u)
        #define LiftA_INTR_FALLING   (uint16)(0x0002u)
        #define LiftA_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LiftA_INTR_MASK      (0x01u) 
#endif /* (LiftA__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LiftA_PS                     (* (reg8 *) LiftA__PS)
/* Data Register */
#define LiftA_DR                     (* (reg8 *) LiftA__DR)
/* Port Number */
#define LiftA_PRT_NUM                (* (reg8 *) LiftA__PRT) 
/* Connect to Analog Globals */                                                  
#define LiftA_AG                     (* (reg8 *) LiftA__AG)                       
/* Analog MUX bux enable */
#define LiftA_AMUX                   (* (reg8 *) LiftA__AMUX) 
/* Bidirectional Enable */                                                        
#define LiftA_BIE                    (* (reg8 *) LiftA__BIE)
/* Bit-mask for Aliased Register Access */
#define LiftA_BIT_MASK               (* (reg8 *) LiftA__BIT_MASK)
/* Bypass Enable */
#define LiftA_BYP                    (* (reg8 *) LiftA__BYP)
/* Port wide control signals */                                                   
#define LiftA_CTL                    (* (reg8 *) LiftA__CTL)
/* Drive Modes */
#define LiftA_DM0                    (* (reg8 *) LiftA__DM0) 
#define LiftA_DM1                    (* (reg8 *) LiftA__DM1)
#define LiftA_DM2                    (* (reg8 *) LiftA__DM2) 
/* Input Buffer Disable Override */
#define LiftA_INP_DIS                (* (reg8 *) LiftA__INP_DIS)
/* LCD Common or Segment Drive */
#define LiftA_LCD_COM_SEG            (* (reg8 *) LiftA__LCD_COM_SEG)
/* Enable Segment LCD */
#define LiftA_LCD_EN                 (* (reg8 *) LiftA__LCD_EN)
/* Slew Rate Control */
#define LiftA_SLW                    (* (reg8 *) LiftA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LiftA_PRTDSI__CAPS_SEL       (* (reg8 *) LiftA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LiftA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LiftA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LiftA_PRTDSI__OE_SEL0        (* (reg8 *) LiftA__PRTDSI__OE_SEL0) 
#define LiftA_PRTDSI__OE_SEL1        (* (reg8 *) LiftA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LiftA_PRTDSI__OUT_SEL0       (* (reg8 *) LiftA__PRTDSI__OUT_SEL0) 
#define LiftA_PRTDSI__OUT_SEL1       (* (reg8 *) LiftA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LiftA_PRTDSI__SYNC_OUT       (* (reg8 *) LiftA__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LiftA__SIO_CFG)
    #define LiftA_SIO_HYST_EN        (* (reg8 *) LiftA__SIO_HYST_EN)
    #define LiftA_SIO_REG_HIFREQ     (* (reg8 *) LiftA__SIO_REG_HIFREQ)
    #define LiftA_SIO_CFG            (* (reg8 *) LiftA__SIO_CFG)
    #define LiftA_SIO_DIFF           (* (reg8 *) LiftA__SIO_DIFF)
#endif /* (LiftA__SIO_CFG) */

/* Interrupt Registers */
#if defined(LiftA__INTSTAT)
    #define LiftA_INTSTAT            (* (reg8 *) LiftA__INTSTAT)
    #define LiftA_SNAP               (* (reg8 *) LiftA__SNAP)
    
	#define LiftA_0_INTTYPE_REG 		(* (reg8 *) LiftA__0__INTTYPE)
#endif /* (LiftA__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LiftA_H */


/* [] END OF FILE */
