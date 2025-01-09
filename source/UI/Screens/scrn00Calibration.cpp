//------------------------------------------------------------------------------
//  TITLE :          scrn00Calibration.cpp
//  DESCRIPTION :    Implementation of scrn00Calibration screen
//  AUTHOR :         Nabil Lamriben 1/08/2025
//------------------------------------------------------------------------------
#include "scrn00Calibration.h"
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
void Scrn00CalibrationEnter(void)
{
    // to be implemented
}

void Scrn00CalibrationCreate(void)
{
    // to be implemented
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_1, _Key1Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_2, _Key2Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_3, _Key3Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_4, _Key4Release, nullptr);
    ButtonBarRegisterKeyReleaseCallback(KEYINDEX_5, _Key5Release, nullptr);
}

void Scrn00CalibrationUpdate(void)
{
    // to be implemented
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

