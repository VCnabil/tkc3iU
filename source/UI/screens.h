//------------------------------------------------------------------------------
//  TITLE :          screens.h
//  DESCRIPTION :    Routines for screen creation and navigation between them.
//------------------------------------------------------------------------------
#ifndef __SCREENS_H__
#define __SCREENS_H__

#include "project.h"

/// @defgroup screens Screens Functions
/// Functions for handling the Screens.
/// @{

// Uncomment this to enable frames per second counter display
//#define ENABLE_FPS_COUNTER

/// Ids of all the screens within the application
typedef enum
{
    SCREENID_START,
    SCREENID_SYSOPTS,
    SCREENID_TEST,
    SCREENID_FAULTS,
    SCREENID_ABOUT,
    SCREENID_ZEROTHRUST,
    SCREENID_CALIBRATION,
    SCREENID_AUTOCAL,
    SCREENID_PASSCODE,
    SCREENID_CENTRALALARM,
    SCREENID_ALARMSUMMARY,
/// Must be last!
	SCREENID_MAX
} SCREENID_T;

//------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//------------------------------------------------------------------------------

/// @brief Registers and initializes all the screens
void ScreensInit(void);

/// @brief Set the default key bind for all screens
void ScreensSetupDefaultKeys(void);

/// @} // endgroup screens

#endif // #ifndef __SCREENS_H__