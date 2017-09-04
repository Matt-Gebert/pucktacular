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
#include <camera_display.h>
#include <project.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "camera_functions.h"
#include <utils.h>
//IMPORTANT CAMERA CODE:
    //LCD_SetWindowRead(uint16 col_start,uint16 row_start,uint16 col_end,uint16 row_end); 
    //LCD_SetWindowWrite(uint16 col_start,uint16 row_start,uint16 col_end,uint16 row_end);
    //Display is 320 {0,319} by 240 {0,239}

//Functions:
void CamAnalyseFrame(uint16 blobThresholdSize);
void CamSeqOperations();
void CamOrderLargest();
/*void CamGetSequence();
void CamMarkBlobs();
bool CamScanClosest(uint8 clr);
void CamMarkClosest()*/

//Constants moved into header file.
const uint8 offset = 30; //Screen Pixel Offset..
const uint8 blobThresholdSizeDefault = 80;

//Colours
const uint8 RED=0;
const uint8 GREEN=1;
const uint8 BLUE=2;

//Constant Parameters:
const uint8 numRows = 240;
const uint16 numCols = 320;


//1 - General Purpose Registers
pixel loadPix;
uint8 i=0; //Rows Counter
uint16 j=0; //Columns Counter
uint16 k=0; //Backtrack Counter

//2 - For Many Blobs, Final Coords
uint16 scaledX[50];
uint16 scaledY[50];
uint16 scaledDist[50];
uint8 scaledClr[50];
int scaledElements[50];
uint16 blobCounter=0;

//3 - For Init Seq, Calculated Ordering:
uint16 lrgX[5];
uint16 lrgY[5];
uint8 lrgClr[5];
uint16 orderedScaledX[5];
uint16 orderedScaledY[5];
uint8 orderedScaledClr[5];

//4 - Closest of a Specific Colour:
uint16 closestX;
uint16 closestY;

//5 - Magenta Lowest Y index.
uint16 lowestY;

/*******************************************************************************
* Function Name: CamGetSequence
****************************************************************************//**
*
* This Functions calls CamSeqOperations, in order to get the wall sequence of pucks.
* It makes sure the same sequence is read 10x in a row, before returning the values
* and exiting, ensuring that a consistent sequence is read.
*
*******************************************************************************/

void CamGetSequence() {
    
    memset(orderedScaledX,0,5*2);
    memset(orderedScaledY,0,5*2);
    memset(orderedScaledClr,0,5);
    
    CamSeqOperations();
    CamOrderLargest();
    uint8 pastClrSeq[5];
    uint8 q,p;
    bool consistent = false;
    while(!consistent){  
        for(q=0;q<5;q++){
            pastClrSeq[q] = orderedScaledClr[q];
        }
        consistent=true;
        for (p=0; p<3; p++) {
            CamSeqOperations();
            CamOrderLargest();
            for (q=0; q<5; q++) {
                if (pastClrSeq[q] != orderedScaledClr[q]){
                    consistent = false;
                    q=5;
                    p=5;
                }
            }
        }
    }
    //Print out Sequence of 5 to Screen
    for (k=0;k<5;k++) {
        LCD_SetWindowWrite(offset+(k-1)*2+k*15,0,offset+k*15 + (k-1)*2+14,4);
        if(orderedScaledClr[k]==RED){ //R
            loadPix.R=255;
            loadPix.G=0;
            loadPix.B=0;
        } else if (orderedScaledClr[k]==GREEN){ //G
            loadPix.R=0;
            loadPix.G=255;
            loadPix.B=0;} 
        else if (orderedScaledClr[k]==BLUE){ //B
            loadPix.R=0;
            loadPix.G=0;
            loadPix.B=255;
        } else {
            loadPix.R=0;
            loadPix.G=0;
            loadPix.B=0;
        }   
        for (j=0;j<15*5;j++)
            LCD_WritePixel(loadPix);
    }
    
}
/*******************************************************************************
* Function Name: CamDisplaySeq
****************************************************************************//**
*
This function gets the 5 largest Blobs using the CamAnalyseFrame
* to get a frame, and detect all blobs on screen.
*
*******************************************************************************/
void CamDisplaySeq(){
    for (k=0;k<5;k++) {
        LCD_SetWindowWrite(offset+(k-1)*2+k*15,0,offset+k*15 + (k-1)*2+14,4);
        if(orderedScaledClr[k]==RED){ //R
            loadPix.R=255;
            loadPix.G=0;
            loadPix.B=0;
        } else if (orderedScaledClr[k]==GREEN){ //G
            loadPix.R=0;
            loadPix.G=255;
            loadPix.B=0;} 
        else if (orderedScaledClr[k]==BLUE){ //B
            loadPix.R=0;
            loadPix.G=0;
            loadPix.B=255;
        } else {
            loadPix.R=0;
            loadPix.G=0;
            loadPix.B=0;
        }   
        for (j=0;j<15*5;j++)
            LCD_WritePixel(loadPix);
    }
}

