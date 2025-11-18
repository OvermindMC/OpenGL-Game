#include "Renderer.h"
#include "../Game.h"

#include <iostream>

static float cubeVertices[] = {
    // positions
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

const char* vert = R"(
    #version 430 core

    layout (location = 0) in vec3 aPos;

    uniform mat4 uProj;
    uniform mat4 uView;
    uniform mat4 uModel;

    void main()
    {
        gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
    }
)";

const char* frag = R"(
    #version 430 core

    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(0.8, 0.2, 0.3, 1.0); // Red-ish cube
    }
)";

Renderer::Renderer(Game* game) : gamePtr(game) {
    glEnable(GL_DEPTH_TEST);

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // Vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,                    // layout location = 0
        3,                    // vec3
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),    // stride
        (void*)0              // offset
    );

    glBindVertexArray(0);

    cubeShader = createShader(vert, frag);
};

Renderer::~Renderer() {
    //
};

Game* Renderer::getGame() {
    return gamePtr;
};

unsigned int Renderer::createShader(const char* vertexSrc, const char* fragmentSrc) {
    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexSrc, nullptr);
    glCompileShader(vs);

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentSrc, nullptr);
    glCompileShader(fs);

    unsigned int program = glCreateProgram();
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
};

void Renderer::Render(float delta) {
    if(Camera* cam = getGame()->getCam()) {
        glUseProgram(cubeShader);

        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(0.f, 0.f, -5.f));
        
        glm::mat4 view = cam->getViewMatrix();
        glm::mat4 proj = cam->getProjection();

        glUniformMatrix4fv(glGetUniformLocation(cubeShader, "uModel"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(cubeShader, "uView"),  1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(cubeShader, "uProj"),  1, GL_FALSE, &proj[0][0]);

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    };
};