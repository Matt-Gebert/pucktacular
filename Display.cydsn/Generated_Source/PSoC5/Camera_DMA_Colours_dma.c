/***************************************************************************
* File Name: Camera_DMA_Colours_dma.c  
* Version 1.70
*
*  Description:
*   Provides an API for the DMAC component. The API includes functions
*   for the DMA controller, DMA channels and Transfer Descriptors.
*
*
*   Note:
*     This module requires the developer to finish or fill in the auto
*     generated funcions and setup the dma channel and TD's.
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#include <CYLIB.H>
#include <CYDMAC.H>
#include <Camera_DMA_Colours_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* Camera_DMA_Colours__DRQ_CTL_REG
* 
* 
* Camera_DMA_Colours__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* Camera_DMA_Colours__NUMBEROF_TDS
* 
* Priority of this channel.
* Camera_DMA_Colours__PRIORITY
* 
* True if Camera_DMA_Colours_TERMIN_SEL is used.
* Camera_DMA_Colours__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* Camera_DMA_Colours__TERMIN_SEL
* 
* 
* True if Camera_DMA_Colours_TERMOUT0_SEL is used.
* Camera_DMA_Colours__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* Camera_DMA_Colours__TERMOUT0_SEL
* 
* 
* True if Camera_DMA_Colours_TERMOUT1_SEL is used.
* Camera_DMA_Colours__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* Camera_DMA_Colours__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of Camera_DMA_Colours dma channel */
uint8 Camera_DMA_Colours_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 Camera_DMA_Colours_DmaInitalize
**********************************************************************
* Summary:
*   Allocates and initialises a channel of the DMAC to be used by the
*   caller.
*
* Parameters:
*   BurstCount.
*       
*       
*   ReqestPerBurst.
*       
*       
*   UpperSrcAddress.
*       
*       
*   UpperDestAddress.
*       
*
* Return:
*   The channel that can be used by the caller for DMA activity.
*   DMA_INVALID_CHANNEL (0xFF) if there are no channels left. 
*
*
*******************************************************************/
uint8 Camera_DMA_Colours_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    Camera_DMA_Colours_DmaHandle = (uint8)Camera_DMA_Colours__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(Camera_DMA_Colours_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)Camera_DMA_Colours__TERMOUT0_SEL,
                                  (uint8)Camera_DMA_Colours__TERMOUT1_SEL,
                                  (uint8)Camera_DMA_Colours__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(Camera_DMA_Colours_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(Camera_DMA_Colours_DmaHandle, (uint8)Camera_DMA_Colours__PRIORITY);
    
    return Camera_DMA_Colours_DmaHandle;
}

/*********************************************************************
* Function Name: void Camera_DMA_Colours_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with Camera_DMA_Colours.
*
*
* Parameters:
*   void.
*
*
*
* Return:
*   void.
*
*******************************************************************/
void Camera_DMA_Colours_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(Camera_DMA_Colours_DmaHandle);
}

