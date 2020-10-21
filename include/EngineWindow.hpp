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

class EngineWindow
{
public:
    EngineWindow(std::string windowName, int width, int height);

    ~EngineWindow() = default;

    void initWindow();

    void run();

    constexpr HWND getHwnd()
    {
        return _hWnd;
    }
    static bool isWindowsClosed;

private:
    WNDCLASSEX _wcex;
    HWND _hWnd;
    std::string _windowName;
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

#endif /* Engine_HPP_ */
