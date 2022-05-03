#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <iostream>

class RenderTexture
{
public:
    RenderTexture(ID3D11Device* device, int width, int height, DXGI_FORMAT format = DXGI_FORMAT_R32G32B32A32_FLOAT)
    {
        HRESULT result = CreateTexture(device, width, height, format);
        if(FAILED(result))
        {
            PrintErrorMessage();
            return;
        }

        result = CreateRenderTargetView(device, format);
        if (FAILED(result))
        {
            PrintErrorMessage();
            return;
        }

        result = CreateShaderResourceView(device, format);
        if (FAILED(result))
        {
            PrintErrorMessage();
            return;
        }
    }

	void SetShaderResourceView(ID3D11DeviceContext* context, int slot = 0)
	{
		context->PSSetShaderResources(slot, 1, shader_resource_view_.GetAddressOf());
	}

    ID3D11RenderTargetView* GetRenderTargetView() const
    {
        return render_target_view_.Get();
    }

protected:
    HRESULT CreateTexture(ID3D11Device* device, int textureWidth, int textureHeight, DXGI_FORMAT format = DXGI_FORMAT_R32G32B32A32_FLOAT)
    {
        D3D11_TEXTURE2D_DESC texture_desc = {};
        texture_desc.Width = textureWidth;
        texture_desc.Height = textureHeight;
        texture_desc.MipLevels = 1;
        texture_desc.ArraySize = 1;
        texture_desc.Format = format;
        texture_desc.SampleDesc.Count = 1;
        texture_desc.SampleDesc.Quality = 0;
        texture_desc.Usage = D3D11_USAGE_DEFAULT;
        texture_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        texture_desc.CPUAccessFlags = 0;
        texture_desc.MiscFlags = 0;

        return device->CreateTexture2D(&texture_desc, nullptr, texture_.GetAddressOf());
    }

    HRESULT CreateRenderTargetView(ID3D11Device* device, DXGI_FORMAT format = DXGI_FORMAT_R32G32B32A32_FLOAT)
    {
        D3D11_RENDER_TARGET_VIEW_DESC render_target_view_desc;
        ZeroMemory(&render_target_view_desc, sizeof(render_target_view_desc));
        render_target_view_desc.Format = format;
        render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        render_target_view_desc.Texture2D.MipSlice = 0;
        
        return device->CreateRenderTargetView(texture_.Get(), &render_target_view_desc, render_target_view_.GetAddressOf());
    }

    HRESULT CreateShaderResourceView(ID3D11Device* device, DXGI_FORMAT format = DXGI_FORMAT_R32G32B32A32_FLOAT)
    {
        D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
        ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));
        shaderResourceViewDesc.Format = format;
        shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
        shaderResourceViewDesc.Texture2D.MipLevels = 1;

        return device->CreateShaderResourceView(texture_.Get(), &shaderResourceViewDesc, shader_resource_view_.GetAddressOf());
    }

    static void PrintErrorMessage()
    {
        std::cout << "Failed to initialize render texture" << std::endl;
    }

protected:
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture_;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view_;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resource_view_;
};