/*******************************************************************************
* Function Name: CamSeqOperations
****************************************************************************//**
*
This function gets the 5 largest Blobs using the CamAnalyseFrame
* to get a frame, and detect all blobs on screen.
*
*******************************************************************************/
void CamSeqOperations(){
    memset(lrgX,0,5*2);
    memset(lrgY,0,5*2);
    memset(lrgClr,0,5);
    
    //Analyse the Frame, for data.
    CaptureFrameWithLights();
    CamAnalyseFrame(blobThresholdSizeDefault);
    CamMarkBlobs();
    //Find 5 largest blob values:
    uint16 max=0;
    for (j=0;j<5;j++){
        max=0;
        for(k=0;k<i;k++){ //i=amount of valid blobs above pixel weight.
            if(scaledElements[k]>scaledElements[max])
                max=k;
        }
        lrgX[j]=scaledX[max];
        lrgY[j]=scaledY[max];
        lrgClr[j]=scaledClr[max];
        scaledElements[max]=0; //Reset Value of Counter, as to not find it again.
    }
}

/*******************************************************************************
* Function Name: CamSeqOperations
****************************************************************************//**
* 
* This function orders the largest blobs found by Cam Seq Operation.
*
*******************************************************************************/
void CamOrderLargest(){
    //Determine Order of Blobs {Find by first X Cooordinate.}
    for (j=0;j<5;j++){
        uint16 max=321;
        for (k=0;k<5;k++){
            //Find Largest
            if (lrgX[k] < lrgX[max])
                max=k;
        }
        orderedScaledX[j]=lrgX[max];
        orderedScaledY[j]=lrgY[max];
        orderedScaledClr[j]=lrgClr[max];
        lrgX[max]=321; //Reset Counter, to not find again.
        lrgY[max]=241;
        lrgClr[max]=0;
    }    
    
}

/*******************************************************************************
* Function Name: CamAnalyseFrame
****************************************************************************//**
*
* Cam Analyse Frame reads in one row of data at a time,
* and applies group statistics to the rows to determine and identify blobs.
* Final results are generated in the following lists:
*       scaledX     -   The averaged X(Cols=320) position of the blob.
*       scaledY     -   The averaged Y(Rows=240) position of the blob.
*       scaledClr   -   The colour of the blob. 0=Red, 1=Green, 2=Blue
*       i           -   The number of blobs over the threshold size.
*******************************************************************************/

