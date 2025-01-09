//------------------------------------------------------------------------------
//  TITLE :          settings.c
//------------------------------------------------------------------------------

#include "project.h"
#include "VCInc.h"  // <-- Yes as well include this if using #defines or references from VCInc.h 

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
 
	//these parameters are for storing the display configuration. 
	// Station: main_station or wing_station
	uint8_t  STATION_TYPE;
	// Data mode: rs232_mode, CANbus_mode, CANbus_GPSI_mode
	uint8_t  DATA_MODE;
	// Flip modes: normal, flipped
	uint8_t  NOZZLEMAP_FLIP;
	uint8_t  BUCKETMAP_FLIP;
	uint8_t  TABMAP_FLIP;
	// Indication config: 
	// e.g. idc_1buk1noz (1), idc_2buk2noz (2), idc_2buk1noz (3),idc_2buk2noz2tab (4), idc_2buk1noz2tab (5), idc_2buk2noz_grad (6), etc.
	uint8_t  INDICATION_CONFIG;
	// Comms mode: comm_mode_4 or comm_mode_5
	uint8_t  COMMS_MODE;
	 

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

#pragma region DispayConfigValues

// -----------------------
// Station Type
// -----------------------
uint8_t SettingsGetStationType(void)
{
    return m_settings.STATION_TYPE;
}

void SettingsSetStationType(uint8_t newStationType)
{
    // Allowed: main_station (1), wing_station (2)
    if (newStationType == main_station || newStationType == wing_station)
    {
        m_settings.STATION_TYPE = newStationType;
        SettingsSave();
    }
}

 
void SettingsToggleStationType(void* userData)
{
    if (m_settings.STATION_TYPE == main_station)
    {
        m_settings.STATION_TYPE = wing_station;
    }
    else
    {
        m_settings.STATION_TYPE = main_station;
    }
    SettingsSave();
}

// -----------------------
// Data Mode
// -----------------------
uint8_t SettingsGetDataMode(void)
{
    return m_settings.DATA_MODE;
}

void SettingsSetDataMode(uint8_t newDataMode)
{
    // Allowed: rs232_mode (1), CANbus_mode (2), CANbus_GPSI_mode (3)
    if ((newDataMode == rs232_mode) ||
        (newDataMode == CANbus_mode) ||
        (newDataMode == CANbus_GPSI_mode))
    {
        m_settings.DATA_MODE = newDataMode;
        SettingsSave();
    }
}

void SettingsToggleDataMode(void)
{
    // Cycle 1 -> 2 -> 3 -> 1
    if (m_settings.DATA_MODE == rs232_mode)
        m_settings.DATA_MODE = CANbus_mode;
    else if (m_settings.DATA_MODE == CANbus_mode)
        m_settings.DATA_MODE = CANbus_GPSI_mode;
    else
        m_settings.DATA_MODE = rs232_mode;

    SettingsSave();
}

// -----------------------
// NozzleMap Flip
// -----------------------
uint8_t SettingsGetNozzleMapFlip(void)
{
    return m_settings.NOZZLEMAP_FLIP;
}

void SettingsSetNozzleMapFlip(uint8_t newNozzleMapFlip)
{
    // Allowed: normal (1), flipped (2)
    if (newNozzleMapFlip == normal || newNozzleMapFlip == flipped)
    {
        m_settings.NOZZLEMAP_FLIP = newNozzleMapFlip;
        SettingsSave();
    }
}

void SettingsToggleNozzleMapFlip(void)
{
    if (m_settings.NOZZLEMAP_FLIP == normal)
        m_settings.NOZZLEMAP_FLIP = flipped;
    else
        m_settings.NOZZLEMAP_FLIP = normal;

    SettingsSave();
}

// -----------------------
// BucketMap Flip
// -----------------------
uint8_t SettingsGetBucketMapFlip(void)
{
    return m_settings.BUCKETMAP_FLIP;
}

