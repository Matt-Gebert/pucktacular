#ifndef LCD_H
#define LCD_H
#include<project.h>

//Send command to LCD (RS=0)
#define LCD_Command(c) (*(reg16*)LCD_dp__F0_F1_REG=c|1<<8)

//Send data to LCD (RS=1)    
#define LCD_Data(c) (*(reg16*)LCD_dp__F0_F1_REG=(uint8)c)

//Is LCD block ready to receive another command/data?
#define LCD_Ready (*(reg8*)LCD_FIFO_Status__STATUS_REG&0x1)

//Has LCD block emptied its command/data FIFO?    
#define LCD_Empty (*(reg8*)LCD_FIFO_Status__STATUS_REG&0x2)

//Pixel format (only top 6 bits of each byte are used)
typedef struct
{
    uint8 R,G,B;
} pixel;

//Initialise LCD
void LCD_Start();

//Write value to LCD's register
void LCD_WriteReg(uint8 reg,uint8 value);

//Write n bytes from values array to LCD's register (uint8 values[n])
void LCD_WriteArray(uint8 reg,uint8 *values,uint8 n);

//Set window for reading or writing from/to
void LCD_SetWindow(uint16 col_start,uint16 row_start,uint16 col_end,uint16 row_end);

//Set window and start reading/writing. Both functions leave CS at 3 (LCD selected).
//SetWindowRead leaves bus output disabled
//SetWindowWrite leaves bus output enabled
void LCD_SetWindowRead(uint16 col_start,uint16 row_start,uint16 col_end,uint16 row_end);
void LCD_SetWindowWrite(uint16 col_start,uint16 row_start,uint16 col_end,uint16 row_end);

//Read pixel
pixel LCD_ReadPixel();

//Write pixel
void LCD_WritePixel(pixel p);

//Stop reading or writing
void LCD_StopReadWrite();

#endif
