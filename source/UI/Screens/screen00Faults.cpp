//------------------------------------------------------------------------------
//  AUTHOR :			Nabil Lamriben 1/07/2025
//  Desctiption :		
//------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "project.h"
#include "VCInc.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
static void _Key1Release(void* userData);
static void _Key2Release(void* userData);
static void _Key3Release(void* userData);
static void _Key4Release(void* userData);
static void _Key5Release(void* userData);
static int s_currentPage = 0;
static std::vector<std::string> s_faultList;

static uint32_t s_prevSta1Mask = 0;
static uint32_t s_prevSta2Mask = 0;
static uint32_t s_prevSta3Mask = 0;
static uint32_t s_prevNfuMask = 0;
static uint32_t s_prevSfeMask = 0;
static uint32_t s_prevCfeMask = 0;
static uint32_t s_prevGalMask = 0;
 
static void _CheckNewlyActivatedBits(uint32_t currentMask,
    uint32_t* pPrevMask,
    FAULT_CODE code)
{
    // newly activated bits = bits that were off before but are on now
    uint32_t newlyActivated = (~(*pPrevMask)) & currentMask;

    // For each newly activated bit, set isAcked = false
    for (int i = 0; i < NUM_FAULT_ENTRIES; i++)
    {
        if (m_FAULTS_DB[i].FaultCode == code)
        {
            int bitIndex = m_FAULTS_DB[i].Bit;
            if (newlyActivated & (1 << bitIndex))
            {
                // This fault just turned on -> treat as new
                m_FAULTS_DB[i].isAcked = false;
            }
        }
    }

    // Update the previous mask for next time
    *pPrevMask = currentMask;
}
static void _AppendFaultsFromMask2(std::vector<std::string>& faultVec, uint32_t mask, FAULT_CODE code)
{
    for (int i = 0; i < NUM_FAULT_ENTRIES; i++)
    {
        if (m_FAULTS_DB[i].FaultCode == code)
        {
            bool bitActive = ((mask & (1 << m_FAULTS_DB[i].Bit)) != 0);
            if (bitActive)
            {
                std::string line = std::string(m_FAULTS_DB[i].Description);
                if (m_FAULTS_DB[i].isAcked) line += " (Ack)";
                faultVec.push_back(line);
                std::cout << "Appending fault: " << line << std::endl;
            }
        }
    }
}

void Scrn00FaultsEnter(void)
{
}

void Scrn00FaultsCreate(void)
{
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);
    ButtonBarSetHeight(48);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_1, _Key1Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_2, _Key2Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_3, _Key3Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_4, _Key4Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_5, _Key5Release, nullptr);
    ButtonBarSetKeyText(KEYINDEX_1, FONT_INDEX_TTMAIN, 9, BLACK, "to", "Start");
    ButtonBarSetKeyText(KEYINDEX_2, FONT_INDEX_TTMAIN, 9, BLACK, "Prev", "Page");
    ButtonBarSetKeyText(KEYINDEX_3, FONT_INDEX_TTMAIN, 9, BLACK, "Next", "Page");
    ButtonBarSetKeyText(KEYINDEX_4, FONT_INDEX_TTMAIN, 9, BLACK, "Ack", "All");
    ButtonBarSetMode(BUTTONBARMODE_VISIBLE_ALWAYS);
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 20, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 0, "Propulsion System Faults", BLACK, 100, LAYER_FRONT);
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(180, 35, "Active Faults = ", BLACK, 100, LAYER_BACK);
    s_currentPage = 0;
}

