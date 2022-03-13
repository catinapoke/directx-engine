#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>

class Material;

class RenderData
{
public:
    RenderData(Material* material);
    virtual ID3D11Buffer* GetVertexBuffer() = 0;
    virtual ID3D11Buffer** GetVertexBufferAdress() = 0;
    virtual ID3D11Buffer* GetIndexBuffer() = 0;
    virtual int GetIndicesCount() = 0;
    Material* GetMaterial();

protected:
    Material* material;
    static HRESULT CreateVertexBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer, ID3D11Device* device, DirectX::XMFLOAT4* points, int arraySize);
    static HRESULT CreateIndexBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer, ID3D11Device* device, int* indices, int arraySize);
};