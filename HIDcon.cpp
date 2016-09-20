#include "stdafx.h"
#include "HIDcon.h"
#include "hidapi.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    LoadDevice(HWND, UINT, WPARAM, LPARAM);

int  getTextFrom(HWND, UINT, char*, size_t);
void ListHIDEnumeration(HWND);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	MSG msg;
	int res;

	MainApplication      app(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	WindowClassExWrapper *wndCls;
	WindowComponent      *mainWindow;

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_HIDCON, szWindowClass, MAX_LOADSTRING);

	app.setTitle(szTitle);

	wndCls = (new WindowClassExWrapper)->windowClass(szWindowClass)
		->windowProc(WndProc)
		->instance(hInstance)
		->icon(IDI_HIDCON)
		->iconSmall(IDI_SMALL)
		->menuName(IDC_HIDCON);

	app.registerWindowClass(wndCls);

	mainWindow = (new WindowComponent)->className(szWindowClass)
		->hInstance(hInstance)
		->title(szTitle)
		->style(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
		->dimension(640, 480)
		->position(CW_USEDEFAULT, 0)
		->showWindow(nCmdShow)
		->create();

	res = hid_init();

	app.run(mainWindow, &msg);

	delete wndCls;
	delete mainWindow;

	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		HWND hEdit;
		RECT rcClient;

		GetClientRect(hWnd, &rcClient);

		hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"Select Load from App menu ^",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL,
			0, 0, rcClient.right, rcClient.bottom, hWnd, (HMENU)IDC_MAIN_EDIT, GetModuleHandle(NULL), NULL);
		if (hEdit == NULL)
			MessageBox(hWnd, L"Could not create edit box.", L"Error", MB_OK | MB_ICONERROR);
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ENUMERATE:
			ListHIDEnumeration(hWnd);
			break;
		case IDM_LOAD:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DEVDIALOG), hWnd, LoadDevice);
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
	case WM_DESTROY:
		hid_exit();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


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

INT_PTR CALLBACK LoadDevice(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
		{
			static char buf[10];
			HWND hEdit = GetDlgItem(GetParent(hDlg), IDC_MAIN_EDIT);

			getTextFrom(hDlg, IDC_EDIT1, buf, 10);
			SetWindowText(hEdit, (LPCWSTR)buf);
		}
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}


void ListHIDEnumeration(HWND hWnd)
{
}


int getTextFrom(HWND hWnd, UINT item, char *buff, size_t len)
{
	size_t aln = GetWindowTextLength(GetDlgItem(hWnd, item));
	memset(buff, 0, len);
	if (!aln)
	{
		return 0;
	}
	if (aln > len - 1)
	{
		GetDlgItemText(hWnd, item, (LPWSTR)buff, len);
		return len;
	}
	GetDlgItemText(hWnd, item, (LPWSTR)buff, aln + 1);
	return aln;
}
