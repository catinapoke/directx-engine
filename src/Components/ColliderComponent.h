#pragma once
#include <d3d.h>
#include "SceneComponent.h"

typedef DirectX::SimpleMath::Vector4 Vector4;
typedef DirectX::SimpleMath::Vector2 Vector2;

class ColliderComponent
{
public:
    ColliderComponent() :transformComponent(nullptr) {}
    ColliderComponent(SceneComponent* owner, Vector2 size);
    bool IsOverlapingCollider(ColliderComponent& other);
    Vector2 GetSize() { return size; }

    float GetUpperBorder();
    float GetLowerBorder();
    float GetRightBorder();
    float GetLeftBorder();
    
private:
    Vector2 GetPosition();

private:
    Vector2 size;
    SceneComponent* transformComponent;
};