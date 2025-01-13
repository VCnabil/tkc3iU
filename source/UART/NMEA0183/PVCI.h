//------------------------------------------------------------------------------
//  TITLE :        	PVCI.h
//  DESCRIPTION :	For Processing the  PVCI serial string and its variations
//  AUTHOR:			Nabil Lamriben 1/10/2025
//------------------------------------------------------------------------------
#ifndef __PVCI_H__
#define __PVCI_H__

#include <string>

// Function to process $PVCI string
void ProcessPVCI(const std::string& vcciString);
int NMEA0183_ProcessPVCI(char* pBuffer);

#endif // __PVCI_H__
