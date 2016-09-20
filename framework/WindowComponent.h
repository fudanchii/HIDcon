#include <windows.h>

#pragma once
class WindowComponent
{
public:
	WindowComponent()
	: i_hWndParent(nullptr)
	, i_hMenu(nullptr)
	, i_lpParam(nullptr) {};

	~WindowComponent() {};

	WindowComponent *create();

	WindowComponent *className(LPWSTR clName) {
		i_className = clName;
		return this;
	};

	WindowComponent *style(DWORD set) {
		i_style = set;
		return this;
	};

	WindowComponent *dimension(int w, int h) {
		i_width = w;
		i_height = h;
		return this;
	};

	WindowComponent *hInstance(HINSTANCE instance) {
		i_hInstance = instance;
		return this;
	};

	WindowComponent *position(int x, int y) {
		i_x = x;
		i_y = y;
		return this;
	};

	WindowComponent *showWindow(int shwWnd) {
		i_showWindow = shwWnd;
		return this;
	};

	WindowComponent *title(LPWSTR ttle) {
		i_title = ttle;
		return this;
	};

private:
	LPWSTR    i_className;
	DWORD     i_style;
	int       i_height;
	int       i_width;
	int       i_x;
	int       i_y;
	int       i_showWindow;
	LPWSTR    i_title;
	HINSTANCE i_hInstance;
	HWND      i_hWndParent;
	HMENU     i_hMenu;
	LPVOID    i_lpParam;
};

