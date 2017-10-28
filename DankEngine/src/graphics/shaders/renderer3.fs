R"(
#version 300 es

in vec2 texCoord;
in vec4 color;

layout(location = 0) out vec4 outColor;

void main() {
	outColor = color;
}

)"