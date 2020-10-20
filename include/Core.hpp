#pragma once

#ifndef Core_HPP_
#define Core_HPP_

#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdint.h>

class Core
{
public:
    Core() = default;

    void init() const noexcept;

private:
    _In_ HINSTANCE _hInstance;
    HWND _hWnd;
    HINSTANCE _hPrevInstance;
    LPSTR _pCmdLine;
    int _nCmdShow;
}; /* class Core */

#endif /* Core_HPP_ */
