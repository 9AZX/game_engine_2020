#pragma once

#ifndef Engine_HPP_
#define Engine_HPP_

#define NOMINMAX
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdint.h>
#include <string>

bool isWindowsClosed = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_GETMINMAXINFO:
    {
        MINMAXINFO *mmi = (MINMAXINFO *)lParam;
        mmi->ptMinTrackSize.x = 800;
        mmi->ptMinTrackSize.y = 600;
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        isWindowsClosed = true;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}

class EngineWindow
{
public:
    EngineWindow(std::string windowName, int width, int height);

    ~EngineWindow()
    {
    }

    void initWindow();

    void run();

    constexpr HWND getHwnd()
    {
        return _hWnd;
    }

private:
    WNDCLASSEX _wcex;
    HWND _hWnd;
    std::string _windowName;
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
};
#endif /* Engine_HPP_ */
