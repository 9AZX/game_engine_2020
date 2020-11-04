#include "Engine/HID.hpp"

int Engine::HID::mouseX = 0;
int Engine::HID::mouseY = 0;
int Engine::HID::lastEvent = -1;
float Engine::HID::scrollPos = 0.0;

Engine::HID::HID(WNDCLASSEX* wcex, const HWND& hWnd) : _wcex(wcex), _hWnd(hWnd)
{
    _hAccel = LoadAccelerators(_wcex->hInstance, MAKEINTRESOURCE(IDR_ACCEL1));
    _callBackInputEvent = (WNDPROC)SetWindowLongPtr(_hWnd, GWLP_WNDPROC, (LONG_PTR)HID::CallBackInput);
    initMapButtonController();
}

Engine::HID::~HID()
{
}

void Engine::HID::initMapButtonController()
{
    _mapControllerButton[XINPUT_GAMEPAD_DPAD_UP] = DPAD_UP;
    _mapControllerButton[XINPUT_GAMEPAD_DPAD_DOWN] = DPAD_DOWN;
    _mapControllerButton[XINPUT_GAMEPAD_DPAD_LEFT] = DPAD_LEFT;
    _mapControllerButton[XINPUT_GAMEPAD_DPAD_RIGHT] = DPAD_RIGHT;
    _mapControllerButton[XINPUT_GAMEPAD_START] = START;
    _mapControllerButton[XINPUT_GAMEPAD_BACK] = BACK;
    _mapControllerButton[XINPUT_GAMEPAD_LEFT_THUMB] = LEFT_THUMB;
    _mapControllerButton[XINPUT_GAMEPAD_RIGHT_THUMB] = RIGHT_THUMB;
    _mapControllerButton[XINPUT_GAMEPAD_LEFT_SHOULDER] = LEFT_SHOULDER;
    _mapControllerButton[XINPUT_GAMEPAD_RIGHT_SHOULDER] = RIGHT_SHOULDER;
    _mapControllerButton[XINPUT_GAMEPAD_A] = A;
    _mapControllerButton[XINPUT_GAMEPAD_B] = B;
    _mapControllerButton[XINPUT_GAMEPAD_X] = X;
    _mapControllerButton[XINPUT_GAMEPAD_Y] = Y;
}

int Engine::HID::detectEvent(MSG* msg) noexcept
{
    if (!TranslateAccelerator(_hWnd, _hAccel, msg))
    {
        TranslateMessage(msg);
        DispatchMessage(msg);
    }
    return lastEvent;
}

constexpr Engine::vector2d<int> Engine::HID::mousePosition() noexcept
{
    return vector2d<int> { mouseX, mouseY };
}

bool Engine::HID::detectController()
{
    DWORD dwResult;
    DWORD i = 0;
    ZeroMemory(&state, sizeof(XINPUT_STATE));

    dwResult = XInputGetState(i, &state);
    if (dwResult == ERROR_SUCCESS)
    {
        return true;
    }
    return false;
}

float Engine::HID::joystickLeftMagnitude()
{
    float LX = state.Gamepad.sThumbLX;
    float LY = state.Gamepad.sThumbLY;
    float magnitude = sqrt(LX * LX + LY * LY);
    static const int L_DEADZONE = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
    float normalizedMagnitude = 0;

    if (magnitude > L_DEADZONE)
    {
        if (magnitude > 32767)
            magnitude = 32767;
        magnitude -= L_DEADZONE;
        normalizedMagnitude = magnitude / (32767 - L_DEADZONE);
    }
    else
    {
        magnitude = 0.0;
        normalizedMagnitude = 0.0;
    }
    return normalizedMagnitude;
}

float Engine::HID::joystickRightMagnitude()
{
    float LX = state.Gamepad.sThumbRX;
    float LY = state.Gamepad.sThumbRY;
    float magnitude = sqrt(LX * LX + LY * LY);
    static const int R_DEADZONE = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
    float normalizedMagnitude = 0;

    if (magnitude > R_DEADZONE)
    {
        if (magnitude > 32767)
            magnitude = 32767;
        magnitude -= R_DEADZONE;
        normalizedMagnitude = magnitude / (32767 - R_DEADZONE);
    }
    else
    {
        magnitude = 0.0;
        normalizedMagnitude = 0.0;
    }
    return normalizedMagnitude;
}

Engine::vector2d<float> Engine::HID::joystickLeftPosition() noexcept
{
    float LX = state.Gamepad.sThumbLX;
    float LY = state.Gamepad.sThumbLY;
    float magnitude = sqrt(LX * LX + LY * LY);
    float normalizedLX = LX / magnitude;
    float normalizedLY = LY / magnitude;

    return vector2d<float> { normalizedLX, normalizedLY };
}

Engine::vector2d<float> Engine::HID::joystickRightPosition() noexcept
{
    float RX = state.Gamepad.sThumbRX;
    float RY = state.Gamepad.sThumbRY;
    float magnitude = sqrt(RX * RX + RY * RY);
    float normalizedRX = RX / magnitude;
    float normalizedRY = RY / magnitude;

    return vector2d<float> { normalizedRX, normalizedRY };
}

constexpr float Engine::HID::leftTrigger() noexcept
{
    return state.Gamepad.bLeftTrigger / 255.0f;
}

constexpr float Engine::HID::rightTrigger() noexcept
{
    return state.Gamepad.bRightTrigger / 255.0f;
}

constexpr float Engine::HID::getScrollMagnitude() noexcept
{
    return scrollPos;
}

Engine::HID::BUTTON_ID Engine::HID::buttonControllerID() noexcept
{
    return _mapControllerButton[state.Gamepad.wButtons];
}

LRESULT CALLBACK Engine::HID::CallBackInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HID::lastEvent = -1;
    HID::mouseX = GET_X_LPARAM(lParam);
    HID::mouseY = GET_Y_LPARAM(lParam);
    scrollPos = GET_WHEEL_DELTA_WPARAM(wParam);

    switch (message)
    {
    case WM_COMMAND:
    {
        WORD id = LOWORD(wParam);
        HID::lastEvent = id;
        break;
    }
    case WM_LBUTTONUP:
        HID::lastEvent = ID_BUTTON_L;
        break;
    case WM_RBUTTONUP:
        HID::lastEvent = ID_BUTTON_R;
        break;
    case WM_GETMINMAXINFO:
    {
        MINMAXINFO* mmi = (MINMAXINFO*)lParam;
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
