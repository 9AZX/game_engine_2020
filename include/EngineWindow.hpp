#pragma once

#ifndef Engine_HPP_
#define Engine_HPP_

#define NOMINMAX
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdint.h>

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
    EngineWindow() {}

    ~EngineWindow()
    {
    }

    void initWindow()
    {
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = GetModuleHandleW(NULL);
        wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = _T("DesktopApp");
        wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

        if (!RegisterClassEx(&wcex))
        {
            MessageBox(NULL,
                       _T("Call to RegisterClassEx failed!"),
                       _T("Windows Desktop Guided Tour"),
                       NULL);

            return;
        }
        _hWnd = CreateWindow(
            _T("DesktopApp"),
            _T("Windows Desktop Guided Tour Application"),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            WIDTH, HEIGHT,
            NULL,
            NULL,
            GetModuleHandleW(NULL),
            NULL);

        if (!_hWnd)
        {
            MessageBox(NULL,
                       _T("Call to CreateWindow failed!"),
                       _T("Windows Desktop Guided Tour"),
                       NULL);

            return;
        }
        ShowWindow(_hWnd,
            SW_SHOWDEFAULT);
        UpdateWindow(_hWnd);
    }

    void run()
    {
        MSG msg;
        while (isWindowsClosed == false)
        {
            while (PeekMessage(&msg, _hWnd, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                if (msg.message == WM_QUIT)
                    break;
            }
            if (isWindowsClosed == false)
            {
                //drawFrame();
            }
        }
        //vkDeviceWaitIdle(device);
    }

    constexpr HWND getHwnd()
    {
        return _hWnd;
    }

private:
    WNDCLASSEX wcex;
    HWND _hWnd;
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
};
#endif /* Engine_HPP_ */
