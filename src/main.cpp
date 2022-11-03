#include "plankton.h"

#include <iostream>

#include "Shader.h"

#define SCR_WIDTH  800
#define SCR_HEIGHT 600

#ifndef ASSETS_PATH
#define ASSETS_PATH "../assets/"
#endif

int main(void) {
    pt::initWindow(SCR_WIDTH, SCR_HEIGHT, "lol");

    Shader shader(ASSETS_PATH"shaders/vertexShader.vert", ASSETS_PATH"shaders/fragmentShader.frag");

    float vertices[] = {
         // positions       // colors
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top
    };

    unsigned int indices[] = {
        0, 1, 2
    };

    unsigned int vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shader.use();

    while (!pt::windowShouldClose()) {
        pt::prepareFrame();

        PT_INFO("FPS: {}", 1.0/pt::getDeltaTime());

        if (pt::isKeyPressed(pt::Key::KEY_ESCAPE)) {
            pt::exitWindow();
        }

        pt::clearWindow(0.4f, 0.5f, 0.3f, 1.0f);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        pt::displayWindow();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    pt::shutdown();

    return 0;
}
