#pragma once
#include "GeometryBuffer.h"
#include "RenderTexture.h"
#include "DeviceResources.h"

GeometryBuffer::GeometryBuffer(const std::shared_ptr<DeviceResources> resources) : resources_(resources)
{
    render_targets = new ID3D11RenderTargetView*[3];

    ID3D11Device* device = resources->GetDevice();
    int width, height;
    resources->GetBackBufferSize(&width, &height);

    position = new RenderTexture(device, width, height, DXGI_FORMAT_R32G32B32A32_FLOAT);
    normals = new RenderTexture(device, width, height, DXGI_FORMAT_R32G32B32A32_FLOAT); // DXGI_FORMAT_R32G32B32_FLOAT is unsupported https://docs.microsoft.com/en-us/previous-versions//ff471325(v=vs.85)?redirectedfrom=MSDN
    color = new RenderTexture(device, width, height, DXGI_FORMAT_R32G32B32A32_FLOAT);
}

void GeometryBuffer::PrepareDeferredRender()
{
	ID3D11DeviceContext* context = resources_->GetDeviceContext();
    ID3D11DepthStencilView* depth_stencil_view = resources_->GetDepthStencilView();

	const float back_color[4] = { 0,0,0,0 };

	RenderTexture* textures[3] = { position, normals, color };
	for(int i = 0; i< std::size(textures);i++)
	{
		render_targets[i] = textures[i]->GetRenderTargetView();
	}

	//Bind render target view array and depth stencil buffer to output render pipeline
	context->OMSetRenderTargets(std::size(textures), render_targets, depth_stencil_view);

	//Clear the render target buffers
	for (int i = 0; i < std::size(textures); i++)
	{
		context->ClearRenderTargetView(render_targets[i], back_color);
	}

	//Clear the depth buffer
	context->ClearDepthStencilView(depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0);	
}

void GeometryBuffer::SetTextures() const
{
	ID3D11DeviceContext* context = resources_->GetDeviceContext();
	RenderTexture* textures[] = { position, normals, color };
	for (int i = 0; i < std::size(textures); i++)
	{
		textures[i]->SetShaderResourceView(context, i);
	}
}
