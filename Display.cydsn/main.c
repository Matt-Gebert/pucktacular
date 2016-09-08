#include <project.h>
#include "camera_display.h"
#include "claw_functions.h"
#include "movement_functions_unofficial.h"
//*************************************************
//
//Function prototypes
//
//*************************************************   
    void PSOCReset();
    void ISRSetUp(); 
    void VariablesInitialise();
    void InitialisationSequnce();
    void LEDFlash();
    void PWMOperate();
    void Beep(int a);
    void BiDirPortInPut();
    void BiDirPortOutPut();
    void ISR1Handler(); 
//*************************************************
//
//RAM variables
//
//*************************************************    
    int a;
    int b;
    int c;
    int AD0Data;
    int OnOff;
//*************************************************
//
//Main program starts here
//Added Line :)
//
//************************************************* 
int main()
{
    PSOCReset();                                    //Put PSOC in ready state
    VariablesInitialise();                          //Initialise all variables    
    ISRSetUp();                                     //Setup all interupts
    LCD_Start();
    LCD_DMA_Start();
    Camera_Start();
    Camera_WriteReg(0x41,0x02);                     //double colour matrix (more saturation)
    Camera_SetBlankTime(600);                       //increase blanking time if image is corrupted; range is 0-2047 (I used 600 for debug build and 500 for release build)
    
    LCD_CLK_SetDividerValue(5);
    CyGlobalIntEnable;                              //interrupts must be enabled for camera to work
    
    Beep(1);
    CyDelay(200);
    Beep(1); 
    while(OnOff==0)
    {
    }
    InitialisationSequnce();
    //Intialisation of PWM
    PWM_Pan_Enable();
    PWM_Pan_Start();
    PWM_Tilt_Enable();
    PWM_Tilt_Start();
    PWM_Claw_Enable();
    PWM_Claw_Start();
    PWM_Lift_Enable();
    PWM_Lift_Start();
       
    uint8 n=0;
    for(;;n++)
    {
        PanRight();
        CyDelay(200);
        ClawOpen();
        CyDelay(200);
        ClawClose();
        CyDelay(200);
        LiftTop();
        CyDelay(500);
        LiftGround();
        CyDelay(500);
        PanMid();
        CyDelay(200);
        if (n%2) TiltStraight();
        else TiltDown();
        CyDelay(500);
        TiltUp();
        CyDelay(500);

    }
}
//*************************************************
//
//Put 8 bit port in output mode
//
//*************************************************
void BiDirPortOutPut()
{
    OE_Control=3;                           //enable output driver and switch to user output
}
//************************************************
//
//Put 8 bit port in input mode
//
//*************************************************
void BiDirPortInPut()
{
   OE_Control=0;                            //disable output driver                    
}
//*************************************************
//
// Beep for 100mS minimum
// On entry X contains quantity of 100mS beeps
//
//*************************************************
void Beep(int x) 
{
    BiDirPortOutPut();
    for(;x>0;x--)
    {
        Data_Out_Write(0x03);      //Turn beeper on
        CS_Write(0x02);  
        CS_Write(0x08);
        CyDelay(100);
    }
     Data_Out_Write(0x01);      //Turn beeper off
     CS_Write(0x02);  
     CS_Write(0x08);   
}
//************************************************
//
// Do a few things to wake up robot
//
//*************************************************
void InitialisationSequnce()
{
    Beep(2);                         //Beep 4 times
    CyDelay(400);
    for(a=0;a<3;a++)                //Flash LED 5 times
    {
        LEDFlash();
    }
    for(a=0;a<3;a++)                //Flash headlights 3 times
    {
        BiDirPortOutPut();
        Data_Out_Write(0x09);       //HeadLights on
        CS_Write(0x02);  
        CS_Write(0x08);
        CyDelay(100);
        Data_Out_Write(0x01);      //Headlights off
        CS_Write(0x02);  
        CS_Write(0x08);
        CyDelay(100);
    }
}
//************************************************************
//
// Turn LED on for 100mS 
// 
//************************************************************
void LEDFlash() 
{
	BiDirPortOutPut();
    Data_Out_Write(0x09);      //Set bit 2 high
    CS_Write(0x02);  
    CS_Write(0x08);
    CyDelay(100);
    Data_Out_Write(0x01);      //Set bit 2 low
    CS_Write(0x02);  
    CS_Write(0x08); 
}
//************************************************
//
//Set up PSOC in the correct state
//
//*************************************************
void PSOCReset()
{
    CS_Write(0x08); 
    RST_Write(0);
    CyDelay(700);
    RST_Write(1);
    CyDelay(700);
    RST_Write(0);
    CyDelay(700);
    RST_Write(1);
} 
//*************************************************
//
// ISR Set Up all interupts as required
//
//*************************************************
void ISRSetUp()  
{
    isr_1_ClearPending();                          
    isr_1_StartEx(ISR1Handler);                     //for switch 2
} 
//*************************************************
//
//ISR1 Handler for switch. Interupt comes here when switch is pushed
//
//*************************************************
void ISR1Handler()  
{
    if(OnOff==0)
    {
        OnOff=1;
    }
    else
    {
        OnOff=0;
    }
}
//*************************************************
//
//Initialise all necessary variables
//
//*************************************************
 void VariablesInitialise()
{
   OnOff=0;
}