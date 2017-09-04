#include "Camera.h"

extern const uint8 Camera_settings[][2];
extern const uint8 Camera_format[];
extern const uint8 Camera_sxga[];
extern const uint8 Camera_vga[];
extern const uint8 Camera_qvga[];
extern const uint8 Camera_cif[];
extern const uint8 Camera_qcif[];

static uint8 DMA_channel,DMA_TD;

void Camera_WriteReg(const uint8 reg,const uint8 value)
{
	while(Camera_I2C_MasterSendStart(0x30,0)!=Camera_I2C_MSTR_NO_ERROR);
    Camera_I2C_MasterWriteByte(reg);
    Camera_I2C_MasterWriteByte(value);
    Camera_I2C_MasterSendStop();
}

uint8 Camera_ReadReg(const uint8 reg)
{
	while(Camera_I2C_MasterSendStart(0x30,0)!=Camera_I2C_MSTR_NO_ERROR);
    Camera_I2C_MasterWriteByte(reg);
    Camera_I2C_MasterSendStop();
	
	while(Camera_I2C_MasterSendStart(0x30,1)!=Camera_I2C_MSTR_NO_ERROR);
    uint8 value=Camera_I2C_MasterReadByte(Camera_I2C_NAK_DATA);
    Camera_I2C_MasterSendStop();
	return value;
}

void Camera_SyncFrame()
{
	while(Camera_VSYNC_Read());
	while(!Camera_VSYNC_Read());
}

void Camera_Start()
{
	//Camera_SIOD_SetDriveMode(Camera_SIOD_DM_RES_UP); //turn on pull-up resistors on I2C pins
	//Camera_SIOC_SetDriveMode(Camera_SIOC_DM_RES_UP);
	Camera_I2C_Start();
	
	Camera_WriteReg(0x12,0x80); //reset
	CyDelay(1);
	uint16 i;
	for(i=0;Camera_settings[i][0]!=0xff;i++) Camera_WriteReg(Camera_settings[i][0],Camera_settings[i][1]); //camera settings
	for(i=0;Camera_format[i]!=0xff;i++) Camera_WriteReg(Camera_format[i],Camera_qvga[i]); //qvga format (320x240)
	
	DMA_channel=Camera_DMA_DmaInitialize(1,1,HI16(CYDEV_PERIPH_BASE),HI16(CYDEV_SRAM_BASE)); //peripheral -> SRAM
	DMA_TD=CyDmaTdAllocate();
    CyDmaTdSetAddress(DMA_TD,LO16(Camera_FIFO_dp__F0_REG),LO16((uint32)Camera_linebuffer));
    CyDmaTdSetConfiguration(DMA_TD,sizeof(Camera_linebuffer),DMA_TD,TD_INC_DST_ADR|Camera_DMA__TD_TERMOUT_EN); //loop TDs
	CyDmaChPriority(DMA_channel,0); //ensure highest priority for DMA channel

    Camera_end_line_StartEx(Camera_end_line);
    
	*(reg8*)Camera_FIFO_dp__F0_REG;
	*(reg8*)Camera_FIFO_dp__F0_REG;
	*(reg8*)Camera_FIFO_dp__F0_REG;
	*(reg8*)Camera_FIFO_dp__F0_REG; //clear fifo
	CyDmaClearPendingDrq(DMA_channel); //invalidate pending requests
	CyDmaChSetInitialTd(DMA_channel,DMA_TD); //set initial TD
	CyDmaChEnable(DMA_channel,1); //enable channel (start streaming)
    
    
    
    Camera_R_Start();
    Camera_G_Start();
    Camera_B_Start();
    Camera_M_Start();
    
    DMA_channel=Camera_DMA_Colours_DmaInitialize(1,1,HI16(CYDEV_PERIPH_BASE),HI16(CYDEV_SRAM_BASE)); //peripheral -> SRAM
	DMA_TD=CyDmaTdAllocate();
    CyDmaTdSetAddress(DMA_TD,LO16(Camera_FIFO_Colours_dp__F0_REG),LO16((uint32)Camera_linebuffer));
    CyDmaTdSetConfiguration(DMA_TD,sizeof(Camera_linebuffer)/4,DMA_TD,TD_INC_DST_ADR|Camera_DMA__TD_TERMOUT_EN); //loop TDs
	CyDmaChPriority(DMA_channel,0); //ensure highest priority for DMA channel

    Camera_end_line_colours_StartEx(Camera_end_line);
    
	*(reg8*)Camera_FIFO_Colours_dp__F0_REG;
	*(reg8*)Camera_FIFO_Colours_dp__F0_REG;
    *(reg8*)Camera_FIFO_Colours_dp__F0_REG;
    *(reg8*)Camera_FIFO_Colours_dp__F0_REG; //clear fifo
	CyDmaClearPendingDrq(DMA_channel); //invalidate pending requests
	CyDmaChSetInitialTd(DMA_channel,DMA_TD); //set initial TD
	CyDmaChEnable(DMA_channel,1); //enable channel (start streaming)
}