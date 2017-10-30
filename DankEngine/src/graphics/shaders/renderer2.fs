R"(
#version 100

precision mediump float;
precision mediump int;

uniform sampler2D samplers[16];

varying vec4 color;
varying vec2 texCoord;
varying float tID;
varying float text;

void main() {
	vec4 tex = color;
	int t = int(tID);
	if(text < 1.0){
		if(t >= 0) {
			tex *= texture2D(samplers[t], texCoord);
		}
	} else {
		tex.a = texture2D(samplers[t], texCoord).r;
	}
	gl_FragColor = vec4(tex);

}
)"