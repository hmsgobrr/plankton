#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

namespace pt {

class Texture {
public:
	Texture();

	void create(int width, int height, unsigned char* data, bool dataUsesAlpha, bool useAlpha);
	void createFromFile(const std::string& filePath, bool useAlpha);
	void use();

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
private:
	unsigned int m_id;

	int m_width, m_height;
};

}

#endif // TEXTURE_H
