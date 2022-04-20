#pragma once
#include "MeshRenderData.h"

struct PhongMaterial
{
    float ambient;
    float shininess;
    float specular;
    float empty_space;
};

class PhongRenderData : public MeshRenderData
{
public:
    PhongRenderData(ID3D11Device* device, Material* material, Mesh* mesh, Texture* texture, PhongMaterial data) :
        MeshRenderData(device, material, mesh, texture), material_data(data){}

    PhongMaterial GetMaterialData() const { return material_data; }

private:
    PhongMaterial material_data;
};