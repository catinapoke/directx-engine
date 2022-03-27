#include "MeshMaterial.h"
#include "InputLayoutSchemes.h"

HRESULT MeshMaterial::CreateInputLayout(ID3DBlob* compiledVertexBlob)
{
    return device_resources->GetDevice()->CreateInputLayout(
        InputLayoutScheme::PositionTexture,
        2,
        compiledVertexBlob->GetBufferPointer(),
        compiledVertexBlob->GetBufferSize(),
        &input_layout);
}

void MeshMaterial::PrepareRender()
{   
    Basic3DMaterial::PrepareRender();
    sampler->SetSampler();
}
