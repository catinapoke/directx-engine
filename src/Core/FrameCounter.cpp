#include "FrameCounter.h"

void FrameCounter::Init()
{
    time = std::chrono::steady_clock::now();
    totalTime = 0;
    frameCount = 0;
    fps = 0;
}

void FrameCounter::CountFrame()
{
    auto current = std::chrono::steady_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(current - time).count() / 1000000.0f;

    totalTime += deltaTime;
    frameCount++;

    if (totalTime > 1.0f) {
        fps = frameCount / totalTime;
        totalTime -= 1.0f;
        frameCount = 0;
    }
    time = current;
}

