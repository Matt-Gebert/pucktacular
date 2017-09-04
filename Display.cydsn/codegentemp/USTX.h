/*******************************************************************************
* File Name: USTX.h  
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

#if !defined(CY_PINS_USTX_H) /* Pins USTX_H */
#define CY_PINS_USTX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "USTX_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 USTX__PORT == 15 && ((USTX__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    USTX_Write(uint8 value);
void    USTX_SetDriveMode(uint8 mode);
uint8   USTX_ReadDataReg(void);
uint8   USTX_Read(void);
void    USTX_SetInterruptMode(uint16 position, uint16 mode);
uint8   USTX_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the USTX_SetDriveMode() function.
     *  @{
     */
        #define USTX_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define USTX_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define USTX_DM_RES_UP          PIN_DM_RES_UP
        #define USTX_DM_RES_DWN         PIN_DM_RES_DWN
        #define USTX_DM_OD_LO           PIN_DM_OD_LO
        #define USTX_DM_OD_HI           PIN_DM_OD_HI
        #define USTX_DM_STRONG          PIN_DM_STRONG
        #define USTX_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define USTX_MASK               USTX__MASK
#define USTX_SHIFT              USTX__SHIFT
#define USTX_WIDTH              1u

/* Interrupt constants */
#if defined(USTX__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in USTX_SetInterruptMode() function.
     *  @{
     */
        #define USTX_INTR_NONE      (uint16)(0x0000u)
        #define USTX_INTR_RISING    (uint16)(0x0001u)
        #define USTX_INTR_FALLING   (uint16)(0x0002u)
        #define USTX_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define USTX_INTR_MASK      (0x01u) 
#endif /* (USTX__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define USTX_PS                     (* (reg8 *) USTX__PS)
/* Data Register */
#define USTX_DR                     (* (reg8 *) USTX__DR)
/* Port Number */
#define USTX_PRT_NUM                (* (reg8 *) USTX__PRT) 
/* Connect to Analog Globals */                                                  
#define USTX_AG                     (* (reg8 *) USTX__AG)                       
/* Analog MUX bux enable */
#define USTX_AMUX                   (* (reg8 *) USTX__AMUX) 
/* Bidirectional Enable */                                                        
#define USTX_BIE                    (* (reg8 *) USTX__BIE)
/* Bit-mask for Aliased Register Access */
#define USTX_BIT_MASK               (* (reg8 *) USTX__BIT_MASK)
/* Bypass Enable */
#define USTX_BYP                    (* (reg8 *) USTX__BYP)
/* Port wide control signals */                                                   
#define USTX_CTL                    (* (reg8 *) USTX__CTL)
/* Drive Modes */
#define USTX_DM0                    (* (reg8 *) USTX__DM0) 
#define USTX_DM1                    (* (reg8 *) USTX__DM1)
#define USTX_DM2                    (* (reg8 *) USTX__DM2) 
/* Input Buffer Disable Override */
#define USTX_INP_DIS                (* (reg8 *) USTX__INP_DIS)
/* LCD Common or Segment Drive */
#define USTX_LCD_COM_SEG            (* (reg8 *) USTX__LCD_COM_SEG)
/* Enable Segment LCD */
#define USTX_LCD_EN                 (* (reg8 *) USTX__LCD_EN)
/* Slew Rate Control */
#define USTX_SLW                    (* (reg8 *) USTX__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define USTX_PRTDSI__CAPS_SEL       (* (reg8 *) USTX__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define USTX_PRTDSI__DBL_SYNC_IN    (* (reg8 *) USTX__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define USTX_PRTDSI__OE_SEL0        (* (reg8 *) USTX__PRTDSI__OE_SEL0) 
#define USTX_PRTDSI__OE_SEL1        (* (reg8 *) USTX__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define USTX_PRTDSI__OUT_SEL0       (* (reg8 *) USTX__PRTDSI__OUT_SEL0) 
#define USTX_PRTDSI__OUT_SEL1       (* (reg8 *) USTX__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define USTX_PRTDSI__SYNC_OUT       (* (reg8 *) USTX__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(USTX__SIO_CFG)
    #define USTX_SIO_HYST_EN        (* (reg8 *) USTX__SIO_HYST_EN)
    #define USTX_SIO_REG_HIFREQ     (* (reg8 *) USTX__SIO_REG_HIFREQ)
    #define USTX_SIO_CFG            (* (reg8 *) USTX__SIO_CFG)
    #define USTX_SIO_DIFF           (* (reg8 *) USTX__SIO_DIFF)
#endif /* (USTX__SIO_CFG) */

/* Interrupt Registers */
#if defined(USTX__INTSTAT)
    #define USTX_INTSTAT            (* (reg8 *) USTX__INTSTAT)
    #define USTX_SNAP               (* (reg8 *) USTX__SNAP)
    
	#define USTX_0_INTTYPE_REG 		(* (reg8 *) USTX__0__INTTYPE)
#endif /* (USTX__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_USTX_H */


/* [] END OF FILE */
