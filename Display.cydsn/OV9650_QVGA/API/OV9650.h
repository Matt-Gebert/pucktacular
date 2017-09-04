#ifndef `$INSTANCE_NAME`_H
#define `$INSTANCE_NAME`_H
#include <project.h>

//Synchronise to rising edge of VSYNC
//ensures alignment of frame in memory
//this function is blocking
void `$INSTANCE_NAME`_SyncFrame();

//Write a value to one of the camera's registers
void `$INSTANCE_NAME`_WriteReg(const uint8 reg,const uint8 value);

//Read a value from one of the camera's registers
uint8 `$INSTANCE_NAME`_ReadReg(const uint8 reg);

//Initialise the camera
void `$INSTANCE_NAME`_Start();

uint32 `$INSTANCE_NAME`_linebuffer[160];
extern void `$INSTANCE_NAME`_end_line(); //external interrupt for end of line

#endif
