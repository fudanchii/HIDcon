#include <windows.h>
#include "WindowComponent.h"

WindowComponent *WindowComponent::create()
{
	HWND hwnd = CreateWindowW(i_className, i_title, i_style,
		i_x, i_y, i_width, i_height, i_hWndParent, i_hMenu,	i_hInstance, i_lpParam);

	ShowWindow(hwnd, i_showWindow);
	UpdateWindow(hwnd);

	return this;
}