void CamAnalyseFrame(uint16 blobThresholdSize) {
    //Reset BlobCounter.
    blobCounter=0;
    //Hold Weighting Sums & Colours.
    int blobWeightsX[numCols];
    int blobWeightsY[numCols];
    int blobElements[numCols];
    uint8 blobClr[numCols];
    //Hold Rows of Pixels
    uint8 top[numCols];
    uint8 bottom[numCols];
    
    
    //Initialize Vals.
    //NOTE: MEMSET only resets Btyes --> That's 8 Bits. An integer is 32 bits, 4x. A 16b is 2x.
    memset(scaledElements,0,50*4);
    memset(scaledDist,0,50*2);
    memset(scaledX,0,50*2);
    memset(scaledY,0,50*2);
    memset(scaledClr,0,50);
    memset(blobWeightsX,0,numCols*4);
    memset(blobWeightsY,0,numCols*4);
    memset(blobElements,0,numCols*4);
    memset(top,0,numCols);
    memset(bottom,0,numCols);
    memset(blobClr,0,numCols);
    
    
    uint8 clr=0; //Colour --> R,G,B == 0,1,2.
    
    uint8 A,B,C,D;
    
    
    for (clr=0;clr<3;clr++) {
        for (i=0;i<numRows;i++) {
            //Set Top Row to Bottom Row
            for (j=0;j<numCols;j++)
                top[j]=bottom[j];
            //Read in the Row
            LCD_SetWindowRead(0,i,numCols,i);
            for(j=0;j<numCols;j++){
                loadPix = LCD_ReadPixel();
                if (clr==RED) bottom[j]=loadPix.R;
                else if (clr==GREEN) bottom[j]=loadPix.G;
                else  bottom[j]=loadPix.B;
            }
            //Enter Cols
            for(j=0;j<numCols;j++) {
                //Prep ABCD Vals 
                A=bottom[j];
                if(j==1){
                    D=0;C=0;
                } else {
                    D=bottom[j-1];
                    if(i!=1) C=top[j-1];
                }
                if(i==1){
                    C=0;B=0;
                }else {
                    B=top[j];
                }
                
                //Rules For Assigning A.
                //Rule 1: If Background for A, do nothing.
                if (A==0);
                //Rule 2: All blank but A, A is new blob type.
                else if (B==0 && C==0 && D==0 && A!=0) {
                    blobCounter=blobCounter+1;
                    blobClr[blobCounter-1]=clr;
                    blobWeightsX[blobCounter-1]=blobWeightsX[blobCounter-1]+j;
                    blobWeightsY[blobCounter-1]=blobWeightsY[blobCounter-1]+i;
                    blobElements[blobCounter-1]=blobElements[blobCounter-1]+1;
                    bottom[j]=blobCounter;
                }
                //Rule 3: If A == D ~= B, and B~=0, then A,D becomes B. Don't care about C.
                else if (A!=0 && D!=0 && B!=0 && B!=D) {
                    blobWeightsX[B-1]=blobWeightsX[B-1]+blobWeightsX[D-1]+j;
                    blobWeightsX[D-1]=0;
                    blobWeightsY[B-1]=blobWeightsY[B-1]+blobWeightsY[D-1]+i;
                    blobWeightsY[D-1]=0;
                    blobElements[B-1]=blobElements[B-1]+blobElements[D-1]+1;
                    blobElements[D-1]=0;
                    bottom[j]=top[j];
                    for (k = 0;k<j-1;k++)
                        if (bottom[k]==bottom[j-1])
                            bottom[k]=top[j];
                }
                //Rule 4: If B=0 and D~=0, then A is assigned to D. Don't care about C.
                else if (A!=0 && D!= 0 && B==0) {
                    blobWeightsX[D-1]=blobWeightsX[D-1]+j;
                    blobWeightsY[D-1]=blobWeightsY[D-1]+i;
                    blobElements[D-1]=blobElements[D-1]+1;
                    bottom[j]=bottom[j-1];
                }
                //Rule 5:  If B==D==0, C~=0, then A assigned to C.
                else if (B==0 && D==0 && A!=0 && C!=0) {
                    blobWeightsX[C-1]=blobWeightsX[C-1]+j;
                    blobWeightsY[C-1]=blobWeightsY[C-1]+i;
                    blobElements[C-1]=blobElements[C-1]+1;
                    bottom[j]=top[j-1];
                }
                //Rule 6: When B==D and nonzero A.
                else if (B!=0 && A!=0 && D==B) {
                    blobWeightsX[B-1]=blobWeightsX[B-1]+j;
                    blobWeightsY[B-1]=blobWeightsY[B-1]+i;
                    blobElements[B-1]=blobElements[B-1]+1;
                    bottom[j]=top[j];
                }
                //Rule 7: if B~=0, and A~=0, but D==0...
                else if (B!=0 && D==0 && A!=0) {
                    blobWeightsX[B-1]=blobWeightsX[B-1]+j;
                    blobWeightsY[B-1]=blobWeightsY[B-1]+i;
                    blobElements[B-1]=blobElements[B-1]+1;
                    bottom[j]=top[j];
                }
            }   
        }
    }
    
    i=0;//Reset i=0 for counting valid blobs.
    for (j=0;j<numCols;j++) { //Starts at 1, because the 0 index in blobWeights etc is not the first blobIndex.
        if(blobElements[j]>blobThresholdSize){
            scaledX[i]=blobWeightsX[j]/blobElements[j];
            scaledY[i]=blobWeightsY[j]/blobElements[j];
            scaledClr[i]=blobClr[j];
            scaledElements[i]=blobElements[j];
            scaledDist[i]=sqrt(pow(abs(scaledX[i]-numCols/2),2) + pow((scaledY[i]-numRows),2)); //Distance calculated from bottomw row, middle column.
            i++;
        }
    }    
}

