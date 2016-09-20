#pragma once
#include "application.h"
#include <windows.h>

class WindowClassExWrapper {
public:
	WindowClassExWrapper()
		: i_wce(new WNDCLASSEXW) {
		//memset(i_wce, 0, sizeof(WNDCLASSEXW));
		i_wce->cbSize = sizeof(WNDCLASSEX);
		i_wce->style = CS_HREDRAW | CS_VREDRAW;
		i_wce->cbClsExtra = 0;
		i_wce->cbWndExtra = 0;
		i_wce->hCursor = LoadCursor(nullptr, IDC_ARROW);
		i_wce->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	};


	WindowClassExWrapper *style(UINT);
	WindowClassExWrapper *windowProc(WNDPROC);
	WindowClassExWrapper *clsExtra(int);
	WindowClassExWrapper *wndExtra(int);
	WindowClassExWrapper *instance(HINSTANCE);
	WindowClassExWrapper *icon(UINT);
	WindowClassExWrapper *background(UINT);
	WindowClassExWrapper *iconSmall(UINT);
	WindowClassExWrapper *cursor(const LPWSTR);
	WindowClassExWrapper *menuName(UINT);
	WindowClassExWrapper *windowClass(const LPWSTR);

	WNDCLASSEXW unwrap();

	~WindowClassExWrapper() { delete i_wce;	};
private:
	WNDCLASSEXW *i_wce;
};
