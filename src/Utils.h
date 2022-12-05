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
	Camera(const Vector2& p_position, float p_zoom, float p_rotation):
		position({ p_position.x, p_position.y }),
		zoom(p_zoom),
		rotation(p_rotation) {}
	Vector2 position;
	float zoom;
	float rotation;
};

}

#endif
