#pragma once
#include "CommonRenderData.h"
#include "Texture.h"
#include "Mesh.h"

class MeshRenderData : public CommonRenderData
{
public:
	MeshRenderData(ID3D11Device* device, Material* material, Mesh* mesh, Texture* texture) :
		CommonRenderData(material, sizeof(mesh->vertices[0])), texture(texture)
    {
		ConvertToBuffers(device, mesh);
    }

	void SetBuffers(ID3D11DeviceContext* context) override
	{
		CommonRenderData::SetBuffers(context);
		texture->SetTexture(context);
	}

	Texture* GetTexture() const { return texture; }

private:
	void ConvertToBuffers(ID3D11Device* device, Mesh* mesh);

private:
	Texture* texture;
};


