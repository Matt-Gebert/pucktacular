/*******************************************************************************
* File Name: SELiftB.h  
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

#if !defined(CY_PINS_SELiftB_H) /* Pins SELiftB_H */
#define CY_PINS_SELiftB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SELiftB_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SELiftB__PORT == 15 && ((SELiftB__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SELiftB_Write(uint8 value);
void    SELiftB_SetDriveMode(uint8 mode);
uint8   SELiftB_ReadDataReg(void);
uint8   SELiftB_Read(void);
void    SELiftB_SetInterruptMode(uint16 position, uint16 mode);
uint8   SELiftB_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SELiftB_SetDriveMode() function.
     *  @{
     */
        #define SELiftB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SELiftB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SELiftB_DM_RES_UP          PIN_DM_RES_UP
        #define SELiftB_DM_RES_DWN         PIN_DM_RES_DWN
        #define SELiftB_DM_OD_LO           PIN_DM_OD_LO
        #define SELiftB_DM_OD_HI           PIN_DM_OD_HI
        #define SELiftB_DM_STRONG          PIN_DM_STRONG
        #define SELiftB_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SELiftB_MASK               SELiftB__MASK
#define SELiftB_SHIFT              SELiftB__SHIFT
#define SELiftB_WIDTH              1u

/* Interrupt constants */
#if defined(SELiftB__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SELiftB_SetInterruptMode() function.
     *  @{
     */
        #define SELiftB_INTR_NONE      (uint16)(0x0000u)
        #define SELiftB_INTR_RISING    (uint16)(0x0001u)
        #define SELiftB_INTR_FALLING   (uint16)(0x0002u)
        #define SELiftB_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SELiftB_INTR_MASK      (0x01u) 
#endif /* (SELiftB__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SELiftB_PS                     (* (reg8 *) SELiftB__PS)
/* Data Register */
#define SELiftB_DR                     (* (reg8 *) SELiftB__DR)
/* Port Number */
#define SELiftB_PRT_NUM                (* (reg8 *) SELiftB__PRT) 
/* Connect to Analog Globals */                                                  
#define SELiftB_AG                     (* (reg8 *) SELiftB__AG)                       
/* Analog MUX bux enable */
#define SELiftB_AMUX                   (* (reg8 *) SELiftB__AMUX) 
/* Bidirectional Enable */                                                        
#define SELiftB_BIE                    (* (reg8 *) SELiftB__BIE)
/* Bit-mask for Aliased Register Access */
#define SELiftB_BIT_MASK               (* (reg8 *) SELiftB__BIT_MASK)
/* Bypass Enable */
#define SELiftB_BYP                    (* (reg8 *) SELiftB__BYP)
/* Port wide control signals */                                                   
#define SELiftB_CTL                    (* (reg8 *) SELiftB__CTL)
/* Drive Modes */
#define SELiftB_DM0                    (* (reg8 *) SELiftB__DM0) 
#define SELiftB_DM1                    (* (reg8 *) SELiftB__DM1)
#define SELiftB_DM2                    (* (reg8 *) SELiftB__DM2) 
/* Input Buffer Disable Override */
#define SELiftB_INP_DIS                (* (reg8 *) SELiftB__INP_DIS)
/* LCD Common or Segment Drive */
#define SELiftB_LCD_COM_SEG            (* (reg8 *) SELiftB__LCD_COM_SEG)
/* Enable Segment LCD */
#define SELiftB_LCD_EN                 (* (reg8 *) SELiftB__LCD_EN)
/* Slew Rate Control */
#define SELiftB_SLW                    (* (reg8 *) SELiftB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SELiftB_PRTDSI__CAPS_SEL       (* (reg8 *) SELiftB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SELiftB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SELiftB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SELiftB_PRTDSI__OE_SEL0        (* (reg8 *) SELiftB__PRTDSI__OE_SEL0) 
#define SELiftB_PRTDSI__OE_SEL1        (* (reg8 *) SELiftB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SELiftB_PRTDSI__OUT_SEL0       (* (reg8 *) SELiftB__PRTDSI__OUT_SEL0) 
#define SELiftB_PRTDSI__OUT_SEL1       (* (reg8 *) SELiftB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SELiftB_PRTDSI__SYNC_OUT       (* (reg8 *) SELiftB__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SELiftB__SIO_CFG)
    #define SELiftB_SIO_HYST_EN        (* (reg8 *) SELiftB__SIO_HYST_EN)
    #define SELiftB_SIO_REG_HIFREQ     (* (reg8 *) SELiftB__SIO_REG_HIFREQ)
    #define SELiftB_SIO_CFG            (* (reg8 *) SELiftB__SIO_CFG)
    #define SELiftB_SIO_DIFF           (* (reg8 *) SELiftB__SIO_DIFF)
#endif /* (SELiftB__SIO_CFG) */

/* Interrupt Registers */
#if defined(SELiftB__INTSTAT)
    #define SELiftB_INTSTAT            (* (reg8 *) SELiftB__INTSTAT)
    #define SELiftB_SNAP               (* (reg8 *) SELiftB__SNAP)
    
	#define SELiftB_0_INTTYPE_REG 		(* (reg8 *) SELiftB__0__INTTYPE)
#endif /* (SELiftB__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SELiftB_H */


/* [] END OF FILE */
