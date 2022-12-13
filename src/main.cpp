#include "plankton.h"

#define SCR_WIDTH  800
#define SCR_HEIGHT 600

#define COW_WIDTH  220
#define COW_HEIGHT 184

#define COW_ROWS 7
#define COW_COLS 3

#define CAM_SPEED 100
#define CAM_ROT_SPEED 70
#define CAM_ZOOM_AMOUNT 2.0f

int main(void) {
    pt::initWindow(SCR_WIDTH, SCR_HEIGHT, "lol");

    pt::Camera camera({ 0.0f, 0.0f }, 1.0f, 0.0f);

    pt::Texture polishcow;
    polishcow.createFromFile(ASSETS_PATH"polishcow.png", true);

    float animationTimeCounter = 0.0f;
    int currentFrame = 0;

    pt::Rect frameRects[21];
    for (int i = 0; i < COW_COLS; i++) {
        for (int j = 0; j < COW_ROWS; j++) {
            frameRects[j + (i * COW_ROWS)] = {
                j * (1.0f / (float)COW_ROWS),
                i * (1.0f / (float)COW_COLS),
                1.0f / (float)COW_ROWS,
                1.0f / (float)COW_COLS
            };
        }
    }

    while (!pt::windowShouldClose()) {
        pt::prepareFrame();

        if (pt::isKeyPressed(pt::Key::KEY_ESCAPE)) {
            pt::closeWindow();
        }

        if (pt::isKeyDown(pt::Key::KEY_A)) camera.position.x -= CAM_SPEED * pt::getDeltaTime();
        if (pt::isKeyDown(pt::Key::KEY_D)) camera.position.x += CAM_SPEED * pt::getDeltaTime();
        if (pt::isKeyDown(pt::Key::KEY_W)) camera.position.y -= CAM_SPEED * pt::getDeltaTime();
        if (pt::isKeyDown(pt::Key::KEY_S)) camera.position.y += CAM_SPEED * pt::getDeltaTime();

        if (pt::isKeyDown(pt::Key::KEY_E)) camera.rotation += CAM_ROT_SPEED * pt::getDeltaTime();
        if (pt::isKeyDown(pt::Key::KEY_Q)) camera.rotation -= CAM_ROT_SPEED * pt::getDeltaTime();

        camera.zoom += pt::getMouseWheelMovement().y * CAM_ZOOM_AMOUNT * pt::getDeltaTime();

        pt::setView(camera);
        
        animationTimeCounter += pt::getDeltaTime();

        if (animationTimeCounter >= 1 / 10.0f) { // TODO: sync animation speed with the music
            currentFrame++;
            currentFrame %= 21; // loop it back to 0 if it reaches 21 (max frame)
            animationTimeCounter = 0;
        }

        pt::Vector2 mousepos = pt::getMousePosition();

        PT_INFO(
            "LEFT: {} {}\tRIGHT: {} {}\tMID: {} {}",
            pt::isMouseButtonDown(pt::MouseButton::MOUSE_BUTTON_LEFT) ? 1 : 0,
            pt::isMouseButtonPressed(pt::MouseButton::MOUSE_BUTTON_LEFT) ? "X" : (pt::isMouseButtonReleased(pt::MouseButton::MOUSE_BUTTON_LEFT) ? "O" : ""),

            pt::isMouseButtonDown(pt::MouseButton::MOUSE_BUTTON_RIGHT) ? 1 : 0,
            pt::isMouseButtonPressed(pt::MouseButton::MOUSE_BUTTON_RIGHT) ? "X" : (pt::isMouseButtonReleased(pt::MouseButton::MOUSE_BUTTON_RIGHT) ? "O" : ""),

            pt::isMouseButtonDown(pt::MouseButton::MOUSE_BUTTON_MIDDLE) ? 1 : 0,
            pt::isMouseButtonPressed(pt::MouseButton::MOUSE_BUTTON_MIDDLE) ? "X" : (pt::isMouseButtonReleased(pt::MouseButton::MOUSE_BUTTON_MIDDLE) ? "O" : "")
        );

        pt::clearFrame({ 0.1f, 0.1f, 0.1f, 1.0f });
        pt::drawTexture(
            polishcow,
            frameRects[currentFrame],
            { mousepos.x - COW_WIDTH/2, mousepos.y - COW_HEIGHT / 2, COW_WIDTH, COW_HEIGHT },
            0.0f,
            { 1.0f, 1.0f, 1.0f, 1.0f }
        );

        pt::display();
    }

    pt::shutdown();

    return 0;
}
