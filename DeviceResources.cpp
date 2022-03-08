#include "DeviceResources.h"

HRESULT DeviceResources::InitializeDeviceResources(HWND windowHandle)
{
    D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };

    DXGI_SWAP_CHAIN_DESC swapDesc = {};
    swapDesc.BufferCount = 2;
    swapDesc.BufferDesc.Width = 640;
    swapDesc.BufferDesc.Height = 320;
    swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapDesc.OutputWindow = windowHandle;
    swapDesc.Windowed = true;
    swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    swapDesc.SampleDesc.Count = 1;
    swapDesc.SampleDesc.Quality = 0;

    HRESULT result = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        D3D11_CREATE_DEVICE_DEBUG,
        featureLevel,
        1,
        D3D11_SDK_VERSION,
        &swapDesc,
        &m_pDXGISwapChain,
        &m_pd3dDevice,
        nullptr,
        &m_pd3dDeviceContext);

    // Configure the back buffer and viewport.
    result = m_pDXGISwapChain->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D),
        (void**)&m_pBackBuffer);

    m_pBackBuffer->GetDesc(&m_backBufferDesc);

    ZeroMemory(&m_viewport, sizeof(D3D11_VIEWPORT));
    m_viewport.Height = (float)m_backBufferDesc.Height;
    m_viewport.Width = (float)m_backBufferDesc.Width;
    m_viewport.MinDepth = 0;
    m_viewport.MaxDepth = 1;


    m_pd3dDeviceContext->RSSetViewports(
        1,
        &m_viewport
    );

    result = m_pd3dDevice->CreateRenderTargetView(
        m_pBackBuffer.Get(),
        nullptr,
        m_pRenderTarget.GetAddressOf()
    );

    return result;
}

void DeviceResources::GetBackBufferSize(float* width, float* height)
{
    *height = (float)m_backBufferDesc.Height;
    *width = (float)m_backBufferDesc.Width;
}
