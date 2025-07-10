#include <stdio.h>
//We will be using windows APIs to interact with teh operating system
//Windows is natively UNICODE
#include <windows.h>
#include "Main.h"
//The entry point for a windows application is WinMain
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	if (GameAlreadyRunning()) //if the game is already running, exit
	{
		MessageBoxA(NULL, "Game is already running!", "Error", MB_ICONERROR | MB_OK);
        goto Exit;
	}
	//hInst is the handle to the current instance of the application
	if (CreateMainGameWindow() != ERROR_SUCCESS) 
	{
		MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONERROR | MB_OK);
		goto Exit;
	}

    MSG Msg = { 0 };

    while (GetMessageA(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
    }
    Exit:
	return (0);
}

LRESULT CALLBACK MainWndProc(
    HWND hwnd,        // handle to window
    UINT uMsg,        // message identifier
    WPARAM wParam,    // first message parameter
    LPARAM lParam)    // second message parameter
{
    LRESULT Result = 0;
    char buf[12] = { 0 };
	_itoa(uMsg, _countof(buf), 10);
    OutputDebugStringA(buf);
    OutputDebugStringA("\n");

    switch (uMsg) // What is the message that we are getting?
    {

    case WM_CLOSE:
	{
		PostQuitMessage(0);
	}
        default:
        {
           Result = DefWindowProc(hwnd, uMsg, wParam, lParam); //default window procedure
        }
    }
    return (Result);
}

DWORD CreateMainGameWindow(void)
{
    DWORD Result = ERROR_SUCCESS;

    //Since wc is a data structure, the parentheses are used to initialize
    WNDCLASSA wc = { sizeof(WNDCLASSA) };

    // Register the main window class.
    HWND WindowHandle = { 0 };
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = MainWndProc; //long pointer to a windows precedure function
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandleA(NULL);
    wc.hIcon = LoadIconA(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(WHITE_BRUSH); //background color
    wc.lpszMenuName = "MainMenu"; //long pointer to a string
    wc.lpszClassName = GAME_NAME "_WINDOWCLASS";

    if (RegisterClassA(&wc) == 0) { 

        Result = GetLastError();

        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONERROR | MB_OK);

		goto Exit; 
    }
    //windows wont assume you want to close the application when you close the window, so you have to do it yourself
    WindowHandle = CreateWindowExA(
        WS_EX_CLIENTEDGE, wc.lpszClassName, "Window Name", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        240, 120, 240, 120, NULL, NULL, NULL, NULL
    );



    if (WindowHandle == NULL) { //if the window creation fails, return false
		Result = GetLastError();
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONERROR | MB_OK);
		goto Exit; 
    }

Exit:
	return(Result);

}

BOOL GameAlreadyRunning(void)
{
	HANDLE hMutex = NULL;
	hMutex = CreateMutexA(NULL, TRUE, GAME_NAME "_MUTEX");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        return(TRUE);
    }
    else {
		return(FALSE);
    }
}


