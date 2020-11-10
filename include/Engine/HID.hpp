#pragma once

#ifndef ENGINE_HID_HPP_
#define ENGINE_HID_HPP_

#include "Engine/ResourcesHID/resourceAcceleratorTable.h"
#include "Engine/Window.hpp"

#include <Windows.h>
#include <windowsx.h>
#include <Xinput.h>
#pragma comment(lib,"XInput.lib")
#include <map>
#include <iostream>

namespace Engine {

template <typename T>
struct vector2d
{
    T x;
    T y;
};

class HID
    {
    public:
        HID(WNDCLASSEX* wcex, const HWND& hWnd);;

        ~HID();

        //Keyboard and mouse event methods

        void initMapButtonController();
        int detectEvent(MSG* msg) noexcept;
        constexpr vector2d<int> mousePosition() noexcept;

        //Controller methods

        bool detectController();
        float joystickLeftMagnitude();
        float joystickRightMagnitude();
        vector2d<float> joystickLeftPosition() noexcept;
        vector2d<float> joystickRightPosition() noexcept;
        constexpr float leftTrigger() noexcept;
        constexpr float rightTrigger() noexcept;

        enum BUTTON_ID {
            DPAD_UP = 1,
            DPAD_DOWN,
            DPAD_LEFT,
            DPAD_RIGHT,
            START,
            BACK,
            LEFT_THUMB,
            RIGHT_THUMB,
            LEFT_SHOULDER,
            RIGHT_SHOULDER,
            A,
            B,
            X,
            Y
        };
        constexpr float HID::getScrollMagnitude() noexcept;
        BUTTON_ID buttonControllerID() noexcept;

    private:
        static LRESULT CALLBACK CallBackInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    private:
        static int lastEvent;
        static int mouseX;
        static int mouseY;
        static float scrollPos;
        std::map<int, BUTTON_ID> _mapControllerButton;
        XINPUT_STATE state;
        HACCEL _hAccel;
        WNDCLASSEX* _wcex;
        HWND _hWnd;
        WNDPROC _callBackInputEvent;
    };

} /* namespace Engine */

#endif /* ENGINE_HID_HPP */
