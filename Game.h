#pragma once
#include <memory>
#include <vector>

class DeviceResources;
class InputDevice;
class Actor;
class SceneActor;

class Game
{
public:
    Game() = default;
    Game(std::shared_ptr<DeviceResources> deviceResources, std::shared_ptr<InputDevice> input) {};
    ~Game();

    virtual void Awake();
    virtual void Start();
    virtual void Update(float deltaTime);
    void AddActors(std::vector<Actor*> actor);

    std::vector<SceneActor*>* GetSceneActors();

    static Game* GetCurrentGame();

protected:
    std::vector<Actor*> actors;
    std::vector<SceneActor*> sceneActors;

    static Game* current_game;
};