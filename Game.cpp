#include "Game.h"

#include "DeviceResources.h"
#include "InputDevice\InputDevice.h"
#include "Actor.h"
#include "SceneActor.h"

Game::~Game()
{
    for (Actor* actor : actors)
        delete actor;
}

void Game::Awake()
{
    for (Actor* actor : actors)
        actor->Awake();
}

void Game::Start()
{
    for (Actor* actor : actors)
        actor->Start();
}

void Game::Update(float deltaTime)
{
    for (Actor* actor : actors)
        actor->Update(deltaTime);
}

void Game::AddActors(std::vector<Actor*> actors)
{
    this->actors.reserve(this->actors.size() + actors.size());

    for (Actor* actor : actors)
    {
        this->actors.push_back(actor);
    }
}

std::vector<SceneActor*>* Game::GetSceneActors()
{
    return &sceneActors; 
}
