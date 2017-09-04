/*******************************************************************************
* File Name: SELiftA.h  
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

#if !defined(CY_PINS_SELiftA_H) /* Pins SELiftA_H */
#define CY_PINS_SELiftA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SELiftA_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SELiftA__PORT == 15 && ((SELiftA__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SELiftA_Write(uint8 value);
void    SELiftA_SetDriveMode(uint8 mode);
uint8   SELiftA_ReadDataReg(void);
uint8   SELiftA_Read(void);
void    SELiftA_SetInterruptMode(uint16 position, uint16 mode);
uint8   SELiftA_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SELiftA_SetDriveMode() function.
     *  @{
     */
        #define SELiftA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SELiftA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SELiftA_DM_RES_UP          PIN_DM_RES_UP
        #define SELiftA_DM_RES_DWN         PIN_DM_RES_DWN
        #define SELiftA_DM_OD_LO           PIN_DM_OD_LO
        #define SELiftA_DM_OD_HI           PIN_DM_OD_HI
        #define SELiftA_DM_STRONG          PIN_DM_STRONG
        #define SELiftA_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SELiftA_MASK               SELiftA__MASK
#define SELiftA_SHIFT              SELiftA__SHIFT
#define SELiftA_WIDTH              1u

/* Interrupt constants */
#if defined(SELiftA__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SELiftA_SetInterruptMode() function.
     *  @{
     */
        #define SELiftA_INTR_NONE      (uint16)(0x0000u)
        #define SELiftA_INTR_RISING    (uint16)(0x0001u)
        #define SELiftA_INTR_FALLING   (uint16)(0x0002u)
        #define SELiftA_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SELiftA_INTR_MASK      (0x01u) 
#endif /* (SELiftA__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SELiftA_PS                     (* (reg8 *) SELiftA__PS)
/* Data Register */
#define SELiftA_DR                     (* (reg8 *) SELiftA__DR)
/* Port Number */
#define SELiftA_PRT_NUM                (* (reg8 *) SELiftA__PRT) 
/* Connect to Analog Globals */                                                  
#define SELiftA_AG                     (* (reg8 *) SELiftA__AG)                       
/* Analog MUX bux enable */
#define SELiftA_AMUX                   (* (reg8 *) SELiftA__AMUX) 
/* Bidirectional Enable */                                                        
#define SELiftA_BIE                    (* (reg8 *) SELiftA__BIE)
/* Bit-mask for Aliased Register Access */
#define SELiftA_BIT_MASK               (* (reg8 *) SELiftA__BIT_MASK)
/* Bypass Enable */
#define SELiftA_BYP                    (* (reg8 *) SELiftA__BYP)
/* Port wide control signals */                                                   
#define SELiftA_CTL                    (* (reg8 *) SELiftA__CTL)
/* Drive Modes */
#define SELiftA_DM0                    (* (reg8 *) SELiftA__DM0) 
#define SELiftA_DM1                    (* (reg8 *) SELiftA__DM1)
#define SELiftA_DM2                    (* (reg8 *) SELiftA__DM2) 
/* Input Buffer Disable Override */
#define SELiftA_INP_DIS                (* (reg8 *) SELiftA__INP_DIS)
/* LCD Common or Segment Drive */
#define SELiftA_LCD_COM_SEG            (* (reg8 *) SELiftA__LCD_COM_SEG)
/* Enable Segment LCD */
#define SELiftA_LCD_EN                 (* (reg8 *) SELiftA__LCD_EN)
/* Slew Rate Control */
#define SELiftA_SLW                    (* (reg8 *) SELiftA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SELiftA_PRTDSI__CAPS_SEL       (* (reg8 *) SELiftA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SELiftA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SELiftA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SELiftA_PRTDSI__OE_SEL0        (* (reg8 *) SELiftA__PRTDSI__OE_SEL0) 
#define SELiftA_PRTDSI__OE_SEL1        (* (reg8 *) SELiftA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SELiftA_PRTDSI__OUT_SEL0       (* (reg8 *) SELiftA__PRTDSI__OUT_SEL0) 
#define SELiftA_PRTDSI__OUT_SEL1       (* (reg8 *) SELiftA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SELiftA_PRTDSI__SYNC_OUT       (* (reg8 *) SELiftA__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SELiftA__SIO_CFG)
    #define SELiftA_SIO_HYST_EN        (* (reg8 *) SELiftA__SIO_HYST_EN)
    #define SELiftA_SIO_REG_HIFREQ     (* (reg8 *) SELiftA__SIO_REG_HIFREQ)
    #define SELiftA_SIO_CFG            (* (reg8 *) SELiftA__SIO_CFG)
    #define SELiftA_SIO_DIFF           (* (reg8 *) SELiftA__SIO_DIFF)
#endif /* (SELiftA__SIO_CFG) */

/* Interrupt Registers */
#if defined(SELiftA__INTSTAT)
    #define SELiftA_INTSTAT            (* (reg8 *) SELiftA__INTSTAT)
    #define SELiftA_SNAP               (* (reg8 *) SELiftA__SNAP)
    
	#define SELiftA_0_INTTYPE_REG 		(* (reg8 *) SELiftA__0__INTTYPE)
#endif /* (SELiftA__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SELiftA_H */


/* [] END OF FILE */
