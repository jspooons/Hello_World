#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

HINSTANCE hInst;


// just as every C++ application, we must have a 'main'
// function as its starting point

// every Windows desktop application must have a WinMain
// function. 

// WinMain has the following syntax:
int CALLBACK WinMain(
	_In_ HINSTANCE hInstance, // a handle to the current instance of the application
	_In_opt_ HINSTANCE hPrevInstance, // a handle to the previous instance of the application
	_In_ LPSTR     lpCmdLine, // command line for the application
	_In_ int       nCmdShow // TBD
);
// your WinMain should initialize the application, display its
// main window, and enter a message retrieval-and-dispatch loop
// that is the top-level control structure for the remainder
// of the application's execution.


// Forward declarations of functions included in this code module:
// ________
// along with the WinMain function, every windows desktop 
// application must also have a window-procedure function.
LRESULT CALLBACK WndProc(
	_In_ HWND   hWnd,
	_In_ UINT   message,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);
// in this function, you write code to handle messages that the
// application receives from Windows events when events occur
// its called handling an event. You only handle events that
// are relevant for your application


int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{

	// structure of type WNDCLASSEX.
	WNDCLASSEX wcex;
	// contains info about the window
	// like application icon, backgroun color of window, name of
	// display in the title bar.
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

	// The parameters to CreateWindow explained:
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application dows not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 300,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	// returns an HWND, which is a handle to a window. A handle is somewhat like a pointer that Windows uses to keep track of open windows

	// At this point, the window has been created, but we still need to tell Windows to make it visible.


	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);
	// The displayed window doesn't have much content because you haven't yet implemented the WndProc function. In other words, the application isn't yet handling the messages that Windows is now sending to it.

	// To handle the messages, we first add a message loop to listen for the messages that Windows sends
	// When the application receives a message, this loop dispatches it to your WndProc function to be handled
	// Main message loop:
	MSG msg;
	// pointer to an MSG; handle to window whose messages are to be retrieved, if NULL, messages for any window that belongs to current thread and any messages on current thread's message queue whose hwnd value is NULL, -1? only messages on current thread's message queue whose hwnd value is NULL; int value of lowest message value to be retrieved; int value of highest msg value to be retrieved 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}


//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return

// now to add some functionality to this function
LRESULT CALLBACK WndProc(
	_In_ HWND   hWnd,
	_In_ UINT   message,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	// To enable the WndProc function to handle the messages that the application receives, implement a switch statement

	// important message to handle is the WM_PAINT message
	// received when part of its displayed window must be updated
	// event can occur when a user moves a window in front of your window
	// then moves it away again
	// to handle a WM_PAINT message, first call BeginPaint
	// then handle all the logic to lay out the text, buttons, 
	// and other controls in the window
	
	// the logic between the beginning call and the ending 
	// call displays the string "Hello, Windows desktop!" in 
	// the window

	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, Windows desktop!");

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.
		// For this introduction, we just print out "Hello, Windows desktop!"
		// in the top left corner.
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));
		// End application-specific layout section.

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	// HDC in the code is a handle to a device context, which is used to draw in the window's client area
	// Use the BeginPaint and EndPaint functions to prepare for and complete the drawing in the client area
	// BeginPaint returns a handle to the display device context used for drawing in the client area
	// EndPaint ends the paint request and releases the device context.
	// An application typically handles many other messages
	//  WM_CREATE when a window is first created
	//  WM_DESTROY when the window is closed



	return 0;
}

