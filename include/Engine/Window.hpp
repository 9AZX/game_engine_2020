#pragma once

#ifndef ENGINE_WINDOW_HPP_
#define ENGINE_WINDOW_HPP_

#define NOMINMAX
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdint.h>
#include <string>

namespace Engine
{

    class Window
    {
    public:
        Window(std::string windowName, int width, int height);

        ~Window() = default;

        void initWindow();

        void run();

        constexpr HWND getHwnd()
        {
            return _hWnd;
        }
        static bool isWindowsClosed;

        constexpr HINSTANCE getHinstance()
        {
            return _hInstance;
        }

    private:
        WNDCLASSEX _wcex;
        HINSTANCE _hInstance;
        HWND _hWnd;
        std::string _windowName;
        const uint32_t WIDTH = 800;
        const uint32_t HEIGHT = 600;

        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    };
} // namespace Engine
#endif /* ENGINE_WINDOW_HPP_ */
