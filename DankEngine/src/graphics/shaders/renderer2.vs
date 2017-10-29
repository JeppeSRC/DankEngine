R"(
#version 100

attribute vec3 position;
attribute vec2 texCoords;
attribute vec4 colors;
attribute float textureID;

uniform mat4 projection;

varying vec4 color;
varying vec2 texCoord;
varying float tID;

void main() {
	color = colors;
	texCoord = texCoords;
	tID = textureID;

	gl_Position = /*projection */ vec4(position, 1);
}
)"