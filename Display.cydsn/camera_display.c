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
#include<project.h>
#include "camera_display.h"

static uint8 LCD_linebuffer[320*3];

static uint16 hist[32][32];

__attribute__((section(".ram")))
static void convert_line()
{
    uint32 *p=Camera_linebuffer;
    uint8 *o=LCD_linebuffer;
    while(p<Camera_linebuffer+160)
    {
        union
        {
            uint32 packed;
            struct
            {
                int8 U;
                uint8 Y0;
                int8 V;
                uint8 Y1;
            } data;
        } pix;
        pix.packed=*p++; //read pixel from Camera_linebuffer
        int U=pix.data.U;
        int Y0=pix.data.Y0;
        int V=pix.data.V;
        int Y1=pix.data.Y1;
                
        //convert YUV to RGB (left pixel in pair)
        int R=Y0+V;
        int G=Y0-U-V;
        int B=Y0+U;
        
        //saturate to 0-255 range; should compile to single unsigned saturate (USAT) instruction each
        R=R<0?0:R>0xff?0xff:R;
        G=G<0?0:G>0xff?0xff:G;
        B=B<0?0:B>0xff?0xff:B;
        
        //write out to LCD_linebuffer
        *o++=R;
        *o++=G;
        *o++=B;
        
         //convert YUV to RGB (right pixel in pair)
        R=Y1+V;
        G=Y1-U-V;
        B=Y1+U;
        
        //saturate to 0-255 range; should compile to single unsigned saturate (USAT) instruction each
        R=R<0?0:R>0xff?0xff:R;
        G=G<0?0:G>0xff?0xff:G;
        B=B<0?0:B>0xff?0xff:B;
        
        //write out to LCD_linebuffer
        *o++=R;
        *o++=G;
        *o++=B;
    }
}

__attribute__((section(".ram")))
static void threshold_line()
{
    uint8 *p=(uint8*)Camera_linebuffer;
    uint8 *o=LCD_linebuffer;
    while(p<(uint8*)Camera_linebuffer+160)
    {
        uint8 c=*p++;
        
        //convert YUV to RGB (left pixel in pair)
        uint8 R=c&9?255:0;
        uint8 G=c&2?255:0;
        uint8 B=c&0xc?255:0;
        
        //write out to LCD_linebuffer
        *o++=R;
        *o++=G;
        *o++=B;
        
        *o++=R;
        *o++=G;
        *o++=B;
    }
}

static uint8 LCD_DMA_ch,LCD_DMA_TD;

__attribute__((section(".ram")))
static void disp_line()
{
    CS_Write(3);
    OE_Control=1;
    
    CyDmaChSetInitialTd(LCD_DMA_ch,LCD_DMA_TD); //set initial TD
	CyDmaChEnable(LCD_DMA_ch,1); //enable channel (start streaming)
    
    uint8 state=1;
    while(state&1) CyDmaChStatus(LCD_DMA_ch,NULL,&state); //wait until DMA is finished
    while(!LCD_Empty); //make sure FIFO has been emptied
    
    OE_Control=0;
    CS_Write(0);
}

__attribute__((section(".ram")))
void Camera_end_line()
{
    if(display_mode==HISTOGRAM)
    {
        uint32 *p=Camera_linebuffer;
        while(p<Camera_linebuffer+160)
        {
            union
            {
                uint32 packed;
                struct
                {
                    int8 U;
                    uint8 Y0;
                    int8 V;
                    uint8 Y1;
                } data;
            } pix;
            pix.packed=*p++; //read pixel from Camera_linebuffer
            int U=pix.data.U;
            int V=pix.data.V;
            
            hist[(U+128)>>3][(V+128)>>3]++;
        }
        
        return;
    }
    
    static uint32 y=0;
    if(y++) disp_line(); //don't display first line (not converted yet)
    
    if(display_mode==THRESHOLDED) threshold_line();
    else convert_line(); //conversion starts before start of next line (DMA won't catch up if conversion is faster than capture)
    
    if(y==240) y=0,disp_line(); //display last line (just converted)
}

