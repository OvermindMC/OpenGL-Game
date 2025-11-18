#pragma once

#include "Render/Renderer.h"
#include "Camera/Camera.h"

enum class CursorMode {
    Locked,     // FPS Gameplay
    Free,       // Menus, UI
    Hidden,     // Other
};

class Game {
public:
    Game();
    ~Game();

    GLFWwindow* getWindow();
    
    Renderer* getRndr();
    Camera* getCam();

    void Run();
    void Stop();

    void setCursorMode(CursorMode);
    CursorMode getCursorMode();

    void handleMouseInput(double, double);

    void updateViewport(int, int);
    const int* getViewport();
private:
    GLFWwindow* mWindow;
    Renderer* mRndr;
    Camera* mCam;

    bool mIsRunning;
    float mDelta;

    int mVp[2] = { 0, 0 };

    CursorMode mCursorMode;
    glm::vec2 lastMousePos;
};