void Scrn00FaultsUpdate(void)
{  
    // Clear the screen
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);
    // Display Station and Communication Mode String
    const char* info = GetStationAndComModeString();
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 10, HORIZONTAL_ALIGNMENT_CENTRE, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(lcd_get_width() / 2, 10, info, BLACK, 100, LAYER_FRONT);

    // Check and add faults based on global flags
    if (Helm1_Fault == STATE3)
    {
        s_faultList.push_back("Helm1 Fault (Blinking)");
    }
    else if (Helm1_Fault == STATE2)
    {
        s_faultList.push_back("Helm1 Fault (Active)");
    }
    else if (Helm1_Fault == STATE1)
    {
        s_faultList.push_back("Helm1 Fault (Acknowledged)");
    }

    // Repeat for other global fault flags
    if (Helm2_Fault == STATE3)
    {
        s_faultList.push_back("Helm2 Fault (Blinking)");
    }
    else if (Helm2_Fault == STATE2)
    {
        s_faultList.push_back("Helm2 Fault (Active)");
    }
    else if (Helm2_Fault == STATE1)
    {
        s_faultList.push_back("Helm2 Fault (Acknowledged)");
    }

    // Display the total fault count
    int faultCount = static_cast<int>(s_faultList.size());
    if (faultCount == 0)
    {
        SimpleTextDraw(10, 60, "No Faults Detected", BLACK, 100, LAYER_FRONT);
        return;
    }

    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(282, 35, std::to_string(faultCount).c_str(), BLACK, 100, LAYER_FRONT);

    // Handle pagination
    const int totalPages = (faultCount + FAULTS_PER_PAGE - 1) / FAULTS_PER_PAGE;
    if (s_currentPage >= totalPages) s_currentPage = totalPages - 1;
    if (s_currentPage < 0) s_currentPage = 0;

    // Display faults for the current page
    int yPos = 60;
    int startIndex = s_currentPage * FAULTS_PER_PAGE;
    int endIndex = std::min(startIndex + FAULTS_PER_PAGE, faultCount);
    for (int i = startIndex; i < endIndex; i++)
    {
        SimpleTextDraw(5, yPos, s_faultList[i].c_str(), BLACK, 100, LAYER_FRONT);
        yPos += 20;
    }

    // Display the current page
    char pageMsg[32];
    snprintf(pageMsg, sizeof(pageMsg), "Page %d / %d", s_currentPage + 1, totalPages);
    SimpleTextDraw(5, 35, pageMsg, BLACK, 100, LAYER_FRONT);
}


void Scrn00FaultsExit(void)
{
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
    if (s_currentPage > 0)
    {
        s_currentPage--;
        Scrn00FaultsUpdate();
    }
}

static void _Key3Release(void* userData)
{
    s_currentPage++;
    Scrn00FaultsUpdate();
}

