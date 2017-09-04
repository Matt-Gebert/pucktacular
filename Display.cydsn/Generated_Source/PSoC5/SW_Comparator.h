/*******************************************************************************
* File Name: SW_Comparator.c
* Version 2.0
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Analog Comparator User Module.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_COMP_SW_Comparator_H) 
#define CY_COMP_SW_Comparator_H

#include "cytypes.h"
#include "CyLib.h"
#include "cyfitter.h" 


#define SW_Comparator_RECALMODE (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Comp_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*       Type defines
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
   /* uint8 compCRReg; */
}SW_Comparator_backupStruct;

#if (CY_PSOC5A)
    /* Stop API changes for PSoC5A */
    typedef struct
    {
        uint8 compCRReg;
    }   SW_Comparator_LOWPOWER_BACKUP_STRUCT;
#endif /* CY_PSOC5A */

/* component init state */
extern uint8 SW_Comparator_initVar;


/**************************************
*        Function Prototypes 
**************************************/

void    SW_Comparator_Start(void)                  ;
void    SW_Comparator_Stop(void)                   ;
void    SW_Comparator_SetSpeed(uint8 speed)        ;
uint8   SW_Comparator_GetCompare(void)             ;
uint16  SW_Comparator_ZeroCal(void)                ;
void    SW_Comparator_LoadTrim(uint16 trimVal)     ;
void SW_Comparator_Init(void)                      ; 
void SW_Comparator_Enable(void)                    ;
void SW_Comparator_SaveConfig(void)                ;
void SW_Comparator_RestoreConfig(void)             ;
void SW_Comparator_Sleep(void)                     ;
void SW_Comparator_Wakeup(void)                    ;
/* Below APIs are valid only for PSoC3, PSoC5LP silicons.*/
#if (CY_PSOC3 || CY_PSOC5LP) 
    void SW_Comparator_PwrDwnOverrideEnable(void)  ;
    void SW_Comparator_PwrDwnOverrideDisable(void) ;
#endif /* CY_PSOC3 || CY_PSOC5LP */


/**************************************
*           API Constants        
**************************************/

/* Power constants for SetSpeed() function */
#define SW_Comparator_SLOWSPEED   (0x00u)
#define SW_Comparator_HIGHSPEED   (0x01u)
#define SW_Comparator_LOWPOWER    (0x02u)


/**************************************
*           Parameter Defaults        
**************************************/

#define SW_Comparator_DEFAULT_SPEED       (1u) 
#define SW_Comparator_DEFAULT_HYSTERESIS  (0u)
#define SW_Comparator_DEFAULT_POLARITY    (0u)
#define SW_Comparator_DEFAULT_BYPASS_SYNC (0u)
#define SW_Comparator_DEFAULT_PWRDWN_OVRD (0u)


/**************************************
*             Registers        
**************************************/
#define SW_Comparator_CR_REG            (* (reg8 *) SW_Comparator_ctComp__CR )               /* Config register */
#define SW_Comparator_CR_PTR            (  (reg8 *) SW_Comparator_ctComp__CR )
#define SW_Comparator_CLK_REG           (* (reg8 *) SW_Comparator_ctComp__CLK )  /* Comp clock control register */
#define SW_Comparator_CLK_PTR           (  (reg8 *) SW_Comparator_ctComp__CLK )
#define SW_Comparator_SW0_REG           (* (reg8 *) SW_Comparator_ctComp__SW0 )            /* Routing registers */
#define SW_Comparator_SW0_PTR           (  (reg8 *) SW_Comparator_ctComp__SW0 )
#define SW_Comparator_SW2_REG           (* (reg8 *) SW_Comparator_ctComp__SW2 )
#define SW_Comparator_SW2_PTR           (  (reg8 *) SW_Comparator_ctComp__SW2 )
#define SW_Comparator_SW3_REG           (* (reg8 *) SW_Comparator_ctComp__SW3 )
#define SW_Comparator_SW3_PTR           (  (reg8 *) SW_Comparator_ctComp__SW3 )
#define SW_Comparator_SW4_REG           (* (reg8 *) SW_Comparator_ctComp__SW4 )
#define SW_Comparator_SW4_PTR           (  (reg8 *) SW_Comparator_ctComp__SW4 )
#define SW_Comparator_SW6_REG           (* (reg8 *) SW_Comparator_ctComp__SW6 )
#define SW_Comparator_SW6_PTR           (  (reg8 *) SW_Comparator_ctComp__SW6 )

/* Trim registers */
/* PSoC5A */
#if (CY_PSOC5A)
    #define SW_Comparator_TR_REG        (* (reg8 *) SW_Comparator_ctComp__TR )                /* Trim registers */
    #define SW_Comparator_TR_PTR        (  (reg8 *) SW_Comparator_ctComp__TR )
#endif /* CY_PSOC5A */

