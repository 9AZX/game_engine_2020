#include "Core.hpp"

#if defined(WIN32)
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    Core core;

    core.init(hInstance, hPrevInstance, pCmdLine, nCmdShow);
}

#else
int main(void)
{
    Core core;

    core.init();
}
#endif