static void _Key4Release(void* userData)
{
    // Acknowledge all signal faults
    if (PTab_sigFault == STATE3 || PTab_sigFault == STATE2) PTab_sigFault = STATE1;
    if (STab_sigFault == STATE3 || STab_sigFault == STATE2) STab_sigFault = STATE1;
    if (PNoz_sigFault == STATE3 || PNoz_sigFault == STATE2) PNoz_sigFault = STATE1;
    if (SNoz_sigFault == STATE3 || SNoz_sigFault == STATE2) SNoz_sigFault = STATE1;
    if (PBkt_sigFault == STATE3 || PBkt_sigFault == STATE2) PBkt_sigFault = STATE1;
    if (SBkt_sigFault == STATE3 || SBkt_sigFault == STATE2) SBkt_sigFault = STATE1;

    // Acknowledge all NFU faults
    if (PTab_nfuFault == STATE3 || PTab_nfuFault == STATE2) PTab_nfuFault = STATE1;
    if (STab_nfuFault == STATE3 || STab_nfuFault == STATE2) STab_nfuFault = STATE1;
    if (PNoz_nfuFault == STATE3 || PNoz_nfuFault == STATE2) PNoz_nfuFault = STATE1;
    if (SNoz_nfuFault == STATE3 || SNoz_nfuFault == STATE2) SNoz_nfuFault = STATE1;
    if (PBkt_nfuFault == STATE3 || PBkt_nfuFault == STATE2) PBkt_nfuFault = STATE1;
    if (SBkt_nfuFault == STATE3 || SBkt_nfuFault == STATE2) SBkt_nfuFault = STATE1;

    // Acknowledge Helm1-related faults
    if (JoyX1_Fault == STATE3 || JoyX1_Fault == STATE2) JoyX1_Fault = STATE1;
    if (JoyY1_Fault == STATE3 || JoyY1_Fault == STATE2) JoyY1_Fault = STATE1;
    if (PLev1_Fault == STATE3 || PLev1_Fault == STATE2) PLev1_Fault = STATE1;
    if (SLev1_Fault == STATE3 || SLev1_Fault == STATE2) SLev1_Fault = STATE1;
    if (Helm1_Fault == STATE3 || Helm1_Fault == STATE2) Helm1_Fault = STATE1;
    if (Idle1_Fault == STATE3 || Idle1_Fault == STATE2) Idle1_Fault = STATE1;

    // Acknowledge Helm2-related faults
    if (JoyX2_Fault == STATE3 || JoyX2_Fault == STATE2) JoyX2_Fault = STATE1;
    if (JoyY2_Fault == STATE3 || JoyY2_Fault == STATE2) JoyY2_Fault = STATE1;
    if (PLev2_Fault == STATE3 || PLev2_Fault == STATE2) PLev2_Fault = STATE1;
    if (SLev2_Fault == STATE3 || SLev2_Fault == STATE2) SLev2_Fault = STATE1;
    if (Helm2_Fault == STATE3 || Helm2_Fault == STATE2) Helm2_Fault = STATE1;
    if (Idle2_Fault == STATE3 || Idle2_Fault == STATE2) Idle2_Fault = STATE1;

    // Acknowledge Helm3-related faults
    if (JoyX3_Fault == STATE3 || JoyX3_Fault == STATE2) JoyX3_Fault = STATE1;
    if (JoyY3_Fault == STATE3 || JoyY3_Fault == STATE2) JoyY3_Fault = STATE1;
    if (PLev3_Fault == STATE3 || PLev3_Fault == STATE2) PLev3_Fault = STATE1;
    if (SLev3_Fault == STATE3 || SLev3_Fault == STATE2) SLev3_Fault = STATE1;
    if (Helm3_Fault == STATE3 || Helm3_Fault == STATE2) Helm3_Fault = STATE1;
    if (Idle3_Fault == STATE3 || Idle3_Fault == STATE2) Idle3_Fault = STATE1;

    // Acknowledge other general faults
    if (Cal_Fault == STATE3 || Cal_Fault == STATE2) Cal_Fault = STATE1;
    if (Roll1_Fault == STATE3 || Roll1_Fault == STATE2) Roll1_Fault = STATE1;
    if (Trim1_Fault == STATE3 || Trim1_Fault == STATE2) Trim1_Fault = STATE1;
    if (Inbd_Fault == STATE3 || Inbd_Fault == STATE2) Inbd_Fault = STATE1;
    if (Otbd_Fault == STATE3 || Otbd_Fault == STATE2) Otbd_Fault = STATE1;
    if (AP_Fault == STATE3 || AP_Fault == STATE2) AP_Fault = STATE1;
    if (clutchDiseng_Fault == STATE3 || clutchDiseng_Fault == STATE2) clutchDiseng_Fault = STATE1;
    if (generalDock_Fault == STATE3 || generalDock_Fault == STATE2) generalDock_Fault = STATE1;
    if (Roll2_Fault == STATE3 || Roll2_Fault == STATE2) Roll2_Fault = STATE1;
    if (Trim2_Fault == STATE3 || Trim2_Fault == STATE2) Trim2_Fault = STATE1;

    //Ack clucth
    if(ClutchST1_CAN_Fault == STATE3 || ClutchST1_CAN_Fault == STATE2) ClutchST1_CAN_Fault = STATE1;
    if(ClutchST2_CAN_Fault == STATE3 || ClutchST2_CAN_Fault == STATE2) ClutchST2_CAN_Fault = STATE1;




    Scrn00FaultsUpdate();
}

