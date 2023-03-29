#include "pt/Texture.h"

#include "pt/Log.h"

#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace pt {

Texture::Texture(): m_width(0), m_height(0) {
	glGenTextures(1, &m_id);
}

void Texture::create(int width, int height, unsigned char* data, bool dataUsesAlpha, bool useAlpha) {
	m_width = width;
	m_height = height;

	glBindTexture(GL_TEXTURE_2D, m_id);

	// create texture
	unsigned int colorFormat = useAlpha ? GL_RGBA : GL_RGB;
	unsigned int dataColorFormat = dataUsesAlpha ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, m_width, m_height, 0, dataColorFormat, GL_UNSIGNED_BYTE, data);

	// set texture wrapping & filtering mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::createFromFile(const std::string& filePath, bool useAlpha) {
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
	if (!data) {
		PT_CORE_ERROR("Unable to open file: {}", filePath.c_str());
	} else{
		create(width, height, data, nrChannels == 4, useAlpha);
	}

	stbi_image_free(data);
}

void Texture::use() {
	glBindTexture(GL_TEXTURE_2D, m_id);
}

}
