#include "plankton.h"

#define SCR_WIDTH  800
#define SCR_HEIGHT 600

#define COW_WIDTH  220
#define COW_HEIGHT 184

#define COW_ROWS 7
#define COW_COLS 3

#define CAM_SPEED 100

int main(void) {
    pt::initWindow(SCR_WIDTH, SCR_HEIGHT, "lol");

    pt::Camera camera({ 0.0f, 0.0f }, { SCR_WIDTH/2.0f, SCR_HEIGHT/2.0f }, 0.0f, 0.0f);

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

        if (pt::isKeyDown(pt::Key::KEY_A)) {
            camera.position.x -= CAM_SPEED * pt::getDeltaTime();
        }
        if (pt::isKeyDown(pt::Key::KEY_D)) {
            camera.position.x += CAM_SPEED * pt::getDeltaTime();
        }
        if (pt::isKeyDown(pt::Key::KEY_W)) {
            camera.position.y -= CAM_SPEED * pt::getDeltaTime();
        }
        if (pt::isKeyDown(pt::Key::KEY_S)) {
            camera.position.y += CAM_SPEED * pt::getDeltaTime();
        }
        
        animationTimeCounter += pt::getDeltaTime();

        if (animationTimeCounter >= 1 / 10.0f) { // TODO: sync animation speed with the music
            currentFrame++;
            currentFrame %= 21; // loop it back to 0 if it reaches 21 (max frame)
            animationTimeCounter = 0;
        }

        pt::clearFrame({ 0.1f, 0.1f, 0.1f, 1.0f });

        pt::drawTexture(
            polishcow,
            frameRects[currentFrame],
            { SCR_WIDTH / 2 - COW_WIDTH / 2, SCR_HEIGHT / 2 - COW_HEIGHT / 2, COW_WIDTH, COW_HEIGHT },
            0.0f,
            { 1.0f, 1.0f, 1.0f, 1.0f }
        );

        pt::display(camera);
    }

    pt::shutdown();

    return 0;
}
