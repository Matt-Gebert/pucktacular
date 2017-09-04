/*
 * Copyright @Pucktacular, 2016
 * @Matt Gebert, Daniel Hranilovic & Kevin Duxbury
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
 *
 * Contains all ultrasonic related code
*/

#include <project.h>
#include <stdbool.h>

double Ultrasonics(uint8 sensor);
/*  
    Take input of 1 for left ultrasonic, other (0 or 2 used) for right
    Ouptus double which is distance as seen by ultrasonic sensor
*/
double UltrasonicsSensitive(uint8 sensor);
/*  
    Take input of 1 for left ultrasonic, other (0 or 2 used) for right
    Ouptus double which is distance as seen by ultrasonic sensor
    Works on faster clokc so should be more accurate, emergency if camera no good
*/


double Wall_Align(bool sense, bool sensors);
/*
    No input, will first gain readings from both ultrasonics 
    then straighten to wall on presion that varies with distance from wall
    Outputs distance from wall
*/

void MoveAlign(double distance, bool sense, bool sensors, float prec);
/*
    Input is desired final distance from wall to ultrasonic sensors
    Move perpendicular towards wall, until reach input distance (forwards & backwards)
    within specified precision (cm float).
*/


/* [] END OF FILE */
