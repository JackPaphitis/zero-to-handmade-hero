#pragma once
#include "platform.h"

struct Engine
{
	PlatformWindow* platform_window;
	PlatformApi* platform_api;
};

// creating window
// destroying window
// getting memory

Engine
init_engine(PlatformApi* platform_api, Arena arena);


