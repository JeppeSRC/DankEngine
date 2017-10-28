R"(
#version 100

precision mediump float;
precision mediump int;

varying vec4 color;

void main() {
	gl_FragColor = vec4(color.xyz, 1.0);

}
)"