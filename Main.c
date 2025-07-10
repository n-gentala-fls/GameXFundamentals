#include <stdio.h>
//We will be using windows APIs to interact with teh operating system
//Windows is natively UNICODE
#include <windows.h>
#

//declared early because without this, the top down approach in c uses MainWndProc before it is declared
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//The entry point for a windows application is WinMain
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	//hInst is the handle to the current instance of the application
    memcpy_s();

	//Since wc is a data structure, the parentheses are used to initialize
    WNDCLASSA wc = { sizeof(WNDCLASSA) };

    // Register the main window class.
    HWND WindowHandle = { 0 };
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = MainWndProc; //long pointer to a windows precedure function
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIconA(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(WHITE_BRUSH); //background color
    wc.lpszMenuName = "MainMenu"; //long pointer to a string
    wc.lpszClassName = "GAMEX_CLASS";

    if (!RegisterClassA(&wc)) { //always check documentation when using other people's methods. It may not return 0 like you would think!


		MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONERROR | MB_OK);
		return FALSE; //if the window registration fails, return false
    }
	//windows wont assume you want to close the application when you close the window, so you have to do it yourself
    WindowHandle = CreateWindowExA(
        WS_EX_CLIENTEDGE, wc.lpszClassName, "Window Name", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		240, 120, 240, 120, NULL, NULL, NULL, NULL
    );



    if (WindowHandle == NULL) { //if the window creation fails, return false
		MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONERROR | MB_OK);
		return FALSE;
	}

	//ShowWindow(WindowHandle, TRUE); //Show the window








	//Loop will take the messages that window will recieve
	//Moving of a mouse over window, any action, etc.
	MSG Msg;

    while (GetMessageA(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
    }

	return (0);
}


LRESULT CALLBACK MainWndProc(
    HWND hwnd,        // handle to window
    UINT uMsg,        // message identifier
    WPARAM wParam,    // first message parameter
    LPARAM lParam)    // second message parameter
{

	switch (uMsg) // What is the message that we are getting?
    {
        case WM_CREATE:
            // Initialize the window. 
            return 0;

        case WM_PAINT:
            // Paint the window's client area. 
            return 0;

        case WM_SIZE:
            // Set the size and position of the window. 
            return 0;

        case WM_DESTROY:
            // Clean up window-specific data objects. 
            return 0;

       

    default:
        return DefWindowProcA(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}


