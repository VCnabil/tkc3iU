//------------------------------------------------------------------------------
//  TITLE :          scrn00Calibration.cpp
//  DESCRIPTION :    Implementation of scrn00Calibration screen
//  AUTHOR :         Nabil Lamriben 1/08/2025
//------------------------------------------------------------------------------
#include "scrn00Calibration.h"
#include "UI/screens.h"

//Button Bar
static void _Key1Release(void* userData);
static void _Key2Release(void* userData);
static void _Key3Release(void* userData);
static void _Key3ReleaseHideThrust(void* userData);
static void _Key4Release(void* userData);
static void _Key5Release(void* userData);

static char* CalcChecksumSend(const char* msg) {
	static char checksumStr[3];
	int checksum = 0;
	if (msg[0] == '$') {
		msg++;
	}
	//while ( *msg != '*') {
	//	checksum ^= (unsigned char)(*msg++);
	//}
	while (*msg && *msg != '*') {
		checksum ^= (unsigned char)(*msg++);
	}
	snprintf(checksumStr, sizeof(checksumStr), "%02X", checksum);
	return checksumStr;
}
void sendSerial(void) {
	//if (!m_SYSTEMOPTIONS_DB[1].status) return;

	if(SettingsGetXmitrs232OnOff() == 0) return;

	char messageWithoutChecksum[50];

	//snprintf(messageWithoutChecksum, sizeof(messageWithoutChecksum), "$PVCC,%d,%d,%d,%d,%d,%d,%d,%d", value0, value1, value2, value3, value4, value5, value6, value7);
	snprintf(messageWithoutChecksum, sizeof(messageWithoutChecksum), "$PVCC,%d,%d,%d,%d,%d,%d,%d,%d", SettingsGetInSteerOnOff() ? 0 : 1, Autocal_CMD, Set1_Set2_Mode, Position_Capture_Request, 0, 0, 0, 0);

	char* checksum = CalcChecksumSend(messageWithoutChecksum);
	char fullMessage[60]; //guestimate I counted 38bytes , but there could be more , so 60 is safe  
	snprintf(fullMessage, sizeof(fullMessage), "%s*%s\r", messageWithoutChecksum, checksum);
	uint32_t dataLen = strlen(fullMessage);
	UARTSend((uint8_t*)fullMessage, dataLen);
}



//int Autocal_CMD = NONE;
Screen_State screen_state = DEFAULT;
uint8_t DisplayConfigVar;
//------------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//------------------------------------------------------------------------------
void Scrn00CalibrationEnter(void)
{
    // to be implemented
	Autocal_CMD = NONE;
    DisplayConfigVar = SettingsGetIndicationConfig();
}

void Scrn00CalibrationCreate(void)
{
    screen_state = DEFAULT;
    DisplayConfigVar = SettingsGetIndicationConfig();
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);
    ScreensSetupDefaultKeys();
    ButtonBarSetKeyImages(KEYINDEX_1, &view_meters, &view_meters);
    ButtonBarSetKeyImages(KEYINDEX_2, &blank, &blank);
    if (DisplayConfigVar == 3 || DisplayConfigVar == 1) ButtonBarSetKeyImages(KEYINDEX_3, &thrust_calib, &thrust_calib);
    else ButtonBarSetKeyImages(KEYINDEX_3, &blank, &blank);
    ButtonBarSetKeyImages(KEYINDEX_4, &init_cal, &init_cal);
    ButtonBarSetKeyImages(KEYINDEX_5, &blank, &blank);

    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_1, _Key1Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_2, _Key2Release, nullptr);
    if (DisplayConfigVar == 3 || DisplayConfigVar == 1) ButtonBarRegisterKeyReleaseCallback(KEYINDEX_3, _Key3Release, nullptr);
    else ButtonBarRegisterKeyReleaseCallback(KEYINDEX_3, _Key3ReleaseHideThrust, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_4, _Key4Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_5, _Key5Release, nullptr);

    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 25, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 5, "System Calibration", BLACK, 100, LAYER_BACK);
  

    ButtonBarSetMode(BUTTONBARMODE_VISIBLE_WITH_TIMEOUT);
}

