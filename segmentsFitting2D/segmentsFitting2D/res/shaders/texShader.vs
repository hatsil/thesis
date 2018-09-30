#version 130

in vec2 position;
in vec2 texCoord;

out vec2 texCoord0;

void main() {
	texCoord0 = texCoord;
	gl_Position = vec4(position, 0.0, 1.0);
}