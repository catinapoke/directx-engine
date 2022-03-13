#pragma once
#include <windows.h>
#include <winuser.h>
#include <string>
#include <memory>
#include <d3d.h>

#include "DeviceResources.h"
#include "Renderer.h"
#include "FrameCounter.h"

class InputDevice;
class Game;


class WindowApplication
{
public:
    WindowApplication() :windowHandle(NULL), instanceHandle(NULL), game(NULL), size(640, 320) {};
    ~WindowApplication() { };

    HRESULT CreateDesktopWindow();
    HRESULT Run(
        std::shared_ptr<DeviceResources> deviceResources,
        std::shared_ptr<Renderer> renderer
    );

    HWND GetHandle() { return windowHandle; }

    DirectX::XMFLOAT2 GetWindowSize() { return size; }
    float GetAspectRatio() { return size.x / size.y; }

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

    Game* game;
    DirectX::XMFLOAT2 size;
    std::shared_ptr<InputDevice> inputDevice;
    const LPCWSTR windowClassName = L"DirectXGame";
    HINSTANCE instanceHandle;
    HWND windowHandle;
};