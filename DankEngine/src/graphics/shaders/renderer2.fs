R"(
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
		if (t == 0) {
			tex *= texture2D(samplers[0], texCoord);
		} else if (t == 1) {
			tex *= texture2D(samplers[1], texCoord);
		} else if (t == 2) {
			tex *= texture2D(samplers[2], texCoord);
		} else if (t == 3) {
			tex *= texture2D(samplers[3], texCoord);
		} else if (t == 4) {
			tex *= texture2D(samplers[4], texCoord);
		} else if (t == 5) {
			tex *= texture2D(samplers[5], texCoord);
		} else if (t == 6) {
			tex *= texture2D(samplers[6], texCoord);
		} else if (t == 7) {
			tex *= texture2D(samplers[7], texCoord);
		} else if (t == 8) {
			tex *= texture2D(samplers[8], texCoord);
		} else if (t == 9) {
			tex *= texture2D(samplers[9], texCoord);
		} else if (t == 10) {
			tex *= texture2D(samplers[10], texCoord);
		} else if (t == 11) {
			tex *= texture2D(samplers[11], texCoord);
		} else if (t == 12) {
			tex *= texture2D(samplers[12], texCoord);
		} else if (t == 13) {
			tex *= texture2D(samplers[13], texCoord);
		} else if (t == 14) {
			tex *= texture2D(samplers[14], texCoord);
		} else if (t == 15) {
			tex *= texture2D(samplers[15], texCoord);
		}
	} else {
		if (t == 0) {
			tex.w *= texture2D(samplers[0], texCoord).r;
		} else if (t == 1) {
			tex.w *= texture2D(samplers[1], texCoord).r;
		} else if (t == 2) {
			tex.w *= texture2D(samplers[2], texCoord).r;
		} else if (t == 3) {
			tex.w *= texture2D(samplers[3], texCoord).r;
		} else if (t == 4) {
			tex.w *= texture2D(samplers[4], texCoord).r;
		} else if (t == 5) {
			tex.w *= texture2D(samplers[5], texCoord).r;
		} else if (t == 6) {
			tex.w *= texture2D(samplers[6], texCoord).r;
		} else if (t == 7) {
			tex.w *= texture2D(samplers[7], texCoord).r;
		} else if (t == 8) {
			tex.w *= texture2D(samplers[8], texCoord).r;
		} else if (t == 9) {
			tex.w *= texture2D(samplers[9], texCoord).r;
		} else if (t == 10) {
			tex.w *= texture2D(samplers[10], texCoord).r;
		} else if (t == 11) {
			tex.w *= texture2D(samplers[11], texCoord).r;
		} else if (t == 12) {
			tex.w *= texture2D(samplers[12], texCoord).r;
		} else if (t == 13) {
			tex.w *= texture2D(samplers[13], texCoord).r;
		} else if (t == 14) {
			tex.w *= texture2D(samplers[14], texCoord).r;
		} else if (t == 15) {
			tex.w *= texture2D(samplers[15], texCoord).r;
		}
	}
	gl_FragColor = tex;

}
)"