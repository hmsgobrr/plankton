#ifndef RENDERER_H
#define RENDERER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

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

	void init(GLFWwindow* contextWindow);
private:
	Renderer() {}
};

}

#endif
