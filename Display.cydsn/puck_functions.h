/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <project.h>
#include <stdbool.h>

bool PuckCloseAquire(uint8 clr, bool path);
bool PuckFarAquire(uint8 clr);
bool PuckCloseScan(uint8 clr);
bool PuckFarScan(uint8 clr);
bool PuckCanCollect(uint8 clr, bool path);
bool PuckFindEndzone();
void PuckAquire(uint8 clr, bool path);
void PuckPositionToStack(uint8 clr);
bool PuckPositionToStack2(uint8 clr);
void PuckResetAngleTotal();
/* [] END OF FILE */