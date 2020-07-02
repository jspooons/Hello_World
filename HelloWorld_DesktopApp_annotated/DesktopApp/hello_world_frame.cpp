#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

HINSTANCE hInst;

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance, // a handle to the current instance of the application
	_In_opt_ HINSTANCE hPrevInstance, // a handle to the previous instance of the application
	_In_ LPSTR     lpCmdLine, // command line for the application
	_In_ int       nCmdShow // TBD
)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); // size, in bytes of this structure
	wcex.style = CS_HREDRAW | CS_VREDRAW; // class style(s), describes how to update window after moving or resizing it, how to process double-clicks of the mouse, how to allocate space for the device context, and other aspects of the window
	wcex.lpfnWndProc = WndProc; // pointer to the window procedure
	wcex.cbClsExtra = 0; // no. of extra bytes to allocate following the window-class structure
	wcex.cbWndExtra = 0; // no. of extra bytes to allocate following the window instrance
	wcex.hInstance = hInstance; // A handle to the instance that contains the window procedure for the class.
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION); // A handle to the class icon. This member must be a handle to an icon resource. If this member is NULL, the system provides a default icon.
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); // A handle to the class cursor. This member must be a handle to a cursor resource. If this member is NULL, an application must explicitly set the cursor shape whenever the mouse moves into the application's window.
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // A handle to the class background brush. This member can be a handle to the brush to be used for painting the background, or it can be a color value
	wcex.lpszMenuName = NULL; // Pointer to a null-terminated character string that specifies the resource name of the class menu, as the name appears in the resource file
	wcex.lpszClassName = szWindowClass; // Distinguishes the class from other registered classes.
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION); // A handle to a small icon that is associated with the window class

	// Register the WNDCLASSEX with Windows so that it knows about your window and how to send messages to it. Use the RegisterClassEx function and pass the window class structure as an argument. The _T macro is used because we use the TCHAR type
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	// Store instance handle in our global variable
	hInst = hInstance;

	HWND hWnd = CreateWindow(
		szWindowClass, // name of application
		szTitle, // name of application
		WS_OVERLAPPEDWINDOW, // type of window to create
		CW_USEDEFAULT, CW_USEDEFAULT, // initial position
		500, 300, // initial size (w,l)
		NULL, // parent of this window
		NULL, // this app. does not have a menu bar
		hInstance, // first parameter from WinMain
		NULL // not used in this app.
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}


//  PURPOSE:  Processes messages for the main window.
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(
	_In_ HWND   hWnd,
	_In_ UINT   message,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, Windows desktop!");

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		TextOut(hdc, 5, 5, greeting, _tcslen(greeting));

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}