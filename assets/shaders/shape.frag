#version 330 core

out vec4 FragColor;

in vec2 texCoords;

uniform bool useTex;
uniform sampler2D texture;
uniform vec4 shapeColor;

void main() {
	if (useTex) {
		FragColor = shapeColor * texture(texture, texCoords);
	} else {
		FragColor = shapeColor;
	}
}
