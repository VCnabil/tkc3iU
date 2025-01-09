//------------------------------------------------------------------------------
//  TITLE :          scrn00Autocal.cpp
//  DESCRIPTION :    Implementation of scrn00Autocal screen
//  AUTHOR :         Nabil Lamriben 1/08/2025
//------------------------------------------------------------------------------
#include "scrn00Autocal.h"
#include "UI/screens.h"

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
void Scrn00AutocalEnter(void)
{
    // to be implemented
}

void Scrn00AutocalCreate(void)
{
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);
    // to be implemented
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_1, _Key1Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_2, _Key2Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_3, _Key3Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_4, _Key4Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_5, _Key5Release, nullptr);
}

void Scrn00AutocalUpdate(void)
{
    vLcdBlankerEx(MAKERGB565(121, 137, 121), ALPHA_COLOR);
    // to be implemented
}

void Scrn00AutocalExit(void)
{
    // to be implemented
}

//------------------------------------------------------------------------------
// LOCAL FUNCTIONS
//------------------------------------------------------------------------------
static void _Key1Release(void* userData)
{
    // to be implemented
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
    // to be implemented
}
