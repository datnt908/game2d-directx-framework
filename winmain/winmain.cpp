#include "winmainHelper.h"
#include "DxGraphic.h"
#include "DxInput.h"
#include "DxSound.h"
#include "inputHandler.h"
#include "GameWorld.h"

ATOM registerMyWindowClass(HINSTANCE hInstance);
HWND createGameWindow(HINSTANCE hInstance, int nCmdShow);
void loopMainMessage();

DxGraphic* directGraphic;
DxInput* directInput;
DxSound* directSound;
WinKeyHandler* keyHandler;
WinMouseHandler* mouseHandler;
BaseGameWorld* gameWorld;

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	int codeErr = 0;
	HWND hWnd = createGameWindow(hInstance, nCmdShow);
	if (hWnd == FALSE) codeErr = 1;
	if (!showWindow(hWnd, nCmdShow))
		codeErr = 2;

	directGraphic = DxGraphic::getInstance();
	if (!directGraphic->initialize(hWnd, IS_FULLSCREEN))
		codeErr = 3;

	directInput = DxInput::getInstance();
	keyHandler = new WinKeyHandler();
	mouseHandler = new WinMouseHandler();
	if (!directInput->initializeKeyb(keyHandler))
		codeErr = 4;
	if (!directInput->initializeMouse(mouseHandler))
		codeErr = 5;

	directSound = DxSound::getInstance();
	if (!directSound->initialize())
		codeErr = 6;

	gameWorld = GameWorld::getInstance();
	if (gameWorld == NULL || !gameWorld->initialize())
		codeErr = 7;

	if(codeErr == 0)
		loopMainMessage();

	delete directGraphic;
	delete directInput;
	delete directSound;
	delete keyHandler;
	delete mouseHandler;
	delete gameWorld;
	return codeErr;
}


void loopMainMessage()
{
	bool isDone = false;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FPS;

	while (!isDone)
	{
		isDone = isNoQuitMessageInQueue();

		// deltaTime là khoảng thời gian giữa 2 lần khung hình cần được cập nhật
		// Có thể xem thêm các khái niệm và kiến thức liên quan về FPS (Frame Per Sec) để hiểu rõ hơn
		DWORD now = GetTickCount();
		DWORD deltaTime = now - frameStart;

		if (deltaTime >= tickPerFrame)
		{
			frameStart = now;
			directInput->processInput();
			gameWorld->update(deltaTime / 1000.f);
			gameWorld->render();
		}
		else
			Sleep(tickPerFrame - deltaTime);
	};
}

HWND createGameWindow(HINSTANCE hInstance, int nCmdShow)
{
	registerMyWindowClass(hInstance);

	DWORD ScreenMode;
	if (IS_FULLSCREEN != 0)
		ScreenMode = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		ScreenMode = WS_TILEDWINDOW;

	HWND hWnd = CreateWindow(
		GAME_TITLE, GAME_TITLE,
		ScreenMode,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_W, SCREEN_H,
		NULL, NULL, hInstance, NULL
	);

	if (!hWnd) return FALSE;
	return hWnd;
}

ATOM registerMyWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)processMessage;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = GAME_TITLE;
	wc.hIconSm = NULL;

	return RegisterClassEx(&wc);
}
