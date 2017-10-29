R"(
#version 300 es

in vec2 texCoord;
in vec4 color;
in float tID;

uniform sampler2D samplers[16];

layout(location = 0) out vec4 outColor;

void main() {
	vec4 tex = color;

	int t = int(tID);
	if (t >= 0) {
		tex *= texture(samplers[t], texCoord);
	}
	outColor = tex;
}

)"