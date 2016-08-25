/*******************************************************************************
* File Name: osc.h  
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

#if !defined(CY_PINS_osc_H) /* Pins osc_H */
#define CY_PINS_osc_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "osc_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 osc__PORT == 15 && ((osc__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    osc_Write(uint8 value);
void    osc_SetDriveMode(uint8 mode);
uint8   osc_ReadDataReg(void);
uint8   osc_Read(void);
void    osc_SetInterruptMode(uint16 position, uint16 mode);
uint8   osc_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the osc_SetDriveMode() function.
     *  @{
     */
        #define osc_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define osc_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define osc_DM_RES_UP          PIN_DM_RES_UP
        #define osc_DM_RES_DWN         PIN_DM_RES_DWN
        #define osc_DM_OD_LO           PIN_DM_OD_LO
        #define osc_DM_OD_HI           PIN_DM_OD_HI
        #define osc_DM_STRONG          PIN_DM_STRONG
        #define osc_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define osc_MASK               osc__MASK
#define osc_SHIFT              osc__SHIFT
#define osc_WIDTH              1u

/* Interrupt constants */
#if defined(osc__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in osc_SetInterruptMode() function.
     *  @{
     */
        #define osc_INTR_NONE      (uint16)(0x0000u)
        #define osc_INTR_RISING    (uint16)(0x0001u)
        #define osc_INTR_FALLING   (uint16)(0x0002u)
        #define osc_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define osc_INTR_MASK      (0x01u) 
#endif /* (osc__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define osc_PS                     (* (reg8 *) osc__PS)
/* Data Register */
#define osc_DR                     (* (reg8 *) osc__DR)
/* Port Number */
#define osc_PRT_NUM                (* (reg8 *) osc__PRT) 
/* Connect to Analog Globals */                                                  
#define osc_AG                     (* (reg8 *) osc__AG)                       
/* Analog MUX bux enable */
#define osc_AMUX                   (* (reg8 *) osc__AMUX) 
/* Bidirectional Enable */                                                        
#define osc_BIE                    (* (reg8 *) osc__BIE)
/* Bit-mask for Aliased Register Access */
#define osc_BIT_MASK               (* (reg8 *) osc__BIT_MASK)
/* Bypass Enable */
#define osc_BYP                    (* (reg8 *) osc__BYP)
/* Port wide control signals */                                                   
#define osc_CTL                    (* (reg8 *) osc__CTL)
/* Drive Modes */
#define osc_DM0                    (* (reg8 *) osc__DM0) 
#define osc_DM1                    (* (reg8 *) osc__DM1)
#define osc_DM2                    (* (reg8 *) osc__DM2) 
/* Input Buffer Disable Override */
#define osc_INP_DIS                (* (reg8 *) osc__INP_DIS)
/* LCD Common or Segment Drive */
#define osc_LCD_COM_SEG            (* (reg8 *) osc__LCD_COM_SEG)
/* Enable Segment LCD */
#define osc_LCD_EN                 (* (reg8 *) osc__LCD_EN)
/* Slew Rate Control */
#define osc_SLW                    (* (reg8 *) osc__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define osc_PRTDSI__CAPS_SEL       (* (reg8 *) osc__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define osc_PRTDSI__DBL_SYNC_IN    (* (reg8 *) osc__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define osc_PRTDSI__OE_SEL0        (* (reg8 *) osc__PRTDSI__OE_SEL0) 
#define osc_PRTDSI__OE_SEL1        (* (reg8 *) osc__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define osc_PRTDSI__OUT_SEL0       (* (reg8 *) osc__PRTDSI__OUT_SEL0) 
#define osc_PRTDSI__OUT_SEL1       (* (reg8 *) osc__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define osc_PRTDSI__SYNC_OUT       (* (reg8 *) osc__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(osc__SIO_CFG)
    #define osc_SIO_HYST_EN        (* (reg8 *) osc__SIO_HYST_EN)
    #define osc_SIO_REG_HIFREQ     (* (reg8 *) osc__SIO_REG_HIFREQ)
    #define osc_SIO_CFG            (* (reg8 *) osc__SIO_CFG)
    #define osc_SIO_DIFF           (* (reg8 *) osc__SIO_DIFF)
#endif /* (osc__SIO_CFG) */

/* Interrupt Registers */
#if defined(osc__INTSTAT)
    #define osc_INTSTAT            (* (reg8 *) osc__INTSTAT)
    #define osc_SNAP               (* (reg8 *) osc__SNAP)
    
	#define osc_0_INTTYPE_REG 		(* (reg8 *) osc__0__INTTYPE)
#endif /* (osc__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_osc_H */


/* [] END OF FILE */
