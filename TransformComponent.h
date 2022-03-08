#pragma once
#include "ComponentBase.h"
#include "InputDevice\SimpleMath.h"

typedef DirectX::SimpleMath::Vector4 Vector4;

class TransformComponent : ComponentBase
{
public:
    TransformComponent(Vector4 start_position = Vector4(0, 0, 0, 0), TransformComponent* parentNode = nullptr)
    {
        position = start_position;
        parent = parentNode;
    }

    Vector4 position;
    TransformComponent* parent;
};