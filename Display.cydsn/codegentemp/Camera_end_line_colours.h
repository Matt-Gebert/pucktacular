/*******************************************************************************
* File Name: Camera_end_line_colours.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Camera_end_line_colours_H)
#define CY_ISR_Camera_end_line_colours_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Camera_end_line_colours_Start(void);
void Camera_end_line_colours_StartEx(cyisraddress address);
void Camera_end_line_colours_Stop(void);

CY_ISR_PROTO(Camera_end_line_colours_Interrupt);

void Camera_end_line_colours_SetVector(cyisraddress address);
cyisraddress Camera_end_line_colours_GetVector(void);

void Camera_end_line_colours_SetPriority(uint8 priority);
uint8 Camera_end_line_colours_GetPriority(void);

void Camera_end_line_colours_Enable(void);
uint8 Camera_end_line_colours_GetState(void);
void Camera_end_line_colours_Disable(void);

void Camera_end_line_colours_SetPending(void);
void Camera_end_line_colours_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Camera_end_line_colours ISR. */
#define Camera_end_line_colours_INTC_VECTOR            ((reg32 *) Camera_end_line_colours__INTC_VECT)

/* Address of the Camera_end_line_colours ISR priority. */
#define Camera_end_line_colours_INTC_PRIOR             ((reg8 *) Camera_end_line_colours__INTC_PRIOR_REG)

/* Priority of the Camera_end_line_colours interrupt. */
#define Camera_end_line_colours_INTC_PRIOR_NUMBER      Camera_end_line_colours__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Camera_end_line_colours interrupt. */
#define Camera_end_line_colours_INTC_SET_EN            ((reg32 *) Camera_end_line_colours__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Camera_end_line_colours interrupt. */
#define Camera_end_line_colours_INTC_CLR_EN            ((reg32 *) Camera_end_line_colours__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Camera_end_line_colours interrupt state to pending. */
#define Camera_end_line_colours_INTC_SET_PD            ((reg32 *) Camera_end_line_colours__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Camera_end_line_colours interrupt. */
#define Camera_end_line_colours_INTC_CLR_PD            ((reg32 *) Camera_end_line_colours__INTC_CLR_PD_REG)


#endif /* CY_ISR_Camera_end_line_colours_H */


/* [] END OF FILE */
