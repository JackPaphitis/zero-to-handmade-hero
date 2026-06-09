#include "win32_platform.h"

static LRESULT CALLBACK 
win32_window_proc(
		HWND	hwnd, 
		UINT	message, 
		WPARAM	wParam,
		LPARAM	lParam)
{
	switch (message)
	{
		case WM_SIZE:
		{
			// TODO dealing with resize of window
		} break;
		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
		} break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		} break;
		default:
		{
			return DefWindowProcW(hwnd, message, wParam, lParam);
		}
	}
	return 0;
}

PlatformWindow*
win32_create_window(Arena* arena)
{
	const wchar_t* class_name = L"Zero to Handmade Hero";

	HINSTANCE hInstance = GetModuleHandle(NULL);

	WNDCLASSW wc		= {0};
	wc.lpfnWndProc		= win32_window_proc;
	wc.hInstance		= hInstance;
	wc.lpszClassName	= class_name;

	RegisterClassW(&wc);

	HWND hwnd = CreateWindowExW(
			0,
			class_name,
			class_name,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 
			CW_USEDEFAULT, 
			800,
			400, 
			NULL, 
			NULL, 
			hInstance, 
			NULL);
	
	if (hwnd == 0)
	{
		OutputDebugStringW(L"Handle to window is 0");
		return NULL;	
	}

	PlatformWindow* platform_window
		= (PlatformWindow*)arena_push(
				arena, 
				sizeof(PlatformWindow), 
				DEFAULT_ALIGNMENT);

	platform_window->handle		= hwnd;
	platform_window->class_name = class_name;

	win32_show_window(platform_window);

	return platform_window;
}

int 
win32_pump_messages()
{
	MSG msg = {0};
	while(PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
	{
		if(msg.message == WM_QUIT)
		{
			return 0;
		}
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}

int
win32_show_window(PlatformWindow* window)
{
	HWND handle = window->handle;	
	int window_shown = ShowWindow(handle, SW_SHOW);

	return window_shown; 
}

MemoryChunk
win32_init_memory(size_t size)
{
	MemoryChunk mem	= {0};
	mem.begin		= (u8*)VirtualAlloc(0, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	mem.size		= size;
	return mem;
}



int
win32_destroy_memory(MemoryChunk* mem)
{
	int destroyed	= VirtualFree(mem->begin, 0, MEM_RELEASE);	
	mem->begin		= 0;
	mem->size		= 0;
	return destroyed;
}