/* PSoC3, PSoC5LP or later */
#if (CY_PSOC3 || CY_PSOC5LP) 
    #define SW_Comparator_TR0_REG       (* (reg8 *) SW_Comparator_ctComp__TR0 )/* Trim register for P-type load */
    #define SW_Comparator_TR0_PTR       (  (reg8 *) SW_Comparator_ctComp__TR0 ) 
    #define SW_Comparator_TR1_REG       (* (reg8 *) SW_Comparator_ctComp__TR1 )/* Trim register for N-type load */
    #define SW_Comparator_TR1_PTR       (  (reg8 *) SW_Comparator_ctComp__TR1 ) 
#endif /* CY_PSOC3 || CY_PSOC5LP */

#define SW_Comparator_WRK_REG           (* (reg8 *) SW_Comparator_ctComp__WRK )    /* Working register - output */
#define SW_Comparator_WRK_PTR           (  (reg8 *) SW_Comparator_ctComp__WRK )
#define SW_Comparator_PWRMGR_REG        (* (reg8 *) SW_Comparator_ctComp__PM_ACT_CFG )  /* Active Power manager */
#define SW_Comparator_PWRMGR_PTR        (  (reg8 *) SW_Comparator_ctComp__PM_ACT_CFG )
#define SW_Comparator_STBY_PWRMGR_REG   (* (reg8 *) SW_Comparator_ctComp__PM_STBY_CFG )/* Standby Power manager */
#define SW_Comparator_STBY_PWRMGR_PTR   (  (reg8 *) SW_Comparator_ctComp__PM_STBY_CFG )

/*      Trim Locations      */
#define SW_Comparator_ctComp__TRIM__TR0_HS_PTR     ((void CYFAR *) SW_Comparator_ctComp__TRIM__TR0_HS)
#define SW_Comparator_ctComp__TRIM__TR0_HS_REG     CY_GET_XTND_REG8(SW_Comparator_ctComp__TRIM__TR0_HS_PTR)
#if (CY_PSOC3 || CY_PSOC5LP)
    #define SW_Comparator_ctComp__TRIM__TR1_HS_PTR ((void CYFAR *) SW_Comparator_ctComp__TRIM__TR1_HS)
    #define SW_Comparator_ctComp__TRIM__TR1_HS_REG CY_GET_XTND_REG8(SW_Comparator_ctComp__TRIM__TR1_HS_PTR)
#endif /* (CY_PSOC3 || CY_PSOC5LP) */
#define SW_Comparator_ctComp__TRIM__TR0_LS_PTR     ((void CYFAR *) ((uint32)SW_Comparator_ctComp__TRIM__TR0 + 1u))
#define SW_Comparator_ctComp__TRIM__TR0_LS_REG     CY_GET_XTND_REG8(SW_Comparator_ctComp__TRIM__TR0_LS_PTR)
#if (CY_PSOC3 || CY_PSOC5LP)
    #define SW_Comparator_ctComp__TRIM__TR1_LS_PTR ((void CYFAR *) ((uint32)SW_Comparator_ctComp__TRIM__TR1 + 1u))
    #define SW_Comparator_ctComp__TRIM__TR1_LS_REG CY_GET_XTND_REG8(SW_Comparator_ctComp__TRIM__TR1_LS_PTR)
#endif /* CY_PSOC3 || CY_PSOC5LP */


/***************************************
*  Registers definitions
* for backward capability        
***************************************/
#define SW_Comparator_CR                (* (reg8 *) SW_Comparator_ctComp__CR )               /* Config register */
#define SW_Comparator_CLK               (* (reg8 *) SW_Comparator_ctComp__CLK )  /* Comp clock control register */
#define SW_Comparator_SW0               (* (reg8 *) SW_Comparator_ctComp__SW0 )            /* Routing registers */
#define SW_Comparator_SW2               (* (reg8 *) SW_Comparator_ctComp__SW2 )
#define SW_Comparator_SW3               (* (reg8 *) SW_Comparator_ctComp__SW3 )
#define SW_Comparator_SW4               (* (reg8 *) SW_Comparator_ctComp__SW4 )
#define SW_Comparator_SW6               (* (reg8 *) SW_Comparator_ctComp__SW6 )

/* Trim registers */
/* PSoC5A */
#if (CY_PSOC5A)
    #define SW_Comparator_TR            (* (reg8 *) SW_Comparator_ctComp__TR )                /* Trim registers */
#endif /* CY_PSOC5A */

/* PSoC3, PSoC5LP or later */
#if (CY_PSOC3 || CY_PSOC5LP) 
    #define SW_Comparator_TR0           (* (reg8 *) SW_Comparator_ctComp__TR0 )/* Trim register for P-type load */
    #define SW_Comparator_TR1           (* (reg8 *) SW_Comparator_ctComp__TR1 )/* Trim register for N-type load */
#endif /* CY_PSOC3 || CY_PSOC5LP */

#define SW_Comparator_WRK               (* (reg8 *) SW_Comparator_ctComp__WRK )    /* Working register - output */
#define SW_Comparator_PWRMGR            (* (reg8 *) SW_Comparator_ctComp__PM_ACT_CFG )  /* Active Power manager */
#define SW_Comparator_STBY_PWRMGR       (* (reg8 *) SW_Comparator_ctComp__PM_STBY_CFG )/* Standby Power manager */

