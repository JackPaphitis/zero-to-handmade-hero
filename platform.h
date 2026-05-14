#pragma once

struct PlatformWindow;

struct PlatformApi
{
	PlatformWindow* (*create_window)(const wchar_t *);
	int (*pump_messages)();
};
