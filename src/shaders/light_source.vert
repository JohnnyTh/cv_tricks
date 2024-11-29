#version 330

in vec2 value;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec2 val;

void main() {
    val = value;
    gl_Position = projectionMatrix * viewMatrix * vec4(value, 0.0, 1.0);
}
