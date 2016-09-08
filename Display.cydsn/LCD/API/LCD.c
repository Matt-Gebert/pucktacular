#include<project.h>

#define `$INSTANCE_NAME`_CS_Write     `$CS` ## _Write
#define `$INSTANCE_NAME`_CS_Read      `$CS` ## _Read
#define `$INSTANCE_NAME`_OE      `$Data_OE` ## _Control
#define `$INSTANCE_NAME`_D_PS       `$Data` ## _PS
#define `$INSTANCE_NAME`_LCD_RD_Write `$RD` ## _Write

void `$INSTANCE_NAME`_Start()
{
    uint8 cs=`$INSTANCE_NAME`_CS_Read(); //read intial state to restore afterwards
    uint8 oe=`$INSTANCE_NAME`_OE;
    `$INSTANCE_NAME`_CS_Write(3); //select LCD
    `$INSTANCE_NAME`_OE=1; //enable data bus output
    
    `$INSTANCE_NAME`_Command(0x01); //software reset
    CyDelay(5);
    `$INSTANCE_NAME`_Command(0x11); //take out of sleep
    CyDelay(100);
    `$INSTANCE_NAME`_Command(0x29); //turn display on
    `$INSTANCE_NAME`_WriteReg(0x36,0xe8); //flip image horizontally and vertically; swap rows/columns; set to BGR drive mode}
    
    //gamma correction settings
    uint8 gamma_p[]={0x0F,0x31,0x2B,0x0C,0x0E,0x08,0x4E,0xF1,0x37,0x07,0x10,0x03,0x0E,0x09,0x00};
    uint8 gamma_n[]={0x00,0x0E,0x14,0x03,0x11,0x07,0x31,0xC1,0x48,0x08,0x0F,0x0C,0x31,0x36,0x0F};
    `$INSTANCE_NAME`_WriteArray(0xe0,gamma_p,sizeof gamma_p);
    `$INSTANCE_NAME`_WriteArray(0xe1,gamma_n,sizeof gamma_n);
    
    `$INSTANCE_NAME`_OE=oe; //restore output enable
    `$INSTANCE_NAME`_CS_Write(cs); //restore initial chip select
}

void `$INSTANCE_NAME`_WriteReg(uint8 reg,uint8 value)
{
    uint8 cs=`$INSTANCE_NAME`_CS_Read(); //read intial state to restore afterwards
    uint8 oe=`$INSTANCE_NAME`_OE;
    `$INSTANCE_NAME`_CS_Write(3); //select LCD
    `$INSTANCE_NAME`_OE=1; //enable data bus output
    
    while(!`$INSTANCE_NAME`_Ready);
    `$INSTANCE_NAME`_Command(reg);
    while(!`$INSTANCE_NAME`_Ready);
    `$INSTANCE_NAME`_Data(value);
    while(!`$INSTANCE_NAME`_Empty);
    
    `$INSTANCE_NAME`_OE=oe; //restore output enable
    `$INSTANCE_NAME`_CS_Write(cs); //restore initial chip select
}

void `$INSTANCE_NAME`_WriteArray(uint8 reg,uint8 *values,uint8 n)
{
    uint8 cs=`$INSTANCE_NAME`_CS_Read(); //read intial state to restore afterwards
    uint8 oe=`$INSTANCE_NAME`_OE;
    `$INSTANCE_NAME`_CS_Write(3); //select LCD
    `$INSTANCE_NAME`_OE=1; //enable data bus output
    
    while(!`$INSTANCE_NAME`_Ready);
    `$INSTANCE_NAME`_Command(reg);
    int i;
    for(i=0;i<n;i++)
    {
        while(!`$INSTANCE_NAME`_Ready);
        `$INSTANCE_NAME`_Data(values[i]);
    }
    while(!`$INSTANCE_NAME`_Empty);
    
    `$INSTANCE_NAME`_OE=oe; //restore output enable
    `$INSTANCE_NAME`_CS_Write(cs); //restore initial chip select
}

