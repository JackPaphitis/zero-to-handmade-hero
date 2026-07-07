#include "win32_platform.h"

static int
win32_show_window(PlatformWindow* window);

static LRESULT CALLBACK 
win32_window_proc(
		HWND	hwnd, 
		UINT	message, 
		WPARAM	wParam,
		LPARAM	lParam)
{
	switch (message)
	{
		case WM_SIZE: // This gets called when we resize the window
		{
			// TODO dealing with resize of window
		} break;
		case WM_CLOSE: // This is the message that user has asked to close window
		{
			DestroyWindow(hwnd);
		} break;
		case WM_DESTROY: // This is the message the window has been destroyed
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
	const wchar_t* class_name = L"zthm-engine";

	HINSTANCE hInstance = GetModuleHandle(NULL);

	WNDCLASSW wc		= {0};
	wc.lpfnWndProc		= win32_window_proc;
	wc.hInstance		= hInstance;
	wc.lpszClassName	= class_name;

	// TODO(Jack): Check this return value
	RegisterClassW(&wc);

	HWND hwnd = CreateWindowExW(
			0,
			class_name,
			L"Zero to handmade hero engine window",
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
	platform_window->dc			= GetDC(hwnd);

	win32_show_window(platform_window);

	return platform_window;
}

void
win32_destroy_window(PlatformWindow* window)
{
	int dc_released			= ReleaseDC(window->handle, window->dc);
	int window_destroyed	= DestroyWindow(window->handle);

	//TODO(Jack): When logger or error handling, comeback
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
		DispatchMessageW(&msg);
	}

	return 1;
}

static int
win32_show_window(PlatformWindow* window)
{
	HWND handle = window->handle;	
	int window_shown = ShowWindow(handle, SW_SHOW);

	return window_shown; 
}

MemoryChunk
win32_init_memory(size_t capacity)
{
	MemoryChunk mem	= {0};
	mem.begin		= (u8*)VirtualAlloc(0, capacity, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	mem.capacity	= capacity;
	return mem;
}

int
win32_destroy_memory(MemoryChunk* mem)
{
	int destroyed	= VirtualFree(mem->begin, 0, MEM_RELEASE);	
	mem->begin		= 0;
	mem->capacity	= 0;
	return destroyed;
}

FileData*
win32_read_file(
		const wchar_t*	path, 
		Arena*			arena)
{
	HANDLE file_handle = CreateFileW(
			path,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);

	if (file_handle == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	size_t restore_point = arena_save(arena);

	FileData* file = (FileData*)arena_push(
			arena,
			sizeof(FileData),
			DEFAULT_ALIGNMENT);
	
	LARGE_INTEGER file_size = {0};

	if (!GetFileSizeEx(file_handle, &file_size))
	{
		arena_restore(arena, restore_point);
		CloseHandle(file_handle);
		return 0;
	}
	
	// TODO(Jack): is this big enough?
	file->size = (u32)file_size.QuadPart;

	file->file_bytes = (char*)arena_push(
			arena,
			file->size + 1, 
			DEFAULT_ALIGNMENT);

	DWORD bytes_read = 0;
	int file_read = ReadFile(
			file_handle,
			file->file_bytes,
			file->size,
			&bytes_read,
			NULL);
	int correct_size = (bytes_read == file->size); 

	CloseHandle(file_handle);

	if (!(file_read && correct_size))
	{
		arena_restore(arena, restore_point);
		return 0;
	}

	file->file_bytes[file->size] = 0;
	return file;
}

int
win32_write_file(
	const wchar_t*	path,
	FileData*		file_data)
{
	HANDLE file_handle = CreateFileW(
			path,
			GENERIC_WRITE,
			NULL,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);
	
	if (file_handle == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	
	DWORD bytes_written = 0;
	int file_written = WriteFile(
			file_handle,
			file_data->file_bytes,
			file_data->size,
			&bytes_written,
			NULL);

	CloseHandle(file_handle);
	
	return file_written && (bytes_written == file_data->size);
}




























