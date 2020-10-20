#include "EngineWindow.hpp"

EngineWindow::EngineWindow(std::string windowName, int width, int height) : _windowName(windowName), WIDTH(width), HEIGHT(height)
{
}

void EngineWindow::run()
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

void EngineWindow::initWindow()
{
    _wcex.cbSize = sizeof(WNDCLASSEX);
    _wcex.style = CS_HREDRAW | CS_VREDRAW;
    _wcex.lpfnWndProc = WndProc;
    _wcex.cbClsExtra = 0;
    _wcex.cbWndExtra = 0;
    _wcex.hInstance = GetModuleHandleW(NULL);
    _wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    _wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    _wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    _wcex.lpszMenuName = NULL;
    _wcex.lpszClassName = _T("DesktopApp");
    _wcex.hIconSm = LoadIcon(_wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&_wcex))
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
