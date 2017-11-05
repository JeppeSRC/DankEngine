R"(

attribute vec3 position;
attribute vec2 texCoords;
attribute vec4 colors;
attribute float textureID;
attribute float tex;

uniform mat4 projection;

varying vec4 color;
varying vec2 texCoord;
varying float tID;
varying float text;

void main() {
	color = colors;
	texCoord = texCoords;
	tID = textureID;
	text = tex;

	gl_Position = projection * vec4(position, 1);
}
)"