#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include "resource1.h"
using namespace std;


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND , UINT , WPARAM , LPARAM);


int
APIENTRY
wWinMain (
HINSTANCE hInstance ,
HINSTANCE hPrevInstance ,
LPWSTR lpCmdLine ,
int nShowCmd)
{
	// Setup window class attributes.
	WNDCLASSEX wcex;
	ZeroMemory (&wcex , sizeof( wcex ));


	wcex.cbSize = sizeof( wcex );	// WNDCLASSEX size in bytes
	wcex.style = CS_HREDRAW | CS_VREDRAW;		// Window class styles
	wcex.lpszClassName = TEXT ("MYFIRSTWINDOWCLASS");	// Window class name
	wcex.hbrBackground = (HBRUSH)( COLOR_WINDOW + 1 );	// Window background brush color.
	wcex.hCursor = LoadCursor (hInstance , IDC_ARROW); // Window cursor
	wcex.lpfnWndProc = WindowProcedure;		// Window procedure associated to this window class.
	wcex.hInstance = hInstance;	// The application instance.
	wcex.hIcon = LoadIcon (hInstance , MAKEINTRESOURCE (IDB_PNG1));


	// Register window and ensure registration success.
	if ( !RegisterClassEx (&wcex) )
		return 1;



	// Setup window initialization attributes.
	CREATESTRUCT cs;
	ZeroMemory (&cs , sizeof( cs ));

	cs.x = 0;	// Window X position
	cs.y = 0;	// Window Y position
	cs.cx = 1280;	// Window width
	cs.cy = 720;	// Window height
	cs.hInstance = hInstance; // Window instance.
	cs.lpszClass = wcex.lpszClassName;		// Window class name
	cs.lpszName = TEXT ("AGM Editor");	// Window title
	cs.style = WS_OVERLAPPEDWINDOW;		// Window style


	// Create the window.
	HWND hWnd = ::CreateWindowEx (
		cs.dwExStyle ,
		cs.lpszClass ,
		cs.lpszName ,
		cs.style ,
		cs.x ,
		cs.y ,
		cs.cx ,
		cs.cy ,
		cs.hwndParent ,
		cs.hMenu ,
		cs.hInstance ,
		cs.lpCreateParams);

	// Validate window.
	if ( !hWnd )
		return 1;

	// Display the window.
	::ShowWindow (hWnd , SW_SHOWDEFAULT);
	::UpdateWindow (hWnd);

	// Main message loop.
	MSG msg;
	while ( ::GetMessage (&msg , hWnd , 0 , 0) > 0 )
		::DispatchMessage (&msg);

	// Unregister window class, freeing the memory that was
	// previously allocated for this window.
	::UnregisterClass (wcex.lpszClassName , hInstance);

	return (int)msg.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd , UINT message , WPARAM wParam , LPARAM lParam)
{
	PAINTSTRUCT p;
	COLORREF color = RGB (0 , 0 , 0);
	HDC hdc;
	switch ( message )                  /* handle the messages */
	{
	case WM_DESTROY:
		PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
		break;
	case WM_PAINT:

		break;
	case WM_LBUTTONDOWN:
		break;

	case WM_LBUTTONUP:
		hdc = BeginPaint (hwnd , &p);
		
		EndPaint (hwnd , &p);
		InvalidateRect (hwnd , NULL , FALSE);//to paint more points and remain the prev points
		break;
	default:                      /* for messages that we don't deal with */
		return DefWindowProc (hwnd , message , wParam , lParam);
	}

	return 0;
}