void `$INSTANCE_NAME`_SetWindow(uint16 col_start,uint16 row_start,uint16 col_end,uint16 row_end)
{
    uint8 cols[]={col_start>>8,col_start,col_end>>8,col_end}; //LCD uses big endian words
    uint8 rows[]={row_start>>8,row_start,row_end>>8,row_end};
    `$INSTANCE_NAME`_WriteArray(0x2a,cols,4);
    `$INSTANCE_NAME`_WriteArray(0x2b,rows,4);
}

void `$INSTANCE_NAME`_SetWindowRead(uint16 col_start,uint16 row_start,uint16 col_end,uint16 row_end)
{
    `$INSTANCE_NAME`_CS_Write(3); //select LCD
    `$INSTANCE_NAME`_OE=1; //enable data bus output
    
    `$INSTANCE_NAME`_SetWindow(col_start,row_start,col_end,row_end);
    `$INSTANCE_NAME`_Command(0x2e);
    while(!`$INSTANCE_NAME`_Empty); //wait for buffer to empty before turning off output
    `$INSTANCE_NAME`_OE=0; //disable drivers on output bus
    
    //dummy read
    `$INSTANCE_NAME`_LCD_RD_Write(0);
    CyDelayCycles(BCLK__BUS_CLK__MHZ/3); //delay for about 333ns (actually 355ns is required, but overhead in function calls accounts for it)
    `$INSTANCE_NAME`_LCD_RD_Write(1);
    CyDelayCycles(BCLK__BUS_CLK__MHZ/11); //delay for about 90ns
}

void `$INSTANCE_NAME`_SetWindowWrite(uint16 col_start,uint16 row_start,uint16 col_end,uint16 row_end)
{
    `$INSTANCE_NAME`_CS_Write(3); //select LCD
    `$INSTANCE_NAME`_OE=1; //enable data bus output

    `$INSTANCE_NAME`_SetWindow(col_start,row_start,col_end,row_end);
    `$INSTANCE_NAME`_Command(0x2c);
}

pixel `$INSTANCE_NAME`_ReadPixel()
{
    pixel p;
    `$INSTANCE_NAME`_LCD_RD_Write(0);
    CyDelayCycles(BCLK__BUS_CLK__MHZ/3); //delay for about 333ns (actually 355ns is required, but overhead in function calls accounts for it)
    p.R=`$INSTANCE_NAME`_D_PS;
    `$INSTANCE_NAME`_LCD_RD_Write(1);
    CyDelayCycles(BCLK__BUS_CLK__MHZ/11); //delay for about 90ns
    `$INSTANCE_NAME`_LCD_RD_Write(0);
    CyDelayCycles(BCLK__BUS_CLK__MHZ/3); //delay for about 333ns (actually 355ns is required, but overhead in function calls accounts for it)
    p.G=`$INSTANCE_NAME`_D_PS;
    `$INSTANCE_NAME`_LCD_RD_Write(1);
    CyDelayCycles(BCLK__BUS_CLK__MHZ/11); //delay for about 90ns
    `$INSTANCE_NAME`_LCD_RD_Write(0);
    CyDelayCycles(BCLK__BUS_CLK__MHZ/3); //delay for about 333ns (actually 355ns is required, but overhead in function calls accounts for it)
    p.B=`$INSTANCE_NAME`_D_PS;
    `$INSTANCE_NAME`_LCD_RD_Write(1);
    CyDelayCycles(BCLK__BUS_CLK__MHZ/11); //delay for about 90ns
    return p;
}

void `$INSTANCE_NAME`_WritePixel(pixel p)
{
    while(!`$INSTANCE_NAME`_Empty);
    `$INSTANCE_NAME`_Data(p.R);
    `$INSTANCE_NAME`_Data(p.G);
    `$INSTANCE_NAME`_Data(p.B);
}

void `$INSTANCE_NAME`_StopReadWrite()
{
    uint8 oe=`$INSTANCE_NAME`_OE;
    
    `$INSTANCE_NAME`_OE=1;
    `$INSTANCE_NAME`_Command(0);
    while(!`$INSTANCE_NAME`_Ready);
    
    `$INSTANCE_NAME`_OE=oe;
}