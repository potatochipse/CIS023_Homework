// Project:	CIS023_S2020_HW10 Miguel Antonio Logarta.cpp
// Author:	Miguel Antonio Logarta
// Date:	January 31, 2020
// Purpose:	Create a class definition
//			Create a pointer to an object from the class definition
//			Destroy the object pointer when the program closes
//			Call an object method

// #include "framework.h"
#include "CIS023_S2020_HW10 Miguel Antonio Logarta.h"

#define MAX_LOADSTRING 100

// We need a window for the text input, a button to capture it, and a static control to show the conversion
HWND hWnd_Input;								// Handle to input
HWND hWnd_Output;								// Handle to output
HWND hWnd_Button;								// Handle to button
StringConversionClass* StringConversionObject;	// Pointer to StringConversionClass Object

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CIS023S2020HW10MIGUELANTONIOLOGARTA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CIS023S2020HW10MIGUELANTONIOLOGARTA));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CIS023S2020HW10MIGUELANTONIOLOGARTA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+0);						// Make background gray
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CIS023S2020HW10MIGUELANTONIOLOGARTA);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 275, 180, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case BN_CLICKED:						// When the button is clicked...
				if (LOWORD(lParam) == (WORD)hWnd_Button)
				{
					TCHAR	szInput[TCHAR_SIZE];		// Array to hold the input
					string	strStringFromTCHAR;			// String returned from StringConversionObject
					TCHAR*	szTCHARFromString;			// TCHAR returned from StringConversionObject

					if (!StringConversionObject)								// If the object hasn't been created
					{
						StringConversionObject = new StringConversionClass;		// Create the new object
					}

					// Get user input
					SendMessage(					// Send message to window
						hWnd_Input,					// From the edit box
						WM_GETTEXT,					// Get the text
						TCHAR_SIZE,					// Of size TCHAR_SIZE
						LPARAM(szInput));			// To szInput (Destination)

					// Send user input to for conversion
					// Step e: Convert the input to a string
					strStringFromTCHAR = StringConversionObject->ConvertTCHARtoString(szInput);

					// Step f: Convert the string to a TCHAR
					szTCHARFromString = StringConversionObject->ConvertStringtoTCHAR(strStringFromTCHAR);

					// Output the TCHAR
					SetWindowText(
						hWnd_Output,				// The static control that's beside the button
						szTCHARFromString);			// The TCHAR that was converted from the string
				}
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_CREATE:
		// Text prompt for the user
		CreateWindow(
			TEXT("STATIC"),								// Label
			TEXT("Enter some text:"),					// Text on label
			WS_VISIBLE | WS_CHILD,						// Options
			10, 10, 135, 20,							// Location and size
			hWnd, NULL, NULL, NULL);					// Parent window

		// Create a window for text input
		hWnd_Input = CreateWindow(
			TEXT("EDIT"),								// Label
			TEXT(""),									// Blank
			WS_VISIBLE | WS_CHILD |						// Options
			WS_BORDER | ES_AUTOHSCROLL,
			145, 10, 100, 20,							// Size and location
			hWnd, NULL, NULL, NULL);					// Parent window

		// Create a button to capture the input
		hWnd_Button = CreateWindow(
			TEXT("BUTTON"),								// Label
			TEXT("SHOW"),								// Text on button
			WS_VISIBLE | WS_CHILD |						// Options
			WS_BORDER,
			10, 50, 100, 20,							// Size and location
			hWnd, NULL, NULL, NULL);					// Parent window

		// Create a window to show the output
		hWnd_Output = CreateWindow(
			TEXT("STATIC"),								// Static control window
			TEXT(""),									// Show blank
			WS_VISIBLE | WS_CHILD |						// Options
			WS_BORDER | ES_AUTOHSCROLL,
			120, 50, 125, 20,							// Location and size
			hWnd, NULL, NULL, NULL);					// Parent window

		break;
    case WM_DESTROY:
		if (StringConversionObject)						// If the object exists
		{
			delete StringConversionObject;				// Delete the object
		}
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
