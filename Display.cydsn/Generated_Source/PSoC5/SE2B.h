/*******************************************************************************
* File Name: SE2B.h  
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

#if !defined(CY_PINS_SE2B_H) /* Pins SE2B_H */
#define CY_PINS_SE2B_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SE2B_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SE2B__PORT == 15 && ((SE2B__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SE2B_Write(uint8 value);
void    SE2B_SetDriveMode(uint8 mode);
uint8   SE2B_ReadDataReg(void);
uint8   SE2B_Read(void);
void    SE2B_SetInterruptMode(uint16 position, uint16 mode);
uint8   SE2B_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SE2B_SetDriveMode() function.
     *  @{
     */
        #define SE2B_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SE2B_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SE2B_DM_RES_UP          PIN_DM_RES_UP
        #define SE2B_DM_RES_DWN         PIN_DM_RES_DWN
        #define SE2B_DM_OD_LO           PIN_DM_OD_LO
        #define SE2B_DM_OD_HI           PIN_DM_OD_HI
        #define SE2B_DM_STRONG          PIN_DM_STRONG
        #define SE2B_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SE2B_MASK               SE2B__MASK
#define SE2B_SHIFT              SE2B__SHIFT
#define SE2B_WIDTH              1u

/* Interrupt constants */
#if defined(SE2B__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SE2B_SetInterruptMode() function.
     *  @{
     */
        #define SE2B_INTR_NONE      (uint16)(0x0000u)
        #define SE2B_INTR_RISING    (uint16)(0x0001u)
        #define SE2B_INTR_FALLING   (uint16)(0x0002u)
        #define SE2B_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SE2B_INTR_MASK      (0x01u) 
#endif /* (SE2B__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SE2B_PS                     (* (reg8 *) SE2B__PS)
/* Data Register */
#define SE2B_DR                     (* (reg8 *) SE2B__DR)
/* Port Number */
#define SE2B_PRT_NUM                (* (reg8 *) SE2B__PRT) 
/* Connect to Analog Globals */                                                  
#define SE2B_AG                     (* (reg8 *) SE2B__AG)                       
/* Analog MUX bux enable */
#define SE2B_AMUX                   (* (reg8 *) SE2B__AMUX) 
/* Bidirectional Enable */                                                        
#define SE2B_BIE                    (* (reg8 *) SE2B__BIE)
/* Bit-mask for Aliased Register Access */
#define SE2B_BIT_MASK               (* (reg8 *) SE2B__BIT_MASK)
/* Bypass Enable */
#define SE2B_BYP                    (* (reg8 *) SE2B__BYP)
/* Port wide control signals */                                                   
#define SE2B_CTL                    (* (reg8 *) SE2B__CTL)
/* Drive Modes */
#define SE2B_DM0                    (* (reg8 *) SE2B__DM0) 
#define SE2B_DM1                    (* (reg8 *) SE2B__DM1)
#define SE2B_DM2                    (* (reg8 *) SE2B__DM2) 
/* Input Buffer Disable Override */
#define SE2B_INP_DIS                (* (reg8 *) SE2B__INP_DIS)
/* LCD Common or Segment Drive */
#define SE2B_LCD_COM_SEG            (* (reg8 *) SE2B__LCD_COM_SEG)
/* Enable Segment LCD */
#define SE2B_LCD_EN                 (* (reg8 *) SE2B__LCD_EN)
/* Slew Rate Control */
#define SE2B_SLW                    (* (reg8 *) SE2B__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SE2B_PRTDSI__CAPS_SEL       (* (reg8 *) SE2B__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SE2B_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SE2B__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SE2B_PRTDSI__OE_SEL0        (* (reg8 *) SE2B__PRTDSI__OE_SEL0) 
#define SE2B_PRTDSI__OE_SEL1        (* (reg8 *) SE2B__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SE2B_PRTDSI__OUT_SEL0       (* (reg8 *) SE2B__PRTDSI__OUT_SEL0) 
#define SE2B_PRTDSI__OUT_SEL1       (* (reg8 *) SE2B__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SE2B_PRTDSI__SYNC_OUT       (* (reg8 *) SE2B__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SE2B__SIO_CFG)
    #define SE2B_SIO_HYST_EN        (* (reg8 *) SE2B__SIO_HYST_EN)
    #define SE2B_SIO_REG_HIFREQ     (* (reg8 *) SE2B__SIO_REG_HIFREQ)
    #define SE2B_SIO_CFG            (* (reg8 *) SE2B__SIO_CFG)
    #define SE2B_SIO_DIFF           (* (reg8 *) SE2B__SIO_DIFF)
#endif /* (SE2B__SIO_CFG) */

/* Interrupt Registers */
#if defined(SE2B__INTSTAT)
    #define SE2B_INTSTAT            (* (reg8 *) SE2B__INTSTAT)
    #define SE2B_SNAP               (* (reg8 *) SE2B__SNAP)
    
	#define SE2B_0_INTTYPE_REG 		(* (reg8 *) SE2B__0__INTTYPE)
#endif /* (SE2B__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SE2B_H */


/* [] END OF FILE */
