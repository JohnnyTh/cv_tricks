#version 330

layout(location = 0) in vec3 position; // ATTRIB_VERTEX
layout(location = 1) in vec2 value;    // ATTRIB_VALUE
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec2 val;

void main() {
    val = value;
    //gl_Position = projectionMatrix * viewMatrix * vec4(value, 0.0, 1.0);
    gl_Position = vec4(position, 1.0);
}
