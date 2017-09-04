/*******************************************************************************
* File Name: D.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_D_ALIASES_H) /* Pins D_ALIASES_H */
#define CY_PINS_D_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define D_0			(D__0__PC)
#define D_0_INTR	((uint16)((uint16)0x0001u << D__0__SHIFT))

#define D_1			(D__1__PC)
#define D_1_INTR	((uint16)((uint16)0x0001u << D__1__SHIFT))

#define D_2			(D__2__PC)
#define D_2_INTR	((uint16)((uint16)0x0001u << D__2__SHIFT))

#define D_3			(D__3__PC)
#define D_3_INTR	((uint16)((uint16)0x0001u << D__3__SHIFT))

#define D_4			(D__4__PC)
#define D_4_INTR	((uint16)((uint16)0x0001u << D__4__SHIFT))

#define D_5			(D__5__PC)
#define D_5_INTR	((uint16)((uint16)0x0001u << D__5__SHIFT))

#define D_6			(D__6__PC)
#define D_6_INTR	((uint16)((uint16)0x0001u << D__6__SHIFT))

#define D_7			(D__7__PC)
#define D_7_INTR	((uint16)((uint16)0x0001u << D__7__SHIFT))

#define D_INTR_ALL	 ((uint16)(D_0_INTR| D_1_INTR| D_2_INTR| D_3_INTR| D_4_INTR| D_5_INTR| D_6_INTR| D_7_INTR))

#endif /* End Pins D_ALIASES_H */


/* [] END OF FILE */
