#pragma once
#include <chrono>
class FrameCounter
{
public:
    void Init();
    void CountFrame();

    float GetFPS() { return fps; }
    float GetDeltaTime() { return deltaTime; }

private:
    std::chrono::time_point<std::chrono::steady_clock> time;
    float totalTime;
    unsigned int frameCount;
    float fps;
    float deltaTime;
};