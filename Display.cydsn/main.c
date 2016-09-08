#include <project.h>
#include "camera_display.h"

int main()
{
    CS_Write(2); //select output latch
    OE_Control=3; //enable output driver and switch to user output
    Data_Out_Control=0; //write to user output data bus
    CS_Write(8); //deselect output latch to clock in data
    OE_Control=0; //disable output driver
    
    SW_Start();
    
    LCD_Start();
    LCD_DMA_Start();

    Camera_Start();
    Camera_WriteReg(0x41,0x02); //double colour matrix (more saturation)
    Camera_SetBlankTime(1000); //increase blanking time if image is corrupted; range is 0-2047
    
    CyGlobalIntEnable; //interrupts must be enabled for camera to work
    
    uint8 n=0;
    display_mode=IMAGE; //start displaying image
    uint8 buttons_old=0xff; //assume buttons have not been pressed
    
    Camera_SetEGWB(80,0,128,128); //set exposure, gain and white balance
    Camera_SetThresholds(-32,64,0,-64,48,-32,-16,32); //set thresholds for the 4 colours
    
    for(;;n++)
    {
        uint8 buttons=Buttons_Status;
        if(buttons&~buttons_old&2) //right button switches between display modes (IMAGE, HISTROGRAM, THRESHOLDED)
        {
            display_mode++;
            if(display_mode>THRESHOLDED) display_mode=IMAGE;
        }
        buttons_old=buttons;
        
        CaptureFrame(); //read frame into LCD
        
         //toggle light every frame
        CS_Write(2); //select output latch
        OE_Control=3; //enable output driver and switch to user output
        Data_Out_Control=n&1?4:0; //write to user output data bus
        CS_Write(8); //deselect output latch to clock in data
        OE_Control=0; //disable output driver
        
//        //read top 100x100 pixels into array
//        pixel box[100][100];
//        LCD_SetWindowRead(0,0,99,99);
//        uint8 i,j;
//        for(i=0;i<100;i++) for(j=0;j<100;j++)
//            box[i][j]=LCD_ReadPixel();
//        LCD_StopReadWrite();
//                
//        //write array back into bottom corner
//        LCD_SetWindowWrite(220,140,319,239);
//        for(i=0;i<100;i++) for(j=0;j<100;j++) LCD_WritePixel(box[i][j]);
//        LCD_StopReadWrite();
//        
//        CyDelay(300);
    }
}
