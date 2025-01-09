//------------------------------------------------------------------------------
//  TITLE :          scrn00SysOpt.cpp
//  DESCRIPTION :    Implementation of scrn00SysOpt screen
//  AUTHOR :         Nabil Lamriben 1/08/2025
//------------------------------------------------------------------------------
#include "scrn00SysOpts.h"
#include "UI/screens.h"
#include <iostream>
#include <string>

//------------------------------------------------------------------------------
// LOCAL FUNCTION PROTOTYPES
//------------------------------------------------------------------------------
static void _Key1Release(void* userData);
static void _Key2Release(void* userData);
static void _Key3Release(void* userData);
static void _Key4Release(void* userData);
static void _Key5Release(void* userData);

//------------------------------------------------------------------------------
// PUBLIC FUNCTIONS
//------------------------------------------------------------------------------
void Scrn00SysOptEnter(void)
{
     
}

void Scrn00SysOptCreate(void)
{
    vLcdBlankerEx(MAKERGB565(200, 200, 200), ALPHA_COLOR); // Set gray background

    // Setup buttons and their callbacks
    ButtonBarSetHeight(48);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_1, _Key1Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_2, _Key2Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_3, _Key3Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_4, _Key4Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_5, _Key5Release, nullptr);
}

void Scrn00SysOptUpdate(void)
{
    vLcdBlankerEx(MAKERGB565(100, 100, 100), ALPHA_COLOR); // Example: Darker gray background
    
}

void Scrn00SysOptExit(void)
{
    
}

//------------------------------------------------------------------------------
// LOCAL FUNCTIONS
//------------------------------------------------------------------------------
static void _Key1Release(void* userData)
{
   
}

static void _Key2Release(void* userData)
{
    
}

static void _Key3Release(void* userData)
{
    
}

static void _Key4Release(void* userData)
{
    
}

static void _Key5Release(void* userData)
{
   
}
