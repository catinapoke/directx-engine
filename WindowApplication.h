#pragma once
#include <windows.h>
#include <winuser.h>
#include <string>
#include <memory>

#include "DeviceResources.h"
#include "Renderer.h"
#include "FrameCounter.h"

class InputDevice;
class PongGame;


class WindowApplication
{
public:
    WindowApplication() :windowHandle(NULL), instanceHandle(NULL), game(NULL) {};
    ~WindowApplication() { };

    HRESULT CreateDesktopWindow();
    HRESULT Run(
        std::shared_ptr<DeviceResources> deviceResources,
        std::shared_ptr<Renderer> renderer
    );

    HWND GetHandle() { return windowHandle; }

    static WindowApplication* GetInstance()
    {
        if (instance == nullptr)
            instance = new WindowApplication();
        return instance;
    }
    LRESULT CALLBACK ProcessWindowMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    void InitScene(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<Renderer> renderer);
    void DisplayFPS(float fps);
    void HandleInput(MSG* message);

private:
    static WindowApplication* instance;

    PongGame* game;
    InputDevice* inputDevice;
    const LPCWSTR windowClassName = L"DirectXGame";
    HINSTANCE instanceHandle;
    HWND windowHandle;
};