#version 130

in vec4 t;

uniform mat4x2 f;

void main() {
	gl_Position = vec4(f * t, 0.0, 1.0);
}