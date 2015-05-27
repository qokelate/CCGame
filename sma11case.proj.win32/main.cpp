#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

#if _MSC_VER > 1700
#pragma comment(lib,"libcocos2d_2013.lib")
#pragma comment(lib,"libbox2d_2013.lib")
#pragma comment(lib,"libSpine_2013.lib")
#else
#pragma comment(lib,"libcocos2d_2012.lib")
#pragma comment(lib,"libbox2d_2012.lib")
#pragma comment(lib,"libSpine_2012.lib")
#endif

BOOL WINAPI ConsoleCreate()
{
	if (!AttachConsole(GetCurrentProcessId()))
	{
		if (!AllocConsole()) return FALSE;
		AttachConsole(GetCurrentProcessId());
		FILE* f = NULL;
		f = freopen("CONOUT$", "wb", stdout);  // reopen stout handle as console window output
		if (f == NULL) f = freopen("CON", "w", stdout);  // reopen stout handle as console window output
		f = freopen("CONOUT$", "wb", stderr); // reopen stderr handle as console window output
//		f = freopen("CONIN$", "rb", stdin);   // reopen stdin handle as console window input
		setvbuf(stdout, NULL, _IONBF, 0);
	}
	else
	{
		HWND hwConsoleWindow = GetConsoleWindow();
		ShowWindow(hwConsoleWindow, SW_SHOW);
	}
	return TRUE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	ConsoleCreate();

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
