#include <Windows.h>
#include "MainApplication.h"


void MainApplication::run(WindowComponent *wnd, MSG *msg)
{
	while (GetMessage(msg, nullptr, 0, 0))
	{
		TranslateMessage(msg);
		DispatchMessage(msg);
	}
}
