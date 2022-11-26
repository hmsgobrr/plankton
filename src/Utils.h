#ifndef COLOR_H
#define COLOR_H

namespace pt {

struct Color {
	float r, g, b, a;
};

struct Rect {
	float x, y, w, h;
};

struct Vector2 {
	float x, y;
};

struct Camera {
	Vector2 position;
	float scale;
	float rotation;
};

}

#endif
