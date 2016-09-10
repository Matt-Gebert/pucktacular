#include<project.h>

//Captures a frame from the camera into the LCD framebuffer
//Blocks until full frame is captured
void CaptureFrame();

//Set the horizontal blanking for the camera
//Shorter times give higher frame rates
//If the time is too short, the image will be corrupted
//Maximum value is 2047
void Camera_SetBlankTime(uint16 time);

//Initialise the DMA block that transfers pixel data to the display
void LCD_DMA_Start();

//Choose which image to display on LCD
enum
{
    IMAGE,
    HISTOGRAM,
    THRESHOLDED
} display_mode;

//Set thresholds for the 4 corners of the histogram
//These are signed U and V values between -128 and +127
//Neutral colours (black, white, and greys) have U=V=0
void Camera_SetThresholds(int8 redU,int8 redV,int8 greenU,int8 greenV,int8 blueU,int8 blueV,int8 magentaU,int8 magentaV);

//Let camera automatically adjust exposure, gain, and white balance
void Camera_AutoEGWB();

//Set custom exposure/gain/white balance
void Camera_SetEGWB(uint16 exposure,uint8 gain,uint8 red_gain,uint8 blue_gain);