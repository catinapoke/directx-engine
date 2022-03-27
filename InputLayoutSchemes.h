#pragma once
#include <d3d11.h>

class InputLayoutScheme
{
public:
    static const D3D11_INPUT_ELEMENT_DESC Position[];
    static const D3D11_INPUT_ELEMENT_DESC PositionColor[];
    static const D3D11_INPUT_ELEMENT_DESC PositionTexture[];
    static const D3D11_INPUT_ELEMENT_DESC PositionTextureNormal[];
};