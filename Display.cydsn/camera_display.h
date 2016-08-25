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