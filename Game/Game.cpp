#include "Game.h"
#include <iostream>

void windowResizeCallback(GLFWwindow* window, int width, int height) {
    if(Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window))) {
        std::cout << "!\n";
        game->updateViewport(width, height);
        glfwSwapInterval(1);
    };
};

void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
    if(Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window))) {
        game->handleMouseInput(xPos, yPos);
    };
};

Game::Game() : mWindow(nullptr), mRndr(nullptr), mPlayer(nullptr), mCam(nullptr), mIsRunning(false) {
    if(!glfwInit()) {
        std::cout << "Failed to initialize GLFW!\n";
    } else {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

        mWindow = glfwCreateWindow(mode->width, mode->height, "Game", nullptr, nullptr);
        if(!mWindow) {
            std::cout << "Failed to create GLFW Window!\n";
            glfwTerminate();
        } else {
            glfwMakeContextCurrent(mWindow);
            glfwSwapInterval(1); // Set VSync == true

            if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cout << "Failed to initialize GLAD!\n";
            };

            glfwSetWindowUserPointer(mWindow, this);

            int width, height;
            glfwGetFramebufferSize(mWindow, &width, &height);
            updateViewport(width, height);

            glfwSetFramebufferSizeCallback(mWindow, windowResizeCallback);
            glfwSetCursorPosCallback(mWindow, mouseCallback);

            mRndr = new Renderer(this);

            mPlayer = new Player(this);
            mCam = new Camera(this);

            mCam->setMode(CameraMode::Attach, mPlayer);

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();

            ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
            ImGui_ImplOpenGL3_Init("#version 430");

            bindInput(MoveInput::Left, GLFW_KEY_A);
            bindInput(MoveInput::Right, GLFW_KEY_D);
            bindInput(MoveInput::Forward, GLFW_KEY_W);
            bindInput(MoveInput::Backward, GLFW_KEY_S);

            bindInput(MoveInput::Jump, GLFW_KEY_SPACE);
            bindInput(MoveInput::Crouch, GLFW_KEY_LEFT_SHIFT);

            this->Run(); // Begin Render Loop
        };
    };
};

Game::~Game() {
    if(ImGui::GetCurrentContext()) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        
        ImGui::DestroyContext();
    };

    if(mWindow) {
        glfwDestroyWindow(mWindow);
        mWindow = nullptr;
    };

    glfwTerminate();
};

GLFWwindow* Game::getWindow() {
    return mWindow;
};

Renderer* Game::getRndr() {
    return mRndr;
};

Camera* Game::getCam() {
    return mCam;
};

void Game::Run() {
    if(mIsRunning || !mWindow) {
        return;
    };

    mIsRunning = true;
    double startTime = glfwGetTime();

    setCursorMode(CursorMode::Locked);

    while(!glfwWindowShouldClose(mWindow) && mIsRunning) {
        double currTime = glfwGetTime();
        double deltaTime = currTime - startTime;
        
        deltaTime = std::min(0.1, deltaTime);
        mDelta = deltaTime;

        startTime = currTime;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mCam->update();
        mPlayer->update(mDelta);
        mRndr->Render(mDelta);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    };
};

void Game::Stop() {
    if(!mIsRunning)
        return;
    
    mIsRunning = false;
};

void Game::setCursorMode(CursorMode mode) {
    mCursorMode = mode;

    glfwSetInputMode(mWindow, GLFW_CURSOR,
        mode == CursorMode::Locked ? GLFW_CURSOR_DISABLED :
            mode == CursorMode::Hidden ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL
    );

    if(mode == CursorMode::Locked) {
        double x, y;
        
        glfwGetCursorPos(mWindow, &x, &y);
        lastMousePos = glm::vec2(x, y);
    };
};

CursorMode Game::getCursorMode() {
    return mCursorMode;
};

void Game::handleMouseInput(double xPos, double yPos) {
    if (mCursorMode != CursorMode::Locked || !mPlayer)
        return;

    glm::vec2 curr(xPos, yPos);

    glm::vec2 raw(
        lastMousePos.y - curr.y,     // pitch
        curr.x - lastMousePos.x      // yaw
    );

    lastMousePos = curr;

    float sens = 0.10f;
    raw *= sens;

    float speed = glm::length(raw);

    static glm::vec2 smooth(0.f);
    float blend;

    if (speed < 0.5f)
        blend = 0.0f;
    else if (speed < 1.5f)
        blend = (speed - 0.5f) / 1.0f;
    else
        blend = 1.0f;

    float smoothStrength = 12.f;
    float t = 1.f - expf(-smoothStrength * mDelta);

    smooth = glm::mix(smooth, raw, t);
    glm::vec2 final = glm::mix(smooth, raw, blend);

    if (speed < 0.0001f)
        smooth = glm::vec2(0.f);
    
    glm::vec2 rot = mPlayer->getRot();
    rot.x += final.x;
    rot.y += final.y;

    mPlayer->setRot(rot);
};

void Game::updateViewport(int width, int height) {
    mVp[0] = width, mVp[1] = height;
    glViewport(0, 0, width, height);
};

const int* Game::getViewport() {
    return mVp;
};

bool Game::isInputPressed(MoveInput input) {
    auto iter = mInputs.find(input);

    return (
        iter != mInputs.end() ? glfwGetKey(mWindow, iter->second) == GLFW_PRESS : false
    );
};

void Game::bindInput(MoveInput input, int keyCode) {
    mInputs[input] = keyCode;
};