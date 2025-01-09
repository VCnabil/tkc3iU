//------------------------------------------------------------------------------
// File:        settings.h
// Description: System settings.
//------------------------------------------------------------------------------

#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "project.h"
#include "VCInc.h" // <-- We include VCInc.h so we can use main_station, wing_station, etc.


/// @defgroup settings Settings Functions
/// Functions for handling the Settings.
/// @{

//------------------------------------------------------------------------------
// DEFINES
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// TYPES
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PUBLIC FUNCTION PROTOTYPES
//------------------------------------------------------------------------------

/// Initialize the settings
void SettingsInit(void);

/// Function to Load the settings and apply them.
void SettingsLoad(void);

/// Function to Save the current settings.
void SettingsSave(void);

 

/// Get the current state of the buzzer
///@returns TRUE if the buzzer is enabled, FALSE otherwise
BOOL SettingsIsBleepEnabled(void);

/// Toggles the Buzzer ON/OFF.
void SettingsToggleBleep(void);

/// Units related Functions

// Station Type
uint8_t SettingsGetStationType(void);
void SettingsSetStationType(uint8_t newStationType);
void SettingsToggleStationType(void* userData = nullptr);
// Data Mode
uint8_t SettingsGetDataMode(void);
void SettingsSetDataMode(uint8_t newDataMode);
void SettingsToggleDataMode(void);
// Nozzle Flip
uint8_t SettingsGetNozzleMapFlip(void);
void SettingsSetNozzleMapFlip(uint8_t newNozzleMapFlip);
void SettingsToggleNozzleMapFlip(void);

// Bucket Flip
uint8_t SettingsGetBucketMapFlip(void);
void SettingsSetBucketMapFlip(uint8_t newBucketMapFlip);
void SettingsToggleBucketMapFlip(void);

// Tab Flip
uint8_t SettingsGetTabMapFlip(void);
void SettingsSetTabMapFlip(uint8_t newTabMapFlip);
void SettingsToggleTabMapFlip(void);

// Indication Config
uint8_t SettingsGetIndicationConfig(void);
void SettingsSetIndicationConfig(uint8_t newConfig);
void SettingsToggleIndicationConfig(void);

// Comms Mode
uint8_t SettingsGetCommsMode(void);
void SettingsSetCommsMode(uint8_t newCommsMode);
void SettingsToggleCommsMode(void);
 

/// Load default settings and force a save
void load_eeprom_defaults(void);

/// @} // endgroup settings

#endif  // #ifndef __SETTINGS_H__
