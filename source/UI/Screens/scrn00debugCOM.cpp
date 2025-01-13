//------------------------------------------------------------------------------
//  TITLE :          scrn00debugCOM.cpp
//  DESCRIPTION :    Implementation of scrn00debugCOM screen
//  AUTHOR :         Nabil Lamriben 1/10/2025
//------------------------------------------------------------------------------
#include "scrn00debugCOM.h"
#include "UI/screens.h"
#include "project.h"

//------------------------------------------------------------------------------
// LOCAL FUNCTION PROTOTYPES
//------------------------------------------------------------------------------
static void _Key1Release(void* userData);
static void _Key2Release(void* userData);
static void _Key3Release(void* userData);
static void _Key4Release(void* userData);
static void _Key5Release(void* userData);

static uint32_t m_eidHeaderText = ELEMENTID_INVALID;
static uint32_t m_eidData = ELEMENTID_INVALID;

//------------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//------------------------------------------------------------------------------
void Scrn00DebugCOMEnter(void)
{
    // to be implemented
}

void Scrn00DebugCOMCreate(void)
{
    m_eidHeaderText = ElementGetNewId();
    m_eidData = ElementGetNewId();


    vLcdBlankerEx(MAKERGB565(150, 150, 200), ALPHA_COLOR);
	// Setup buttons and their callbacks
	ButtonBarSetHeight(48);
	ButtonBarSetMode(BUTTONBARMODE_VISIBLE_ALWAYS);
    // Draw a title
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 20, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 5, "Debug COM Screen", BLACK, 100, LAYER_FRONT);
    // to be implemented
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_1, _Key1Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_2, _Key2Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_3, _Key3Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_4, _Key4Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_5, _Key5Release, nullptr);
}

void Scrn00DebugCOMUpdate(void)
{
	const uint32_t dataStart_Y = 100;
	const uint32_t dataGap_X = 40;
	const uint32_t dataGap_Y = 11;
	const uint32_t fontSize = 9;
	const uint32_t messagesPerScreen = (uint32_t)((lcd_get_height() - dataStart_Y - back.y) / dataGap_Y);

	char str[255];
	uint32_t screenPos;
	MessageQueueInfo_t queueInfo;

	GetQueueInfo(&queueInfo);

	// Clear Previous Header text and redraw
	ElementFillPrevRect(m_eidHeaderText, WHITE, LAYER_FRONT);
	SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, fontSize, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 1);
	sprintf(str, "UART PORT - RdIndex=%d, WrIndex=%d", queueInfo.NextReadIndex, queueInfo.NextWriteIndex);
	SimpleTextDrawEle(m_eidHeaderText, 5, 100 - 2 - fontSize, str, WHITE_TEXT, 100, LAYER_FRONT);

	ElementFillPrevRect(m_eidData, WHITE, LAYER_FRONT);
	SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, fontSize, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 1);

	for (screenPos = 0; screenPos < messagesPerScreen; screenPos++)
	{
		uint8_t* buf = PeekMessage(PeekTail, messagesPerScreen - screenPos - 1, (uint8_t*)str, sizeof(str));

		if (buf != nullptr)
		{
			SimpleTextDrawEle(m_eidData, (dataGap_X / 2), dataStart_Y + (dataGap_Y * screenPos), str, WHITE_TEXT, 100, LAYER_FRONT);
		}
	}
}

void Scrn00DebugCOMExit(void)
{
    // to be implemented
}

//------------------------------------------------------------------------------
// LOCAL FUNCTIONS
//------------------------------------------------------------------------------
static void _Key1Release(void* userData)
{
	MMIScreenGoto(SCREENID_START);
}

static void _Key2Release(void* userData)
{
    // to be implemented
}

static void _Key3Release(void* userData)
{
    // to be implemented
}

static void _Key4Release(void* userData)
{
    // to be implemented
}

static void _Key5Release(void* userData)
{
   // MMIScreenGoto(SCREENID_MAINMENU);
}
