#pragma once
#include "WindowApplication.h"
#include "InputDevice\InputDevice.h"
#include "PaddleRenderComponent.h"
#include "BallRenderComponent.h"
#include "Game.h"
#include "CameraTestLab.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
WindowApplication* WindowApplication::instance = nullptr;

HRESULT WindowApplication::CreateDesktopWindow()
{
    if (instanceHandle == NULL)
        instanceHandle = GetModuleHandle(nullptr);

    WNDCLASSEX wc;

    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = instanceHandle;
    wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    wc.hIconSm = wc.hIcon;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = windowClassName;
    wc.cbSize = sizeof(WNDCLASSEX);

    // Register the window class.
    RegisterClassEx(&wc);

    // Create window
    RECT windowRect = { 0, 0, static_cast<LONG>(size.x), static_cast<LONG>(size.y) };
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

    auto dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX; // Disable resize window -> | WS_THICKFRAME

    auto posX = (GetSystemMetrics(SM_CXSCREEN) - size.x) / 2;
    auto posY = (GetSystemMetrics(SM_CYSCREEN) - size.y) / 2;

    windowHandle = CreateWindowEx(WS_EX_APPWINDOW, windowClassName, windowClassName,
        dwStyle,
        posX, posY,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr, nullptr, instanceHandle, nullptr);

    ShowWindow(windowHandle, SW_SHOW);
    SetForegroundWindow(windowHandle);
    SetFocus(windowHandle);

    ShowCursor(true);

    if (windowHandle == NULL)
    {
        DWORD dwError = GetLastError();
        return HRESULT_FROM_WIN32(dwError);
    }

    instance = this;
    inputDevice = std::shared_ptr<InputDevice>(new InputDevice(this));

    return S_OK;
}

void WindowApplication::InitScene(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<Renderer> renderer)
{
    ID3D11Device* device = deviceResources->GetDevice();

    game = new CameraTestLab(deviceResources, inputDevice);
    game->Awake();
    game->Start();

    renderer->PassSceneActors(game->GetSceneActors());
}

void WindowApplication::DisplayFPS(float fps)
{
    WCHAR text[256];
    swprintf_s(text, TEXT("FPS: %.1f"), fps);
    SetWindowText(windowHandle, text);
}

void WindowApplication::HandleInput(MSG* message)
{
    while (PeekMessage(message, windowHandle, 0, 0, PM_REMOVE))
    {
        TranslateMessage(message);
        DispatchMessageW(message);
    }
}

HRESULT WindowApplication::Run(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<Renderer> renderer)
{
    if (!IsWindowVisible(windowHandle))
        ShowWindow(windowHandle, SW_SHOW);

    InitScene(deviceResources, renderer);

    MSG message;
    float delta;
    message.message = NULL;
    PeekMessage(&message, windowHandle, 0, 0, PM_REMOVE);
    FrameCounter frameCounter;
    frameCounter.Init();

    while (message.message != WM_QUIT)
    {
        frameCounter.CountFrame();
        DisplayFPS(frameCounter.GetFPS());
        delta = frameCounter.GetDeltaTime();

        HandleInput(&message);
        game->Update(delta);
        renderer->Render();
        deviceResources->Present();
    }

    return S_OK;
}

LRESULT CALLBACK WindowApplication::ProcessWindowMessages(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    switch (uMsg)
    {
    case WM_KEYDOWN:
    {
        auto key = static_cast<unsigned int>(wParam);
        inputDevice->AddPressedKey(static_cast<Keys>(key));
        break;
    }
    case WM_KEYUP:
    {
        auto key = static_cast<unsigned int>(wParam);
        inputDevice->RemovePressedKey(static_cast<Keys>(key));
        break;
    }
    case WM_CLOSE:
    {
        HMENU hMenu;
        hMenu = GetMenu(hWnd);
        if (hMenu != NULL)
        {
            DestroyMenu(hMenu);
        }
        DestroyWindow(hWnd);
        UnregisterClass(windowClassName, instanceHandle);
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return WindowApplication::GetInstance()->ProcessWindowMessages(hWnd, uMsg, wParam, lParam);
}