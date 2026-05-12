#pragma once

#include <Windows.h>

struct PlatformWindow
{
	HWND handle;
	LPCWSTR class_name;
};

LRESULT CALLBACK 
WindowProc(
		HWND hwnd, 
		UINT message, 
		WPARAM wParam,
		LPARAM lParam);

PlatformWindow*
win32_create_window(
		LPCWSTR class_name,
		HINSTANCE hInstance);
