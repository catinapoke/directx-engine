#include <assert.h>
#include "Sampler.h"

Sampler::Sampler(ID3D11Device* device, ID3D11DeviceContext* context,
	D3D11_FILTER filter, D3D11_COMPARISON_FUNC func, unsigned int max_anisotropy) :
	filter_(filter),
	comp_func_(func),
	max_anisotropy_(max_anisotropy), 
	sampler_state_(nullptr)
{
	Init(device);
	this->context = context;
}


HRESULT Sampler::Init(ID3D11Device* device) 
{
	D3D11_SAMPLER_DESC sampler_desc = {};
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.Filter = filter_; // D3D11_FILTER_MIN_MAG_MIP_LINEAR
	sampler_desc.ComparisonFunc = comp_func_;
	sampler_desc.BorderColor[0] = 1.0f;
	sampler_desc.BorderColor[1] = 0.0f;
	sampler_desc.BorderColor[2] = 0.0f;
	sampler_desc.BorderColor[3] = 1.0f;
	sampler_desc.MaxLOD = INT_MAX;
	sampler_desc.MaxAnisotropy = max_anisotropy_; // 0

	return device->CreateSamplerState(&sampler_desc, &sampler_state_);
}

void Sampler::SetSampler(int slot) 
{
	assert(context != nullptr && "Sampler isn't initialized.");
	context->PSSetSamplers(slot, 1, sampler_state_.GetAddressOf());
}