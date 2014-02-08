//Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

#ifndef MFD_STUFF_HEADER
#define MFD_STUFF_HEADER

#include "resource.h"
#include <stdio.h>
#include "orbitersdk.h"
#include <windows.h>

HINSTANCE g_hInst;    // module instance handle
HBITMAP g_hPin;       // "pin" button bitmap
DWORD g_dwCmd;        // custom function identifier

inline BOOL CALLBACK MsgProc (HWND, UINT, WPARAM, LPARAM);
extern long FAR PASCAL MFD_WndProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern long FAR PASCAL MFD_BtnProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void InitMFD(HINSTANCE hDLL)
{
		// To allow the user to open our new dialog box, we create
	// an entry in the "Custom Functions" list which is accessed
	// in Orbiter via Ctrl-F4.

	// Load the bitmap for the "pin" title button
	g_hPin = (HBITMAP)LoadImage (g_hInst, MAKEINTRESOURCE(IDB_PIN), IMAGE_BITMAP, 15, 30, 0);

	// Register a window classes for the MFD display and buttons
	WNDCLASS wndClass;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc   = MFD_WndProc;
	wndClass.cbClsExtra    = 0;
	wndClass.cbWndExtra    = 0;
	wndClass.hInstance     = hDLL;
	wndClass.hIcon         = NULL;
	wndClass.hCursor       = LoadCursor (NULL, MAKEINTRESOURCE(IDC_ARROW));
	wndClass.hbrBackground = (HBRUSH)GetStockObject (BLACK_BRUSH);
	wndClass.lpszMenuName  = NULL;
	wndClass.lpszClassName = "ExtMFD_Display";
	RegisterClass (&wndClass);

	wndClass.lpfnWndProc   = MFD_BtnProc;
	wndClass.hbrBackground = (HBRUSH)GetStockObject (LTGRAY_BRUSH);
	wndClass.lpszClassName = "ExtMFD_Button";
	RegisterClass (&wndClass);
}

void ShutdownMFD (HINSTANCE hDLL)
{
	// Unregister window classes
	UnregisterClass ("ExtMFD_Display", g_hInst);
	UnregisterClass ("ExtMFD_Button", g_hInst);

	// Free bitmap resources
	DeleteObject (g_hPin);

	// Unregister the custom function in Orbiter
	oapiUnregisterCustomCmd (g_dwCmd);
}

#endif