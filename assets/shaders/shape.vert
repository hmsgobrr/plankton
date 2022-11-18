#version 330 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 vertexTexCoords;

out vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;

uniform mat4 texCoordsTransform;

void main() {
   gl_Position = projection * model * vec4(vertex, 0.0f, 1.0f);
   vec4 transformedTexCoords = texCoordsTransform * vec4(vertexTexCoords, 0.0f, 1.0f);
   texCoords = vec2(transformedTexCoords.x, transformedTexCoords.y);
}
