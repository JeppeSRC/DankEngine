R"(
#version 100

attribute vec3 position;
attribute vec2 texCoords;
attribute vec4 colors;

uniform mat4 projection;

varying vec4 color;

void main() {

	color = colors;

	gl_Position = /*projection */ vec4(position, 1);
}
)"