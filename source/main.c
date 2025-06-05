/*
	BonkClicker - a goofy clicker for WinAPI
	Made by Applehat. (github.com/ApplehatDot)
	
*/ 

#include <windows.h>
#include <stdio.h>
#include "PredFunc.c"

HWND hClicka, hText;
HBITMAP hBitmap;
int points = 0;

void UpdatePointsText() {
    wchar_t buffer[64];
    swprintf(buffer, 64, L"Points: %d", points);
    SetWindowTextW(hText, buffer);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch(uMsg){
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_CREATE:
			hText = CreateWindowExW(
				0,
				L"STATIC",
				L"Points: 0",
				WS_CHILD | WS_VISIBLE,
				70, 50, 130, 20,
				hwnd,
				NULL,
				GetModuleHandle(NULL),
				NULL
			);
			
			SetSystemThemeFont(hText);
			
			hClicka = CreateWindowExW(
				0, 
				L"BUTTON",
				L"bonk",
				WS_VISIBLE | WS_CHILD | BS_BITMAP,
				70, 100, 130, 130,
				hwnd,
				(HMENU)100, 
				GetModuleHandle(NULL), 
				NULL
			);
			
			hBitmap = (HBITMAP)LoadImageW(
                NULL,
                L"bonk.bmp",      // Ścieżka do pliku BMP
                IMAGE_BITMAP,
                0, 0,
                LR_LOADFROMFILE
            );
            if (hBitmap) {
                SendMessageW(hClicka, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
            }
            break;
			
		case WM_COMMAND:
            if (LOWORD(wParam) == 100) { // Przycisk bonk
                points++; // Zwiększ punkty
                UpdatePointsText(); // Aktualizuj wyświetlany tekst
            }
            break;
		default:
			return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	}
	
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	const wchar_t CLASS_NAME[] = L"MainClickWnd";
	
	WNDCLASSW wc = {};
	
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	
	if(!RegisterClassW(&wc)){
		MessageBoxW(NULL, L"Window Registration Failed", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	
	HWND hwnd = CreateWindowExW(
		0,
		CLASS_NAME,
		L"BonkClicker",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		300, 300,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	MSG msg = {};
	while(GetMessage(&msg, NULL, 0, 0) > 0){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
	
}