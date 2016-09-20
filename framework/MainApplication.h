#pragma once
#include <windows.h>
#include "application.h"
#include "MessageActionTable.h"
#include "WindowClassExWrapper.h"
#include "WindowComponent.h"

class MainApplication
{
public:
	MainApplication(HINSTANCE hInstance)
		: i_hinstance(hInstance)
	    , i_cmdShow(1) {};

	MainApplication(HINSTANCE hInstance, HINSTANCE, LPWSTR, int cmdShow)
		: i_hinstance(hInstance)
	    , i_cmdShow(cmdShow) {};

	~MainApplication() {};

	void setTitle(const LPWSTR title) { i_title = title; };

	void registerWindowClass(WindowClassExWrapper *wce) {
		RegisterClassExW(&wce->unwrap());
	};

	void run(WindowComponent*, MSG*);

private:
	int                   i_cmdShow;
	LPWSTR                i_title;
	WindowClassExWrapper *i_wce;
	HINSTANCE             i_hinstance;
	HWND                  i_hwnd;
};