static void _Key5Release(void* userData)
{
  
    MMIScreenGoto(SCREENID_START);
}
/*
void Scrn00FaultsUpdate(void)
{
    // Clear the screen and reset the fault list
    fill_lcd_screen(ALPHA_COLOR, LAYER_FRONT);
    s_faultList.clear();

    // Retrieve fault masks from the database
    DBELEMENT_T dbElement;
    uint32_t sta1mask = 0, sta2mask = 0, sta3mask = 0;
    uint32_t nfumask = 0, sfemask = 0, cfemask = 0, galmask = 0;

    if (DataBase_Get(&dbElement, db_VECTOR_STA1_fault_error, 0)) {
        sta1mask = dbElement.Data.ui;
        Decode_STA1Fault(); // Decode STA1 faults
    }
    if (DataBase_Get(&dbElement, db_VECTOR_STA2_fault_error, 0)) {
        sta2mask = dbElement.Data.ui;
        Decode_STA2Fault(); // Decode STA2 faults
    }
    if (DataBase_Get(&dbElement, db_VECTOR_STA3_fault_error, 0)) {
        sta3mask = dbElement.Data.ui;
        Decode_STA3Fault(); // Decode STA3 faults
    }
    if (DataBase_Get(&dbElement, db_VECTOR_nfu_fault_error, 0)) {
        nfumask = dbElement.Data.ui;
        Decode_NfuFault(); // Decode NFU faults
    }
    if (DataBase_Get(&dbElement, db_VECTOR_signal_fault_error, 0)) {
        sfemask = dbElement.Data.ui;
        Decode_SignalFault(); // Decode Signal faults
    }
    if (DataBase_Get(&dbElement, db_VECTOR_cal_fault_error, 0)) {
        cfemask = dbElement.Data.ui;
        Decode_CalFault(); // Decode Calibration faults
    }
    if (DataBase_Get(&dbElement, db_VECTOR_GAL_fault_error, 0)) {
        galmask = dbElement.Data.ui;
        // If there's a GAL-specific decode function, call it here
    }

    // Detect newly activated bits
    _CheckNewlyActivatedBits(sta1mask, &s_prevSta1Mask, STA1);
    _CheckNewlyActivatedBits(sta2mask, &s_prevSta2Mask, STA2);
    _CheckNewlyActivatedBits(sta3mask, &s_prevSta3Mask, STA3);
    _CheckNewlyActivatedBits(nfumask, &s_prevNfuMask, NFU);
    _CheckNewlyActivatedBits(sfemask, &s_prevSfeMask, SFE);
    _CheckNewlyActivatedBits(cfemask, &s_prevCfeMask, CFE);
    _CheckNewlyActivatedBits(galmask, &s_prevGalMask, GAL);

    // Populate fault list
    _AppendFaultsFromMask2(s_faultList, sta1mask, STA1);
    _AppendFaultsFromMask2(s_faultList, sta2mask, STA2);
    _AppendFaultsFromMask2(s_faultList, sta3mask, STA3);
    _AppendFaultsFromMask2(s_faultList, nfumask, NFU);
    _AppendFaultsFromMask2(s_faultList, sfemask, SFE);
    _AppendFaultsFromMask2(s_faultList, cfemask, CFE);
    _AppendFaultsFromMask2(s_faultList, galmask, GAL);

    // Display fault count
    int faultCount = static_cast<int>(s_faultList.size());
    if (faultCount == 0)
    {
        SimpleTextDraw(10, 60, "No Faults Detected", BLACK, 100, LAYER_FRONT);
        return;
    }
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(282, 35, std::to_string(faultCount).c_str(), BLACK, 100, LAYER_FRONT);

    // Pagination
    const int totalPages = (faultCount + FAULTS_PER_PAGE - 1) / FAULTS_PER_PAGE;
    if (s_currentPage < 0) s_currentPage = 0;
    if (s_currentPage >= totalPages) s_currentPage = totalPages - 1;

    // Display faults on the current page
    int yPos = 60;
    int startIndex = s_currentPage * FAULTS_PER_PAGE;
    int endIndex = std::min(startIndex + FAULTS_PER_PAGE, faultCount);
    for (int i = startIndex; i < endIndex; i++)
    {
        SimpleTextDraw(5, yPos, s_faultList[i].c_str(), BLACK, 100, LAYER_FRONT);
        yPos += 20;
    }

    // Display current page
    char pageMsg[32];
    snprintf(pageMsg, sizeof(pageMsg), "Page %d / %d", s_currentPage + 1, totalPages);
    SimpleTextDraw(5, 35, pageMsg, BLACK, 100, LAYER_FRONT);
}

static void _Key4Release(void* userData)
{
    for (int i = 0; i < NUM_FAULT_ENTRIES; i++)
    {
        if (!m_FAULTS_DB[i].isAcked)
        {
            m_FAULTS_DB[i].isAcked = true;
        }
    }
    Scrn00FaultsUpdate();
}

*/