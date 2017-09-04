/*
 * Copyright @Pucktacular, 2016
 * @Matt Gebert, Daniel Hranilovic & Kevin Duxbury
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <project.h>
#include <stdbool.h>




/*External Functions*/
void CamDisplaySeq();
void CamMarkBlobs();
void CamGetSequence();
bool CamScanClosest(uint8 clr, uint16 blobThresholdSize);
void CamMarkClosest();
bool CamIdentifyEndzone();
bool CamIdenifyEndzonePuck(uint8 clr);
void CamSeqOperations();
/*Internal Functions*/
//void CamAnalyseFrame();