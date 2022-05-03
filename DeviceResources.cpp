#include "DeviceResources.h"

#include <DirectXMath.h>
#include <iostream>

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
    result = CreateRasterizerStates();

    return result;
}

void DeviceResources::SetViewport() const
{
    m_pd3dDeviceContext->RSSetViewports(1, &m_viewport);
}

void DeviceResources::GetBackBufferSize(float* width, float* height) const
{
    *height = static_cast<float>(m_backBufferDesc.Height);
    *width = static_cast<float>(m_backBufferDesc.Width);
}

void DeviceResources::GetBackBufferSize(int* width, int* height) const
{
    *height = static_cast<int>(m_backBufferDesc.Height);
    *width = static_cast<int>(m_backBufferDesc.Width);
}

void DeviceResources::SetCullBackSolidState() const
{
    m_pd3dDeviceContext->RSSetState(m_pCullBackSolidState.Get());
}

void DeviceResources::SetCullNoneSolidState() const
{
    m_pd3dDeviceContext->RSSetState(m_pCullNoneSolidState.Get());
}

void DeviceResources::SetBlendOneOneState() const
{
    constexpr float blend[4] = { 1, 1, 1, 1 };
    m_pd3dDeviceContext->OMSetBlendState(m_pBlendOneOneState.Get(), blend, 0xFFFFFFFF);
}

void DeviceResources::SetBlendNoneState() const
{
    constexpr float blend[4] = { 0, 0, 0, 0 };
    m_pd3dDeviceContext->OMSetBlendState(m_pBlendNoneState.Get(), blend, 0xFFFFFFFF);
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

    if (FAILED(hr))
    {
        std::cout << "Failed to create depth stencil" << std::endl;
        return hr;
    }

    D3D11_DEPTH_STENCIL_DESC dsDesc;

    // Depth test parameters
    dsDesc.DepthEnable = true;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL; //D3D11_COMPARISON_LESS

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
    m_pd3dDevice->CreateDepthStencilState(&dsDesc, m_pDepthStencilState.GetAddressOf());

    // Bind depth stencil state
    m_pd3dDeviceContext->OMSetDepthStencilState(m_pDepthStencilState.Get(), 1);

    // Create the depth stencil view
    hr = m_pd3dDevice->CreateDepthStencilView(pDepthStencil, // Depth stencil texture
        nullptr, // Depth stencil desc
        &m_pDepthStencilView);  // [out] Depth stencil view

    return hr;
}

HRESULT DeviceResources::CreateRasterizerStates()
{
    CD3D11_RASTERIZER_DESC rasterizer_desc = {};
    rasterizer_desc.CullMode = D3D11_CULL_BACK;
    rasterizer_desc.FillMode = D3D11_FILL_SOLID;

    HRESULT result = m_pd3dDevice->CreateRasterizerState(&rasterizer_desc, m_pCullBackSolidState.GetAddressOf());
    if (FAILED(result))
    {
        std::cout << "Failed to CreateRasterizerState\n";
        return result;
    }

    rasterizer_desc.CullMode = D3D11_CULL_NONE;
    result = m_pd3dDevice->CreateRasterizerState(&rasterizer_desc, m_pCullNoneSolidState.GetAddressOf());
    if (FAILED(result))
    {
        std::cout << "Failed to CreateRasterizerState\n";
        return result;
    }

    m_pd3dDeviceContext->RSSetState(m_pCullBackSolidState.Get());

    return result;
}

HRESULT DeviceResources::CreateBlendStates()
{
    HRESULT result = S_OK;

    D3D11_BLEND_DESC blend_desc;
    ZeroMemory(&blend_desc, sizeof(blend_desc));
    blend_desc.AlphaToCoverageEnable = false;
    blend_desc.IndependentBlendEnable = false;
    blend_desc.RenderTarget[0].BlendEnable = true;
    blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
    blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
    blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
    blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    result = m_pd3dDevice->CreateBlendState(&blend_desc, m_pBlendOneOneState.GetAddressOf());

    if (FAILED(result))
    {
        std::cout << "Failed to CreateBlendState\n";
        return result;
    }

    ZeroMemory(&blend_desc, sizeof(D3D11_BLEND_DESC));
    blend_desc.RenderTarget[0].BlendEnable = FALSE;
    blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    result = m_pd3dDevice->CreateBlendState(&blend_desc, m_pBlendNoneState.GetAddressOf());

    if (FAILED(result))
        std::cout << "Failed to CreateBlendState\n";

    return result;
}
