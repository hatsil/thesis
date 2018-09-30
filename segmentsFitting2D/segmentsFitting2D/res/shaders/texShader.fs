#version 130

in vec2 texCoord0;

uniform float darkness;
uniform sampler2D sampler;

void main() {
	gl_FragColor = vec4((1 - darkness) * texture2D(sampler, texCoord0).rgb, 1);
}