void LCD_DMA_Start()
{
    LCD_DMA_ch=LCD_DMA_DmaInitialize(1,1,HI16(CYDEV_SRAM_BASE),HI16(CYDEV_PERIPH_BASE)); //SRAM->peripheral
	LCD_DMA_TD=CyDmaTdAllocate();
    CyDmaTdSetAddress(LCD_DMA_TD,LO16((uint32)LCD_linebuffer),LO16(LCD_dp__F0_REG)); //from LCD_linebuffer to LCD's F0 register
    CyDmaTdSetConfiguration(LCD_DMA_TD,sizeof LCD_linebuffer,CY_DMA_DISABLE_TD,TD_INC_SRC_ADR); //disable TD after completion
	CyDmaChPriority(LCD_DMA_ch,0); //ensure highest DMA priority (cannot intefere with camera's DMA since they happen at different times)
}

void CaptureFrame()
{
    uint8 cs=CS_Read();
    uint8 oe=OE_Read();
    
    Camera_Threshold_Control=display_mode==THRESHOLDED; //control reg chooses whether image data or colour detection FIFO is enabled
    
    if(display_mode==HISTOGRAM)
    {
        memset(hist,0,sizeof hist); //clear histogram before capturing
        LCD_SetWindowWrite(0,0,223,223); //histogram uses a 224x224 window (32x32 histogram; each bin is 7x7 pixels)
    }
    else LCD_SetWindowWrite(0,0,319,239); //set window to full frame 320x240
    
    while(!LCD_Empty); //wait until command has finished before disabling bus output
    OE_Control=0;
    
    while(!Camera_VSYNC_Read());
    //Camera_SyncFrame(); //wait until start of next frame before capturing
    
    CS_Write(0); //selecting camera will automatically enable its interrupts
    Camera_SyncFrame(); //block until frame is fully captured
    CS_Write(3); //select LCD
    
    if(display_mode==HISTOGRAM) //display histogram on the LCD
    {
        OE_Control=1;
        int U,V,a,b;
        for(V=0;V<32;V++) for(a=0;a<7;a++) for(U=0;U<32;U++) for(b=0;b<7;b++)
        {
            pixel p;
            int h=hist[U][V];
            //h*=2; //optional scaling
            h=h>0xff?0xff:h; //saturate to 255
            p.R=p.G=p.B=h;
            
            //colour in regions that would be thresholded
            U<<=3;
            V<<=3;
            if(U<Camera_R_U&&V>=Camera_R_V) p.G=p.B=0;
            else if(U<Camera_G_U&&V<Camera_G_V) p.R=p.B=0;
            else if(U>=Camera_B_U&&V<Camera_B_V) p.R=p.G=0;
            else if(U>=Camera_M_U&&V>=Camera_M_V) p.G=0;
            U>>=3;
            V>>=3;
            
            LCD_WritePixel(p);
        }
    }
    
    LCD_StopReadWrite();
    
    OE_Control=oe; //restore original output enable
    CS_Write(cs); //restore original chip select
}

void Camera_SetBlankTime(uint16 time)
{
    time&=0x7ff; //limit to 11 bits
    Camera_WriteReg(0x2a,time>>8<<4);
    Camera_WriteReg(0x2b,time);
}

void Camera_SetThresholds(int8 redU,int8 redV,int8 greenU,int8 greenV,int8 blueU,int8 blueV,int8 magentaU,int8 magentaV)
{
    //Inputs are signed, but camera gives unsigned U and V (offset by 128)
    Camera_R_SetThresholds(redU+128,redV+128);
    Camera_G_SetThresholds(greenU+128,greenV+128);
    Camera_B_SetThresholds(blueU+128,blueV+128);
    Camera_M_SetThresholds(magentaU+128,magentaV+128);
}

void Camera_AutoEGWB()
{
    Camera_WriteReg(0x13,0xe7);
}

void Camera_SetEGWB(uint16 exposure,uint8 gain,uint8 red_gain,uint8 blue_gain)
{
    Camera_WriteReg(0x13,0xe0);
    
    Camera_WriteReg(0,gain);
    Camera_WriteReg(1,blue_gain);
    Camera_WriteReg(2,red_gain);
    Camera_WriteReg(4,exposure&3);
    Camera_WriteReg(0x10,exposure>>2);
    Camera_WriteReg(0xa1,0x40|exposure>>10);
}
