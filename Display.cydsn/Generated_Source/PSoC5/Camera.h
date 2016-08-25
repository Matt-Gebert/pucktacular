#ifndef Camera_H
#define Camera_H
#include <project.h>

//Synchronise to rising edge of VSYNC
//ensures alignment of frame in memory
//this function is blocking
void Camera_SyncFrame();

//Write a value to one of the camera's registers
void Camera_WriteReg(const uint8 reg,const uint8 value);

//Read a value from one of the camera's registers
uint8 Camera_ReadReg(const uint8 reg);

//Initialise the camera
void Camera_Start();

uint32 Camera_linebuffer[160];
extern void Camera_end_line(); //external interrupt for end of line

#endif
