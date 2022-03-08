#pragma once
#include <memory>
#include <vector>

#include "InputDevice\InputDevice.h"

#include "SceneComponent.h"
#include "MoveComponent.h"
#include "InputComponent.h"
#include "ColliderComponent.h"
#include "PaddleInputComponent.h"

typedef DirectX::SimpleMath::Vector2 Vector2;

class PongGame
{
public:
    PongGame(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<Renderer> renderer, InputDevice* input);

    void InitGame();
    void Update(float deltaTime);
    void HandleInput();

    void Debug();
    std::vector<SceneComponent>* GetSceneComponents() { return &sceneComponents; }

private:
    void RestartRound();
    void CheckBallCollision();
    void FixPaddlesPositions();
    void PrintScore();


private:
    Vector2 worldSize;
    std::vector<SceneComponent> sceneComponents;
    SceneComponent* paddles[2];
    SceneComponent* ball;

    InputComponent* playersInput[2];
    MoveComponent moveComponents[3];
    ColliderComponent colliders[3];

    int score[2];
};