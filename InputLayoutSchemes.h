#pragma once
#include <vector>
#include <d3d11.h>

using InputScheme = std::vector<D3D11_INPUT_ELEMENT_DESC>;

class InputLayoutSchemes
{
public:
    static const InputScheme Position;
    static const InputScheme PositionColor;
    static const InputScheme PositionTexture;
    static const InputScheme PositionTextureNormal;
};