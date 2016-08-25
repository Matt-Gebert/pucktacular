#include<project.h>

static uint8 LCD_linebuffer[320*3];

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
    static uint32 y=0;
    if(y++) disp_line(); //don't display first line (not converted yet)
    convert_line(); //conversion starts before start of next line (DMA won't catch up if conversion is faster than capture)
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
    
    Camera_SyncFrame(); //wait until start of next frame before capturing
    LCD_SetWindowWrite(0,0,319,239); //set window to full frame 320x240
    while(!LCD_Empty); //wait until command has finished before disabling bus output
    OE_Control=0;
    CS_Write(0); //selecting camera will automatically enable its interrupts
    Camera_SyncFrame(); //block until frame is fully captured
    CS_Write(3); //select LCD
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