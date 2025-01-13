//------------------------------------------------------------------------------
//  TITLE :        	VCIncShared.cpp 
//  DESCRIPTION :	For Global variables 
//  AUTHOR:			Nabil Lamriben 1/10/2025
//------------------------------------------------------------------------------
 #include "VCInc.h"
#include <stdarg.h>
#include <stdio.h>

// Provide the actual definition (storage) for these globals:
int gPVCICallCount = 0;
int gJ1939CallCount = 0;      // Definition with initial value = 0


// Example: Initialize shared vector
std::vector<std::string> dbElementStrings(DATABASE_MAX_VECTORVARS, "Unknown");

char gDebugMsg[DEBUG_MSG_MAX_LENGTH] = { 0 };

// Helper function to format debug messages
void SetDebugMessage(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(gDebugMsg, DEBUG_MSG_MAX_LENGTH, format, args);
    va_end(args);
}

// Provide the actual storage definition for m_FAULTS_DB[]
extern FAULTS_DB m_FAULTS_DB[] = {

 { STA1, 0, false, "Idle Knob" },
    { STA1, 1, false, "Helm / Tiller" },
    { STA1, 2, false, "Stbd Lever" },
    { STA1, 3, false, "Port Lever" },
    { STA1, 4, false, "Joystick Y-axis" },
    { STA1, 5, false, "Joystick X-axis" },

    { STA2, 0, false, "Idle Knob" },
	{ STA2, 1, false, "Helm / Tiller" },
	{ STA2, 2, false, "Stbd Lever" },
	{ STA2, 3, false, "Port Lever" },
	{ STA2, 4, false, "Joystick Y-axis" },
	{ STA2, 5, false, "Joystick X-axis" },

	{ STA3, 0, false, "Idle Knob" },
	{ STA3, 1, false, "Helm / Tiller" },
	{ STA3, 2, false, "Stbd Lever" },
	{ STA3, 3, false, "Port Lever" },
	{ STA3, 4, false, "Joystick Y-axis" },
	{ STA3, 5, false, "Joystick X-axis" },

	{ NFU, 0, false, "Stbd Bucket NFU" },
	{ NFU, 1, false, "Port Bucket NFU" },
	{ NFU, 2, false, "Stbd Nozzle NFU" },
	{ NFU, 3, false, "Port Nozzle NFU" },
	{ NFU, 4, false, "Stbd Trim Tab / INT NFU" },
	{ NFU, 5, false, "Port Trim Tab / INT NFU" },

	{ SFE, 0, false, "Stbd Bucket feedback" },
	{ SFE, 1, false, "Port Bucket feedback" },
	{ SFE, 2, false, "Stbd Nozzle feedback" },
	{ SFE, 3, false, "Port Nozzle feedback" },
	{ SFE, 4, false, "Stbd Trim Tab / INT feedback" },
	{ SFE, 5, false, "Port Trim Tab / INT feedback" },

	{ CFE, 0, false, "Calibration Fault" },
	{ GAL, 0, false, "General Alarm" }
};