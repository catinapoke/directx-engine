#include "ColliderComponent.h"
#include "../InputDevice/SimpleMath.h"

ColliderComponent::ColliderComponent(SceneComponent* owner, Vector2 size)
{
    transformComponent = owner;
    this->size = size;
}

bool ColliderComponent::IsOverlapingCollider(ColliderComponent& other)
{
    Vector2 difference = other.GetPosition() - GetPosition();
    difference.x = abs(difference.x);
    difference.y = abs(difference.y);

    return difference.x < ((other.size.x + size.x) / 2) && difference.y < ((other.size.y + size.y) / 2);
}

float ColliderComponent::GetUpperBorder()
{
    return transformComponent->GetPosition().y + size.y / 2;
}

float ColliderComponent::GetLowerBorder()
{
    return transformComponent->GetPosition().y - size.y / 2;
}

float ColliderComponent::GetRightBorder()
{
    return transformComponent->GetPosition().x + size.x / 2;
}

float ColliderComponent::GetLeftBorder()
{
    return transformComponent->GetPosition().x - size.x / 2;
}

Vector2 ColliderComponent::GetPosition()
{
    Vector4 pos = transformComponent->GetPosition();
    return Vector2(pos.x, pos.y);
}
