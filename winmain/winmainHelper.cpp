#include "winmainHelper.h"

LRESULT __stdcall processMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool isNoQuitMessageInQueue()
{
	MSG message;
	bool isDone = false;
	if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	{
		if (message.message == WM_QUIT)
			isDone = true;
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return isDone;
}

bool showWindow(HWND hWnd, int nCmdShow)
{
	if (!hWnd)
		return false;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return true;
}
