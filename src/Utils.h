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
	Camera(const Vector2& p_position, const Vector2& p_zoomRotationOrigin, float p_zoom, float p_rotation):
		position({ p_position.x, p_position.y }),
		zoomRotationOrigin({ p_zoomRotationOrigin.x, p_zoomRotationOrigin.y }),
		zoom(p_zoom),
		rotation(p_rotation) {}
	Vector2 position;
	Vector2 zoomRotationOrigin;
	float zoom;
	float rotation;
};

}

#endif