void Scrn00CalibrationUpdate(void)
{
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);
    // to be implemented
	sendSerial();
	if (screen_state == DEFAULT) {

	}
	else if (screen_state == THRUST_MENU) {

	}
	else if (screen_state == TRANSMIT) {
		switch (Autocal_Status)
		{
		case 0:
			SimpleTextDraw(160, 50, "Not Active", BLACK, 100, LAYER_FRONT);
			break;

		case 77:
			SimpleTextDraw(160, 50, "ACTIVE", BLACK, 100, LAYER_FRONT);
			SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 18, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
			if (Position_Capture_Request == 11) SimpleTextDraw(160, 80, "Request Pending...", BLACK, 100, LAYER_FRONT);
			else SimpleTextDraw(160, 80, "Set Transverse Thrust Offset.", BLACK, 100, LAYER_FRONT);
			break;

		case 88:
			SimpleTextDraw(160, 50, "ACTIVE", BLACK, 100, LAYER_FRONT);
			SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 18, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
			SimpleTextDraw(160, 80, "Transverse Offset Set!", BLACK, 100, LAYER_FRONT);
			break;

		default:
			SimpleTextDraw(190, 50, "Unknown Status", BLACK, 100, LAYER_FRONT);
			break;
		}
	}
	else if (screen_state == AUTOCALIBRATION) {
		switch (Autocal_Status)
		{
		case 0:
			SimpleTextDraw(160, 50, "Not Active", BLACK, 100, LAYER_FRONT);
			break;

		case 11:
			SimpleTextDraw(160, 50, "ACTIVE", BLACK, 100, LAYER_FRONT);
			SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 18, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
			SimpleTextDraw(160, 80, "Cylinders Moving Up / Stbd", BLACK, 100, LAYER_FRONT);
			break;

		case 22:
			SimpleTextDraw(160, 50, "ACTIVE", BLACK, 100, LAYER_FRONT);
			SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 18, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
			SimpleTextDraw(160, 80, "Cylinders Moving Down / Port", BLACK, 100, LAYER_FRONT);
			break;

		case 33:
			SimpleTextDraw(160, 50, "ACTIVE", BLACK, 100, LAYER_FRONT);
			SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 18, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
			SimpleTextDraw(160, 80, "Cycle Controls...", BLACK, 100, LAYER_FRONT);
			break;

		case 44:
			SimpleTextDraw(160, 50, "COMPLETE", BLACK, 100, LAYER_FRONT);
			SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 18, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
			SimpleTextDraw(160, 80, "Move controls to detent", BLACK, 100, LAYER_FRONT);
			break;

		default:
			SimpleTextDraw(190, 50, "Unknown Status", BLACK, 100, LAYER_FRONT);
			break;
		}
	}
	else if (screen_state == ZERO_THRUST) {
		switch (Autocal_Status)
		{
		case 0:
			SimpleTextDraw(160, 50, "Not Active", BLACK, 100, LAYER_FRONT);
			break;

		case 55:
			SimpleTextDraw(160, 50, "ACTIVE", BLACK, 100, LAYER_FRONT);
			SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 18, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
			if (Position_Capture_Request == 11) SimpleTextDraw(160, 80, "Request Pending...", BLACK, 100, LAYER_FRONT);
			else SimpleTextDraw(160, 80, "Set Neutral Thrust Position", BLACK, 100, LAYER_FRONT);
			break;

		case 66:
			SimpleTextDraw(160, 50, "ACTIVE", BLACK, 100, LAYER_FRONT);
			SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 18, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
			SimpleTextDraw(160, 80, "Neutral Thrust Set!", BLACK, 100, LAYER_FRONT);
			break;

		default:
			SimpleTextDraw(190, 50, "Unknown Status", BLACK, 100, LAYER_FRONT);
			break;
		}
	}

}

static void _Key3ReleaseHideThrust(void* userData) {
    if (screen_state == AUTOCALIBRATION) {
        Autocal_CMD = ABORT;
    }
    else if (screen_state == ZERO_THRUST) {

    }
}

void Scrn00CalibrationExit(void)
{
    // to be implemented
}

//------------------------------------------------------------------------------
// LOCAL FUNCTIONS
//------------------------------------------------------------------------------
static void _Key1Release(void* userData)
{
	if (screen_state == DEFAULT) {
		MMIScreenGoto(SCREENID_START);
	}
	else if (screen_state == THRUST_MENU) {
		MMIScreenGoto(SCREENID_START);
	}
	else if (screen_state == TRANSMIT) {

	}
	else if (screen_state == AUTOCALIBRATION) {
		Autocal_CMD = FINISH;
		screen_state = DEFAULT;
		ButtonBarSetKeyImages(KEYINDEX_1, &view_meters, &view_meters);
		ButtonBarSetKeyImages(KEYINDEX_2, &blank, &blank);
		ButtonBarSetKeyImages(KEYINDEX_3, &thrust_calib, &thrust_calib);
		ButtonBarSetKeyImages(KEYINDEX_4, &init_cal, &init_cal);
		ButtonBarSetKeyImages(KEYINDEX_5, &blank, &blank);
	}
	else if (screen_state == ZERO_THRUST) {
		Position_Capture_Request = 11;
	}

}

