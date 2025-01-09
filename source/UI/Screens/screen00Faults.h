//------------------------------------------------------------------------------
//  TITLE :				screen00Faults.h
//  DESCRIPTION :		Screen 00 Faults drawing functions.
//  AUTHOR :			Nabil Lamriben 1/07/2025
//------------------------------------------------------------------------------
#ifndef __SCREEN00FAULTS_H__
#define __SCREEN00FAULTS_H__

#include "project.h"

/// @addtogroup screens
/// @{

/// Called once when the screen is entered.
void Scrn00FaultsEnter(void);

/// Called to redraw the entire screen.
void Scrn00FaultsCreate(void);

/// Drawing Function. 
/// Called every frame.
void Scrn00FaultsUpdate(void);

/// Called when exiting a screen.
void Scrn00FaultsExit(void);

/// @} // endgroup screens

#endif // #ifndef __SCREEN00FAULTS_H__
