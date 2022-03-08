#pragma once
#include "PongGame.h"

#include <cstdlib>
#include <map>
#include <iostream>

#include "PaddleRenderComponent.h"
#include "BallRenderComponent.h"
#include "InputDevice\Keys.h"

// entt 
PongGame::PongGame(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<Renderer> renderer, InputDevice* input)
{
    ID3D11Device* device = deviceResources->GetDevice();

    std::shared_ptr<RenderData> paddleRender = std::make_shared<PaddleRenderComponent>(device);
    std::shared_ptr<RenderData> ballRender = std::make_shared<BallRenderComponent>(device);
    sceneComponents = std::vector<SceneComponent>(3);

    sceneComponents[0] = SceneComponent(paddleRender, -0.85, 0.0);
    sceneComponents[1] = SceneComponent(paddleRender, 0.85, 0.0);
    sceneComponents[2] = SceneComponent(ballRender, 0, 0.0);
    
    paddles[0] = &(sceneComponents[0]);
    paddles[1] = &(sceneComponents[1]);
    ball = &(sceneComponents[2]);

    moveComponents[0] = MoveComponent(&sceneComponents[0]);
    moveComponents[1] = MoveComponent(&sceneComponents[1]);
    moveComponents[2] = MoveComponent(&sceneComponents[2]);

    std::map<Keys, DirectX::XMFLOAT2> left = std::map<Keys, DirectX::XMFLOAT2>{ {Keys::W, DirectX::XMFLOAT2(0,1)}, {Keys::S, DirectX::XMFLOAT2(0,-1)}, };
    std::map<Keys, DirectX::XMFLOAT2> right = std::map<Keys, DirectX::XMFLOAT2>{ {Keys::Up, DirectX::XMFLOAT2(0,1)}, {Keys::Down, DirectX::XMFLOAT2(0,-1)}, };

    playersInput[0] = new PaddleInputComponent(input, &moveComponents[0], left);
    playersInput[1] = new PaddleInputComponent(input, &moveComponents[1], right);

    colliders[0] = ColliderComponent(&sceneComponents[0], Vector2(0.1, 0.4));
    colliders[1] = ColliderComponent(&sceneComponents[1], Vector2(0.1, 0.4));
    colliders[2] = ColliderComponent(&sceneComponents[2], Vector2(0.024, 0.058));

    worldSize = Vector2(2, 1);
    score[0] = 0;
    score[1] = 0;
}

void PongGame::InitGame()
{
    RestartRound();
    score[0] = 0;
    score[1] = 0;
    PrintScore();
}

void PongGame::HandleInput()
{
    for (auto& input : playersInput)
    {
        input->HandleInput();
    }
}

void PongGame::Update(float deltaTime)
{
    for (auto& item : moveComponents)
    {
        item.Update(deltaTime);
    }

    // fix ball and paddles positions
    FixPaddlesPositions();
    CheckBallCollision();
}

void PongGame::FixPaddlesPositions()
{
    for (int i = 0; i < 2; i++)
    {
        Vector4 position = paddles[i]->GetPosition();

        float border = colliders[i].GetUpperBorder();
        if (border > worldSize.y / 2)
        {
            position.y -= border - worldSize.y / 2;
            paddles[i]->SetPosition(position);
        }
        else
        {
            border = colliders[i].GetLowerBorder();
            if (border < -worldSize.y / 2)
            {
                position.y -= border + worldSize.y / 2;
                paddles[i]->SetPosition(position);
            }
        }
    }
}

void PongGame::PrintScore()
{
    std::cout << "Score: " << score[0] << " : " << score[1] << std::endl;
}

void PongGame::Debug()
{
    Vector4 pos = paddles[0]->GetPosition();
    std::cout << "Pos: " << pos.x << " " << pos.y << "\n Upper: " << colliders[0].GetUpperBorder() << " Lower: " << colliders[0].GetLowerBorder() << std::endl;
}

void PongGame::RestartRound()
{
    paddles[0]->SetY(0);
    paddles[1]->SetY(0);

    ball->SetY(0);
    ball->SetX(0);
    float random_float = (rand() * 1.f / RAND_MAX - 0.5) * 2;
    float random_float_2 = (rand() * 1.f / RAND_MAX - 0.5) * 2;
    Vector2 velocity = Vector2((random_float_2 > 0 ? 1 : -1), random_float);
    velocity.Normalize();
    moveComponents[2].SetVelocity(velocity);
}

void PongGame::CheckBallCollision()
{
    // Check win state: left right borders collisions
    if (colliders[2].GetLeftBorder() < -worldSize.x / 2)
    {
        score[1]++;
        PrintScore();
        RestartRound();
        return;
    }

    if (colliders[2].GetRightBorder() > worldSize.x / 2)
    {
        score[0]++;
        PrintScore();
        RestartRound();
        return;
    }

    // Check top bottom border collision
    if (colliders[2].GetUpperBorder() > worldSize.y / 2)
    {
        Vector2 velocity = moveComponents[2].GetVelocity();
        velocity.y *= -1;
        moveComponents[2].SetVelocity(velocity);
    }

    if (colliders[2].GetLowerBorder() < -worldSize.y / 2)
    {
        Vector2 velocity = moveComponents[2].GetVelocity();
        velocity.y *= -1;
        moveComponents[2].SetVelocity(velocity);
    }

    // Check paddle collision and check angle
    Vector4 ballPos = ball->GetPosition();
    SceneComponent* paddle = nullptr;
    ColliderComponent* collider = nullptr;

    if (ballPos.x > colliders[0].GetRightBorder() && colliders[0].IsOverlapingCollider(colliders[2]))
    {
        paddle = paddles[0];
        collider = &colliders[0];
    }
    else if(ballPos.x < colliders[1].GetLeftBorder() && colliders[1].IsOverlapingCollider(colliders[2]))
    {
        paddle = paddles[1];
        collider = &colliders[1];
    }

    // Bounce
    if (paddle != nullptr)
    {
        float centerBoard = paddle->GetPosition().y;
        float distance = ballPos.y - centerBoard;
        Vector2 velocity = moveComponents[2].GetVelocity();
        
        velocity.y = distance / collider->GetSize().y;
        velocity.x *= -1;

        float length = velocity.Length() * 1.05;
        velocity.Normalize();
        moveComponents[2].SetVelocity(velocity * length);
    }
}

