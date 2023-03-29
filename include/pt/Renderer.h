#ifndef RENDERER_H
#define RENDERER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "pt/plankton.h"
#include "pt/Shader.h"

namespace pt {

// Wrapper class for OpenGL rendering, meant to be used only from main api (plankton.h) not directly.
class Renderer {
public:
	// Singleton stuff
	Renderer(Renderer const&) = delete;
	void operator=(Renderer const&) = delete;
	static Renderer& getInstance() {
		static Renderer instance;
		return instance;
	}

	void init(GLFWwindow* contextWindow, float p_frameWidth, float p_frameHeight);
	void shutdown(); // Destroy buffers and shaders.

	void clearFrame(const Color& color);
	void setView(const Camera& camera);
	void drawRect(const Rect& rect, float rotation, const Color& color);
	void drawTexture(Texture& texture, const Rect& sourceRec, const Rect& destinationRec, float rotation, const Color& tint);
private:
	Renderer():
		m_quadVAO(0),
		m_quadVBO(0),
		m_quadIB(0),
		m_frameWidth(0.0f),
		m_frameHeight(0.0f) {}

	void drawQuad(const Rect& rect, float rotation);

	Shader m_shader;
	unsigned int m_quadVAO, m_quadVBO, m_quadIB;
	float m_frameWidth, m_frameHeight;
};

}

#endif
