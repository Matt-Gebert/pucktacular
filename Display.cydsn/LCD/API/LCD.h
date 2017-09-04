#ifndef `$INSTANCE_NAME`_H
#define `$INSTANCE_NAME`_H
#include<project.h>

//Send command to LCD (RS=0)
#define `$INSTANCE_NAME`_Command(c) (*(reg16*)`$INSTANCE_NAME`_dp__F0_F1_REG=c|1<<8)

//Send data to LCD (RS=1)    
#define `$INSTANCE_NAME`_Data(c) (*(reg16*)`$INSTANCE_NAME`_dp__F0_F1_REG=(uint8)c)

//Is LCD block ready to receive another command/data?
#define `$INSTANCE_NAME`_Ready (*(reg8*)`$INSTANCE_NAME`_FIFO_Status__STATUS_REG&0x1)

//Has LCD block emptied its command/data FIFO?    
#define `$INSTANCE_NAME`_Empty (*(reg8*)`$INSTANCE_NAME`_FIFO_Status__STATUS_REG&0x2)

//Pixel format (only top 6 bits of each byte are used)
typedef struct
{
    uint8 R,G,B;
} pixel;

//Initialise LCD
void `$INSTANCE_NAME`_Start();

//Write value to LCD's register
void `$INSTANCE_NAME`_WriteReg(uint8 reg,uint8 value);

//Write n bytes from values array to LCD's register (uint8 values[n])
void `$INSTANCE_NAME`_WriteArray(uint8 reg,uint8 *values,uint8 n);

//Set window for reading or writing from/to
void `$INSTANCE_NAME`_SetWindow(uint16 col_start,uint16 row_start,uint16 col_end,uint16 row_end);

//Set window and start reading/writing. Both functions leave CS at 3 (LCD selected).
//SetWindowRead leaves bus output disabled
//SetWindowWrite leaves bus output enabled
void `$INSTANCE_NAME`_SetWindowRead(uint16 col_start,uint16 row_start,uint16 col_end,uint16 row_end);
void `$INSTANCE_NAME`_SetWindowWrite(uint16 col_start,uint16 row_start,uint16 col_end,uint16 row_end);

//Read pixel
pixel `$INSTANCE_NAME`_ReadPixel();

//Write pixel
void `$INSTANCE_NAME`_WritePixel(pixel p);

//Stop reading or writing
void `$INSTANCE_NAME`_StopReadWrite();

#endif
