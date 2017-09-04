/*******************************************************************************
* File Name: SE2A.h  
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

#if !defined(CY_PINS_SE2A_H) /* Pins SE2A_H */
#define CY_PINS_SE2A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SE2A_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SE2A__PORT == 15 && ((SE2A__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SE2A_Write(uint8 value);
void    SE2A_SetDriveMode(uint8 mode);
uint8   SE2A_ReadDataReg(void);
uint8   SE2A_Read(void);
void    SE2A_SetInterruptMode(uint16 position, uint16 mode);
uint8   SE2A_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SE2A_SetDriveMode() function.
     *  @{
     */
        #define SE2A_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SE2A_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SE2A_DM_RES_UP          PIN_DM_RES_UP
        #define SE2A_DM_RES_DWN         PIN_DM_RES_DWN
        #define SE2A_DM_OD_LO           PIN_DM_OD_LO
        #define SE2A_DM_OD_HI           PIN_DM_OD_HI
        #define SE2A_DM_STRONG          PIN_DM_STRONG
        #define SE2A_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SE2A_MASK               SE2A__MASK
#define SE2A_SHIFT              SE2A__SHIFT
#define SE2A_WIDTH              1u

/* Interrupt constants */
#if defined(SE2A__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SE2A_SetInterruptMode() function.
     *  @{
     */
        #define SE2A_INTR_NONE      (uint16)(0x0000u)
        #define SE2A_INTR_RISING    (uint16)(0x0001u)
        #define SE2A_INTR_FALLING   (uint16)(0x0002u)
        #define SE2A_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SE2A_INTR_MASK      (0x01u) 
#endif /* (SE2A__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SE2A_PS                     (* (reg8 *) SE2A__PS)
/* Data Register */
#define SE2A_DR                     (* (reg8 *) SE2A__DR)
/* Port Number */
#define SE2A_PRT_NUM                (* (reg8 *) SE2A__PRT) 
/* Connect to Analog Globals */                                                  
#define SE2A_AG                     (* (reg8 *) SE2A__AG)                       
/* Analog MUX bux enable */
#define SE2A_AMUX                   (* (reg8 *) SE2A__AMUX) 
/* Bidirectional Enable */                                                        
#define SE2A_BIE                    (* (reg8 *) SE2A__BIE)
/* Bit-mask for Aliased Register Access */
#define SE2A_BIT_MASK               (* (reg8 *) SE2A__BIT_MASK)
/* Bypass Enable */
#define SE2A_BYP                    (* (reg8 *) SE2A__BYP)
/* Port wide control signals */                                                   
#define SE2A_CTL                    (* (reg8 *) SE2A__CTL)
/* Drive Modes */
#define SE2A_DM0                    (* (reg8 *) SE2A__DM0) 
#define SE2A_DM1                    (* (reg8 *) SE2A__DM1)
#define SE2A_DM2                    (* (reg8 *) SE2A__DM2) 
/* Input Buffer Disable Override */
#define SE2A_INP_DIS                (* (reg8 *) SE2A__INP_DIS)
/* LCD Common or Segment Drive */
#define SE2A_LCD_COM_SEG            (* (reg8 *) SE2A__LCD_COM_SEG)
/* Enable Segment LCD */
#define SE2A_LCD_EN                 (* (reg8 *) SE2A__LCD_EN)
/* Slew Rate Control */
#define SE2A_SLW                    (* (reg8 *) SE2A__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SE2A_PRTDSI__CAPS_SEL       (* (reg8 *) SE2A__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SE2A_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SE2A__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SE2A_PRTDSI__OE_SEL0        (* (reg8 *) SE2A__PRTDSI__OE_SEL0) 
#define SE2A_PRTDSI__OE_SEL1        (* (reg8 *) SE2A__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SE2A_PRTDSI__OUT_SEL0       (* (reg8 *) SE2A__PRTDSI__OUT_SEL0) 
#define SE2A_PRTDSI__OUT_SEL1       (* (reg8 *) SE2A__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SE2A_PRTDSI__SYNC_OUT       (* (reg8 *) SE2A__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SE2A__SIO_CFG)
    #define SE2A_SIO_HYST_EN        (* (reg8 *) SE2A__SIO_HYST_EN)
    #define SE2A_SIO_REG_HIFREQ     (* (reg8 *) SE2A__SIO_REG_HIFREQ)
    #define SE2A_SIO_CFG            (* (reg8 *) SE2A__SIO_CFG)
    #define SE2A_SIO_DIFF           (* (reg8 *) SE2A__SIO_DIFF)
#endif /* (SE2A__SIO_CFG) */

/* Interrupt Registers */
#if defined(SE2A__INTSTAT)
    #define SE2A_INTSTAT            (* (reg8 *) SE2A__INTSTAT)
    #define SE2A_SNAP               (* (reg8 *) SE2A__SNAP)
    
	#define SE2A_0_INTTYPE_REG 		(* (reg8 *) SE2A__0__INTTYPE)
#endif /* (SE2A__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SE2A_H */


/* [] END OF FILE */
