#include "application.h"
#include "WindowClassExWrapper.h"
#include <windows.h>


WindowClassExWrapper * WindowClassExWrapper::style(UINT st)
{
	i_wce->style = st;
	return this;
}

WindowClassExWrapper * WindowClassExWrapper::windowProc(WNDPROC wndProc)
{
	i_wce->lpfnWndProc = wndProc;
	return this;
}

WindowClassExWrapper * WindowClassExWrapper::clsExtra(int ext)
{
	i_wce->cbClsExtra = ext;
	return this;
}

WindowClassExWrapper * WindowClassExWrapper::wndExtra(int ext)
{
	i_wce->cbWndExtra = ext;
	return this;
}

WindowClassExWrapper * WindowClassExWrapper::instance(HINSTANCE hInstance)
{
	i_wce->hInstance = hInstance;
	return this;
}

WindowClassExWrapper * WindowClassExWrapper::icon(UINT id)
{
	i_wce->hIcon = LoadIcon(i_wce->hInstance, MAKEINTRESOURCE(id));
	return this;
}

WindowClassExWrapper * WindowClassExWrapper::background(UINT color)
{
	i_wce->hbrBackground = (HBRUSH)color;
	return this;
}

WindowClassExWrapper * WindowClassExWrapper::iconSmall(UINT id)
{
	i_wce->hIconSm = LoadIcon(i_wce->hInstance, MAKEINTRESOURCE(id));
	return this;
}

WindowClassExWrapper * WindowClassExWrapper::cursor(const LPWSTR cursor)
{
	// Use predefined cursor as explained here:
	// https://msdn.microsoft.com/en-us/library/windows/desktop/ms648391(v=vs.85).aspx
	i_wce->hCursor = LoadCursor(nullptr, cursor);
	return this;
}

WindowClassExWrapper * WindowClassExWrapper::menuName(UINT id)
{
	i_wce->lpszMenuName = MAKEINTRESOURCEW(id);
	return this;
}

WindowClassExWrapper * WindowClassExWrapper::windowClass(const LPWSTR wndClass)
{
	i_wce->lpszClassName = wndClass;
	return this;
}

WNDCLASSEXW WindowClassExWrapper::unwrap()
{
	return *i_wce;
}
