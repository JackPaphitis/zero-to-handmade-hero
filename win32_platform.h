#pragma once

#include <Windows.h>

struct PlatformWindow
{
	HWND handle;
	LPCWSTR class_name;
};

LRESULT CALLBACK 
win32_window_proc(
		HWND hwnd, 
		UINT message, 
		WPARAM wParam,
		LPARAM lParam);

PlatformWindow*
win32_create_window(LPCWSTR class_name);

int 
win32_pump_messages();