void SettingsSetBucketMapFlip(uint8_t newBucketMapFlip)
{
    // Allowed: normal (1), flipped (2)
    if (newBucketMapFlip == normal || newBucketMapFlip == flipped)
    {
        m_settings.BUCKETMAP_FLIP = newBucketMapFlip;
        SettingsSave();
    }
}

void SettingsToggleBucketMapFlip(void)
{
    if (m_settings.BUCKETMAP_FLIP == normal)
        m_settings.BUCKETMAP_FLIP = flipped;
    else
        m_settings.BUCKETMAP_FLIP = normal;

    SettingsSave();
}

// -----------------------
// TabMap Flip
// -----------------------
uint8_t SettingsGetTabMapFlip(void)
{
    return m_settings.TABMAP_FLIP;
}

void SettingsSetTabMapFlip(uint8_t newTabMapFlip)
{
    // Allowed: normal (1), flipped (2)
    if (newTabMapFlip == normal || newTabMapFlip == flipped)
    {
        m_settings.TABMAP_FLIP = newTabMapFlip;
        SettingsSave();
    }
}

void SettingsToggleTabMapFlip(void)
{
    if (m_settings.TABMAP_FLIP == normal)
        m_settings.TABMAP_FLIP = flipped;
    else
        m_settings.TABMAP_FLIP = normal;

    SettingsSave();
}

// -----------------------
// Indication Config
// -----------------------
uint8_t SettingsGetIndicationConfig(void)
{
    return m_settings.INDICATION_CONFIG;
}

void SettingsSetIndicationConfig(uint8_t newConfig)
{
    // Allowed range: idc_1buk1noz (1) up to idc_2buk2noz_grad (6) 
    // or any new definitions you add
    if (newConfig >= idc1_1buk1noz && newConfig <= idc6_2buk2noz_grad)
    {
        m_settings.INDICATION_CONFIG = newConfig;
        SettingsSave();
    }
}

void SettingsToggleIndicationConfig(void)
{
    // Example: cycle from 1->2->3->4->5->6->1
    // if you use more definitions, adjust accordingly
    uint8_t next = m_settings.INDICATION_CONFIG + 1;
    if (next > idc6_2buk2noz_grad)
    {
        next = idc1_1buk1noz;
    }
    m_settings.INDICATION_CONFIG = next;
    SettingsSave();
}

// -----------------------
// Comms Mode
// -----------------------
uint8_t SettingsGetCommsMode(void)
{
    return m_settings.COMMS_MODE;
}

void SettingsSetCommsMode(uint8_t newCommsMode)
{
    // Allowed: comm_mode_4 (4), comm_mode_5 (5)
    if (newCommsMode == comm_mode_4 || newCommsMode == comm_mode_5)
    {
        m_settings.COMMS_MODE = newCommsMode;
        SettingsSave();
    }
}

void SettingsToggleCommsMode(void)
{
    if (m_settings.COMMS_MODE == comm_mode_4)
        m_settings.COMMS_MODE = comm_mode_5;
    else
        m_settings.COMMS_MODE = comm_mode_4;

    SettingsSave();
}

#pragma endregion



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

    // Station type
    m_settings.STATION_TYPE = main_station;

    // Data mode
    m_settings.DATA_MODE = rs232_mode;
    // Alternatively: 
    //   = CANbus_mode; 
    //   = CANbus_GPSI_mode; 

    // Flip modes
    m_settings.NOZZLEMAP_FLIP = normal;
    m_settings.BUCKETMAP_FLIP = normal;
    m_settings.TABMAP_FLIP = normal;

    // Indication config
    // e.g. idc_1buk1noz (1), idc_2buk2noz (2), ...
    m_settings.INDICATION_CONFIG = idc2_2buk2noz;

    // Comms Mode
    m_settings.COMMS_MODE = comm_mode_4;
    // or  = comm_mode_5;
  
}
