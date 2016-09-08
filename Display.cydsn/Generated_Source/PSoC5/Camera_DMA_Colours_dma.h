/******************************************************************************
* File Name: Camera_DMA_Colours_dma.h  
* Version 1.70
*
*  Description:
*   Provides the function definitions for the DMA Controller.
*
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#if !defined(CY_DMA_Camera_DMA_Colours_DMA_H__)
#define CY_DMA_Camera_DMA_Colours_DMA_H__



#include <CYDMAC.H>
#include <CYFITTER.H>

#define Camera_DMA_Colours__TD_TERMOUT_EN (((0 != Camera_DMA_Colours__TERMOUT0_EN) ? TD_TERMOUT0_EN : 0) | \
    (Camera_DMA_Colours__TERMOUT1_EN ? TD_TERMOUT1_EN : 0))

/* Zero based index of Camera_DMA_Colours dma channel */
extern uint8 Camera_DMA_Colours_DmaHandle;


uint8 Camera_DMA_Colours_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) ;
void  Camera_DMA_Colours_DmaRelease(void) ;


/* CY_DMA_Camera_DMA_Colours_DMA_H__ */
#endif
