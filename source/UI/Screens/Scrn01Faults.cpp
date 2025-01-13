#include "Scrn01Faults.h"
#include "VCInc.h"
#include "UI/screens.h"
#include "Database/database.h"    
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>  
extern FAULTS_DB m_FAULTS_DB[];
static std::vector<std::string> s_faultList;
static int s_currentPage = 0;
static uint32_t s_prevSta1Mask = 0;
static uint32_t s_prevSta2Mask = 0;
static uint32_t s_prevSta3Mask = 0;
static uint32_t s_prevNfuMask = 0;
static uint32_t s_prevSfeMask = 0;
static uint32_t s_prevCfeMask = 0;
static uint32_t s_prevGalMask = 0;  // If you have GAL
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
static const int FAULTS_PER_PAGE = 6;
static void _Key1Release(void* userData);
static void _Key2Release(void* userData);
static void _Key3Release(void* userData);
static void _Key4Release(void* userData);
static void _Key5Release(void* userData);
static void _Key1Release(void* userData);
static void _Key2Release(void* userData);
static void _Key3Release(void* userData);
static void _Key4Release(void* userData);
static void _Key5Release(void* userData);
static void _AppendFaultsFromMask(std::vector<std::string>& faultVec, uint32_t mask, FAULT_CODE code);
void Scrn01FaultsCreate(void)
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
    SimpleTextDraw(lcd_get_width() / 2, 0, "Faults Screen", BLACK, 100, LAYER_FRONT);
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(180, 35, "Active Faults = ", BLACK, 100, LAYER_BACK);
    s_currentPage = 0;
}
void Scrn01FaultsEnter(void)
{
}
void Scrn01FaultsUpdate(void)
{
    fill_lcd_screen(ALPHA_COLOR, LAYER_FRONT);
    s_faultList.clear();

    DBELEMENT_T dbElement;
    uint32_t sta1mask = 0, sta2mask = 0, sta3mask = 0;
    uint32_t nfumask = 0, sfemask = 0, cfemask = 0;
    uint32_t galmask = 0;

    if (DataBase_Get(&dbElement, db_VECTOR_STA1_fault_error, 0)) {
        sta1mask = dbElement.Data.ui;
    }
    if (DataBase_Get(&dbElement, db_VECTOR_STA2_fault_error, 0)) {
        sta2mask = dbElement.Data.ui;
    }
    if (DataBase_Get(&dbElement, db_VECTOR_STA3_fault_error, 0)) {
        sta3mask = dbElement.Data.ui;
    }
    if (DataBase_Get(&dbElement, db_VECTOR_nfu_fault_error, 0)) {
        nfumask = dbElement.Data.ui;
    }
    if (DataBase_Get(&dbElement, db_VECTOR_signal_fault_error, 0)) {
        sfemask = dbElement.Data.ui;
    }
    if (DataBase_Get(&dbElement, db_VECTOR_cal_fault_error, 0)) {
        cfemask = dbElement.Data.ui;
    }
    if (DataBase_Get(&dbElement, db_VECTOR_GAL_fault_error, 0)) {
        galmask = dbElement.Data.ui;
    }

    // -- NEWLY ADDED: detect newly activated bits, so we can un-ack them
    _CheckNewlyActivatedBits(sta1mask, &s_prevSta1Mask, STA1);
    _CheckNewlyActivatedBits(sta2mask, &s_prevSta2Mask, STA2);
    _CheckNewlyActivatedBits(sta3mask, &s_prevSta3Mask, STA3);
    _CheckNewlyActivatedBits(nfumask, &s_prevNfuMask, NFU);
    _CheckNewlyActivatedBits(sfemask, &s_prevSfeMask, SFE);
    _CheckNewlyActivatedBits(cfemask, &s_prevCfeMask, CFE);
    _CheckNewlyActivatedBits(galmask, &s_prevGalMask, GAL);
    // --------------------------------

    // Now build s_faultList
    _AppendFaultsFromMask(s_faultList, sta1mask, STA1);
    _AppendFaultsFromMask(s_faultList, sta2mask, STA2);
    _AppendFaultsFromMask(s_faultList, sta3mask, STA3);
    _AppendFaultsFromMask(s_faultList, nfumask, NFU);
    _AppendFaultsFromMask(s_faultList, sfemask, SFE);
    _AppendFaultsFromMask(s_faultList, cfemask, CFE);
    _AppendFaultsFromMask(s_faultList, galmask, GAL);

    int faultCount = (int)s_faultList.size();
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 15, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);
    SimpleTextDraw(282, 35, std::to_string(faultCount).c_str(), BLACK, 100, LAYER_FRONT);
    int totalPages = (faultCount == 0) ? 1 : (faultCount + FAULTS_PER_PAGE - 1) / FAULTS_PER_PAGE;
    if (s_currentPage >= totalPages) {
        s_currentPage = totalPages - 1;
    }
    if (s_currentPage < 0) {
        s_currentPage = 0;
    }
    SimpleTextSetupFontEx(FONT_INDEX_TTMAIN, 18, HORIZONTAL_ALIGNMENT_LEFT, VERTICAL_ALIGNMENT_TOP, 0);
    int startIndex = s_currentPage * FAULTS_PER_PAGE;
    int endIndex = startIndex + FAULTS_PER_PAGE;
    if (endIndex > faultCount) {
        endIndex = faultCount;
    }
    int yPos = 60;
    for (int i = startIndex; i < endIndex; i++) {
        SimpleTextDraw(5, yPos, s_faultList[i].c_str(), BLACK, 100, LAYER_FRONT);
        yPos += 20;
    }
    char pageMsg[32];
    snprintf(pageMsg, sizeof(pageMsg), "Page %d / %d", s_currentPage + 1, totalPages);
    SimpleTextDraw(5, 35, pageMsg, BLACK, 100, LAYER_FRONT);
}
void Scrn01FaultsExit(void)
{
    s_currentPage = 0;
}
static void _AppendFaultsFromMask(std::vector<std::string>& faultVec,
    uint32_t mask,
    FAULT_CODE code)
{
    for (int i = 0; i < NUM_FAULT_ENTRIES; i++)
    {
        if (m_FAULTS_DB[i].FaultCode == code)
        {
            bool bitActive = ((mask & (1 << m_FAULTS_DB[i].Bit)) != 0);
            if (bitActive)
            {
                bool isAcked = m_FAULTS_DB[i].isAcked;
                if (isAcked)
                {
                    std::string line = std::string(m_FAULTS_DB[i].Description) + " (Ack)";
                    faultVec.push_back(line);
                }
                else
                {
                    faultVec.push_back(m_FAULTS_DB[i].Description);
                }
            }
        }
    }
}
static void _Key1Release(void* userData)
{
    MMIScreenGoto(SCREENID_START);
}
static void _Key2Release(void* userData)
{
    if (s_currentPage > 0)
    {
        s_currentPage--;
        Scrn01FaultsUpdate();
    }
}
static void _Key3Release(void* userData)
{
    DBELEMENT_T dbElement;
    uint32_t sta1mask = 0;
    uint32_t sta2mask = 0;
    uint32_t sta3mask = 0;
    uint32_t nfumask = 0;
    uint32_t sfemask = 0;
    uint32_t cfemask = 0;
    uint32_t galmask = 0;
    if (DataBase_Get(&dbElement, db_VECTOR_STA1_fault_error, 0)) {
        sta1mask = dbElement.Data.ui;
    }
    for (int i = 0; i < NUM_FAULT_ENTRIES; i++)
    {
        if (m_FAULTS_DB[i].FaultCode == STA1) {
            bool bitActive = ((sta1mask & (1 << m_FAULTS_DB[i].Bit)) != 0);
            if (bitActive) {
                m_FAULTS_DB[i].isAcked = true;
            }
        }
        if (m_FAULTS_DB[i].FaultCode == STA2) {
            bool bitActive = ((sta2mask & (1 << m_FAULTS_DB[i].Bit)) != 0);
            if (bitActive) {
                m_FAULTS_DB[i].isAcked = true;
            }
        }
        if (m_FAULTS_DB[i].FaultCode == STA3) {
            bool bitActive = ((sta3mask & (1 << m_FAULTS_DB[i].Bit)) != 0);
            if (bitActive) {
                m_FAULTS_DB[i].isAcked = true;
            }
        }
        if (m_FAULTS_DB[i].FaultCode == NFU) {
            bool bitActive = ((nfumask & (1 << m_FAULTS_DB[i].Bit)) != 0);
            if (bitActive) {
                m_FAULTS_DB[i].isAcked = true;
            }
        }
        if (m_FAULTS_DB[i].FaultCode == SFE) {
            bool bitActive = ((sfemask & (1 << m_FAULTS_DB[i].Bit)) != 0);
            if (bitActive) {
                m_FAULTS_DB[i].isAcked = true;
            }
        }
        if (m_FAULTS_DB[i].FaultCode == CFE) {
            bool bitActive = ((cfemask & (1 << m_FAULTS_DB[i].Bit)) != 0);
            if (bitActive) {
                m_FAULTS_DB[i].isAcked = true;
            }
        }
        if (m_FAULTS_DB[i].FaultCode == GAL) {
            bool bitActive = ((galmask & (1 << m_FAULTS_DB[i].Bit)) != 0);
            if (bitActive) {
                m_FAULTS_DB[i].isAcked = true;
            }
        }
    }
    Scrn01FaultsUpdate();
}
static void _Key4Release(void* userData)
{
    for (int i = 0; i < NUM_FAULT_ENTRIES; i++)
    {
        if (m_FAULTS_DB[i].isAcked == false)
        {
            m_FAULTS_DB[i].isAcked = true;
        }
    }
}
static void _Key5Release(void* userData)
{
}