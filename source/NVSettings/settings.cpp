//------------------------------------------------------------------------------
//  TITLE :          settings.c
//------------------------------------------------------------------------------

#include "project.h"
static void _SettingsLoadDefaults(void);

#define CRC_START_VALUE 0x1D0F

// This is the structure for storing parameters in EEPROM.
typedef struct
{
	///////////////////////////////////////////////////////////////////////////
	// SYSTEM SECTION - DO NOT MODIFY - THESE 2 ENTRIES _MUST_ BE FIRST!
	///////////////////////////////////////////////////////////////////////////
	uint32_t settingsCRC;
	uint32_t settingsSaveCount;

	///////////////////////////////////////////////////////////////////////////
	// Default User Settings
	///////////////////////////////////////////////////////////////////////////
 
	// Key bleep on/off
	BOOL isBuzzerMuted;

	///////////////////////////////////////////////////////////////////////////
	// You _MUST_ add any new settings to be saved _AFTER_ this comment...
	///////////////////////////////////////////////////////////////////////////

	 

} SETTINGS_T;

//------------------------------------------------------------------------------
// MODULE GLOBALS
//------------------------------------------------------------------------------

// Instances of settings structure
static SETTINGS_T m_settings;
static const void * m_crcStartingPoint = (char*)&m_settings.settingsCRC + sizeof(m_settings.settingsCRC);
static const uint32_t m_crcLength = sizeof(m_settings) - sizeof(m_settings.settingsCRC);

//------------------------------------------------------------------------------
// LOCAL FUNCTIONS
//------------------------------------------------------------------------------

static void SettingsSaveCallback(void* pUserData = nullptr);

static void SettingsSaveCallback(void* pUserData)
{
	(void)pUserData;
	SettingsSave();
}

//------------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//------------------------------------------------------------------------------

void SettingsInit(void)
{
	// Register a 1 minute timer to automatically save the settings
	timer_register(SettingsSaveCallback, nullptr, 1000 * 60, 1000 * 60);

	// Load the settings
	SettingsLoad();
}

void SettingsLoad(void)
{
	if (eepromRead(EEPROMSimulated, 0, (uint8_t *)&m_settings, sizeof(m_settings)) == 0)
	{
		m_settings.settingsSaveCount = 0;
		load_eeprom_defaults();
	}
	else
	{
		if (m_settings.settingsCRC != crc16(CRC_START_VALUE, m_crcStartingPoint, m_crcLength))
		{
			// CRC Failed.
			m_settings.settingsSaveCount = 0;
			load_eeprom_defaults();
		}
	}

	// Initialise the key press beep state from settings
	buzzer_mute(m_settings.isBuzzerMuted);
}

void SettingsSave(void)
{
	uint16_t settingsCRC = crc16(CRC_START_VALUE, m_crcStartingPoint, m_crcLength);
	uint16_t savedDataCRC = 0;

	SETTINGS_T currentSavedData;

	uint32_t bytesRead = eepromRead(EEPROMSimulated, 0, (uint8_t *)&currentSavedData, sizeof(currentSavedData));

	if (bytesRead != 0)
	{
		savedDataCRC = currentSavedData.settingsCRC;
	}

	if (savedDataCRC != settingsCRC || bytesRead == 0)
	{
		// CRC's are different, save the data.
		m_settings.settingsSaveCount++;
		m_settings.settingsCRC = crc16(CRC_START_VALUE, m_crcStartingPoint, m_crcLength);
		eepromWrite(EEPROMSimulated, 0, (uint8_t *)&m_settings, sizeof(m_settings));
	}
}



BOOL SettingsIsBleepEnabled(void)
{
	return m_settings.isBuzzerMuted;
}

void SettingsToggleBleep(void)
{
	if (m_settings.isBuzzerMuted)
	{
		m_settings.isBuzzerMuted = FALSE;
	}
	else
	{
		m_settings.isBuzzerMuted = TRUE;
	}
	buzzer_mute(m_settings.isBuzzerMuted);

	SettingsSave();
}

// Load default settings to EEPROM and force a save
// This is called from syslib if the settings are being reset to defaults
void load_eeprom_defaults(void)
{
    // Set all the other defaults
    _SettingsLoadDefaults();
    // Force a save of the settings
    SettingsSave();
    // Make a 500ms beep
    buzzer_out_timed(500);
}

// Load settings defaults
static void _SettingsLoadDefaults(void)
{
	m_settings.isBuzzerMuted = FALSE;                                      
	buzzer_mute(m_settings.isBuzzerMuted);
  
}
