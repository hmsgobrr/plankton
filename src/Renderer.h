#ifndef RENDERER_H
#define RENDERER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Shader.h"
#include "Utils.h"

namespace pt {

class Renderer {
public:
	// Singleton stuff
	Renderer(Renderer const&) = delete;
	void operator=(Renderer const&) = delete;
	static Renderer& getInstance() {
		static Renderer instance;
		return instance;
	}

	void init(GLFWwindow* contextWindow, float frameWidth, float frameHeight);
	void shutdown();

	void clearFrame(Color color);
	void drawRect(Rect rect, Color color);
private:
	Renderer() {}

	Shader m_shapeShader;
	unsigned int m_quadVAO;
};

}

#endif