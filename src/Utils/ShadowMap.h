#pragma once
#include <cassert>
#include <iostream>
#include <wrl.h>

#include "../Core/DeviceResources.h"

class ShadowMap {
public:
    ShadowMap(int width = 0, int height = 0) :
        texture_(nullptr),
        shadow_map_view_(nullptr),
        depth_buffer_(nullptr),
        viewport_(), width_(width), height_(height)
    {}

    ShadowMap(ID3D11Device* device, int width, int height) :
        ShadowMap(width, height)
    {
        if (Init(device) != S_OK)
            std::cout << "Got shadow map initialization error!" << std::endl;
    }

    void SetRenderTarget(ID3D11DeviceContext* context, int slot = 0) {
        assert(shadow_map_view_ != nullptr && "Depth stencil view isn't initialized.");

        ID3D11RenderTargetView* render_target = nullptr;
        context->RSSetViewports(1, &viewport_);
        context->OMSetRenderTargets(1, &render_target, depth_buffer_.Get());
        context->ClearDepthStencilView(depth_buffer_.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
    }

    void SetTexture(ID3D11DeviceContext* context, int slot = 0) {
        assert(shadow_map_view_ != nullptr && "Shadow map view isn't initialized.");
        context->PSSetShaderResources(slot, 1, shadow_map_view_.GetAddressOf());
    }

    void SetSampler(ID3D11DeviceContext* context) const
    {
        assert(sampler_state_ != nullptr && "Sampler isn't initialized.");
        context->PSSetSamplers(0, 1, sampler_state_.GetAddressOf());
    }

private:
    HRESULT Init(ID3D11Device* device) {
        viewport_ = CreateViewport(width_, height_);

        HRESULT result = CreateDepthMap(device, texture_.GetAddressOf());
        if (FAILED(result))
            return result;

        result = CreateDepthStencilView(device, texture_.Get());
        if (FAILED(result))
            return result;

        result = CreateShadowMapView(device, texture_.Get());
        if (FAILED(result))
            return result;

        result = CreateSamplerState(device);
        if (FAILED(result))
            return result;

        return result;
    }

    static D3D11_VIEWPORT CreateViewport(UINT width, UINT height)
    {
        D3D11_VIEWPORT viewport;

        viewport.TopLeftX = 0.0f;
        viewport.TopLeftY = 0.0f;
        viewport.Width = static_cast<float>(width);
        viewport.Height = static_cast<float>(height);
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;

        return viewport;
    }

    HRESULT CreateDepthMap(ID3D11Device* device, ID3D11Texture2D** depth_map) const {
        D3D11_TEXTURE2D_DESC depth_map_desc = {};
        depth_map_desc.Width = width_;
        depth_map_desc.Height = height_;
        depth_map_desc.MipLevels = 1;
        depth_map_desc.ArraySize = 1;
        depth_map_desc.Format = DXGI_FORMAT_R24G8_TYPELESS;
        depth_map_desc.SampleDesc.Count = 1;
        depth_map_desc.SampleDesc.Quality = 0;
        depth_map_desc.Usage = D3D11_USAGE_DEFAULT;
        depth_map_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
        depth_map_desc.CPUAccessFlags = 0;
        depth_map_desc.MiscFlags = 0;

        return device->CreateTexture2D(&depth_map_desc, nullptr, depth_map);
    }

    HRESULT CreateDepthStencilView(ID3D11Device* device, ID3D11Texture2D* depth_map) {
        D3D11_DEPTH_STENCIL_VIEW_DESC depth_buffer_desc = {};
        depth_buffer_desc.Flags = 0;
        depth_buffer_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depth_buffer_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        depth_buffer_desc.Texture2D.MipSlice = 0;

        return device->CreateDepthStencilView(
            depth_map, &depth_buffer_desc, depth_buffer_.GetAddressOf());
    }

    HRESULT CreateShadowMapView(ID3D11Device* device, ID3D11Texture2D* depth_map) {
        D3D11_SHADER_RESOURCE_VIEW_DESC shadow_map_desc = {};
        shadow_map_desc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
        shadow_map_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        shadow_map_desc.Texture2D.MipLevels = 1;
        shadow_map_desc.Texture2D.MostDetailedMip = 0;

        return device->CreateShaderResourceView(
            depth_map, &shadow_map_desc, shadow_map_view_.GetAddressOf());
    }

    HRESULT CreateSamplerState(ID3D11Device* device)
    {
        D3D11_SAMPLER_DESC sampler_desc = {};
        sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        sampler_desc.BorderColor[0] = 0.0f;
        sampler_desc.BorderColor[1] = 0.0f;
        sampler_desc.BorderColor[2] = 0.0f;
        sampler_desc.BorderColor[3] = 1.0f;
        sampler_desc.MaxLOD = INT_MAX;
        sampler_desc.MaxAnisotropy = 0; // 0

        return device->CreateSamplerState(&sampler_desc, &sampler_state_);
    }

private:
    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture_;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shadow_map_view_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_buffer_;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler_state_;

    D3D11_VIEWPORT viewport_;
    UINT width_ = 0;
    UINT height_ = 0;
};