static void _Key2Release(void* userData)
{
	if (screen_state == DEFAULT) {

	}
	else if (screen_state == THRUST_MENU) {
		Set1_Set2_Mode = 11;

		screen_state = ZERO_THRUST;
		ButtonBarSetKeyImages(KEYINDEX_1, &set_zthrust, &set_zthrust);
		ButtonBarSetKeyImages(KEYINDEX_2, &finish_calib, &finish_calib);
		ButtonBarSetKeyImages(KEYINDEX_3, &blank, &blank);
		ButtonBarSetKeyImages(KEYINDEX_4, &blank, &blank);
		ButtonBarSetKeyImages(KEYINDEX_5, &blank, &blank);
	}
	else if (screen_state == TRANSMIT) {
		Set1_Set2_Mode = 0;
		Position_Capture_Request = 0;

		screen_state = DEFAULT;
		ButtonBarSetKeyImages(KEYINDEX_1, &view_meters, &view_meters);
		ButtonBarSetKeyImages(KEYINDEX_2, &blank, &blank);
		ButtonBarSetKeyImages(KEYINDEX_3, &thrust_calib, &thrust_calib);
		ButtonBarSetKeyImages(KEYINDEX_4, &init_cal, &init_cal);
		ButtonBarSetKeyImages(KEYINDEX_5, &blank, &blank);
	}
	else if (screen_state == AUTOCALIBRATION) {
		Autocal_CMD = ABORT;
		screen_state = DEFAULT;
		ButtonBarSetKeyImages(KEYINDEX_1, &view_meters, &view_meters);
		ButtonBarSetKeyImages(KEYINDEX_2, &blank, &blank);
		ButtonBarSetKeyImages(KEYINDEX_3, &thrust_calib, &thrust_calib);
		ButtonBarSetKeyImages(KEYINDEX_4, &init_cal, &init_cal);
		ButtonBarSetKeyImages(KEYINDEX_5, &blank, &blank);
	}
	else if (screen_state == ZERO_THRUST) {
		Set1_Set2_Mode = 0;
		Position_Capture_Request = 0;

		screen_state = DEFAULT;
		ButtonBarSetKeyImages(KEYINDEX_1, &view_meters, &view_meters);
		ButtonBarSetKeyImages(KEYINDEX_2, &blank, &blank);
		ButtonBarSetKeyImages(KEYINDEX_3, &thrust_calib, &thrust_calib);
		ButtonBarSetKeyImages(KEYINDEX_4, &init_cal, &init_cal);
		ButtonBarSetKeyImages(KEYINDEX_5, &blank, &blank);
	}
}

static void _Key3Release(void* userData)
{
	if (screen_state == DEFAULT) {
		screen_state = THRUST_MENU;
		ButtonBarSetKeyImages(KEYINDEX_1, &view_meters, &view_meters);
		ButtonBarSetKeyImages(KEYINDEX_2, &init_zthrust, &init_zthrust);
		ButtonBarSetKeyImages(KEYINDEX_3, &init_transmit, &init_transmit);
		ButtonBarSetKeyImages(KEYINDEX_4, &blank, &blank);
		ButtonBarSetKeyImages(KEYINDEX_5, &exit_menu, &exit_menu);
	}
	else if (screen_state == THRUST_MENU) {
		Set1_Set2_Mode = 22;

		screen_state = TRANSMIT;
		ButtonBarSetKeyImages(KEYINDEX_1, &set_transmit, &set_transmit);
		ButtonBarSetKeyImages(KEYINDEX_2, &finish_calib, &finish_calib);
		ButtonBarSetKeyImages(KEYINDEX_3, &blank, &blank);
		ButtonBarSetKeyImages(KEYINDEX_4, &blank, &blank);
		ButtonBarSetKeyImages(KEYINDEX_5, &blank, &blank);
	}
	else if (screen_state == TRANSMIT) {

	}
	else if (screen_state == AUTOCALIBRATION) {
		Autocal_CMD = ABORT;
	}
	else if (screen_state == ZERO_THRUST) {

	}
}

static void _Key4Release(void* userData)
{
	if (screen_state == DEFAULT) {
		screen_state = AUTOCALIBRATION;
		ButtonBarSetKeyImages(KEYINDEX_1, &finish_calib, &finish_calib);
		ButtonBarSetKeyImages(KEYINDEX_2, &abort_calib, &abort_calib);
		ButtonBarSetKeyImages(KEYINDEX_3, &blank, &blank);
		ButtonBarSetKeyImages(KEYINDEX_4, &blank, &blank);
		ButtonBarSetKeyImages(KEYINDEX_5, &exit_menu, &blank);
		Autocal_CMD = INITIALIZE;
	}
	else if (screen_state == THRUST_MENU) {

	}
	else if (screen_state == TRANSMIT) {

	}
	else if (screen_state == AUTOCALIBRATION) {

	}
	else if (screen_state == ZERO_THRUST) {

	}
}

static void _Key5Release(void* userData)
{
	if (screen_state == DEFAULT) {

	}
	else if (screen_state == THRUST_MENU) {
		screen_state = DEFAULT;
		ButtonBarSetKeyImages(KEYINDEX_1, &view_meters, &view_meters);
		ButtonBarSetKeyImages(KEYINDEX_2, &blank, &blank);
		ButtonBarSetKeyImages(KEYINDEX_3, &thrust_calib, &thrust_calib);
		ButtonBarSetKeyImages(KEYINDEX_4, &init_cal, &init_cal);
		ButtonBarSetKeyImages(KEYINDEX_5, &blank, &blank);
	}
	else if (screen_state == TRANSMIT) {

	}
	else if (screen_state == AUTOCALIBRATION) {

	}
	else if (screen_state == ZERO_THRUST) {

	}
}