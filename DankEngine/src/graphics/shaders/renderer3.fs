R"(

precision mediump float;
precision mediump int;

in vec2 texCoord;
in vec4 color;
in float tID;
in float text;

uniform sampler2D samplers[16];

layout(location = 0) out vec4 outColor;

void main() {
	vec4 tex = color;

	int t = int(tID);
	if(text < 1.0){
		if (t == 0) {
			tex *= texture(samplers[0], texCoord);
		} else if (t == 1) {
			tex *= texture(samplers[1], texCoord);
		} else if (t == 2) {
			tex *= texture(samplers[2], texCoord);
		} else if (t == 3) {
			tex *= texture(samplers[3], texCoord);
		} else if (t == 4) {
			tex *= texture(samplers[4], texCoord);
		} else if (t == 5) {
			tex *= texture(samplers[5], texCoord);
		} else if (t == 6) {
			tex *= texture(samplers[6], texCoord);
		} else if (t == 7) {
			tex *= texture(samplers[7], texCoord);
		} else if (t == 8) {
			tex *= texture(samplers[8], texCoord);
		} else if (t == 9) {
			tex *= texture(samplers[9], texCoord);
		} else if (t == 10) {
			tex *= texture(samplers[10], texCoord);
		} else if (t == 11) {
			tex *= texture(samplers[11], texCoord);
		} else if (t == 12) {
			tex *= texture(samplers[12], texCoord);
		} else if (t == 13) {
			tex *= texture(samplers[13], texCoord);
		} else if (t == 14) {
			tex *= texture(samplers[14], texCoord);
		} else if (t == 15) {
			tex *= texture(samplers[15], texCoord);
		}
	} else {
		if (t == 0) {
			tex.w *= texture(samplers[0], texCoord).r;
		} else if (t == 1) {
			tex.w *= texture(samplers[1], texCoord).r;
		} else if (t == 2) {
			tex.w *= texture(samplers[2], texCoord).r;
		} else if (t == 3) {
			tex.w *= texture(samplers[3], texCoord).r;
		} else if (t == 4) {
			tex.w *= texture(samplers[4], texCoord).r;
		} else if (t == 5) {
			tex.w *= texture(samplers[5], texCoord).r;
		} else if (t == 6) {
			tex.w *= texture(samplers[6], texCoord).r;
		} else if (t == 7) {
			tex.w *= texture(samplers[7], texCoord).r;
		} else if (t == 8) {
			tex.w *= texture(samplers[8], texCoord).r;
		} else if (t == 9) {
			tex.w *= texture(samplers[9], texCoord).r;
		} else if (t == 10) {
			tex.w *= texture(samplers[10], texCoord).r;
		} else if (t == 11) {
			tex.w *= texture(samplers[11], texCoord).r;
		} else if (t == 12) {
			tex.w *= texture(samplers[12], texCoord).r;
		} else if (t == 13) {
			tex.w *= texture(samplers[13], texCoord).r;
		} else if (t == 14) {
			tex.w *= texture(samplers[14], texCoord).r;
		} else if (t == 15) {
			tex.w *= texture(samplers[15], texCoord).r;
		}
	}
	outColor = tex;
}

)"