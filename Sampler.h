#pragma once
#include <d3d11.h>
#include <wrl.h>

class Sampler {
public:
	Sampler(ID3D11Device* device, ID3D11DeviceContext* context,
		D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_COMPARISON_FUNC func = D3D11_COMPARISON_ALWAYS,
		unsigned int max_anisotropy = 0);

	HRESULT Init(ID3D11Device* device);
	void SetSampler(int slot = 0);

private:
	D3D11_FILTER filter_;
	D3D11_COMPARISON_FUNC comp_func_;
	unsigned int max_anisotropy_;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler_state_;
	ID3D11DeviceContext* context;
};