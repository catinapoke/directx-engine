#pragma once
#include <d3d11.h>
#include <wrl.h>

class Sampler {
public:
	Sampler(ID3D11Device* device, ID3D11DeviceContext* context,
		D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR, 
		unsigned int max_anisotropy = 0);

	HRESULT Init(ID3D11Device* device);
	void SetSampler();

private:
	D3D11_FILTER filter_;
	unsigned int max_anisotropy_;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler_state_;
	ID3D11DeviceContext* context;
};