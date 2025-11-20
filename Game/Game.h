#pragma once

#include "Render/Renderer.h"
#include "Entity/Player.h"
#include "Camera/Camera.h"

#include <map>

enum class CursorMode {
    Locked,     // FPS Gameplay
    Free,       // Menus, UI
    Hidden,     // Other
};

enum class MoveInput : int {
    Forward, Backward, Left, Right,
    Jump, Crouch
};

class Game {
public:
    Game();
    ~Game();

    GLFWwindow* getWindow();
    
    Renderer* getRndr();
    Player* getPlayer();
    Camera* getCam();

    void Run();
    void Stop();

    void setCursorMode(CursorMode);
    CursorMode getCursorMode();

    void handleMouseInput(double, double);

    void updateViewport(int, int);
    const int* getViewport();

    bool isInputPressed(MoveInput);
    void bindInput(MoveInput, int);
private:
    GLFWwindow* mWindow;
    Renderer* mRndr;
    Player* mPlayer;
    Camera* mCam;

    bool mIsRunning;
    float mDelta;

    int mVp[2] = { 0, 0 };

    CursorMode mCursorMode;
    glm::vec2 lastMousePos;

    std::map<MoveInput, int> mInputs;
};