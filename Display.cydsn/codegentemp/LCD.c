#include<project.h>

#define LCD_CS_Write     CS ## _Write
#define LCD_CS_Read      CS ## _Read
#define LCD_OE      OE ## _Control
#define LCD_D_PS       D ## _PS
#define LCD_LCD_RD_Write LCD_RD ## _Write

void LCD_Start()
{
    uint8 cs=LCD_CS_Read(); //read intial state to restore afterwards
    uint8 oe=LCD_OE;
    LCD_CS_Write(3); //select LCD
    LCD_OE=1; //enable data bus output
    
    LCD_Command(0x01); //software reset
    CyDelay(5);
    LCD_Command(0x11); //take out of sleep
    CyDelay(100);
    LCD_Command(0x29); //turn display on
    LCD_WriteReg(0x36,0xe8); //flip image horizontally and vertically; swap rows/columns; set to BGR drive mode}
    
    //gamma correction settings
    uint8 gamma_p[]={0x0F,0x31,0x2B,0x0C,0x0E,0x08,0x4E,0xF1,0x37,0x07,0x10,0x03,0x0E,0x09,0x00};
    uint8 gamma_n[]={0x00,0x0E,0x14,0x03,0x11,0x07,0x31,0xC1,0x48,0x08,0x0F,0x0C,0x31,0x36,0x0F};
    LCD_WriteArray(0xe0,gamma_p,sizeof gamma_p);
    LCD_WriteArray(0xe1,gamma_n,sizeof gamma_n);
    
    LCD_OE=oe; //restore output enable
    LCD_CS_Write(cs); //restore initial chip select
}

void LCD_WriteReg(uint8 reg,uint8 value)
{
    uint8 cs=LCD_CS_Read(); //read intial state to restore afterwards
    uint8 oe=LCD_OE;
    LCD_CS_Write(3); //select LCD
    LCD_OE=1; //enable data bus output
    
    while(!LCD_Ready);
    LCD_Command(reg);
    while(!LCD_Ready);
    LCD_Data(value);
    while(!LCD_Empty);
    
    LCD_OE=oe; //restore output enable
    LCD_CS_Write(cs); //restore initial chip select
}

void LCD_WriteArray(uint8 reg,uint8 *values,uint8 n)
{
    uint8 cs=LCD_CS_Read(); //read intial state to restore afterwards
    uint8 oe=LCD_OE;
    LCD_CS_Write(3); //select LCD
    LCD_OE=1; //enable data bus output
    
    while(!LCD_Ready);
    LCD_Command(reg);
    int i;
    for(i=0;i<n;i++)
    {
        while(!LCD_Ready);
        LCD_Data(values[i]);
    }
    while(!LCD_Empty);
    
    LCD_OE=oe; //restore output enable
    LCD_CS_Write(cs); //restore initial chip select
}

void LCD_SetWindow(uint16 col_start,uint16 row_start,uint16 col_end,uint16 row_end)
{
    uint8 cols[]={col_start>>8,col_start,col_end>>8,col_end}; //LCD uses big endian words
    uint8 rows[]={row_start>>8,row_start,row_end>>8,row_end};
    LCD_WriteArray(0x2a,cols,4);
    LCD_WriteArray(0x2b,rows,4);
}

void LCD_SetWindowRead(uint16 col_start,uint16 row_start,uint16 col_end,uint16 row_end)
{
    LCD_CS_Write(3); //select LCD
    LCD_OE=1; //enable data bus output
    
    LCD_SetWindow(col_start,row_start,col_end,row_end);
    LCD_Command(0x2e);
    while(!LCD_Empty); //wait for buffer to empty before turning off output
    LCD_OE=0; //disable drivers on output bus
    
    //dummy read
    LCD_LCD_RD_Write(0);
    CyDelayCycles(BCLK__BUS_CLK__MHZ/3); //delay for about 333ns (actually 355ns is required, but overhead in function calls accounts for it)
    LCD_LCD_RD_Write(1);
    CyDelayCycles(BCLK__BUS_CLK__MHZ/11); //delay for about 90ns
}

void LCD_SetWindowWrite(uint16 col_start,uint16 row_start,uint16 col_end,uint16 row_end)
{
    LCD_CS_Write(3); //select LCD
    LCD_OE=1; //enable data bus output

    LCD_SetWindow(col_start,row_start,col_end,row_end);
    LCD_Command(0x2c);
}

pixel LCD_ReadPixel()
{
    pixel p;
    LCD_LCD_RD_Write(0);
    CyDelayCycles(BCLK__BUS_CLK__MHZ/3); //delay for about 333ns (actually 355ns is required, but overhead in function calls accounts for it)
    p.R=LCD_D_PS;
    LCD_LCD_RD_Write(1);
    CyDelayCycles(BCLK__BUS_CLK__MHZ/11); //delay for about 90ns
    LCD_LCD_RD_Write(0);
    CyDelayCycles(BCLK__BUS_CLK__MHZ/3); //delay for about 333ns (actually 355ns is required, but overhead in function calls accounts for it)
    p.G=LCD_D_PS;
    LCD_LCD_RD_Write(1);
    CyDelayCycles(BCLK__BUS_CLK__MHZ/11); //delay for about 90ns
    LCD_LCD_RD_Write(0);
    CyDelayCycles(BCLK__BUS_CLK__MHZ/3); //delay for about 333ns (actually 355ns is required, but overhead in function calls accounts for it)
    p.B=LCD_D_PS;
    LCD_LCD_RD_Write(1);
    CyDelayCycles(BCLK__BUS_CLK__MHZ/11); //delay for about 90ns
    return p;
}

void LCD_WritePixel(pixel p)
{
    while(!LCD_Empty);
    LCD_Data(p.R);
    LCD_Data(p.G);
    LCD_Data(p.B);
}

void LCD_StopReadWrite()
{
    uint8 oe=LCD_OE;
    
    LCD_OE=1;
    LCD_Command(0);
    while(!LCD_Ready);
    
    LCD_OE=oe;
}