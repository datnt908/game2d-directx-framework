#pragma once

#ifndef SYS_CONST_GROUP
#define GAME_TITLE L"YOUR GAME TITLE"
#define IS_FULLSCREEN false
#define SCREEN_W 256
#define SCREEN_H 144
#define MAX_FPS 60
#endif // !SYS_CONST_GROUP

#include <d3d9.h>
#include <DxHelper.h>

LRESULT WINAPI processMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
bool isNoQuitMessageInQueue();
bool showWindow(HWND hWnd, int nCmdShow);