#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <string>

class Game;

class Renderer {
public:
    Renderer(Game*);
    ~Renderer();

    Game* getGame();

    unsigned int createShader(const char*, const char*);

    void Render(float);
    
    void updateOrigin();
    glm::dvec3 getOrigin();
private:
    Game* gamePtr;

    glm::dvec3 mRndrOffset;
    

    unsigned int cubeVAO = 0, cubeVBO = 0, cubeShader = 0;
};