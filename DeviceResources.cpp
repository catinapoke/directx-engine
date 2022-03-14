#include "DeviceResources.h"

#include "WindowApplication.h"

HRESULT DeviceResources::InitializeDeviceResources(HWND windowHandle)
{
    D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };

    DirectX::XMFLOAT2 window_size = WindowApplication::GetInstance()->GetWindowSize();

    DXGI_SWAP_CHAIN_DESC swapDesc = {};
    swapDesc.BufferCount = 2;
    swapDesc.BufferDesc.Width = window_size.x;
    swapDesc.BufferDesc.Height = window_size.y;
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

    result = InitDepthBuffer();

    return result;
}

void DeviceResources::GetBackBufferSize(float* width, float* height)
{
    *height = (float)m_backBufferDesc.Height;
    *width = (float)m_backBufferDesc.Width;
}

HRESULT DeviceResources::InitDepthBuffer()
{
    HRESULT hr = S_OK;

    ID3D11Texture2D* pDepthStencil = NULL;
    D3D11_TEXTURE2D_DESC descDepth;
    descDepth.Width = m_backBufferDesc.Width;
    descDepth.Height = m_backBufferDesc.Height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT; //DXGI_FORMAT_D32_FLOAT DXGI_FORMAT_D32_FLOAT
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;
    hr = m_pd3dDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);

    D3D11_DEPTH_STENCIL_DESC dsDesc;

    // Depth test parameters
    dsDesc.DepthEnable = true;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

    // Stencil test parameters
    dsDesc.StencilEnable = true;
    dsDesc.StencilReadMask = 0xFF;
    dsDesc.StencilWriteMask = 0xFF;

    // Stencil operations if pixel is front-facing
    dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // Stencil operations if pixel is back-facing
    dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // Create depth stencil state
    ID3D11DepthStencilState* pDSState;
    m_pd3dDevice->CreateDepthStencilState(&dsDesc, &pDSState);

    // Bind depth stencil state
    m_pd3dDeviceContext->OMSetDepthStencilState(pDSState, 1);


    // Create the depth stencil view
    hr = m_pd3dDevice->CreateDepthStencilView(pDepthStencil, // Depth stencil texture
        nullptr, // Depth stencil desc
        &m_pDepthStencilView);  // [out] Depth stencil view

    return hr;
}
