#pragma once

#include <d3d11.h>
#include <DirectXTex.h>
#include <wrl/client.h>

class Texture {
public:
	Texture():
		texture_(nullptr), 
		texture_view_(nullptr)
	{}

	HRESULT Init(ID3D11Device* device, const DirectX::ScratchImage& image) {

		HRESULT result = CreateTextureEx(
			device,
			image.GetImages(),
			image.GetImageCount(),
			image.GetMetadata(),
			D3D11_USAGE_DEFAULT,
			D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET,
			0, 0, false,
			reinterpret_cast<ID3D11Resource**>(texture_.GetAddressOf()));

		if (FAILED(result)) {
			return result;
		}

		return device->CreateShaderResourceView(texture_.Get(), nullptr, &texture_view_);
	}

	void SetTexture(ID3D11DeviceContext* context, int slot = 0) {
		assert(context != nullptr && "Texture isn't initialized.");
		context->PSSetShaderResources(slot, 1, texture_view_.GetAddressOf());
	}

private:
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture_;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture_view_;
};

