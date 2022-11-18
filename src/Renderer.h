#ifndef RENDERER_H
#define RENDERER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Shader.h"
#include "Utils.h"
#include "Texture.h"

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

	void clearFrame(const Color& color);
	void drawRect(const Rect& rect, float rotation, const Color& color);
	void drawTexture(Texture& texture, const Rect& sourceRec, const Rect& destinationRec, float rotation, const Color& tint);
private:
	Renderer():
		m_quadVAO(0),
		m_quadVBO(0),
		m_quadIB(0) {}

	void drawQuad(const Rect& rect, float rotation);

	Shader m_shader;
	unsigned int m_quadVAO, m_quadVBO, m_quadIB;
};

}

#endif
