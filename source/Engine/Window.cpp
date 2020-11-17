#include "Engine/Window.hpp"

bool Engine::Window::isWindowsClosed = false;

Engine::Window::Window(std::string windowName, int width, int height) : _windowName(windowName), WIDTH(width), HEIGHT(height)
{
}

void Engine::Window::run()
{
    MSG msg;
    /*while (isWindowsClosed == false)
    {*/
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
    //}
    //vkDeviceWaitIdle(device);
}

void Engine::Window::initWindow()
{
    _hInstance = GetModuleHandleW(NULL);

    _wcex.cbSize = sizeof(WNDCLASSEX);
    _wcex.style = CS_HREDRAW | CS_VREDRAW;
    _wcex.lpfnWndProc = Engine::Window::WndProc;
    _wcex.cbClsExtra = 0;
    _wcex.cbWndExtra = 0;
    _wcex.hInstance = _hInstance;
    _wcex.hIcon = LoadIcon(_hInstance, IDI_APPLICATION);
    _wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    _wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    _wcex.lpszMenuName = NULL;
    _wcex.lpszClassName = _T("DesktopApp");
    _wcex.hIconSm = LoadIcon(_wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&_wcex))
    {
        MessageBox(NULL,
                   _T("Call to RegisterClassEx failed!"),
                   _T("3D Game Engine"),
                   NULL);

        return;
    }
    _hWnd = CreateWindow(
        _T("DesktopApp"),
        _T("3D Game Engine Application"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WIDTH, HEIGHT,
        NULL,
        NULL,
        _hInstance,
        NULL);

    if (!_hWnd)
    {
        MessageBox(NULL,
                   _T("Call to CreateWindow failed!"),
                   _T("3D Game Engine"),
                   NULL);

        return;
    }
    SetWindowTextA(_hWnd, _windowName.c_str());
    ShowWindow(_hWnd,
               SW_SHOWDEFAULT);
    UpdateWindow(_hWnd);
}

LRESULT CALLBACK Engine::Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
        Engine::Window::isWindowsClosed = true;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}
