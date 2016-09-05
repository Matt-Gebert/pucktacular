/*******************************************************************************
* File Name: HREF.h  
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

#if !defined(CY_PINS_HREF_H) /* Pins HREF_H */
#define CY_PINS_HREF_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HREF_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HREF__PORT == 15 && ((HREF__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    HREF_Write(uint8 value);
void    HREF_SetDriveMode(uint8 mode);
uint8   HREF_ReadDataReg(void);
uint8   HREF_Read(void);
void    HREF_SetInterruptMode(uint16 position, uint16 mode);
uint8   HREF_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the HREF_SetDriveMode() function.
     *  @{
     */
        #define HREF_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define HREF_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define HREF_DM_RES_UP          PIN_DM_RES_UP
        #define HREF_DM_RES_DWN         PIN_DM_RES_DWN
        #define HREF_DM_OD_LO           PIN_DM_OD_LO
        #define HREF_DM_OD_HI           PIN_DM_OD_HI
        #define HREF_DM_STRONG          PIN_DM_STRONG
        #define HREF_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define HREF_MASK               HREF__MASK
#define HREF_SHIFT              HREF__SHIFT
#define HREF_WIDTH              1u

/* Interrupt constants */
#if defined(HREF__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HREF_SetInterruptMode() function.
     *  @{
     */
        #define HREF_INTR_NONE      (uint16)(0x0000u)
        #define HREF_INTR_RISING    (uint16)(0x0001u)
        #define HREF_INTR_FALLING   (uint16)(0x0002u)
        #define HREF_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define HREF_INTR_MASK      (0x01u) 
#endif /* (HREF__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HREF_PS                     (* (reg8 *) HREF__PS)
/* Data Register */
#define HREF_DR                     (* (reg8 *) HREF__DR)
/* Port Number */
#define HREF_PRT_NUM                (* (reg8 *) HREF__PRT) 
/* Connect to Analog Globals */                                                  
#define HREF_AG                     (* (reg8 *) HREF__AG)                       
/* Analog MUX bux enable */
#define HREF_AMUX                   (* (reg8 *) HREF__AMUX) 
/* Bidirectional Enable */                                                        
#define HREF_BIE                    (* (reg8 *) HREF__BIE)
/* Bit-mask for Aliased Register Access */
#define HREF_BIT_MASK               (* (reg8 *) HREF__BIT_MASK)
/* Bypass Enable */
#define HREF_BYP                    (* (reg8 *) HREF__BYP)
/* Port wide control signals */                                                   
#define HREF_CTL                    (* (reg8 *) HREF__CTL)
/* Drive Modes */
#define HREF_DM0                    (* (reg8 *) HREF__DM0) 
#define HREF_DM1                    (* (reg8 *) HREF__DM1)
#define HREF_DM2                    (* (reg8 *) HREF__DM2) 
/* Input Buffer Disable Override */
#define HREF_INP_DIS                (* (reg8 *) HREF__INP_DIS)
/* LCD Common or Segment Drive */
#define HREF_LCD_COM_SEG            (* (reg8 *) HREF__LCD_COM_SEG)
/* Enable Segment LCD */
#define HREF_LCD_EN                 (* (reg8 *) HREF__LCD_EN)
/* Slew Rate Control */
#define HREF_SLW                    (* (reg8 *) HREF__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HREF_PRTDSI__CAPS_SEL       (* (reg8 *) HREF__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HREF_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HREF__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HREF_PRTDSI__OE_SEL0        (* (reg8 *) HREF__PRTDSI__OE_SEL0) 
#define HREF_PRTDSI__OE_SEL1        (* (reg8 *) HREF__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HREF_PRTDSI__OUT_SEL0       (* (reg8 *) HREF__PRTDSI__OUT_SEL0) 
#define HREF_PRTDSI__OUT_SEL1       (* (reg8 *) HREF__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HREF_PRTDSI__SYNC_OUT       (* (reg8 *) HREF__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(HREF__SIO_CFG)
    #define HREF_SIO_HYST_EN        (* (reg8 *) HREF__SIO_HYST_EN)
    #define HREF_SIO_REG_HIFREQ     (* (reg8 *) HREF__SIO_REG_HIFREQ)
    #define HREF_SIO_CFG            (* (reg8 *) HREF__SIO_CFG)
    #define HREF_SIO_DIFF           (* (reg8 *) HREF__SIO_DIFF)
#endif /* (HREF__SIO_CFG) */

/* Interrupt Registers */
#if defined(HREF__INTSTAT)
    #define HREF_INTSTAT            (* (reg8 *) HREF__INTSTAT)
    #define HREF_SNAP               (* (reg8 *) HREF__SNAP)
    
	#define HREF_0_INTTYPE_REG 		(* (reg8 *) HREF__0__INTTYPE)
#endif /* (HREF__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HREF_H */


/* [] END OF FILE */
