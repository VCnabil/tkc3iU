//------------------------------------------------------------------------------
//  AUTHOR :			Nabil Lamriben 1/08/2025
//  TITLE :          scrnStart00.cpp
//  DESCRIPTION :    Implementation of scrnStart00 screen
//------------------------------------------------------------------------------
#include "scrn00Start.h"
#include "UI/screens.h"
#include <iostream>
#include <string>
 
//------------------------------------------------------------------------------
// Global variables for background color
//------------------------------------------------------------------------------
static uint8_t red = 121, green = 137, blue = 121; // Initial RGB values

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
void Scrn00StartEnter(void)
{ 
}

void Scrn00StartCreate(void)
{	
	vLcdBlankerEx(MAKERGB565(red, green, blue), ALPHA_COLOR);
	// Setup buttons and their callbacks
	ButtonBarSetHeight(48);
   	ButtonBarRegisterKeyReleaseCallback(KEYINDEX_1, _Key1Release, nullptr);
	ButtonBarRegisterKeyReleaseCallback(KEYINDEX_2, _Key2Release, nullptr);
	ButtonBarRegisterKeyReleaseCallback(KEYINDEX_3, _Key3Release, nullptr);
	ButtonBarRegisterKeyReleaseCallback(KEYINDEX_4, _Key4Release, nullptr);
	ButtonBarRegisterKeyReleaseCallback(KEYINDEX_5, _Key5Release, nullptr);
}

void Scrn00StartUpdate(void)
{
	// Update the background color
	vLcdBlankerEx(MAKERGB565(red, green, blue), ALPHA_COLOR);
	// run updates here
}

void Scrn00StartExit(void)
{
  
}

//------------------------------------------------------------------------------
// LOCAL FUNCTIONS
//------------------------------------------------------------------------------
static void _Key1Release(void* userData)
{
    // Add actions for Key 1 release
}

static void _Key2Release(void* userData)
{
    // Add actions for Key 2 release
}

static void _Key3Release(void* userData)
{
    // Add actions for Key 3 release
}

static void _Key4Release(void* userData)
{
    // Add actions for Key 4 release
}

static void _Key5Release(void* userData)
{
    // Add actions for Key 5 release
}