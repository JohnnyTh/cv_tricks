#version 330

layout (location = 0) in vec2 aPos;
out vec2 fragPos;

void main() {
    fragPos = aPos; // Pass the position to the fragment shader
    gl_Position = vec4(aPos, 0.0, 1.0);
}