/*******************************************************************************
* File Name: SE1B.h  
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

#if !defined(CY_PINS_SE1B_H) /* Pins SE1B_H */
#define CY_PINS_SE1B_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SE1B_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SE1B__PORT == 15 && ((SE1B__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SE1B_Write(uint8 value);
void    SE1B_SetDriveMode(uint8 mode);
uint8   SE1B_ReadDataReg(void);
uint8   SE1B_Read(void);
void    SE1B_SetInterruptMode(uint16 position, uint16 mode);
uint8   SE1B_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SE1B_SetDriveMode() function.
     *  @{
     */
        #define SE1B_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SE1B_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SE1B_DM_RES_UP          PIN_DM_RES_UP
        #define SE1B_DM_RES_DWN         PIN_DM_RES_DWN
        #define SE1B_DM_OD_LO           PIN_DM_OD_LO
        #define SE1B_DM_OD_HI           PIN_DM_OD_HI
        #define SE1B_DM_STRONG          PIN_DM_STRONG
        #define SE1B_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SE1B_MASK               SE1B__MASK
#define SE1B_SHIFT              SE1B__SHIFT
#define SE1B_WIDTH              1u

/* Interrupt constants */
#if defined(SE1B__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SE1B_SetInterruptMode() function.
     *  @{
     */
        #define SE1B_INTR_NONE      (uint16)(0x0000u)
        #define SE1B_INTR_RISING    (uint16)(0x0001u)
        #define SE1B_INTR_FALLING   (uint16)(0x0002u)
        #define SE1B_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SE1B_INTR_MASK      (0x01u) 
#endif /* (SE1B__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SE1B_PS                     (* (reg8 *) SE1B__PS)
/* Data Register */
#define SE1B_DR                     (* (reg8 *) SE1B__DR)
/* Port Number */
#define SE1B_PRT_NUM                (* (reg8 *) SE1B__PRT) 
/* Connect to Analog Globals */                                                  
#define SE1B_AG                     (* (reg8 *) SE1B__AG)                       
/* Analog MUX bux enable */
#define SE1B_AMUX                   (* (reg8 *) SE1B__AMUX) 
/* Bidirectional Enable */                                                        
#define SE1B_BIE                    (* (reg8 *) SE1B__BIE)
/* Bit-mask for Aliased Register Access */
#define SE1B_BIT_MASK               (* (reg8 *) SE1B__BIT_MASK)
/* Bypass Enable */
#define SE1B_BYP                    (* (reg8 *) SE1B__BYP)
/* Port wide control signals */                                                   
#define SE1B_CTL                    (* (reg8 *) SE1B__CTL)
/* Drive Modes */
#define SE1B_DM0                    (* (reg8 *) SE1B__DM0) 
#define SE1B_DM1                    (* (reg8 *) SE1B__DM1)
#define SE1B_DM2                    (* (reg8 *) SE1B__DM2) 
/* Input Buffer Disable Override */
#define SE1B_INP_DIS                (* (reg8 *) SE1B__INP_DIS)
/* LCD Common or Segment Drive */
#define SE1B_LCD_COM_SEG            (* (reg8 *) SE1B__LCD_COM_SEG)
/* Enable Segment LCD */
#define SE1B_LCD_EN                 (* (reg8 *) SE1B__LCD_EN)
/* Slew Rate Control */
#define SE1B_SLW                    (* (reg8 *) SE1B__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SE1B_PRTDSI__CAPS_SEL       (* (reg8 *) SE1B__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SE1B_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SE1B__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SE1B_PRTDSI__OE_SEL0        (* (reg8 *) SE1B__PRTDSI__OE_SEL0) 
#define SE1B_PRTDSI__OE_SEL1        (* (reg8 *) SE1B__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SE1B_PRTDSI__OUT_SEL0       (* (reg8 *) SE1B__PRTDSI__OUT_SEL0) 
#define SE1B_PRTDSI__OUT_SEL1       (* (reg8 *) SE1B__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SE1B_PRTDSI__SYNC_OUT       (* (reg8 *) SE1B__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SE1B__SIO_CFG)
    #define SE1B_SIO_HYST_EN        (* (reg8 *) SE1B__SIO_HYST_EN)
    #define SE1B_SIO_REG_HIFREQ     (* (reg8 *) SE1B__SIO_REG_HIFREQ)
    #define SE1B_SIO_CFG            (* (reg8 *) SE1B__SIO_CFG)
    #define SE1B_SIO_DIFF           (* (reg8 *) SE1B__SIO_DIFF)
#endif /* (SE1B__SIO_CFG) */

/* Interrupt Registers */
#if defined(SE1B__INTSTAT)
    #define SE1B_INTSTAT            (* (reg8 *) SE1B__INTSTAT)
    #define SE1B_SNAP               (* (reg8 *) SE1B__SNAP)
    
	#define SE1B_0_INTTYPE_REG 		(* (reg8 *) SE1B__0__INTTYPE)
#endif /* (SE1B__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SE1B_H */


/* [] END OF FILE */
