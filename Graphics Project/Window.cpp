#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include<vector>
#include "resource1.h"
#include"Editor.h"
#include"Clipping.h"
#include"Ellipse.h"
#include"Line.h"
#include"Curves.h"
using namespace std;


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND , UINT , WPARAM , LPARAM);
bool HandleMenuItem (HWND , HDC , COLORREF);

int menuItemsId;
Editor myEditor;

int counter;
vector<Point> Points;

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
	wcex.lpszMenuName = MAKEINTRESOURCE (MY_MENU);



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
	COLORREF color = RGB (255 , 0 , 0);

	HDC hdc;
	switch ( message )                  /* handle the messages */
	{
	case WM_DESTROY:
		PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
		break;

	case WM_COMMAND:
		menuItemsId = wParam;

	case WM_PAINT:
		hdc = BeginPaint (hwnd , &p);
		HandleMenuItem (hwnd,hdc,color);
		EndPaint (hwnd , &p);
		InvalidateRect (hwnd , NULL , FALSE);//to paint more points and remain the prev points
		break;

	case WM_LBUTTONDOWN:
		if ( counter < 4 ){

			Point point (LOWORD (lParam) , HIWORD (lParam));
			Points.push_back (point);
			counter++;
		}

		break;

	default:                      /* for messages that we don't deal with */
		return DefWindowProc (hwnd , message , wParam , lParam);
	}

	return 0;
}

bool HandleMenuItem (HWND hwnd , HDC hdc , COLORREF color)
{
	Clipping myClipp;
	AGMEllipse ellipse;	
	Line myLine;
	//Curves myCurve;

	switch ( menuItemsId )
	{

	case ID_FILE_EXIT:	
		DestroyWindow (hwnd);
		return true;

	case ID_LINE_DDA:	   
		if ( Points.size () == 2 ){
			myLine.drawLineDDA (hdc , Points[0].x , Points[0].y , Points[1].x , Points[1].y , color);
			counter = 0;
			Points.clear ();
			return true;
		}
		else {
			return false;
		}
	
	case ID_LINE_MIDPOINT:
		if ( Points.size () == 2 ){
			myLine.drawLineMidPoint (hdc , Points[0].x , Points[0].y , Points[1].x , Points[1].y , color);
			counter = 0;
			Points.clear ();
			return true;
		}
		else {
			return false;
		}
	case ID_LINE_PARAMETRIC:
		if ( Points.size () == 2 ){
			myLine.drawLineParam (hdc , Points[0].x , Points[0].y , Points[1].x , Points[1].y , color);
			counter = 0;
			Points.clear ();
			return true;
		}
		else {
			return false;
		}
		
	case ID_ELLIPSE_DIRECT:
		if ( Points.size () == 2 ){
			ellipse.drawEllipseDirect(hdc , Points[0].x , Points[0].y , Points[1].x , Points[1].y , color);
			counter = 0;
			Points.clear ();
			return true;
		}
		else {
			return false;
		}

	case ID_ELLIPSE_POLAR:
		if ( Points.size () == 2 ){
			ellipse.drawEllipsePolar (hdc , Points[0].x , Points[0].y , Points[1].x , Points[1].y , color);
			counter = 0;
			Points.clear ();
			return true;
		}
		else {
			return false;
		}
	case ID_ELLIPSE_MIDPOINT:
		if ( Points.size () == 2 ){
			ellipse.drawEllipseMidPoint (hdc , Points[0].x , Points[0].y , Points[1].x , Points[1].y , color);
			counter = 0;
			Points.clear ();
			return true;
		}
		else {
			return false;
		}
	case ID_CLIPPING_POLYGON:
		myClipp.DrawRectangle (hdc);
		if ( Points.size () == 4 ){
			myClipp.DrawInitialPolygon (hdc , Points);
			myClipp.PolygonClip (hdc , Points);
			counter = 0;
			Points.clear ();
			return true;
		}
		else {
			return false;
		}
		//ID_CURVES_BEZIER
	case ID_CURVES_BEZIER:
		break;
		//ID_CURVES_HERMITE
	case ID_CURVES_HERMITE:
		break;
		//ID_CURVES_SPLINES
	case ID_CURVES_SPLINES:
		break;
		//ID_EDIT_SAVE
	case ID_EDIT_SAVE:
		break;
		//ID_EDIT_LOAD
	case ID_EDIT_LOAD:
		break;
	default:
		return false;
	}

}
