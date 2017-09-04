/*******************************************************************************
* File Name: Camera_osc.h  
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

#if !defined(CY_PINS_Camera_osc_H) /* Pins Camera_osc_H */
#define CY_PINS_Camera_osc_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Camera_osc_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Camera_osc__PORT == 15 && ((Camera_osc__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Camera_osc_Write(uint8 value);
void    Camera_osc_SetDriveMode(uint8 mode);
uint8   Camera_osc_ReadDataReg(void);
uint8   Camera_osc_Read(void);
void    Camera_osc_SetInterruptMode(uint16 position, uint16 mode);
uint8   Camera_osc_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Camera_osc_SetDriveMode() function.
     *  @{
     */
        #define Camera_osc_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Camera_osc_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Camera_osc_DM_RES_UP          PIN_DM_RES_UP
        #define Camera_osc_DM_RES_DWN         PIN_DM_RES_DWN
        #define Camera_osc_DM_OD_LO           PIN_DM_OD_LO
        #define Camera_osc_DM_OD_HI           PIN_DM_OD_HI
        #define Camera_osc_DM_STRONG          PIN_DM_STRONG
        #define Camera_osc_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Camera_osc_MASK               Camera_osc__MASK
#define Camera_osc_SHIFT              Camera_osc__SHIFT
#define Camera_osc_WIDTH              1u

/* Interrupt constants */
#if defined(Camera_osc__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Camera_osc_SetInterruptMode() function.
     *  @{
     */
        #define Camera_osc_INTR_NONE      (uint16)(0x0000u)
        #define Camera_osc_INTR_RISING    (uint16)(0x0001u)
        #define Camera_osc_INTR_FALLING   (uint16)(0x0002u)
        #define Camera_osc_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Camera_osc_INTR_MASK      (0x01u) 
#endif /* (Camera_osc__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Camera_osc_PS                     (* (reg8 *) Camera_osc__PS)
/* Data Register */
#define Camera_osc_DR                     (* (reg8 *) Camera_osc__DR)
/* Port Number */
#define Camera_osc_PRT_NUM                (* (reg8 *) Camera_osc__PRT) 
/* Connect to Analog Globals */                                                  
#define Camera_osc_AG                     (* (reg8 *) Camera_osc__AG)                       
/* Analog MUX bux enable */
#define Camera_osc_AMUX                   (* (reg8 *) Camera_osc__AMUX) 
/* Bidirectional Enable */                                                        
#define Camera_osc_BIE                    (* (reg8 *) Camera_osc__BIE)
/* Bit-mask for Aliased Register Access */
#define Camera_osc_BIT_MASK               (* (reg8 *) Camera_osc__BIT_MASK)
/* Bypass Enable */
#define Camera_osc_BYP                    (* (reg8 *) Camera_osc__BYP)
/* Port wide control signals */                                                   
#define Camera_osc_CTL                    (* (reg8 *) Camera_osc__CTL)
/* Drive Modes */
#define Camera_osc_DM0                    (* (reg8 *) Camera_osc__DM0) 
#define Camera_osc_DM1                    (* (reg8 *) Camera_osc__DM1)
#define Camera_osc_DM2                    (* (reg8 *) Camera_osc__DM2) 
/* Input Buffer Disable Override */
#define Camera_osc_INP_DIS                (* (reg8 *) Camera_osc__INP_DIS)
/* LCD Common or Segment Drive */
#define Camera_osc_LCD_COM_SEG            (* (reg8 *) Camera_osc__LCD_COM_SEG)
/* Enable Segment LCD */
#define Camera_osc_LCD_EN                 (* (reg8 *) Camera_osc__LCD_EN)
/* Slew Rate Control */
#define Camera_osc_SLW                    (* (reg8 *) Camera_osc__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Camera_osc_PRTDSI__CAPS_SEL       (* (reg8 *) Camera_osc__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Camera_osc_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Camera_osc__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Camera_osc_PRTDSI__OE_SEL0        (* (reg8 *) Camera_osc__PRTDSI__OE_SEL0) 
#define Camera_osc_PRTDSI__OE_SEL1        (* (reg8 *) Camera_osc__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Camera_osc_PRTDSI__OUT_SEL0       (* (reg8 *) Camera_osc__PRTDSI__OUT_SEL0) 
#define Camera_osc_PRTDSI__OUT_SEL1       (* (reg8 *) Camera_osc__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Camera_osc_PRTDSI__SYNC_OUT       (* (reg8 *) Camera_osc__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Camera_osc__SIO_CFG)
    #define Camera_osc_SIO_HYST_EN        (* (reg8 *) Camera_osc__SIO_HYST_EN)
    #define Camera_osc_SIO_REG_HIFREQ     (* (reg8 *) Camera_osc__SIO_REG_HIFREQ)
    #define Camera_osc_SIO_CFG            (* (reg8 *) Camera_osc__SIO_CFG)
    #define Camera_osc_SIO_DIFF           (* (reg8 *) Camera_osc__SIO_DIFF)
#endif /* (Camera_osc__SIO_CFG) */

/* Interrupt Registers */
#if defined(Camera_osc__INTSTAT)
    #define Camera_osc_INTSTAT            (* (reg8 *) Camera_osc__INTSTAT)
    #define Camera_osc_SNAP               (* (reg8 *) Camera_osc__SNAP)
    
	#define Camera_osc_0_INTTYPE_REG 		(* (reg8 *) Camera_osc__0__INTTYPE)
#endif /* (Camera_osc__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Camera_osc_H */


/* [] END OF FILE */
