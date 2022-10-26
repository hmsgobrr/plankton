#ifndef PLANKTON_H
#define PLANKTON_H

#include "Window.h"
#include "Log.h"

#include <string.h>

namespace pt {

void initWindow(int windowWidth, int windowHeight, const char* windowTitle);
bool windowShouldClose();
void exitWindow();
void clearWindow(float red, float green, float blue, float alpha);
void displayWindow();
void shutdown();

} // namespace pt


#endif // PLANKTON_H
