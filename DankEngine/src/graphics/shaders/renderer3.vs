R"(
#version 300 es

layout(location = 0) in vec3 positions;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec4 colors;
layout(location = 3) in float texID;
layout(location = 4) in float tex;

uniform mat4 projection;

out vec2 texCoord;
out vec4 color;
out float tID;
out float text;

void main() {
	texCoord = texCoords;
	color = colors;
	tID = texID;
	text = tex;


	gl_Position = /*projection */ vec4(positions, 1);
}
)"