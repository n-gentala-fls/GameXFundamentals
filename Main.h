#pragma once
#define GAME_NAME "GameX"
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

DWORD CreateMainGameWindow(void);
BOOL GameAlreadyRunning(void);