/*      Trim Locations      */
#define SW_Comparator_HS_TRIM_TR0        CY_GET_XTND_REG8(SW_Comparator_ctComp__TRIM__TR0_HS_PTR)
#if (CY_PSOC3 || CY_PSOC5LP)
    #define SW_Comparator_HS_TRIM_TR1    CY_GET_XTND_REG8(SW_Comparator_ctComp__TRIM__TR1_HS_PTR)
#endif /* (CY_PSOC3 || CY_PSOC5LP) */
#define SW_Comparator_LS_TRIM_TR0        CY_GET_XTND_REG8(SW_Comparator_ctComp__TRIM__TR0_LS_PTR)
#if (CY_PSOC3 || CY_PSOC5LP)
    #define SW_Comparator_LS_TRIM_TR1    CY_GET_XTND_REG8(SW_Comparator_ctComp__TRIM__TR1_LS_PTR)
#endif /* CY_PSOC3 || CY_PSOC5LP */


/**************************************
*       Register Constants        
**************************************/

/* CR (Comp Control Register)             */
#define SW_Comparator_CFG_MODE_MASK      (0x78u)
#define SW_Comparator_FILTER_ON          (0x40u)
#define SW_Comparator_HYST_OFF           (0x20u)
#define SW_Comparator_CAL_ON             (0x10u)
#define SW_Comparator_MX_AO              (0x08u)
#define SW_Comparator_PWRDWN_OVRD        (0x04u)

#define SW_Comparator_PWR_MODE_SHIFT     (0x00u)
#define SW_Comparator_PWR_MODE_MASK      ((uint8)(0x03u << SW_Comparator_PWR_MODE_SHIFT))
#define SW_Comparator_PWR_MODE_SLOW      ((uint8)(0x00u << SW_Comparator_PWR_MODE_SHIFT))
#define SW_Comparator_PWR_MODE_FAST      ((uint8)(0x01u << SW_Comparator_PWR_MODE_SHIFT))
#define SW_Comparator_PWR_MODE_ULOW      ((uint8)(0x02u << SW_Comparator_PWR_MODE_SHIFT))

/* CLK (Comp Clock Control Register)      */
#define SW_Comparator_BYPASS_SYNC        (0x10u)
#define SW_Comparator_SYNC_CLK_EN        (0x08u)
#define SW_Comparator_SYNCCLK_MASK       (SW_Comparator_BYPASS_SYNC | SW_Comparator_SYNC_CLK_EN)

/* SW3 Routing Register definitions */
#define SW_Comparator_CMP_SW3_INPCTL_MASK (0x09u)   /* SW3 bits for inP routing control */

/* TR (Comp Trim Register)     */
#define SW_Comparator_DEFAULT_CMP_TRIM    (0x00u)

/* PSoC5A */
#if (CY_PSOC5A)
    #define SW_Comparator_CMP_TRIM1_DIR   (0x08u)   /* Trim direction for N-type load for offset calibration */
    #define SW_Comparator_CMP_TRIM1_MASK  (0x07u)   /* Trim for N-type load for offset calibration */
    #define SW_Comparator_CMP_TRIM2_DIR   (0x80u)   /* Trim direction for P-type load for offset calibration */
    #define SW_Comparator_CMP_TRIM2_MASK  (0x70u)   /* Trim for P-type load for offset calibration */
#endif /* CY_PSOC5A */

/* PSoC3, PSoC5LP or later */
#if (CY_PSOC3 || CY_PSOC5LP)
    #define SW_Comparator_CMP_TR0_DIR     (0x10u)   /* Trim direction for N-type load for offset calibration */
    #define SW_Comparator_CMP_TR0_MASK    (0x0Fu)   /* Trim for N-type load for offset calibration */
    #define SW_Comparator_CMP_TR1_DIR     (0x10u)   /* Trim direction for P-type load for offset calibration */
    #define SW_Comparator_CMP_TR1_MASK    (0x07u)   /* Trim for P-type load for offset calibration */ 
#endif /* CY_PSOC3 || CY_PSOC5LP */


/* WRK (Comp output working register)     */ 
#define SW_Comparator_CMP_OUT_MASK       SW_Comparator_ctComp__WRK_MASK /* Specific comparator out mask */

/* PM_ACT_CFG7 (Active Power Mode CFG Register)     */ 
#define SW_Comparator_ACT_PWR_EN         SW_Comparator_ctComp__PM_ACT_MSK /* Power enable mask */

/* PM_STBY_CFG7 (Standby Power Mode CFG Register)     */ 
#define SW_Comparator_STBY_PWR_EN        SW_Comparator_ctComp__PM_STBY_MSK /* Standby Power enable mask */

#if (CY_PSOC5A)
    /* For stop API changes mask to make the COMP register CR to 0X00  */
    #define SW_Comparator_COMP_REG_CLR   (0x00u)
#endif /* CY_PSOC5A */

#endif /* CY_COMP_SW_Comparator_H */


/* [] END OF FILE */
