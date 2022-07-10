#include "MeshMaterial.h"

void MeshMaterial::PrepareRender()
{
    Basic3DMaterial::PrepareRender();
    sampler->SetSampler();
}
