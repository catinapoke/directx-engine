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

    static bool AreEqual(InputScheme a, InputScheme b)
    {
        if (a.size() != b.size())
            return false;

        for (int i = 0; i < a.size(); i++)
            if (!AreEqual(a[i],b[i])) return false;

        return true;
    }

    static bool AreEqual (const D3D11_INPUT_ELEMENT_DESC& lhs, const D3D11_INPUT_ELEMENT_DESC& rhs)
    {
        return lhs.Format == rhs.Format
            && lhs.InputSlot == rhs.InputSlot
            && lhs.SemanticIndex == rhs.SemanticIndex
            && lhs.SemanticName == rhs.SemanticName;
    }
};