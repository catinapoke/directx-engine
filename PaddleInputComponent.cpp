#pragma once
#include "PaddleInputComponent.h"
//#include "InputComponent.h"
#include "MoveComponent.h"

typedef DirectX::SimpleMath::Vector2 Vector2;

PaddleInputComponent::PaddleInputComponent(InputDevice* input, MoveComponent* movement, std::map<Keys, DirectX::XMFLOAT2>& velocityMap)
    :InputComponent(input), moveComponent(movement), velocity(velocityMap)
{
}

void PaddleInputComponent::HandleInput()
{
    Vector2 finalVelocity(0, 0);
    for (const auto& pair : velocity) {
        if (inputDevice->IsKeyDown(pair.first))
            finalVelocity += pair.second;
    }
    
    moveComponent->SetVelocity(finalVelocity);
}
