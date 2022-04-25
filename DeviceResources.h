#pragma once
#include <wrl.h>
#include <d3d11.h>

class DeviceResources
{
public:
    HRESULT InitializeDeviceResources(HWND windowHandle);

    ID3D11Device* GetDevice() const { return m_pd3dDevice.Get(); }
    ID3D11DeviceContext* GetDeviceContext() const { return m_pd3dDeviceContext.Get(); }
    IDXGISwapChain* GetSwapChain() const { return m_pDXGISwapChain.Get(); }
    ID3D11RenderTargetView* GetRenderTargetView() const { return m_pRenderTarget.Get(); }
    ID3D11DepthStencilView* GetDepthStencilView() const { return m_pDepthStencilView.Get(); }
    void SetViewport() const;

    void Present() { GetSwapChain()->Present(1, 0); }

    void GetBackBufferSize(float* width, float* height) const;

private:
    HRESULT InitDepthBuffer();


private:
    Microsoft::WRL::ComPtr<ID3D11Device>        m_pd3dDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pd3dDeviceContext; // immediate context
    Microsoft::WRL::ComPtr<IDXGISwapChain>      m_pDXGISwapChain;

    // Swap chain resources
    Microsoft::WRL::ComPtr<ID3D11Texture2D>        m_pBackBuffer;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTarget;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_pDepthStencilState;

    // Resource metadata
    // D3D_FEATURE_LEVEL       m_featureLevel;
    D3D11_TEXTURE2D_DESC    m_backBufferDesc;
    D3D11_DEPTH_STENCIL_VIEW_DESC m_depthStencilViewDesc;
    D3D11_VIEWPORT          m_viewport;
};