#include <project.h>
#include "camera_display.h"
#include "camera_functions.h"
#include "movement_functions.h"
#include "claw_functions.h"


void LastResort();   
void Initialise();
void Headlights();
void Beep(int x);
void BiDirPortOutPut();

int16 SE1, SE2,diffSE,diff1;
int SE1Tot=0;
int SE2Tot=0;


int main()
{
    CS_Write(2); //select output latch
    OE_Control=3; //enable output driver and switch to user output
    Data_Out_Control=0; //write to user output data bus
    CS_Write(8); //deselect output latch to clock in data
    OE_Control=0; //disable output driver
    
    SW_Start();
    
    LCD_Start();
    LCD_DMA_Start();

    Camera_Start();
    Camera_WriteReg(0x41,0x02); //double colour matrix (more saturation)
    Camera_SetBlankTime(1000); //increase blanking time if image is corrupted; range is 0-2047
    
    CyGlobalIntEnable; //interrupts must be enabled for camera to work
    
    uint8 n=0;
    display_mode=THRESHOLDED; //start displaying image
    //uint8 buttons_old=0xff; //assume buttons have not been pressed
    
    Camera_SetEGWB(80,0,128,128); //set exposure, gain and white balance
    Camera_SetThresholds(-32,64,0,-64,48,-32,-16,32); //set thresholds for the 4 colours
    
    int16 count=0;
    Initialise();
    CyDelay(3000);
    
    for(;;n++)
    {
        /*uint8 buttons=Buttons_Status;
        if(buttons&~buttons_old&2) //right button switches between display modes (IMAGE, HISTROGRAM, THRESHOLDED)
        {
            display_mode++;
            if(display_mode>THRESHOLDED) display_mode=IMAGE;
        }
        buttons_old=buttons;
        */
        
        CaptureFrame(); //read frame into LCD
        CamAnalyseSequence();
        
        CyDelay(3000);
        
         //toggle light every frame
        CS_Write(2); //select output latch
        OE_Control=3; //enable output driver and switch to user output
        Data_Out_Control=n&1?4:0; //write to user output data bus
        CS_Write(8); //deselect output latch to clock in data
        OE_Control=0; //disable output driver
        
        
        Beep(1);
    }
}

void Initialise(){
    Quad_1_Start();
    Quad_2_Start();
    PWM_Pan_Start();
    PWM_Tilt_Start();
    PWM_Claw_Start();
    PWM_Lift_Start();
}

void Headlights(){
    CS_Write(2);                    //Bus address set to LatchDevices {Hbridge, LEDG, Buzzer etc.}
    OE_Control=3;
    Data_Out_Control=0x9;          //Writes 1001 to activate the LEDs
    CS_Write(8);                    //Bus address deactivated.
    OE_Control=0;
}

void LastResort(){
    int i;
    for(i=0;i<40;i++){ // change to i<3 for arena
    Quad_1_SetCounter(0);
    Quad_2_SetCounter(0);
    MovementForward(500);
    SE1=Quad_1_GetCounter();
    SE2=Quad_2_GetCounter();
    SE1Tot=SE1Tot+SE1;
    SE2Tot=SE2Tot+SE2;
    diffSE=SE2-SE1;
    diff1=SE2;
    //1000*diffSE/diff1
    MovementRight(500*diffSE/diff1);
    }
    ClawClose();
    CyDelay(200);
    LiftHalf();
    MovementRight90();
    MovementRight90();
    
    for(i=0;i<40;i++){ // change to i>3 for arena
    Quad_1_SetCounter(0);
    Quad_2_SetCounter(0);
    MovementForward(500);
    SE1=Quad_1_GetCounter();
    SE2=Quad_2_GetCounter();
    SE1Tot=SE1Tot+SE1;
    SE2Tot=SE2Tot+SE2;
    diffSE=SE2-SE1;
    diff1=SE2;
    //1000*diffSE/diff1
    MovementRight(500*diffSE/diff1);
    }
    LiftGround();
    CyDelay(200);
    ClawOpen();
    MovementBackward(1500);
    MovementRight90();
    MovementRight90();
}

void BiDirPortOutPut()
{
    OE_Control=3;                           //enable output driver and switch to user output
}

void Beep(int x) 
{
    BiDirPortOutPut();
    for(;x>0;x--)
    {
        Data_Out_Write(0x03);      //Turn beeper on
        CS_Write(0x02);  
        CS_Write(0x08);
        CyDelay(10);
    }
     Data_Out_Write(0x01);      //Turn beeper off
     CS_Write(0x02);  
     CS_Write(0x08);   
}