/*******************************************************************************
* Function Name: CamMarkBlobs
****************************************************************************//**
*
* Takes the scaledX,Y data, and generates a white 10x10 square at the area 
* of interest. This shows the effective pinpointing done, in real time.
* 'i' holds how many blobs have been detected prior, from an Analyse Frame call.
*
*******************************************************************************/

void CamMarkBlobs() {
    loadPix.R=255;
    loadPix.G=255;
    loadPix.B=255;
    for (j=0;j<i; j++) {
        LCD_SetWindowWrite(scaledX[j]-5,scaledY[j]-5,scaledX[j]+5,scaledY[j]+5);
        for (k=0;k<100;k++) {
            LCD_WritePixel(loadPix);
        }
    }
}

/*******************************************************************************
* Function Name: CamScanClosest
****************************************************************************//**
*
* Finds the closest puck of a specific colour, using depth perception.
* Returns False if no puck is found.
*
*******************************************************************************/

bool CamScanClosest(uint8 clr, uint16 blobThresholdSize) {
    //Get a frame and find significant blobs.
    CamAnalyseFrame(blobThresholdSize);
    CamMarkBlobs();
    //Reset Counters for X and Y values.
    closestX=321;
    closestY=241;
    uint16 closestDist=229;
    
    //i Holds how many blobs have been detected.
    for (j=0; j<i; j++) {
        if (scaledDist[j] < closestDist && scaledClr[j]==clr) {
            closestY = scaledY[j];
            closestX = scaledX[j];
            closestDist = scaledDist[j];
        }
    }
    
    if(closestX != 321) {
    
        //mark closest with inverted colour.
        LCD_SetWindowWrite(closestX-5,closestY-5,closestX+5,closestY+5);
        if (clr == RED) { //Red.
            loadPix.R=0;
            loadPix.G=255;
            loadPix.B=255;
        } else if (clr == GREEN){ //Green.
            loadPix.R=255;
            loadPix.G=0;
            loadPix.B=255;
        } else  {
            loadPix.R=255;
            loadPix.G=255;
            loadPix.B=0;
        }
        
        for (k=0; k<100; k++) {
            LCD_WritePixel(loadPix);
        }
    
        return true;
    } else {
        return false;      
    }
}

