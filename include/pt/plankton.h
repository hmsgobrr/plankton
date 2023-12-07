#ifndef PLANKTON_H
#define PLANKTON_H

#include "pt/Texture.h"

namespace pt {

/// Struct for representing a color. Uses a RGBA format.
struct Color {
	float r, g, b, a;
};

/// Struct for representing a rectangle.
struct Rect {
	float x, y, width, height;
};

/// A 2D Vector struct consisting x, y in floats
struct Vector2 {
	float x, y;
};

/// A 2D Vector struct consisting x, y in integers
struct Vector2Int {
	int x, y;
};

/// Struct for representing a camera viewpoint.
struct Camera {
	Camera(const Vector2& p_position, float p_zoom, float p_rotation):
		position({ p_position.x, p_position.y }),
		zoom(p_zoom),
		rotation(p_rotation) {}
	Vector2 position;
	float zoom;
	float rotation;
};

/// Keyboard key enums, refers to a glfw keycodes that represents a keyboard key.
enum class Key {
    NO_KEY              = 0,
    KEY_SPACE           = 32,
    KEY_APOSTROPHE      = 39, // Key: '
    KEY_COMMA           = 44, // Key: ,
    KEY_MINUS           = 45, // Key: -
    KEY_PERIOD          = 46, // Key: .
    KEY_SLASH           = 47, // Key: /
    KEY_0               = 48,
    KEY_1               = 49,
    KEY_2               = 50,
    KEY_3               = 51,
    KEY_4               = 52,
    KEY_5               = 53,
    KEY_6               = 54,
    KEY_7               = 55,
    KEY_8               = 56,
    KEY_9               = 57,
    KEY_SEMICOLON       = 59, // Key: ;
    KEY_EQUAL           = 61, // Key: =
    KEY_A               = 65,
    KEY_B               = 66,
    KEY_C               = 67,
    KEY_D               = 68,
    KEY_E               = 69,
    KEY_F               = 70,
    KEY_G               = 71,
    KEY_H               = 72,
    KEY_I               = 73,
    KEY_J               = 74,
    KEY_K               = 75,
    KEY_L               = 76,
    KEY_M               = 77,
    KEY_N               = 78,
    KEY_O               = 79,
    KEY_P               = 80,
    KEY_Q               = 81,
    KEY_R               = 82,
    KEY_S               = 83,
    KEY_T               = 84,
    KEY_U               = 85,
    KEY_V               = 86,
    KEY_W               = 87,
    KEY_X               = 88,
    KEY_Y               = 89,
    KEY_Z               = 90,
    KEY_LEFT_BRACKET    = 91, // Key: [
    KEY_BACKSLASH       = 92, // Key: '\'
    KEY_RIGHT_BRACKET   = 93, // Key: ]
    KEY_GRAVE_ACCENT    = 96, // Key: `
    KEY_ESCAPE          = 256,
    KEY_ENTER           = 257,
    KEY_TAB             = 258,
    KEY_BACKSPACE       = 259,
    KEY_INSERT          = 260,
    KEY_DELETE          = 261,
    KEY_RIGHT           = 262,
    KEY_LEFT            = 263,
    KEY_DOWN            = 264,
    KEY_UP              = 265,
    KEY_PAGE_UP         = 266,
    KEY_PAGE_DOWN       = 267,
    KEY_HOME            = 268,
    KEY_END             = 269,
    KEY_CAPS_LOCK       = 280,
    KEY_SCROLL_LOCK     = 281,
    KEY_NUM_LOCK        = 282,
    KEY_PRINT_SCREEN    = 283,
    KEY_PAUSE           = 284,
    KEY_F1              = 290,
    KEY_F2              = 291,
    KEY_F3              = 292,
    KEY_F4              = 293,
    KEY_F5              = 294,
    KEY_F6              = 295,
    KEY_F7              = 296,
    KEY_F8              = 297,
    KEY_F9              = 298,
    KEY_F10             = 299,
    KEY_F11             = 300,
    KEY_F12             = 301,
    KEY_F13             = 302,
    KEY_F14             = 303,
    KEY_F15             = 304,
    KEY_F16             = 305,
    KEY_F17             = 306,
    KEY_F18             = 307,
    KEY_F19             = 308,
    KEY_F20             = 309,
    KEY_F21             = 310,
    KEY_F22             = 311,
    KEY_F23             = 312,
    KEY_F24             = 313,
    KEY_F25             = 314,
    KEY_LEFT_SHIFT      = 340,
    KEY_LEFT_CONTROL    = 341,
    KEY_LEFT_ALT        = 342,
    KEY_LEFT_SUPER      = 343,
    KEY_RIGHT_SHIFT     = 344,
    KEY_RIGHT_CONTROL   = 345,
    KEY_RIGHT_ALT       = 346,
    KEY_RIGHT_SUPER     = 347,
    KEY_MENU            = 348,
    // Keypad keys
    KEY_KP_0            = 320,
    KEY_KP_1            = 321,
    KEY_KP_2            = 322,
    KEY_KP_3            = 323,
    KEY_KP_4            = 324,
    KEY_KP_5            = 325,
    KEY_KP_6            = 326,
    KEY_KP_7            = 327,
    KEY_KP_8            = 328,
    KEY_KP_9            = 329,
    KEY_KP_DECIMAL      = 330,
    KEY_KP_DIVIDE       = 331,
    KEY_KP_MULTIPLY     = 332,
    KEY_KP_SUBTRACT     = 333,
    KEY_KP_ADD          = 334,
    KEY_KP_ENTER        = 335,
    KEY_KP_EQUAL        = 336
};

/// Mouse Buttons enums, refers to the clickable buttons on the mouse.
enum class MouseButton {
    MOUSE_BUTTON_LEFT   = 0,
    MOUSE_BUTTON_RIGHT  = 1,
    MOUSE_BUTTON_MIDDLE = 2
};

/// Initialize window.
void initWindow(int windowWidth, int windowHeight, const char* windowTitle);
/// Returns true if window should be closed at that time.
bool windowShouldClose();
/// Sets windowShould close value to true which results in exiting the game loop after the current frame.
void closeWindow();
/// Resets the frame with the specified color as a background.
void clearFrame(const Color& color);
/// Displays the frame that has been drawn.
void display();
/// Updates states and other variables, call this before doing other stuff on a frame.
void prepareFrame();
/// Sets the viewpoint of the game world to the camera specified.
void setView(const Camera& camera);
/// Closes the window and unloads OpenGL context.
void shutdown();

/// Returns seconds since last frame has drawn.
float getDeltaTime();
/// Returns seconds since window has been created.
double getTime();
/// Return a random number between min and max (min and max included).
int getRandomNumber(int min, int max);

/**
 * Draws a rectangle on the frame.
 * 
 * @param rect      The size and position of the rectangle.
 * @param rotation  The rotation of the rectangle.
 * @param color     The color of the rectangle.
 */
void drawRect(const Rect& rect, float rotation, const Color& color);

/**
 * Draws an image texture on the frame.
 * 
 * @param texture           The texture object to draw.
 * @param sourceRec         The part of the image to draw.
 * @param destinationRec    The size and position of the texture. A negative width/height value will flip the texture.
 * @param rotation          The rotation of the texture.
 * @param tint              The color to tint the resulting texture. Use a white color if you don't need tinting.
 */
void drawTexture(Texture& texture, const Rect& sourceRec, const Rect& destinationRec, float rotation, const Color& tint);

/// Check if a key has been pressed once.
bool isKeyPressed(Key key);
/// Check if a key has been released once.
bool isKeyReleased(Key key);
/// Check if a key is being pressed.
bool isKeyDown(Key key);
/// Check if a key is not being pressed.
bool isKeyUp(Key key);
/**
 * @brief Return keys pressed at the time.
 * Call multiple time to get the key pressed after (still in the same frame time).
 * Returns NO_KEY if no keys are pressed.
 */
Key getKeyPressed();

/// Check if a mouse button has been pressed once.
bool isMouseButtonPressed(MouseButton button);
/// Check if a mouse button has been released once.
bool isMouseButtonReleased(MouseButton button);
/// Check if a mouse button is being pressed.
bool isMouseButtonDown(MouseButton button);
/// Check if a mouse is not being pressed.
bool isMouseButtonUp(MouseButton button);
/// Returns the current mouse cursor position.
Vector2& getMousePosition();
/**
 * @brief Returns any movement of the mouse wheel.
 * The returning x from the Vector2 shows the vertical movement, Positive means upwards, Negative means downwards.
 * Whereas the y shows the horizontal movement, Positive means right, Negative means left.
 */
Vector2& getMouseWheelMovement();

/**
* Generates a 2D perlin noise.
* Just ignore the y if you want a 1D noise.
* (might be buggy)
* 
* This function is defined at PerlinNoise.cpp.
* 
* @param x      The sample point in x-axis.
* @param y      The sample point in y-axis.
* @param seed   A value between 0.0 and 1.0 that will be used as a seed for the noise.
* @return       A value between -1 and 1 representing the specified point.
*/
double perlinNoise(double x, double y, double seed);

} // namespace pt

#endif // PLANKTON_H
