#include "plankton.h"

#define SCR_WIDTH  800
#define SCR_HEIGHT 600

int main(void) {
    pt::initWindow(SCR_WIDTH, SCR_HEIGHT, "lol");

    while (!pt::windowShouldClose()) {
        pt::prepareFrame();

        PT_INFO("FPS: {}", 1.0f/pt::getDeltaTime());

        if (pt::isKeyPressed(pt::Key::KEY_ESCAPE)) {
            pt::exitWindow();
        }

        pt::clearFrame({ 0.1f, 0.1f, 0.1f, 1.0f });

        pt::drawRect({ SCR_WIDTH / 2 - 100 / 2, SCR_HEIGHT / 2 - 100 / 2, 100, 100 }, { 0.0f, 0.0f, 0.9f, 1.0f });

        pt::displayWindow();
    }

    pt::shutdown();

    return 0;
}