/*******************************************************************************
* Function Name: CamMarkClosest
****************************************************************************//**
*
* Marks the found puck on the display.
*
*******************************************************************************/
void CamMarkClosest() {
    loadPix.R=255;
    loadPix.G=255;
    loadPix.B=255;
    LCD_SetWindowWrite(closestX-5,closestY-5,closestX+5,closestY+5);
    for (k=0;k<100;k++) {
        LCD_WritePixel(loadPix);
    }
}
/*******************************************************************************
* Function Name: CamIdentifyEndzone
****************************************************************************//**
*
* Finds the average position of the endzone, as well as the lowst pixel.
* Outputs into closestX, closestY and lowestY.
*
*******************************************************************************/
bool CamIdentifyEndzone() {
     //Reset BlobCounter.
    blobCounter=0;
    //Hold Weighting Sums & Colours.
    int blobWeightsX=0;
    int blobWeightsY=0;
    int blobElements=0;
    
    //Initialize Vals.
    uint8 clr; //Colour --> R,G,B == 0,1,2.
    lowestY = 0;
    for (i=0;i<numRows;i++) {
        //Read in the Row
        LCD_SetWindowRead(0,i,numCols,i);
        for(j=0;j<numCols;j++){
            loadPix = LCD_ReadPixel();
            if(((loadPix.R)&(loadPix.B))==255){//Bitwise AND of 255 values for magenta.
                blobWeightsX += j;
                blobWeightsY += i;
                blobElements+=1;
                if (j > lowestY)
                    lowestY = j;
            }
        }
    }
    closestX = blobWeightsX/blobElements;
    closestY = blobWeightsY/blobElements;
    
    //Mark the Reigon in Orange:
    loadPix.G=127;
    loadPix.B=39;
    loadPix.R=255;
    LCD_SetWindowWrite(scaledX[j]-5,scaledY[j]-5,scaledX[j]+5,scaledY[j]+5);
        for (k=0;k<100;k++) {
            LCD_WritePixel(loadPix);
        }
    
    return (blobElements>50);
}
/*******************************************************************************
* Function Name: CamIdentifyEndzonePuck
****************************************************************************//**
*
* Finds the lowest Y coordinates, also returns the highest Y coordinate.
* This is determined by the threshold of pixels the camera looks for.
*
*******************************************************************************/

bool CamIdenifyEndzonePuck(uint8 clr) {
    
    int blobWeightsX=0;
    int blobWeightsY=0;
    int blobElements=0;
    
    uint16 n;
    int16 m;
    pixel loadPix;
    uint8 const numPix=20;
    lowestY = 241;
    //uint8 Yend = 241;
    
    for (m=numRows-20; m>0; m--) {
        //Read in the Row
        LCD_SetWindowRead(0, m, numCols-1, m);
        bool rowCheck = false;
        for(n=0;n<numCols;n++){
            loadPix = LCD_ReadPixel();
            bool cR = !(loadPix.R==0);
            bool cB = !(loadPix.B==0);
            bool cG = !(loadPix.G==0);
            if(((clr==RED)&&cR&&!cB&&!cG)  || ((clr==BLUE)&&cB&&!cR&&!cG) || ((clr==GREEN)&&cG&&!cB&&!cR)) {
                rowCheck=true;
                blobWeightsX += n;
                blobWeightsY += m;
                blobElements+=1;
                if(lowestY < m || lowestY==241){
                    lowestY = m;
                }
            }
        }
        if (rowCheck) {
            
        }
        if(blobElements>=numPix){
            //Yend = m;
            m=-1;    //exit loop
        }
    }
    
    closestX = blobWeightsX/blobElements;
    closestY = blobWeightsY/blobElements;
    /*
    loadPix.R=255;
    loadPix.G=255;
    loadPix.B=255;
    LCD_SetWindowWrite(0,closestY,numCols,closestY);
    for(n=0;n<numCols;n++){
        LCD_WritePixel(loadPix);
        if(n==numCols-2)
            loadPix.B=0;
    }
    */
    CamMarkClosest();
    return (blobElements > numPix);
}
