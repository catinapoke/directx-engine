#pragma once
#include <d3d.h>
#include <memory>
#include <string>
#include <windows.h>
#include <winuser.h>

#include "DeviceResources.h"
#include "FrameCounter.h"
#include "Renderer.h"

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
    float GetAspectRatio() const { return size.x / size.y; }

    RECT GetWindowCorners() const
    {
        RECT rct = { 0,0,0,0 };
        // GetWindowRect(windowHandle, &rct);

        GetClientRect(windowHandle, (LPRECT)&rct);
        ClientToScreen(windowHandle, (LPPOINT)&rct.left);
        ClientToScreen(windowHandle, (LPPOINT)&rct.right);

        return rct;
    }

    POINT GetWindowCenter() const
    {
        const RECT rct = GetWindowCorners();
        return { rct.left + (rct.right - rct.left) / 2, rct.top + (rct.bottom - rct.top) / 2 };
    }

    static WindowApplication* GetInstance()
    {
        if (instance == nullptr)
            instance = new WindowApplication();
        return instance;
    }

    static POINT GetCursorPosition()
    {
        POINT point;
        if(GetCursorPos(&point))
        {
            return point;
        }
        return { 0, 0 };
    }

    static void SetCursorPosition(POINT position)
    {
        SetCursorPos(position.x, position.y);
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