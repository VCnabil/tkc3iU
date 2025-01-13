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
MUTEXHANDLE_T gPVCICountMutex;

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

